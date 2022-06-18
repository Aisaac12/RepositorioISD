/*
Controla el modulo SIM800L
*/

#ifndef SIM800L_H_
#define SIM800L_H_

char array[150];
int increment;

void UART_init();
void delayms(int i);

void sendUART(char message[]);
void sendText(char message[]);

void clear_array();


//Port 2 MICROS TX = P2.3 RX = P2.2
//Uncomment #define for use of Port 2
//#define UART EUSCI_A1
//#define ENABLE NVIC_SetPriority(EUSCIA1_IRQn,4);NVIC_EnableIRQ(EUSCIA1_IRQn);
//#define UART_PORT P2

//PORT 3 TX = P3.3 RX = P3.2
//Uncomment #define for use of Port 3
#define UART EUSCI_A2
#define ENABLE NVIC_SetPriority(EUSCIA2_IRQn,4);NVIC_EnableIRQ(EUSCIA2_IRQn);
#define UART_PORT P3


#endif /* SIM800L_H_ */
