#include "string.h"
#include <stdio.h>
#include "SIM800L.h"   //Se agrega la libreria para utilizar comandos AT del GSM Sim800L
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void var(void) {
    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4); //Se configura el botón y LED para utilización
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}


}void main(void) {

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    //Variables & Strings
    char AT[] = "AT\r\n";             //COmando de inicio de comunicación
    char hangup[] = "ATH\r\n";
    char answer[] = "ATA\r\n";
    char mess[] = "Entraron a tu casa!!";       //Mensaje a mandar
    int opt;
    var();
    delayms(4000);
    //Inicialización para el módulo
    UART_init();               //Inicializar puerto UART
    delayms(4000);             //Se espera 4 segundos
    sendUART(AT);              //Envio de la variable AT
    delayms(3000);             //Espera de 3 segundos
    printf("%s\n", array);      //Imprime el ECO
    increment = 0;             //Reiniciar contador
    clear_array();             //Se limpia la variable del ECO

    while(1) {
        if(!(P1IN & BIT4)) {                                    //Si se presiona el botón
            printf("Enviando mensaje: \n");                   //Se muestra en consola que se envia el mensaje
            sendText(mess);                                  //Se envia la variable mensaje como prueba
            delayms(1000);
            printf("%s\n", array);                                //Muestra el ECO y respuesta del módulo
            delayms(1000);
                if( increment >= 1 ){
                    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);  //Si se envio el mensaje prende el LED
                    delayms(5000);
                }
            increment = 0;                                        //Se reinicia el contador
            clear_array();                                        //Y tambien el arreglo
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);      //Se apaga el LED
        }
    }
}
