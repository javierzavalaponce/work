#include "fsl_device_registers.h"
#include "fsl_gpio.h"
#include "fsl_uart.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "MK64F12.h"
#include <string.h>


#define DEMO_UART UART3
#define MONA_GPIO GPIOB
#define MONB_GPIO GPIOB
#define MONC_GPIO GPIOC
#define MOND_GPIO GPIOD
#define MON_PINA 0  //PD0  logic analizer 3
#define MON_PINB 2  //PD2  logic analizer 2
#define MON_PINC 3  //PD3  logic analizer 1
#define MON_PIND 1  //PD1  logic analizer 0

#define MON_PINE 3  //PC3  logic analizer 7
#define MON_PINF 2  //PC2  logic analizer 6
#define MON_PING 2  //PA2  logic analizer 5
#define MON_PINH 23 //PB23 logic analizer 4

#define MONB_GPIO GPIOB 

void delay(volatile uint32_t count)
{
    while(count--) __asm("nop");
}

void func(void){
    static unsigned short var = 0;
    var = var?0:1;
    if (var) {
        GPIO_PinWrite(MOND_GPIO, MON_PINA, 1);
        GPIO_PinWrite(MOND_GPIO, MON_PINC, 1);
    }
    else {
        GPIO_PinWrite(MOND_GPIO, MON_PINA, 0);
        GPIO_PinWrite(MOND_GPIO, MON_PINC, 0);

    }
}

void init_gpios(void){


    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortD);

    PORT_SetPinMux(PORTD, MON_PINA, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, MON_PINB, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, MON_PINC, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, MON_PIND, kPORT_MuxAsGpio);

    PORT_SetPinMux(PORTC, MON_PINE, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTC, MON_PINF, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTA, MON_PING, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTB, MON_PINH, kPORT_MuxAsGpio);


    //activo alto:
    gpio_pin_config_t led_config = {kGPIO_DigitalOutput,0,};
    GPIO_PinInit(MOND_GPIO, MON_PINA, &led_config);
    GPIO_PinInit(MOND_GPIO, MON_PINB, &led_config);
    GPIO_PinInit(MOND_GPIO, MON_PINC, &led_config);
    GPIO_PinInit(MOND_GPIO, MON_PIND, &led_config);

    GPIO_PinInit(MONC_GPIO, MON_PINE, &led_config);
    GPIO_PinInit(MONC_GPIO, MON_PINF, &led_config);
    GPIO_PinInit(MONA_GPIO, MON_PING, &led_config);
    GPIO_PinInit(MONB_GPIO, MON_PINH, &led_config);


    //pin OFF
    GPIO_PinWrite(MOND_GPIO, MON_PINA, 0);
    GPIO_PinWrite(MOND_GPIO, MON_PINB, 0);
    GPIO_PinWrite(MOND_GPIO, MON_PINC, 0);
    GPIO_PinWrite(MOND_GPIO, MON_PIND, 0);


    GPIO_PinWrite(MONC_GPIO, MON_PINE, 0);
    GPIO_PinWrite(MONC_GPIO, MON_PINF, 0);
    GPIO_PinWrite(MONA_GPIO, MON_PING, 0);
    GPIO_PinWrite(MONB_GPIO, MON_PINH, 0);

}

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

    const char *text = "UART3 C16/C17 OK\r\n";
    UART_Init(DEMO_UART, &config, coreClock);
    UART_WriteBlocking(DEMO_UART,
                      (uint8_t *)text,
                      strlen(text));
    for (volatile uint32_t i = 0; i < 8000000; i++);                      

    init_gpios();
    while (1)
    {
        delay(100000); // cada 37.9 ms
        func();
    }
}