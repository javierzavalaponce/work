/*
 * Copyright 2017-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __PD_BOARD_CONFIG_H__
#define __PD_BOARD_CONFIG_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define BOARD_PD_I2C_IRQ LPI2C1_IRQn
#define BOARD_PD_I2C_INDEX (1)

#define BOARD_PD_SW_INPUT_SUPPORT (0)
#define BOARD_PD_EXTERNAL_POWER_SUPPORT (1)
#define BOARD_PD_USB3_CROSS_SUPPORT (1)
#define PD_PTN36502_SLAVE_ADDRESS (0x12)

#define PD_DEMO_EXPECTED_VOLTAGE (5 * 1000) /* 5V */
#define PD_DEMO_EXPECTED_CURRENT (3000)     /* 3A */
#define PD_DEMO_TYPEC_CURRENT (kCurrent_3A) /* 3A */

#define PD_COMPLIANCE_TEST_DRP (1)
#define PD_COMPLIANCE_TEST_DRP_TRY_SNK (0)
#define PD_COMPLIANCE_TEST_DRP_TRY_SRC (0)
#define PD_COMPLIANCE_TEST_CONSUMER_PROVIDER (0)
#define PD_COMPLIANCE_TEST_PROVIDER_CONSUMER (0)

#if (defined PD_CONFIG_COMPLIANCE_TEST_ENABLE) && (PD_CONFIG_COMPLIANCE_TEST_ENABLE)
#define PD_TEST_ENABLE_AUTO_POLICY (1)
#else
#if (PD_COMPLIANCE_TEST_DRP)
/* 0 - disable auto policy;
 * 1 - enable auto policy 1:
 * don't auto request, auto accept all request for pr swap, data swap and vconn swap;
 * 2 - enable auto policy 2:
 * auto request pr swap when works as sink, auto accept for swap to source/DFP/vconn source, auto reject for swap to
 * sink/UFP/not vconn source, auto request power when working as sink;
 * 3 - enable auto policy 3:
 * auto request data swap to DFP, auto accept for swap to sink/UFP/not vconn source, auto reject for swap to
 * source/DFP/vconn source;
 * 4 - enable auto policy 4:
 * auto request vconn swap to vconn source, auto reject all request for pr swap, data swap and vconn swap.
 */
#define PD_TEST_ENABLE_AUTO_POLICY (1)
#endif
#endif

#define PD_DEMO_PORT1_ENABLE (1)
#define PD_DEMO_PORT2_ENABLE (0)
#define PD_DEMO_PORT3_ENABLE (0)
#define PD_DEMO_PORT4_ENABLE (0)
#define PD_DEMO_PORTS_COUNT (PD_DEMO_PORT1_ENABLE + PD_DEMO_PORT2_ENABLE + PD_DEMO_PORT3_ENABLE + PD_DEMO_PORT4_ENABLE)

/*******************************************************************************
 * API
 ******************************************************************************/

#endif
