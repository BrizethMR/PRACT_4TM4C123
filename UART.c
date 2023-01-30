#include "lib/include.h"

//configuración UART4, Baud-rate 57600
//U4Tx->PC5 (se conecta al Rx del modulo)
//U4Rx->PC4


extern void Configurar_UART0(void)
{
    SYSCTL->RCGCUART  = (1<<4); //inicializar y habilitar el UART (RCGCUART) p. 902,344

    SYSCTL->RCGCGPIO |= (1<<2); //habilitar el reloj para el módulo GPIO (RCGCGPIO) p. 902,1351,340

    //habilitar reloj del puerto C
    GPIOC->AFSEL = (1<<5) | (1<<4); //habilitar funciones alternativas p. 902,1350,672

    GPIOC->PCTL = (GPIOC->PCTL&0xFF00FFFF) | 0x00110000;    //configurar GPIO port control (GPIOPCTL)

    //GPIO Port Control PC4-> U4Rx PC5-> U4Tx p. 688
    //(1<<16) | (1<<20);
    GPIOC->DEN = (1<<5) | (1<<4);//habilitar funciones digitales del pin (GPIODEN) p. 688 

    //PC5 PC4
    UART4->CTL = (0<<9) | (0<<8) | (0<<0); //deshabilitar el UART -> UART control (UARTCTL) p. 918

    // UART Integer Baud-Rate Divisor (UARTIBRD) p. 914 ***
    /*
    BRD = 20,000,000 / (16*57600) = 21.7
    UARTFBRD[DIVFRAC] = integer(.7 * 64 + 0.5) = 45.3 se redondea hacia arriba 
    */
    UART4->IBRD = 21;

    UART4->FBRD = 46; // UART Fractional Baud-Rate Divisor (UARTFBRD) p. 915

    UART4->LCRH = (0x3<<5)|(1<<4); //configurar UART Line Control (UARTLCRH) p. 916
    //se transmiten/reciben 8 bits, habilitar FIFO buffers

    UART4->CC =(0<<0);  //configurar reloj -> UART Clock Configuration (UARTCC) p. 939
    
    UART4->CTL = (1<<9) | (1<<8) | (1<<0); //habilitar el UART p. 918
}

extern void printChar(char c) //recibe a c
{
    while((UART4->FR & (1<<5)) != 0 ); 
    //1 -> el transmit FIFO is full 
    //0 -> el transmitter is not full
    UART4->DR = c;
}

extern void printString(char *string) //enviar una cadena
{
    while(*string)
    {
        printChar(*(string++));
    }
}



