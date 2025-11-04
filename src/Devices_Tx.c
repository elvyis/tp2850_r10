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
#include "inc\Device_Tx.h"
#include "inc\tp2802.h"


CODE_P	BYTE	*ptr_TVP7002;
CODE_P 	BYTE	*ptr_ADV7611_HDMIMAP;
CODE_P 	BYTE	*ptr_ADV7611_IO;

extern CODE BYTE TVP7002_1080P30_DataSet[];
extern CODE BYTE TVP7002_720P_DataSet[];
extern CODE BYTE TVP7002_480i_DataSet[];
extern CODE BYTE ADV7611_HDMIMAP_Dataset[];
extern CODE BYTE ADV7611IO__1080P30_Dataset[];
extern CODE BYTE ADV7611IO__1080P25_Dataset[];
extern CODE BYTE ADV7611IO__720P60_Dataset[];
extern CODE BYTE ADV7611IO__720P50_Dataset[];
extern CODE BYTE PO3100K__720PP30_Dataset[];

extern xdata BYTE ManVidRes;

void TVP7002_720P(){
	ptr_TVP7002 = TVP7002_720P_DataSet;	// Video ADC
	I2CDeviceSet( ptr_TVP7002 );
}

 void TVP7002_1080P30(){
	 ptr_TVP7002 = TVP7002_1080P30_DataSet; // Video ADC
	 I2CDeviceSet( ptr_TVP7002 );
 }


 void TVP7002_480i(){
	 ptr_TVP7002 = TVP7002_480i_DataSet; // Video ADC
	 I2CDeviceSet( ptr_TVP7002 );
 }

 void ADV7611_1080P30(){
 	ptr_ADV7611_IO = ADV7611IO__1080P30_Dataset;
	I2CDeviceSet( ptr_ADV7611_IO );
 	}
 void ADV7611_1080P25(){
 	ptr_ADV7611_IO = ADV7611IO__1080P25_Dataset;
	I2CDeviceSet( ptr_ADV7611_IO );
 	}
 void ADV7611_720P60(){
 	ptr_ADV7611_IO = ADV7611IO__720P60_Dataset;
	I2CDeviceSet( ptr_ADV7611_IO );
 	}
  void ADV7611_720P50(){
 	ptr_ADV7611_IO = ADV7611IO__720P50_Dataset;
	I2CDeviceSet( ptr_ADV7611_IO );
 	}
 void Set_ADV7611_CPMAP(BYTE Addr){
 	WriteI2C(Addr,0x6c,0x00);
 }

 void Set_ADV7611_HDMI(BYTE Addr){
 	WriteI2C(Addr,0x01,0x01);
 }

 void Set_ADV7611_SubAddr(BYTE DAddr,BYTE  CECAddr,BYTE INFOAddr,BYTE DPLLAddr, BYTE KSVAddr,BYTE EDIDAddr, BYTE HDMIAddr,BYTE CPAddr){
 	WriteI2C(DAddr,0xf4,CECAddr);		//CEC Map I2C address
 	WriteI2C(DAddr,0xf5,INFOAddr);		//InforFrame Map I2C address
 	WriteI2C(DAddr,0xf8,DPLLAddr);		//DPLL Map I2C address
 	WriteI2C(DAddr,0xf9,KSVAddr);		//KSV Map I2C address
 	WriteI2C(DAddr,0xfa,EDIDAddr);		//EDID Map I2C address
 	WriteI2C(DAddr,0xfb,HDMIAddr);		//HDMI Map I2C address
 	WriteI2C(DAddr,0xfd,CPAddr);		//CP Map I2C address
 }

 void SetInit_ADV7611(){				//HDMI RX
 	BYTE DAddr = 0x98;
	BYTE CECAddr = 0x80;
	BYTE INFOAddr = 0x7c;
	BYTE DPLLAddr = 0x4c;
	BYTE KSVAddr = 0x62;
	BYTE EDIDAddr = 0x6c;
	BYTE HDMIAddr = 0x68;
	BYTE CPAddr = 0x44;

	Set_ADV7611_SubAddr(DAddr,CECAddr,INFOAddr,DPLLAddr,KSVAddr,EDIDAddr,HDMIAddr,CPAddr);
	Set_ADV7611_CPMAP(CPAddr);
	
	ptr_ADV7611_HDMIMAP = ADV7611_HDMIMAP_Dataset;
	I2CDeviceSet( ptr_ADV7611_HDMIMAP );
 }
 
 void SetInit_CAM_PO3100K(){
 
	 BYTE	 *ptr_PO3100K;
 
	 ptr_PO3100K = PO3100K__720PP30_Dataset;
	 I2CDeviceSet( ptr_PO3100K );
	 
 }

void SetDevicesFor1080P30(){
	
	TVP7002_1080P30();
	ADV7611_1080P30();
//	Printf("\r\nWrite done to devices registers for 1080P30...");
}

void SetDevicesFor1080P25(){
	
	//TVP7002_1080P30();
	ADV7611_1080P25();
//	Printf("\r\nWrite done to devices registers for 1080P30...");
}
	
void SetDevicesFor720P60(){
	TVP7002_720P(); 				//Set 720P for TVP7002(Video ADC)
	ADV7611_720P60();
//	Printf("\r\nWrite done to devices registers for 720P60...");
}

void SetDevicesFor720P50(){
	TVP7002_720P(); 				//Set 720P for TVP7002(Video ADC)
	ADV7611_720P50();
//	Printf("\r\nWrite done to devices registers for 720P50...");
}

void Init_RegSet_For_Devices(){
	
	SetInit_ADV7611();

	if(ReadI2C(PO3100K,0x00) != 0xff)
		SetInit_CAM_PO3100K();
	
	if(ManVidRes == R1080P30)				
		SetDevicesFor1080P30();
	else if(ManVidRes == R1080P25)
		SetDevicesFor1080P25();
	else if(ManVidRes == R720P50)
		SetDevicesFor720P50();
	else
		SetDevicesFor720P60();
}

