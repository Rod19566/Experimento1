
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//
/**
 * main.c
 */
int main(void)
    {
    volatile uint32_t ui32Loop;      //for the delay with a loop
    volatile uint32_t i;          //for the blinking light loop.
    volatile uint8_t debounce = 0; //for the debounce

        //
        // Enable the GPIO port that is used for the on-board LED.
        //
        SysCtlClockSet(SYSCTL_SYSDIV_7|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
        //CLK FREQUENCY 33.33 MHz
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //ENABLES PORT

        //
        // Check if the peripheral access is enabled.
        //
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        {
        }

        //
        // Enable the GPIO pin for the LED (PG2).  Set the direction as output, and
        // enable the GPIO pin for digital function.
        //
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
        GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); //pin PUSH1

        //
        // Loop forever.
        //
        while(1)
        {
            //
            // Turn on the LED.
            //
            if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0){  //for the debounce
                        debounce++;
                    } //if button pressed

            if (debounce == 1){ //begins

                debounce = 0; //resets debounce

                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);  //turns on green led
                SysCtlDelay(10000000);       //delay

                for(i = 0; i < 3; i++)
                                {
                                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
                                    SysCtlDelay(5000000);  //delay function
                                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
                                    SysCtlDelay(5000000);

                                } //blinking green light

                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1); //turns on red led for yellow
                SysCtlDelay(15000000);       //delay
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);       //turns off green for red
                SysCtlDelay(15000000);       //delay
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);       //turns off

            }// if debounce

        }
    }



	//return 0;
//}
