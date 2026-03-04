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

#define PD_DEMO_PORT1_ENABLE (1)
#define PD_DEMO_PORT2_ENABLE (0)
#define PD_DEMO_PORT3_ENABLE (0)
#define PD_DEMO_PORT4_ENABLE (0)
#define PD_DEMO_PORTS_COUNT (PD_DEMO_PORT1_ENABLE + PD_DEMO_PORT2_ENABLE + PD_DEMO_PORT3_ENABLE + PD_DEMO_PORT4_ENABLE)

/*******************************************************************************
 * API
 ******************************************************************************/

#endif
