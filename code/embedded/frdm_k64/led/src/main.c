#include "fsl_device_registers.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"

#define LED_GPIO GPIOB
#define LED_PIN 22U


#define LED_BLUE_GPIO GPIOB
#define LED_BLUE_PORT PORTB
#define LED_BLUE_PIN  21U

//GPIO_PinWrite(LED_BLUE_GPIO, LED_BLUE_PIN, 0);
//GPIO_PinWrite(LED_BLUE_GPIO, LED_BLUE_PIN, 1);










void delay(volatile uint32_t count)
{
    while(count--) __asm("nop");
}


#define N (2)
void func(void){
    static unsigned int k = 0;
    static unsigned int t = 0;
    static unsigned int cont = 0;
    //cada sec:
    if(k++==10) {
        k=0; 
        t=0;
        cont++;
        if((cont%2) == 0) GPIO_PinWrite(LED_GPIO, LED_PIN, 0);
        if((cont%3) == 0) GPIO_PinWrite(LED_BLUE_GPIO, LED_BLUE_PIN, 0);

    } else {
        if(k==N){
            //ambos OFF
            GPIO_PinWrite(LED_BLUE_GPIO, LED_BLUE_PIN, 1);
            GPIO_PinWrite(LED_GPIO, LED_PIN, 1);
        }
    }

}

int main(void)
{
    CLOCK_EnableClock(kCLOCK_PortB);

    PORT_SetPinMux(PORTB, LED_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTB, LED_BLUE_PIN, kPORT_MuxAsGpio);

    gpio_pin_config_t led_config =
    {
        kGPIO_DigitalOutput,
        1,
    };


    gpio_pin_config_t blue_led_config =
    {
        kGPIO_DigitalOutput,
        1, // apagado (activo en bajo)
    };

    GPIO_PinInit(LED_GPIO, LED_PIN, &led_config);
    GPIO_PinInit(LED_BLUE_GPIO, LED_BLUE_PIN, &blue_led_config);

    //ambos OFF
    GPIO_PinWrite(LED_BLUE_GPIO, LED_BLUE_PIN, 1);
    GPIO_PinWrite(LED_GPIO, LED_PIN, 1);
   
    while (1)
    {
        //GPIO_PortToggle(LED_GPIO, 1u << LED_PIN);
        //GPIO_PortToggle(LED_BLUE_GPIO, 1u << LED_BLUE_PIN);
        delay(100000); // cada sec
        func();
    }
}

