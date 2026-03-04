/*
 * Copyright 2017 NXP
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

#define PD_DEMO_EXPECTED_VOLTAGE (5 * 1000) /* 5V */
#define PD_DEMO_EXPECTED_CURRENT (3000)     /* 3A */
#define PD_DEMO_TYPEC_CURRENT (kCurrent_3A) /* 3A */

#define PD_COMPLIANCE_TEST_DRP (1)
#define PD_COMPLIANCE_TEST_DRP_TRY_SNK (0)
#define PD_COMPLIANCE_TEST_DRP_TRY_SRC (0)
#define PD_COMPLIANCE_TEST_CONSUMER_PROVIDER (0)
#define PD_COMPLIANCE_TEST_PROVIDER_CONSUMER (0)

#define PD_DEMO_PORT1_ENABLE (1)
#define PD_DEMO_PORT2_ENABLE (0)
#define PD_DEMO_PORT3_ENABLE (0)
#define PD_DEMO_PORT4_ENABLE (0)
#define PD_DEMO_PORTS_COUNT (PD_DEMO_PORT1_ENABLE + PD_DEMO_PORT2_ENABLE + PD_DEMO_PORT3_ENABLE + PD_DEMO_PORT4_ENABLE)

/*******************************************************************************
 * API
 ******************************************************************************/

#endif
