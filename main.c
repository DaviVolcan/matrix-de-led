/* File:   main.c
 * Author: Davi Volcan
 * Data: 02/10/2016 (DD/MM/YYYY)
*/ 

 /* DATA = RA3
  *  CLOCK = RA4
  *"A", "B", "C" sao os bits que selecionam as linhas do display
  * A = RA2  <---- LSB 
  * B = RA1
  * C = RA0  <---- MSB
*/

#include <xc.h>
#include "fuses.h"
#include <stdint.h>
unsigned long long L0 = 0B00010001000010010001000100000111;
unsigned long long L1 = 0B00010001000010010001001010001001;
unsigned long long L2 = 0B00010001000010010001010001010001;
unsigned long long L3 = 0B00010001000010010001010001010001;
unsigned long long L4 = 0B00010001000010010001011111010001;
unsigned long long L5 = 0B00001010000010001010010001001001;
unsigned long long L6 = 0B01000100000010000100010001000111;

void escreve(unsigned long long d)                 //funcao que carrega os shift registers (LINHAS)
{
          for(unsigned long long a=0; a <=69 ;++a)
{
        PORTA = 0b00000111;                        // move para a linha inexistente na matriz(se isso nao for feito havera ruido na vizualizaçao)
        PORTAbits.RA3 = (d >> a );                 // informaçao a ser escrita
        PORTAbits.RA4 =1; PORTAbits.RA4 =0;        //da um pulso no pino clock

}
    return;
}
void varre(void)                    // laço responsavel por escrever todo o display (LINHAS E COLUNAS)
{
    while(1)                        // laço infinito apenas por motivos de vizualizaçao enquanto as funcoes são desenvolvidas
    {
        
        escreve(L0);                //carregas dados referentes a linha 0
        PORTA = 0b00000000;         //joga na primeira linha os dados anteriormente carregados
        __delay_us(100); 
        escreve(L1);                //carregas dados referentes a linha 1
        PORTA = 0b00000100;         //joga na segunda linha os dados anteriormente carregados
        __delay_us(100);
         escreve(L2);               //carregas dados referentes a linha 2
        PORTA = 0b00000010;         //joga na terceira linha os dados anteriormente carregados
        __delay_us(100);  
         escreve(L3);               //carregas dados referentes a linha 3
        PORTA = 0b00000110;         //joga na quarta linha os dados anteriormente carregados
        __delay_us(100);  
         escreve(L4);               //carregas dados referentes a linha 4
        PORTA = 0b00000001;         //joga na quinta linha os dados anteriormente carregados
        __delay_us(100);  
         escreve(L5);               //carregas dados referentes a linha 5
        PORTA = 0b00000101;         //joga na sexta linha os dados anteriormente carregados
        __delay_us(100);  
        escreve(L6);                //carregas dados referentes a linha 6
        PORTA = 0b00000011;         //joga na setima linha os dados anteriormente carregados
        __delay_us(100);  
    }
}

void main(void) 
{
   ADCON1 = 0B11001111;       //DESATIVA OS COMPARADORES E CANAIS ANALOGICOS REFERENTES A PORTA A
   TRISA = 0B00000000;        // DEFINE OS I/O COMO OUTPUT
   PORTA = 0B00000000;        // LIMPA A PORTA A
   varre();
   SLEEP();                   //coloca o mcu em sleep
   return;
}
