#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

typedef struct disp {                         //Se crea la estructura para el display de 7 segmentos
    uint8_t port[7];
    uint8_t pines[7];
}disp;

typedef struct boton_in {                     //Estructura para ports y pines
    uint8_t port;
    uint8_t pines;
}boton_in;

struct disp u;
struct disp d;

struct boton_in señal_in;

volatile unsigned long milis=0;                //Se crea una variable para contar milesimas

volatile uint8_t status = 0;

bool num_to_7s[12][7]= {{1,1,1,1,1,1,0},
                        {0,1,1,0,0,0,0},
                        {1,1,0,1,1,0,1},
                        {1,1,1,1,0,0,1},
                        {0,1,1,0,0,1,1},        //Se crea la logica para el pin de 7 segmentos segun su hoja de datos
                        {1,0,1,1,0,1,1},
                        {1,0,1,1,1,1,1},
                        {1,1,1,0,0,0,0},
                        {1,1,1,1,1,1,1},
                        {1,1,1,1,0,1,1},
                        {1,0,0,1,1,1,1},
                        {0,0,0,0,1,0,1}};

bool lectura( uint8_t port,  uint8_t pines ){               //Lectura de pines
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

void escritura( uint8_t port,  uint8_t pines, bool st){              //Escritura de pines
    switch(port){
        case 1:{
            if(st){
                P1->OUT |= (1<<pines);
            }
            else{
                P1->OUT &= ~(1<<pines);
            }
            break;
        }
        case 2:{
            if(st){
                P2->OUT |= (1<<pines);
            }
            else{
                P2->OUT &= ~(1<<pines);
            }
            break;
        }
        case 3:{
            if(st){
                P3->OUT |= (1<<pines);
            }
            else{
                P3->OUT &= ~(1<<pines);
            }
            break;
        }
        case 4:{
            if(st){
                P4->OUT |= (1<<pines);
            }
            else{
                P4->OUT &= ~(1<<pines);
            }
            break;
        }
        case 5:{
            if(st){
                P5->OUT |= (1<<pines);
            }
            else{
                P5->OUT &= ~(1<<pines);
            }
            break;
        }
        case 6:{
            if(st){
                P6->OUT |= (1<<pines);
            }
            else{
                P6->OUT &= ~(1<<pines);
            }
            break;
        }
        case 7:{
            if(st){
                P7->OUT |= (1<<pines);
            }
            else{
                P7->OUT &= ~(1<<pines);
            }
            break;
        }
        case 8:{
            if(st){
                P8->OUT |= (1<<pines);
            }
            else{
                P8->OUT &= ~(1<<pines);
            }
            break;
        }
        case 9:{
            if(st){
                P9->OUT |= (1<<pines);
            }
            else{
                P9->OUT &= ~(1<<pines);
            }
            break;
        }
        case 10:{
            if(st){
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

void toggle( uint8_t port,  uint8_t pines){           //Toggleo de pines
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

void salida_pin( uint8_t port,  uint8_t pines){          //Logica de pines para su salida
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

void Init_ports(void){

    u.port[0] = 1;
    u.pines[0] = 1;
    u.port[1] = 1;
    u.pines[1] = 1;
    u.port[2] = 1;
    u.pines[2] = 1;
    u.port[3] = 1;
    u.pines[3] = 1;
    u.port[4] = 1;
    u.pines[4] = 1;
    u.port[5] = 1;
    u.pines[5] = 1;
    u.port[6] = 1;
    u.pines[6] = 1;

    d.port[0] = 1;
    d.pines[0] = 1;
    d.port[1] = 1;
    d.pines[1] = 1;
    d.port[2] = 1;
    d.pines[2] = 1;
    d.port[3] = 1;
    d.pines[3] = 1;
    d.port[4] = 1;
    d.pines[4] = 1;
    d.port[5] = 1;
    d.pines[5] = 1;
    d.port[6] = 1;
    d.pines[6] = 1;

    uint8_t i;
    for(i=0;i<7;i++){
        salida_pin(u.port[i], u.pines[i]);
        salida_pin(d.port[i], d.pines[i]);
    }

    señal_in.port = 4;
    señal_in.pines=1;

    GPIO_setAsInputPinWithPullDownResistor(señal_in.port, señal_in.pines);      //Se configura el pin P4.1 con pulldown

    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(señal_in.port, señal_in.pines);

}

void conversion(uint8_t aux,bool logic){
    uint8_t i;
    uint8_t dec = aux/10;
    uint8_t uni = aux-(dec*10);

    for(i=0;i<7;i++){
            if(logic){
                escritura(u.port[i], u.pines[i], num_to_7s[uni][i]);
                escritura(d.port[i], d.pines[i], num_to_7s[dec][i]);
            }
            else{
                escritura(u.port[i], u.pines[i], !num_to_7s[uni][i]);
                escritura(d.port[i], d.pines[i], !num_to_7s[dec][i]);
            }
    }
}

void error(bool logic){
    uint8_t i;

    for(i=0;i<7;i++){
        if(logic){
            escritura(u.port[i], u.pines[i], num_to_7s[12][i]);
            escritura(d.port[i], d.pines[i], num_to_7s[11][i]);
        }
        else{
            escritura(u.port[i], u.pines[i], !num_to_7s[12][i]);
            escritura(d.port[i], d.pines[i], !num_to_7s[11][i]);
        }
    }
}

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    Init_ports();

    Interrupt_enableMaster(); //habilitando todas las interrups

    while(1)
    {
        switch(status){
            case 0:{
                unsigned int i;
                for(i=0;i<(3500000/1000);i++);          //Cuenta el tiempo en que se esta en el caso 0 si cambia el status
                milis++;
                break;
            }
            case 1:{
                float T = (milis*0.001);
                float F = 1/T;

                if(F>=1 && F<100){
                    conversion((uint8_t)F, true);
                }
                else{
                    error(true);
                }

                milis=0;

                break;
            }
        }
        
    }
}

void PORT4_IRQHandler (void){
    if(lectura(señal_in.port, señal_in.pines)){                         //Si se detecta una señal se activa la interrupcion y se cambia de status
        GPIO_clearInterruptFlag(señal_in.port, señal_in.pines);
        if(status==0){
            status=1;
        }
        else{
            status=0;
        }
    }
}
