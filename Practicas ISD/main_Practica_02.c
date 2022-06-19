
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
//Iniciamos los estados
static volatile uint8_t state=1; // 1  estado A, 2 estado B, 3 estado C y 4= estado D
void configPorts(void){

    P2 ->SEL0 &= ~0x07;
    P2 ->SEL1 &= ~0x07;//incializamos puertos RGB 
    P2 ->DIR |= 0x07;

    /* interrupción */
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1); //boton1
    // configurando interrupciones
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);

    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    Interrupt_enableInterrupt(INT_PORT1);

    Interrupt_enableMaster();
}

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();
    configPorts();

    //maquina de estados
    while(1)
    {
        switch (state){
            case 1:{ //estado A
                P2->OUT=1;
                break;
            }
            case 2:{ //estado B
                P2->OUT=2;
                break;
            }
            case 3:{ //estado C
                P2->OUT=3;
                break;
            }
            case 4:{ //estado D
                P2->OUT=4;
                break;
            }
        }
    }
}
void PORT1_IRQHandler (void){

    if (!(P1IN & BIT1)){
        if(state==4){
            state=1;
        }else{
            state++;
        }
        GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
        while(!(P1IN & BIT1));
    }

}
