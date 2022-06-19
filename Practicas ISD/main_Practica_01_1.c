#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

int conttt=0; //contador que permite cambiar el color del LED
int i;//inicializamos

int mode = 1; // entra en modo automatico   

void in_LED(void){
    P2 ->SEL0 &= ~0x07;
    P2 ->SEL1 &= ~0x07;
    P2 ->DIR |= 0x07;
    P2 ->OUT &= ~(0x07);
}

void in_ boton(){
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4); // configramos el boton1
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1); //configuramos el boton2
}

void Manual(void){
    if(mode == 0){
        contt=contt+1;
        P2->OUT=contt;
        if(contt>=8) contt=0;
        while(!(P1IN & BIT4)); // configuramos el modo manual para antirebotes
    }
}

void Automatico(void){
        for (i=0;i<281250;i++);//espera 1.5 s
        contt=contt+1;
        P2->OUT=contt;
        if(contt>=8) contt=0;
}

void change_mode(void){ //configuramos el modo 
    if(!(P1IN & BIT4)){
        i=0;
        while(!(P1IN & BIT4) && i<375000){ //lo activa el boton1
            i++;
        }
        if(!(P1IN & BIT4) && i>=375000){
            i=0;
            while((P1IN & BIT1)); // esperamos a que el boton 2 sea presionado
            while(!(P1IN & BIT4) && i<375000 && !(P1IN & BIT1)){
                i++;
            }
            if(i>=375000){
                while(!(P1IN & BIT1));
                if((P1IN & BIT1) && !(P1IN & BIT4)){
                    while(!(P1IN & BIT4));
                    if(mode == 1){
                        mode = 0;
                        GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
                    }
                    else{
                        mode = 1;
                        GPIO_disableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
                    }
                }
            }
        }
    }

}

void PORT1_IRQHandler (void){
    if(!(P1IN & BIT4)){
        GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
        change_mode();
    }
    else if (!(P1IN & BIT1)){
        GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
        Manual();
    }
}

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    // puertos
    in_LED();
    in_ boton();
    mode = 1;

    //  interrupciones
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    //GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);

    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
    //GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);


    Interrupt_enableInterrupt(INT_PORT1);

    Interrupt_enableMaster();


    while(1)
    {
        if(mode == 1){
            Automatico();
        }
    }
}
