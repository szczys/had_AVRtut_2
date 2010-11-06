/*
* Hackaday.com AVR Tutorial firmware
* written by: Mike Szczys (@szczys)
* 10/24/2010
*
* ATmega168
* Blinks one LED conneced to PD0
*
* http://hackaday.com/2010/10/25/avr-programming-02-the-hardware/
*/

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{

  //Setup the clock
  cli();			//Disable global interrupts
  TCCR1B |= 1<<CS11 | 1<<CS10;	//Divide by 64
  OCR1A = 15624;		//Count 15624 cycles for 1 second interrupt
  TCCR1B |= 1<<WGM12;		//Put Timer/Counter1 in CTC mode
  TIMSK1 |= 1<<OCIE1A;		//enable timer compare interrupt
  sei();			//Enable global interrupts

  //Setup the I/O for the LED

  DDRD |= (1<<0);		//Set PortD Pin0 as an output
  PORTD |= (1<<0);		//Set PortD Pin0 high to turn on LED

  while(1) { }			//Loop forever, interrupts do the rest
}

ISR(TIMER1_COMPA_vect)		//Interrupt Service Routine
{
  PORTD ^= (1<<0);		//Use xor to toggle the LED
}
