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
#include "pd_dp_board_chip.h"
#include "pd_power_nx20p3483.h"

#include "clock_config.h"
#include "pin_mux.h"
#include "fsl_port.h"
#include "usb_timer.h"
#include "usb_io.h"
#if (defined PD_CONFIG_ENABLE_AUTO_POLICY) && (PD_CONFIG_ENABLE_AUTO_POLICY)
#include "usb_pd_auto_policy.h"
#endif
#include "usb_pd_alt_mode.h"
#include "usb_pd_alt_mode_dp.h"
#include "pd_crossbar_cbtl.h"
#include "pd_dp_hpd_driver.h"
#include "pd_ptn36502.h"
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
void BOARD_InitHardware(void);
void HW_GpioInit(uint8_t port);
void HW_TimerInit(void);
void HW_GpioPDPHYIntEnable(uint8_t port, uint8_t enable);
void HW_TimerCallback(void);
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
    PD_PowerSrcTurnOnDefaultVbus,  PD_PowerSrcTurnOnRequestVbus,  PD_PowerSrcTurnOffVbus,
    PD_PowerSrcGotoMinReducePower, PD_PowerSnkDrawTypeCVbus,      PD_PowerSnkDrawRequestVbus,
    PD_PowerSnkStopDrawVbus,       PD_PowerSnkGotoMinReducePower, PD_PowerControlVconn,
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

#define PD_SHIELD2_DP4LANE_PIN (2U)
#define PD_SHIELD2_DP4LANE_PORT (1)
#define PD_SHIELD2_DP4LANE_GPIO (1)

#define PD_SHIELD2_XSD_PIN (11U)
#define PD_SHIELD2_XSD_PORT (1)
#define PD_SHIELD2_XSD_GPIO (1)

#define PD_SHIELD2_ORIENT_PIN (7U)
#define PD_SHIELD2_ORIENT_PORT (3)
#define PD_SHIELD2_ORIENT_GPIO (3)

#define PD_SHIELD2_HPD_PIN (9U)
#define PD_SHIELD2_HPD_PORT (1)
#define PD_SHIELD2_HPD_GPIO (1)

#define PD_PTN5110_GPIO_INTERRUPT_PRIORITY (3)
#define PD_I2C_INTERRUPT_PRIORITY (2)
#define PD_TIMER_INTERRUPT_PRIORITY (1)

#define SYSTICK_CTRL_REG (*((volatile uint32_t *)0xe000e010))
#define SYSTICK_LOAD_REG (*((volatile uint32_t *)0xe000e014))
#define SYSTICK_CURRENT_VALUE_REG (*((volatile uint32_t *)0xe000e018))
#define SYSTICK_ENABLE_BIT (1UL << 0UL)
#define SYSTICK_CLK_BIT (1UL << 2UL)
#define SYSTICK_VALUE_MASK (0x00FFFFFFu)

#define PD_PTN36502_SLAVE_ADDRESS (0x12)
#define PD_NX20P3483_SLAVE_ADDRESS (0x72)

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
                                             .fixedPDO.operateCurrent = (3 * 100),
                                         },
                                         {
                                             /* PDO2: fixed: 9V, 2A */
                                             .PDOValue = 0,
                                             .fixedPDO.fixedSupply = kPDO_Fixed,
                                             .fixedPDO.voltage = (9 * 1000 / 50),
                                             .fixedPDO.operateCurrent = (2 * 100),
                                         }};

const static pd_dp_peripheral_interface_t s_boardChipInterface = {PD_DpBoardChipsInit, PD_DpBoardChipsDeinit,
                                                                  PD_DpBoardChipsControl};

#if (defined PD_CONFIG_ENABLE_AUTO_POLICY) && (PD_CONFIG_ENABLE_AUTO_POLICY)
static pd_auto_policy_t s_autoPolicyForAllPorts = {
    0,                          /* autoRequestPRSwapAsSource */
    0,                          /* autoRequestPRSwapAsSink */
    kAutoRequestProcess_Accept, /* autoAcceptPRSwapAsSource */
    kAutoRequestProcess_Accept, /* autoAcceptPRSwapAsSink */
    kPD_DataRoleNone,           /* autoRequestDRSwap */
    kAutoRequestProcess_Accept, /* autoAcceptDRSwapToDFP */
    kAutoRequestProcess_Reject, /* autoAcceptDRSwapToUFP */
    kPD_VconnNone,              /* autoRequestVConnSwap */
    kAutoRequestProcess_Accept, /* autoAcceptVconnSwapToOn */
    kAutoRequestProcess_Accept, /* autoAcceptVconnSwapToOff */
    0,                          /* autoSinkNegotiation */
};
#endif

#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE > 0)
/* displayport config */
const static pd_cbtl_crossbar_config_t s_CrossbarConfig1 = {
    PD_SHIELD2_ORIENT_GPIO,  /* orientControlGPIO */
    PD_SHIELD2_ORIENT_PORT,  /* orientControlPort */
    PD_SHIELD2_ORIENT_PIN,   /* orientControlPin */
    PD_SHIELD2_XSD_GPIO,     /* xsdnControlGPIO */
    PD_SHIELD2_XSD_PORT,     /* xsdnControlPort */
    PD_SHIELD2_XSD_PIN,      /* xsdnControlPin */
    PD_SHIELD2_DP4LANE_GPIO, /* dp4laneControlGPIO */
    PD_SHIELD2_DP4LANE_PORT, /* dp4laneControlPort */
    PD_SHIELD2_DP4LANE_PIN,  /* dp4laneControlPin */
};
const static pd_hpd_driver_config_t s_HpdDriverConfig1 = {
    PD_SHIELD2_HPD_GPIO, /* hpd GPIO */
    PD_SHIELD2_HPD_PORT, /* hpd port */
    PD_SHIELD2_HPD_PIN,  /* hpd pin */
};

const static pd_dp_redriver_config_t s_Ptn36502Config1 = {
    kInterface_i2c0 + BOARD_PD_I2C_INDEX, /* I2C master */
    PD_PTN36502_SLAVE_ADDRESS,            /* slave addresss */
};

const static pd_dp_peripheral_config_t s_dpBoardConfig1 = {
    (void *)&s_CrossbarConfig1, (void *) & s_HpdDriverConfig1, (void *) & s_Ptn36502Config1,
};

static pd_alt_mode_dp_host_config_t s_DPHostConfig1 = {
    &s_dpBoardConfig1,
    &s_boardChipInterface,
    kPinAssign_D | kPinAssign_C | kPinAssign_E,
    0, /* multi function prefered */
    0, /* reserved */
};

/* alt mode config */
const static pd_alt_mode_module_t s_AltModeModules1[] = {{0xFF01, &s_DPHostConfig1}};
const static pd_alt_mode_config_t s_AltModeConfig1 = {.altModeRole = kDataConfig_DFP,
                                                      .altModeHostConfig = {
                                                          .modules = &s_AltModeModules1[0], .moduleCount = 1,
                                                      }};

const static pd_power_port_config_t s_PortPowerConfig1 = {
    (uint32_t *)&s_PortSourceCaps[0],                   /* source caps */
    (uint32_t *)&s_PortSinkcaps[0],                     /* self sink caps */
    sizeof(s_PortSourceCaps) / sizeof(pd_source_pdo_t), /* source cap count */
    sizeof(s_PortSinkcaps) / sizeof(pd_sink_pdo_t),     /* sink cap count */
    kPowerConfig_DRPToggling,                           /* typec role */
    PD_DEMO_TYPEC_CURRENT,                              /* source: Rp current level */
    kTypecTry_None,                                     /* drp try function */
    kDataConfig_DRD,                                    /* data function */
    1,                                                  /* support vconn */
    0,                                                  /* reserved */
    (void *) & s_AltModeConfig1,                        /* alt mode config */
#if (defined PD_CONFIG_ENABLE_AUTO_POLICY) && (PD_CONFIG_ENABLE_AUTO_POLICY)
    (void *) & s_autoPolicyForAllPorts, /* auto policy */
#else
    NULL, /* auto policy */
#endif
    NULL,
};

pd_instance_config_t g_Port1PDConfig = {
    kDeviceType_NormalPowerPort, /* normal power port */
    PORTD_IRQn,                  /* interrupt number */
    kPD_PhyPTN5110,
    kInterface_i2c0 + BOARD_PD_I2C_INDEX,
    0x52u,
    (void *) & s_PortPowerConfig1,
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

static void HW_SystickInit(void)
{
    /* For FreeRTOS, don't need this function, FreeRTOS will initialize systick by self */
    SYSTICK_LOAD_REG = SYSTICK_VALUE_MASK;
    SYSTICK_CURRENT_VALUE_REG = 0UL;
    SYSTICK_CTRL_REG = (SYSTICK_CLK_BIT | SYSTICK_ENABLE_BIT);
}


void HW_WaitUs(uint32_t us)
{
    int32_t sysTickMaxValue = SYSTICK_LOAD_REG;
    int32_t startSystickCount = ((SYSTICK_CURRENT_VALUE_REG)&SYSTICK_VALUE_MASK);
    /* systick's clock source is core clock */
    int32_t waitCount = SystemCoreClock / 1000000 * us;
    int32_t currentCount;

    do
    {
        currentCount = ((SYSTICK_CURRENT_VALUE_REG)&SYSTICK_VALUE_MASK);
        /* systick is decreased */
        currentCount = startSystickCount - currentCount;
        if (currentCount < 0)
        {
            currentCount = (sysTickMaxValue + currentCount);
        }
    } while (currentCount < waitCount);
}

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
    enable = !enable;
    if (enable)
    {
        USB_GpioOutputWritePin(PD_EXTRA_SRC_GPIO, PD_EXTRA_SRC_PORT, PD_EXTRA_SRC_PIN, 1);
    }
    else
    {
        USB_GpioOutputWritePin(PD_EXTRA_SRC_GPIO, PD_EXTRA_SRC_PORT, PD_EXTRA_SRC_PIN, 0);
    }
}

void HW_GpioInit(uint8_t port)
{
    if (port != 1)
    {
        return;
    }
    /* the external power control pin */
    USB_GpioOutputInit(PD_SHIELD2_DP4LANE_GPIO, PD_SHIELD2_DP4LANE_PORT, PD_SHIELD2_DP4LANE_PIN, 0);
    USB_GpioOutputInit(PD_SHIELD2_XSD_GPIO, PD_SHIELD2_XSD_PORT, PD_SHIELD2_XSD_PIN, 0);
    USB_GpioOutputInit(PD_SHIELD2_ORIENT_GPIO, PD_SHIELD2_ORIENT_PORT, PD_SHIELD2_ORIENT_PIN, 0);
    USB_GpioOutputInit(PD_SHIELD2_HPD_GPIO, PD_SHIELD2_HPD_PORT, PD_SHIELD2_HPD_PIN, 0);
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


void PD_BMEnterCritical(uint32_t *sr)
{
    *sr = DisableGlobalIRQ();
    __ASM("CPSID i");
}

void PD_BMExitCritical(uint32_t sr)
{
    EnableGlobalIRQ(sr);
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
            uint8_t getInfo;

            PD_NX20PExitDeadBatteryMode(pdAppInstance->portNumber);
            pdAppInstance->partnerSourceCapNumber = 0;
            pdAppInstance->partnerSinkCapNumber = 0;
            pdAppInstance->portShieldVersion = 0;
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

pd_status_t PD_StackDemoAppCallback(void *callbackParam, uint32_t event, void *param)
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

        case PD_DPM_ALTMODE_DP_DFP_MODE_CONFIGURED:
            PRINTF("enter and configure DP\r\n");
            break;

        case PD_DPM_ALTMODE_DP_DFP_MODE_UNCONFIGURED:
            PRINTF("Exit DP\r\n");
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
        if (PD_InstanceInit(&pdAppInstance->pdHandle, PD_StackDemoAppCallback, &callbackFunctions, pdAppInstance,
                            g_PortsConfigArray[index]) != kStatus_PD_Success)
        {
            PRINTF("pd port %d init fail\r\n", pdAppInstance->portNumber);
        }
        else
        {
            PD_PowerBoardControlInit(pdAppInstance->portNumber, pdAppInstance->pdHandle);

            pdAppInstance->msgSop = kPD_MsgSOP;
            pdAppInstance->partnerSourceCapNumber = 0;
            pdAppInstance->partnerSinkCapNumber = 0;
            /* evaluate result */
            pdAppInstance->prSwapAccept = 1;
            pdAppInstance->vconnSwapAccept = 1;
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
    PD_DpBoardChip1msIsr();
    g_SoftTimerCount++;
}

int main(void)
{
    uint8_t index;
    BOARD_InitPins();
    BOARD_BootClockHSRUN();
    BOARD_I2C1_ReleaseBus();
    BOARD_InitDebugConsole();
    HW_SystickInit();

    HW_I2CInit();
    HW_TimerInit();
    PD_AppInit();

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
        PD_AltModeTask();
        PD_DpBoardChipTask();
    }
}
