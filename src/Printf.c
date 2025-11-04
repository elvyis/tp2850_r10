// *****************************************************
// Company : Techpoint Inc
// $Id: Printf.c 16054 2013-10-17 21:05:52Z SJ $
// $Author: SJ $
// $Date: 2013-10-17 14:05:52 -0700 (Thu, 17 Oct 2013) $
// $Revision: 00 $
// $Log:  $
// ******************************************************
#include "inc\Config.h"

#include "inc\reg.h"
#include "inc\Typedefs.h"
//#include "debug.h"
#include "inc\main.h"
#include "inc\printf.h"
#include <stdarg.h>

CODE BYTE Hex[] = "0123456789ABCDEF";
extern	bit     	RS_Xbusy;			// bit RS_Xbusy=0;
extern	IDATA BYTE	DebugLevel;


void DoPrint( const char CODE_P *fmt, va_list ap )
{
	char  ch;
	char  i;
	long  value;
	bit   fl_zero;
	bit   fl_num;
	bit   fl_long;
	BYTE  cnt;
	DWORD mask=1;

	#ifdef KEILC
	char *ptr;
	#endif

	while(1) {
		
		//----- Find Formatter % -----

		switch( ch = *fmt++ ) {
			case 0:
				return;
			case '%':
				if( *fmt != '%' )
					break;
				fmt++;
			default:
				_outchar( ch );
				continue;
		}

		//----- Get Count -------------
		
		fl_zero = 0;
		fl_num = 0;
		cnt = 0;

		ch = *fmt++;

		if( ch=='0' ) {
			fl_zero = 1;
			ch = *fmt++;
			cnt = ch - '0';
			ch = *fmt++;
		}
		else if( ch>='0' && ch<='9' ) {
			cnt = ch - '0';
			ch = *fmt++;
		}

		//----- Get long ----------------

		fl_long = 0;
		if( ch=='l' || ch=='L' ) {
			ch = *fmt++;
			fl_long = 1;
		}
		
		//----- Get Type Discriptor -----
		
		switch( ch ) {

			case 'd':
			case 'D':
				if( fl_long ) value = (DWORD)va_arg( ap, DWORD );
				else          value = (WORD)va_arg( ap, WORD );

				if(cnt==0) {
					if( value==0 ) { _outchar('0'); continue; }

					for(cnt=0, mask=1; cnt<9; cnt++) {
						if( (value/mask)==0 ) break;
						mask = mask*10;
					}
				}

				for(i=0, mask=1; i<cnt; i++) mask = mask*10;

				while(1) {
					value = value % (mask);
					mask = mask / 10;
					ch = (value / mask) + '0';
					
					if( ch=='0' && fl_zero==0 && mask!=1 ) ch=' ';
					else fl_zero = 1;
					
					_outchar(ch);
					if( mask==1 ) 
						break;
				}
				continue;

			case 'x':
			case 'X':

				if( fl_long ) value = (DWORD)va_arg( ap, DWORD );
				else          value = (WORD)va_arg( ap, WORD );


				if(cnt==0) cnt = 4;
				for(i=0; i<cnt; i++) {
					_outchar( Hex[(value >> (cnt-i-1)*4) & 0x000f] );
				}
				continue;

			case 's':

				#ifdef TASKINGC
				
				value = (WORD)va_arg( ap, WORD );
				while(*(char CODE_P *)value!='\0')
					_outchar(*(char CODE_P *)value++);
				continue;

				#elif defined KEILC
				
				ptr = (char *)va_arg( ap, char* );
				while(*ptr!='\0')
					_outchar(*ptr++);
				continue;

				#endif


			case 'c':
				value = va_arg( ap, int );
					_outchar((BYTE)value);
				continue;

			default:
				value = (WORD)va_arg( ap, int );
				continue;
		}
	}
}

//===========================================================================//
//                                                                           //
//===========================================================================//
//va_list ap;

void Printf( const char CODE_P *fmt, ... )
{
	va_list ap;

	va_start(ap, fmt);
	DoPrint( fmt, ap );
	va_end( ap );
}

void Puts( CODE_P char *ptr )
{
	while(*ptr!='\0')
		RS_tx(*ptr++);
}

//===========================================================================//
//                                                                           //
//===========================================================================//
#ifdef DEBUG

void dPrintf( const char CODE_P *fmt, ... )
{
	va_list ap;

	if( DebugLevel >= DEBUG_INFO ) {
		va_start(ap, fmt);
		DoPrint( fmt, ap );
		va_end( ap );
	}
}
/*
void wPrintf( const char rom *fmt, ... )
{
	va_list ap;

	if( DebugLevel >= DEBUG_WARN ) {
		va_start(ap, fmt);
		DoPrint( fmt, ap );
		va_end( ap );
	}
}
*/

void ePrintf( const char CODE_P *fmt, ... )
{
	va_list ap;

	if( DebugLevel >= DEBUG_ERR ) {
		va_start(ap, fmt);
		DoPrint( fmt, ap );
		va_end( ap );
	}
}

//===========================================================================//
//                                                                           //
//===========================================================================//
void dPuts( CODE_P char *ptr )
{
	if( DebugLevel >= DEBUG_INFO ) {
		while(*ptr!='\0')
			RS_tx(*ptr++);
	}
}

void wPuts( CODE_P char *ptr )
{
	if( DebugLevel >= DEBUG_WARN ) {
		while(*ptr!='\0')
			RS_tx(*ptr++);
	}
}

void ePuts( CODE_P char *ptr )
{
	if( DebugLevel >= DEBUG_ERR ) {
		while(*ptr!='\0')
			RS_tx(*ptr++);
	}
}

#endif // DEBUG

//===========================================================================//
//                                                                           //
//===========================================================================//
/*
#ifdef DEBUG
BYTE Getch(void)
{
	while(!RS_ready());
	return RS_rx();
}
#endif

BYTE Getche(void)
{
	BYTE ch;

	while(!RS_ready());
	ch = RS_rx();
	RS_tx(ch);

	return ch;
}
*/
