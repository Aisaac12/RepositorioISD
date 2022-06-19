
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Definicion de variables
volatile uint16_t RxData;

//Configuración para habilitar hasta 4 esclavos
void encenderSalidas(void){
    //Se encienden ya que una señal en bajo es la que indicará cuál esclavo se seleccionó
    P5 -> OUT |= BIT6;
    P6 -> OUT |= BIT6;
    P6 -> OUT |= BIT7;
    P2 -> OUT |= BIT3;
}
void confEsclavos(void){
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN6);//Para el esclavo 1
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN6);//Para el esclavo 2
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN7);//Para el esclavo 3
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN3);//Para el esclavo 4
    //Botones para selecionar al esclavo que se le transmitiran los datos
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN6);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7);
    encenderSalidas();
}

const static uint8_t Dato[16]={0x00, 0x01, 0x02, 0x03,
                         0x04, 0x05, 0x06,
                         0x07, 0x08, 0x09,
                         0x0A, 0x0B, 0x0C,
                         0x0D, 0x0E, 0x0F};
const static uint8_t CipherKey[32]={0x00, 0x01, 0x02, 0x03,
                              0x04, 0x05, 0x06, 0x07,
                              0x08, 0x09, 0x0A, 0x0B,
                              0x0C, 0x0D, 0x0E, 0x0F,
                              0x00, 0x01, 0x02, 0x03,
                              0x04, 0x05, 0x06, 0x07,
                              0x08, 0x09, 0x0A, 0x0B,
                              0x0C, 0x0D, 0x0E, 0x0F
                             };
const static uint8_t DatoAESencrip [16];


int main(void)
{
    /* Stop Watchdog  */
    volatile uint32_t i;

     WDT_A -> CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Detenemos watch dog

     // Configuración de senales de
     // UCB0SIMO
     P1 -> SEL0 |= BIT5 + BIT6 + BIT7;
     // Reinicio de estado de maquina de eusib0
     EUSCI_B0-> CTLW0 |= EUSCI_B_CTLW0_SWRST;
     EUSCI_B0-> CTLW0 = EUSCI_B_CTLW0_SWRST + // Estado de maquina en reset
             EUSCI_B_CTLW0_MST+ // Seleccion SPI modo maestro
             EUSCI_B_CTLW0_SYNC+ // Habilitamos modo sincrono
             EUSCI_B_CTLW0_CKPL+ // Seleccionamos polaridad reloj en alto
             EUSCI_B_CTLW0_MSB+  // Primero se envia el bit mas significativo
             EUSCI_B_CTLW0_SSEL__ACLK; // Seleccion de fuente de reloj
     EUSCI_B0 -> BRW = 1;
     // Inicializamos el estado de maquina
     EUSCI_B0 -> CTLW0 &= ~ EUSCI_B_CTLW0_SWRST;
    // Interrupcion global
     __enable_irq();
     NVIC -> ISER[0] = 1 << ((EUSCIB0_IRQn)&31);
     // Desíerta al salir de la rutina de la interrupcion
     SCB-> SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
     // Garantizamos que la rutina anterior tenga efecto inmediato
     __DSB();

     /*Cargamos la llave al módulo AES con longitud 256*/
     AES256_setCipherKey(AES256_BASE, CipherKey, AES256_KEYLENGTH_256BIT);
     /*Encriptacion de Dato y almacenado en DATOAESencript*/
     AES256_encryptData(AES256_BASE, Dato, DatoAESencrip);

     //confEsclavos(); //Por si queremos usar la configuración para 4 esclavos

    while(1)
    {
        /* Configuración para seleccionar los esclavos
        if(!(P1IN & BIT1)){
            P5 -> OUT &= ~BIT6;
            EUSCI_B0-> IFG |= EUSCI_B_IFG_TXIFG; //Habilitamos la interrupción para envio de datos
            EUSCI_B0-> IE |= EUSCI_B_IE_TXIE;
            while(!(P1IN & BIT1));
        }
        if(!(P1IN & BIT4)){
            P6 -> OUT &= ~BIT6;
            EUSCI_B0-> IFG |= EUSCI_B_IFG_TXIFG; //Habilitamos la interrupción para envio de datos
            EUSCI_B0-> IE |= EUSCI_B_IE_TXIE;
            while(!(P1IN & BIT4));
        }
        if(!(P2IN & BIT6)){
            P6 -> OUT &= ~BIT7;
            EUSCI_B0-> IFG |= EUSCI_B_IFG_TXIFG; //Habilitamos la interrupción para envio de datos
            EUSCI_B0-> IE |= EUSCI_B_IE_TXIE;
            while(!(P2IN & BIT6));
        }
        if(!(P2IN & BIT7)){
            P2 -> OUT &= ~BIT3;
            EUSCI_B0-> IFG |= EUSCI_B_IFG_TXIFG; //Habilitamos la interrupción para envio de datos
            EUSCI_B0-> IE |= EUSCI_B_IE_TXIE;
            while(!(P2IN & BIT7));
        }
        */
        //Si solo transmitiremos a un esclavo lo dejamos así, en caso contrario lo comentamos
        EUSCI_B0-> IFG |= EUSCI_B_IFG_TXIFG;
        EUSCI_B0-> IE |= EUSCI_B_IE_TXIE;

    }
}
    void EUSCIB0_IRQHandler(void){
        if (EUSCI_B0 -> IFG & EUSCI_B_IFG_TXIFG){
            uint8_t j=0;
            for (j=0;j<16;j++){
                // CArgamos bufer de transmision
                EUSCI_B0 -> TXBUF =DatoAESencrip[j];
            }
            // Deshabilitamos interrupciones por tx
            EUSCI_B0 -> IE &= ~EUSCI_B_IE_TXIE;
            //encenderSalidas();//Regresan a su estado inicial una vez que se transmitieron los datos
            // espera a recibir el dato
            while (!(EUSCI_B0 -> IFG & EUSCI_B_IFG_RXIFG));
            // Guardamos dato
            RxData = EUSCI_B0->RXBUF;
            EUSCI_B0 -> IFG &= ~EUSCI_B_IFG_RXIFG;
        }
    }

