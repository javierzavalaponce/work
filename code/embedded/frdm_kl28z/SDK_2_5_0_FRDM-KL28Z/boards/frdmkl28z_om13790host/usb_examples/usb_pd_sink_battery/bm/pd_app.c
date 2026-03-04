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
#include "pd_app.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "board.h"
#include "pd_power_interface.h"
#include "pd_board_config.h"
#include "pd_power_nx20p3483.h"

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
void PD_Demo1msIsrProcess(void);
void HW_GpioInit(uint8_t port);
void HW_TimerInit(void);
void HW_GpioPDPHYIntEnable(uint8_t port, uint8_t enable);
void HW_TimerCallback(void);
pd_status_t PD_PowerBoardReset(uint8_t port);
void PD_DemoReset(pd_app_t *pdAppInstance);
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
    NULL,
    NULL,
    NULL,
    NULL,
    PD_PowerSnkDrawTypeCVbus,
    PD_PowerSnkDrawRequestVbus,
    PD_PowerSnkStopDrawVbus,
    PD_PowerSnkGotoMinReducePower,
    PD_PowerControlVconn,
};

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

#define PD_NX20P3483_SLAVE_ADDRESS (0x72)

static pd_sink_pdo_t s_PortSinkcaps[] = {{
                                             /* PDO1: fixed:5.0V, 3A */
                                             .PDOValue = 0,
                                             .fixedPDO.fixedSupply = kPDO_Fixed,
                                             .fixedPDO.dualRoleData = 1,
                                             .fixedPDO.dualRolePower = 1,
                                             .fixedPDO.externalPowered = 1,
#if ((defined PD_CONFIG_REVISION) && (PD_CONFIG_REVISION >= PD_SPEC_REVISION_30))
#if (defined PD_CONFIG_COMPLIANCE_TEST_ENABLE) && (PD_CONFIG_COMPLIANCE_TEST_ENABLE)
                                             .fixedPDO.frSwapRequiredCurrent = 0,
#else
                                             .fixedPDO.frSwapRequiredCurrent = kFRSwap_CurrentDefaultUSB,
#endif
#endif
                                             .fixedPDO.higherCapability = 1,
                                             .fixedPDO.usbCommunicationsCapable = 0,
                                             .fixedPDO.voltage = (5 * 1000 / 50),
                                             .fixedPDO.operateCurrent = (2 * 100),
                                         },
                                         {
                                             /* PDO2: fixed: 9V, 2A */
                                             .PDOValue = 0,
                                             .fixedPDO.fixedSupply = kPDO_Fixed,
                                             .fixedPDO.voltage = (9 * 1000 / 50),
                                             .fixedPDO.operateCurrent = (2 * 100),
                                         }};

static pd_power_port_config_t s_PortPowerConfig = {
    NULL,                                           /* source caps */
    (uint32_t *)&s_PortSinkcaps[0],                 /* self sink caps */
    0,                                              /* source cap count */
    sizeof(s_PortSinkcaps) / sizeof(pd_sink_pdo_t), /* sink cap count */
    kPowerConfig_SinkOnly,                          /* typec role */
    kCurrent_Invalid,                               /* source: Rp current level */
    kTypecTry_None,                                 /* drp try function */
    kDataConfig_DRD,                                /* data function */
    0,                                              /* support vconn */
    0,                                              /* reserved */
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
    0x52u,
    &s_PortPowerConfig,
};
#endif

pd_instance_config_t *g_PortsConfigArray[] = {
#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE)
    &g_Port1PDConfig,
#endif
};

pd_nx20p_config_t g_PortsNX20PConfigArray[] = {
    {kInterface_i2c0 + BOARD_PD_I2C_INDEX, PD_NX20P3483_SLAVE_ADDRESS},
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

void HW_GpioInit(uint8_t port)
{
    /* the external power control pin */
    USB_GpioOutputInit(PD_EXTRA_SRC_GPIO, PD_EXTRA_SRC_PORT, PD_EXTRA_SRC_PIN, 1);

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
            PD_DemoReset(pdAppInstance);
            PRINTF("port %d disconnect\r\n", pdAppInstance->portNumber);
            status = kStatus_PD_Success;
            break;

        case PD_CONNECT_ROLE_CHANGE:
        case PD_CONNECTED:
        {
            uint8_t getInfo;

            PD_NX20PExitDeadBatteryMode(pdAppInstance->portNumber);
            PD_DemoReset(pdAppInstance);
            pdAppInstance->partnerSourceCapNumber = 0;
            PD_Control(pdAppInstance->pdHandle, PD_CONTROL_GET_POWER_ROLE, &getInfo);

            PRINTF((event == PD_CONNECTED) ? "port %d connected," : "port %d connect change,",
                   pdAppInstance->portNumber);
            PRINTF(" power role:%s,", (getInfo == kPD_PowerRoleSource) ? "Source" : "Sink");
            PD_Control(pdAppInstance->pdHandle, PD_CONTROL_GET_DATA_ROLE, &getInfo);
            PRINTF(" data role:%s,", (getInfo == kPD_DataRoleDFP) ? "DFP" : "UFP");
            PD_Control(pdAppInstance->pdHandle, PD_CONTROL_GET_VCONN_ROLE, &getInfo);
            PRINTF(" vconn source:%s\r\n", (getInfo == kPD_IsVconnSource) ? "yes" : "no");
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
    pd_app_t *pdAppInstance = (pd_app_t *)callbackParam;

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

        case PD_DPM_OVP_OCP_FAULT:
            PD_NX20PClearInt(pdAppInstance->portNumber);
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
            pdAppInstance->partnerSourceCapNumber = 0;
            /* alternate mode (VDM) */
            pdAppInstance->selfVdmIdentity.idHeaderVDO.vdoValue = 0;
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.modalOperateSupport = 1;
#if ((defined PD_CONFIG_REVISION) && (PD_CONFIG_REVISION >= PD_SPEC_REVISION_30))
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.productTypeDFP = 2; /* PDUSB Host */
#endif
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.productTypeUFPOrCablePlug = 2; /* PDUSB Peripheral */
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.usbCommunicationCapableAsDevice = 0;
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.usbCommunicationCapableAsHost = 0;
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.usbVendorID = PD_VENDOR_VID;
            pdAppInstance->selfVdmIdentity.pid = PD_CONFIG_PID;
            pdAppInstance->selfVdmIdentity.certStatVDO = PD_CONFIG_XID;
            pdAppInstance->selfVdmIdentity.bcdDevice = PD_CONFIG_BCD_DEVICE;
            pdAppInstance->selfVdmSVIDs = ((uint32_t)PD_VENDOR_VID << 16); /* only one SVID (display port) */
            PRINTF("pd port %d init success\r\n", pdAppInstance->portNumber);
        }
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

    PD_Demo1msIsrProcess();
}

int main(void)
{
    uint8_t index;

    BOARD_InitPins();
    BOARD_BootClockHSRUN();
    BOARD_I2C1_ReleaseBus();
    BOARD_InitDebugConsole();

    HW_I2CInit();
    HW_TimerInit();
    PD_AppInit();
    PD_DemoInit();

    for (index = 0; index < PD_DEMO_PORTS_COUNT; ++index)
    {
        if (g_PDAppInstanceArray[index]->pdHandle != NULL)
        {
            HW_GpioPDPHYIntEnable(g_PDAppInstanceArray[index]->portNumber, 1);
        }
    }

    while (1)
    {
#if (defined PD_CONFIG_COMMON_TASK) && (PD_CONFIG_COMMON_TASK)
        PD_Task();
#else
        for (index = 0; index < PD_DEMO_PORTS_COUNT; ++index)
        {
            PD_InstanceTask(g_PDAppInstanceArray[index]->pdHandle);
        }
#endif
        PD_DemoTaskFun();
    }
}
