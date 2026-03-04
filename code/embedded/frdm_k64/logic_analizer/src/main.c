#include "fsl_device_registers.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"

#define MONITOR_GPIO GPIOD 
#define MONITOR_PINA 0
#define MONITOR_PINB 2
#define MONITOR_PINC 3
#define MONITOR_PIND 1

void delay(volatile uint32_t count)
{
    while(count--) __asm("nop");
}

void func(void){
    static unsigned short var = 0;
    var = var?0:1;
    if (var) {
        GPIO_PinWrite(MONITOR_GPIO, MONITOR_PIND, 1);
        GPIO_PinWrite(MONITOR_GPIO, MONITOR_PINB, 1);
        GPIO_PinWrite(MONITOR_GPIO, MONITOR_PINA, 0);
        GPIO_PinWrite(MONITOR_GPIO, MONITOR_PINC, 0);

    }
    else {
        GPIO_PinWrite(MONITOR_GPIO, MONITOR_PIND, 0);
        GPIO_PinWrite(MONITOR_GPIO, MONITOR_PINB, 0);
        GPIO_PinWrite(MONITOR_GPIO, MONITOR_PINA, 1);
        GPIO_PinWrite(MONITOR_GPIO, MONITOR_PINC, 1);
    }
}

int main(void)
{
    CLOCK_EnableClock(kCLOCK_PortD);

    PORT_SetPinMux(PORTD, MONITOR_PINA, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, MONITOR_PINB, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, MONITOR_PINC, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, MONITOR_PIND, kPORT_MuxAsGpio);
    //activo alto:
    gpio_pin_config_t led_config = {kGPIO_DigitalOutput,0,};
    GPIO_PinInit(MONITOR_GPIO, MONITOR_PINA, &led_config);
    GPIO_PinInit(MONITOR_GPIO, MONITOR_PINB, &led_config);
    GPIO_PinInit(MONITOR_GPIO, MONITOR_PINC, &led_config);
    GPIO_PinInit(MONITOR_GPIO, MONITOR_PIND, &led_config);

    //pin OFF
    GPIO_PinWrite(MONITOR_GPIO, MONITOR_PINA, 0);
    GPIO_PinWrite(MONITOR_GPIO, MONITOR_PINB, 0);
    GPIO_PinWrite(MONITOR_GPIO, MONITOR_PINC, 0);
    GPIO_PinWrite(MONITOR_GPIO, MONITOR_PIND, 0);
   
    while (1)
    {
        delay(100000); // cada 37.9 ms
        func();
    }
}

