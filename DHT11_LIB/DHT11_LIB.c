/*
 * Project:	DHT11_LIB
 * File:	DHT11_LIB.c
 *
 * Engineer: Bryce Feigum (bafeigum at gmail)
 * Date: December 22, 2012
 *
 * Version: 1.0 - Initial Release
 *
 */

#include <msp430.h>
#include <DHT11_LIB.h>

unsigned char read_Byte(){
	TOUT = 0;
	unsigned char num = 0;
	unsigned char i;
	CLR(TACCTL0,CCIE);
	for (i=8; i>0; i--){
		while(!(TST(P2IN,DPIN))); //Wait for signal to go high
		SET(TACTL,TACLR); //Reset timer
		SET(TA0CTL,0x10); //Reenable timer
		SET(TACCTL0,CCIE); //Enable timer interrupt
		while(TST(P2IN,DPIN)); //Wait for signal to go low
		CLR(TA0CTL,0x30); //Halt Timer
		if (TAR > 13)	 //40 @ 1x divider
			num |= 1 << (i-1);
	}
	return num;
}

unsigned char read_Packet(unsigned char * data){
	start_Signal();
	if (check_Response()){
		//Cannot be done with a for loop!
		data[0] = read_Byte();
		data[1] = read_Byte();
		data[2] = read_Byte();
		data[3] = read_Byte();
		data[4] = read_Byte();
		return 1;
	}
	else return 0;
}

unsigned char check_Response(){
	TOUT=0;
	SET(TACTL,TACLR); 	//Reset timer to 0;
	TACCR0 = 25;		//Set timer to overflow in 100uS. 100 @ 1x divider
	SET(TACCTL0,CCIE); 	//And enable timer interrupt
	while(!(TST(P2IN,DPIN)) && !TOUT);
	if (TOUT)
		return 0;
	else {
		SET(TACTL,TACLR);
		SET(TACCTL0,CCIE);
		while((TST(P2IN,DPIN)) && !TOUT);
		if(TOUT)
			return 0;
		else{
			CLR(TACCTL0,CCIE);	// Disable timer interrupt
			return 1;
		}
	}
}

void start_Signal(){
	SET(P2DIR, DPIN);		// Set Data pin to output direction
	CLR(P2OUT,DPIN); 		// Set output to low
	__delay_cycles(25000); 	// Low for at least 18ms
	SET(P2OUT,DPIN);
	__delay_cycles(30);		// High for at 20us-40us
	CLR(P2DIR,DPIN);		// Set data pin to input direction
}

//returns true if checksum is correct
unsigned char check_Checksum(unsigned char *data){
	if (data[4] != (data[0] + data[1] + data[2] + data[3])){
		return 0;
	}
	else return 1;
}
