/*
 * led_matrix_bluetooth.c
 *
 * Created: 26/05/2020 18:35:00
 * Author : bee
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "USART_M328P.h"
uint8_t buffer;
volatile uint8_t StrRX_flag = 0;


ISR(USART_RX_vect){
	buffer = UDR0;
	StrRX_flag =1;
}

int main(void)
{
	DDRB = 0b11111111; // set port b0,1,2,3,4,5 as output for led column
    DDRD = 0b11000000; // set port d6,7 as output for led column, set port d0,1 as input for Tx,Rx
	DDRC = 0b00111111; // set port c0,1,2,3,4 output for led row
	PORTB = 0b00000000;
	PORTC = 0b11111111;
	USART0Init();
	sei();
	USART_putstring("A");
	USART_send_char(10);
	uint8_t  portC[5] = {0b11111110,0b11111101,0b11111011,0b11110111,0b11101111}; // port c 01234low
	uint8_t  portB[5] = {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000};
	uint8_t  portD[5] = {0b00000000,0b00000000};
	uint8_t j;
	
	while (1)
	{
		if (StrRX_flag == 1){
			if (buffer == 48){
				//0 on
				portB[0] += 0b00000001;
			
			}
			if (buffer == 122){
				//z off
				portB[0] -= 0b00000001;
				
			}
			
			if (buffer == 121){
				//y on and off
				PORTB ^= (1<<PORTB0);
				
			}
			
			else if (buffer == 49){
				//1
				portB[1] += 0b00000001;
			}
			else if (buffer == 50){
				//2
				portB[2] += 0b00000001;
			}
			else if (buffer == 51){
				//3
				portB[3] += 0b00000001;
			}
			else if (buffer == 52){
				//4
				portB[4] += 0b00000001;
			}
			else if (buffer == 53){
				//5
				portB[0] += 0b00000010;
			}
			else if (buffer == 54){
				//6
				portB[1] += 0b00000010;
			}
			else if (buffer == 55){
				//7
				portB[2] += 0b00000010;
			}
			else if (buffer == 56){
				//8
				portB[3] += 0b00000010;
			}
			else if (buffer == 57){
				//9
				portB[4] += 0b00000010;
			}
			else if (buffer == 65){
				//A
				portB[0] += 0b00000100;
			}
			else if (buffer == 66){
				//B
				portB[1] += 0b00000100;
			}
			else if (buffer == 67){
				//C
				portB[2] += 0b00000100;
			}
			else if (buffer == 68){
				//D
				portB[3] += 0b00000100;
			}
			else if (buffer == 69){
				//E
				portB[4] += 0b00000100;
			}
			else if (buffer == 70){
				//F
				portB[0] += 0b00001000;
			}
			else if (buffer == 71){
				//G
				portB[1] += 0b00001000;
			}
			else if (buffer == 72){
				//H
				portB[2] += 0b00001000;
			}
			else if (buffer == 73){
				//I
				portB[3] += 0b00001000;
			}
			else if (buffer == 74){
				//J
				portB[4] += 0b00001000;
			}
			else if (buffer == 75){
				//K
				portB[0] += 0b00010000;
			}
			else if (buffer == 76){
				//L
				portB[1] += 0b00010000;
			}
			else if (buffer == 77){
				//M
				portB[2] += 0b00010000;
			}
			else if (buffer == 78){
				//N
				portB[3] += 0b00010000;
			}
			else if (buffer == 79){
				//O
				portB[4] += 0b00010000;
			}
			else if (buffer == 80){
				//P
				portB[0] += 0b00100000;
			}
			else if (buffer == 81){
				//Q
				portB[1] += 0b00100000;
			}
			else if (buffer == 82){
				//R
				portB[2] += 0b00100000;
			}
			else if (buffer == 83){
				//S
				portB[3] += 0b00100000;
			}
			else if (buffer == 84){
				//T
				portB[4] += 0b00100000;
			}
			
		StrRX_flag =0;
		}
		for (j = 0;j <5;j++){
			PORTB = portB[j];
			PORTC = portC[j];
			_delay_ms(1);
		}
	}
}

