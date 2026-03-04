/*
 * Copyright 2016 - 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "usb_pd_config.h"
#include "usb_pd.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "pd_app.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "board.h"
#include "pd_power_interface.h"
#include "pd_board_config.h"

#include "clock_config.h"
#include "pin_mux.h"
#include "fsl_port.h"
#include "usb_timer.h"
#include "usb_io.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if (PD_DEMO_PORTS_COUNT > PD_CONFIG_MAX_PORT)
#error "please increase the instance count"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void HW_I2CInit(void);
void PD_DemoInit(void);
void PD_DemoTaskFun(void);
void BOARD_InitHardware(void);
void HW_GpioInit(uint8_t port);
void HW_TimerInit(void);
void HW_GpioPDPHYIntEnable(uint8_t port, uint8_t enable);
void HW_TimerCallback(void);
pd_status_t PD_PowerBoardReset(uint8_t port);
pd_status_t PD_DpmAppCommandCallback(void *callbackParam, uint32_t event, void *param);

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE > 0)
pd_app_t g_PDAppInstancePort1;
#endif
#if (defined PD_DEMO_PORT2_ENABLE) && (PD_DEMO_PORT2_ENABLE > 0)
pd_app_t g_PDAppInstancePort2;
#endif
#if (defined PD_DEMO_PORT3_ENABLE) && (PD_DEMO_PORT3_ENABLE > 0)
pd_app_t g_PDAppInstancePort3;
#endif
#if (defined PD_DEMO_PORT4_ENABLE) && (PD_DEMO_PORT4_ENABLE > 0)
pd_app_t g_PDAppInstancePort4;
#endif

extern pd_instance_config_t *g_PortsConfigArray[];
pd_app_t *g_PDAppInstanceArray[] = {
#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE > 0)
    &g_PDAppInstancePort1,
#endif
#if (defined PD_DEMO_PORT2_ENABLE) && (PD_DEMO_PORT2_ENABLE > 0)
    &g_PDAppInstancePort2,
#endif
#if (defined PD_DEMO_PORT3_ENABLE) && (PD_DEMO_PORT3_ENABLE > 0)
    &g_PDAppInstancePort3,
#endif
#if (defined PD_DEMO_PORT3_ENABLE) && (PD_DEMO_PORT4_ENABLE > 0)
    &g_PDAppInstancePort4,
#endif
};

pd_power_handle_callback_t callbackFunctions = {
    PD_PowerSrcTurnOnDefaultVbus,
    PD_PowerSrcTurnOnRequestVbus,
    PD_PowerSrcTurnOffVbus,
    PD_PowerSrcGotoMinReducePower,
    NULL,
    NULL,
    NULL,
    NULL,
    PD_PowerControlVconn,
};
volatile uint32_t g_SoftTimerCount;
/*******************************************************************************
 * Code
 ******************************************************************************/
void BOARD_I2C1_ReleaseBus(void);
#define I2C_RELEASE_BUS_COUNT 100U
#define PD_I2C_SCL (1U)
#define PD_I2C_SDA (2U)
#define PD_I2C_PORT (2)
#define PD_I2C_GPIO (2)
#define PD_PHY_INTERRUPT_PIN (6U)
#define PD_PHY_INTERRUPT_PORT (3)
#define PD_PHY_INTERRUPT_GPIO (3)
#define PD_EXTRA_SRC_PIN (10U)
#define PD_EXTRA_SRC_PORT (1)
#define PD_EXTRA_SRC_GPIO (1)
#define PD_TIMER_INSTANCE (0)

#define PD_PTN5110_GPIO_INTERRUPT_PRIORITY (3)
#define PD_I2C_INTERRUPT_PRIORITY (2)
#define PD_TIMER_INTERRUPT_PRIORITY (1)

static pd_source_pdo_t s_PortSourceCaps[] = {
    {
        /* PDO1: fixed supply: dual-role power; Externally Powered; no USB communication; dual-role data; 5V; 3A */
        .PDOValue = 0,
        .fixedPDO.dualRoleData = 1,
        .fixedPDO.dualRolePower = 1,
        .fixedPDO.externalPowered = 1,
        .fixedPDO.fixedSupply = kPDO_Fixed,
        .fixedPDO.maxCurrent = (3 * 100),
        .fixedPDO.peakCurrent = 0,
#if ((defined PD_CONFIG_REVISION) && (PD_CONFIG_REVISION >= PD_SPEC_REVISION_30))
        .fixedPDO.unchunkedSupported = 1,
#endif
        .fixedPDO.usbCommunicationsCapable = 0,
        .fixedPDO.usbSuspendSupported = 0,
        .fixedPDO.voltage = (5 * 1000 / 50),
    },
    {
        /* PDO2: fixed Supply: 9V - 2A */
        .PDOValue = 0,
        .fixedPDO.fixedSupply = kPDO_Fixed,
        .fixedPDO.maxCurrent = (2 * 100),
        .fixedPDO.voltage = (9 * 1000 / 50),
    },
};

static pd_power_port_config_t s_PortPowerConfig = {
    (uint32_t *)&s_PortSourceCaps[0],                   /* source caps */
    NULL,                                               /* self sink caps */
    sizeof(s_PortSourceCaps) / sizeof(pd_source_pdo_t), /* source cap count */
    0,                                                  /* sink cap count */
    kPowerConfig_SourceOnly,                            /* typec role */
    PD_DEMO_TYPEC_CURRENT,                              /* source: Rp current level */
    kTypecTry_None,                                     /* drp try function */
    kDataConfig_DFP,                                    /* data function */
    1,                                                  /* support vconn */
    0,                                                  /* reserved */
    NULL,
    NULL,
    NULL,
};

#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE)
pd_instance_config_t g_Port1PDConfig = {
    kDeviceType_NormalPowerPort, /* normal power port */
    PORTD_IRQn,                  /* interrupt number */
    kPD_PhyPTN5110,
    kInterface_i2c0 + BOARD_PD_I2C_INDEX,
    0x50u,
    &s_PortPowerConfig,
};
#endif

pd_instance_config_t *g_PortsConfigArray[] = {
#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE)
    &g_Port1PDConfig,
#endif
};


void HW_I2CInit(void)
{
    CLOCK_SetIpSrc(kCLOCK_Lpi2c1, kCLOCK_IpSrcFircAsync);
    NVIC_SetPriority(BOARD_PD_I2C_IRQ, PD_I2C_INTERRUPT_PRIORITY);
}

void HW_TimerInit(void)
{
    CLOCK_SetIpSrc(kCLOCK_Lpit0, kCLOCK_IpSrcSircAsync);
    NVIC_SetPriority(LPIT0_IRQn, PD_TIMER_INTERRUPT_PRIORITY);
    USB_TimerInit(PD_TIMER_INSTANCE, 1000U, CLOCK_GetIpFreq(kCLOCK_Lpit0), HW_TimerCallback);
    USB_TimerInt(PD_TIMER_INSTANCE, 1);
}

#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE)
extern void HW_GpioPDPHYPort1IntCallback(void);
void PORTD_IRQHandler(void)
{
    GPIO_Type *gpioList[] = GPIO_BASE_PTRS;

    if (GPIO_PortGetInterruptFlags(gpioList[PD_PHY_INTERRUPT_GPIO]) & (0x01u << PD_PHY_INTERRUPT_PIN))
    {
        GPIO_PortClearInterruptFlags(gpioList[PD_PHY_INTERRUPT_GPIO], (0x01u << PD_PHY_INTERRUPT_PIN));
        if (!GPIO_PinRead(gpioList[PD_PHY_INTERRUPT_GPIO], PD_PHY_INTERRUPT_PIN))
        {
            HW_GpioPDPHYPort1IntCallback();
        }
    }
}
#endif

void HW_GpioPDPHYIntEnable(uint8_t port, uint8_t enable)
{
    if (port != 1)
    {
        return;
    }
    if (enable)
    {
        USB_GpioInterruptEnable(PD_PHY_INTERRUPT_GPIO, PD_PHY_INTERRUPT_PORT, PD_PHY_INTERRUPT_PIN, 1);
        NVIC_EnableIRQ(PORTD_IRQn);
    }
    else
    {
        USB_GpioInterruptEnable(PD_PHY_INTERRUPT_GPIO, PD_PHY_INTERRUPT_PORT, PD_PHY_INTERRUPT_PIN, 0);
        NVIC_DisableIRQ(PORTD_IRQn);
    }
}

void HW_GpioExternalSourceEnable(uint8_t port, uint8_t enable)
{
    if (enable)
    {
        USB_GpioOutputWritePin(PD_EXTRA_SRC_GPIO, PD_EXTRA_SRC_PORT, PD_EXTRA_SRC_PIN, 1);
    }
    else
    {
        USB_GpioOutputWritePin(PD_EXTRA_SRC_GPIO, PD_EXTRA_SRC_PORT, PD_EXTRA_SRC_PIN, 0);
    }
}

extern void HW_GpioPDPHYPort1IntCallback(void);
void HW_GpioInit(uint8_t port)
{
    if (port != 1)
    {
        return;
    }
    /* the external power control pin */
    USB_GpioOutputInit(PD_EXTRA_SRC_GPIO, PD_EXTRA_SRC_PORT, PD_EXTRA_SRC_PIN, 0);

    /* the PD PHY interrupt gpio */
    USB_GpioInterruptInit(PD_PHY_INTERRUPT_GPIO, PD_PHY_INTERRUPT_PORT, PD_PHY_INTERRUPT_PIN,
                          kUSB_GpioInterruptLogicZero, HW_GpioPDPHYPort1IntCallback);
    NVIC_SetPriority((IRQn_Type)PORTD_IRQn, PD_PTN5110_GPIO_INTERRUPT_PRIORITY);
}

uint32_t LPI2C1_GetFreq(void)
{
    return CLOCK_GetIpFreq(kCLOCK_Lpi2c1);
}

static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < I2C_RELEASE_BUS_COUNT; i++)
    {
        __NOP();
    }
}

void BOARD_I2C1_ReleaseBus(void)
{
    uint8_t i = 0;
    port_pin_config_t i2c_pin_config = {0};
    PORT_Type *portList[] = PORT_BASE_PTRS;

    CLOCK_EnableClock(kCLOCK_PortC);
    /* Config pin mux as gpio */
    i2c_pin_config.pullSelect = kPORT_PullUp;
    i2c_pin_config.mux = kPORT_MuxAsGpio;
    PORT_SetPinConfig(portList[PD_I2C_PORT], PD_I2C_SCL, &i2c_pin_config);
    PORT_SetPinConfig(portList[PD_I2C_PORT], PD_I2C_SDA, &i2c_pin_config);

    USB_GpioOutputInit(PD_I2C_GPIO, PD_I2C_PORT, PD_I2C_SCL, 1);
    USB_GpioOutputInit(PD_I2C_GPIO, PD_I2C_PORT, PD_I2C_SDA, 1);

    /* Drive SDA low first to simulate a start */
    USB_GpioOutputWritePin(PD_I2C_GPIO, PD_I2C_PORT, PD_I2C_SDA, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA high */
    for (i = 0; i < 9; i++)
    {
        USB_GpioOutputWritePin(PD_I2C_GPIO, PD_I2C_PORT, PD_I2C_SCL, 0U);
        i2c_release_bus_delay();

        USB_GpioOutputWritePin(PD_I2C_GPIO, PD_I2C_PORT, PD_I2C_SDA, 1U);
        i2c_release_bus_delay();

        USB_GpioOutputWritePin(PD_I2C_GPIO, PD_I2C_PORT, PD_I2C_SCL, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    USB_GpioOutputWritePin(PD_I2C_GPIO, PD_I2C_PORT, PD_I2C_SCL, 0U);
    i2c_release_bus_delay();

    USB_GpioOutputWritePin(PD_I2C_GPIO, PD_I2C_PORT, PD_I2C_SDA, 0U);
    i2c_release_bus_delay();

    USB_GpioOutputWritePin(PD_I2C_GPIO, PD_I2C_PORT, PD_I2C_SCL, 1U);
    i2c_release_bus_delay();

    USB_GpioOutputWritePin(PD_I2C_GPIO, PD_I2C_PORT, PD_I2C_SDA, 1U);
    i2c_release_bus_delay();
}


#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE > 0)
void HW_GpioPDPHYPort1IntCallback(void)
{
    PD_PTN5110IsrFunction(g_PDAppInstancePort1.pdHandle);
}
#endif

#if (defined PD_DEMO_PORT2_ENABLE) && (PD_DEMO_PORT2_ENABLE > 0)
void HW_GpioPDPHYPort2IntCallback(void)
{
    PD_PTN5110IsrFunction(g_PDAppInstancePort2.pdHandle);
}
#endif

#if (defined PD_DEMO_PORT3_ENABLE) && (PD_DEMO_PORT3_ENABLE > 0)
void HW_GpioPDPHYPort3IntCallback(void)
{
    PD_PTN5110IsrFunction(g_PDAppInstancePort3.pdHandle);
}
#endif

#if (defined PD_DEMO_PORT4_ENABLE) && (PD_DEMO_PORT4_ENABLE > 0)
void HW_GpioPDPHYPort4IntCallback(void)
{
    PD_PTN5110IsrFunction(g_PDAppInstancePort4.pdHandle);
}
#endif

pd_status_t PD_DpmConnectCallback(void *callbackParam, uint32_t event, void *param)
{
    pd_status_t status = kStatus_PD_Error;
    pd_app_t *pdAppInstance = (pd_app_t *)callbackParam;

    switch (event)
    {
        case PD_DISCONNECTED:
            PD_PowerBoardReset(pdAppInstance->portNumber);
            PRINTF("port %d disconnect\r\n", pdAppInstance->portNumber);
            status = kStatus_PD_Success;
            break;

        case PD_CONNECT_ROLE_CHANGE:
        case PD_CONNECTED:
        {
            uint8_t roleInfo;

            PD_Control(pdAppInstance->pdHandle, PD_CONTROL_GET_POWER_ROLE, &roleInfo);
            if (roleInfo == kPD_PowerRoleSource)
            {
                PRINTF("port %d provide default 5V vbus\r\n", pdAppInstance->portNumber);
            }

            status = kStatus_PD_Success;
            break;
        }

        default:
            break;
    }

    return status;
}

pd_status_t PD_DpmDemoAppCallback(void *callbackParam, uint32_t event, void *param)
{
    pd_status_t status = kStatus_PD_Error;

    switch (event)
    {
        case PD_FUNCTION_DISABLED:
            /* need hard or software reset */
            status = kStatus_PD_Success;
            break;

        case PD_CONNECTED:
        case PD_CONNECT_ROLE_CHANGE:
        case PD_DISCONNECTED:
            status = PD_DpmConnectCallback(callbackParam, event, param);
            break;

        default:
            status = PD_DpmAppCommandCallback(callbackParam, event, param);
            break;
    }
    return status;
}

void PD_AppInit(void)
{
    uint8_t index;
    pd_app_t *pdAppInstance;
    pd_app_t *pdAppInstanceArray[] =
    {
#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE > 0)
        &g_PDAppInstancePort1,
#else
        NULL,
#endif
#if (defined PD_DEMO_PORT2_ENABLE) && (PD_DEMO_PORT2_ENABLE > 0)
        &g_PDAppInstancePort2,
#else
        NULL,
#endif
#if (defined PD_DEMO_PORT3_ENABLE) && (PD_DEMO_PORT3_ENABLE > 0)
        &g_PDAppInstancePort3,
#else
        NULL,
#endif
#if (defined PD_DEMO_PORT3_ENABLE) && (PD_DEMO_PORT4_ENABLE > 0)
        &g_PDAppInstancePort4,
#else
        NULL,
#endif
    };

    g_SoftTimerCount = 0;
    for (index = 0; index < 4; ++index)
    {
        if (pdAppInstanceArray[index] != NULL)
        {
            pdAppInstanceArray[index]->portNumber = (index + 1);
            HW_GpioInit((index + 1));
        }
    }

    for (index = 0; index < PD_DEMO_PORTS_COUNT; ++index)
    {
        pdAppInstance = g_PDAppInstanceArray[index];
        pdAppInstance->pdHandle = NULL;
        pdAppInstance->pdConfigParam = g_PortsConfigArray[index];
        if (PD_InstanceInit(&pdAppInstance->pdHandle, PD_DpmDemoAppCallback, &callbackFunctions, pdAppInstance,
                            g_PortsConfigArray[index]) != kStatus_PD_Success)
        {
            PRINTF("pd port %d init fail\r\n", pdAppInstance->portNumber);
        }
        else
        {
            PD_PowerBoardControlInit(pdAppInstance->portNumber, pdAppInstance->pdHandle);

            pdAppInstance->msgSop = kPD_MsgSOP;
            PRINTF("pd port %d init success\r\n", pdAppInstance->portNumber);
        }
    }
}

/* ms */
uint32_t PD_DemoSoftTimer_msGet(void)
{
    return g_SoftTimerCount;
}

/* ms */
uint32_t PD_DemoSoftTimer_getInterval(uint32_t startTime)
{
    if (g_SoftTimerCount >= startTime)
    {
        return (g_SoftTimerCount - startTime);
    }
    else
    {
        return (0xFFFFFFFFu - (startTime - g_SoftTimerCount));
    }
}

void HW_TimerCallback(void)
{
    /* Callback into timer service */
    uint8_t index;
    for (index = 0; index < PD_DEMO_PORTS_COUNT; ++index)
    {
        PD_TimerIsrFunction(g_PDAppInstanceArray[index]->pdHandle);
    }
    g_SoftTimerCount++;
}

#if (defined PD_CONFIG_COMMON_TASK) && (PD_CONFIG_COMMON_TASK)
void PD_PortsTask(void *arg)
{
    for (uint8_t index = 0; index < PD_DEMO_PORTS_COUNT; ++index)
    {
        HW_GpioPDPHYIntEnable(g_PDAppInstanceArray[index]->portNumber, 1);
    }
    while (1)
    {
        PD_Task();
    }
}
#else
void PD_PortTask(void *arg)
{
    pd_app_t *pdAppInstance = (pd_app_t *)arg;
    HW_GpioPDPHYIntEnable(pdAppInstance->portNumber, 1);
    while (1)
    {
        PD_InstanceTask(pdAppInstance->pdHandle);
    }
}
#endif

static void pd_demo_task(void *arg)
{
    HW_I2CInit();
    HW_TimerInit();
    PD_AppInit();
    PD_DemoInit();

#if (defined PD_CONFIG_COMMON_TASK) && (PD_CONFIG_COMMON_TASK)
    if (xTaskCreate(PD_PortsTask, "PD", (2048u) / sizeof(portSTACK_TYPE), NULL, 5, NULL) != pdPASS)
    {
        PRINTF("create task error\r\n");
    }
#else
    for (uint8_t index = 0; index < PD_DEMO_PORTS_COUNT; ++index)
    {
        if (xTaskCreate(PD_PortTask, "port", (1024u + 512u) / sizeof(portSTACK_TYPE), g_PDAppInstanceArray[index], 5,
                        NULL) != pdPASS)
        {
            PRINTF("create task error\r\n");
        }
    }
#endif

    vTaskDelete(NULL);
}

int main(void)
{
    BOARD_InitPins();
    BOARD_BootClockHSRUN();
    BOARD_I2C1_ReleaseBus();
    BOARD_InitDebugConsole();

    if (xTaskCreate(pd_demo_task, "demo", 1024 / sizeof(portSTACK_TYPE), NULL, 4, NULL) != pdPASS)
    {
        PRINTF("create demo task error\r\n");
    }

    vTaskStartScheduler();

    while (1)
    {
        ;
    }
}
