 * This library interfaces with the DHT11 device to
 * read temperature and humidity. The maximum
 * sampling rate of the DHT11 is 1Hz.
 *
 * The data pin of the DHT11 must be connected
 * to PIN 2.4 on the MSP430
 * The Vcc pin of the DHT11 should be connected
 * to a 3.3V power supply rail.
 * THe GND pin of the DHT11 must be connected to 
 * to the GND pin of the MSP430
 *
 * The DHT11 requires precise timing to read
 * from the device. There is one necessary timer
 * to allow this library to work properly.
 * The timer used is TA0. It should be set to
 * "up" mode and should count every 4uS (250kHz).
 * This can be achieved my modifying the frequency
 * at which the MSP430 runs, modifying the counter's
 * divider, or both. An ISR must be included
 * which sets an unsigned char volatile TOUT
 * to 1. The ISR shuold also clear the interrupt flag
 * by setting the CCIFG bit in the TACCTL0 register.
 *
 * The humidity data is sent in decimal form
 * and represents the humidity in percentage
 * (20-95).
 *
 * The temperature data is sent in decimal form
 * and represents the temperature in degrees
 * Centigrade (0-50).
 *
 * The checksum represents the sum of both
 * the humidity data (both bytes but the second
 * byte should be equal to 0) and the temperature
 * data (both bytes).
 *
 * For an example program including examples
 * and the proper setup instructions, check
 * the main.c file in the DHT11_APP project.
 *
 * There are two ways to receive data from the DHT11
 * with this library. The simplest way is to
 * call the read_Packet() function to send a
 * "start" signal, wait for	the DHT11 to respond,
 * and gather all of the data from the DHT11.
 * Pass an array with 5 unsigned char elements to
 * read_Packet() and it will load the array with
 * the first humidity byte, an empty humidity byte,
 * the first temperature byte, an empty temperature byte,
 * and the checksum in that order (first humidity byte is
 * loaded into array index 0).
 *
 * The second way is to manually handle all of these
 * steps by
 * 1. Calling start_Signal().
 * 2. Calling check_Response()
 * 3. Calling read_Byte() 5 times to gather the
 * the first humidity byte, an empty humidity byte,
 * the first temperature byte, an empty temperature byte,
 * and the checksum in that order one immediately one
 * after the other. (There can be no other code in
 * between the read_Byte calls.)
 *
 * !!!Step 3 cannot be done with a for loop!!!
 * The timing requirements are not met with
 * the added code instructions required by a for loop.
 *
 *
 * unsigned char read_Byte()
 * Returns the next byte read from the DHT11.
 * This function should be called 5 times immediately after
 * start_Signal() and check_Response()
 *
 * void start_Signal()
 * Sends the start signal to the DHT11. Should be followed
 * immediately by check_Response() and 5 calls to read_Byte()
 *
 * unsigned char check_Response()
 * Checks the handshake signal sent by the DHT11. If
 * the handshake is successful, 1 is returned.
 * If the handshake fails, 0 is returned. If this happens
 * the read should be aborted and tried again 1 second later.
 *
 * unsigned char read_Packet(unsigned char *)
 * Completes a complete read cycle from the DHT11.
 * An array of 5 unsigned char elements should be passed.
 * The handshaking is handled and 5 bytes are read
 * and stored in the array passed as an argument.
 * The bytes stored are the first humidity byte,
 * an empty humidity byte, the first temperature byte,
 * an empty temperature byte, and the checksum in that order.
 * Will return 1 if the read is completed successfully.
 * Will return 0 is the read is not completely successfully.
 * This function does not check the checksum. If the checksum
 * is not correct, the function will still return a 1. This is
 * done to save cycles in case a user does not care if the
 * checksum is correct.
 *
 * unsigned char check_Checksum (unsigned char *)
 * Checks the checksum returned by the DHT11.
 * The array passed should be formatted as the read_Packet
 * function stores data in the passed array (the array passed
 * to read_Packet can be directly inserted into this function).
 * Will return 1 if the checksum is correct.
 * Will return 0 if the checksum is incorrect.