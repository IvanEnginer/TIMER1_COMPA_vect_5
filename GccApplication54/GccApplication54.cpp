#include <avr/io.h>
#include <avr/interrupt.h>
volatile int vol = 0;
volatile int sec = 0;
volatile unsigned char segcounter = 0;
char SEGMENTE[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

ISR(TIMER1_COMPA_vect)
{
	vol++;
	TCNT1H=0x00;
	TCNT1L=0x00;
}

ISR(TIMER2_OVF_vect)
{
	
		PORTB = 0x00;
		PORTA = ~(1 << segcounter);
		switch (segcounter)
		{
			case 0:
			PORTB = SEGMENTE[vol];
			break;
			case 1:
			PORTB = SEGMENTE[sec];
			break;
		}
		
			if ((segcounter++) == 1)
			{
				segcounter = 0;
			}
}

int main(void)
{
	DDRA=0xFF;
	PORTA=0x00;
	PORTB=0x00;
	DDRB=0xFF;
	TCCR1A=0x00;
	TCCR1B=0x05;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x1E;
	OCR1AL=0x85;
	OCR1BH=0x00;
	OCR1BL=0x00;
	TIMSK=0x50;
	TCCR2 |= (1 << CS21);
	sei();
	
	while(1)
	{
			if (vol == 10)
			{
				sec++;
				vol = 0;
			}
			if (sec == 10)
			{
				sec = 0;
			}
	}
}