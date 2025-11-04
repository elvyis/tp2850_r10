// *****************************************************
// Company : Techpoint Inc
// $Id: TP2802.h 16792 2013-10-17 02:08:40Z SJ $
// $Author: SJ $
// $Date: 2014-03-10 $
// $Revision: 00 $
// $Log:  $
// ******************************************************

#ifndef __TP2802_H__
#define __TP2802_H__

enum {
	CH1 = 0,
	CH2,
	CH3,
	CH4,
	AutoSel
};

enum{
	VIN1_Y = 0,
	VIN2_Y,
	VIN3_Y,
	VIN4_Y,
	VIN1_C,
	VIN2_C,
	VIN3_C,
	VIN4_C
};

enum{
TP2802_1080P25 =	    0x03,
TP2802_1080P30 =	    0x02,
TP2802_720P25  =	    0x05,
TP2802_720P30  =    	0x04,
TP2802_720P50  =	    0x01,
TP2802_720P60  =    	0x00,
TP2802_SD      =        0x06,
INVALID_FORMAT =		0x07,
TP2802_720P25V2=	    0x0D,
TP2802_720P30V2=		0x0C,
TP2802_PAL	   =        0x0E,
TP2802_NTSC	   =    	0x0F,
TP2802_3M18         =   0x20,   //2048x1536@18.75 for TVI
TP2802_5M12         =   0x21,   //2592x1944@12.5 for TVI
//TP2802_4M15         =   0x22,   //2688x1520@15 for TVI
TP2802_3M20         =   0x23,   //2048x1536@20 for TVI
TP2802_4M12         =   0x24,   //2688x1520@12.5 for TVI
TP2802_6M10         =   0x25,   //3200x1800@10 for TVI
TP2802_QHD30        =   0x26,   //2560x1440@30 for TVI/HDA/HDC
TP2802_QHD25        =   0x27,   //2560x1440@25 for TVI/HDA/HDC
TP2802_QHD15        =   0x28,   //2560x1440@15 for HDA
TP2802_QXGA18       =   0x29,   //2048x1536@18 for HDA/TVI
TP2802_QXGA30       =   0x2A,   //2048x1536@30 for HDA
TP2802_QXGA25       =   0x2B,   //2048x1536@25 for HDA
TP2802_4M30         =   0x2C,   //2688x1520@30 for TVI(for future)
TP2802_4M25         =   0x2D,   //2688x1520@25 for TVI(for future)
TP2802_5M20         =   0x2E,   //2592x1944@20 for TVI/HDA
TP2802_8M15         =   0x2f,   //3840x2160@15 for TVI
TP2802_8M12         =   0x30,   //3840x2160@12.5 for TVI
TP2802_1080P15      =   0x31,   //1920x1080@15 for TVI
TP2802_1080P60      =   0x32,   //1920x1080@60 for TVI
TP2802_960P30       =   0x33,   //1280x960@30 for TVI
TP2802_1080P20      =   0x34,    //1920x1080@20 for TVI
TP2802_720P30HDR    =   0x35,    //1280x720@30 for TVI
TP2802_WXGA			    =   0x36,    //1280x800@30 for TVI
TP2802_1080P27      =   0x37,   //1920x1080@27.5 for TVI
TP2802_1080P24      =   0x38,   //1920x1080@24 for TVI
TP2802_1280x320P60  =   0x39,
TP2802_960P25       =   0x3a,   //1280x960@25 for AHD
TP2802_1080P50      =   0x3e,   //1920x1080@60 for TVI
TP2802_720P25HDR    =   0x3f,    //1280x720@25 for TVI
TP2802_720P864M = 0x40,		 //1280x720@30 for TVI(1600X900)
TP2802_1080P_X3C		    =   0x41,    //1920X1080@25 for X3C TVI
TP2802_QHD275						=		0x42,		//QHD 27.5, 
TP2802_480P20							=		0x43,		//1024x480@20Hz, total 1250x540
};
enum{
    VIDEO_UNPLUG,
    VIDEO_IN,
    VIDEO_LOCKED,
    VIDEO_UNLOCK
};
enum{
    STD_TVI,
    STD_HDA,
    STD_HDC,
    STD_HDA_DEFAULT,
    STD_HDC_DEFAULT
};
enum{
    PTZ_TVI      = 0,
	  PTZ_TVI_720P = 1,
    PTZ_HDA_1    = 2,
	  PTZ_HDA_2    = 3,
    PTZ_CVBS     = 4, 
    PTZ_HDC_1    = 5,
	  PTZ_960P     = 6,
	  PTZ_960P30_AHD = 7,	
};
enum{
    RES_1080P,
    RES_720P,
    RES_480I,
    RES_576I
};

#define FLAG_LOSS       0x80
#define FLAG_LOCKED     0x60

#define Bits16out	0
#define Bits8out	1

#define NoVid	0
#define IsVid	1

#define	USER_DATA_UPDATE	157
#define	FIRMWARE_UPDATE	158
#define	FONT_UPDATE	159

#define	BLOCK_LENGTH	128

void Init_TP_RegSet(void);
BYTE Set_ResWithAutoDet(BYTE ch);
void Sel_VD_Out(BYTE ch);
void MonTX(BYTE cmd, BYTE data1, BYTE data2, BYTE data3, BYTE data4);
void TP2825B_SetTX(BYTE cmd);
void TP2825B_SetRX(BYTE cmd);
BYTE WaitRX(BYTE data1,data2); 
BYTE MonRX(void);
void BurstTX(BYTE* buf);
void Menu(void);
void Up(void);
void Down(void);
void Left(void);
void Right(void);
void Reset(void);
void Set_VidRes(BYTE Res, BYTE Std);
void ReadUTC(void);
#endif

