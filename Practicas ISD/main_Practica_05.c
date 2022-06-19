#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

volatile unsigned long milis = 0;
volatile unsigned long aux = 0;

volatile float T = 0;
volatile float F =0;
volatile uint8_t state = 0;

const unsigned int F_max = 1000;
const float res = 1/F_max;

const eUSCI_UART_ConfigV1 uartConfig =
{
       EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
       78,                                     // BRDIV = 78
       2,                                       // UCxBRF = 2
       0,                                       // UCxBRS = 0
       EUSCI_A_UART_NO_PARITY,                  // No Parity
       EUSCI_A_UART_LSB_FIRST,                  // LSB First
       EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
       EUSCI_A_UART_MODE,                       // UART mode
       EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
       EUSCI_A_UART_8_BIT_LEN                  // 8 bit data length
};

typedef struct buttons {
    uint8_t pines;
    uint8_t port;                           //Configuracion de botones
}buttons;

struct buttons señal_in;                   //Se llama la estructura como una señal de entrada

void casos_pines( uint8_t port,  uint8_t pines){        //Se configura cada caso de los pines
    switch(port){
        case 1:{
            P1->DIR |= (1<<pines);
            P1->OUT &= ~(1<<pines);
            break;
        }
        case 2:{
            P2->DIR |= (1<<pines);
            P2->OUT &= ~(1<<pines);
            break;
        }
        case 3:{
            P3->DIR |= (1<<pines);
            P3->OUT &= ~(1<<pines);
            break;
        }
        case 4:{
            P4->DIR |= (1<<pines);
            P4->OUT &= ~(1<<pines);
            break;
        }
        case 5:{
            P5->DIR |= (1<<pines);
            P5->OUT &= ~(1<<pines);
            break;
        }
        case 6:{
            P6->DIR |= (1<<pines);
            P6->OUT &= ~(1<<pines);
            break;
        }
        case 7:{
            P7->DIR |= (1<<pines);
            P7->OUT &= ~(1<<pines);
            break;
        }
        case 8:{
            P8->DIR |= (1<<pines);
            P8->OUT &= ~(1<<pines);
            break;
        }
        case 9:{
            P9->DIR |= (1<<pines);
            P9->OUT &= ~(1<<pines);
            break;
        }
        case 10:{
            P10->DIR |= (1<<pines);
            P10->OUT &= ~(1<<pines);
            break;
        }
        default:{
            break;
        }

    }
}

void escritura( uint8_t port,  uint8_t pines, bool s ){         //Se escribe una señal digital para cada pin
    switch(port){
        case 1:{
            if(s){
                P1->OUT |= (1<<pines);
            }
            else{
                P1->OUT &= ~(1<<pines);
            }
            break;
        }
        case 2:{
            if(s){
                P2->OUT |= (1<<pines);
            }
            else{
                P2->OUT &= ~(1<<pines);
            }
            break;
        }
        case 3:{
            if(s){
                P3->OUT |= (1<<pines);
            }
            else{
                P3->OUT &= ~(1<<pines);
            }
            break;
        }
        case 4:{
            if(s){
                P4->OUT |= (1<<pines);
            }
            else{
                P4->OUT &= ~(1<<pines);
            }
            break;
        }
        case 5:{
            if(s){
                P5->OUT |= (1<<pines);
            }
            else{
                P5->OUT &= ~(1<<pines);
            }
            break;
        }
        case 6:{
            if(s){
                P6->OUT |= (1<<pines);
            }
            else{
                P6->OUT &= ~(1<<pines);
            }
            break;
        }
        case 7:{
            if(s){
                P7->OUT |= (1<<pines);
            }
            else{
                P7->OUT &= ~(1<<pines);
            }
            break;
        }
        case 8:{
            if(s){
                P8->OUT |= (1<<pines);
            }
            else{
                P8->OUT &= ~(1<<pines);
            }
            break;
        }
        case 9:{
            if(s){
                P9->OUT |= (1<<pines);
            }
            else{
                P9->OUT &= ~(1<<pines);
            }
            break;
        }
        case 10:{
            if(s){
                P10->OUT |= (1<<pines);
            }
            else{
                P10->OUT &= ~(1<<pines);
            }
            break;
        }
        default:{
            break;
        }

    }
}

void toggleo( uint8_t port,  uint8_t pines){                    //Se hace un toggle con los pines
    switch(port){
        case 1:{
            P1->OUT ^= (1<<pines);
            break;
        }
        case 2:{
            P2->OUT ^= (1<<pines);
            break;
        }
        case 3:{
            P3->OUT ^= (1<<pines);
            break;
        }
        case 4:{
            P4->OUT ^= (1<<pines);
            break;
        }
        case 5:{
            P5->OUT ^= (1<<pines);
            break;
        }
        case 6:{
            P6->OUT ^= (1<<pines);
            break;
        }
        case 7:{
            P7->OUT ^= (1<<pines);
            break;
        }
        case 8:{
            P8->OUT ^= (1<<pines);
            break;
        }
        case 9:{
            P9->OUT ^= (1<<pines);
            break;
        }
        case 10:{
            P10->OUT ^= (1<<pines);
            break;
        }
        default:{
            break;
        }

    }
}

bool lectura( uint8_t port,  uint8_t pines ){           //Se lee lo que da cada pin
    bool res;
    switch(port){
        case 1:{
            if(P1IN & (1<<pines)){
                res = true;
            }
            else{
                res = false;
            }
            break;
        }
        case 2:{
            if(P2IN & (1<<pines)){
                res = true;
            }
            else{
                res = false;
            }
            break;
        }
        case 3:{
            if(P3IN & (1<<pines)){
                res = true;
            }
            else{
                res = false;
            }
            break;
        }
        case 4:{
            if(P4IN & (1<<pines)){
                res = true;
            }
            else{
                res = false;
            }
            break;
        }
        case 5:{
            if(P5IN & (1<<pines)){
                res = true;
            }
            else{
                res = false;
            }
            break;
        }
        case 6:{
            if(P6IN & (1<<pines)){
                res = true;
            }
            else{
                res = false;
            }
            break;
        }
        case 7:{
            if(P7IN & (1<<pines)){
                res = true;
            }
            else{
                res = false;
            }
            break;
        }
        case 8:{
            if(P8IN & (1<<pines)){
                res = true;
            }
            else{
                res = false;
            }
            break;
        }
        case 9:{
            if(P9IN & (1<<pines)){
                res = true;
            }
            else{
                res = false;
            }
            break;
        }
        case 10:{
            if(P10IN & (1<<pines)){
                res = true;
            }
            else{
                res = false;
            }
            break;
        }
        default:{
            res = false;
            break;
        }

    }
    return res;
}

void Init_GPIO(void){                                 //Se inicializan los GPIOs
    señal_in.port = 4;
    señal_in.pines=1;

    GPIO_setAsInputPinWithPullDownResistor(señal_in.port, señal_in.pines);

    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1); //Se habilita la interrupcion para cuando se presione el boton P1.1
    GPIO_enableInterrupt(señal_in.port, señal_in.pines);
}

void Init_UART_A0(void){                              //Se habilita el UART A0
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION );  //Habilitar el pin P1.2 y P1.3 en modo UART

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);  //Reloj de 12MHz

    UART_initModule(EUSCI_A0_BASE, &uartConfig);      //Configurar UART a 9600 baudios
    UART_enableModule(EUSCI_A0_BASE);

    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIA0);           //Se habilita la interrupcion del UART
}

void Init_TIMER_A0(void){
    TIMER_A0 -> CCR[0] = 12000000/F_max;              //Se obtiene la frecuencia para el CCR0

    TIMER_A0 ->CCTL[0] = TIMER_A_CCTLN_OUTMOD_0 + TIMER_A_CCTLN_CCIE;
    TIMER_A0 -> CTL = TIMER_A_CTL_MC__UP | TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_CLR | TIMER_A_CTL_IE;

    Interrupt_enableInterrupt(INT_TA0_0);            //Se habilita la interrupcion con el timer
}

unsigned long miles(void){
    return milis;
}

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    Init_GPIO();
    Init_UART_A0();
    Init_TIMER_A0();

    Interrupt_enableMaster();

    while(1)
    {
        switch(state){
            case 2:{
                char msj[50];
                uint8_t i;
                sprintf(msj, "El periodo es: %0.5f, La frecuencia es = %0.5f\n", T, F); //Muestra un mensaje en la consola con la frecuencia y el periodo
                for(i=0;i<strlen(msj); i++){
                    UART_transmitData(EUSCI_A0_BASE, msj[i]);                           //Transmite los datos por UART
                }
                state = 0;

                break;
            }
            default:{
                break;
            }
        }
        
    }
}

void PORT4_IRQHandler (void){
    if(lectura(señal_in.port, señal_in.pines)){
        GPIO_clearInterruptFlag(señal_in.port, señal_in.pines);         //Si se presiona algun boton se entra a la interrupcion
        if(state == 0){
            aux = miles();
            state = 1;
        }
        else if(state == 1){
            T = (miles() - aux) * res;
            F = 1/T;
            state = 2;
        }
    }

}

void TA0_0_IRQHandler(void){        //Se entra a la interrupcion cada cierto tiempo segun la formula obtenida
    TIMER_A0->CCTL[0] &= ~0x0001;
    milis++;

}
