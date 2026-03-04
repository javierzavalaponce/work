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

#include "clock_config.h"
#include "pin_mux.h"
#include "fsl_port.h"
#include "usb_timer.h"
#include "usb_io.h"
#if (defined PD_CONFIG_ENABLE_AUTO_POLICY) && (PD_CONFIG_ENABLE_AUTO_POLICY)
#include "usb_pd_auto_policy.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if (PD_DEMO_PORTS_COUNT > PD_CONFIG_MAX_PORT)
#error "please increase the instance count"
#endif

/* The follow MACROs are for passing compliance test, it is not actual product logical */
#define PD_SOURCE_POWER (18) /* W */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void HW_I2CInit(void);
void PD_DemoInit(void);
void PD_DemoTaskFun(void);
void BOARD_InitHardware(void);
#if (defined BOARD_PD_SW_INPUT_SUPPORT) && (BOARD_PD_SW_INPUT_SUPPORT)
void PD_Demo1msIsrProcessSW(pd_app_t *pdAppInstance);
#endif
void HW_GpioInit(uint8_t port);
void HW_TimerInit(void);
void HW_GpioPDPHYIntEnable(uint8_t port, uint8_t enable);
void HW_TimerCallback(void);
pd_status_t PD_DpmAppCommandCallback(void *callbackParam, uint32_t event, void *param);
#if (defined BOARD_PD_USB3_CROSS_SUPPORT) && (BOARD_PD_USB3_CROSS_SUPPORT)
void HW_GpioUSB3CrossControl(uint8_t port, uint8_t value);
#endif

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

pd_demo_global_t g_DemoGlobal;
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
#define PD_CROSS_PIN (2)
#define PD_CROSS_PORT (1)
#define PD_CROSS_GPIO (1)

#define PD_PTN5110_GPIO_INTERRUPT_PRIORITY (3)
#define PD_I2C_INTERRUPT_PRIORITY (2)
#define PD_TIMER_INTERRUPT_PRIORITY (1)

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

#if (defined PD_CONFIG_ENABLE_AUTO_POLICY) && (PD_CONFIG_ENABLE_AUTO_POLICY)
#if (defined PD_TEST_ENABLE_AUTO_POLICY)
#if (PD_TEST_ENABLE_AUTO_POLICY == 1)
static pd_auto_policy_t s_autoPolicy1 = {
    0,                          /* autoRequestPRSwapAsSource */
    0,                          /* autoRequestPRSwapAsSink */
    kAutoRequestProcess_Accept, /* autoAcceptPRSwapAsSource */
    kAutoRequestProcess_Accept, /* autoAcceptPRSwapAsSink */
    kPD_DataRoleNone,           /* autoRequestDRSwap */
    kAutoRequestProcess_Accept, /* autoAcceptDRSwapToDFP */
    kAutoRequestProcess_Accept, /* autoAcceptDRSwapToUFP */
    kPD_VconnNone,              /* autoRequestVConnSwap */
    kAutoRequestProcess_Accept, /* autoAcceptVconnSwapToOn */
    kAutoRequestProcess_Accept, /* autoAcceptVconnSwapToOff */
    0,                          /* autoSinkNegotiation */
};
#endif

#if (PD_TEST_ENABLE_AUTO_POLICY == 2)
static pd_auto_policy_t s_autoPolicy2 = {
    0,                          /* autoRequestPRSwapAsSource */
    1,                          /* autoRequestPRSwapAsSink */
    kAutoRequestProcess_Reject, /* autoAcceptPRSwapAsSource */
    kAutoRequestProcess_Accept, /* autoAcceptPRSwapAsSink */
    kPD_DataRoleNone,           /* autoRequestDRSwap */
    kAutoRequestProcess_Accept, /* autoAcceptDRSwapToDFP */
    kAutoRequestProcess_Reject, /* autoAcceptDRSwapToUFP */
    kPD_VconnNone,              /* autoRequestVConnSwap */
    kAutoRequestProcess_Accept, /* autoAcceptVconnSwapToOn */
    kAutoRequestProcess_Reject, /* autoAcceptVconnSwapToOff */
    1,                          /* autoSinkNegotiation */
};
#endif

#if (PD_TEST_ENABLE_AUTO_POLICY == 3)
static pd_auto_policy_t s_autoPolicy3 = {
    0,                          /* autoRequestPRSwapAsSource */
    0,                          /* autoRequestPRSwapAsSink */
    kAutoRequestProcess_Accept, /* autoAcceptPRSwapAsSource */
    kAutoRequestProcess_Reject, /* autoAcceptPRSwapAsSink */
    kPD_DataRoleDFP,            /* autoRequestDRSwap */
    kAutoRequestProcess_Reject, /* autoAcceptDRSwapToDFP */
    kAutoRequestProcess_Accept, /* autoAcceptDRSwapToUFP */
    kPD_VconnNone,              /* autoRequestVConnSwap */
    kAutoRequestProcess_Reject, /* autoAcceptVconnSwapToOn */
    kAutoRequestProcess_Accept, /* autoAcceptVconnSwapToOff */
    0,                          /* autoSinkNegotiation */
};
#endif

#if (PD_TEST_ENABLE_AUTO_POLICY == 4)
static pd_auto_policy_t s_autoPolicy4 = {
    0,                          /* autoRequestPRSwapAsSource */
    0,                          /* autoRequestPRSwapAsSink */
    kAutoRequestProcess_Reject, /* autoAcceptPRSwapAsSource */
    kAutoRequestProcess_Reject, /* autoAcceptPRSwapAsSink */
    kPD_DataRoleNone,           /* autoRequestDRSwap */
    kAutoRequestProcess_Reject, /* autoAcceptDRSwapToDFP */
    kAutoRequestProcess_Reject, /* autoAcceptDRSwapToUFP */
    kPD_IsVconnSource,          /* autoRequestVConnSwap */
    kAutoRequestProcess_Reject, /* autoAcceptVconnSwapToOn */
    kAutoRequestProcess_Reject, /* autoAcceptVconnSwapToOff */
    0,                          /* autoSinkNegotiation */
};
#endif
#endif
#endif

#if (defined PD_COMPLIANCE_TEST_DRP) && (PD_COMPLIANCE_TEST_DRP)
static pd_power_port_config_t s_PortPowerConfig = {
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
    NULL,                                               /* alt mode config */
#if (defined PD_TEST_ENABLE_AUTO_POLICY) && (defined PD_CONFIG_ENABLE_AUTO_POLICY) && (PD_CONFIG_ENABLE_AUTO_POLICY)
#if (PD_TEST_ENABLE_AUTO_POLICY == 1)
    (void *) & s_autoPolicy1,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 2)
    (void *) & s_autoPolicy2,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 3)
    (void *) & s_autoPolicy3,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 4)
    (void *) & s_autoPolicy4,
#else
    NULL,
#endif
#else
    NULL,
#endif
    NULL,
};

#endif

#if (defined PD_COMPLIANCE_TEST_DRP_TRY_SNK) && (PD_COMPLIANCE_TEST_DRP_TRY_SNK)
static pd_power_port_config_t s_PortPowerConfig = {
    (uint32_t *)&s_PortSourceCaps[0],                   /* source caps */
    (uint32_t *)&s_PortSinkcaps[0],                     /* self sink caps */
    sizeof(s_PortSourceCaps) / sizeof(pd_source_pdo_t), /* source cap count */
    sizeof(s_PortSinkcaps) / sizeof(pd_sink_pdo_t),     /* sink cap count */
    kPowerConfig_DRPToggling,                           /* typec role */
    PD_DEMO_TYPEC_CURRENT,                              /* source: Rp current level */
    kTypecTry_Snk,                                      /* drp try function */
    kDataConfig_DRD,                                    /* data function */
    1,                                                  /* support vconn */
    0,                                                  /* reserved */
    NULL,                                               /* alt mode config */
#if (defined PD_TEST_ENABLE_AUTO_POLICY) && (defined PD_CONFIG_ENABLE_AUTO_POLICY) && (PD_CONFIG_ENABLE_AUTO_POLICY)
#if (PD_TEST_ENABLE_AUTO_POLICY == 1)
    (void *) & s_autoPolicy1,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 2)
    (void *) & s_autoPolicy2,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 3)
    (void *) & s_autoPolicy3,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 4)
    (void *) & s_autoPolicy4,
#else
    NULL,
#endif
#else
    NULL,
#endif
    NULL,
};
#endif

#if (defined PD_COMPLIANCE_TEST_DRP_TRY_SRC) && (PD_COMPLIANCE_TEST_DRP_TRY_SRC)
static pd_power_port_config_t s_PortPowerConfig = {
    (uint32_t *)&s_PortSourceCaps[0],                   /* source caps */
    (uint32_t *)&s_PortSinkcaps[0],                     /* self sink caps */
    sizeof(s_PortSourceCaps) / sizeof(pd_source_pdo_t), /* source cap count */
    sizeof(s_PortSinkcaps) / sizeof(pd_sink_pdo_t),     /* sink cap count */
    kPowerConfig_DRPToggling,                           /* typec role */
    PD_DEMO_TYPEC_CURRENT,                              /* source: Rp current level */
    kTypecTry_Src,                                      /* drp try function */
    kDataConfig_DRD,                                    /* data function */
    1,                                                  /* support vconn */
    0,                                                  /* reserved */
    NULL,                                               /* alt mode config */
#if (defined PD_TEST_ENABLE_AUTO_POLICY) && (defined PD_CONFIG_ENABLE_AUTO_POLICY) && (PD_CONFIG_ENABLE_AUTO_POLICY)
#if (PD_TEST_ENABLE_AUTO_POLICY == 1)
    (void *) & s_autoPolicy1,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 2)
    (void *) & s_autoPolicy2,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 3)
    (void *) & s_autoPolicy3,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 4)
    (void *) & s_autoPolicy4,
#else
    NULL,
#endif
#else
    NULL,
#endif
    NULL,
};
#endif

#if (defined PD_COMPLIANCE_TEST_CONSUMER_PROVIDER) && (PD_COMPLIANCE_TEST_CONSUMER_PROVIDER)
static pd_power_port_config_t s_PortPowerConfig = {
    (uint32_t *)&s_PortSourceCaps[0],                   /* source caps */
    (uint32_t *)&s_PortSinkcaps[0],                     /* self sink caps */
    sizeof(s_PortSourceCaps) / sizeof(pd_source_pdo_t), /* source cap count */
    sizeof(s_PortSinkcaps) / sizeof(pd_sink_pdo_t),     /* sink cap count */
    kPowerConfig_SinkDefault,                           /* typec role */
    PD_DEMO_TYPEC_CURRENT,                              /* source: Rp current level */
    kTypecTry_None,                                     /* drp try function */
    kDataConfig_DRD,                                    /* data function */
    1,                                                  /* support vconn */
    0,                                                  /* reserved */
    NULL,                                               /* alt mode config */
#if (defined PD_TEST_ENABLE_AUTO_POLICY) && (defined PD_CONFIG_ENABLE_AUTO_POLICY) && (PD_CONFIG_ENABLE_AUTO_POLICY)
#if (PD_TEST_ENABLE_AUTO_POLICY == 1)
    (void *) & s_autoPolicy1,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 2)
    (void *) & s_autoPolicy2,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 3)
    (void *) & s_autoPolicy3,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 4)
    (void *) & s_autoPolicy4,
#else
    NULL,
#endif
#else
    NULL,
#endif
    NULL,
};
#endif

#if (defined PD_COMPLIANCE_TEST_PROVIDER_CONSUMER) && (PD_COMPLIANCE_TEST_PROVIDER_CONSUMER)
static pd_power_port_config_t s_PortPowerConfig = {
    (uint32_t *)&s_PortSourceCaps[0],                   /* source caps */
    (uint32_t *)&s_PortSinkcaps[0],                     /* self sink caps */
    sizeof(s_PortSourceCaps) / sizeof(pd_source_pdo_t), /* source cap count */
    sizeof(s_PortSinkcaps) / sizeof(pd_sink_pdo_t),     /* sink cap count */
    kPowerConfig_SourceDefault,                         /* typec role */
    PD_DEMO_TYPEC_CURRENT,                              /* source: Rp current level */
    kTypecTry_None,                                     /* drp try function */
    kDataConfig_DRD,                                    /* data function */
    1,                                                  /* support vconn */
    0,                                                  /* reserved */
    NULL,                                               /* alt mode config */
#if (defined PD_TEST_ENABLE_AUTO_POLICY) && (defined PD_CONFIG_ENABLE_AUTO_POLICY) && (PD_CONFIG_ENABLE_AUTO_POLICY)
#if (PD_TEST_ENABLE_AUTO_POLICY == 1)
    (void *) & s_autoPolicy1,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 2)
    (void *) & s_autoPolicy2,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 3)
    (void *) & s_autoPolicy3,
#elif(PD_TEST_ENABLE_AUTO_POLICY == 4)
    (void *) & s_autoPolicy4,
#else
    NULL,
#endif
#else
    NULL,
#endif
    NULL,
};
#endif

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

void HW_GpioUSB3CrossControl(uint8_t port, uint8_t value)
{
    if (port != 1)
    {
        return;
    }
    USB_GpioOutputWritePin(PD_CROSS_GPIO, PD_CROSS_PORT, PD_CROSS_PIN, (value ? 1 : 0));
}

void HW_GpioInit(uint8_t port)
{
    if (port != 1)
    {
        return;
    }
    /* the external power control pin */
    USB_GpioOutputInit(PD_EXTRA_SRC_GPIO, PD_EXTRA_SRC_PORT, PD_EXTRA_SRC_PIN, 0);

    USB_GpioOutputInit(PD_CROSS_GPIO, PD_CROSS_PORT, PD_CROSS_PIN, 0);
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
            PD_PowerSrcTurnOffVbus(pdAppInstance, kVbusPower_Stable);
            pdAppInstance->selfHasEnterAlernateMode = 0;
            PRINTF("port %d disconnect\r\n", pdAppInstance->portNumber);
            status = kStatus_PD_Success;
            break;

        case PD_CONNECT_ROLE_CHANGE:
        case PD_CONNECTED:
        {
            uint8_t getInfo;

            pdAppInstance->selfHasEnterAlernateMode = 0;
            pdAppInstance->partnerSourceCapNumber = 0;
            pdAppInstance->partnerSinkCapNumber = 0;
            pdAppInstance->portShieldVersion = 0;
            pdAppInstance->powerRoleChangedOrAttached = 0;
#if (defined BOARD_PD_USB3_CROSS_SUPPORT) && (BOARD_PD_USB3_CROSS_SUPPORT)
            PD_Control(pdAppInstance->pdHandle, PD_CONTROL_GET_TYPEC_ORIENTATION, &getInfo);
            /* set CROSS based on the typec orientation */
            HW_GpioUSB3CrossControl(pdAppInstance->portNumber, (getInfo ? 1 : 0));
#endif
            PD_Control(pdAppInstance->pdHandle, PD_CONTROL_GET_POWER_ROLE, &getInfo);
            PRINTF((event == PD_CONNECTED) ? "port %d connected," : "port %d connect change,",
                   pdAppInstance->portNumber);
            PRINTF(" power role:%s,", (getInfo == kPD_PowerRoleSource) ? "Source" : "Sink");
            PD_Control(pdAppInstance->pdHandle, PD_CONTROL_GET_DATA_ROLE, &getInfo);
            PRINTF(" data role:%s,", (getInfo == kPD_DataRoleDFP) ? "DFP" : "UFP");
            PD_Control(pdAppInstance->pdHandle, PD_CONTROL_GET_VCONN_ROLE, &getInfo);
            PRINTF(" vconn source:%s\r\n", (getInfo == kPD_IsVconnSource) ? "yes" : "no");
            status = kStatus_PD_Success;
            PRINTF("Please input '0' to show test menu\r\n");
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

            /* the follow many settings are only for passing compliance, not the actual procudt logical */
            pdAppInstance->msgSop = kPD_MsgSOP;
            pdAppInstance->partnerSourceCapNumber = 0;
            pdAppInstance->partnerSinkCapNumber = 0;
            pdAppInstance->reqestResponse = kCommandResult_Accept;
            /* default SVDM command header */
            pdAppInstance->defaultSVDMCommandHeader.bitFields.objPos = 0;
            pdAppInstance->defaultSVDMCommandHeader.bitFields.vdmVersion = PD_CONFIG_STRUCTURED_VDM_VERSION;
            pdAppInstance->defaultSVDMCommandHeader.bitFields.vdmType = 1;
            pdAppInstance->defaultSVDMCommandHeader.bitFields.SVID = PD_STANDARD_ID;
            /* self ext cap */
            pdAppInstance->selfExtCap.vid = PD_VENDOR_VID;
            pdAppInstance->selfExtCap.pid = PD_CONFIG_PID;
            pdAppInstance->selfExtCap.xid = PD_CONFIG_XID;
            pdAppInstance->selfExtCap.fwVersion = PD_CONFIG_FW_VER;
            pdAppInstance->selfExtCap.hwVersion = PD_CONFIG_HW_VER;
            pdAppInstance->selfExtCap.batteries = 0;
            pdAppInstance->selfExtCap.sourcePDP = PD_SOURCE_POWER;
            /* self alert */
            pdAppInstance->selfAlert.alertValue = 0u;
            /* self battery */
            pdAppInstance->selfBatteryCap.batteryDesignCap = 10;
            pdAppInstance->selfBatteryCap.batteryLastFullChargeCap = 10;
            pdAppInstance->selfBatteryCap.batteryType = 1; /* invalid battery reference */
            pdAppInstance->selfBatteryCap.pid = PD_CONFIG_PID;
            pdAppInstance->selfBatteryCap.vid = PD_VENDOR_VID;
            pdAppInstance->selfBatteryStatus.batterInfo = 0;
            /* no battery */
            pdAppInstance->selfBatteryStatus.batterInfoBitFields.invalidBatteryRef = 1;
            pdAppInstance->selfBatteryStatus.batteryPC = 10;
            /* manufacturer string */
            pdAppInstance->selfManufacInfo.vid = PD_VENDOR_VID;
            pdAppInstance->selfManufacInfo.pid = PD_CONFIG_PID;
            pdAppInstance->selfManufacInfo.manufacturerString[0] = 'N';
            pdAppInstance->selfManufacInfo.manufacturerString[1] = 'X';
            pdAppInstance->selfManufacInfo.manufacturerString[2] = 'P';
            /* self status */
            pdAppInstance->selfStatus.eventFlags = 0;
            pdAppInstance->selfStatus.internalTemp = 0;
            pdAppInstance->selfStatus.presentBatteryInput = 0;
            pdAppInstance->selfStatus.presentInput = 0;
            pdAppInstance->selfStatus.temperatureStatus = 0;
            /* alternate mode (VDM) */
            pdAppInstance->selfVdmIdentity.idHeaderVDO.vdoValue = 0;
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.modalOperateSupport = 1;
#if ((defined PD_CONFIG_REVISION) && (PD_CONFIG_REVISION >= PD_SPEC_REVISION_30))
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.productTypeDFP = 0; /* Udefined */
#endif
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.productTypeUFPOrCablePlug = 0; /* PDUSB Undefined */
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.usbCommunicationCapableAsDevice = 0;
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.usbCommunicationCapableAsHost = 0;
            pdAppInstance->selfVdmIdentity.idHeaderVDO.bitFields.usbVendorID = PD_VENDOR_VID;
            pdAppInstance->selfVdmIdentity.pid = PD_CONFIG_PID;
            pdAppInstance->selfVdmIdentity.certStatVDO = PD_CONFIG_XID;
            pdAppInstance->selfVdmIdentity.bcdDevice = PD_CONFIG_BCD_DEVICE;
            pdAppInstance->selfVdmSVIDs = ((uint32_t)PD_VENDOR_VID << 16); /* only one SVID (display port) */
            pdAppInstance->selfVdmModes = PD_CONFIG_APP_MODE;              /* only one Mode */
            /* evaluate result */
            pdAppInstance->prSwapAccept = 1;
            pdAppInstance->drSwapAccept = 1;
            pdAppInstance->vconnSwapAccept = 1;
            /* other */
            pdAppInstance->selfHasEnterAlernateMode = 0;
            pdAppInstance->powerRoleChangedOrAttached = 0;
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

#if (defined BOARD_PD_SW_INPUT_SUPPORT) && (BOARD_PD_SW_INPUT_SUPPORT)
    for (index = 0; index < PD_DEMO_PORTS_COUNT; ++index)
    {
        if (g_PDAppInstanceArray[index]->pdHandle != NULL)
        {
            PD_Demo1msIsrProcessSW(g_PDAppInstanceArray[index]);
        }
    }
#endif
    g_SoftTimerCount++;
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
