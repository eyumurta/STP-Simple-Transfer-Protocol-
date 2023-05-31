/*
 * STP.h
 *
 *  Created on: May 16, 2023
 *      Author: Muhammed
 */

#ifndef STP_INC_STP_H_
#define STP_INC_STP_H_

#include "STP_config.h"
#include <stdint.h>
#include <string.h>




/*    ********************* MASTER *************************    */

typedef struct{

	int8_t Register_Group_1[MAX_DATA_LENGHT]	;
	int8_t Register_Group_2[MAX_DATA_LENGHT]	;
	int8_t Register_Group_3[MAX_DATA_LENGHT]	;
	int8_t Register_Group_4[MAX_DATA_LENGHT]	;
	int8_t Register_Group_5[MAX_DATA_LENGHT]	;
	int8_t Register_Group_6[MAX_DATA_LENGHT]	;
	int8_t Register_Group_7[MAX_DATA_LENGHT]	;
	int8_t Register_Group_8[MAX_DATA_LENGHT]	;
}MASTER_REGISTER;


//mastera gelen cevaplar
typedef struct {

	uint8_t Slave_Adress;
	uint8_t Register_Group;
	uint8_t Startin_Adress_of_Register;
	uint8_t Number_of_Register;
	uint8_t Request;
	uint8_t Error_Information;
	uint8_t Data[MAX_DATA_LENGHT];
	uint8_t CRC_High;
	uint8_t CRC_Low;
	uint8_t Receiving_Frame[MAX_DATA_LENGHT + 8];




}STP_RESPONS_FROM_SLAVE_Typedef;

//Master gönderilen istekler için yazıldı.
typedef struct {

	uint8_t Slave_Adress;
	uint8_t Register_Group;
	uint8_t Startin_Adress_of_Register;
	uint8_t Number_of_Register;
	uint8_t Request;
	uint8_t Error_Information;
	uint8_t Data[MAX_DATA_LENGHT];
	uint8_t CRC_High;
	uint8_t CRC_Low;
	uint8_t Sender_Frame[MAX_DATA_LENGHT + 8];

	STP_RESPONS_FROM_SLAVE_Typedef Response_From_Slave;

	void (*Data_Callback)(STP_RESPONS_FROM_SLAVE_Typedef STP);
	void (*Error_Callback)(STP_RESPONS_FROM_SLAVE_Typedef STP);




}STP_MASTER_Typedef;

/*    ********************* MASTER *************************    */


/*    ********************* SLAVE *************************    */
typedef struct{

int8_t Register_Group_1[MAX_DATA_LENGHT]	;
int8_t Register_Group_2[MAX_DATA_LENGHT]	;
int8_t Register_Group_3[MAX_DATA_LENGHT]	;
int8_t Register_Group_4[MAX_DATA_LENGHT]	;
int8_t Register_Group_5[MAX_DATA_LENGHT]	;
int8_t Register_Group_6[MAX_DATA_LENGHT]	;
int8_t Register_Group_7[MAX_DATA_LENGHT]	;
int8_t Register_Group_8[MAX_DATA_LENGHT]	;
}SLAVE_REGISTER;



//SLAVE Gelen isteklerde hata algılandığında oluşturulacak cevap.
typedef struct{

	    uint8_t Slave_Adress;
		uint8_t Register_Group;
		uint8_t Startin_Adress_of_Register;
		uint8_t Number_of_Register;
		uint8_t Request;
		uint8_t Error_Information;
		uint8_t Data[MAX_DATA_LENGHT];
		uint8_t CRC_High;
		uint8_t CRC_Low;
		uint8_t Sender_Frame[MAX_DATA_LENGHT + 8];

}STP_SLAVE_Response;

//SLAVE Gelen istkler için yazıldı.
typedef struct{

	    uint8_t Slave_Adress;
		uint8_t Register_Group;
		uint8_t Startin_Adress_of_Register;
		uint8_t Number_of_Register;
		uint8_t Request;
		uint8_t Error_Information;
		uint8_t Data[MAX_DATA_LENGHT];
		uint8_t CRC_High;
		uint8_t CRC_Low;
		uint8_t Received_Frame[MAX_DATA_LENGHT + 8];

		STP_SLAVE_Response STP_SLAVE_Response;

			void (*Data_Callback)(STP_SLAVE_Response STP);
		    void (*Error_Callback)(STP_SLAVE_Response STP);


}STP_Received_Typedef;

/*    ********************** SLAVE ****************************    */

 uint16_t MODBUS_CRC16_v3( uint8_t *buf, uint8_t len );
void Master_Frame_Packer_Read_Req(STP_MASTER_Typedef *STP,uint8_t Register_Group,uint8_t Slave_Adress);
void Master_Frame_Packer_Write_Req(STP_MASTER_Typedef *STP, uint8_t Register_Group,uint8_t Slave_Adress, uint8_t Startin_Adress_of_Register,uint8_t Number_of_Register, int8_t Data[]);
void Master_Frame_Depacker(STP_MASTER_Typedef *STP,uint8_t rawdata[]);
void Generate_Slave_Response(STP_Received_Typedef *STP,uint8_t Error_Information);
void Calculate_CRC(STP_Received_Typedef *STP);
void Slave_Frame_DePacker(STP_Received_Typedef *STP,int8_t Data[]);
void Slave_Register_Response(STP_Received_Typedef *STP,uint8_t Request);
void Register_Write(int8_t Reg_Data[],uint8_t Register_Group);
void Init_STP_Slave(STP_Received_Typedef *STP,int8_t slave_adr,void (*Data_Callback)(STP_SLAVE_Response STP),void (*Error_Callback)(STP_SLAVE_Response STP));
void Write_Request(STP_Received_Typedef *STP,int8_t Data[]);
void Read_Request(STP_Received_Typedef *STP,int8_t Data[]);
void Init_STP_Master(STP_MASTER_Typedef *STP,void (*Data_Callback)(STP_RESPONS_FROM_SLAVE_Typedef STP),void (*STP_RESPONS_FROM_SLAVE_Typedef)(STP_RESPONS_FROM_SLAVE_Typedef STP));
void Master_Register_Write(int8_t Reg_Data[],uint8_t Register_Group);
static SLAVE_REGISTER Slave_Register;
static MASTER_REGISTER Master_Register;


#endif /* STP_INC_STP_H_ */
