#ifndef __ISP_REG_H__
#define __ISP_REG_H__


// System Register (0xf0a00 ~ 0xfa5f)
#define		rSYS_MODE		0xfff0		// [7] : fw_sel
						// [6] : sw_reset
#define		rGPD_CTRL		0xfff2		 
#define		rGPC_DIR		0xfff7
#define		rGPD_DIR		0xfffa
#define		rGPC_CTRL		0xfff8

// i2c read register (0xf900 ~ 0xf93f)
#define		rAPP_RDATA0		0xf900
#define		rAPP_RDATA1		0xf901
#define		rAPP_RDATA2		0xf902
#define		rAPP_RDATA3		0xf903
#define		rAPP_RDATA4		0xf904
#define		rAPP_RDATA5		0xf905
#define		rAPP_RDATA6		0xf906
#define		rAPP_RDATA7		0xf907
#define		rAPP_RDATA8		0xf908
#define		rAPP_RDATA9		0xf909
#define		rAPP_RDATA10		0xf90a
#define		rAPP_RDATA11		0xf90b
#define		rAPP_RDATA12		0xf90c
#define		rAPP_RDATA13		0xf90d
#define		rAPP_RDATA14		0xf90e
#define		rAPP_RDATA15		0xf90f
#define		rAPP_RDATA16		0xf910
#define		rAPP_RDATA17		0xf911
#define		rAPP_RDATA18		0xf912
#define		rAPP_RDATA19		0xf913
#define		rAPP_RDATA20		0xf914
#define		rAPP_RDATA21		0xf915
#define		rAPP_RDATA22		0xf916
#define		rAPP_RDATA23		0xf917
#define		rAPP_RDATA24		0xf918
#define		rAPP_RDATA25		0xf919
#define		rAPP_RDATA26		0xf91a
#define		rAPP_RDATA27		0xf91b
#define		rAPP_RDATA28		0xf91c
#define		rAPP_RDATA29		0xf91d
#define		rAPP_RDATA30		0xf91e
#define		rAPP_RDATA31		0xf91f

// 3wire register (0xf940 ~ 0xf95f)
#define		r3W_CTRL		0xf940
#define		r3W_FREQ		0xf941
#define		r3W_ADDR0		0xf942
#define		r3W_ADDR1		0xf943
#define		r3W_DATA0		0xf944
#define		r3W_DATA1		0xf945
#define		r3W_DATA2		0xf946
#define		r3W_DATA3		0xf947
#define		r3W_DATA4		0xf948
#define		r3W_DATA5		0xf949
#define		r3W_DATA6		0xf94a
#define		r3W_DATA7		0xf94b

#define		rN2D_FLAGA		0xf94e
#define		rN2D_FLAGB		0xf94f


//TP2801 registers
#define		rIndex00			0xf800		//Product ID
#define		rIndex01			0xf801		//Freq. register1
#define		rIndex02			0xf802		//Mode control
#define		rIndex03			0xf803		//Mode control Enc
#define		rIndex04			0xf804		//Freq. register2
#define		rIndex05			0xf805		//BSTLN
#define		rIndex06			0xf806		//IO Control
#define		rIndex07			0xf807		//MISC Control
#define		rIndex08			0xf808		//H0 Timing1
#define		rIndex09			0xf809		//SYLO
#define		rIndex0a			0xf80a		//SYHI
#define		rIndex0b			0xf80b		//H0 Timing2
#define		rIndex0c			0xf80c		//H0TVS
#define		rIndex0d			0xf80d		//H0TVD
#define		rIndex0e			0xf80e		//H0TBST
#define		rIndex0f			0xf80f		//HLEN1

#define		rIndex10			0xf810		//HLEN2
#define		rIndex11			0xf811		//HINDLY1
#define		rIndex12			0xf812		//VINDLY
#define		rIndex13			0xf813		//BKLVL
#define		rIndex14			0xf814		//SYPHT
#define		rIndex15			0xf815		//SYNHT
#define		rIndex16			0xf816		//YLMTLI
#define		rIndex17			0xf817		//YLMTLO
#define		rIndex18			0xf818		//YOFFSET
#define		rIndex19			0xf819		//YLMTHI
#define		rIndex1a			0xf81a		//YLMTHO
#define		rIndex1b			0xf81b		//YGAIN
#define		rIndex1c			0xf81c		//UGAIN
#define		rIndex1d			0xf81d		//VGAIN
#define		rIndex1e			0xf81e		//BGAIN
#define		rIndex1f			0xf81f		//TEST

// sensor, regen register (0xf980 ~ 0xf99f)
#define		rSDI_CTRL0		0xf980
#define		rSDI_CTRL1		0xf981
#define		rREG_MAXPH		0xf982
#define		rREG_MAXPL		0xf983
#define		rREG_POSLH		0xf984
#define		rREG_POSLL		0xf985
#define		rREG_POSPH		0xf986
#define		rREG_POSPL		0xf987
#define		rIP_HLENGH		0xf988
#define		rIP_HLENGL		0xf989
#define		rIP_LLENGH		0xf98a
#define		rIP_LLENGL		0xf98b
#define		rSDI_CTRL2		0xf98c

#define		rRFIFO_WPOSH		0xf990
#define		rRFIFO_WPOSL		0xf991
#define		rRFIFO_RPOSH		0xf994
#define		rRFIFO_RPOSL		0xf995
#define		rRFIFO_LENGH		0xf996
#define		rRFIFO_LENGL		0xf997
#define		rFDELAY_NOH       0xf998
#define		rFDELAY_NOL       0xf999

#define		rIP_WR_LENGH   	0xf9a0
#define		rIP_WR_LENGL   	0xf9a1
#define		rIP_RD_LENGH   	0xf9a2
#define		rIP_RD_LENGL   	0xf9a3
#define		rHHH_LENGH   	0xf9a4
#define		rHHH_LENGL   	0xf9a5
#define		rNOP_L_LENGH   	0xf9a6
#define		rNOP_L_LENGL   	0xf9a7

#define		rPWM_CTRL		0xfa10
#define		rPWM_FREQ1		0xfa11
#define		rPWM_FREQ2		0xfa12
#define		rPWM_FREQ3		0xfa13
#define		rPWM_FREQ4		0xfa14
#define		rPWM_FREQ5		0xfa15
#define		rPWM_FREQ6		0xfa16
#define		rPWM_DUTY1		0xfa17
#define		rPWM_DUTY2		0xfa18
#define		rPWM_DUTY3		0xfa19
#define		rPWM_DUTY4		0xfa1a
#define		rPWM_DUTY5		0xfa1b
#define		rPWM_DUTY6		0xfa1c

#define		rFRONT_CTRL	  0xfa20
#define		rEND_CTRL0		0xfa21
#define		rEND_CTRL1		0xfa22
//  			isp_decifil_on(flag)	   	rEND_CTRL1.7
//  			isp_yfil_onoff(flag)   		 	rEND_CTRL1.6
//  			isp_APSSW(flag)		         	rEND_CTRL1.5
//  			isp_APSTH(flag)   		 			rEND_CTRL1.4
//  			isp_enhence_onoff(flag)			rEND_CTRL1.3
//  			isp_lowfil_onoff(flag)   	 	rEND_CTRL1.1~0

#define		rEND_CTRL2    0xfa23
#define		rEND_CTRL3    0xfa24
#define		rEND_CTRL4		0xfa25
#define		rEND_CTRL5    0xfa26
#define		rEND_CTRL6    0xfa27
#define		rSEPHIA_CR		0xfa28
#define		rSEPHIA_CB		0xfa29

#define		rI2CS_ADDR_BUF		0xfa30		// added, 2007.5.29
#define		rI2CS_DATA_BUF		0xfa31
#define		rI2CS_CHIP_BUF		0xfa32

#define		rPRODUCTP_ID		0xfa33
#define		rVERSION		0xfa34
#define		rISP_CHIP_ID		0xfa35

#define		rDAC_CTRL		0xfa36
#define		rDAC_DINA		0xfa37
#define		rDAC_DINB		0xfa38
#define		rFONT_WCTRL		0xfa39		// [4] : font_sel  (0:eng(128), 1:other(256))
						// [3] : font_down (0:font down, 1:isp run)
						// [2] : font_en
						// [1] : font_we
						// [0] : font_clk
                 
// Isp Front Register (0xfb00 ~ 0xfb4F)
#define   rCLP_GRH		0xfb00
#define   rCLP_GRL		0xfb01
#define	  rCLP_BH			0xfb02
#define	  rCLP_BL			0xfb03
#define	  rCLP_RH			0xfb04
#define	  rCLP_RL			0xfb05
#define 	rCLP_GBH		0xfb06
#define 	rCLP_GBL		0xfb07

#define   rFGAIN_GRH		0xfb08
#define   rFGAIN_GRL		0xfb09
#define	  rFGAIN_BH			0xfb0a
#define	  rFGAIN_BL			0xfb0b
#define	  rFGAIN_RH			0xfb0c
#define	  rFGAIN_RL			0xfb0d
#define 	rFGAIN_GBH		0xfb0e
#define 	rFGAIN_GBL		0xfb0f

#define		rDPGA_GAINH    0xfb10
#define		rDPGA_GAINL    0xfb11

#define 	rAWB_GAIN_RH		0xfb12
#define 	rAWB_GAIN_RL		0xfb13
#define 	rAWB_GAIN_GH		0xfb14
#define 	rAWB_GAIN_GL		0xfb15
#define 	rAWB_GAIN_BH		0xfb16
#define 	rAWB_GAIN_BL		0xfb17

#define 	rRESI_THOLDH		0xfb18
#define 	rRESI_THOLDL		0xfb19
#define 	rSHAD_PARA1H		0xfb1a
#define 	rSHAD_PARA1L		0xfb1b
#define 	rSHAD_PARA2H		0xfb1c
#define 	rSHAD_PARA2L		0xfb1d
#define 	rX_CENTERH		0xfb1e
#define 	rX_CENTERL		0xfb1f
#define 	rY_CENTERH		0xfb20
#define 	rY_CENTERL		0xfb21

#define		rBRIGHT_GAIN			0xfb38

#define		rCUT_CTRLH		0xfb40
#define		rCUT_CTRLL		0xfb41
#define		rCUT_TH			0xfb42
#define		rCUT_Y			0xfb43
#define		rCUT_CB			0xfb44
#define		rCUT_CR			0xfb45
#define		rCONT_LEVEL		0xfb49
#define		rCUT_CNTH		0xfb50
#define		rCUT_CNTL		0xfb51
#
#define		rWDR_MIX_SEL		0xfb72
#define		rWDR_GLOBAL_SEL	0xfb73
#define		rWDR_LOCAL_SEL		0xfb74
#define		rWDR_MASK_SXH		0xfb76
#define		rWDR_MASK_SXL		0xfb77
#define		rWDR_MASK_EXH		0xfb78
#define		rWDR_MASK_EXL		0xfb79
#define		rWDR_MASK_SYH		0xfb7a
#define		rWDR_MASK_SYL		0xfb7b
#define		rWDR_MASK_EYH		0xfb7c
#define		rWDR_MASK_EYL		0xfb7d

#define		rWB_MAX1H		0xfb80		// b1G[9:8]
#define		rWB_MAX1L		0xfb81		// b1G[7:0]
#define		rWB_MAX2H		0xfb82
#define		rWB_MAX2L		0xfb83
#define		rWB_MAX3H		0xfb84
#define		rWB_MAX3L		0xfb85
#define		rWB_MAX4H		0xfb86
#define		rWB_MAX4L		0xfb87
#define		rWB_MAX5H		0xfb88
#define		rWB_MAX5L		0xfb89
#define		rWB_MAX6H		0xfb8a
#define		rWB_MAX6L		0xfb8b
#define		rWB_MAX7H		0xfb8c
#define		rWB_MAX7L		0xfb8d
#define		rWB_MAX8H		0xfb8e
#define		rWB_MAX8L		0xfb8f
#define		rWB_MAX9H		0xfb90
#define		rWB_MAX9L		0xfb91
#define		rWB_MAX10H		0xfb92
#define		rWB_MAX10L		0xfb93
#define		rWB_MAX11H		0xfb94
#define		rWB_MAX11L		0xfb95
#define		rWB_MAX12H		0xfb96
#define		rWB_MAX12L		0xfb97
#define		rWB_MAX13H		0xfb98
#define		rWB_MAX13L		0xfb99
#define		rWB_MAX14H		0xfb9a
#define		rWB_MAX14L		0xfb9b
#define		rWB_MAX15H		0xfb9c
#define		rWB_MAX15L		0xfb9d
#define		rWB_MAX16H		0xfb9e
#define		rWB_MAX16L		0xfb9f
#define		rWB_MAX17H		0xfba0
#define		rWB_MAX17L		0xfba1
#define		rWB_MAX18H		0xfba2
#define		rWB_MAX18L		0xfba3
#define		rWB_MAX19H		0xfba4
#define		rWB_MAX19L		0xfba5

#define		rVENC_INITNO		0xfbc0
#define		rVENC_INITPIXNOH		0xfbc2
#define		rVENC_INITPIXNOL		0xfbc3
#define		rVENC_BRIGHT		0xfbc6
#define		rVENC_CONTRAST		0xfbc7
#define		rVENC_SATURATION	0xfbc8
#define		rVENC_HUE		0xfbc9
#define		rVENC_MODE0		0xfbca
#define		rVENC_MODE1		0xfbcb
#define		rVENC_MODE2		0xfbcc
#define		rVENC_MODE3		0xfbcd
#define		rVENC_REG		0xfbce



// Isp End Register (0xfc00 ~ 0xfcFF)

#define		rCGR1           	0xfc10
#define		rCGB1           	0xfc11
#define		rCGRH1      		0xfc12
#define		rCGBH1      		0xfc13
#define		rCGR2       		0xfc14
#define		rCGB2       		0xfc15
#define		rCGRH2      		0xfc16
#define		rCGBH2      		0xfc17
#define		rCGR3       		0xfc18
#define		rCGB3       		0xfc19
#define		rCGRH3      		0xfc1a
#define		rCGBH3      		0xfc1b
#define		rCGR4       		0xfc1c
#define		rCGB4       		0xfc1d
#define		rCGRH4      		0xfc1e
#define		rCGBH4      		0xfc1f

#define		rVCGR0      		0xfc20
#define		rVCGB0      		0xfc21
#define		rVCGR1      		0xfc22
#define		rVCGB1      		0xfc23
#define		rVCGR2      		0xfc24
#define		rVCGB2      		0xfc25
#define		rVCGR3      		0xfc26
#define		rVCGB3      		0xfc27
#define		rVCGR4      		0xfc28
#define		rVCGB4      		0xfc29

#define		rCGRD0H      		0xfc30
#define		rCGRD0L      		0xfc31
#define		rCGBD0H      		0xfc32
#define		rCGBD0L      		0xfc33
#define		rCGRD1H      		0xfc34
#define		rCGRD1L      		0xfc35
#define		rCGBD1H      		0xfc36
#define		rCGBD1L      		0xfc37
#define		rCGRD2H      		0xfc38
#define		rCGRD2L      		0xfc39
#define		rCGBD2H      		0xfc3a
#define		rCGBD2L      		0xfc3b
#define		rCGRD3H      		0xfc3c
#define		rCGRD3L      		0xfc3d
#define		rCGBD3H      		0xfc3e
#define		rCGBD3L      		0xfc3f
#define		rCGRD4H      		0xfc40
#define		rCGRD4L      		0xfc41
#define		rCGBD4H      		0xfc42
#define		rCGBD4L      		0xfc43

#define		rCRTHY1     		0xfc44
#define		rCBTHY1     		0xfc45
#define		rCRTHY2     		0xfc46
#define		rCBTHY2     		0xfc47
#define		rCRTHY3     		0xfc48
#define		rCBTHY3     		0xfc49
#define		rCRTHY4     		0xfc4a
#define		rCBTHY4     		0xfc4b


#define		rWIN_X0H		0xfc50
#define		rWIN_X0L		0xfc51
#define		rWIN_X1H		0xfc52
#define		rWIN_X1L		0xfc53
#define		rWIN_X2H		0xfc54
#define		rWIN_X2L		0xfc55
#define		rWIN_X3H		0xfc56
#define		rWIN_X3L		0xfc57
#define		rWIN_X4H		0xfc58
#define		rWIN_X4L		0xfc59
#define		rWIN_X5H		0xfc5a
#define		rWIN_X5L		0xfc5b
#define		rWIN_X6H		0xfc5c
#define		rWIN_X6L		0xfc5d
#define		rWIN_X7H		0xfc5e
#define		rWIN_X7L		0xfc5f
#define		rWIN_Y0H		0xfc60
#define		rWIN_Y0L		0xfc61
#define		rWIN_Y1H		0xfc62
#define		rWIN_Y1L		0xfc63
#define		rWIN_Y2H		0xfc64
#define		rWIN_Y2L		0xfc65
#define		rWIN_Y3H		0xfc66
#define		rWIN_Y3L		0xfc67
#define		rWIN_Y4H		0xfc68
#define		rWIN_Y4L		0xfc69
#define		rWIN_Y5H		0xfc6a
#define		rWIN_Y5L		0xfc6b
#define		rWIN_Y6H		0xfc6c
#define		rWIN_Y6L		0xfc6d
#define		rWIN_Y7H		0xfc6e
#define		rWIN_Y7L		0xfc6f
#define		rRECT_SXH	0xfc70
#define		rRECT_SXL	0xfc71
#define		rRECT_SYH	0xfc72
#define		rRECT_SYL	0xfc73
#define		rRECT_EXH	0xfc74
#define		rRECT_EXL	0xfc75
#define		rRECT_EYH	0xfc76
#define		rRECT_EYL	0xfc77
#define		rFILL_SXH	0xfc78
#define		rFILL_SXL	0xfc79
#define		rFILL_SYH	0xfc7a
#define		rFILL_SYL	0xfc7b
#define		rFILL_EXH	0xfc7c
#define		rFILL_EXL	0xfc7d
#define		rFILL_EYH	0xfc7e
#define		rFILL_EYL	0xfc7f
#define		rWIN_FLAGX	0xfc80
#define		rWIN_FLAGY	0xfc81

//#define		rWIN_FLAGRF		0xfc82
#define		rWIN_Y			0xfc83
#define		rWIN_CB			0xfc84
#define		rWIN_CR			0xfc85

#define		rWIN_CB1		   0xfc92
#define		rWIN_CR1		   0xfc93
#define		rWIN_CB2		   0xfc94
#define		rWIN_CR2		   0xfc95
#define		rFILL_SX1H		0xfc96
#define		rFILL_SX1L		0xfc97
#define		rFILL_SY1H		0xfc98
#define		rFILL_SY1L		0xfc99
#define		rFILL_EX1H		0xfc9a
#define		rFILL_EX1L		0xfc9b
#define		rFILL_EY1H		0xfc9c
#define		rFILL_EY1L		0xfc9d
#define		rFILL_SX2H		0xfc9e
#define		rFILL_SX2L		0xfc9f
#define		rFILL_SY2H		0xfca0
#define		rFILL_SY2L		0xfca1
#define		rFILL_EX2H		0xfca2
#define		rFILL_EX2L		0xfca3
#define		rFILL_EY2H		0xfca4
#define		rFILL_EY2L		0xfca5

/********************************************/
#define		rCFILL_SX1H		0xfcb0
#define		rCFILL_SX1L		0xfcb1
#define		rCFILL_SY1H		0xfcb2
#define		rCFILL_SY1L		0xfcb3
#define		rCFILL_EX1H		0xfcb4
#define		rCFILL_EX1L		0xfcb5
#define		rCFILL_EY1H		0xfcb6
#define		rCFILL_EY1L		0xfcb7
#define		rCFILL_SX2H		0xfcb8
#define		rCFILL_SX2L		0xfcb9
#define		rCFILL_SY2H		0xfcba
#define		rCFILL_SY2L		0xfcbb
#define		rCFILL_EX2H		0xfcbc
#define		rCFILL_EX2L		0xfcbd
#define		rCFILL_EY2H		0xfcbe
#define		rCFILL_EY2L		0xfcbf
/********************************************/

// Isp Gamma Register (0xfd00 ~ 0xfd67)
#define		rGAMMA_1H		0xfd00		// b1R[9:8]
#define		rGAMMA_1L		0xfd01		// b1R[7:0]
#define		rGAMMA_2H		0xfd02
#define		rGAMMA_2L		0xfd03
#define		rGAMMA_3H		0xfd04
#define		rGAMMA_3L		0xfd05
#define		rGAMMA_4H		0xfd06
#define		rGAMMA_4L		0xfd07
#define		rGAMMA_5H		0xfd08
#define		rGAMMA_5L		0xfd09
#define		rGAMMA_6H		0xfd0a
#define		rGAMMA_6L		0xfd0b
#define		rGAMMA_7H		0xfd0c
#define		rGAMMA_7L		0xfd0d
#define		rGAMMA_8H		0xfd0e
#define		rGAMMA_8L		0xfd0f
#define		rGAMMA_9H		0xfd10
#define		rGAMMA_9L		0xfd11
#define		rGAMMA_10H		0xfd12
#define		rGAMMA_10L		0xfd13
#define		rGAMMA_11H		0xfd14
#define		rGAMMA_11L		0xfd15
#define		rGAMMA_12H		0xfd16
#define		rGAMMA_12L		0xfd17
#define		rGAMMA_13H		0xfd18
#define		rGAMMA_13L		0xfd19

#define		rGAMMA_1RH		0xfd1a		// b1R[9:8]
#define		rGAMMA_1RL		0xfd1b		// b1R[7:0]
#define		rGAMMA_2RH		0xfd1c
#define		rGAMMA_2RL		0xfd1d
#define		rGAMMA_3RH		0xfd1e
#define		rGAMMA_3RL		0xfd1f
#define		rGAMMA_4RH		0xfd20
#define		rGAMMA_4RL		0xfd21
#define		rGAMMA_5RH		0xfd22
#define		rGAMMA_5RL		0xfd23
#define		rGAMMA_6RH		0xfd24
#define		rGAMMA_6RL		0xfd25
#define		rGAMMA_7RH		0xfd26
#define		rGAMMA_7RL		0xfd27
#define		rGAMMA_8RH		0xfd28
#define		rGAMMA_8RL		0xfd29
#define		rGAMMA_9RH		0xfd2a
#define		rGAMMA_9RL		0xfd2b
#define		rGAMMA_10RH		0xfd2c
#define		rGAMMA_10RL		0xfd2d
#define		rGAMMA_11RH		0xfd2e
#define		rGAMMA_11RL		0xfd2f
#define		rGAMMA_12RH		0xfd30
#define		rGAMMA_12RL		0xfd31
#define		rGAMMA_13RH		0xfd32
#define		rGAMMA_13RL		0xfd33

#define		rGAMMA_1GH		0xfd34		// b1R[9:8]
#define		rGAMMA_1GL		0xfd35		// b1R[7:0]
#define		rGAMMA_2GH		0xfd36
#define		rGAMMA_2GL		0xfd37
#define		rGAMMA_3GH		0xfd38
#define		rGAMMA_3GL		0xfd39
#define		rGAMMA_4GH		0xfd3a
#define		rGAMMA_4GL		0xfd3b	
#define		rGAMMA_5GH		0xfd3c
#define		rGAMMA_5GL		0xfd3d
#define		rGAMMA_6GH		0xfd3e
#define		rGAMMA_6GL		0xfd3f
#define		rGAMMA_7GH		0xfd40
#define		rGAMMA_7GL		0xfd41
#define		rGAMMA_8GH		0xfd42
#define		rGAMMA_8GL		0xfd43
#define		rGAMMA_9GH		0xfd44
#define		rGAMMA_9GL		0xfd45
#define		rGAMMA_10GH		0xfd46
#define		rGAMMA_10GL		0xfd47
#define		rGAMMA_11GH		0xfd48
#define		rGAMMA_11GL		0xfd49
#define		rGAMMA_12GH		0xfd4a
#define		rGAMMA_12GL		0xfd4b
#define		rGAMMA_13GH		0xfd4c
#define		rGAMMA_13GL		0xfd4d

#define		rGAMMA_1BH		0xfd4e		// b1R[9:8]
#define		rGAMMA_1BL		0xfd4f		// b1R[7:0]
#define		rGAMMA_2BH		0xfd50
#define		rGAMMA_2BL		0xfd51
#define		rGAMMA_3BH		0xfd52
#define		rGAMMA_3BL		0xfd53
#define		rGAMMA_4BH		0xfd54
#define		rGAMMA_4BL		0xfd55
#define		rGAMMA_5BH		0xfd56
#define		rGAMMA_5BL		0xfd57
#define		rGAMMA_6BH		0xfd58
#define		rGAMMA_6BL		0xfd59
#define		rGAMMA_7BH		0xfd5a
#define		rGAMMA_7BL		0xfd5b
#define		rGAMMA_8BH		0xfd5c
#define		rGAMMA_8BL		0xfd5d
#define		rGAMMA_9BH		0xfd5e
#define		rGAMMA_9BL		0xfd5f
#define		rGAMMA_10BH		0xfd60
#define		rGAMMA_10BL		0xfd61
#define		rGAMMA_11BH		0xfd62
#define		rGAMMA_11BL		0xfd63
#define		rGAMMA_12BH		0xfd64
#define		rGAMMA_12BL		0xfd65
#define		rGAMMA_13BH		0xfd66
#define		rGAMMA_13BL		0xfd67

#define		rEDGE_LEVEL 	0xfd68		// b1R[9:8]
#define		rEDGE_SUPTH 	0xfd69		// b1R[7:0]
#define		rEDGE_TH0	  	0xfd6a
#define		rEDGE_TH1	  	0xfd6b
#define		rEDGE_TH2	  	0xfd6c
#define		rEDGE_TH3	  	0xfd6d
#define		rEDGE_TH4	  	0xfd6e
#define		rEDGE_TH5	  	0xfd6f
#define		rEDGE_TH6	  	0xfd70
#define		rEDGE_TH7	  	0xfd71
#define		rEDGE_TH8	  	0xfd72
#define		rEDGE_VAL0		0xfd73
#define		rEDGE_VAL1		0xfd74
#define		rEDGE_VAL2		0xfd75
#define		rEDGE_VAL3		0xfd76
#define		rEDGE_VAL4		0xfd77
#define		rEDGE_VAL5		0xfd78
#define		rEDGE_VAL6		0xfd79
#define		rEDGE_VAL7		0xfd7a
#define		rEDGE_VAL8		0xfd7b
#define		rEDGE_VAL9		0xfd7c 

//      Privacy (0xfd80 ~ 0xfddf)
#define		rPRIV_CON		0xfd80
#define		rPRIV_Y0		0xfd82
#define		rPRIV_CR0		0xfd83
#define		rPRIV_CB0		0xfd84
#define		rPRIV_Y1		0xfd85
#define		rPRIV_CR1		0xfd86
#define		rPRIV_CB1		0xfd87
#define		rPRIV_Y2		0xfd88
#define		rPRIV_CR2		0xfd89
#define		rPRIV_CB2		0xfd8a
#define		rPRIV_Y3		0xfd8b
#define		rPRIV_CR3		0xfd8c
#define		rPRIV_CB3		0xfd8d
#define		rPRIV_Y4		0xfd8e
#define		rPRIV_CR4		0xfd8f
#define		rPRIV_CB4		0xfd90
#define		rPRIV_Y5		0xfd91
#define		rPRIV_CR5		0xfd92
#define		rPRIV_CB5		0xfd93
#define		rPRIV_Y6		0xfd94
#define		rPRIV_CR6		0xfd95
#define		rPRIV_CB6		0xfd96
#define		rPRIV_Y7		0xfd97
#define		rPRIV_CR7		0xfd98
#define		rPRIV_CB7		0xfd99

#define		rPRIV_SX0H		0xfda0
#define		rPRIV_SX0L		0xfda1
#define		rPRIV_EX0H		0xfda2
#define		rPRIV_EX0L		0xfda3
#define		rPRIV_SY0H		0xfda4
#define		rPRIV_SY0L		0xfda5
#define		rPRIV_EY0H		0xfda6
#define		rPRIV_EY0L		0xfda7
#define		rPRIV_SX1H		0xfda8
#define		rPRIV_SX1L		0xfda9
#define		rPRIV_EX1H		0xfdaa
#define		rPRIV_EX1L		0xfdab
#define		rPRIV_SY1H		0xfdac
#define		rPRIV_SY1L		0xfdad
#define		rPRIV_EY1H		0xfdae
#define		rPRIV_EY1L		0xfdaf
#define		rPRIV_SX2H		0xfdb0
#define		rPRIV_SX2L		0xfdb1
#define		rPRIV_EX2H		0xfdb2
#define		rPRIV_EX2L		0xfdb3
#define		rPRIV_SY2H		0xfdb4
#define		rPRIV_SY2L		0xfdb5
#define		rPRIV_EY2H		0xfdb6
#define		rPRIV_EY2L		0xfdb7
#define		rPRIV_SX3H		0xfdb8
#define		rPRIV_SX3L		0xfdb9
#define		rPRIV_EX3H		0xfdba
#define		rPRIV_EX3L		0xfdbb
#define		rPRIV_SY3H		0xfdbc
#define		rPRIV_SY3L		0xfdbd
#define		rPRIV_EY3H		0xfdbe
#define		rPRIV_EY3L		0xfdbf
#define		rPRIV_SX4H		0xfdc0
#define		rPRIV_SX4L		0xfdc1
#define		rPRIV_EX4H		0xfdc2
#define		rPRIV_EX4L		0xfdc3
#define		rPRIV_SY4H		0xfdc4
#define		rPRIV_SY4L		0xfdc5
#define		rPRIV_EY4H		0xfdc6
#define		rPRIV_EY4L		0xfdc7
#define		rPRIV_SX5H		0xfdc8
#define		rPRIV_SX5L		0xfdc9
#define		rPRIV_EX5H		0xfdca
#define		rPRIV_EX5L		0xfdcb
#define		rPRIV_SY5H		0xfdcc
#define		rPRIV_SY5L		0xfdcd
#define		rPRIV_EY5H		0xfdce
#define		rPRIV_EY5L		0xfdcf
#define		rPRIV_SX6H		0xfdd0
#define		rPRIV_SX6L		0xfdd1
#define		rPRIV_EX6H		0xfdd2
#define		rPRIV_EX6L		0xfdd3
#define		rPRIV_SY6H		0xfdd4
#define		rPRIV_SY6L		0xfdd5
#define		rPRIV_EY6H		0xfdd6
#define		rPRIV_EY6L		0xfdd7
#define		rPRIV_SX7H		0xfdd8
#define		rPRIV_SX7L		0xfdd9
#define		rPRIV_EX7H		0xfdda
#define		rPRIV_EX7L		0xfddb
#define		rPRIV_SY7H		0xfddc
#define		rPRIV_SY7L		0xfddd
#define		rPRIV_EY7H		0xfdde
#define		rPRIV_EY7L		0xfddf


// Isp Histo Register (0xfde0 ~ 0xfdfF)
#define		rHISTO1H		0xfde0		// b1B[9:8]
#define		rHISTO1L		0xfde1		// b1B[7:0]
#define		rHISTO2H		0xfde2
#define		rHISTO2L		0xfde3
#define		rHISTO3H		0xfde4
#define		rHISTO3L		0xfde5
#define		rHISTO4H		0xfde6
#define		rHISTO4L		0xfde7
#define		rHISTO5H		0xfde8
#define		rHISTO5L		0xfde9
#define		rHISTO6H		0xfdea
#define		rHISTO6L		0xfdeb
#define		rHISTO7H		0xfdec
#define		rHISTO7L		0xfded
#define		rHISTO8H		0xfdee
#define		rHISTO8L		0xfdef
#define		rHISTO9H		0xfdf0
#define		rHISTO9L		0xfdf1
#define		rHISTO10H	0xfdf2
#define		rHISTO10L	0xfdf3
#define		rHISTO11H	0xfdf4
#define		rHISTO11L	0xfdf5
#define		rHISTO12H	0xfdf6
#define		rHISTO12L	0xfdf7
#define		rHISTO13H	0xfdf8
#define		rHISTO13L	0xfdf9
#define		rHISTO14H	0xfdfa
#define		rHISTO14L	0xfdfb
#define		rHISTO15H	0xfdfc
#define		rHISTO15L	0xfdfd
#define		rHISTO16H	0xfdfe
#define		rHISTO16L	0xfdff


// Isp 3A Window Register (0xfe00 ~ 0xfe7F)
#define 	rAF_WIN_SX1		0xfe00
#define 	rAF_WIN_SY1		0xfe01
#define 	rAF_WIN_EX1		0xfe02
#define 	rAF_WIN_EY1		0xfe03
#define 	rAF_WIN_SX2		0xfe04
#define 	rAF_WIN_SY2		0xfe05
#define 	rAF_WIN_EX2		0xfe06
#define 	rAF_WIN_EY2		0xfe07

#define 	rAE_WIN_EX0 		0xfe40
#define 	rAE_WIN_EY0 		0xfe41
#define 	rAE_WIN_SX1 		0xfe42
#define 	rAE_WIN_SY1 		0xfe43
#define 	rAE_WIN_EX1 		0xfe44
#define 	rAE_WIN_EY1 		0xfe45
#define 	rAE_WIN_SX2 		0xfe46
#define 	rAE_WIN_SY2 		0xfe47
#define 	rAE_WIN_EX2 		0xfe48
#define 	rAE_WIN_EY2 		0xfe49

#define 	rWB_WIN_EX0 		0xfe4a
#define 	rWB_WIN_EY0 		0xfe4b
#define 	rWB_WIN_SX1 		0xfe4c
#define 	rWB_WIN_SY1 		0xfe4d
#define 	rWB_WIN_EX1 		0xfe4e
#define 	rWB_WIN_EY1 		0xfe4f
#define 	rWB_WIN_SX2 		0xfe50
#define 	rWB_WIN_SY2 		0xfe51
#define 	rWB_WIN_EX2 		0xfe52
#define 	rWB_WIN_EY2 		0xfe53
#define 	rWB_WIN_SX3 		0xfe54
#define 	rWB_WIN_SY3 		0xfe55
#define 	rWB_WIN_EX3 		0xfe56
#define 	rWB_WIN_EY3 		0xfe57

#define 	rAWB_SUMRH		0xfe58
#define 	rAWB_SUMRL		0xfe59
#define 	rAWB_SUMGH		0xfe5a
#define 	rAWB_SUMGL		0xfe5b
#define 	rAWB_SUMBH		0xfe5c
#define 	rAWB_SUMBL		0xfe5d

#define 	rAWB_SUM1RH		0xfe5e
#define 	rAWB_SUM1RL		0xfe5f
#define 	rAWB_SUM1GH		0xfe60
#define 	rAWB_SUM1GL		0xfe61
#define 	rAWB_SUM1BH		0xfe62
#define 	rAWB_SUM1BL		0xfe63

#define 	rAWB_SUM2RH		0xfe64
#define 	rAWB_SUM2RL		0xfe65
#define 	rAWB_SUM2GH		0xfe66
#define 	rAWB_SUM2GL		0xfe67
#define 	rAWB_SUM2BH		0xfe68
#define 	rAWB_SUM2BL		0xfe69

#define 	rAWB_SUM3RH		0xfe6a
#define 	rAWB_SUM3RL		0xfe6b
#define 	rAWB_SUM3GH		0xfe6c
#define 	rAWB_SUM3GL		0xfe6d
#define 	rAWB_SUM3BH		0xfe6e
#define 	rAWB_SUM3BL		0xfe6f

#define 	rAE_SUMH  		0xfe70
#define 	rAE_SUML  		0xfe71
#define 	rAE_SUM1H  		0xfe72
#define 	rAE_SUM1L  		0xfe73
#define 	rAE_SUM2H  		0xfe74
#define 	rAE_SUM2L  		0xfe75

#define 	rAE_SUMBLCH  		0xfe76
#define 	rAE_SUMBLCL  		0xfe77

#define		rBLC_SXH		0xfe78
#define		rBLC_SYH		0xfe7a
#define		rBLC_EXH		0xfe7c
#define		rBLC_EYH		0xfe7e


#define 	rAF_SUM1AH		0xfcc0 
#define 	rAF_SUM1AL		0xfcc1
#define 	rAF_SUM1BH		0xfcc2
#define 	rAF_SUM1BL		0xfcc3
#define 	rAF_SUM2AH		0xfcc4 
#define 	rAF_SUM2AL		0xfcc5
#define 	rAF_SUM2BH		0xfcc6
#define 	rAF_SUM2BL		0xfcc7

// OSD Register (0xfe80 ~ 0xffff)
#define         rOSD_POSX0              0xfe83
#define         rOSD_POSY0              0xfe84
#define         rOSD_DATA0_0            0xfe85
#define         rOSD_DATA0_1            0xfe86
#define         rOSD_DATA0_2            0xfe87
#define         rOSD_DATA0_3            0xfe88
#define         rOSD_DATA0_4            0xfe89
#define         rOSD_DATA0_5            0xfe8a
#define         rOSD_DATA0_6            0xfe8b
#define         rOSD_DATA0_7            0xfe8c
#define         rOSD_DATA0_8            0xfe8d
#define         rOSD_DATA0_9            0xfe8e
#define         rOSD_DATA0_10           0xfe8f
#define         rOSD_DATA0_11           0xfe90
#define         rOSD_DATA0_12           0xfe91
#define         rOSD_DATA0_13           0xfe92
#define         rOSD_DATA0_14           0xfe93
#define         rOSD_DATA0_15           0xfe94
#define         rOSD_DATA0_16           0xfe95
#define         rOSD_DATA0_17           0xfe96
#define         rOSD_DATA0_18           0xfe97
#define         rOSD_DATA0_19           0xfe98
#define         rOSD_DATA0_20           0xfe99
#define         rOSD_DATA0_21           0xfe9a
#define         rOSD_DATA0_22           0xfe9b
#define         rOSD_DATA0_23           0xfe9c
#define         rOSD_POSX1              0xfe9f
#define         rOSD_POSY1              0xfea0
#define         rOSD_DATA1_0            0xfea1
#define         rOSD_DATA1_1            0xfea2
#define         rOSD_DATA1_2            0xfea3
#define         rOSD_DATA1_3            0xfea4
#define         rOSD_DATA1_4            0xfea5
#define         rOSD_DATA1_5            0xfea6
#define         rOSD_DATA1_6            0xfea7
#define         rOSD_DATA1_7            0xfea8
#define         rOSD_DATA1_8            0xfea9
#define         rOSD_DATA1_9            0xfeaa
#define         rOSD_DATA1_10           0xfeab
#define         rOSD_DATA1_11           0xfeac
#define         rOSD_DATA1_12           0xfead
#define         rOSD_DATA1_13           0xfeae
#define         rOSD_DATA1_14           0xfeaf
#define         rOSD_DATA1_15           0xfeb0
#define         rOSD_DATA1_16           0xfeb1
#define         rOSD_DATA1_17           0xfeb2
#define         rOSD_DATA1_18           0xfeb3
#define         rOSD_DATA1_19           0xfeb4
#define         rOSD_DATA1_20           0xfeb5
#define         rOSD_DATA1_21           0xfeb6
#define         rOSD_DATA1_22           0xfeb7
#define         rOSD_DATA1_23           0xfeb8
#define         rOSD_POSX2              0xfebb
#define         rOSD_POSY2              0xfebc
#define         rOSD_DATA2_0            0xfebd
#define         rOSD_DATA2_1            0xfebe
#define         rOSD_DATA2_2            0xfebf
#define         rOSD_DATA2_3            0xfec0
#define         rOSD_DATA2_4            0xfec1
#define         rOSD_DATA2_5            0xfec2
#define         rOSD_DATA2_6            0xfec3
#define         rOSD_DATA2_7            0xfec4
#define         rOSD_DATA2_8            0xfec5
#define         rOSD_DATA2_9            0xfec6
#define         rOSD_DATA2_10           0xfec7
#define         rOSD_DATA2_11           0xfec8
#define         rOSD_DATA2_12           0xfec9
#define         rOSD_DATA2_13           0xfeca
#define         rOSD_DATA2_14           0xfecb
#define         rOSD_DATA2_15           0xfecc
#define         rOSD_DATA2_16           0xfecd
#define         rOSD_DATA2_17           0xfece
#define         rOSD_DATA2_18           0xfecf
#define         rOSD_DATA2_19           0xfed0
#define         rOSD_DATA2_20           0xfed1
#define         rOSD_DATA2_21           0xfed2
#define         rOSD_DATA2_22           0xfed3
#define         rOSD_DATA2_23           0xfed4
#define         rOSD_POSX3              0xfed7
#define         rOSD_POSY3              0xfed8
#define         rOSD_DATA3_0            0xfed9
#define         rOSD_DATA3_1            0xfeda
#define         rOSD_DATA3_2            0xfedb
#define         rOSD_DATA3_3            0xfedc
#define         rOSD_DATA3_4            0xfedd
#define         rOSD_DATA3_5            0xfede
#define         rOSD_DATA3_6            0xfedf
#define         rOSD_DATA3_7            0xfee0
#define         rOSD_DATA3_8            0xfee1
#define         rOSD_DATA3_9            0xfee2
#define         rOSD_DATA3_10           0xfee3
#define         rOSD_DATA3_11           0xfee4
#define         rOSD_DATA3_12           0xfee5
#define         rOSD_DATA3_13           0xfee6
#define         rOSD_DATA3_14           0xfee7
#define         rOSD_DATA3_15           0xfee8
#define         rOSD_DATA3_16           0xfee9
#define         rOSD_DATA3_17           0xfeea
#define         rOSD_DATA3_18           0xfeeb
#define         rOSD_DATA3_19           0xfeec
#define         rOSD_DATA3_20           0xfeed
#define         rOSD_DATA3_21           0xfeee
#define         rOSD_DATA3_22           0xfeef
#define         rOSD_DATA3_23           0xfef0
#define         rOSD_POSX4              0xfef3
#define         rOSD_POSY4              0xfef4
#define         rOSD_DATA4_0            0xfef5
#define         rOSD_DATA4_1            0xfef6
#define         rOSD_DATA4_2            0xfef7
#define         rOSD_DATA4_3            0xfef8
#define         rOSD_DATA4_4            0xfef9
#define         rOSD_DATA4_5            0xfefa
#define         rOSD_DATA4_6            0xfefb
#define         rOSD_DATA4_7            0xfefc
#define         rOSD_DATA4_8            0xfefd
#define         rOSD_DATA4_9            0xfefe
#define         rOSD_DATA4_10           0xfeff
#define         rOSD_DATA4_11           0xff00
#define         rOSD_DATA4_12           0xff01
#define         rOSD_DATA4_13           0xff02
#define         rOSD_DATA4_14           0xff03
#define         rOSD_DATA4_15           0xff04
#define         rOSD_DATA4_16           0xff05
#define         rOSD_DATA4_17           0xff06
#define         rOSD_DATA4_18           0xff07
#define         rOSD_DATA4_19           0xff08
#define         rOSD_DATA4_20           0xff09
#define         rOSD_DATA4_21           0xff0a
#define         rOSD_DATA4_22           0xff0b
#define         rOSD_DATA4_23           0xff0c
#define         rOSD_POSX5              0xff0f
#define         rOSD_POSY5              0xff10
#define         rOSD_DATA5_0            0xff11
#define         rOSD_DATA5_1            0xff12
#define         rOSD_DATA5_2            0xff13
#define         rOSD_DATA5_3            0xff14
#define         rOSD_DATA5_4            0xff15
#define         rOSD_DATA5_5            0xff16
#define         rOSD_DATA5_6            0xff17
#define         rOSD_DATA5_7            0xff18
#define         rOSD_DATA5_8            0xff19
#define         rOSD_DATA5_9            0xff1a
#define         rOSD_DATA5_10           0xff1b
#define         rOSD_DATA5_11           0xff1c
#define         rOSD_DATA5_12           0xff1d
#define         rOSD_DATA5_13           0xff1e
#define         rOSD_DATA5_14           0xff1f
#define         rOSD_DATA5_15           0xff20
#define         rOSD_DATA5_16           0xff21
#define         rOSD_DATA5_17           0xff22
#define         rOSD_DATA5_18           0xff23
#define         rOSD_DATA5_19           0xff24
#define         rOSD_DATA5_20           0xff25
#define         rOSD_DATA5_21           0xff26
#define         rOSD_DATA5_22           0xff27
#define         rOSD_DATA5_23           0xff28
#define         rOSD_POSX6              0xff2b
#define         rOSD_POSY6              0xff2c
#define         rOSD_DATA6_0            0xff2d
#define         rOSD_DATA6_1            0xff2e
#define         rOSD_DATA6_2            0xff2f
#define         rOSD_DATA6_3            0xff30
#define         rOSD_DATA6_4            0xff31
#define         rOSD_DATA6_5            0xff32
#define         rOSD_DATA6_6            0xff33
#define         rOSD_DATA6_7            0xff34
#define         rOSD_DATA6_8            0xff35
#define         rOSD_DATA6_9            0xff36
#define         rOSD_DATA6_10           0xff37
#define         rOSD_DATA6_11           0xff38
#define         rOSD_DATA6_12           0xff39
#define         rOSD_DATA6_13           0xff3a
#define         rOSD_DATA6_14           0xff3b
#define         rOSD_DATA6_15           0xff3c
#define         rOSD_DATA6_16           0xff3d
#define         rOSD_DATA6_17           0xff3e
#define         rOSD_DATA6_18           0xff3f
#define         rOSD_DATA6_19           0xff40
#define         rOSD_DATA6_20           0xff41
#define         rOSD_DATA6_21           0xff42
#define         rOSD_DATA6_22           0xff43
#define         rOSD_DATA6_23           0xff44
#define         rOSD_POSX7              0xff47
#define         rOSD_POSY7              0xff48
#define         rOSD_DATA7_0            0xff49
#define         rOSD_DATA7_1            0xff4a
#define         rOSD_DATA7_2            0xff4b
#define         rOSD_DATA7_3            0xff4c
#define         rOSD_DATA7_4            0xff4d
#define         rOSD_DATA7_5            0xff4e
#define         rOSD_DATA7_6            0xff4f
#define         rOSD_DATA7_7            0xff50
#define         rOSD_DATA7_8            0xff51
#define         rOSD_DATA7_9            0xff52
#define         rOSD_DATA7_10           0xff53
#define         rOSD_DATA7_11           0xff54
#define         rOSD_DATA7_12           0xff55
#define         rOSD_DATA7_13           0xff56
#define         rOSD_DATA7_14           0xff57
#define         rOSD_DATA7_15           0xff58
#define         rOSD_DATA7_16           0xff59
#define         rOSD_DATA7_17           0xff5a
#define         rOSD_DATA7_18           0xff5b
#define         rOSD_DATA7_19           0xff5c
#define         rOSD_DATA7_20           0xff5d
#define         rOSD_DATA7_21           0xff5e
#define         rOSD_DATA7_22           0xff5f
#define         rOSD_DATA7_23           0xff60
#define         rOSD_POSX8              0xff63
#define         rOSD_POSY8              0xff64
#define         rOSD_DATA8_0            0xff65
#define         rOSD_DATA8_1            0xff66
#define         rOSD_DATA8_2            0xff67
#define         rOSD_DATA8_3            0xff68
#define         rOSD_DATA8_4            0xff69
#define         rOSD_DATA8_5            0xff6a
#define         rOSD_DATA8_6            0xff6b
#define         rOSD_DATA8_7            0xff6c
#define         rOSD_DATA8_8            0xff6d
#define         rOSD_DATA8_9            0xff6e
#define         rOSD_DATA8_10           0xff6f
#define         rOSD_DATA8_11           0xff70
#define         rOSD_DATA8_12           0xff71
#define         rOSD_DATA8_13           0xff72
#define         rOSD_DATA8_14           0xff73
#define         rOSD_DATA8_15           0xff74
#define         rOSD_DATA8_16           0xff75
#define         rOSD_DATA8_17           0xff76
#define         rOSD_DATA8_18           0xff77
#define         rOSD_DATA8_19           0xff78
#define         rOSD_DATA8_20           0xff79
#define         rOSD_DATA8_21           0xff7a
#define         rOSD_DATA8_22           0xff7b
#define         rOSD_DATA8_23           0xff7c
#define         rOSD_POSX9              0xff7f
#define         rOSD_POSY9              0xff80
#define         rOSD_DATA9_0            0xff81
#define         rOSD_DATA9_1            0xff82
#define         rOSD_DATA9_2            0xff83
#define         rOSD_DATA9_3            0xff84
#define         rOSD_DATA9_4            0xff85
#define         rOSD_DATA9_5            0xff86
#define         rOSD_DATA9_6            0xff87
#define         rOSD_DATA9_7            0xff88
#define         rOSD_DATA9_8            0xff89
#define         rOSD_DATA9_9            0xff8a
#define         rOSD_DATA9_10           0xff8b
#define         rOSD_DATA9_11           0xff8c
#define         rOSD_DATA9_12           0xff8d
#define         rOSD_DATA9_13           0xff8e
#define         rOSD_DATA9_14           0xff8f
#define         rOSD_DATA9_15           0xff90
#define         rOSD_DATA9_16           0xff91
#define         rOSD_DATA9_17           0xff92
#define         rOSD_DATA9_18           0xff93
#define         rOSD_DATA9_19           0xff94
#define         rOSD_DATA9_20           0xff95
#define         rOSD_DATA9_21           0xff96
#define         rOSD_DATA9_22           0xff97
#define         rOSD_DATA9_23           0xff98
#define         rOSD_POSX10             0xff9b
#define         rOSD_POSY10             0xff9c
#define         rOSD_DATA10_0           0xff9d
#define         rOSD_DATA10_1           0xff9e
#define         rOSD_DATA10_2           0xff9f
#define         rOSD_DATA10_3           0xffa0
#define         rOSD_DATA10_4           0xffa1
#define         rOSD_DATA10_5           0xffa2
#define         rOSD_DATA10_6           0xffa3
#define         rOSD_DATA10_7           0xffa4
#define         rOSD_DATA10_8           0xffa5
#define         rOSD_DATA10_9           0xffa6
#define         rOSD_DATA10_10          0xffa7
#define         rOSD_DATA10_11          0xffa8
#define         rOSD_DATA10_12          0xffa9
#define         rOSD_DATA10_13          0xffaa
#define         rOSD_DATA10_14          0xffab
#define         rOSD_DATA10_15          0xffac
#define         rOSD_DATA10_16          0xffad
#define         rOSD_DATA10_17          0xffae
#define         rOSD_DATA10_18          0xffaf
#define         rOSD_DATA10_19          0xffb0
#define         rOSD_DATA10_20          0xffb1
#define         rOSD_DATA10_21          0xffb2
#define         rOSD_DATA10_22          0xffb3
#define         rOSD_DATA10_23          0xffb4
#define         rOSD_POSX11             0xffb7
#define         rOSD_POSY11             0xffb8
#define         rOSD_DATA11_0           0xffb9
#define         rOSD_DATA11_1           0xffba
#define         rOSD_DATA11_2           0xffbb
#define         rOSD_DATA11_3           0xffbc
#define         rOSD_DATA11_4           0xffbd
#define         rOSD_DATA11_5           0xffbe
#define         rOSD_DATA11_6           0xffbf
#define         rOSD_DATA11_7           0xffc0
#define         rOSD_DATA11_8           0xffc1
#define         rOSD_DATA11_9           0xffc2
#define         rOSD_DATA11_10          0xffc3
#define         rOSD_DATA11_11          0xffc4
#define         rOSD_DATA11_12          0xffc5
#define         rOSD_DATA11_13          0xffc6
#define         rOSD_DATA11_14          0xffc7
#define         rOSD_DATA11_15          0xffc8
#define         rOSD_DATA11_16          0xffc9
#define         rOSD_DATA11_17          0xffca
#define         rOSD_DATA11_18          0xffcb
#define         rOSD_DATA11_19          0xffcc
#define         rOSD_DATA11_20          0xffcd
#define         rOSD_DATA11_21          0xffce
#define         rOSD_DATA11_22          0xffcf
#define         rOSD_DATA11_23          0xffd0

#define		rVGA_clk_reg         0xffd2
#define		rPLL2_mul_reg        0xffd4
#define		rPLL3_mul_reg        0xffd5
#define		rPLL2_div_reg        0xffd6
#define		rPLL3_div_reg        0xffd7
#define		rDAC_REGL		0xffd8	//DAC data[7:0]   <--0xfa36
#define		rDAC_REGH		0xffd9  //dac_clk[7]/dac_RESETn[3]/ data9[1]/ data8[0]
#define		rADC_reg    0xffdb	//XPD[7]_L power down/STC[3]/AIN1[1]/AIN0[0]
#define		rADC_freq   0xffdc  //27MHz/27 = 1MHz
#define		rADC_DATH	  0xffde  //EOC[4]/ ADC9[1]/ADC8[0]
#define		rADC_DATL	  0xffdf	//ADC7..0	         0xffdf

#define		rOSD_FCOLOR_Y		0xffe1
#define		rOSD_FCOLOR_CR		0xffe2
#define		rOSD_FCOLOR_CB		0xffe3
#define		rOSD_ECOLOR_Y		0xffe4
#define		rOSD_ECOLOR_CR		0xffe5
#define		rOSD_ECOLOR_CB		0xffe6
#define		rDISP_ONOFFH		0xffe8
#define		rDISP_ONOFFL		0xffe9


#endif