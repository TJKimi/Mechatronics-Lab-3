#include "driverlib.h"
#include "stdlib.h"
#include "initializations.h"


int main(void)
{
    //initialize variables
    WDT_A_holdTimer(); //stop the timer

    MAP_GPIO_setAsOutputPin     (GPIO_PORT_P1, GPIO_PIN0); //p1.1
    MAP_GPIO_setAsOutputPin     (GPIO_PORT_P2,LED0); //p2.0
    MAP_GPIO_setAsOutputPin     (GPIO_PORT_P2,LED1); //p2.1
    MAP_GPIO_setAsOutputPin     (GPIO_PORT_P2,LED2); //p2.2
    MAP_GPIO_setOutputLowOnPin  (GPIO_PORT_P2, LED0);//turn off p2.0
    MAP_GPIO_setOutputLowOnPin  (GPIO_PORT_P2, LED1);//turn off p2.1
    MAP_GPIO_setOutputLowOnPin  (GPIO_PORT_P2, LED2);//turn off p2.2
    MAP_GPIO_setOutputLowOnPin  (GPIO_PORT_P1, GPIO_PIN0);//turn off p1.0
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,GPIO_PIN1); //S1 pull up
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,GPIO_PIN4); //S2 pull down
    while(1)
    {//inside while loop
        buttonPress();
    }//end while loop

}

void buttonPress(void)
{

    unsigned int cycle_delay = 50000 ;
    unsigned int delay_LED_on = 2500 ;
    unsigned short usiButton1 = 0;
    unsigned short usiButton2 = 0;
    int i = 0;
    for(i=0; i<cycle_delay-delay_LED_on; i++)// Delay cycle while LEDs are off
            {
                usiButton1 = MAP_GPIO_getInputPinValue ( GPIO_PORT_P1, GPIO_PIN1 );// Read button p1.1
                usiButton2 = MAP_GPIO_getInputPinValue ( GPIO_PORT_P1, GPIO_PIN4 );// Read button p1.4

                    if ( usiButton1 == GPIO_INPUT_PIN_LOW )
                    {
                        if(cycle_delay == 50000)// toggle frequency
                            cycle_delay = 5000 ;//cycle_delay/2 ;
                        else
                            cycle_delay = 50000 ;//cycle_delay*2 ;

                        while(MAP_GPIO_getInputPinValue ( GPIO_PORT_P1, GPIO_PIN1 ) == GPIO_INPUT_PIN_LOW)//while p1.1 is pressed in, turn on p1.0
                        {
                            MAP_GPIO_setOutputHighOnPin  (GPIO_PORT_P1, GPIO_PIN0);
                        }

                        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
                        //break out the entire loop once the button is no longer pressed
                    }
                    if ( usiButton2 == GPIO_INPUT_PIN_LOW)
                                    {
                                        if(cycle_delay == 50000)// toggle frequency
                                            cycle_delay = 5000 ;//cycle_delay/2 ;
                                        else
                                            cycle_delay = 50000 ;//cycle_delay*2 ;

                                        int r = rand()%3;
                                        while(MAP_GPIO_getInputPinValue ( GPIO_PORT_P1, GPIO_PIN4 ) == GPIO_INPUT_PIN_LOW)//while p1.4 is pressed in, turn on p2.0
                                        {

                                            if (r == 0)
                                            {
                                                MAP_GPIO_setOutputHighOnPin  (GPIO_PORT_P2, GPIO_PIN0);
                                            }else if (r == 1)
                                            {
                                                MAP_GPIO_setOutputHighOnPin  (GPIO_PORT_P2, GPIO_PIN1);
                                            }else if (r == 2)
                                            {
                                                MAP_GPIO_setOutputHighOnPin  (GPIO_PORT_P2, GPIO_PIN2);
                                            }

                                        }

                                        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
                                        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
                                        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
                                         //break out the entire loop once the button is no longer pressed
                                    }
            }

}
