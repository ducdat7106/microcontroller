/* 
 * File:   dht11.h
 * Author: NGUYEN DUC DAT
 *
 * Created on 4 January, 2022, 5:18 AM
 */

#ifndef DHT11_H
#define	DHT11_H

#ifdef	__cplusplus
extern "C" {
#endif

// DHT11 sensor connection (here data pin is connected to RB0)
#define DHT11_PIN      RB0
#define DHT11_PIN_DIR  TRISB0	//DIR --> Direction
    
#include<xc.h>

/*
Start_Signal(): this function sends the start signal to the sensor, 
it sends a logic low for 25 ms and a logic high for 30 us. 
*/
void Start_Signal(void);

/*
 Check_Response(): this function checks if there is a response from the sensor 
 (after sending the start signal using the previous function), 
 returns 1 (true) if ok and 0 (false) if error (for example a connection problem).
 */
__bit Check_Response();

/*
 Read_Data(*dht_data): this function reads temperature and humidity data from the sensor (4 bytes), 
 it also reads an other byte (5th byte) which is used as a checksum. 
 This function returns 0 (false) if data read was ok and 1 (true) if there was a time out problem.
 */
__bit Read_Data(unsigned char* dht_data);


#ifdef	__cplusplus
}
#endif

#endif	/* DHT11_H */

