/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* Baudios 9600*/
const eUSCI_UART_ConfigV1 uartConfig1 =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        78,                                     // BRDIV = 78
        2,                                       // UCxBRF = 2
        0,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};
//![Simple UART Config]

/* Baudios 115200*/
const eUSCI_UART_ConfigV1 uartConfig2 =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        6,                                       // BRDIV = 6
        8,                                       // UCxBRF = 8
        0,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

int main(void)
{
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    /* Configurar pines P1.2 y P1.3 en modo UART */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
            GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configurar DCO a 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    /* Configurar modulo UART */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig1);
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig2);

    /* Habilitar modulo UART */
    MAP_UART_enableModule(EUSCI_A0_BASE);
    MAP_UART_enableModule(EUSCI_A2_BASE);

    /* Habilitar interrupciones */
    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    while(1)
    {
        MAP_PCM_gotoLPM0();
    }
}

/* Se transmite por A0 y se recibe por A2 */
void EUSCIA0_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);

    MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        MAP_UART_transmitData(EUSCI_A2_BASE, MAP_UART_receiveData(EUSCI_A2_BASE));
    }
    uint32_t status2 = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);

        MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
      {
         MAP_UART_transmitData(EUSCI_A2_BASE, MAP_UART_receiveData(EUSCI_A2_BASE));
      }
}
