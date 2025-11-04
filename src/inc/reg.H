/* AL8051EX SFR(Special Function Register) */

#ifndef _AL8051EX_H_
#define _AL8051EX_H_


sfr P0      = 0x80 ;   /* reset - FFh */
sfr SP      = 0x81 ;   /* reset - 07h */
sfr DPL     = 0x82 ;   /* reset - 00h */
sfr DPH     = 0x83 ;   /* reset - 00h */
sfr DPL1    = 0x84 ;   /* extension, reset - 00h */
sfr DPH1    = 0x85 ;   /* extension, reset - 00h */
sfr DPS     = 0x86 ;   /* extension, reset - 00h */
sfr PCON    = 0x87 ;   /* reset - 00h */
sfr TCON    = 0x88 ;   /* reset - 00h */
sfr TMOD    = 0x89 ;   /* reset - 00h */
sfr TL0     = 0x8A ;   /* reset - 00h */
sfr TL1     = 0x8B ;   /* reset - 00h */
sfr TH0     = 0x8C ;   /* reset - 00h */
sfr TH1     = 0x8D ;   /* reset - 00h */
sfr DPP     = 0x8E ;   /* extension, reset - 00h */   
sfr STRETCH = 0x8F ;   /* extension, reset - 07h */
sfr P1      = 0x90 ;   /* reset - FFh */
sfr EXIF    = 0x91 ;   /* extension, reset - 00h */
sfr SCON    = 0x98 ;   /* reset - 00h */
sfr SBUF    = 0x99 ;   /* reset - 00h */
sfr P2      = 0xA0 ;   /* reset - FFh */
sfr IE      = 0xA8 ;   /* reset - 00h */
sfr P3      = 0xB0 ;   /* reset - FFh */
sfr IP      = 0xB8 ;   /* reset - 00h */
sfr SCON1   = 0xC0 ;   /* extension, reset - 00h */
sfr SBUF1   = 0xC1 ;   /* extension, reset - 00h */
sfr I2CSA   = 0xC4 ;   /* extension, reset - 00h */
sfr I2CCR   = 0xC5 ;   /* extension, reset - 00h */
sfr I2CBUF  = 0xC6 ;   /* extension, reset - 00h */
sfr I2CTP   = 0xC7 ;   /* extension, reset - 00h */
sfr T2CON   = 0xC8 ;   /* reset - 00h */
sfr TL2     = 0xCC ;   /* reset - 00h */
sfr RCAP2L  = 0xCA ;   /* reset - 00h */
sfr RCAP2H  = 0xCB ;   /* reset - 00h */
sfr TH2     = 0xCD ;   /* reset - 00h */
sfr PSW     = 0xD0 ;   /* reset - 00h */
sfr EIE     = 0xE8 ;   /* extension, reset - 00h */
sfr EICON   = 0xD8 ;   /* extension, reset - 00h */
sfr ACC     = 0xE0 ;   /* reset - 00h */
sfr B       = 0xF0 ;   /* reset - 00h */
sfr EIP     = 0xF8 ;   /* extension, reset - 00h */

/* after reset PC - 0000h, SMOD - 00h */

/* bit addressing */

/* P0(80h) */
sbit P0_0 = 0x80 ;
sbit P0_1 = 0x81 ;
sbit P0_2 = 0x82 ;
sbit P0_3 = 0x83 ;
sbit P0_4 = 0x84 ;
sbit P0_5 = 0x85 ;
sbit P0_6 = 0x86 ;
sbit P0_7 = 0x87 ;

/* TCON(88h) */ 
sbit IT0 = 0x88 ;
sbit IE0 = 0x89 ;
sbit IT1 = 0x8A ;
sbit IE1 = 0x8B ;
sbit TR0 = 0x8C ;
sbit TF0 = 0x8D ;
sbit TR1 = 0x8E ;
sbit TF1 = 0x8F ;

/* P1(90h) */
sbit P1_0 = 0x90 ;
sbit P1_1 = 0x91 ;
sbit P1_2 = 0x92 ;
sbit P1_3 = 0x93 ;
sbit P1_4 = 0x94 ;
sbit P1_5 = 0x95 ;
sbit P1_6 = 0x96 ;
sbit P1_7 = 0x97 ;

/* SCON(98h) */
sbit RI  = 0x98 ;
sbit TI  = 0x99 ;
sbit RB8 = 0x9A ;
sbit TB8 = 0x9B ;
sbit REN = 0x9C ;
sbit SM2 = 0x9D ;
sbit SM1 = 0x9E ;
sbit SM0 = 0x9F ;

/* P2(A0) */
sbit P2_0 = 0xA0 ;
sbit P2_1 = 0xA1 ;
sbit P2_2 = 0xA2 ;
sbit P2_3 = 0xA3 ;
sbit P2_4 = 0xA4 ;
sbit P2_5 = 0xA5 ;
sbit P2_6 = 0xA6 ;
sbit P2_7 = 0xA7 ;

/* IE(A8) */
sbit EX0 = 0xA8 ;
sbit ET0 = 0xA9 ;
sbit EX1 = 0xAA ;
sbit ET1 = 0xAB ;
sbit ES  = 0xAC ;
sbit ES1 = 0xAE ;
sbit EA  = 0xAF ;

/* P3(B0) */
sbit P3_0 = 0xB0 ;
sbit P3_1 = 0xB1 ;
sbit P3_2 = 0xB2 ;
sbit P3_3 = 0xB3 ;
sbit P3_4 = 0xB4 ;
sbit P3_5 = 0xB5 ;
sbit P3_6 = 0xB6 ;
sbit P3_7 = 0xB7 ;

/* IP(B8) */
sbit PX0 = 0xB8 ;
sbit PT0 = 0xB9 ;
sbit PX1 = 0xBA ;
sbit PT1 = 0xBB ;
sbit PS  = 0xBC ;
sbit PS1 = 0xBE ;

/* SCON1(C0) */
sbit RI1 = 0xC0 ;
sbit TI1 = 0xC1 ;

/* T2CON(C8) */
sbit CP_RL2 = 0xC8 ;
sbit C_T2   = 0xC9 ;
sbit TR2    = 0xCA ;
sbit EXEN2  = 0xCB ;
sbit TCLK   = 0xCC ;
sbit RCLK   = 0xCD ;
sbit EXF2   = 0xCE ;
sbit TF2    = 0xCF ;

/* PSW(D0) */
sbit P   = 0xD0 ;
sbit OV  = 0xD2 ;
sbit RS0 = 0xD3 ;
sbit RS1 = 0xD4 ;
sbit F0  = 0xD5 ;
sbit AC  = 0xD6 ;
sbit CY  = 0xD7 ;

/* EICON(D8) */
sbit IE6     = 0xDB ;
sbit RESUME  = 0xDC ;
sbit ERESUME = 0xDD ;
sbit SMOD1   = 0xDF ;

/* ACC(E0) */

/* EIE(E8) */
sbit EINT2 = 0xE8 ;
sbit EINT3 = 0xE9 ;
sbit EINT4 = 0xEA ;
sbit EINT5 = 0xEB ;
sbit EINT6 = 0xEC ;

/* B(F0) */

/* EIP(F8) */
sbit PINT2 = 0xF8 ;
sbit PINT3 = 0xF9 ;
sbit PE4   = 0xFA ;
sbit PE5   = 0xFB ;
sbit PE6   = 0xFC ;

#endif