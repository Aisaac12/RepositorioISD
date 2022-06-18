#include "string.h"
#include <stdio.h>
#include "SIM800L.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*Se inicializa el puerto para el modulo*/
void UART_init() {
    UART->CTLW0 |= 1; //Modo reset
    UART->MCTLW = 0;
    UART->CTLW0 = 0x0081;
    UART->BRW = 312; //115200 = 260 //312 = 9600     Se configuran los baudios

    /*Declaracion de GPIOS*/
    UART_PORT->SEL0 |= 0x0C;
    UART_PORT->SEL1 &= ~0x0C;
    UART->CTLW0 &= ~1; // Sin reset

    //Interrupcion
    UART->IE |= 1; // Interrupt Handler
    ENABLE
    __enable_irq();

    increment = 0;
}

//RX Handler para recibir datos
void EUSCIA2_IRQHandler() {

    array[increment] = UART-> RXBUF;
    increment++;
}

//Se reinician variables
void clear_array() {

    int i;
    for(i = 0; 100 > i; i++) {
        array[i] = 0;
    }
    increment = 0;
}

//Envio de texto
void sendText(char message[]) {
    char send[50];
    char mess[100];
    char SUB[50];
    char Init_Text[] = "AT+CMGF=1\r\n";     //Comando para vonfigurar en modo SMS


    sprintf(send, "AT+CMGS=\"+524922918838\"\r\n"); //Comando para mandar mensaje al numero
    sprintf(mess, "%s\r\n", message);
    sprintf(SUB, "%c\r\n", 0x1A);//0x1A


    sendUART(Init_Text);
    delayms(100);
    sendUART(send);
    delayms(100);
    sendUART(mess);
    delayms(100);
    sendUART(SUB);
    delayms(100);
}

/*Manda por UART la informacion del mensaje*/
void sendUART(char message[]) {
    int i;

    for(i = 0; i < strlen(message); i++) {
        while(!(UART->IFG & 0x02));
        UART->TXBUF = message[i];
    }
}

//Creación de delay
void delayms(int n) {
    int i, j;
    for(j = 0; j < n; j++)
            for(i = 250; i > 0 ; i--);
}

