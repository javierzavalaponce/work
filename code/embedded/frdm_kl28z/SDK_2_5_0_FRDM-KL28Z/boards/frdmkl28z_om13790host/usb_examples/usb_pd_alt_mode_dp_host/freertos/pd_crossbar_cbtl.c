/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "usb_pd_config.h"
#include "pd_board_config.h"
#include "usb_pd.h"
#include "string.h"
#include "usb_pd_alt_mode.h"
#include "usb_pd_alt_mode_dp.h"
#include "pd_crossbar_cbtl.h"
#include "usb_io.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void PD_CrossbarCBTLSetMux(pd_cbtl_crossbar_instance_t *cbtlCrossInstance,
                           uint8_t orient,
                           uint8_t mux,
                           uint32_t modeVDO);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/* 0 - intialize success; other values - fail */
uint8_t PD_CrossbarCBTLInit(pd_cbtl_crossbar_instance_t *cbtlCrossInstance, pd_handle pdHandle, void *config)
{
    /* initialize crossbar enable pin */
    cbtlCrossInstance->pdHandle = pdHandle;
    cbtlCrossInstance->config = (const pd_cbtl_crossbar_config_t *)config;

    if ((cbtlCrossInstance->config->orientControlGPIO != 0xFFu) &&
        (cbtlCrossInstance->config->orientControlPort != 0xFFu) &&
        (cbtlCrossInstance->config->orientControlPin != 0xFFu))
    {
        USB_GpioOutputInit(cbtlCrossInstance->config->orientControlGPIO, cbtlCrossInstance->config->orientControlPort,
                           cbtlCrossInstance->config->orientControlPin, 0);
    }

    if ((cbtlCrossInstance->config->xsdnControlGPIO != 0xFFu) &&
        (cbtlCrossInstance->config->xsdnControlPort != 0xFFu) && (cbtlCrossInstance->config->xsdnControlPin != 0xFFu))
    {
        USB_GpioOutputInit(cbtlCrossInstance->config->xsdnControlGPIO, cbtlCrossInstance->config->xsdnControlPort,
                           cbtlCrossInstance->config->xsdnControlPin, 0);
    }

    if ((cbtlCrossInstance->config->dp4laneControlGPIO != 0xFFu) &&
        (cbtlCrossInstance->config->dp4laneControlPort != 0xFFu) &&
        (cbtlCrossInstance->config->dp4laneControlPin != 0xFFu))
    {
        USB_GpioOutputInit(cbtlCrossInstance->config->dp4laneControlGPIO, cbtlCrossInstance->config->dp4laneControlPort,
                           cbtlCrossInstance->config->dp4laneControlPin, 0);
    }

    PD_CrossbarCBTLSetMux(cbtlCrossInstance, 0, kDPPeripheal_ControlSetMuxDisable, 0);
    return 0;
}

uint8_t PD_CrossbarCBTLDeinit(pd_cbtl_crossbar_instance_t *cbtlCrossInstance)
{
    return 0;
}

void PD_CrossbarCBTLSetMux(pd_cbtl_crossbar_instance_t *cbtlCrossInstance,
                           uint8_t orient,
                           uint8_t mux,
                           uint32_t modeVDO)
{
    switch (mux)
    {
        case kDPPeripheal_ControlSetMuxUSB3Only:
            USB_GpioOutputWritePin(cbtlCrossInstance->config->orientControlGPIO,
                                   cbtlCrossInstance->config->orientControlPort,
                                   cbtlCrossInstance->config->orientControlPin, (orient ? 1 : 0));
            USB_GpioOutputWritePin(cbtlCrossInstance->config->dp4laneControlGPIO,
                                   cbtlCrossInstance->config->dp4laneControlPort,
                                   cbtlCrossInstance->config->dp4laneControlPin, 0);
            USB_GpioOutputWritePin(cbtlCrossInstance->config->xsdnControlGPIO,
                                   cbtlCrossInstance->config->xsdnControlPort,
                                   cbtlCrossInstance->config->xsdnControlPin, 0);
            break;

        case kDPPeripheal_ControlSetMuxShutDown:
        case kDPPeripheal_ControlSetMuxDisable:
        case kDPPeripheal_ControlSetMuxSaftMode:
            USB_GpioOutputWritePin(cbtlCrossInstance->config->xsdnControlGPIO,
                                   cbtlCrossInstance->config->xsdnControlPort,
                                   cbtlCrossInstance->config->xsdnControlPin, 1);
            USB_GpioOutputWritePin(cbtlCrossInstance->config->dp4laneControlGPIO,
                                   cbtlCrossInstance->config->dp4laneControlPort,
                                   cbtlCrossInstance->config->dp4laneControlPin, 0);
            break;

        case kDPPeripheal_ControlSetMuxDP2LANEUSB3:
        case kDPPeripheal_ControlSetMuxDP2LANENOUSB:
            USB_GpioOutputWritePin(cbtlCrossInstance->config->orientControlGPIO,
                                   cbtlCrossInstance->config->orientControlPort,
                                   cbtlCrossInstance->config->orientControlPin, (orient ? 1 : 0));
            USB_GpioOutputWritePin(cbtlCrossInstance->config->dp4laneControlGPIO,
                                   cbtlCrossInstance->config->dp4laneControlPort,
                                   cbtlCrossInstance->config->dp4laneControlPin, 0);
            USB_GpioOutputWritePin(cbtlCrossInstance->config->xsdnControlGPIO,
                                   cbtlCrossInstance->config->xsdnControlPort,
                                   cbtlCrossInstance->config->xsdnControlPin, 0);
            break;

        case kDPPeripheal_ControlSetMuxDP4LANE:
            USB_GpioOutputWritePin(cbtlCrossInstance->config->orientControlGPIO,
                                   cbtlCrossInstance->config->orientControlPort,
                                   cbtlCrossInstance->config->orientControlPin, (orient ? 1 : 0));
            USB_GpioOutputWritePin(cbtlCrossInstance->config->dp4laneControlGPIO,
                                   cbtlCrossInstance->config->dp4laneControlPort,
                                   cbtlCrossInstance->config->dp4laneControlPin, 1);
            USB_GpioOutputWritePin(cbtlCrossInstance->config->xsdnControlGPIO,
                                   cbtlCrossInstance->config->xsdnControlPort,
                                   cbtlCrossInstance->config->xsdnControlPin, 0);
            break;

        default:
            break;
    }
}
