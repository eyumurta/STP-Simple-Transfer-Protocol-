/*
 * STP_config.h
 *
 *  Created on: May 16, 2023
 *      Author: Muhammed
 */

#ifndef STP_CONFIG_STP_CONFIG_H_
#define STP_CONFIG_STP_CONFIG_H_

#define MAX_DATA_LENGHT 32


#define MAX_REGISTER_GROUP 4


#define REGISTER_GROUP_1 1
#define REGISTER_GROUP_2 2
#define REGISTER_GROUP_3 3
#define REGISTER_GROUP_4 4
#define REGISTER_GROUP_5 5
#define REGISTER_GROUP_6 6
#define REGISTER_GROUP_7 7
#define REGISTER_GROUP_8 8


#define WRITE_REQUEST 1
#define READ_REQUEST 2




#define NO_ERROR 0x00
#define WRITE_CRC_ERROR 0x01
#define READ_CRC_ERROR 0x02
#define WRITE_OUT_OF_RANGE 0x03
#define READ_OUT_OF_RANGE 0x04
#define ANOTHER_DEVICE_RESPONSE 0x05//This error code for master

#endif /* STP_CONFIG_STP_CONFIG_H_ */
