/*
 * blink.c
 *
 *  Created on: 9 de out de 2015
 *      Author: aluno
 */
#include <avr/io.h>
#include <avr/interrupt.h>



static unsigned char led1_msk = 0x02; // 0000 0010
static unsigned char led2_msk = 0x01; // 0000 0001

volatile unsigned char led1_state = 0;
volatile  unsigned char led2_state = 0;

void setup() {
	void milli_counter_start();
	EIMSK = 0x03;
	EICRA = 0x0f;
	DDRB = (1<<DDB1)|(1<<DDB0);
}
void delay(){
	volatile unsigned long x = 0xffff;
	while(x--);
}

ISR(INT0_vect){
	led1_state = !led1_state;
}

ISR(INT1_vect){
	led2_state = !led2_state;
}

void loop() {
	if (led1_state)
		PORTB |= led1_msk ;
	else
		PORTB &= ~led1_msk;
	if (led2_state)
		PORTB |= led2_msk;
	else
		PORTB &= ~led2_msk;

	delay();
}

int main() {
	setup();
	asm("sei");
	while(1)
		loop();
}
