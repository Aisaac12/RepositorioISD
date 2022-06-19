
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Definicion de variables
volatile uint16_t RxData=0;
volatile uint16_t TxData;
volatile uint16_t DatoPrevio;
volatile uint8_t j=0;
volatile uint8_t dataencripReady=0;
volatile uint8_t cont=0;

//Variables

const static uint8_t Dato_Resuelto[16]={0x00, 0x01, 0x02, 0x03,
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
const static uint8_t DatoAESdesencrip [16];
static uint8_t Dato [16];


int main(void)
{

     WDT_A -> CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Detenemos watch dog
    //Configuracion de GPIOS
     P10 ->DIR |= BIT5;
     P10 ->OUT &= ~BIT5;
     // UCB0SIMO
     P1 -> SEL0 |= BIT5 + BIT6 + BIT7;
     // Reinicio de estado de maquina de eusib0
     EUSCI_B0-> CTLW0 |= EUSCI_B_CTLW0_SWRST;
     EUSCI_B0-> CTLW0 = EUSCI_B_CTLW0_SWRST + // Estado de maquina en reset
         EUSCI_B_CTLW0_SYNC+ // Habilitamos modo sincrono
         EUSCI_B_CTLW0_CKPL+ // Seleccionamos polaridad reloj en alto
         EUSCI_B_CTLW0_MSB;

     // Inicializamos el estado de maquina
     EUSCI_B0 -> CTLW0 &= ~ EUSCI_B_CTLW0_SWRST;
     EUSCI_B0 -> IE |= EUSCI_B_IE_RXIE;

     SCB-> SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
      // Garantizamos que la rutina anterior tenga efecto inmediato
      __DSB();

    // Interrupcion global
     __enable_irq();
     NVIC -> ISER[0] = 1 << ((EUSCIB0_IRQn)&31);

     while(1){
         if(dataencripReady==1){

             /*Desencriptación de DATOASencript y almancenado en DATOASencript */
             AES256_setDecipherKey(AES256_BASE, CipherKey, AES256_KEYLENGTH_256BIT);
             /*Desencriptación de DATOASencript y almancenado en DATOASencript */
             AES256_decryptData(AES256_BASE, Dato, DatoAESdesencrip);
             if(cont==16){
                 P10 ->OUT |= BIT5;//El dato fue desencriptado correctamente
             }else{
                 P10 ->OUT &= ~BIT5;
             }
             cont=0;
             j=0;
             dataencripReady=0;

         }
     }

}
void EUSCIB0_IRQHandler(void){
    if (EUSCI_B0 -> IFG & EUSCI_B_IFG_RXIFG){
        // espera a recibir el dato
        while (!(EUSCI_B0 -> IFG & EUSCI_B_IFG_TXIFG));
        // Guardamos dato
        if(j<=15){
            Dato[j]=EUSCI_B0->RXBUF;
            if(Dato[j]==Dato_Resuelto[j]){
                cont++;
            }
            j++;
            if(j==15){
                dataencripReady = 1;
            }
        }
    }
}
