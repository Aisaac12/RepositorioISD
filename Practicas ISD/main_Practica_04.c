/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

const int  pwm = 60;
const int valor_max = 3000000/pwm;

unsigned int pwm2[]={valor_max*(0.04),valor_max*(0.07),valor_max*(0.08),valor_max*(0.09),valor_max*(0.1)}; //Se guardan varias configuraciones para el pwm
unsigned int status1=0;
unsigned int status2=0;
unsigned int status3=0;         //Se agregan estados para tener movimientos de servomotores

void Init_botones(void){
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN2);
}

void Init_GPIO(void){
    P10 ->DIR|= BIT5;
    P10 ->OUT &= ~BIT5;
    P10 -> SEL0 |= BIT5;
    P2 ->DIR|= BIT4;           //Configuracion de pines de varios puertos con pwm para cada servomotor
    P5 ->DIR|= BIT6;

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);

    CS -> KEY = CS_KEY_VAL;    //Se habilita la escritura en el CS
    CS -> KEY = 0;             //Se deshabilita la escritura en el CS
}

void Init_TIMER_A0(void){
    TIMER_A0 -> CTL = TIMER_A_CTL_MC__UP | TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_CLR;           //Configuracion y habilitacion de timer A0 con los valores maximos y del pwm
    TIMER_A0 -> CCR[0] = valor_max;
    TIMER_A0 -> CCR[1] = pwm2[0];

    TIMER_A0 ->CCTL[0] = TIMER_A_CCTLN_OUTMOD_4;
    TIMER_A0 ->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;        //Configuracion del modo de operar para el timer
}

void Init_TIMER_A2(void){
    TIMER_A2 -> CTL = TIMER_A_CTL_MC__UP | TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_CLR;           //Configuracion y habilitacion de timer A2 con los valores maximos y del pwm
    TIMER_A2 -> CCR[0] = valor_max;
    TIMER_A2 -> CCR[1] = pwm2[0];

    TIMER_A2 ->CCTL[0] = TIMER_A_CCTLN_OUTMOD_4;
    TIMER_A2 ->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;       //Configuracion del modo de operar para el timer
}

void Init_TIMER_A3(void){
    TIMER_A3 -> CTL = TIMER_A_CTL_MC__UP | TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_CLR;           //Configuracion y habilitacion de timer A3 con los valores maximos y del pwm
    TIMER_A3 -> CCR[0] = valor_max;
    TIMER_A3 -> CCR[1] = pwm2[0];

    TIMER_A3 ->CCTL[0] = TIMER_A_CCTLN_OUTMOD_4;
    TIMER_A3 ->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
}


int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();
    Init_botones();
    Init_GPIO();
    Init_TIMER_A0();
    Init_TIMER_A2();                    //Se mandan llamar todas las funciones
    Init_TIMER_A3();
    while(1)
    {
        if(!(P1->IN & BIT1)){           //Si se presiona el boton P1.1 se mueve el servo 1
            if(status1==4){
                status1=0;
            }else{
                status1++;
            }
            while(!(P1->IN & BIT1));
        }
        if(!(P1->IN & BIT4)){           //Si se presiona el boton P1.4 se mueve el servo 2
            if(status2==4){
                status2=0;
            }else{
                status2++;
            }
            while(!(P1->IN & BIT4));
        }
        if(!(P3->IN & BIT2)){           //Si se presiona el boton P3.2 se mueve el servo 3
            if(status3==4){
                status3=0;
            }else{
                status3++;
            }
            while(!(P3->IN & BIT2));
        }
        TIMER_A0 -> CCR[1] = pwm2[status1];
        TIMER_A2 -> CCR[1] = pwm2[status2];
        TIMER_A3 -> CCR[1] = pwm2[status3];
    }
}
