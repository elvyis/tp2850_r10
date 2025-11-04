// *****************************************************
// Company : Techpoint Inc
// $Id: Main.h 16792 2013-10-17 02:08:40Z SJ $
// $Author: SJ $
// $Date: 2013-10-17 18:08:40 -0800 (Thu, 17 Oct 2013) $
// $Revision: 00 $
// $Log:  $
// ******************************************************

#ifndef __MAIN__
#define __MAIN__


//----------- P0 Define ------------
//#define MD0_0			P0_0
//#define MD0_1			P0_1
//#define MD0_2			P0_2
//#define MD0_3			P0_3
#define MD0_0			P3_4
#define MD0_1			P3_5
#define MD0_2			P3_6
#define MD0_3			P3_7




#ifdef TP2802
#define Chan1			P0_4
#define Chan2			P0_5
#define Chan3			P0_6
#define Chan4			P0_7
#endif

//----------- P1 Define ------------

#define RNT_nPAL 		P1_5
#define R6050f_n3025f  	P1_6
#define R1080P_n720P	P1_7

//----------- reset Define ------------

//#define reset			P3_3
#define reset			P2_0


#define Test 	0
#define Live	1

//#define	R720P60		0
//#define	R1080P30	1

void delay(BYTE cnt);

BYTE RS_ready(void);
BYTE RS_rx(void);
void RS_tx(BYTE tx_buf);
void NewLine(void);
void PutsP(DATA_P BYTE *ptr);
void MonWriteI2C(BYTE addr, BYTE index, BYTE val);
BYTE MonReadI2C(BYTE addr, BYTE index);

void I2CDeviceSet_(BYTE addr, CODE_P BYTE *RegSet);

void I2CDeviceSet(BYTE addr, CODE_P BYTE *RegSet);
void MonWriteI2Cn_(BYTE addr, BYTE *val, BYTE cnt); 
void Main_Initialize(void);

void Prompt(void);

BYTE Asc1Bin(BYTE asc);
BYTE Asc2Bin(DATA_P BYTE *s);
#define DISPLAY_DEBUG_INFO
#endif	// __MAIN__

