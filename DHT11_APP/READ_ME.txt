 * This code interfaces with the DHT11 with the
 * DHT11_Lib library.
 * It receives both temperature and relative humidity in one loop
 * at 1Hz.
 * Humidity is in percentage (20-95)
 * Temperature is in degrees C.
 *
 * LED 1 is blinked while the software is running. It will stutter
 * when a read is initiated.
 *
 * LED 2 is held high as long as the checksum is correct.
 *
 * Insert a breakpoint to ensure proper functionality
 * only AFTER a complete read is completed. (After
 * calling read_Packet() or after calling the fifth
 * read_Byte().
 * Stopping the code in the middle of a read will cause
 * an error during the read.