//----------------------------------------------------------------------------------------------------------------------
// (C) Copyright 2010  Macro Image Technology Co., LTd. , All rights reserved
// 
// This source code is the property of Macro Image Technology and is provided
// pursuant to a Software License Agreement. This code's reuse and distribution
// without Macro Image Technology's permission is strictly limited by the confidential
// information provisions of the Software License Agreement.
//-----------------------------------------------------------------------------------------------------------------------
//
// File Name   		:	MDINDLY.C
// Description 		:
// Ref. Docment		: 
// Revision History 	:

// ----------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------
#include	"intrins.h"
#include	"mdin3xx.h"

// ----------------------------------------------------------------------
// Struct/Union Types and define
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Static Global Data section variables
// ----------------------------------------------------------------------
//VWORD usDelay, msDelay;

// ----------------------------------------------------------------------
// External Variable 
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Static Prototype Functions
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Static functions
// ----------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
// Drive Function for delay (usec and msec)
// You must make functions which is defined below.
//--------------------------------------------------------------------------------------------------------------------------
MDIN_ERROR_t MDINDLY_10uSec(WORD delay)
{
	// For 10us delay, add user delay function --------------------------------------------//
	while(delay)
	{
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		delay--;		

	}

	//-------------------------------------------------------------------------------------//
	
	return MDIN_NO_ERROR;
}

//--------------------------------------------------------------------------------------------------------------------------
extern xdata BYTE mS_timer; 
MDIN_ERROR_t MDINDLY_mSec(BYTE delay)
{
	// For 1ms delay, add user delay function ---------------------------------------------//
	mS_timer=delay;
	while(mS_timer) _nop_();

	//-------------------------------------------------------------------------------------//
	
	return MDIN_NO_ERROR;
}

/*  FILE_END_HERE */
