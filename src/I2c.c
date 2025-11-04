// *****************************************************
// Company : Techpoint Inc
// $Date: 2013-09-17 
// $Log:  $
// ******************************************************

#include "inc\Config.h"
#include "inc\reg.h"
#include "inc\typedefs.h"
#include "inc\I2C.h"
#include "inc\main.h"
#include "inc\printf.h"

#define	I2C_SCL		P1_0
#define	I2C_SDA		P1_1
#define MDC_UCOM	P1_2
#define MDIO_UCOM	P1_3
#define I2C_FAST

extern xdata BYTE TVII2CAddress;

void delay1(WORD del)
{
    while(del--);
}

#ifdef I2C_FAST

 #define I2Cdelay()
#else
 void I2Cdelay(void)
 {
	int i;
	for (i=0;i<10;i++) {
		};
}
#endif

//BYTE I2CWriteData_Wait(BYTE value);
BYTE I2C_byte_read(BYTE addr, BYTE index)
{
	BYTE val;
/*
	I2CStart();
	I2CWriteData(addr);
	//I2CWriteData(TVII2CAddress);
	I2CWriteData(index);
	I2CReStart();
	I2CWriteData(TVII2CAddress | 0x01);
	val = I2CReadData();
	I2CStop();
*/
	
	I2CSA =(BYTE)(addr);
	I2CBUF =(BYTE)(index);
	I2CCR = 0x03;
	delay1(300);

	I2CSA = (BYTE)(addr|0x01);
	I2CCR = 0x07;
	delay1(500);
	val = I2CBUF;	
	return(val);
}

void I2C_byte_write(BYTE addr, BYTE index, BYTE val)
{
/*	
	I2CStart();
	I2CWriteData(addr);
	//I2CWriteData(TVII2CAddress);
	I2CWriteData(index);
	I2CWriteData(val);
	I2CStop();
*/
    I2CSA = (BYTE)(addr);
    I2CBUF = (BYTE)(index);
    I2CCR = 0x03;
    delay1(300);

    I2CBUF = (BYTE)(val);
    I2CCR = 0x05;
    delay1(500);	
}

//BYTE tp28xx_byte_read(BYTE addr, BYTE index)
BYTE tp28xx_byte_read(BYTE index)
{
/*	
	BYTE val;

	I2CStart();
	//I2CWriteData(addr);
	I2CWriteData(TVII2CAddress);
	I2CWriteData(index);
	I2CReStart();
	I2CWriteData(TVII2CAddress | 0x01);
	val = I2CReadData();
	I2CStop();

	return val;
*/
	return I2C_byte_read(TVII2CAddress, index);
}

//void tp28xx_byte_write(BYTE addr, BYTE index, BYTE val)
void tp28xx_byte_write(BYTE index, BYTE val)
{
/*	
	I2CStart();
	//I2CWriteData(addr);
	I2CWriteData(TVII2CAddress);
	I2CWriteData(index);
	I2CWriteData(val);
	I2CStop();
*/
	I2C_byte_write(TVII2CAddress, index, val);	
}

void WriteI2C16(BYTE addr, BYTE indexH, BYTE indexL, BYTE valH, BYTE valL)
{
/*	
	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(indexH);
	I2CWriteData(indexL);
	I2CWriteData(valH);
	I2CWriteData(valL);
	I2CStop();
*/
	I2CSA = addr;
	I2CBUF = indexH;
	I2CCR = 0x03;
	delay1(300);		
	
	I2CBUF = indexL;
	I2CCR = 0x01;
	delay1(300);
	
	I2CBUF = valH;
	I2CCR = 0x01;
	delay1(500);	
	I2CBUF = valL;
	I2CCR = 0x05;
	delay1(500);			
}

WORD ReadI2C16(BYTE addr, BYTE indexH, BYTE indexL)
{
	WORD val;
/*
	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(indexH);
	I2CWriteData(indexL);
	I2CReStart();
	I2CWriteData(addr | 0x01);
	val =(WORD) I2CReadDataWithACK();
	val <<=8;
	val =(WORD) I2CReadDataWithNAK();
	I2CStop();
*/
	I2CSA = addr;
	I2CBUF = indexH;
	I2CCR = 0x03;
	delay1(300);		
	
	I2CBUF = indexL;
	I2CCR = 0x01;
	delay1(300);
	
	I2CSA = addr|0x01;
	I2CCR = 0x03;
	delay1(500);	
	val = (WORD)I2CBUF<<8;
	I2CCR = 0x05;
	delay1(500);	
	val |= (WORD)I2CBUF;	
	return val;
}
/*
BYTE WriteI2Cn(BYTE addr, BYTE index, BYTE *val, BYTE cnt)
{
	BYTE rd=1, i;

	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index);

	for(i=0; i<cnt; i++)
		I2CWriteData(*(val+i));		//LJY050101

	I2CStop();

	return rd;
}
*/
/*
BYTE WriteI2Cn_(BYTE addr, BYTE *val, BYTE cnt)
{
	BYTE rd=1, i;

	I2CStart();
	I2CWriteData(addr);

	for(i=0; i<cnt; i++)
		I2CWriteData(*(val+i));		//LJY050101

	I2CStop();

	return rd;
}
*/
//BYTE I2CWriteData_Wait(BYTE value);
/*
void I2CReadByteMSP(BYTE addr, BYTE index, BYTE *pd, BYTE cnt)
{
	BYTE i;

	I2CStart();
	I2CWriteData_Wait(addr);
	I2CWriteData(index);
	for(i=0; i<cnt; i++) {
		I2CWriteData(*(pd+i));
	}
	I2CStart();
	I2CWriteData_Wait(addr | 0x01);
	*pd = I2CReadDataWithACK();
	*(pd+1) = I2CReadData();

	I2CStop();
}


BYTE ReadI2CStatus( BYTE addr )
{
	BYTE val;

	I2CStart();
	I2CWriteData(addr | 0x01);
	val = I2CReadData();
	I2CStop();

	return val;
}
*/

//BYTE I2CReadDataWithNAK(void)
//{
////	return I2CReadData();
//	int i;
//	BYTE value=0;

//	I2C_SDA = 1;	I2Cdelay();
//	I2C_SCL = 0;

//	for(i=0; i<8; i++) {
//		I2C_SCL = 1;
//		value <<= 1;
//		if(I2C_SDA) value |= 1;
//		I2C_SCL = 0;
//	}
//	I2C_SDA = 1;	I2Cdelay();		//nck
//	I2C_SCL = 1;	I2Cdelay();
//	I2C_SCL = 0;

//	return value;
//}

//void ReadI2Cmn(BYTE addr, BYTE wcnt, BYTE rcnt, BYTE *rwdata)
//{
//	BYTE i;

//	I2CStart();
//	I2CWriteData(addr);
//	for(i=0; i<wcnt; i++)
//		I2CWriteData( rwdata[i] );

//	I2CStart();
//	I2CWriteData(addr | 0x01);
//	for(i=0; i<rcnt-1; i++)
//		rwdata[i] = I2CReadDataWithACK();
//	rwdata[i++] = I2CReadDataWithNAK();
//	I2CStop();
//}


/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
/*
BYTE I2CWriteData_Wait(BYTE value)
{
	WORD i;
	BYTE ack;

	for(i=0; i<8; i++, value<<=1) {
		if(value & 0x80) I2C_SDA = 1;
		else			 I2C_SDA = 0;
		I2Cdelay();
		I2C_SCL = 1;	I2Cdelay();
		I2C_SCL = 0;
	}
	I2C_SDA = 1;	I2Cdelay();
	I2C_SCL = 1;	I2Cdelay();
	i=0;
    while(1) {
		if( I2C_SCL ) break;
		i++;
	}

	ack = I2C_SDA;	//I2Cdelay();
	I2C_SCL = 0;
	return (1-ack);
}
*/

//void I2CStart()
//{
//	I2C_SCL = 1;	I2Cdelay();
//	I2C_SDA = 1;	I2Cdelay();
//	I2C_SDA = 0;	I2Cdelay();

//}

//void I2CReStart()
//{
//	I2C_SDA = 1;	I2Cdelay();
//	I2C_SCL = 1;	I2Cdelay();
//	I2C_SDA = 0;	I2Cdelay();

//}


//void I2CStop()
//{
//	I2C_SDA = 0;	I2Cdelay();
//	I2C_SCL = 0;	I2Cdelay();
//	I2C_SCL = 1;	I2Cdelay();
//	I2C_SDA = 1;	I2Cdelay();
////	I2C_SCL = 1;	I2Cdelay();
////	I2C_SDA = 1;
//}

//void I2CWriteData(BYTE value)
//{
//	int i;

//	for(i=0; i<8; i++){
//		I2C_SCL = 0;
//		I2Cdelay();
//		if((value & 0x80) != 0) 
//			I2C_SDA = 1;
//		else 			 
//			I2C_SDA = 0;
//		I2Cdelay();
//		I2C_SCL = 1;
//		I2Cdelay();//vhuang
//		I2C_SCL = 0;
//		I2Cdelay();
//		value<<=1;
//	}
//	I2C_SCL = 0;		I2Cdelay();
//	I2C_SCL = 1;		I2Cdelay();
//	I2C_SCL = 0;		I2Cdelay();
//}

//BYTE I2CReadData()
//{
//	int i;
//	BYTE value=0;

//	
//	for(i=0; i<8; i++) {
//		I2C_SCL = 0;
//		I2Cdelay();
//		I2C_SCL = 1;
//		value <<= 1;
//		if(I2C_SDA) value |= 1;
//		I2Cdelay();
//		I2C_SCL = 0;
//		I2Cdelay();
//	}

//	I2C_SCL = 0;	I2Cdelay();
//	I2C_SCL = 1;	I2Cdelay();
//	I2C_SCL = 0;	I2Cdelay();

//	return value;

//}

//BYTE I2CReadDataWithACK()
//{
//	int i;
//	BYTE value=0;

//	I2C_SDA = 1;	I2Cdelay();
//	I2C_SCL = 0;

//	for(i=0; i<8; i++) {
//		I2C_SCL = 1;
//		value <<= 1;
//		if(I2C_SDA) value |= 1;
//		I2C_SCL = 0;
//	}
//	I2C_SDA = 0;	I2Cdelay();		//ack
//	I2C_SCL = 1;	I2Cdelay();
//	I2C_SCL = 0;

//	return value;
//}


