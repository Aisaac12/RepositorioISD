#include "msp.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t contt=0;

void configPorts(void){
    P1-> DIR |= BIT0;
    P1 -> OUT &= ~BIT0;
    P2-> DIR |= BIT1;//inicializamos ambos LED
    P2 -> OUT &= ~BIT1;

}
uint8_t primo_scan(uint8_t c){//funcion numero  primo
    uint8_t primo=0;
    uint8_t div=2;
    while(div<c  && primo!=1)
    {
        if(c%div==0) primo=1;
        div++;
    }
    return primo; //si el valor de  primo es igual a cero es numero primo
}
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	configPorts();
	while(1){
	    uint32_t i;
	    for(i=0;i<125000;i++);//0.5 seg de tiempo     
	    P2 -> OUT &= ~(BIT1);
	    for(i=0;i<125000;i++)
	    P2->OUT |= (BIT1);
	    if(contt==1000){
	        contt=0;
	    }else{
	        contt++;
	    }
	    if(primo_scan(contt)==0){
	        P1->OUT |= (BIT0);
	    }else{
	        P1 -> OUT &= ~(BIT0);
	    }
	}
}
