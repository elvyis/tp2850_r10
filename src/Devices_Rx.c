// *****************************************************
// Company : Techpoint Inc
// $Date: 2013-09-17 
// $Log:  $
// ******************************************************

#include "inc\Config.h"
//#include "reg.h"
#include "inc\typedefs.h"
#include "inc\I2C.h"
#include "inc\main.h"
#include "inc\printf.h"
#include "inc\Device_Rx.h"
#include "inc\tp2802.h"

CODE_P	BYTE	*ptr_THS8200_720p;
CODE_P	BYTE	*ptr_THS8200_1080i;
CODE_P	BYTE	*ptr_THS8200_1080p30f;
CODE_P	BYTE	*ptr_SII9022;

extern CODE BYTE THS8200_720p_Dataset[];
extern CODE BYTE THS8200_1080i_Dataset[];
extern CODE BYTE THS8200_1080p30f_Dataset[];
extern CODE BYTE SII9022A_720p60f_Dataset[];
extern CODE BYTE SII9022A_1080p30f_Dataset[];
//extern CODE BYTE SII9022A_720p30f_Dataset[];
//extern CODE BYTE SII9022A_720p25f_Dataset[];
extern CODE BYTE SII9022A_720p50f_Dataset[];
extern CODE BYTE SII9022A_1080p25f_Dataset[];



extern xdata BYTE ManVidRes;

void Set_THS8200_720P(void)
{
	ptr_THS8200_720p = THS8200_720p_Dataset; // video DAC
	I2CDeviceSet( ptr_THS8200_720p);
//	Printf("\r\nDone to write THS8200 registers for 720P...");

}

 void Set_THS8200_1080i(void)
 {
 	ptr_THS8200_1080i = THS8200_1080i_Dataset; // video DAC
	I2CDeviceSet( ptr_THS8200_1080i);
//	Printf("\r\nDone to write THS8200 registers for 1080i...");
 }

 void Set_THS8200_1080P30F(void)
 {
 	ptr_THS8200_1080p30f = THS8200_1080p30f_Dataset; // video DAC
	I2CDeviceSet( ptr_THS8200_1080p30f);
//	Printf("\r\nDone to write THS8200 registers for 1080p 30f...");
 }

void SII9022A_TMDS_Off(BYTE Addr)
{
	WriteI2C(Addr,0x1a,(ReadI2C(Addr,0x1a)|0x10));
} 

 
void SII9022A_TMDS_On(BYTE Addr)
{
	WriteI2C(Addr,0x1a,(ReadI2C(Addr,0x1a)&0xef));
}

void Set_HDMI_Output(BYTE Addr){
	WriteI2C(Addr,0x1a,(ReadI2C(Addr,0x1a)|0x01));
}

 void Set_Init_SII9022(){
 	BYTE dat;
 	BYTE Addr = 0x72;

	WriteI2C(Addr,0xc7,0x00);		//Enable TPI mode
	dat = ReadI2C(Addr,0x1E);		
	WriteI2C(Addr,0x1E,(dat&0xfc));			//TPI enable active mode

	WriteI2C(Addr,0xBC,0x01);
	WriteI2C(Addr,0xBD,0x82);
	dat = ReadI2C(Addr,0xBE);
	WriteI2C(Addr,0xBE,(dat|0x01));			//Enalble source termination
	
	SII9022A_TMDS_Off(Addr);

	if(ManVidRes == R1080P30)				
		ptr_SII9022 = SII9022A_1080p30f_Dataset;
	else if(ManVidRes == R1080P25)
		ptr_SII9022 = SII9022A_1080p25f_Dataset;
	else if(ManVidRes == R720P25)
		ptr_SII9022 = SII9022A_720p25f_Dataset;
	else if(ManVidRes == R720P30)
		ptr_SII9022 = SII9022A_720p30f_Dataset;
	else if(ManVidRes == R720P50)
		ptr_SII9022 = SII9022A_720p50f_Dataset;
	else
		ptr_SII9022 = SII9022A_720p60f_Dataset;



	I2CDeviceSet( ptr_SII9022);
	
	Set_HDMI_Output(Addr);
	SII9022A_TMDS_On(Addr);
	
 }

 void SetDevicesFor1080P30(){
 	Set_THS8200_1080P30F();
 }

 void SeteDvicesFor720P60(){
 	Set_THS8200_720P();
 }

 void Init_RegSet_For_Devices(){
	Set_Init_SII9022();
 	if(ManVidRes == R1080P30)				
		SetDevicesFor1080P30();
	else
		SeteDvicesFor720P60();
}
