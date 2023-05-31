/*
 * STP_Slave.c
 *
 *  Created on: 27 May 2023
 *      Author: Muhammed
 */



#include "STP.h"

//low level part of API
void Slave_Frame_DePacker(STP_Received_Typedef *STP,int8_t Data[]) {

	uint16_t CRC;
	memcpy(STP->Received_Frame, Data, MAX_DATA_LENGHT + 8);

	STP->Register_Group = STP->Received_Frame[1];
	STP->Startin_Adress_of_Register = STP->Received_Frame[2];
	STP->Number_of_Register = STP->Received_Frame[3];
	STP->Request = STP->Received_Frame[4];
	STP->Error_Information = STP->Received_Frame[5];

	CRC = MODBUS_CRC16_v3(STP->Received_Frame, MAX_DATA_LENGHT + 5);
	STP->CRC_High = CRC >> 8; //High Byte
	STP->CRC_Low = CRC & 0x00FF; //Low byte
	if( (STP->Slave_Adress == STP->Received_Frame[0])){
	switch (STP->Request) {

	case READ_REQUEST:

		Read_Request(STP, Data);

		break;
	case WRITE_REQUEST:

		Write_Request(STP,Data);

		break;



	default:
		break;
	}

}}

//SLAVE Response generator
//low level part of API
void Generate_Slave_Response(STP_Received_Typedef *STP,
		uint8_t Error_Information) {

	STP->STP_SLAVE_Response.Slave_Adress = STP->Slave_Adress;
	STP->STP_SLAVE_Response.Register_Group = STP->Register_Group;
	STP->STP_SLAVE_Response.Sender_Frame[0] =STP->STP_SLAVE_Response.Slave_Adress;
	STP->STP_SLAVE_Response.Sender_Frame[1] =STP->STP_SLAVE_Response.Register_Group;

	STP->STP_SLAVE_Response.Startin_Adress_of_Register =STP->Startin_Adress_of_Register;
	STP->STP_SLAVE_Response.Number_of_Register = STP->Number_of_Register;
	STP->STP_SLAVE_Response.Sender_Frame[2] =STP->STP_SLAVE_Response.Startin_Adress_of_Register;
	STP->STP_SLAVE_Response.Sender_Frame[3] =STP->STP_SLAVE_Response.Number_of_Register;

	STP->STP_SLAVE_Response.Request = STP->Request;
	STP->STP_SLAVE_Response.Error_Information = Error_Information;
	STP->STP_SLAVE_Response.Sender_Frame[4] = STP->STP_SLAVE_Response.Request;
	STP->STP_SLAVE_Response.Sender_Frame[5] =STP->STP_SLAVE_Response.Error_Information;

}

//low level part of API
void Calculate_CRC(STP_Received_Typedef *STP) {
	uint16_t CRC;
	CRC = MODBUS_CRC16_v3(STP->STP_SLAVE_Response.Sender_Frame,MAX_DATA_LENGHT + 5);		//Calculatin CRC
	STP->STP_SLAVE_Response.CRC_High = CRC >> 8;		//High Byte
	STP->STP_SLAVE_Response.CRC_Low = CRC & 0x00FF;		//Low byte
	STP->STP_SLAVE_Response.Sender_Frame[MAX_DATA_LENGHT + 5 + 1] =STP->STP_SLAVE_Response.CRC_High;		//High Byte
	STP->STP_SLAVE_Response.Sender_Frame[MAX_DATA_LENGHT + 5 + 2] =STP->STP_SLAVE_Response.CRC_Low;		//Low byte

}

//low level part of API
void Slave_Register_Response(STP_Received_Typedef *STP,uint8_t Request){
if(Request==READ_REQUEST){
	switch (STP->Register_Group) {
				case REGISTER_GROUP_1:
					memcpy(STP->STP_SLAVE_Response.Data,
							Slave_Register.Register_Group_1, MAX_DATA_LENGHT);
					break;

				case REGISTER_GROUP_2:
					memcpy(STP->STP_SLAVE_Response.Data,
							Slave_Register.Register_Group_2, MAX_DATA_LENGHT);
					break;

				case REGISTER_GROUP_3:
					memcpy(STP->STP_SLAVE_Response.Data,
							Slave_Register.Register_Group_3, MAX_DATA_LENGHT);
					break;

				case REGISTER_GROUP_4:
					memcpy(STP->STP_SLAVE_Response.Data,
							Slave_Register.Register_Group_4, MAX_DATA_LENGHT);
					break;

				case REGISTER_GROUP_5:
					memcpy(STP->STP_SLAVE_Response.Data,
							Slave_Register.Register_Group_5, MAX_DATA_LENGHT);
					break;

				case REGISTER_GROUP_6:
					memcpy(STP->STP_SLAVE_Response.Data,
							Slave_Register.Register_Group_6, MAX_DATA_LENGHT);
					break;

				case REGISTER_GROUP_7:
					memcpy(STP->STP_SLAVE_Response.Data,
							Slave_Register.Register_Group_7, MAX_DATA_LENGHT);
					break;
				case REGISTER_GROUP_8:
					memcpy(STP->STP_SLAVE_Response.Data,
							Slave_Register.Register_Group_8, MAX_DATA_LENGHT);
					break;
				default:
					break;
				}}
else if(Request == WRITE_REQUEST){

		switch (STP->Register_Group) {
					case REGISTER_GROUP_1:
						memcpy(&(Slave_Register.Register_Group_1[STP->Startin_Adress_of_Register]),&(STP->Data[STP->Startin_Adress_of_Register]),STP->Number_of_Register);
						break;

					case REGISTER_GROUP_2:
						memcpy(STP->STP_SLAVE_Response.Data,
								&(Slave_Register.Register_Group_2[STP->Startin_Adress_of_Register]),
								STP->Number_of_Register);
						break;

					case REGISTER_GROUP_3:
						memcpy(STP->STP_SLAVE_Response.Data,
								&(Slave_Register.Register_Group_3[STP->Startin_Adress_of_Register]),
								STP->Number_of_Register);
						break;

					case REGISTER_GROUP_4:
						memcpy(STP->STP_SLAVE_Response.Data,
								&(Slave_Register.Register_Group_4[STP->Startin_Adress_of_Register]),
								STP->Number_of_Register);
						break;

					case REGISTER_GROUP_5:
						memcpy(STP->STP_SLAVE_Response.Data,
								&(Slave_Register.Register_Group_5[STP->Startin_Adress_of_Register]),
								STP->Number_of_Register);
						break;

					case REGISTER_GROUP_6:
						memcpy(STP->STP_SLAVE_Response.Data,
								&(Slave_Register.Register_Group_6[STP->Startin_Adress_of_Register]),
								STP->Number_of_Register);
						break;

					case REGISTER_GROUP_7:
						memcpy(STP->STP_SLAVE_Response.Data,
								&(Slave_Register.Register_Group_7[STP->Startin_Adress_of_Register]),
								STP->Number_of_Register);
						break;
					case REGISTER_GROUP_8:
						memcpy(STP->STP_SLAVE_Response.Data,
								&(Slave_Register.Register_Group_8[STP->Startin_Adress_of_Register]),
								STP->Number_of_Register);


							break;
					default:
						break;}



}
}

//write data for the slave register.
//Buraya paremetre olarak verilen dizi registerlara yüklenir.Slave cihazın içerisindeki adreslerdir. Okuma isteği geldiğinde bu adreslerdeki bilgiler
//gönderilir.
//user write register coomand


//user slave init function
void Init_STP_Slave(STP_Received_Typedef *STP,int8_t slave_adr,void (*Data_Callback)(STP_SLAVE_Response STP),void (*Error_Callback)(STP_SLAVE_Response STP)){

	STP->Data_Callback = Data_Callback;
	STP->Error_Callback = Error_Callback;
	STP->Slave_Adress = slave_adr ;

}

//Low level part of API
void Write_Request(STP_Received_Typedef *STP,int8_t Data[]){
	memcpy(STP->Data,&Data[6], MAX_DATA_LENGHT);

	if (((MAX_DATA_LENGHT < STP->Number_of_Register)
					| (STP->Register_Group > MAX_REGISTER_GROUP)
					| (MAX_DATA_LENGHT < STP->Startin_Adress_of_Register)
					| (MAX_DATA_LENGHT <= (STP->Number_of_Register
									+ STP->Startin_Adress_of_Register)))) {

				Generate_Slave_Response(STP, WRITE_OUT_OF_RANGE);

				memset(STP->STP_SLAVE_Response.Data, 0, MAX_DATA_LENGHT);//Fill Data Area to 0.
				memcpy(&(STP->STP_SLAVE_Response.Sender_Frame[6]),
						STP->STP_SLAVE_Response.Data, MAX_DATA_LENGHT);

				Calculate_CRC(STP);
				//Request out of range
				STP->Error_Callback(STP->STP_SLAVE_Response);

			}

			else if (STP->CRC_High == STP->Received_Frame[MAX_DATA_LENGHT + 5 + 1]
					&& STP->CRC_Low == STP->Received_Frame[MAX_DATA_LENGHT + 5 + 2]) {
				Slave_Register_Response( STP, WRITE_REQUEST);


				Generate_Slave_Response(STP, NO_ERROR);
				//burada data alanı sıfırlanacak.
				memcpy(&(STP->STP_SLAVE_Response.Sender_Frame[6]),
						STP->STP_SLAVE_Response.Data, MAX_DATA_LENGHT);

				Calculate_CRC(STP);
				//Succesful Command
				STP->Data_Callback(STP->STP_SLAVE_Response);
			} else {

				memset(STP->STP_SLAVE_Response.Data, 0, MAX_DATA_LENGHT);//Fill Data Area to 0.
				memcpy(&(STP->STP_SLAVE_Response.Sender_Frame[6]),
						STP->STP_SLAVE_Response.Data, MAX_DATA_LENGHT);

				Generate_Slave_Response(STP, WRITE_CRC_ERROR);

				Calculate_CRC(STP);
				//Crc Error.
				STP->Error_Callback(STP->STP_SLAVE_Response);
			}



}

//Low level part of API
void Read_Request(STP_Received_Typedef *STP,int8_t Data[]){

	if ((MAX_DATA_LENGHT < STP->Number_of_Register)
					| (STP->Register_Group > MAX_REGISTER_GROUP)) {

				Generate_Slave_Response(STP, READ_OUT_OF_RANGE);

				memset(STP->STP_SLAVE_Response.Data, 0, MAX_DATA_LENGHT);//Fill Data Area to 0.
				memcpy(&(STP->STP_SLAVE_Response.Sender_Frame[6]),
						STP->STP_SLAVE_Response.Data, MAX_DATA_LENGHT);

				Calculate_CRC(STP);

				//request out of range
				STP->Error_Callback(STP->STP_SLAVE_Response);

			}

			else if (STP->CRC_High == STP->Received_Frame[MAX_DATA_LENGHT + 5 + 1]
					&& STP->CRC_Low == STP->Received_Frame[MAX_DATA_LENGHT + 5 + 2]) {
				Slave_Register_Response(STP, READ_REQUEST);
				Generate_Slave_Response(STP, NO_ERROR);

				memcpy(&(STP->STP_SLAVE_Response.Sender_Frame[6]),
						STP->STP_SLAVE_Response.Data, MAX_DATA_LENGHT);

				Calculate_CRC(STP);

				//burada GELEN istenen adrese göre işlem yapılacak.
				//Succesful command
				STP->Data_Callback(STP->STP_SLAVE_Response);

			} else {
				Generate_Slave_Response(STP, READ_CRC_ERROR);

				memset(STP->STP_SLAVE_Response.Data, 0, MAX_DATA_LENGHT);//Fill Data Area to 0.
				memcpy(&(STP->STP_SLAVE_Response.Sender_Frame[6]),
						STP->STP_SLAVE_Response.Data, MAX_DATA_LENGHT);
				Calculate_CRC(STP);

				//CRC error
				STP->Error_Callback(STP->STP_SLAVE_Response);
			}





}




void Register_Write(int8_t Reg_Data[],uint8_t Register_Group){

	switch (Register_Group) {
					case REGISTER_GROUP_1:
						memcpy(Slave_Register.Register_Group_1,
								Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_2:
						memcpy(Slave_Register.Register_Group_2,
														Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_3:
						memcpy(Slave_Register.Register_Group_3,
														Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_4:
						memcpy(Slave_Register.Register_Group_4,
														Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_5:
						memcpy(Slave_Register.Register_Group_5,
														Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_6:
						memcpy(Slave_Register.Register_Group_6,
														Reg_Data, MAX_DATA_LENGHT);
						break;

					case REGISTER_GROUP_7:
						memcpy(Slave_Register.Register_Group_7,
														Reg_Data, MAX_DATA_LENGHT);
						break;
					case REGISTER_GROUP_8:
						memcpy(Slave_Register.Register_Group_8,
														Reg_Data, MAX_DATA_LENGHT);
						break;
					default:
						break;
					}
}

