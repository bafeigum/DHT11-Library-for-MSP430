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
 * Project:  DHT11_LIB
 * File:	DHT11_LIB.h
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
