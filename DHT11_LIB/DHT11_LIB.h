/*
 * DHT11_LIB
 * DHT11_LIB.h
 *
 * Engineer: Bryce Feigum (bafeigum at gmail)
 * Date: December 22, 2012
 * Version: 1.0
 *
 */

#ifndef DHT11_LIB_H_
#define DHT11_LIB_H_

#define TST(x,y)	(x & (y))
#define SET(x,y)	(x|= (y))
#define CLR(x,y)	(x &= ~(y))
#define TOG(x,y)	(x ^= (y))

#define DPIN BIT4

extern unsigned char volatile TOUT;

void start_Signal(void);
unsigned char check_Response(void);
unsigned char read_Byte(void);
unsigned char read_Packet(unsigned char *);		//Pass an array with 5 elements
unsigned char check_Checksum(unsigned char *);	//Pass an array with 5 elements

#endif /* DHT11_LIB_H_ */
