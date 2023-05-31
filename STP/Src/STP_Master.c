/*
 * STP.c
 *
 *  Created on: May 16, 2023
 *      Author: Muhammed
 */
#include "STP.h"


//Packing the sent frame.The read reguest the slave device
void Master_Frame_Packer_Read_Req(STP_MASTER_Typedef *STP, uint8_t Register_Group,
		uint8_t Slave_Adress) {

	uint16_t CRC;
	int8_t data[MAX_DATA_LENGHT];

	STP->Slave_Adress = Slave_Adress;
	STP->Register_Group = Register_Group;
	STP->Sender_Frame[0] = STP->Slave_Adress;
	STP->Sender_Frame[1] = STP->Register_Group;

	STP->Startin_Adress_of_Register = 0;
	STP->Number_of_Register = 0;
	STP->Sender_Frame[2] = STP->Startin_Adress_of_Register;
	STP->Sender_Frame[3] = STP->Number_of_Register;

	STP->Request = READ_REQUEST;
	STP->Error_Information = 0x00;
	STP->Sender_Frame[4] = STP->Request;
	STP->Sender_Frame[5] = STP->Error_Information;

	//Memory_Copybu alanı sıfrla doldurmak gerekbilir.
	memcpy(STP->Data, data, MAX_DATA_LENGHT);
	memcpy(&(STP->Sender_Frame[6]), STP->Data, MAX_DATA_LENGHT);

	//Crc en son hesaplanır.
	CRC = MODBUS_CRC16_v3(STP->Sender_Frame, MAX_DATA_LENGHT + 5);
	STP->Sender_Frame[38] = CRC >> 8; //High Byte
	STP->Sender_Frame[39] = CRC & 0x00FF; //Low byte

}

//BURAD adres aralığı ile ilgili bir ontrol yapılmalı
//Packing the sent frame.The write reguest the slave device
//kaç tane adrese yazılacağı ve hangi adresten itibaren yazma yapacağı girilir.
void Master_Frame_Packer_Write_Req(STP_MASTER_Typedef *STP, uint8_t Register_Group,uint8_t Slave_Adress, uint8_t Startin_Adress_of_Register,uint8_t Number_of_Register, int8_t Data[]){

	uint16_t CRC;

	STP->Slave_Adress = Slave_Adress;
	STP->Register_Group = Register_Group;
	STP->Sender_Frame[0] = STP->Slave_Adress;
	STP->Sender_Frame[1] = STP->Register_Group;

	STP->Startin_Adress_of_Register = Startin_Adress_of_Register;
	STP->Number_of_Register = Number_of_Register;
	STP->Sender_Frame[2] = STP->Startin_Adress_of_Register;
	STP->Sender_Frame[3] = STP->Number_of_Register;

	STP->Request = WRITE_REQUEST;
	STP->Error_Information = 0x00;
	STP->Sender_Frame[4] = STP->Request;
	STP->Sender_Frame[5] = STP->Error_Information;

	//Memory_Copy
	memcpy(STP->Data, Data, MAX_DATA_LENGHT);
	memcpy(&(STP->Sender_Frame[6]), STP->Data,
			MAX_DATA_LENGHT);

	//Crc en son hesaplanır.
	CRC = MODBUS_CRC16_v3(STP->Sender_Frame, MAX_DATA_LENGHT + 5);
	//STP->Sender_Frame[MAX_DATA_LENGHT + 5 + 1] = CRC >> 8; //High Byte
	STP->Sender_Frame[MAX_DATA_LENGHT + 5 + 1] = CRC >> 8;
	STP->Sender_Frame[MAX_DATA_LENGHT + 5 + 2] = CRC & 0x00FF; //Low byte

}

//Master gelen cevabı ayrıştırır.
//De packing the receiving frame
void Master_Frame_Depacker(STP_MASTER_Typedef *STP,uint8_t rawdata[]) {

	uint16_t CRC;
	memcpy(STP->Response_From_Slave.Receiving_Frame, rawdata, MAX_DATA_LENGHT + 8);

	STP->Response_From_Slave.Slave_Adress =STP->Response_From_Slave.Receiving_Frame[0];
	STP->Response_From_Slave.Register_Group =STP->Response_From_Slave.Receiving_Frame[1];
	STP->Response_From_Slave.Startin_Adress_of_Register =STP->Response_From_Slave.Receiving_Frame[2];
	STP->Response_From_Slave.Number_of_Register =STP->Response_From_Slave.Receiving_Frame[3];
	STP->Response_From_Slave.Request = STP->Response_From_Slave.Receiving_Frame[4];
	STP->Response_From_Slave.Error_Information =STP->Response_From_Slave.Receiving_Frame[5];
	memcpy((STP->Response_From_Slave.Data),
			&(STP->Response_From_Slave.Receiving_Frame[6]),
			 MAX_DATA_LENGHT);

	CRC = MODBUS_CRC16_v3((STP->Response_From_Slave.Receiving_Frame), MAX_DATA_LENGHT + 5);
	STP->Response_From_Slave.CRC_High = CRC >> 8;
	STP->Response_From_Slave.CRC_Low = CRC & 0x00ff;

	if (STP->Response_From_Slave.CRC_High
			== rawdata[MAX_DATA_LENGHT + 5 + 1]
					   && STP->Response_From_Slave.CRC_Low
					   == rawdata[MAX_DATA_LENGHT + 5 + 2]) {

		//gelen cevap istek yapılan cihazdan mı gelmiş?
		if(STP->Response_From_Slave.Slave_Adress == STP->Slave_Adress){

			switch (STP->Request) {
				case READ_REQUEST:

					Master_Register_Write((int8_t *)STP->Response_From_Slave.Data,STP->Register_Group);
					STP->Data_Callback(STP->Response_From_Slave);

					break;

				case WRITE_REQUEST:
					STP->Data_Callback(STP->Response_From_Slave);
					break;

				default:
					break;
			}



		}
		else{
			STP->Response_From_Slave.Error_Information = ANOTHER_DEVICE_RESPONSE;
			STP->Error_Callback(STP->Response_From_Slave);
		}




	} else {
		//CRC_Error
		STP->Response_From_Slave.Error_Information = READ_CRC_ERROR;
		STP->Error_Callback(STP->Response_From_Slave);

	}

}

void Init_STP_Master(STP_MASTER_Typedef *STP,void (*Data_Callback)(STP_RESPONS_FROM_SLAVE_Typedef STP),void (*Error_Callback)(STP_RESPONS_FROM_SLAVE_Typedef STP)){

	STP->Data_Callback = Data_Callback;
	STP->Error_Callback = Error_Callback;


}
void Master_Register_Write(int8_t Reg_Data[],uint8_t Register_Group){

	switch (Register_Group) {
					case REGISTER_GROUP_1:
						memcpy(Master_Register.Register_Group_1,
								Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_2:
						memcpy(Master_Register.Register_Group_2,
														Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_3:
						memcpy(Master_Register.Register_Group_3,
														Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_4:
						memcpy(Master_Register.Register_Group_4,
														Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_5:
						memcpy(Master_Register.Register_Group_5,
														Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_6:
						memcpy(Master_Register.Register_Group_6,
														Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_7:
						memcpy(Master_Register.Register_Group_7,
														Reg_Data, MAX_DATA_LENGHT);
						break;
					case REGISTER_GROUP_8:
						memcpy(Master_Register.Register_Group_8,
														Reg_Data, MAX_DATA_LENGHT);
						break;
					default:
						break;
					}
}



