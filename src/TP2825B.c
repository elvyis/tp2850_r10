// *****************************************************
// Company : Techpoint Inc
// $Date: 2014-03-10 
// $Log:  $
// ******************************************************

#include "inc\Config.h"
#include "stdlib.h"
#include "inc\typedefs.h"
#include "inc\I2C.h"
#include "inc\main.h"
#include "inc\printf.h"
#include "inc\TP2825.h"

extern xdata BYTE ManVidRes;
extern xdata BYTE ManVidStd;
extern xdata BYTE ManSelCh;
extern xdata BYTE TVII2CAddress;

xdata BYTE	PTZ_buf[16];
xdata DWORD PTZ_pelco;
xdata BYTE crc;

#define CH_PER_CHIP 0x01
#define MAX_COUNT 	0xff

extern bit DetAutoRes;
extern bit DetAutoStd;
extern bit half_scaler;
extern bit en_tvi960p_H1400;
extern bit BT1120_out;
extern bit en_960P;
void delay(BYTE);
xdata	BYTE	state[CH_PER_CHIP];
xdata	BYTE	count[CH_PER_CHIP];
xdata	BYTE	mode[CH_PER_CHIP];
xdata	BYTE	std[CH_PER_CHIP];
IDATA	BYTE	egain[CH_PER_CHIP][4];
IDATA	BYTE	revision;
IDATA	BYTE	chip;
IDATA	BYTE	UTC_data;
xdata	BYTE	res;
bit sywd;

extern void CreateMDIN340VideoInstance(void);

enum
{
	TP2850 =0x50,
	TP2825B=0x25,
	TP2860 =0x60,
};      
//////////////////////////////////////////////////////
////
/////////////////////////////////////////////////////
CODE BYTE TP2860_DataSet[] = {
0x40, 0x00,
		0x42, 0x00,
		0x4e, 0x1d,
		0xf6, 0x00, //
		0xf7, 0x44,
		0xfa, 0x88,
		0x1b, 0x01, //
		0xfd, 0x80,
0x40, 0x08,
0x13, 0xef,
0x14, 0x41,
0x15, 0x02,
0x40, 0x00,
0xff, 0xff
};

//////////////////////////////////////////////////////
////
/////////////////////////////////////////////////////
CODE BYTE TP2825B_DataSet[] = {

		0x40, 0x00,
		0x35, 0x25,
		0x4c, 0x43,	//BT601 enable
		0x4e, 0x1d,
		0xf5, 0x10,
		0xfd, 0x80,
		0xf6, 0x00, //
		0xf7, 0x44,
		0xfa, 0x03,
		0x1b, 0x01, //
		0xff, 0xff
	};

//////////////////////////////////////////////////////
////
/////////////////////////////////////////////////////
#define MAX_FORMAT 
CODE BYTE TP2825B_FORMAT_DataSet[MAX_FORMAT][32] = {
//addr
	{0x02,0x0c,0x0d, 0x15,0x16,0x17,0x18,0x19,0x1a,0x1c,0x1d, 0x20,0x21,0x22,0x23, 0x25,0x26,0x27,0x28, 0x2b,0x2c,0x2d,0x2e, 0x30,0x31,0x32,0x33, 0x35,0x36,0x00,0x39,0x3a},
//1NTSC 960H
	{0xcf,0x13,0x50, 0x13,0x60,0xbc,0x12,0xf0,0x07,0x09,0x38, 0x40,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x70,0x2a,0x68,0x57, 0x62,0xbb,0x96,0xc0, 0x65,0xdc,0x00,0x04,0x32},
	//{0xcf,0x13,0x50, 0x03,0xd6,0xa0,0x12,0xf0,0x05,0x06,0xb4, 0x40,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x70,0x2a,0x4b,0x57, 0x62,0xbb,0x96,0xcb, 0x65,0xdc,0x00,0x04,0x32},
//2PAL 960H
	{0xcf,0x13,0x51, 0x13,0x76,0xbc,0x17,0x20,0x17,0x09,0x48, 0x48,0x84,0x37,0x3f, 0xff,0x05,0x2d,0x00, 0x70,0x2a,0x64,0x56, 0x7a,0x4a,0x4d,0xf0, 0x65,0xdc,0x00,0x04,0x32},	
	//{0xcf,0x13,0x51, 0x03,0xf0,0xa0,0x17,0x20,0x15,0x06,0xc0, 0x48,0x84,0x37,0x3f, 0xff,0x05,0x2d,0x00, 0x70,0x2a,0x4b,0x56, 0x7a,0x4a,0x4d,0xfb, 0x65,0xdc,0x00,0x04,0x32},	
//3TVI 720P30V2
	{0xca,0x13,0x50, 0x13,0x16,0x00,0x19,0xd0,0x25,0x06,0x72, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x25,0xdc,0x00,0x18,0x32},
//4TVI 720P25V2	
	{0xca,0x13,0x50, 0x13,0x16,0x00,0x19,0xd0,0x25,0x07,0xbc, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x25,0xdc,0x00,0x18,0x32},		
//5TVI 1080P30
	{0xc8,0x03,0x50, 0x03,0xd2,0x80,0x29,0x38,0x47,0x08,0x98, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x05,0xdc,0x00,0x1c,0x32},
//6TVI 1080P25
	{0xc8,0x03,0x50, 0x03,0xd2,0x80,0x29,0x38,0x47,0x0a,0x50, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x05,0xdc,0x00,0x1c,0x32},		
//7HDA 720P30
	{0xce,0x13,0x70, 0x13,0x16,0x00,0x19,0xd0,0x25,0x06,0x72, 0x40,0x46,0x36,0x3c, 0xfe,0x01,0x2d,0x00, 0x60,0x3a,0x5a,0x40, 0x9d,0xca,0x01,0xd0, 0x25,0xdc,0x00,0x18,0x32},		
//8HDA 720P25
	{0xce,0x13,0x71, 0x13,0x16,0x00,0x19,0xd0,0x25,0x07,0xbc, 0x40,0x46,0x36,0x3c, 0xfe,0x01,0x2d,0x00, 0x60,0x3a,0x5a,0x40, 0x9e,0x20,0x01,0x90, 0x25,0xdc,0x00,0x18,0x32},				
//9HDA 1080P30
	{0xcc,0x03,0x72, 0x01,0xf0,0x80,0x29,0x38,0x47,0x08,0x98, 0x38,0x46,0x36,0x3c, 0xfe,0x0d,0x2d,0x00, 0x60,0x3a,0x54,0x40, 0xa5,0x95,0xe0,0x60, 0x05,0xdc,0x00,0x1c,0x32},
//10HDA 1080P25
	{0xcc,0x03,0x73, 0x01,0xf0,0x80,0x29,0x38,0x47,0x0a,0x50, 0x3c,0x46,0x36,0x3c, 0xfe,0x0d,0x2d,0x00, 0x60,0x3a,0x54,0x40, 0xa5,0x86,0xfb,0x60, 0x05,0xdc,0x00,0x1c,0x32},
//11TVI 720P60
	{0xca,0x03,0x50, 0x13,0x16,0x00,0x19,0xd0,0x25,0x06,0x72, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x05,0xdc,0x00,0x1c,0x32},
//12TVI 720P50	
	{0xca,0x03,0x50, 0x13,0x16,0x00,0x19,0xd0,0x25,0x07,0xbc, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x05,0xdc,0x00,0x1c,0x32},			
//13TVI QHD30
	{0xc8,0x03,0x50, 0x23,0x1b,0x04,0x38,0xa0,0x5a,0x0c,0xe4, 0x50,0x84,0x36,0x3c, 0xff,0x05,0xad,0x00, 0x60,0x0a,0x58,0x70, 0x74,0x58,0x9f,0x60, 0x15,0xdc,0x40,0x40,0x12},
//14TVI QHD25	
	{0xc8,0x03,0x50, 0x23,0x1b,0x04,0x38,0xa0,0x5a,0x0f,0x78, 0x50,0x84,0x36,0x3c, 0xff,0x05,0xad,0x00, 0x60,0x0a,0x58,0x70, 0x74,0x58,0x9f,0x60, 0x15,0xdc,0x40,0x40,0x12},		
//15TVI 720P30V1
	{0xca,0x03,0x50, 0x13,0x16,0x00,0x19,0xd0,0x25,0x0c,0xe4, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x05,0xdc,0x00,0x1c,0x32},
//16TVI 720P25V1	
	{0xca,0x03,0x50, 0x13,0x16,0x00,0x19,0xd0,0x25,0x0f,0x78, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x05,0xdc,0x00,0x1c,0x32},
//17TVI 8MP15
	{0xc8,0x03,0x50, 0x13,0xbd,0x04,0x50,0x70,0x8f,0x11,0x30, 0x50,0x84,0x36,0x3c, 0xff,0x05,0xad,0x00, 0x60,0x0a,0x58,0x70, 0x74,0x59,0xbd,0x60, 0x18,0xca,0x40,0x40,0x12},
//18TVI 8MP12	
	{0xc8,0x03,0x50, 0x13,0xbd,0x04,0x50,0x70,0x8f,0x14,0xa0, 0x50,0x84,0x36,0x3c, 0xff,0x05,0xad,0x00, 0x60,0x0a,0x58,0x70, 0x74,0x59,0xbd,0x60, 0x18,0xca,0x40,0x40,0x12},
//19TVI 5MP20	
	{0xc8,0x03,0x50, 0x23,0x36,0x24,0x1a,0x98,0x7a,0x0e,0xa4, 0x50,0x84,0x36,0x3c, 0xff,0x05,0xad,0x00, 0x60,0x0a,0x54,0x70, 0x74,0xa7,0x18,0x50, 0x17,0xbc,0x40,0x40,0x12},
//20TVI 1080P60	
	{0xc8,0x03,0x50, 0x03,0xde,0x80,0x28,0x38,0x47,0x08,0x96, 0x50,0x84,0x36,0x3c, 0xff,0x05,0xad,0x00, 0x60,0x0a,0x40,0x70, 0x74,0x9b,0xa5,0xe0, 0x05,0xbc,0x40,0x40,0x12},
//21TVI 5M12.5
	{0xc8,0x03,0x50, 0x13,0x1f,0x20,0x34,0x98,0x7a,0x0b,0x9a, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x17,0xd0,0x00,0x1c,0x32},
//22HDA 5M12.5	
	{0xc8,0x03,0x50, 0x13,0x10,0x20,0x1a,0x98,0x7a,0x0b,0xb8, 0x38,0x46,0x36,0x3c, 0xfe,0x01,0x2d,0x00, 0x60,0x0a,0x44,0x40, 0x29,0x68,0x72,0xb0, 0x17,0xbc,0x00,0x1c,0x32},		
//23TVI 720P30HDR
	{0xca,0x13,0x50, 0x03,0xb2,0x00,0x60,0xd0,0x25,0x05,0xdc, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x28,0x70, 0x48,0xba,0x2e,0x90, 0x33,0x39,0x00,0x18,0x32},
//24TVI WXGA
//	{0xca,0x13,0x50, 0x03,0xf4,0x00,0xa0,0x20,0x35,0x06,0x90, 0x60,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x32,0x70, 0x48,0xbb,0x2e,0x90, 0x13,0xc0,0x00,0x18,0x32},
	{0xca,0x13,0x50, 0x03,0xee,0x00,0x90,0xd0,0x25,0x06,0x3c, 0x60,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x32,0x70, 0x4c,0x30,0xc3,0x00, 0x13,0xe8,0x00,0x18,0x32},				
//25TVI 1080P27.5
	{0xc8,0x03,0x50, 0x13,0x98,0x80,0x29,0x38,0x47,0x09,0x60, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x05,0xdc,0x00,0x1c,0x32},
//26TVI 1080P24
	{0xc8,0x03,0x50, 0x13,0x40,0x80,0x29,0x38,0x47,0x0a,0xbe, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x05,0xdc,0x00,0x1c,0x32},
//27TVI 1080P15
	{0xc8,0x03,0x50, 0x03,0xd2,0x80,0x29,0x38,0x47,0x08,0x98, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x25,0xdc,0x00,0x18,0x32},		
//28TVI 1280x320P60
	{0xca,0x03,0x50, 0x13,0x10,0x00,0x32,0x40,0x15,0x06,0x72, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xba,0x2e,0x90, 0x31,0x77,0x00,0x18,0x32},		
//29HDA 720P30 for TP2860
	{0xca,0x13,0x70, 0x13,0x16,0x00,0x19,0xd0,0x25,0x86,0x70, 0x38,0x46,0x36,0x3c, 0xfe,0x01,0xad,0x00, 0x60,0x3a,0x48,0x40, 0x4e,0xe5,0x00,0xf0, 0x25,0xdc,0x00,0x08,0x32},		
//30HDA 720P25 for TP2860
	{0xca,0x13,0x70, 0x13,0x16,0x00,0x19,0xd0,0x25,0x87,0xba, 0x38,0x46,0x36,0x3c, 0xfe,0x01,0xad,0x00, 0x60,0x3a,0x48,0x40, 0x4f,0x10,0x08,0x40, 0x25,0xdc,0x00,0x08,0x32},				
//31HDA 1080P30 for TP2860
	{0xc8,0x03,0x70, 0x01,0xf0,0x80,0x29,0x38,0x47,0x88,0x96, 0x38,0x46,0x36,0x3c, 0xfe,0x0d,0xad,0x00, 0x60,0x3a,0x48,0x40, 0x52,0xca,0xf0,0x20, 0x25,0xdc,0x00,0x0c,0x32},
//32HDA 1080P25 for TP2860
	{0xc8,0x03,0x70, 0x01,0xf0,0x80,0x29,0x38,0x47,0x8a,0x4e, 0x3c,0x46,0x36,0x3c, 0xfe,0x0d,0xad,0x00, 0x60,0x3a,0x48,0x40, 0x52,0xc3,0x7d,0xa0, 0x25,0xdc,0x00,0x0c,0x32},		
//33HDA 960P25 for TP2860
	{0xc8,0x03,0x70, 0x03,0xe6,0x00,0x89,0xc0,0x35,0x8a,0x8a, 0x40,0x46,0x36,0x3c, 0xfe,0x05,0xad,0x00, 0x60,0x3a,0x50,0x58, 0x52,0xd2,0x1c,0x00, 0x34,0x4c,0x00,0x0c,0x32},		
//34 NTSC 720H
	//{0xcf,0x13,0x50, 0x13,0x60,0xbc,0x12,0xf0,0x07,0x09,0x38, 0x40,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x70,0x2a,0x68,0x57, 0x62,0xbb,0x96,0xc0, 0x25,0xdc,0x00,0x04,0x32},
	{0xcf,0x13,0x50, 0x03,0xd6,0xa0,0x12,0xf0,0x05,0x06,0xb4, 0x40,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x70,0x2a,0x4b,0x57, 0x62,0xbb,0x96,0xcb, 0x65,0xdc,0x00,0x04,0x32},
//35 PAL 720H
	//{0xcf,0x13,0x51, 0x13,0x76,0xbc,0x17,0x20,0x17,0x09,0x48, 0x48,0x84,0x37,0x3f, 0xff,0x05,0x2d,0x00, 0x70,0x2a,0x64,0x56, 0x7a,0x4a,0x4d,0xf0, 0x25,0xdc,0x00,0x04,0x32},	
	{0xcf,0x13,0x51, 0x03,0xf0,0xa0,0x17,0x20,0x15,0x06,0xc0, 0x48,0x84,0x37,0x3f, 0xff,0x05,0x2d,0x00, 0x70,0x2a,0x4b,0x56, 0x7a,0x4a,0x4d,0xfb, 0x65,0xdc,0x00,0x04,0x32},	
//36 TVI 960P30
	{0xc8,0x03,0x50, 0x13,0x16,0x00,0xa0,0xc0,0x35,0x06,0x72, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x43,0x3b,0x79,0x90, 0x14,0x65,0x00,0x18,0x32},		//reg30-33 = 0x43_3B_79_90(29.2500M)
//37 TVI 960P25
	{0xc8,0x03,0x50, 0x13,0x16,0x00,0xa0,0xc0,0x35,0x07,0xbc, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xba,0x2e,0x90, 0x14,0x65,0x00,0x18,0x32},		//reg30-33 = 0x43_3B_79_90(29.2500M)		
//38 AHD 960P30 54M 1800x1000
	{0xce,0x03,0x76, 0x13,0x8f,0x00,0x23,0xd0,0x25,0x07,0x08, 0x60,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x3a,0x70,0x50, 0x7f,0x49,0xf4,0x90, 0x13,0xe8,0x00,0x88,0x32},	
//39 AHD 960P30 54M 1800x1000
	{0xca,0x13,0x50, 0x13,0x60,0x00,0x90,0xd0,0x25,0x87,0x06, 0x60,0x84,0x36,0x3c, 0xff,0x05,0xad,0x00, 0x60,0x3a,0x32,0x70, 0x40,0x62,0x4d,0xd3, 0x33,0xe8,0x00,0x18,0x32},		
//40 TVI 960P30 54M
	{0xc8,0x03,0x50, 0x13,0x18,0x00,0xa0,0xc0,0x35,0x06,0x74, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x45,0x55,0x55,0x53, 0x14,0x65,0x00,0x18,0x32},		//reg30-33 = 0x43_3B_79_90(29.2500M)
//41 TVI 960P25 54M
	{0xc8,0x03,0x50, 0x13,0x16,0x00,0xa0,0xc0,0x35,0x07,0x80, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x4b,0x00,0x00,0x00, 0x14,0x65,0x00,0x18,0x32},		//reg30-33 = 0x43_3B_79_90(29.2500M)		
//42 TVI 720P25HDR
	{0xca,0x13,0x50, 0x03,0xb2,0x00,0x60,0xd0,0x25,0x07,0x08, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x28,0x70, 0x48,0xba,0x2e,0x90, 0x33,0x39,0x00,0x18,0x32},
//43 AHD 960P30 1650x1125
	{0xcc,0x03,0x70, 0x12,0x12,0x00,0xa0,0xc0,0x35,0x06,0x72, 0x48,0x84,0x36,0x3c, 0xff,0x0d,0x2d,0x00, 0x60,0x0a,0x58,0x70, 0x9d,0xca,0x01,0xe0, 0x14,0x65,0x00,0x88,0x32},		//~17M
//44 AHD 960P30 1400x1125
	{0xc8,0x03,0x76, 0x03,0x5f,0x00,0x9c,0xc0,0x35,0x85,0x78, 0x14,0x84,0x36,0x3c, 0xff,0x0d,0x2d,0x00, 0x60,0x0a,0x1e,0x50, 0x29,0x01,0x76,0x80, 0x14,0x65,0x00,0x88,0x32},		//~15M	
//45 TVI 1080P50	
	{0xc8,0x03,0x50, 0x03,0xde,0x80,0x28,0x38,0x47,0x0a,0x48, 0x50,0x84,0x36,0x3c, 0xff,0x05,0xad,0x00, 0x60,0x0a,0x40,0x70, 0x74,0x9b,0xa5,0xe0, 0x05,0xbc,0x40,0x40,0x12},		
//46 TVI 960P30 1400X1125	
	{0xc8,0x03,0x50, 0x03,0x60,0x00,0xa0,0xc0,0x35,0x05,0x78, 0x18,0x84,0x36,0x3c, 0xff,0x07,0x2d,0x00, 0x60,0x1a,0x1a,0x70, 0x48,0xba,0x2e,0x90, 0x14,0x65,0x40,0x88,0x12},		
//47 TVI 1080P25_X3C
	{0xc8,0x03,0x50, 0x03,0xd2,0x80,0x29,0x38,0x47,0x09,0xab, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x0a,0x30,0x70, 0x48,0xbb,0x2e,0x90, 0x14,0xb5,0x00,0x1c,0x32},	
//48 TVI 1280x720P864M
	{0xca,0x13,0x50, 0x03,0xec,0x00,0xae,0xd0,0x25,0x06,0x40, 0x30,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x2a,0x30,0x70, 0x48,0xba,0x2e,0x90, 0x13,0x84,0x00,0x18,0x32},	
//49 TVI QHD275
	{0xc8,0x03,0x50, 0x33,0x48,0x00,0x36,0xa0,0x5a,0x0e,0x0e, 0x50,0x84,0x36,0x3c, 0xff,0x05,0xad,0x00, 0x60,0x2a,0x58,0x70, 0x74,0x58,0x9f,0x60, 0x15,0xdc,0x40,0x48,0x12},		
//50 TVI 480P20
	{0xce,0x03,0x76, 0x13,0xd8,0x00,0x14,0x00,0x28,0x09,0xc4, 0x50,0x84,0x36,0x3c, 0xff,0x05,0x2d,0x00, 0x60,0x2a,0x6c,0x70, 0x43,0xe4,0x25,0xb0, 0x52,0x1c,0x40,0x48,0x12},			
};
static void TP2825B_SYSCLK_54M(void)
{
 	if(TP2860 == chip)
	{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x12, 0x4e);
		tp28xx_byte_write(0x13, 0xef);						
		tp28xx_byte_write(0x14, 0x41);
		tp28xx_byte_write(0x15, 0x12);		
		tp28xx_byte_write(0x40, 0x00);		
		
	}
	else
	{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x11, 0x4e);
		tp28xx_byte_write(0x13, 0x04);
		tp28xx_byte_write(0x14, 0x04);
		tp28xx_byte_write(0x40, 0x00);
	}
}
static void TP2860_SYSCLK_111375K(void)
{
 	if(TP2860 == chip)
	{
		
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x12, 0x5f);
		tp28xx_byte_write(0x13, 0x0f);		
		tp28xx_byte_write(0x14, 0x41);
		tp28xx_byte_write(0x15, 0x02);		
		tp28xx_byte_write(0x40, 0x00);		
	}
} 
static void TP2825B_SYSCLK_945(void)
{
 	if(TP2860 == chip)
	{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x12, 0x5a);
		tp28xx_byte_write(0x13, 0xef);						
		tp28xx_byte_write(0x14, 0x41);
		tp28xx_byte_write(0x15, 0x12);		
		tp28xx_byte_write(0x40, 0x00);				
	}
	else
	{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x11, 0x5A);
		tp28xx_byte_write(0x13, 0x24);
		tp28xx_byte_write(0x14, 0x04);
		tp28xx_byte_write(0x40, 0x00);
	}
}

static void TP2825B_SYSCLK_864(void)
{
 	if(TP2860 == chip)
	{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x12, 0x7E);
		tp28xx_byte_write(0x13, 0x67);						
		tp28xx_byte_write(0x14, 0x41);
		tp28xx_byte_write(0x15, 0x02);		
		tp28xx_byte_write(0x40, 0x00);				
	}
	else
	{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x11, 0x5A);
		tp28xx_byte_write(0x13, 0x24);
		tp28xx_byte_write(0x14, 0x04);
		tp28xx_byte_write(0x40, 0x00);
	}
}
static void TP2860_SYSCLK_A720P(void)
{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x14, 0x50);
		tp28xx_byte_write(0x15, 0x09);		
		tp28xx_byte_write(0x40, 0x00);	
		tp28xx_byte_write(0xf6, 0x04);	
		tp28xx_byte_write(0xfa, 0x03);	
}
static void TP2860_SYSCLK_A1080P(void)
{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x14, 0x40);
		tp28xx_byte_write(0x15, 0x05);		
		tp28xx_byte_write(0x40, 0x00);	
		tp28xx_byte_write(0xf6, 0x04);	
		tp28xx_byte_write(0xfa, 0x03);		
}

static void TP2825B_SYSCLK_V2(void)
{
 	if(TP2860 == chip)
	{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x12, 0x54);
		tp28xx_byte_write(0x13, 0xef);					
		tp28xx_byte_write(0x14, 0x41);
		tp28xx_byte_write(0x15, 0x12);		
		tp28xx_byte_write(0x40, 0x00);
		tp28xx_byte_write(0xfa, 0x00);			
	}
	else
	{ 
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x11, 0x54);
		tp28xx_byte_write(0x13, 0x24);
		tp28xx_byte_write(0x14, 0x04);
		tp28xx_byte_write(0x40, 0x00);
	}
}
static void TP2825B_SYSCLK_V1(void)
{
 	if(TP2860 == chip)
	{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x12, 0x54);
		tp28xx_byte_write(0x13, 0xef);				
		tp28xx_byte_write(0x14, 0x41);
		tp28xx_byte_write(0x15, 0x02);		
		tp28xx_byte_write(0x40, 0x00);
		tp28xx_byte_write(0xfa, 0x00);			
	}
	else
	{	
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x11, 0x54);
		tp28xx_byte_write(0x13, 0x04);
		tp28xx_byte_write(0x14, 0x04);	
		tp28xx_byte_write(0x40, 0x00);
	}		
}
static void TP2825B_SYSCLK_V3(void)
{
	BYTE tmp;
	if(TP2860 == chip)
	{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x14, 0x00);
		tp28xx_byte_write(0x15, 0x01);		
		tp28xx_byte_write(0x40, 0x00);
		tp28xx_byte_write(0xfa, 0x00);	
	}
	else
	{
		tp28xx_byte_write(0x40, 0x08);
		tp28xx_byte_write(0x11, 0x54);
		tp28xx_byte_write(0x13, 0x04);
		tp28xx_byte_write(0x14, 0x73);	
		tp28xx_byte_write(0x40, 0x00);
	}
		if(!BT1120_out)
		{
			tmp = tp28xx_byte_read(0x35);
			tmp |= 0x40;
			tp28xx_byte_write(0x35, tmp);	
		}		
}
void Set_VidRes(BYTE Res, BYTE Std){

//	BYTE *ptr_Std;
	BYTE ptz;
	BYTE i, index, tmp;
	
	half_scaler=0;
	ptz = PTZ_TVI;
	index = 0xff;
	if( TP2860 == chip )
	{
		tp28xx_byte_write(0x06, 0x12); 
	}
	if(STD_HDA == Std)
	{
		ptz = PTZ_HDA_1;	
		switch(Res){
				
				case TP2802_1080P30:

							 if(en_960P)
							 {
//								 index = 43;
								 index = 44;
								 ptz = PTZ_960P30_AHD;
									TP2825B_SYSCLK_945();	
									tp28xx_byte_write(0x05, 0x01);
								  tp28xx_byte_write(0x0e, 0x12);
							 }
							else
							{
//									if(TP2860 == chip )
//									{
//										{index = 31; ptz = PTZ_HDA_1;}
//										TP2860_SYSCLK_A1080P();
//									}
//									else
									{
										{index = 9; }
										TP2825B_SYSCLK_V1();							 
									}																			
						 }

					//ManVidRes = TP2802_1080P30;
					break;
					
				case TP2802_1080P25:

							 if(en_960P)
							 {
							 }
							else
							{
//									if(TP2860 == chip )
//									{
//										{index = 32; ptz = PTZ_HDA_1;}
//										TP2860_SYSCLK_A1080P();
//									}
//									else
									{
										{index = 10; }
										TP2825B_SYSCLK_V1();							 
									}																			
						 }

					//ManVidRes = TP2802_1080P30;
					break;
						
				case TP2802_720P30V2:
//						 if(TP2860 == chip)
//						 {
//							{index = 29; ptz = PTZ_HDA_2;}
//							TP2860_SYSCLK_A720P();							 
//						 }
//						 else
						 {
							{index = 7;}
							TP2825B_SYSCLK_V2();							 
						 }
					//ManVidRes = TP2802_720P30;
					break;			
				case TP2802_720P25V2:
//						 if(TP2860 == chip)
//						 {
//							{index = 30; ptz = PTZ_HDA_2;}
//							TP2860_SYSCLK_A720P();							 
//						 }
//						 else
						 {
							{index = 8;}
							TP2825B_SYSCLK_V2();							 
						 }
					//ManVidRes = TP2802_720P30;
					break;
				case TP2802_5M12:
					{index = 22;}
					TP2825B_SYSCLK_V1();
					//ManVidRes = TP2802_1080P30;
					break;
				case TP2802_WXGA:
						 if( TP2860 == chip )
						 {

									{index = 38; ptz = PTZ_HDA_1;}
								tp28xx_byte_write(0x05, 0xfd);
								  tp28xx_byte_write(0x0e, 0x16);
						 }					
						else 
						{
								index = 38;
						}
					  TP2825B_SYSCLK_54M();
					
					//ManVidRes = TP2802_1080P30;
					break;						
			}		
	}
	else if(STD_HDC == Std || STD_HDC_DEFAULT == Std)
	{
	}
	else
	{
			switch(Res){
				
				case TP2802_1080P30:
						 if(en_960P)
						 {
							 if(TP2860 == chip)
							 {
								 if(en_tvi960p_H1400)
								 {
									index = 46;
									TP2825B_SYSCLK_945();	
								 }
								 else
								 {
									index = 36;
									TP2860_SYSCLK_111375K();
								 }
							 }
							 else
							 {
							 
								 if(en_tvi960p_H1400)
								 {
									index = 46;
									TP2825B_SYSCLK_945();	
								 }
								 else
								 {
								 	index = 40;
									TP2825B_SYSCLK_54M();	
								 }
							 }
						 }
						else
						{
							index = 5;
							TP2825B_SYSCLK_V1();
						}
					//ManVidRes = TP2802_1080P30;
					break;

				case TP2802_1080P_X3C:

							index = 47;
							TP2825B_SYSCLK_V1();

					//ManVidRes = TP2802_1080P30;
					break;
					
				case TP2802_1080P25:
						 if(en_960P)
						 {
							 if(TP2860 == chip)
							 {
								 index = 37;
									TP2860_SYSCLK_111375K();
							 }
							 else
							 {
								 index = 41;
									TP2825B_SYSCLK_54M();								 
							 }			 
						 }
						else
						{
							index = 6;
							TP2825B_SYSCLK_V1();
						}
					//ManVidRes = TP2802_1080P25;
					break;
						
				case TP2802_720P30V2:

							index = 3;
				  ptz = PTZ_TVI_720P;
					TP2825B_SYSCLK_V2();
					//ManVidRes = TP2802_720P30;
					break;
				
				case TP2802_720P25V2:
							index = 4;
				  ptz = PTZ_TVI_720P;
					TP2825B_SYSCLK_V2();
					//ManVidRes = TP2802_720P30;
					break;	
				
				case TP2802_720P60:
							index = 11;
					TP2825B_SYSCLK_V1();
					//ManVidRes = TP2802_720P30;
					break;
				
				case TP2802_720P50:
							index = 12;
					TP2825B_SYSCLK_V1();
					//ManVidRes = TP2802_720P30;

					break;
				case TP2802_QHD30:
							index = 13;
					TP2825B_SYSCLK_V3();
				half_scaler=1;
					//ManVidRes = TP2802_1080P30;
					break;			
				
				case TP2802_QHD25:
							index = 14;
					TP2825B_SYSCLK_V3();
								half_scaler=1;
					//ManVidRes = TP2802_1080P30;
					break;		

				case TP2802_QHD275:
							index = 49;
					TP2825B_SYSCLK_V3();
								half_scaler=1;
					//ManVidRes = TP2802_1080P30;
					break;					

				case TP2802_720P30:
					index = 15;
					TP2825B_SYSCLK_V1();
					//ManVidRes = TP2802_720P30;
					break;

				case TP2802_720P25:
				index = 16;
					TP2825B_SYSCLK_V1();
					//ManVidRes = TP2802_720P30;
					break;
#if 0
				case TP2802_8M15:
					index = 17;
					TP2825B_SYSCLK_V3();
					//ManVidRes = TP2802_1080P30;
					break;

				case TP2802_8M12:
					index = 18;
					TP2825B_SYSCLK_V3();
					//ManVidRes = TP2802_1080P30;
					break;
				
				case TP2802_5M20:
					index = 19;
					TP2825B_SYSCLK_V3();
					//ManVidRes = TP2802_1080P30;
					break;	
#endif				
				case TP2802_1080P60:
					index = 20;
					TP2825B_SYSCLK_V3();
					//ManVidRes = TP2802_1080P30;
					break;		
				case TP2802_1080P50:
					index = 45;
					TP2825B_SYSCLK_V3();
					//ManVidRes = TP2802_1080P30;
					break;									
				case TP2802_NTSC:

					ptz = PTZ_CVBS;
					TP2825B_SYSCLK_V2();
						 if(TP2860 == chip)
						 {
							index = 34; tp28xx_byte_write(0x06, 0x32); tp28xx_byte_write(0xfa, 0x04); 
						 }
						 else
						 {
							index = 1;
						 }					
					break;

				case TP2802_PAL:

					ptz = PTZ_CVBS;
					TP2825B_SYSCLK_V2();
						 if(TP2860 == chip)
						 {
							index = 35; tp28xx_byte_write(0x06, 0x32); tp28xx_byte_write(0xfa, 0x04); 
						 }
						 else
						 {
							index = 2;
						 }					
					break;
#if 0						 
				case TP2802_5M12:
					index = 21;
					TP2825B_SYSCLK_V1();
					//ManVidRes = TP2802_1080P30;
					break;	
#endif				
				case TP2802_720P30HDR:
					index = 23;
				  ptz = PTZ_TVI_720P;
					TP2825B_SYSCLK_V2();
					//ManVidRes = TP2802_1080P30;
					break;	
				case TP2802_720P25HDR:
					index = 42;
				  ptz = PTZ_TVI_720P;
					TP2825B_SYSCLK_V2();
					//ManVidRes = TP2802_1080P30;
					break;					
				case TP2802_WXGA:
					index = 24;
					TP2825B_SYSCLK_945();
					tp28xx_byte_write(0x0b, 0x80);
					//ManVidRes = TP2802_1080P30;
					break;					
				case TP2802_720P864M:
					index = 48;
					TP2825B_SYSCLK_864();
					tp28xx_byte_write(0x0b, 0x80);
					//ManVidRes = TP2802_1080P30;
					break;	
					
				case TP2802_1080P27:
							index = 25;
					TP2825B_SYSCLK_V1();
					//ManVidRes = TP2802_1080P30;
					break;
					
				case TP2802_1080P24:

							index = 26;;
					
					TP2825B_SYSCLK_V1();
					//ManVidRes = TP2802_1080P30;
					break;	
				
				case TP2802_1080P15:

							index = 27;;
					ptz = PTZ_TVI_720P;
					TP2825B_SYSCLK_V2();
					//ManVidRes = TP2802_1080P30;
					break;	
#if 0				
				case TP2802_1280x320P60:

							index = 28;;
					ptz = PTZ_TVI_720P;
					TP2825B_SYSCLK_V2();
					//ManVidRes = TP2802_1080P30;
					break;
#endif
				case TP2802_480P20:

							index = 50;;
					ptz = PTZ_TVI_720P;
				//	tp28xx_byte_write(0x13, 0x00);	
				//	tp28xx_byte_write(0x14, 0x00);					
					tp28xx_byte_write(0x05, 0x2D);	
					tp28xx_byte_write(0x0E, 0x05);					
					TP2825B_SYSCLK_54M();
					tp28xx_byte_write(0xfa, 0x04);					
								half_scaler=1;				
					//ManVidRes = TP2802_1080P30;
					break;
				
				case TP2802_960P25:
						 if(TP2860 == chip)
						 {
							{index = 33; ptz = PTZ_HDA_1;}
							TP2860_SYSCLK_A1080P();						 
						 }
						 else
						 {

						 }
					break;		
			
			}		
	}
	if(index != 0xff)
	{
			for(i = 0; i < 32; i++)
			{
				tp28xx_byte_write(TP2825B_FORMAT_DataSet[0][i],TP2825B_FORMAT_DataSet[index][i]);
			}
			
			if(BT1120_out)
			{
				tmp = tp28xx_byte_read(0x02);
				tmp &= 0x7f;
				tp28xx_byte_write(0x02, tmp);	
			}
			TP2825B_SetTX(ptz);
      TP2825B_SetRX(ptz); 
			
			tmp = tp28xx_byte_read(0x06);
			tmp |= 0x80;
			tp28xx_byte_write(0x06, tmp);				
			
			Printf("\r\nset video %02x std %02x...", (WORD)Res,(WORD)Std);
	}
}

static void TP2825B_reset_default()
{
  unsigned char tmp;
	
	TP2825B_SYSCLK_V1();
	tp28xx_byte_write(0x35, 0x05);
  tp28xx_byte_write(0x07, 0xc0);
	tp28xx_byte_write(0x0b, 0xc0);
	tp28xx_byte_write(0x26, 0x04);
    tmp = tp28xx_byte_read(0x06);
    tmp &= 0xfb;
    tp28xx_byte_write(0x06, tmp);	
	
	if(TP2860 == chip)
	{		
		tp28xx_byte_write(0xf6, 0x00);
		tp28xx_byte_write(0xfa, 0x88);
	}
	if(0==MD0_2) 
	{
		//half_scaler=1;
		//Printf("\r\nHalf mode enable");
	}
	else
	{
		//half_scaler=0;
	}
}
//////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////
static void TP2850EVK_Switch_Vin(void)
{
	unsigned char tmp;

		tmp = tp28xx_byte_read(0x41);
		tmp &= 0x07;
	if (0x00 == ManSelCh)
	{
			tmp = 0x06;
	}	
	else if(0x02 == ManSelCh)
	{
			tmp = 0x03;
	}	
	else if(0x01 == ManSelCh)
	{
			tmp = 0x02;
	}
	else 
	{			
			if(0x06 == tmp) tmp = 0x02;
			else if(0x02 == tmp) tmp = 0x03;
			else if (0x03 == tmp) tmp = 0x06;
			else tmp = 0x02;
	}

		tp28xx_byte_write(0x41, tmp);
	
				if(0x06 == tmp)
				{
						tmp = tp28xx_byte_read(0xf0); //differential 1 with inside PTZ1
						tmp &= 0xcf;
						tmp |= 0x10;
						tp28xx_byte_write(0xf0, tmp);																	
					tp28xx_byte_write(0x38, 0x4e); //differential
					tp28xx_byte_write(0x3d, 0x40);
					//tp28xx_byte_write(0x3e, 0x80);
				}
				else if(0x02 == tmp)
				{
						tmp = tp28xx_byte_read(0xf0); //Vin 3 with inside PTZ2
						tmp &= 0xcf;
						tmp |= 0x20;
						tp28xx_byte_write(0xf0, tmp);																	
					tp28xx_byte_write(0x38, 0x00); //single-end
					tp28xx_byte_write(0x3d, 0x60);
					//tp28xx_byte_write(0x3e, 0x80);
				}				
				else
				{
					tp28xx_byte_write(0x38, 0x00);	//single-end
					tp28xx_byte_write(0x3d, 0x60);
					//tp28xx_byte_write(0x3e, 0x00);
				}	
}
/////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
static void TP2825BEVK_Switch_Vin(void)
{
	unsigned char tmp;

		tmp = tp28xx_byte_read(0x41);
		tmp &= 0x07;
	if (0x00 == ManSelCh)
	{
			tmp = 0x04;
	}	
	else if(0x02 == ManSelCh)
	{
			tmp = 0x06;
	}	
	else if(0x01 == ManSelCh)
	{
			tmp = 0x07;
	}
	else 
	{			
			if(0x06 == tmp) tmp = 0x07;
			else if(0x07 == tmp) tmp = 0x04;
			else if (0x04 == tmp) tmp = 0x06;
			else tmp = 0x04;
	}

		tp28xx_byte_write(0x41, tmp);
	
				if(0x06 == tmp)
				{
						tmp = tp28xx_byte_read(0xf0); //differential 1 with inside PTZ1
						tmp &= 0xcf;
						tmp |= 0x10;
						tp28xx_byte_write(0xf0, tmp);																	
					tp28xx_byte_write(0x38, 0x4e); //differential
					tp28xx_byte_write(0x3d, 0x40);
					//tp28xx_byte_write(0x3e, 0x80);
				}
				else if(0x07 == tmp)
				{
						tmp = tp28xx_byte_read(0xf0); //differential 2 with inside PTZ2
						tmp &= 0xcf;
						tmp |= 0x20;
						tp28xx_byte_write(0xf0, tmp);																	
					tp28xx_byte_write(0x38, 0x4e); //differential
					tp28xx_byte_write(0x3d, 0x40);
					//tp28xx_byte_write(0x3e, 0x80);
				}				
				else
				{
					if(0x04 == tmp) //vin5 with inside PTZ2
					{
						tmp = tp28xx_byte_read(0xf0);
						tmp &= 0xcf;
						tmp |= 0x20;
						tp28xx_byte_write(0xf0, tmp);
					}
					tp28xx_byte_write(0x38, 0x40);	//single-end
					tp28xx_byte_write(0x3d, 0x60);
					//tp28xx_byte_write(0x3e, 0x00);
				}	
}
//////////////////////////////////////////////////////////////////////////////
void EQ_Detect(){

	
	BYTE cvstd,status,i;
	BYTE gain, tmp;

 
            //for(i = 0; i < CH_PER_CHIP; i++)//scan four inputs:
						i = 0;
            {
                    //SetRegPage(i);
                    status = tp28xx_byte_read(0x01);

                    //state machine for video checking
                    if(status & FLAG_LOSS)
                    {

                            if(VIDEO_UNPLUG == state[i])
                            {
                                if(count[i] < MAX_COUNT) count[i]++;
																	if(TP2825B == chip)
																		TP2825BEVK_Switch_Vin();
																	else
																		TP2850EVK_Switch_Vin();
                            }
                            else
                            {
                                state[i] = VIDEO_UNPLUG;
                                count[i] = 0;
                                std[i] = INVALID_FORMAT;
                                TP2825B_reset_default();
																//Set_VidRes(mode[i], STD_TVI);
                                Printf("video loss ch%02x \r\n", (WORD)i);
                            }

                    }
                    else
                    {
                        if( FLAG_LOCKED == (status & FLAG_LOCKED) ) //video locked
                        {
                            if(VIDEO_LOCKED == state[i])
                            {
                                if(count[i] < MAX_COUNT) count[i]++;
                            }
														else if(VIDEO_UNPLUG == state[i])
														{
																state[i] = VIDEO_IN;
																count[i] = 0;
														}
														else if(mode[i] != INVALID_FORMAT)
														{

                                state[i] = VIDEO_LOCKED;
                                count[i] = 0;
														}		
/*														
                            else
                            {
                                state[i] = VIDEO_LOCKED;
                                count[i] = 0;
                                Printf("video locked ch%02x \r\n", (WORD)i);
                            }
*/
                        }
                        else  //video in but unlocked
                        {
                            if(VIDEO_UNPLUG == state[i])
                            {
                                state[i] = VIDEO_IN; count[i] = 0;
                                Printf("video in ch%02x \r\n", (WORD)i);
                            }
                            else if(VIDEO_LOCKED == state[i])
                            {
                                state[i] = VIDEO_UNLOCK; count[i] = 0;
                                Printf("video unstable ch%02x \r\n", (WORD)i);
                            }
                            else
                            {
                                    if(count[i] < MAX_COUNT) count[i]++;
                                    if(VIDEO_UNLOCK == state[i] && count[i] > 2)
                                    {
                                        state[i] = VIDEO_IN; count[i] = 0;
                                        TP2825B_reset_default();
                                        Printf("video unlocked ch%02x \r\n", (WORD)i);
                                    }
                            }
                        }

                    }

            		if( VIDEO_IN == state[i])
            		{
												cvstd = tp28xx_byte_read(0x03);
												Printf("video format %2x detected ch%02x \r\n", (WORD)(cvstd), (WORD)i );
												sywd = cvstd & 0x08;
												cvstd &= 0x07;
												std[i] = STD_TVI;
												//if(INVALID_FORMAT == cvstd)
												if( cvstd > 0x02)
												{
                                 tp28xx_byte_write(0x2f, 0x09);
                                 tmp = tp28xx_byte_read(0x04);
																 Printf("extend format %2x detected ch%02x \r\n", (WORD)(tmp), (WORD)i );
                                    if(0x4e == tmp)
                                    {

                                           mode[i] = TP2802_3M18;
                                    }	
                                    else if(0x38 == tmp)
                                    {

                                           mode[i] = TP2802_QHD275;
                                    }				
                                    else if(0xd6 == tmp)
                                    {

                                           mode[i] = TP2802_480P20;
                                    }																				
                                    else if(0x4d == tmp)
                                    {
                                        if(count[i] & 1)
                                        {
                                            mode[i] = TP2802_1080P_X3C;
                                            //tp2802_set_video_mode(iChip, wdi-> mode[i], i,  wdi-> std[i]);
                                        }
                                        else
                                        {
                                           mode[i] = TP2802_WXGA;
						}
                                    }																																		
                                    else if(0x5d == tmp)
                                    {
                                        if(count[i] & 1)
                                        {
                                            mode[i] = TP2802_5M12;
                                            std[i] = STD_HDA;
                                            //tp2802_set_video_mode(iChip, wdi-> mode[i], i,  wdi-> std[i]);
                                        }
                                        else
                                        {
                                            mode[i] = TP2802_720P30HDR;
																						//std[i] = STD_TVI;
                                            //tp2802_set_video_mode(iChip, wdi-> mode[i], i, wdi-> std[i]);
                                        }
                                    }
                                    else if(0x70 == tmp)
                                    {

                                           mode[i] = TP2802_720P25HDR;
                                    }																					
                                    else if(0x5c == tmp)
                                    {
                                        mode[i] = TP2802_5M12;
                                    }
/*
                                    else if(0x75 == tmp)
                                    {
                                        wdi-> mode[i] = TP2802_6M10;
                                        tp2802_set_video_mode(iChip, wdi-> mode[i], i, wdi-> std[i]);
                                    }
                                    //else if((tmp > 0x34) && (tmp < 0x40))
                                    else if(0x38 == tmp)
                                    {
                                        wdi-> mode[i] = TP2802_QXGA25; //current only HDA
                                        wdi-> std[i] = STD_HDA;
                                        tp2802_set_video_mode(iChip, wdi-> mode[i], i, wdi-> std[i]);
                                    }
                                    //else if((tmp > 0x28) && (tmp < 0x34))
                                    else if(0x2e == tmp)
                                    {
                                        wdi-> mode[i] = TP2802_QXGA30; //current only HDA
                                        wdi-> std[i] = STD_HDA;
                                        tp2802_set_video_mode(iChip, wdi-> mode[i], i, wdi-> std[i]);
                                    }
*/	
                                    else if(0x3a == tmp)  // invalid for TP2853C
                                    {
                                        mode[i] = TP2802_5M20;
                                    }
																		
                                    else if(0x89 == tmp)
                                    {
                                        mode[i] = TP2802_1080P15;
                                    }
																		
                                    else if(0x22 == tmp)
                                    {
                                        mode[i] = TP2802_1080P60;
                                    }
                                    else if(0x29 == tmp)
                                    {
                                        mode[i] = TP2802_1080P50;
                                    }																			
                                    else if(0x4a == tmp)
                                    {
                                        mode[i] = TP2802_1080P27;
                                    }																				
                                    else if(0x55 == tmp)
                                    {
                                        if(count[i] & 1)
                                        {
                                            mode[i] = TP2802_720P864M;
                                            //tp2802_set_video_mode(iChip, wdi-> mode[i], i,  wdi-> std[i]);
                                        }
                                        else
                                        {
                                          mode[i] = TP2802_1080P24;
						}                                    
                                        
                                    }						
	                                  else if(0x94 == tmp)
                                    {
                                        mode[i] = TP2802_PAL;
                                    }																				
                                    else if(0x93 == tmp)
                                    {
                                        mode[i] = TP2802_NTSC;
                                    }			
                                    else if(0x54 == tmp)
                                    {
                                        mode[i] = TP2802_960P25;
                                    }	
                                    else if(0x55 == tmp)
                                    {
                                        mode[i] = TP2802_720P864M;
                                    }										
																		else if(0x52 == tmp) 
																		{
																						mode[i] = TP2802_1080P25;
																						if(count[i] & 0x01)
																						{
																								//mode[i] = TP2802_WXGA; 
																							  //mode[i] = TP2802_8M12;
																						}	
																		}	
																		else if(0x67 == tmp)
																		{
																				if(count[i] & 0x01)
																					mode[i] = TP2802_1280x320P60;
																				else
																					mode[i] = TP2802_720P30V2;
																		}
																		else if(0x7b == tmp)
																		{
																				mode[i] = TP2802_720P25V2;
																		}																							
																		//Set_VidRes(mode[i], STD_TVI);
												}
/*												
												else if(TP2802_SD == cvstd)
												{
                                         
																if(count[i] & 0x01)
																{
 
																		mode[i] = TP2802_PAL;
																}
																else
																{
																		mode[i] = TP2802_NTSC;

																}
																//Set_VidRes(mode[i], STD_TVI);
                                                            
                        }
*/	
												
												else
												{
																mode[i] = cvstd;
								
																if(DetAutoStd)
																{
																
																		if( TP2802_1080P30 == cvstd )
																		{
																			if(en_960P)
																			{
																				if(!en_tvi960p_H1400)
																					std[i]= std[i] = STD_HDA;
																			}
/*																			
																						if(count[i] & 0x01)
																						{
																								mode[i] = TP2802_8M15;
																						}
*/
																		}
																		else if( TP2802_720P60 == cvstd )
																		{
																						if(count[i] & 0x01)
																						{
																								mode[i] = TP2802_QHD30;
																						}
																		}
																		else if( TP2802_720P50 == cvstd )
																		{
																						if(count[i] & 0x01)
																						{
																								mode[i] = TP2802_QHD25;
																						}	
																		}
																}																
																//Set_VidRes(mode[i], STD_TVI);
												}
												
												Set_VidRes(mode[i], std[i]);

                  }
#define EQ_COUNT 10
                        if( VIDEO_LOCKED == state[i]) //check signal lock
                        {
                            if(0 == count[i])
                            {
															Printf("count=0 \r\n");
															//count[i]++;
															
															
															
                            				tmp = tp28xx_byte_read(0x26);
                            				//tmp &= 0xfc;
                            				tmp |= 0x01;
                            				tp28xx_byte_write(0x26, tmp); 
                                    if( (TP2802_720P30V2 == mode[i]) || (TP2802_720P25V2 == mode[i]) )
                                    {
                                                            if( !(0x08 & tp28xx_byte_read(0x03)))
                                                            {

                                                                Printf("720P V1 Detected ch%02x \r\n", (WORD)i);
                                                                if(TP2802_720P30V2 == mode[i]) //to speed the switching
                                                                {
                                                                    mode[i] = TP2802_720P30;
                                                                }
                                                                else if (TP2802_720P25V2 == mode[i])
                                                                {
                                                                    mode[i] = TP2802_720P25;
                                                                }
																																Set_VidRes(mode[i], STD_TVI);

                                                            }															

                                     }



																
																if(ManVidRes != mode[i])
																{
/*																	
																			if(mode[i] > TP2802_NTSC && ManVidRes == TP2802_1080P30)
																			{
																			}
																			else if(mode[i] < TP2802_720P25 && ManVidRes == TP2802_1080P30)
																			{
																			}
																			else if(mode[i] > TP2802_1080P30 && mode[i] < TP2802_PAL && ManVidRes == TP2802_720P30)
																			{
																			}
																			else
*/																	
																			{
																				ManVidRes = mode[i];
																				CreateMDIN340VideoInstance();
																			}
																}

                            }
                            else if(1 == count[i])
                            {
															//count[i]++;
															Printf("count=1 \r\n");
															tmp = tp28xx_byte_read(0x01);

															if(TP2802_PAL == mode[i] || TP2802_NTSC == mode[i])
															{
																//do nothing
															}
															else if(0x60 == (tmp&0x64) && DetAutoStd )
															{
										
//																UTC_data = tp28xx_byte_read(0x94);
																Printf("UTC set\r\n");
//                                        if     (0xff == UTC_data)                {std[i] = STD_HDC;}
//                                        else if(0x00 == UTC_data)                std[i] = STD_HDC_DEFAULT;
//                                        else                                	 {std[i] = STD_HDA;}
																if(std[i] == STD_TVI)
																{
																     std[i] = STD_HDA;
																	   Set_VidRes(mode[i], std[i]);
																}
																  //TP2825B_SetRX(0x02);
															}
															else
															{
																if(std[i] == STD_HDA && DetAutoStd  )
																{
																     std[i] = STD_TVI;
																	   Set_VidRes(mode[i], std[i]);
																}																
																//TP2825B_SetRX(0); //TVI 
															}
															
															if(half_scaler) //down scaler output
																{
																	tmp = tp28xx_byte_read(0x35);
																	tmp |= 0x40;
																	tp28xx_byte_write(0x35, tmp);
																}
                            }
                            else if( count[i] < EQ_COUNT-3)
                            {

																egain[i][3] = egain[i][2];
																egain[i][2] = egain[i][1];
																egain[i][1] = egain[i][0];
																gain = tp28xx_byte_read(0x03);
																//egain[i][EQ_COUNT - count[i]] = gain&0xf0;
																egain[i][0] = gain&0xf0;
																Printf("Egain=0x%02x ch%02x\r\n", (WORD)gain, (WORD)i);

                            }
                            else if( EQ_COUNT == count[i])
                            {
																count[i]--;

																egain[i][3] = egain[i][2];
																egain[i][2] = egain[i][1];
																egain[i][1] = egain[i][0];

																gain = tp28xx_byte_read(0x03);
																egain[i][0] = gain&0xf0;
																if(abs(egain[i][3] - egain[i][0])< 0x20 && abs(egain[i][2] - egain[i][0])< 0x20 && abs(egain[i][1] - egain[i][0])< 0x20 )
																{

																		count[i]++;

																				tmp = tp28xx_byte_read(0x03);
																				Printf("result Egain=0x%02x ch%02x\r\n", (WORD)tmp, (WORD)i);

																}
                            }

                            else if(EQ_COUNT+1 == count[i])
                            {
																tp28xx_byte_write(0x2f, 00);
            										gain = tp28xx_byte_read(0x04);

                        							if( STD_TVI !=  std[i] )
                        							{
                                						//tp28xx_byte_write(iChip, 0x07, 0x80|(gain>>2));  // manual mode
																						//tp28xx_byte_write(0x07, 0x80|(gain>>2));
                        							}

                            }
                            else if(EQ_COUNT+2 == count[i])
                            {
															//count[i]++;
															if(STD_HDC_DEFAULT == std[i] )
                              {
                                            
																	tp28xx_byte_write(0x2f, 0x0c);
                                            
																	tmp = tp28xx_byte_read(0x04);
                                            
																	status = tp28xx_byte_read(0x01);
                                            //if(0x10 == (0x11 & status) && (tmp < 0x18 || tmp > 0xf0))
                                            if(0x10 == (0x11 & status))
                                            //if((tmp < 0x18 || tmp > 0xf0))
                                            {
                                                std[i] = STD_HDC;
																							//TP2825B_SetTX(0x05); 
                                            }
                                            else
                                            {
                                                std[i] = STD_HDA;
																							//TP2825B_SetTX(0x02); 
																							
                                            }
                                            
                                            //Set_VidRes(mode[i], std[i]);
                                            //Printf("reg01=%02x reg04@2f=0c %02x std%02x \r\n", (WORD)status, (WORD)tmp, (WORD)std[i]);
                                            
                                        }
																				else
																				{
																					 //TP2825B_SetTX(0x00);
																				}

                            			if( STD_TVI != std[i] )
                            			{
                                        	//tp2802_manual_agc(iChip, i); //fix AGC when PTZ operation, it can be removed on TP2826/2827
                                   		 	//tp283x_egain(iChip, 0x0c);
                            			}
						if(0==MD0_1) 
						{
							DetAutoStd=0;
							Printf("\r\nDebug mode enable");
						}
                            }
														else
														{
/*															
																	if(mode[i] < TP2802_3M18)
																	{
                                            tmp = tp28xx_byte_read(0x03); //
                                            tmp &= 0x07;
                                            if(tmp != (mode[i]&0x07) && tmp < TP2802_SD)
                                            {
                                                state[i] = VIDEO_UNPLUG;
                                            }
																	}
*/															
														}


                        }

                }

}



void Init_TP_RegSet(){

//	BYTE *ptr_TP;
	BYTE i;

	TVII2CAddress = 0x88;

	if(0x28 == tp28xx_byte_read(0xfe))
	{
		
	}
	else
	{
			TVII2CAddress = 0x8a;
	}
	Printf("\r\nEVK detection address %02x", (WORD)TVII2CAddress);
	
	chip = tp28xx_byte_read(0xff);
	
	revision = tp28xx_byte_read(0xfc);
	
	Printf("\r\ndetection chip %02x rev %02x", (WORD)chip,(WORD)revision);


	if(TP2825B == chip)
	{
		TP2825BEVK_Switch_Vin();
	}
	else
	{
		TP2850EVK_Switch_Vin();
	}
		i = 0;
		//loss[i] = 1;
		//locked[i] = 0;
		count[i] = 0;
		state[i] = VIDEO_UNPLUG;
		std[i] = ManVidStd;
		mode[i] = ManVidRes;

  if(TP2860 == chip)
	{
		I2CDeviceSet(TVII2CAddress,TP2860_DataSet );
	}
	else
	{
		I2CDeviceSet(TVII2CAddress,TP2825B_DataSet );
	
	}
	
	TP2825B_reset_default();		//soft reset 
	
	Set_VidRes(ManVidRes, ManVidStd);
	
}
//////////////////////////////////////////////////////////////////////////////
void ConvertData(unsigned char dat, unsigned char reg)
{
   unsigned char i;
	
   	PTZ_pelco=0;

 if(0x85 == tp28xx_byte_read(0x1c) && 0x78 == tp28xx_byte_read(0x1d))
 {	
    for(i = 0; i < 8; i++)
    {
        PTZ_pelco <<= 3;

        if(0x01 & dat) PTZ_pelco |= 0x06;
        else PTZ_pelco |= 0x04;

        dat >>= 1;
    }
  }
  else
  {
      for(i = 0; i < 8; i++)
    {
        PTZ_pelco <<= 3;

        if(0x80 & dat) PTZ_pelco |= 0x06;
        else PTZ_pelco |= 0x04;

        dat <<= 1;
    }	
  }
/*		
		PTZ_buf[buf_index]= (PTZ_pelco>>16)&0xff;
		PTZ_buf[buf_index+1]= (PTZ_pelco>>8)&0xff;
		PTZ_buf[buf_index+2]= (PTZ_pelco)&0xff;		
*/
				tp28xx_byte_write(reg + 0 , (PTZ_pelco>>16)&0xff);
				tp28xx_byte_write(reg + 1 , (PTZ_pelco>>8)&0xff);
				tp28xx_byte_write(reg + 2 , (PTZ_pelco)&0xff);		
}



void StartTX(void)
{
			unsigned char tmp,i;
			
			tp28xx_byte_write(0xB6, 0x01); //clear flag
	
				tmp = tp28xx_byte_read(0x6f);
				tmp |= 0x01;
				tp28xx_byte_write(0x6f, tmp); //TX enable 
				tmp &= 0xfe;
				tp28xx_byte_write(0x6f, tmp); //TX disable
				
			for(i = 0; i <20; i++) //wait TX end
			{
					tmp = tp28xx_byte_read(0xB6);	
					if( 0x01 & tmp) break;
					delay(2);
			}
}
//////////////////////////////////////////////////////////////////////////////
//PTZ TX
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//send 128byte data on 4 lines with 16bytes x8 times
///////////////////////////////////////////////////////
void BurstTX(BYTE* buf)
{
//	BYTE i,j;
//	BYTE *p;
//	CODE BYTE TX_ADDR[8]={0x57,0x58,0x59,0x5a,0x5c,0x5d,0x5e,0x5f};
//		

//	p = buf;
//	
//		
//		tp28xx_byte_write(0x40, 0x10);
//		tp28xx_byte_write(0x56, 0x03);
//		tp28xx_byte_write(0x5b, 0x03);
//		tp28xx_byte_write(0x40, 0x00);
//		tp28xx_byte_write(0x56, 0x03);
//		tp28xx_byte_write(0x5b, 0x03);
//		for(j = 0; j < 8; j++)
//		{
//			for(i = 0; i < 8; i++  ) 
//			{
//				tp28xx_byte_write(TX_ADDR[i], *p);
//				//tp28xx_byte_write(TX_ADDR[i], 16*j+i);
//				p++;
//			}
//			tp28xx_byte_write(0x40, 0x10);
//			for(i = 0; i < 8; i++  ) 
//			{
//				tp28xx_byte_write(TX_ADDR[i], *p);
//				//tp28xx_byte_write(TX_ADDR[i], 16*j+i);
//				p++;
//			}
//			tp28xx_byte_write(0x40, 0x00);
//			StartTX();
//			delay(10); 
//		}		

}
//////////////////////////////////////////////////////////////////////////////
//PTZ RX
//////////////////////////////////////////////////////////////////////////////
void TP2825B_SetRX(BYTE index) 
{
   unsigned char i;
    
    //reg0xc9~d7 A8 A7
    CODE BYTE PTZ_dat[][17]=
    {
        {0x00,0x00,0x07,0x08,0x00,0x00,0x04,0x00,0x00,0x60,0x10,0x06,0xbe,0x39,0x27, 0x00,0x03}, //TVI 1080p/960p
				{0x00,0x00,0x07,0x08,0x00,0x00,0x02,0x00,0x00,0x60,0x08,0x06,0x5f,0x39,0x27, 0x00,0x03}, //TVI 720p
				
        {0x00,0x00,0x06,0x07,0x08,0x09,0x03,0x48,0x34,0x60,0x38,0x04,0xf0,0xd8,0x07, 0x00,0x27}, //AHD 1080p
        
			//	{0x00,0x00,0x06,0x07,0x08,0x09,0x03,0x48,0x34,0x60,0x1c,0x04,0xf0,0xd8,0x17, 0x00,0x27}, // AHD 720p
					{0x00,0x00,0x06,0x07,0x08,0x09,0x06,0x90,0x68,0x60,0x1d,0x04,0xf0,0xd8,0x07, 0x00,0x27}, // AHD 720p //changed20231103kevin
        {0x00,0x00,0x07,0x08,0x00,0x00,0x04,0xec,0x4e,0x60,0x10,0x06,0xbe,0x39,0x27, 0x00,0x03}, //BYD new A960p	
        {0x00,0x00,0x07,0x08,0x00,0x00,0x04,0x00,0x00,0x60,0x10,0x06,0xbe,0x39,0x27, 0x00,0x03}, //TVI 1080p/960p
				{0x00,0x00,0x07,0x08,0x00,0x00,0x02,0x00,0x00,0x60,0x08,0x06,0x5f,0x39,0x27, 0x00,0x03}, //TVI 720p	
        {0x00,0x00,0x08,0x09,0x0a,0x0b,0x04,0x69,0xee,0x60,0x2c,0x06,0xbe,0x39,0x07, 0x00,0x27}, //BYD new A960p30					
    };
/* only valid for TP2850/TP2825B    
		tp28xx_byte_write(0x40, 0x08); //mipi page
		i = tp28xx_byte_read(0x13);
		if(0x20&i) index +=1; //720p setting
		tp28xx_byte_write(0x40, 0x00); //mipi page
*/
   if( PTZ_960P == index)	index = 4;
   else if( PTZ_960P30_AHD == index)	index = 7;	
    for(i = 0; i < 15; i++)
    {
        tp28xx_byte_write(0xc9+i, PTZ_dat[index][i]);
    }    
    tp28xx_byte_write(0xa8, PTZ_dat[index][15]); 
		tp28xx_byte_write(0xa7, PTZ_dat[index][16]); 

}
/*
BYTE MonRX(void) 
{
  unsigned char i;
	unsigned char tmp;
		
		for(i = 0; i < 8; i++)
		{
					PTZ_buf[i]=0x00; //clear buf
		}
			tp28xx_byte_write(0xB6, 0x10); //clear flag

			for(i = 0; i < 200; i++) //wait RX end
			{
					tmp = tp28xx_byte_read(0xb6);
					tmp	&= 0x10;		
					if(tmp) break;
					delay(2);
			}

			tp28xx_byte_write(0xB6, 0x10); //clear flag

			if(tmp)
			{
				for(i = 0; i < 4; i++)
				{
							 PTZ_buf[  i] = tp28xx_byte_read(0x8c+i); //line1
							 PTZ_buf[4+i] = tp28xx_byte_read(0x91+i); //line2
				}								
			}
			
			if(tmp )		
			{
				tmp = 0;
				for(i = 0; i < 7; i++)
				{
					tmp += PTZ_buf[i];
				}	
				if( tmp == PTZ_buf[7])
				{
					return 0;
				}
				else
				{
					return 2;//packet error
				}
			}
			else
			{
				return 1; //time_out
			}
			
}
BYTE WaitRX(BYTE data1,data2) 
{
  unsigned char i;
	unsigned char tmp;
		
		for(i = 0; i < 8; i++)
		{
					PTZ_buf[i]=0x00; //clear buf
		}

			for(i = 0; i < 50; i++) //wait RX end
			{
					tmp = tp28xx_byte_read(0x91);
					if(tmp == data1)
					{
						tmp = tp28xx_byte_read(0x92);
						if(tmp == data2) break;
					}
					delay(2);
			}


			if(i < 50)
			{
				return 1;
			}
			else
			{
				return 0;
			}
			
}
*/
//////////////////////////////////////////////////////////////////////////////
//PTZ TX
//////////////////////////////////////////////////////////////////////////////
void MonTX(BYTE cmd, BYTE data1, BYTE data2, BYTE data3, BYTE data4) 
{
  unsigned char i;
	unsigned char sum;
	unsigned char tmp;

		for(i = 0; i < 12; i++)
		{
					PTZ_buf[i]=0x00; //clear buf
		}
		
		sum = data1 + data2 + data3 + data4;
			if(0xfc == cmd)
			{
					sum += 0xa6; //0xa5+0x01
					PTZ_buf[0] = 0xa5;
					PTZ_buf[1] = 0x01;
					PTZ_buf[2] = data1;
					PTZ_buf[3] = data2;
					PTZ_buf[4] = data3;
					PTZ_buf[5] = data4;	
					PTZ_buf[6] = sum;
			}
			else
			{
						sum += 0xb5;
						sum += cmd;
						PTZ_buf[1]=0x02;
						PTZ_buf[2]=0xB5;
						PTZ_buf[4]=cmd;
						PTZ_buf[5]=data1;
						
						PTZ_buf[7]=0x02;
						PTZ_buf[8]=data2;
						PTZ_buf[9]=data3;
						PTZ_buf[10]=data4;
						PTZ_buf[11]=sum;
			}
			
			if(0xfc == cmd) //HDC 
			{	
							 for(i = 0; i < 7; i++)
								{
										tp28xx_byte_write(0x6e, PTZ_buf[i]);
								}

								//StartTX(chip, PTZ_data.ch);

        }				
        else if(0xff == cmd) //HDA 
        {
					
								tmp = tp28xx_byte_read(0x02);
					      if(tmp&0x02)
								{
									TP2825B_SetRX(PTZ_HDA_2);
									TP2825B_SetTX(PTZ_HDA_2);														
								}
								else
								{
									TP2825B_SetRX(PTZ_HDA_1);
									TP2825B_SetTX(PTZ_HDA_1);														
								}

								if(0x85 == tp28xx_byte_read(0x1c) && 0x78 == tp28xx_byte_read(0x1d))
								{
									TP2825B_SetRX(PTZ_960P30_AHD);
									TP2825B_SetTX(PTZ_960P30_AHD);													
								}								

								ConvertData(data1, 0x58);
								ConvertData(data2, 0x5e);				
								ConvertData(data3, 0x64);
								ConvertData(data4, 0x6a);					
        }
				else				
				{
								if(0x85 == tp28xx_byte_read(0x1c) && 0x78 == tp28xx_byte_read(0x1d))
								{
									TP2825B_SetRX(PTZ_960P);
									TP2825B_SetTX(PTZ_960P);													
								}
								else
								{
					        TP2825B_SetRX(PTZ_TVI);
								  TP2825B_SetTX(PTZ_TVI);
                }									
								for(i = 0; i < 12; i++)
								{
												tp28xx_byte_write(0x55+i , PTZ_buf[i]); //line1&2
												tp28xx_byte_write(0x61+i , PTZ_buf[i]); //line3&4
								}				
								
				}

				StartTX();
}
//////////////////////////////////////////////////////////////////////////////
//PTZ TX init
//////////////////////////////////////////////////////////////////////////////
void TP2825B_SetTX(BYTE index) 
{
  unsigned char i;
	//unsigned char page_bak;

    CODE BYTE PTZ_dat[][10]=
    {
        {0x02,0x00,0x00,0x0b,0x0c,0x0d,0x0e,0x19,0x78,0x21}, //TVI 1080p
				{0x02,0x00,0x00,0x0b,0x0c,0x0d,0x0e,0x19,0x78,0x21}, //TVI 720p
				
				{0x02,0x00,0x00,0x0e,0x0f,0x10,0x11,0x24,0xf0,0x57}, //ACP2.0 for 2825B 148.5M

		
        {0x02,0x00,0x00,0x0e,0x0f,0x10,0x11,0x12,0x00,0x57}, //ACP2.0 for 2825B 74.25M
        {0x02,0x00,0x00,0x0f,0x10,0x00,0x00,0x12,0xf0,0x6f}, //960H for 2825B 74.25M
        {0x0a,0x1d,0x80,0x10,0x11,0x12,0x13,0x15,0xb8,0x9f}, //HDC 2825B 148.5M
				{0x0a,0x1d,0x80,0x10,0x11,0x12,0x13,0x0a,0x00,0x9f}, //HDC 2825B 74.25M
				{0x02,0x00,0x00,0x0e,0x0f,0x10,0x11,0x12,0x00,0x57}, //ACP2.0 for 2825B 74.25M
				{0x02,0x00,0x00,0x0d,0x0e,0x0f,0x10,0x0b,0x5a,0x17}, //BYD AHD960p30 94.5M
    };		
   CODE BYTE PTZ_reg[10]={0x6f,0x70,0x71,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8};
		
	  if( PTZ_960P == index)	index = 0;	
	  else if( PTZ_960P30_AHD == index)	index = 8;	
	
			for(i = 0; i < 10; i++)
			{
        tp28xx_byte_write(PTZ_reg[i], PTZ_dat[index][i]);
			}
			for(i = 0; i < 24; i++)
			{
        tp28xx_byte_write(0x55+i, 0x00);
			}    
	
}

void Menu(void)
{
	unsigned char i;
	CODE BYTE menu[][3]={
		{0x17,0x5f,0x00},
		{0xff,0x02,0x00},
		{0xfc,0x89,0x08},
		{0xfc,0x89,0x01}
	};
	
	i = std[0];

	MonTX(menu[i][0], menu[i][1], menu[i][2], 0x00, 0x00);
	if(STD_HDC == i) MonTX(menu[3][0], menu[3][1], menu[3][2], 0x00, 0x00);
}
void Left(void)
{
	unsigned char i;
	CODE BYTE menu[][3]={
		{0x09,0x00,0x00},
		{0xff,0x00,0x04},
		{0xfc,0x89,0x06}
	};
	
	i = std[0];
	MonTX(menu[i][0], menu[i][1], menu[i][2], 0x00, 0x00);
}
void Right(void)
{
	unsigned char i;
	CODE BYTE menu[][3]={
		{0x08,0x00,0x00},
		{0xff,0x00,0x02},
		{0xfc,0x89,0x07}
	};
	
	i = std[0];
	MonTX(menu[i][0], menu[i][1], menu[i][2], 0x00, 0x00);
}
void Up(void)
{
	unsigned char i;
	CODE BYTE menu[][3]={
		{0x06,0x00,0x00},
		{0xff,0x00,0x08},
		{0xfc,0x89,0x04}
	};
	
	i = std[0];
	MonTX(menu[i][0], menu[i][1], menu[i][2], 0x00, 0x00);
}
void Down(void)
{
	unsigned char i;
	CODE BYTE menu[][3]={
		{0x07,0x00,0x00},
		{0xff,0x00,0x10},
		{0xfc,0x89,0x05}
	};
	
	i = std[0];
	MonTX(menu[i][0], menu[i][1], menu[i][2], 0x00, 0x00);
}
void Reset(void)
{
	unsigned char i;
	CODE BYTE menu[][3]={
		{0x14,0x00,0x00},
		{0x00,0x00,0x10},
		{0xfc,0x89,0x00}
	};
	
	i = std[0];
	MonTX(menu[i][0], menu[i][1], menu[i][2], 0x00, 0x00);
}

void ReadUTC(void)
{
			unsigned char tmp;
			if(VIDEO_LOCKED==state[0])
			{			
				tmp = tp28xx_byte_read(0xB6);
	    			if(0x10 & tmp)
				{
					//Printf("\r\nDATA1~4: %02x %02x  %02x %02x", (WORD)tp28xx_byte_read(0x8f),(WORD)tp28xx_byte_read(0x8e),(WORD)tp28xx_byte_read(0x8d),(WORD)tp28xx_byte_read(0x8c));	
					Printf("\r\nDATA1~4: %02x %02x  %02x %02x", (WORD)tp28xx_byte_read(0x8c),(WORD)tp28xx_byte_read(0x8d),(WORD)tp28xx_byte_read(0x8e),(WORD)tp28xx_byte_read(0x8f));	
					tmp = tp28xx_byte_read(0xa7);
					//if(0x03==tmp) Printf("\r\nDATA5~8: %02x %02x  %02x %02x", (WORD)tp28xx_byte_read(0x95),(WORD)tp28xx_byte_read(0x94),(WORD)tp28xx_byte_read(0x93),(WORD)tp28xx_byte_read(0x92));	
					if(0x03==tmp) Printf("\r\nDATA5~8: %02x %02x  %02x %02x", (WORD)tp28xx_byte_read(0x92),(WORD)tp28xx_byte_read(0x93),(WORD)tp28xx_byte_read(0x94),(WORD)tp28xx_byte_read(0x95));	
					tp28xx_byte_write(0xb6, 0x10); //clear 
				}
			}			
}
