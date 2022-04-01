/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Application Defines  */
#define TIMER_PERIOD    0x2DC6

/*Configuracion del timer*/
const Timer_A_UpModeConfig upConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,              // Fuente de reloj SMCLK
        TIMER_A_CLOCKSOURCE_DIVIDER_48,          // SMCLK/1 = 3MHz Divisor del timer
        TIMER_PERIOD,                           // Periodo del timer (5000)
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Deshabilitar interrupcion del timer
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Habilitar interrupcion CCR0
        TIMER_A_DO_CLEAR                        // Inicializar valor
};

int i;                  //Se declara el contador
int mode = 1;           //Se declara el modo

/*Funcion para inicializar los LEDs*/
void LED_Init(void){
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0); //Configuramos el Pin 6.0 V1
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2); //Configuramos el Pin 3.2 A1
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1); //Configuramos el Pin 6.1 R1
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3); //Configuramos el Pin 3.3 V2
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0); //Configuramos el Pin 4.0 A2
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1); //Configuramos el Pin 4.1 R2
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2); //Configuramos el Pin 4.2 V3
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3); //Configuramos el Pin 4.3 A3
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4); //Configuramos el Pin 4.4 R3
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5); //Configuramos el Pin 1.5 V4
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5); //Configuramos el Pin 4.5 A4
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN6);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6); //Configuramos el Pin 4.6 R4
}

/*Funcion para inicializar los botones*/
void boton_init(){
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);  //Se inicializa el boton 1.1
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);  //Se inicializa el boton 1.4
}

/*Funcion para el modo de Precaucion*/
void Precaucion1(void){

       GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);

       GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1);
       GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);

       GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
       GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);

       GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
       GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);

       GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6); //Se inicializan en apagado los pines con los LEDs amarillos

    GPIO_toggleOutputOnPin(GPIO_PORT_P3, GPIO_PIN2);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0);             //Se comienza a prender y apagar el LED 3.2 cada 0.5 segundos

    GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN0);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0);             //Se comienza a prender y apagar el LED 4.0 cada 0.5 segundos

    GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN3);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0);             //Se comienza a prender y apagar el LED 4.3 cada 0.5 segundos

    GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN5);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0);             //Se comienza a prender y apagar el LED 4.5 cada 0.5 segundos
}

/*Funciones para todos los estados del crucero*/
void estado1(void){
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);    //Se prende el LED verde 6.0
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);     //Se apaga el LED amarillo 3.2
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1);     //Se apaga el LED rojo 6.1
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);     //Se apaga el LED verde 3.3
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);     //Se apaga el LED amarillo 4.0
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);    //Se prende el LED rojo 4.1
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);     //Se apaga el LED verde 4.2
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);     //Se apaga el LED amarillo 4.3
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);    //Se prende el LED rojo 4.4
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);     //Se apaga el LED verde 1.5
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);     //Se apaga el LED amarillo 4.5
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);    //Se prende el LED rojo 4.6
}

void estado1off(void){                                  //Este estado se usa para que parpadee el LED verde 1
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);     //Se apaga el LED verde
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);     //Se apaga el LED amarillo
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1);     //Se apaga el LED rojo
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);     //Se apaga el LED verde
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);     //Se apaga el LED amarillo
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);    //Se apaga el LED rojo
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);     //Se apaga el LED verde
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);     //Se apaga el LED amarillo
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);    //Se apaga el LED rojo
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);     //Se apaga el LED verde
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);     //Se apaga el LED amarillo
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);    //Se apaga el LED rojo
}
/*Estos estados se definiran de manera analoga a los primeros dos (estado1 y estado1off)*/
void estado2(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado2off(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado3(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}
void estado3off(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado4(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado4off(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado5(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado5off(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado6(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado6off(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado7(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado7off(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado8(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void estado8off(void){
   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
   GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

/*Se comienza a hacer la secuencia de crucero, usando retrasos por medio de for*/
void normal(void){
            estado1();              //Se ejecuta el estado1
            for(i=0;i<450000;i++);  //Se espera 2.5 segundos
            estado1off();           //Se ejecuta el parpadeo del LED verde durante 0.33 segundos
            for(i=0;i<62500;i++);
            estado1();              //Se ejecuta nuevamente el estado 1
            for(i=0;i<62500;i++);
            estado1off();           //Parpadea de nuevo
            for(i=0;i<62500;i++);
            estado1();              //Vuelve a ejecutarse el estado 1
            for(i=0;i<62500;i++);

            //Se hace de manera analoga a la primera secuencia pero ahora con menor tiempo (0.33 s)
            estado2();
            for(i=0;i<62500;i++);
            estado2off();
            for(i=0;i<62500;i++);
            estado2();
            for(i=0;i<62500;i++);
            estado2off();
            for(i=0;i<62500;i++);
            estado2();
            for(i=0;i<62500;i++);
            estado2off();
            for(i=0;i<62500;i++);


            estado3();
            for(i=0;i<450000;i++);
            estado3off();
            for(i=0;i<62500;i++);
            estado3();
            for(i=0;i<62500;i++);
            estado3off();
            for(i=0;i<62500;i++);
            estado3();
            for(i=0;i<62500;i++);

            estado4();
            for(i=0;i<62500;i++);
            estado4off();
            for(i=0;i<62500;i++);
            estado4();
            for(i=0;i<62500;i++);
            estado4off();
            for(i=0;i<62500;i++);
            estado4();
            for(i=0;i<62500;i++);
            estado4off();
            for(i=0;i<62500;i++);

            estado5();
            for(i=0;i<450000;i++);
            estado5off();
            for(i=0;i<62500;i++);
            estado5();
            for(i=0;i<62500;i++);
            estado5off();
            for(i=0;i<62500;i++);
            estado5();
            for(i=0;i<62500;i++);

            estado6();
            for(i=0;i<62500;i++);
            estado6off();
            for(i=0;i<62500;i++);
            estado6();
            for(i=0;i<62500;i++);
            estado6off();
            for(i=0;i<62500;i++);
            estado6();
            for(i=0;i<62500;i++);
            estado6off();
            for(i=0;i<62500;i++);

            estado7();
            for(i=0;i<450000;i++);
            estado7off();
            for(i=0;i<62500;i++);
            estado7();
            for(i=0;i<62500;i++);
            estado7off();
            for(i=0;i<62500;i++);
            estado7();
            for(i=0;i<62500;i++);

            estado8();
            for(i=0;i<62500;i++);
            estado8off();
            for(i=0;i<62500;i++);
            estado8();
            for(i=0;i<62500;i++);
            estado8off();
            for(i=0;i<62500;i++);
            estado8();
            for(i=0;i<62500;i++);
            estado8off();
            for(i=0;i<62500;i++);
}

/*Funcion para el cambio del modo*/
void cambio(void){ //Funcion para el cambio de modo
    if(!(P1IN & BIT1)){
        i=0;
        while(!(P1IN & BIT1) && i<250000){ //Mientras se presiona el boton se aumenta un contador
            i++;
        }
        if(!(P1IN & BIT1) && i>=250000){    //Si el contador llega a un determinado conteo (1.3 segundos) y se sigue presionando el boton
            i=0;                            //Se reinicializa el contador
            while((P1IN & BIT4));           //Esperamos a que el boton 2 se presione
            while(!(P1IN & BIT1) && i<250000 && !(P1IN & BIT4)){ //Mientras se presionan los botones se aumenta un contador
                i++;                        //En total son 4 segundos que se debe dejar presionado cada boton
            }
            if(i>=250000){                  //Si el contador llega a 1.3 segundos
                while(!(P1IN & BIT4));      //Mientras se sigue presionando el boton 2
                if((P1IN & BIT4) && !(P1IN & BIT1)){    //Cuando se deja de presionar el boto dos y el boton 1 sigue presionado
                    while(!(P1IN & BIT1));
                    if(mode == 1){          //Si el modo está en 1
                        mode = 0;           //Se cambia al modo 0
                        GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
                        Interrupt_enableSleepOnIsrExit();
                        Interrupt_enableInterrupt(INT_TA1_0);       //Se habilitan las interrupciones del timer para modo precaución
                    }
                    else{
                        mode = 1;           //Si no se cumple lo anterior, el modo queda en 1
                        GPIO_disableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
                        Interrupt_disableSleepOnIsrExit();
                        Interrupt_disableInterrupt(INT_TA1_0);  //Se deshabilitan las interrupciones del timer
                    }
                }
            }
        }
    }

}

/*Funcion para interrupcion del timer*/
void TA1_0_IRQHandler(void)
{
    Precaucion1();          //Interrupcion del timer para el modo de precaución
}

/*Funcion para la interrupcion*/
// Sirve para limpiar la banderas de inteerupicion cuando se presiona el boton 1 y se suelta el otro
void PORT1_IRQHandler (void){
    if(!(P1IN & BIT1)){                                     //Se cambiara de modo si el boton 1 sigue presionado
        GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);   //Se limpia la bandera
        cambio();                                      //Se ejecuta el cambio de modo
    }
    else if ((P1IN & BIT4)){                                //Si no se da el caso anterior y se deja de presionar el botón 2
        GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
        Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);   //Comienza el contador
    }
}

/*Se ejecuta la funcion principal*/
int main(void)
{
    /* Stop WDT  */
    MAP_WDT_A_holdTimer();

    /* Inicializamos los LEDs*/
    LED_Init();                             //Se ejecuta la funcion de inicializar los LEDs
    boton_init();                           //Se ejecuta la funcion de inicializar los botones
    int mode = 1; //normal=1 precaucion=0   /Se inicializa el modo en 1 (modo Normal)

    // configurando interrupciones
        GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
        //GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);

        GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
        //GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
        Interrupt_enableInterrupt(INT_PORT1);       //Se habilitan las interrupciones

            Interrupt_enableMaster();               //Se habilita la interrupcion principal o master
            Timer_A_configureUpMode(TIMER_A1_BASE, &upConfig);      //Se configura el timer

    if (mode == 1){
    while(1){
        normal();                       //Se ejecuta el modo normal en un ciclo indefinido, hasta que se haga la secuencia
    }
    }
}
