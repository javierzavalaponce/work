#include "fsl_uart.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "MK64F12.h"
#include <string.h>

#define DEMO_UART UART3
int main(void)
{
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_Uart3);

    PORT_SetPinMux(PORTC, 16U, kPORT_MuxAlt3); // RX
    PORT_SetPinMux(PORTC, 17U, kPORT_MuxAlt3); // TX

    uart_config_t config;
    UART_GetDefaultConfig(&config);

    config.baudRate_Bps = 115200;
    config.enableTx = true;
    config.enableRx = true;

    uint32_t coreClock = 20971520U; // FEI default
    //uint32_t busClock  = CLOCK_GetBusClkFreq();

    UART_Init(DEMO_UART, &config, coreClock);

    const char *text = "UART3 C16/C17 OK\r\n";

    while (1)
    {
        UART_WriteBlocking(DEMO_UART,
                           (uint8_t *)text,
                           strlen(text));

        for (volatile uint32_t i = 0; i < 8000000; i++);
    }
}