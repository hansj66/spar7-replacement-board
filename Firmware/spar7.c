/*
 * spar7.c
 *
 * Created: 3/9/2013 4:32:22 PM
 *  Author: Hans Jørgen Grimstad
 *  Homepage: https://www.timeexpander.com
 *  Comments:
 *  1) Compilation:
 *		- with optimization O1
 *		- CKDIV8 fuse NOT set.
 *  2) Note that some switches are NC and some are NO (see portmapping.h)
 *
 *
 * Comments regarding switch timing:
 * 1) A coin activated switch is typically active for 50-150 ms
 * 2) Switch activation is _noisy_ Expect a worst case of a wave train of 1-2 ms pulses, 5-10 ms delay before a stable signal.
 * 2) It may take > 5 ms before it is possible to discriminate between signals (2,3,4 vs 7)
 *
 */ 

// Use internal 8 MHz oscillator
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "Spar7.h"
#include "portmapping.h"

const int DEBOUNCE = 5;
const int DEBOUNCE_HOPPER = 10;
const int SCAN_ATTEMPTS = 5;

void InitPorts()
{
	DDRB = 0x00;	// Input (switches)
	PORTB = 0xFF;	// Pull-ups
	DDRC = 0xFF;	// output (motor relay)
	DDRD = 0xFF;	// output (display)
	
	PORTD = 0;		
	_delay_ms(100); // Just to let things settle down
}

void StartMotor()
{
	PORTC |= 1;
}

void StopMotor()
{
	PORTC &= 11111110;
}

void DisplayCredit(uint8_t value)
{
	uint8_t displayValue = value > 7 ? 7 : value;
	
	displayValue ^= 0xFF;
	displayValue &= 0x0F;
	
	PORTD = displayValue;
}


void RunHopper(int credit)  
{
	StartMotor();
	uint8_t switch_array;
	int displayCredits = credit-1;
		
	for (int i=0; i<credit; i++ ) {

		// Wait for hopper switch to close		
		do {
			_delay_ms(DEBOUNCE_HOPPER);
			switch_array = PINB;
		} while (HOPPER(switch_array));
		
		// Wait for hopper switch to open
		do {
			_delay_ms(DEBOUNCE_HOPPER);
			switch_array = PINB;
		} while (!HOPPER(switch_array));
		DisplayCredit(displayCredits);
		displayCredits--;
	}
	StopMotor();
}

uint8_t ActiveSwitch(uint8_t switch_array)
{
	// 1) We know that the common payout line is already triggered.
	// 2) 2,3 or 4 may already be closed, or may be closing in the _very_ near future. 
	// 3) If 2,3 or 4 does not close until we time out, this is indicative of the 7 switch being hit
	
	for (int i=0; i<SCAN_ATTEMPTS; i++) 
	{
		if (PAY2(switch_array))
		{
			return 2;
		}
		else if (PAY3(switch_array))
		{
			return 3;
		}
		else if (PAY4(switch_array))
		{
			return 4;
		}
		_delay_ms(DEBOUNCE);
		switch_array = PINB;
	}
	for (int i=0; i<SCAN_ATTEMPTS; i++)
	{
		if (PAYOUT(switch_array))
		{
			return 7;
		}
		_delay_ms(DEBOUNCE);
		switch_array = PINB;
	}
	return 0; // Ghost
}

int main(void)
{
	uint8_t switch_array;
	uint8_t credits;

	InitPorts();
	//StartMotor();
	//while (1)
	//{
		//for (int i=0;i<60*60*2;i++)
		//{
			//_delay_ms(1000);
		//}
		//StopMotor();
		//_delay_ms(3000);
		//StartMotor();
	//}



	InitPorts();
	DisplayCredit(0);

	while (1)
	{
		credits = 0;
		
		// Continuously loop and scan for triggering of the payout line.
		switch_array = PINB;
		if (PAYOUT(switch_array))
		{
			// The initial triggering may be a false alarm, since old switches may open
			// intermittently because of vibrations from the coins bumping around.
			_delay_ms(DEBOUNCE);
			switch_array = PINB;
			if (PAYOUT(switch_array))
			{
				credits = ActiveSwitch(switch_array);
				if (0 != credits) {
					DisplayCredit(credits);
					RunHopper(credits);
				}
			}
		}
	}
}




