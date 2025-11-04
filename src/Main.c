//****************************************************************/
/*                                                              							*/
/*                     HD encocer & decoder boards of Vertex6              	              */
/*                                                              							*/
/****************************************************************/

#include <stdio.h>
#include <string.h>
#include "inc\Config.h"
#include "inc\reg.h"
#include "inc\typedefs.h"
#include "inc\main.h"
#include "inc\i2c.h"
#include "inc\printf.h"
#include "inc\Coaxitron.h"

#include "inc\TP2825.h"
#include "inc\isp_reg.h"

bit		I2CInitialBlocking = 1;
bit		DetAutoRes = 0;
bit 	MDIN_debug = 0;
bit		half_scaler = 0;
bit 	en_tvi960p_H1400=0;
bit   DetAutoStd = 1;
bit   BT1120_out = 0;
bit		en_960P = 0;
bit		g_uart0_flag = 0;
bit   BYDtest = 0;
xdata	BYTE	ManVidRes;
xdata	BYTE	ManVidStd;
xdata	BYTE	ManSelCh;
xdata	BYTE	IsChannel;

#ifdef TEST_SERCOM
bit		MaskEcho = 0;
xdata	BYTE	StoreArg1 = 0, StoreArg2 = 0;
xdata	BYTE	AddressOffset = 0;
#endif //TEST_SERCOM
xdata	WORD    tm01=0;
xdata	BYTE    tm02=0;
xdata	BYTE	mS_timer;
xdata	BYTE    tic01=0;
xdata	BYTE    tic02=0;
xdata	BYTE	tic_rs485=0;
xdata	BYTE	I2CAddressDeb;
xdata	BYTE	TVII2CAddress;
		bit timeout=1;


extern xdata BYTE cam_ch;
extern CODE PelcoD_cmd PelcoD_cmd_dataset[];
extern xdata BYTE locked[];
//extern BYTE Det_VideoLoss(BYTE);
extern void EQ_Detect();
extern void MDIN340(void);
extern void CreateMDIN340VideoInstance(void);
extern int xmodemReceive(unsigned char data_type);

//===================== Serial ============================================
#define BUF_MAX 	134
static	xdata BYTE	RS_buf[BUF_MAX];
static	xdata BYTE   RS_in=0, RS_out=0;
		bit	        RS_Xbusy=0;			// bit RS_Xbusy=0;

//================== Debug key input ======================================
#define MaxBuf		20					 
#define MaxArg		8					
static  xdata BYTE  commdbuf[MaxBuf];
static  xdata BYTE  commdptr;
static  xdata BYTE	  bptr;
static  xdata BYTE  arg[MaxArg], argn;	
//================== PTZ =================================================

#define		isr_timer0_on()		(ET0=1)
#define		isr_timer1_on()		(ET1=1)
#define		isr_timer2_on()		(ET2=1)
#define		isr_uart0_on()		(ES=1)
#define		isr_uart1_on()		(ES1=1)
#define		isr_ext0_on()		(EX0=1)
#define		isr_ext1_on()		(EX1=1)
#define		isr_global_on()		(EA=1)
#define		isr_i2c_on()		(EINT3=1)
#define		timer0_start()		(TR0=1)
#define		timer1_start()		(TR1=1)
#define		isr5_tp2801_on()		(EINT5=1)
/*****************************************************************************/
/*      INT 0 Interrupt                                                    */
/*****************************************************************************/
INTERRUPT(0, int0_int)
{
	EX0 = 0;
	//g_vsync_flag = 1;

	EX0 = 1;

}


/*****************************************************************************/
/*      Timer 0 Interrupt                                                    */
/*****************************************************************************/
INTERRUPT(1, timer0_int)
{
	EA = 0;
	
	tm01++;						//9600Hz(104us)
	tm02++;
	tic_rs485++;

	#ifdef CLOCK_11M
	if( tm01 > 48 ) {			// 5msec
	#elif defined CLOCK_22M
	if( tm01 > 48*2 ) {		
	#endif
	
		tm01 = 0;
	    tic01++;
		if(tic02)
		{
			tic02--;	
		}
		else
		{
			timeout = 1;
		}	
	}
	if(tm02 > 10)
	{
		tm02 = 0;
		if(mS_timer) mS_timer--;
	}
	EA = 1;
}
void  EX1_int(void) interrupt 2		// I2C Interrupt
{
	EA = 0;

	EA = 1;
}	
void wait_5ms(BYTE cnt)		//5ms period
{
	ET0 = 0;
	timeout = 0;
	tic02 = cnt;
	ET0 = 1;
}
/*****************************************************************************/
/*      Timer 1 Interrupt                                                    */
/*****************************************************************************/
/*
INTERRUPT(5, timer2_int)
{
	ET2 = 0;		//disable interrupt timer2
	
	tic_rs485++;
	
	TF2 = 0; 		//clear interrupt flag
	ET2 = 1;		//enable interrupt timer2
}
*/

void delay(BYTE cnt)		//5ms period
{
	BYTE t;

	if( !cnt ) return;

	t = tic01 + cnt;
	while( tic01 != t );
}

//****************************************************************************/
//      Serial Interrupt                                                   
//****************************************************************************/
INTERRUPT(4, serial_int)
{
	EA = 0;
#if 1	
	if( RI ) {					//--- Receive interrupt ----
		RI = 0;
		RS_buf[RS_in++] = SBUF;
		if( RS_in>=BUF_MAX ) RS_in = 0;
	}

	if( TI ) {					//--- Transmit interrupt ----
		TI = 0;
		RS_Xbusy=0;
	}
#else
	if(g_uart0_flag == 0)
	{
//		g_rx_buf[g_wr_index++] = SBUF;
//		if(g_wr_index == UART_RBUF_MAX)
//			g_wr_index = 0;
//		else	;
		RS_buf[RS_in++] = SBUF;
		if( RS_in>=BUF_MAX ) RS_in = 0;		
		//RI = 0;
	}
	else	;
	RI = 0;
	TI = 0;
	g_uart0_flag = 0;	
#endif
	EA = 1;
}
void i2c_int(void) interrupt 9
{
	EA = 0;
	EXIF = 0;
	//g_i2c_flag = YES;
	EA = 1;
}

void tp2801_int5(void) interrupt 11
{
	EA = 0;
  EXIF = 0;
	//g_2801_int5_flag=1;
	
	EA = 1;
}
//=============================================================================
//		Serial RX Check 												   
//=============================================================================
BYTE RS_ready(void)
{
	if( RS_in == RS_out ) return 0;
	else return 1;
}
//=============================================================================
//		Serial RX														   
//=============================================================================
BYTE RS_rx(void)
{
	BYTE	ret;
		
	//ES = 0;
	ret = RS_buf[RS_out];
	RS_out++;
	if(RS_out >= BUF_MAX) 
		RS_out = 0;
	//ES = 1;

	return ret;
}
//=============================================================================
//		Serial TX														   
//=============================================================================
void RS_tx(BYTE tx_buf)
{
#if 1	
	while(1) {
		if(!RS_Xbusy) {
			SBUF = tx_buf;
			RS_Xbusy=1;
			break;
		}
	}
#else
	//g_uart0_flag = 1; //TX_FLAG;
	SBUF = tx_buf;
	//while(g_uart0_flag)	;
	delay1(20);
#endif	
}
void timer_init(void)
{
	// timer 0 : mode 1
  TMOD = 0x21;

	// timer 0 : 10ms period..
	// 24M/12 = 2M
	// 20,000 / 2M = 10 ms, 0x10000 - 20000 = 0xB1E0
	//TH0 = 0xB1;		//=0x63
	//TL0 = 0xE0;		//=0xC0
	// 200 / 2M = 100 us, 0x10000 - 200 = 0xff38
	TH0 = 0xff;		//=0x63
	TL0 = 0x38;		//=0xC0
	IE = 0x82;
}
void uart0_init(void)
{
	PCON = 0x80 ;		//Double baud rate when Timer1 is used=PCON.7
	SCON = 0x50 ;		//8bit UART, Baud rate is variable=SCON.6
									//Receiver Enable=SCON.4
	TMOD = 0x21 ;		//8bit auto reload counter=TMOD.5
									//16bit counter=TMOD.0 (Timer0 mode1)
	TH1  = 0xF3 ; 	// 0xF3:9600 (24MHz) -> 0xE6:9600(48MHz)
                  // TH1=256-(2x48x1000000)/(384x9600)
//	TH1  = 0xE6 ; 	// 0xF3:9600 (24MHz) -> 0xE6:9600(48MHz)
	timer1_start();
}
/*===========================================================================*/
/*        Initialize CPU                                                     */
/*===========================================================================*/
	
void InitCPU(void)
{
	
PCON = 0x80;		// 0000 0000 SMOD(double baud rate bit) = 1		
	
//	TH1 = 0xf0;
	SCON = 0x50;		// 0100 0000 mode 1 - 8 bit UART				
						// Enable serial reception						
    TMOD = 0x22;		// 0010 0010 timer 0 - 8 bit auto reload		
						// timer 1 - baud rate generator				
    TCON = 0x55;		// 0101 0001 timer 0,1 run						
						// int 0,  edge triggered						
						// int 1,  edge triggered						
						// TF1 TR1 TF0 TR0	EI1 IT1 EI0 IT0				
//	TH0 = TL0 = 64;		// 64=4608 Hz at 11.0592MHz
						// 64=4800Hz at 11.0592MHz (11.0592/12)/192=4800Hz. (255-64+1=192)
						
//	TH0 = TL0 = 160;	// 160=9600Hz at 11.0592MHz (11.0592/12)/96=9600Hz. (255-160+1=96)
	TH0 = TL0 = 100; //100;	// 160=9600Hz at 11.0592MHz (11.0592/12)/96=9600Hz. (255-160+1=96)
	TH1  = 0xF3;    // 19200
						
	
	IP	 = 0x02;		// 0000 0000 interrupt priority					
						// -  - PT2 PS PT1 PX1 PT0 PX0	 		         
	IE	 = 0x82;		// 1001 0010 interrupt enable:Serial,TM0			
						// EA - ET2 ES ET1 EX1 ET0 EX0	


	TI	 = 1;			
	ES   = 1;		
	
I2CTP = 0x03; //1;	//4;	//0x0a;	// i2c timer period

	XBYTE[rGPC_DIR] = 0x7e;		//1->input 0->output  
	XBYTE[rGPC_CTRL] = 0x07;	//GPIOC0~2(P2) as GPIO  
	
	XBYTE[rGPD_DIR] = 0xf8;		//1->input 0->output   
	XBYTE[rGPD_CTRL] = 0x0f;	 //GPIOD4~7(P3) as GPIO
	
	RI=0; TI=0; TF0=0;
}
/*===========================================================================*/
/*		New Line			                             */
/*===========================================================================*/
void NewLine(void)
{
 	Puts("\r\n");	
}

void PutsP(DATA_P BYTE *ptr)
{
	BYTE ch;
	while(*ptr!='\0') {
		ch = *ptr++;
		RS_tx(ch);
	}
}

/*===========================================================================*/
/*		Prompt				                                                 */
/*===========================================================================*/
void Prompt(void)
{
	Printf("\r\nI2C[%02x]>", (WORD)I2CAddressDeb);
}
/*===========================================================================*/
/*		I2C Edit Read		                                                 */
/*===========================================================================*/

void MonWriteI2C(BYTE addr, BYTE index, BYTE val) 
{
	Printf("\r\nWrite %02xh to [Adrs(%02xh)Index(%02xh)]", (WORD)val, (WORD)addr, (WORD)index);
	I2C_byte_write(addr, index, val);
}
/*
void Montp28xx_byte_writen_(BYTE addr, BYTE *val, BYTE cnt) 
{
	BYTE i;

	Printf("Write ");
	for(i=0; i<cnt; i++) {
		Printf("%02xh ", val[i]);
	}
	Printf("to [Adrs(%02xh)", (WORD)addr);
	if( !tp28xx_byte_writen_(addr, val, cnt) )		//LJY001127
		Puts("---> Fail!! ");	
}
*/
/*===========================================================================*/
/*		I2C Edit Read		                                                 */
/*===========================================================================*/
BYTE MonReadI2C(BYTE addr, BYTE index)
{
	BYTE val;

	val = I2C_byte_read(addr, index);
	Printf("Read [Adrs:%02xh,%02xh] %02xh", (WORD)addr, (WORD)index, (WORD)val);

	return val;
}
/*
void MonReadI2Cmn(BYTE addr, BYTE *wrdata, BYTE argcnt)
{
	BYTE i, rcnt;

	Printf("Read  [Adrs:%02xh ", (WORD)addr);
	for(i=0; i<argcnt-1; i++)
		Printf(" Index:%02xh ", wrdata[i] );
	Printf("] ");

	rcnt = wrdata[argcnt-1];
	ReadI2Cmn(addr, argcnt-1, rcnt, wrdata);

	for(i=0; i<rcnt; i++)
		Printf("%02xh ", (WORD)wrdata[i]);
}

BYTE MonReadI2C16(BYTE addr, BYTE indexH, BYTE indexL) 
{
	WORD val;

	val = ReadI2C16(addr, indexH, indexL);

	Printf("Read [Adrs%02xh, %02x%02xh] %04xh",(WORD)addr, (WORD)indexH,(WORD)indexL,(WORD)val );
	return val;

}

void MonWriteI2C16(BYTE addr, BYTE indexH, BYTE indexL, BYTE valH, BYTE valL) 
{
	Printf("\r\nWrite %02x%02xh to [Adrs(%02xh)Index(%02x%02xh)]", (WORD)valH, (WORD)valL, (WORD)addr, (WORD)indexH, (WORD)indexL);
	WriteI2C16(addr, indexH, indexL, valH, valL);
}
*/
/*===========================================================================*/
/*		Convert ASCII to Binery                                              */
/*===========================================================================*/
BYTE Asc1Bin(BYTE asc)
{
	if(asc>='0' && asc <='9') return (asc - '0');
	else if(asc>='a' && asc <='f') return (asc - 'a' + 0x0a);
	else if(asc>='A' && asc <='F') return (asc - 'A' + 0x0a);
	else return 0xff;
}

BYTE Asc2Bin(DATA_P BYTE *s)
{
	BYTE bin;
	BYTE bin0;

	bin = 0;
	while(*s != '\0' && *s !=' ') {
		bin = bin<<4;
		if((bin0=Asc1Bin(*s))==0xff)
			return 0xff;
		bin = bin + bin0;
		s++;
	}
	return (bin);
}

void I2CDeviceSet(BYTE addr, CODE_P BYTE *RegSet)
{
	int	cnt=0;
	BYTE index, val;

	// Output discription
	#ifdef TASKING
	while( *RegSet ) 
		RS_tx( *RegSet++ );
	RegSet++;
	#endif

	while ( *RegSet != 0xFF ) {
/*		if( cnt==0 ) {
			addr = *RegSet;

			cnt = *(RegSet+1);
			RegSet+=2;
		}
*/
		index = *RegSet;
		val = *(RegSet+1);
//		MonWriteI2C(addr, index, val);
		tp28xx_byte_write(index, val);

//		Puts("\r\n");

		RegSet+=2;

		cnt--;
	}

	delay(50);
}


/*===========================================================================*/
/*		Help					                                             */
/*===========================================================================*/
void Usage(void)
{
	delay(2);


	Printf("\r\n+------- TP2825B/TP2850 board-Rev%d.%02x-----+", (WORD)FWVER/0x100, (WORD)FWVER%0x100);		
	
	Puts("\r\n| W Index Data [channel]   Write register                 |");	delay(1);
	Puts("\r\n| R Index [channel]        Read register                  |");	delay(1);
	Puts("\r\n| D Index Index            Dump registers                 |");	delay(1);	
	//Puts("\r\n| C Address                Change I2C Address             |");	delay(1);	
	//Puts("\r\n| < >                      Register++,Register--          |");	delay(1);	
	//Puts("\r\n| /                        Repeat previous command        |");	delay(1);
	Puts("\r\n| scanon/scanoff           enable/disable auto detection  |");	delay(1);
//	Puts("\r\n+-----------------------------------------------+");	delay(1);		
}

/*
BYTE Dec2Hex(BYTE val)
{
	BYTE j =1;
	BYTE dat=0,rem;

	while(val != 0){
		rem = val%16;
		val = val/16;
		dat = dat + (rem*j);
//		Printf("\r\nValue = %02d, remain = %02d, data = %02d",(WORD)val,(WORD)rem,(WORD)dat);
		j=j*10;
	}

//	Printf("\r\nLast Value = %02d",(WORD)dat);
	return dat;

}*/

BYTE StringCommand()
{
BYTE *cmds[MaxBuf]  ;
BYTE cnt = 0;
BYTE cmd_ptr=0;
bit eol;
BYTE PTZ_cmd;
BYTE pan_spd=0;
BYTE tilt_spd=0;
PelcoD_cmd PD_cmdset, *PD_cmd, *PD_cmd_sum;
char ret;	
	PD_cmd_sum = &PD_cmdset;
	cmds[cmd_ptr++] = &commdbuf[commdptr];							//first string command
	
	while(commdbuf[commdptr]!=' '&& commdbuf[commdptr] != '\0'){				
		commdptr ++;
		cnt++;
	}

	if(cnt <= 1) {													//one character command
		commdptr = 0;
		return 1;		
	}	

	if(commdbuf[commdptr] == '\0')									//one string command
		eol = 1;
	else{															//multi string command
		eol = 0;
    	commdbuf[commdptr++] = '\0';
	}

	while(!eol){													//subsidiarily string command

		if( commdbuf[commdptr]=='\0' ) {
				eol = 1; break;
		}
		else if(commdbuf[commdptr]==' ')
			commdbuf[commdptr++] = '\0';

		cmds[cmd_ptr++] = &commdbuf[commdptr];
		arg[++argn] = Asc2Bin(&commdbuf[commdptr]);

		while( commdbuf[commdptr]!=' ' && commdbuf[commdptr]!='\0' )
				commdptr++;
	}

	if((!strcmp(cmds[0],"I2C")) || (!strcmp(cmds[0],"i2c"))){
		Printf("\r\nI2C first string");

		if((!strcmp(cmds[1],"ON")) || (!strcmp(cmds[1],"on"))){
			Printf("\r\nI2C second string");
		}
	}
	else if((!strcmp(cmds[0],"SCANON")) || (!strcmp(cmds[0],"scanon"))){
	
			//MonTX(0x17,0x5f,0x00,0x00,0x00,0x00);
			DetAutoStd = 1;
	
	}	
	else if((!strcmp(cmds[0],"SCANOFF")) || (!strcmp(cmds[0],"scanoff"))){
	
			//MonTX(0x17,0x5f,0x00,0x00,0x00,0x00);
			DetAutoStd = 0;
		if(argn == 2)
		{
		  Printf("\r\nsetvideo : %02x %02x", (WORD)arg[1],(WORD)arg[2]);
			Set_VidRes(arg[1], arg[2]);
		}
	}/*
	else if((!strcmp(cmds[0],"BYDTEST")) || (!strcmp(cmds[0],"bydtest"))){
	
			//MonTX(0x17,0x5f,0x00,0x00,0x00,0x00);
			BYDtest = 1;
	
	}*/	
	else if((!strcmp(cmds[0],"MENU")) || (!strcmp(cmds[0],"menu"))){
	
			//MonTX(0x17,0x5f,0x00,0x00,0x00,0x00);
			Menu();
	
	}
	else if((!strcmp(cmds[0],"UP")) || (!strcmp(cmds[0],"up"))){
	
			//MonTX(0x06,0x00,0x00,0x00,0x00,0x00);
			Up();
	
	}
	else if((!strcmp(cmds[0],"DOWN")) || (!strcmp(cmds[0],"down"))){
	
			//MonTX(0x07,0x00,0x00,0x00,0x00,0x00);
			Down();
	
	}
	else if((!strcmp(cmds[0],"LEFT")) || (!strcmp(cmds[0],"left"))){
	
			//MonTX(0x09,0x00,0x00,0x00,0x00,0x00);
			Left();
	
	}
	else if((!strcmp(cmds[0],"RIGHT")) || (!strcmp(cmds[0],"right"))){
	
			//MonTX(0x08,0x00,0x00,0x00,0x00,0x00);
			Right();
	
	}
	else if((!strcmp(cmds[0],"RESET")) || (!strcmp(cmds[0],"reset"))){
	
			//MonTX(0x08,0x00,0x00,0x00,0x00,0x00);
		Reset();
	
	}	
	else if((!strcmp(cmds[0],"XR")) || (!strcmp(cmds[0],"xr"))){
	
		Printf("\r\nXR...");
		ret = -1;
		if((!strcmp(cmds[1],"DATA")) || (!strcmp(cmds[1],"data"))){
			Printf("user data ");
//			ret=xmodemReceive(USER_DATA_UPDATE);
		}	
		else if((!strcmp(cmds[1],"FW")) || (!strcmp(cmds[1],"fw"))){
			Printf("firmware ");
//			ret=xmodemReceive(FIRMWARE_UPDATE);
		}

		else if((!strcmp(cmds[1],"FONT")) || (!strcmp(cmds[1],"font"))){
			Printf("font ");
//			ret=xmodemReceive(FONT_UPDATE);
		}
		
		if(ret >= 0) Printf("\r\nOK");
		else Printf("\r\nFail %d", ret);	
	
	}			

				
	else
			Puts(" <- Command Error!!");
	

	
	Prompt();
	commdptr = 0;
	commdbuf[0]='\0';
	
	return 0;

}



/*===========================================================================*/
/*			          Debug Command Service Routine                          */
/*===========================================================================*/
void DebugKeyIn(BYTE ikey)
{
	BYTE i;

	#ifdef TEST_SERCOM
	#endif //TEST_SERCOM

	bit eol, cerror;
	static bit comment=0;

	//----- if end of loading -----

	//----- if comment, echo back and ignore -----
	if( comment ) {
		if( ikey=='\r' )
			comment = 0;
		else {
			RS_tx(ikey);
			return;
		}
	}
	else if( ikey==';' ) {
		comment = 1;
		RS_tx(ikey);
		return;
	}

	//----- Command Interpret ------------------------------

	if( (ikey=='\r') || (ikey=='/') ) {
		#ifdef TEST_SERCOM
		if(ikey=='\r')
			MaskEcho = 0;
		#endif //TEST_SERCOM
		comment = 0;

		if (ikey == '/') {      // Repeat 
			PutsP(commdbuf);
			commdptr = bptr;
			commdbuf[0]=arg[0];
		}

		commdbuf[commdptr] = '\0';
		
		bptr = commdptr;
		commdptr = 0;
		argn = 0;
		eol	= 0;
		cerror = 0;
		
		while(commdbuf[commdptr]==' ') commdptr++;		// Cut leading space
		if (commdbuf[commdptr]=='\0'){
  			eol = 1;									// Exit, if null command
		}
		
	//	if(!StringCommand()) return;

	//	arg[argn++] = commdbuf[commdptr++];				// Get command

		arg[argn] = commdbuf[commdptr];		//Get first character
		if(!StringCommand()) return;
		argn++; commdptr++;

		while( !cerror && !eol ) {
			if( commdbuf[commdptr]!=' ' && commdbuf[commdptr]!='\0' ) {
				cerror = 1; break;
			}

			while( commdbuf[commdptr]==' ' ) commdptr++;
			if( commdbuf[commdptr]=='\0' ) {
				eol = 1; break;
			}
			arg[argn++] = Asc2Bin(&commdbuf[commdptr]);
			while( commdbuf[commdptr]!=' ' && commdbuf[commdptr]!='\0' ) {
				commdptr++;
			}
		}

		if(I2CInitialBlocking){	
			cerror = 0;
			I2CInitialBlocking = 0;
		}

		if (cerror) {
			Puts(" <- Error!!");
			Prompt();
			commdptr = bptr = 0;
			return;
		}

		//----- Command ---------------------------

		
		switch(arg[0]) {
/*
			case 'j':
			case 'J':
				if( argn==3 ) {
					NewLine();
					arg[2] = MonReadI2C16(I2CAddressDeb, arg[1], arg[2]);
				
				}
				break;

			case 'x':
			case 'X':
				if( argn > 4 ) {
					NewLine();
					MonWriteI2C16(I2CAddressDeb, arg[1], arg[2], arg[3], arg[4]);
				}
				break;
*/			
			case 'w':
			case 'W':
				if(argn == 3) {
//					NewLine();
					MonWriteI2C(I2CAddressDeb, arg[1], arg[2]);	
					delay(1);
					MonReadI2C(I2CAddressDeb, arg[1]);
					
				}

				else if( argn == 4) {
					MonWriteI2C(I2CAddressDeb, 0x40, arg[3]);	
					delay(1);
					MonWriteI2C(I2CAddressDeb, arg[1], arg[2]);
					delay(1);
					MonReadI2C(I2CAddressDeb, arg[1]);				
				}

				break;
			
			case 'r':
			case 'R':
				if( argn==2 ) {
					NewLine();
					arg[2] = MonReadI2C(I2CAddressDeb, arg[1]);
				
				}

				else if( argn == 3) {
					MonWriteI2C(I2CAddressDeb, 0x40, arg[2]);	
					delay(1);
					MonReadI2C(I2CAddressDeb, arg[1]);
				}
/*				
				else if( argn > 3 ) {	// Read several Byte with several index.
										// r cmd1 cmd2 ... rcnt
										// ex) r 10 20 5
										// read 5 bytes from index 1020.
										// Useful for Z86129(CC Decorder).
					NewLine();
					MonReadI2Cmn(I2CAddressDeb, &arg[1], argn-1);
				}
*/
				break;
			
			case 'D':
			case 'd':
				if(argn == 1) {
					arg[1]+=8;
					arg[2] = arg[1]+7;
				}
				else if(argn == 2)
					arg[2] = arg[1]+7;
				for (i=arg[1]; i<=arg[2] && i<0xff; i++) {
					NewLine();
					MonReadI2C(I2CAddressDeb, i);	
				}
				break;

			case 'Z':
			case 'z':
					if(argn > 4) {
 						MonTX(arg[1],arg[2],arg[3],arg[4],arg[5]);
						Printf("\r\nTX : %02x %02x %02x %02x %02x %02x", (WORD)arg[1],(WORD)arg[2],(WORD)arg[3],(WORD)arg[4],(WORD)arg[5]);
					}
					else
					{
						Printf("\r\ntoo few parameter!");
					}
				break;
/*
			case 't':
			case 'T':
				if(argn ==4) {
//					NewLine();
					Montp28xx_byte_write(I2CAddressDeb, 0x40, arg[3]);	
					delay(1);
					Montp28xx_byte_write(I2CAddressDeb, arg[1],arg[2]);
					
				}
				
			
				break;
			
			case 'i':
			case 'I':
				if(argn == 3) {
//					NewLine();
					Montp28xx_byte_write(I2CAddressDeb, 0x40, arg[2]);	
					delay(1);
					Montp28xx_byte_read(I2CAddressDeb, arg[1]);
					
				}
				break;
*/			
			case 'C':	/* Change I2C Address	*/
			case 'c':
				if(argn == 2)
					I2CAddressDeb = arg[1];
				Printf("\r\nI2C address : %02x", (WORD)I2CAddressDeb);
				break;
		
			
			case 'H':
			case 'h':
			case '?':
				Usage();
				break;
			
			}
		
		Prompt();
		commdptr = 0;
		commdbuf[0]='\0';
	}

	//----- 1 byte command ----------------------------
	else {

			switch(ikey) {

			case 0x08:		// back space
				if(commdptr>0) {
					commdbuf[commdptr--]='\0';
					RS_tx(ikey);
					RS_tx(' ');
					RS_tx(ikey);
				}
				break;

			case 0x1B:		// Esc 
				Prompt();
				commdptr = 0;commdbuf[0]='\0';
				break;

			case ',':
			case '<':
				RS_tx('\r');
				MonWriteI2C(I2CAddressDeb, arg[1], --arg[2]);
				MonReadI2C(I2CAddressDeb, arg[1]);

				Prompt();
				commdptr = 0;commdbuf[0]='\0';
				break;

			case '.':
			case '>':
				RS_tx('\r');
				MonWriteI2C(I2CAddressDeb, arg[1], ++arg[2]);
				MonReadI2C(I2CAddressDeb, arg[1]);

				Prompt();
				commdptr = 0;commdbuf[0]='\0';
				break;



			default:
				#ifdef TEST_SERCOM

				if(ikey == '^' || ikey == '$')
 		    		MaskEcho = 1;

				if(!MaskEcho)
				#endif //TEST_SERCOM
				
				RS_tx(ikey);
				commdbuf[commdptr++] = ikey;
				break;
			}
		
	}

}


void InitReset(){
		int t = tm01;

		reset = 0;
		while(t == tm01);
		
//		delay(1);
		reset = 1;
}

BYTE SW_Sel_Resolution(){
/*	
	BYTE res,frme,sys,zone;
	sys = R1080P_n720P;
	frme = R6050f_n3025f;
	zone = RNT_nPAL;

	res = (sys<<2);
	res |=  (frme<<1);
	res |=  zone;		

	return res;*/
	BYTE tmp;
//	tmp = (P1>>5);
	tmp = (P2>>3)&0x07;
	if(tmp > 0x03)       ManVidStd = STD_TVI;
	else                 ManVidStd = STD_HDA;
	
	tmp &= 0x03;
	if(0x00 == tmp)      tmp = TP2802_720P30V2;
	if(0x01 == tmp)      tmp = TP2802_720P25V2;
	if(0x02 == tmp)      tmp = TP2802_1080P30;
	if(0x02 == tmp)      tmp = TP2802_1080P25;	
	
	return tmp;
}

void InitRegisterSet()
{
	
	ManVidRes = SW_Sel_Resolution();
	Printf("\r\nManual format = %02x",(WORD)ManVidRes);
	
	ManSelCh = (P2>>1)&0x03;
	Printf("\r\nManual channel = %02x",(WORD)ManSelCh);
	//IsChannel = ManSelCh;

	if(0==MD0_2) 
	{
		//half_scaler=1;
		//Printf("\r\nHalf mode enable");
		en_tvi960p_H1400=1;
		Printf("\r\nTVI960P 1400X1125 enable");		
	}
	
	if(0==MD0_3)
	{
		en_960P=1;
		Printf("\r\n960P mode enable");
	}
	
	if(0==MD0_0)
	{
		BT1120_out=1;
		Printf("\r\nBT1120 output");
	}
	
	Init_TP_RegSet();

	delay(5);
	Prompt();
		
}

void Main_Initialize()
{

	InitCPU();
	delay(10);
	
//	reset = 0;
	
	InitReset();
	
	commdptr = 0;
//	RS485DE = 0;
//	RS485DI = 1;

	NewLine();
	delay(10);

	InitRegisterSet();
	Usage();
	delay(10);

	Prompt();


}



/*===========================================================================*/
/*                             MAIN PROGRAM                                  */
/*===========================================================================*/

void main (void)
{
//	int ch;
	BYTE status,i;

	Main_Initialize();

	CreateMDIN340VideoInstance();
	//MDIN340();
	I2CAddressDeb = TVII2CAddress;
 	while(1) 
	{	
		
		if(RS_ready())					//----- Check Serial Port	
			DebugKeyIn( RS_rx() );

		//CheckSwitchEvent();
	
		if(timeout) 
		{
			wait_5ms(200);
			if(DetAutoStd) EQ_Detect();
			
			//ReadUTC();
			//if(BYDtest) 
			//MonTX(0xFF, 0x55, 0xaa, 0x0f, 0xf0);
		}
		
	//	if(!DetAutoStd)
		//{
		//	status = tp28xx_byte_read(0x01);
		//	if(0x7a != status)
		//		Printf("\r\nReg01 = : %02x", (WORD)status);	

	//	}
		
		ReadUTC();
		MDIN340();

	}
	
}
