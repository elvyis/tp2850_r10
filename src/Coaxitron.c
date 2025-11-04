// *****************************************************
// Company : Techpoint Inc
// $Date: 2013-11-14 
// $Log:  $
// ******************************************************

#include "inc\Config.h"
//#include "reg.h"
#include "inc\typedefs.h"
//#include "I2C.h"
#include "inc\main.h"
#include "inc\printf.h"
#include "inc\Coaxitron.h"
//#include "Table.c"

extern xdata	BYTE  tic_rs485;

#ifdef TP2801

xdata BYTE cam_ch = 0;

CODE PelcoD_cmd PelcoD_cmd_dataset[] = {
		{0x00,0x00,0x00,0x00},		//No command
		{0x88,0x00,0x00,0x00},		//Camera on
		{0x08,0x00,0x00,0x00},		//Camera off
		{0x90,0x00,0x00,0x00},		//Auto scan
		{0x10,0x00,0x00,0x00},		//Manual scan
		{0x04,0x00,0x00,0x00},		//IRS close
		{0x02,0x00,0x00,0x00},		//IRS open
		{0x01,0x00,0x00,0x00},		//Focus near
		{0x00,0x80,0x00,0x00},		//Focus far
		{0x00,0x40,0x00,0x00},		//Zoom wide
		{0x00,0x20,0x00,0x00},		//Zoom tele
		{0x00,0x10,0x00,0x00},		//down
		{0x00,0x08,0x00,0x00},		//up
		{0x00,0x04,0x00,0x00},		//Left
		{0x00,0x02,0x00,0x00},		//Right
		{0x00,0x00,0x00,0x40},		//Turbo speed
};


BYTE Get_485bits(BYTE dat, BYTE loc){

	dat >>=loc;
	dat &= 0x01;
//	Printf("\r\nGet_485bit = %02x",(WORD)dat);
	return dat;
	
}

void Tx_RS485_Byte(BYTE RS485dat){

	BYTE cnt;
	BYTE _RS485bit[10];		//start+data+stop
	BYTE *RS485bit = _RS485bit;
	
	*RS485bit = 0;	//Start bit
	RS485bit++;
	
	for(cnt=1;cnt<9;cnt++){

		*RS485bit = Get_485bits(RS485dat,cnt-1);
//		Printf("\r\n485bit = %02x",(WORD)*RS485bit);
		RS485bit++;
	}

	*RS485bit = 1; //stop bit
	cnt++;

	RS485bit -= 9;
//	RS485DE = 1;
		
	for(;cnt>0;cnt--){
//		tic_rs485 = 0;
//		while(tic_rs485 == 0);		//for 9600bps. 9600Hz timer interrupt
		RS485DE = 1;
		RS485DI = *RS485bit;
		RS485bit++;	
		RS485DE = 0;
		tic_rs485 = 0;
		while(tic_rs485 == 0);		//for 9600bps. 9600Hz timer interrupt
	}
//	RS485DE = 0;

}

BYTE Calc_PelcoD_chksum(BYTE *value, BYTE cnt){
	BYTE sum=0;

	for (;cnt>0;cnt--){
		sum += *(value++);
	}
	
	return sum;
	
}

void Set_CAM_addr(BYTE addr){

	cam_ch = addr;
}

void Send_PelcoD_commend(PelcoD_cmd *PD_cmd){
	PelcoD_format PD_dataset, *PD_dataptr;
	BYTE *dataset[7];
	BYTE *dataptr;
	BYTE i=0;

	PD_dataptr = &PD_dataset;
	dataptr = dataset[0];
	
	PD_dataptr->sync = 0xff;
	PD_dataptr->addr = cam_ch;
	PD_dataptr->cmd1 = PD_cmd->cmd1;
	PD_dataptr->cmd2 = PD_cmd->cmd2;
	PD_dataptr->data1 = PD_cmd->data1;
	PD_dataptr->data2 = PD_cmd->data2;

	dataptr = &PD_dataptr->sync; dataptr++;
	dataptr = &PD_dataptr->addr; dataptr++;
	dataptr = &PD_dataptr->cmd1; dataptr++;
	dataptr = &PD_dataptr->cmd2; dataptr++;
	dataptr = &PD_dataptr->data1; dataptr++;
	dataptr = &PD_dataptr->data2; dataptr++;

	PD_dataptr->chksum = Calc_PelcoD_chksum((dataptr-5),5);
	dataptr = &PD_dataptr->chksum; dataptr++;
	
	Printf("\r\ncam=%02x,cmd1=%02x,cmd2=%02x,data1=%02x,data2=%02x,chksum=%02x",(WORD)*(dataptr-6),(WORD)*(dataptr-5),(WORD)*(dataptr-4),(WORD)*(dataptr-3),(WORD)*(dataptr-2),(WORD)*(dataptr-1));

	for(i=7; i>0;i--){
		Tx_RS485_Byte(*(dataptr-i));
	}

}


PelcoD_cmd *PTZ_command(BYTE cmd){

	PelcoD_cmd *PD_cmd;

	PD_cmd = &PelcoD_cmd_dataset[cmd];

	return PD_cmd;
}



#endif
