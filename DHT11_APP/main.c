/*
 * 
 * Engineer: Bryce Feigum (bafeigum at gmail)
 * Date: December 22, 2012
 *
 * Version: 1.0 - Initial Release
 * Version: 1.1 - Added GNUv2 License
 *
 * Copyright (C) 2013  Bryce Feigum
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * Project:	DHT11_LIB
 * File:	main.c
 */
#include <msp430.h>
#include <DHT11_LIB.h>

unsigned char RH_byte1;
unsigned char RH_byte2;
unsigned char T_byte1;
unsigned char T_byte2;
unsigned char checksum;

unsigned char Packet[5];

void init(void);

unsigned char volatile TOUT;			//REQUIRED for library
unsigned char volatile SECOND_TIMER=0;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void CCR0_ISR(void){
		SECOND_TIMER++;
		TOUT=1;
		TOG (P1OUT,0x01);
		CLR (TACCTL0, CCIFG);
}

void main(void) {
	init();
	
	while(1){
		//Must wait 1 second initially and between all reads
		if(SECOND_TIMER >= 5){		//5 @ CCR0 = 50000 & div 4
			// Manual way to gather all data without array
			/*
			start_Signal();
			if(check_Response()){
				RH_byte1 = read_Byte();
				RH_byte2 = read_Byte();
				T_byte1 = read_Byte();
				T_byte2 = read_Byte();
				checksum = read_Byte();
			}
			*/

			//	Simple way to gather all data with one instruction
			read_Packet(Packet);
			RH_byte1 =	Packet[0];
			RH_byte2 =	Packet[1];
			T_byte1 =	Packet[2];
			T_byte2 =	Packet[3];
			checksum =	Packet[4];

			if (check_Checksum(Packet))
				SET (P1OUT, 0x40);

			SET (TACTL, TACLR);
			SET (TA0CTL, 0x10);
			TACCR0 = 50000;		//Initialize the timer to count at 5Hz
			SECOND_TIMER = 0;	//Clear counter
		}
	}
}

void init(){
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer

	P1OUT  = 0x00;				//Start with nothing being output
	P1DIR  = 0x41;				// Set LED to output direction

	BCSCTL1 = CALBC1_1MHZ; 		// Set oscillator to 1MHz
	DCOCTL = CALDCO_1MHZ;  		// Set oscillator to 1MHz

	TACCR0 = 50000;				// Initialize the timer to count at 5Hz
	TACCTL0 = CCIE;				// Enable interrupt
	TA0CTL = TASSEL_2 + ID_2 + MC_1 + TACLR;	// SMCLK, div 4, up mode,
												// clear timer
	_enable_interrupt();						//Enable global interrupt
}
