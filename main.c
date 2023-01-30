#include "lib/include.h"

extern void integer_to_char(uint16_t number) //lo mismo que itoa
{
    char number_in_string[5];
    int i = 3;
    int j = 0; 
    int n_digit;  
    while (i >= 0){
        n_digit = (int)number / (int)(pow(10, i));
        number_in_string[j] = n_digit + '0';
        number = number - (n_digit * pow(10, i)); 
        i = i - 1; 
        j++;
    }
    number_in_string[4] = '\n';
    printString(number_in_string);
}

int main(void)
{
    uint16_t Result[6]; //variables
    uint16_t valor1; //es tipo char porque se envian por el UART
    uint16_t valor2;
    uint16_t valor3;
    uint16_t valor4;
    uint16_t valor5;
    uint16_t valor6;
    
    Configurar_PLL(_20MHZ); //configuracion de la velocidad de reloj 
    Configura_Reg_ADC(); //configuracion del modulo ADC
    Configurar_UART0(); //configuración del UART 

    //Configurar_GPIO();  //falta configuración GPIO
    
    while(1) 
    {
        ADC0_InSeq1(Result); //llamada a la conversion por procesador}
        ADC1_InSeq2(Result);
        ADC1_InSeq3(Result);
        
        valor1 = (uint16_t)(Result[0]);
        valor2 = (uint16_t)(Result[1]);
        valor3 = (uint16_t)(Result[2]);
        valor4 = (uint16_t)(Result[3]);
        valor5 = (uint16_t)(Result[4]);
        valor6 = (uint16_t)(Result[5]);

        integer_to_char(valor1); //funcion para convertir de valor numérico a char
        integer_to_char(valor2); 
        integer_to_char(valor3); 
        integer_to_char(valor4);
        integer_to_char(valor5);
        integer_to_char(valor6);

    }
}
