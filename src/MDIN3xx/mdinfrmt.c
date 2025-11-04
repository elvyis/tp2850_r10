//----------------------------------------------------------------------------------------------------------------------
// (C) Copyright 2008  Macro Image Technology Co., LTd. , All rights reserved
// 
// This source code is the property of Macro Image Technology and is provided
// pursuant to a Software License Agreement. This code's reuse and distribution
// without Macro Image Technology's permission is strictly limited by the confidential
// information provisions of the Software License Agreement.
//-----------------------------------------------------------------------------------------------------------------------
//
// File Name   		:  MDINFRMT.C
// Description 		:  This file contains typedefine for the driver files	
// Ref. Docment		: 
// Revision History 	:

// -----------------------------------------------------------------------------
// Include files
// -----------------------------------------------------------------------------
#include	"mdin3xx.h"

// -----------------------------------------------------------------------------
// Struct/Union Types and define
// -----------------------------------------------------------------------------

// ----------------------------------------------------------------------
// Static Global Data section variables
// ----------------------------------------------------------------------
// OUT sync control
ROMDATA MDIN_OUTVIDEO_SYNC defMDINOutSync[]		= {
// TV
	{	// 720x480i60
		  20,		// hdpulse_pos
		   8,		// vdpulse_pos
		 270,	// vdpulse_pos_bot
		 858,	// htotal_size
		  87,		// hactive_start
		 807,	// hactive_end
		  63,		// hsync_start
		   1,		// hsync_end
		 525,	// vtotal_size
		  21,		// vactive_start
		 261,	// vactive_end
		   6,		// vsync_start
		   3,		// vsync_end
		 284,	// vactive_start_bot
		 524,	// vactive_end_bot
		 268,	// vsync_start_bot
		 265,	// vsync_end_bot
		 430,	// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  16,		// post_div_vclk (M)
		   8,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		  27,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		   1		// axclk_gen_div_t (T)
	#else
		  29,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		   1		// axclk_gen_div_t (T)
	#endif
	},
	{	// 720x576i50
		  20,		// hdpulse_pos
		   8,		// vdpulse_pos
		 320,		// vdpulse_pos_bot
		 864,		// htotal_size
		 100,		// hactive_start
		 820,		// hactive_end
		  64,		// hsync_start
		   1,		// hsync_end
		 625,		// vtotal_size
		  23,		// vactive_start
		 311,		// vactive_end
		   4,		// vsync_start
		   1,		// vsync_end
		 336,		// vactive_start_bot
		 624,		// vactive_end_bot
		 316,		// vsync_start_bot
		 313,		// vsync_end_bot
		 433,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  16,		// post_div_vclk (M)
		   8,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		  27,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		   1		// axclk_gen_div_t (T)
	#else
		  29,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		   1		// axclk_gen_div_t (T)
	#endif
	},
	{	// 720x480p60
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		 858,		// htotal_size
		  90,		// hactive_start
		 810,		// hactive_end
		  63,		// hsync_start
		   1,		// hsync_end
		 525,		// vtotal_size
		  43,		// vactive_start
		 523,		// vactive_end
		  13,		// vsync_start
		   7,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  16,		// post_div_vclk (M)
		   4,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		  13,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		   1		// axclk_gen_div_t (T)
	#else
		  14,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		   1		// axclk_gen_div_t (T)
	#endif
	},
	{	// 720x576p50
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		 864,		// htotal_size
		 100,		// hactive_start
		 820,		// hactive_end
		  65,		// hsync_start
		   1,		// hsync_end
		 625,		// vtotal_size
		  45,		// vactive_start
		 621,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  16,		// post_div_vclk (M)
		   4,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		  13,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		   1		// axclk_gen_div_t (T)
	#else
		  14,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		   1		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1280x720p60
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		1650,		// htotal_size
		 228,		// hactive_start
		1508,		// hactive_end
		  41,		// hsync_start
		   1,		// hsync_end
		 750,		// vtotal_size
		  26,		// vactive_start
		 746,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   2,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1280x720p59.94
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		1650,		// htotal_size
		 228,		// hactive_start
		1508,		// hactive_end
		  41,		// hsync_start
		   1,		// hsync_end
		 750,		// vtotal_size
		  26,		// vactive_start
		 746,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		  91,		// pre_div_vclk (P)
		250,		// post_div_vclk (M)
		   1,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  52		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		  23,		// axclk_gen_div_f (F)
		  50		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1280x720p50
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		1980,		// htotal_size
		 228,		// hactive_start
		1508,		// hactive_end
		  41,		// hsync_start
		   1,		// hsync_end
		 750,		// vtotal_size
		  26,		// vactive_start
		 746,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   2,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1280x720p30
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		3300,		// htotal_size
		 228,		// hactive_start
		1508,		// hactive_end
		  41,		// hsync_start
		   1,		// hsync_end
		 750,		// vtotal_size
		  26,		// vactive_start
		 746,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   2,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1280x720p25
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		3960,		// htotal_size
		 228,		// hactive_start
		1508,		// hactive_end
		  41,		// hsync_start
		   1,		// hsync_end
		 750,		// vtotal_size
		  26,		// vactive_start
		 746,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   2,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1280x720p24
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		3300,	// htotal_size
		 228,		// hactive_start
		1508,		// hactive_end
		  41,		// hsync_start
		   1,		// hsync_end
		 750,		// vtotal_size
		  26,		// vactive_start
		 746,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   6,		// pre_div_vclk (P)
		  66,		// post_div_vclk (M)
		   5,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   6,		// axclk_gen_div_s (S)
		   4,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   6,		// axclk_gen_div_s (S)
		   9,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1920x1080i60
		  20,		// hdpulse_pos
		   1,		// vdpulse_pos
		 564,		// vdpulse_pos_bot
		2200,		// htotal_size
		 160,		// hactive_start
		2080,		// hactive_end
		  45,		// hsync_start
		   1,		// hsync_end
		1125,		// vtotal_size
		  21,		// vactive_start
		 561,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		 584,		// vactive_start_bot
		1124,		// vactive_end_bot
		 568,		// vsync_start_bot
		 563,		// vsync_end_bot
		1101,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   2,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1920x1080i59.94
		  20,		// hdpulse_pos
		   1,		// vdpulse_pos
		 564,		// vdpulse_pos_bot
		2200,		// htotal_size
		 160,		// hactive_start
		2080,		// hactive_end
		  45,		// hsync_start
		   1,		// hsync_end
		1125,		// vtotal_size
		  21,		// vactive_start
		 561,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		 584,		// vactive_start_bot
		1124,		// vactive_end_bot
		 568,		// vsync_start_bot
		 563,		// vsync_end_bot
		1101,		// vsync_bot_fld_pos
	
		   91,		// pre_div_vclk (P)
		  250,		// post_div_vclk (M)
		   1,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  52		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		  23,		// axclk_gen_div_f (F)
		  50		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1920x1080i50
		  20,		// hdpulse_pos
		   1,		// vdpulse_pos
		 564,		// vdpulse_pos_bot
		2640,		// htotal_size
		 160,		// hactive_start
		2080,		// hactive_end
		  45,		// hsync_start
		   1,		// hsync_end
		1125,		// vtotal_size
		  22,		// vactive_start
		 562,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		 585,		// vactive_start_bot
		   0,		// vactive_end_bot
		 568,		// vsync_start_bot
		 563,		// vsync_end_bot
		1321,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   2,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1920x1080p60
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		2200,		// htotal_size
		 160,		// hactive_start
		2080,		// hactive_end
		  45,		// hsync_start
		   1,		// hsync_end
		1125,		// vtotal_size
		  42,		// vactive_start
		1122,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   1,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   2,		// axclk_gen_div_s (S)
		   6,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   2,		// axclk_gen_div_s (S)
		   8,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1920x1080p59.94
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		2200,		// htotal_size
		 160,		// hactive_start
		2080,		// hactive_end
		  45,		// hsync_start
		   1,		// hsync_end
		1125,		// vtotal_size
		  42,		// vactive_start
		1122,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   91,		// pre_div_vclk (P)
		  500,		// post_div_vclk (M)
		   1,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   2,		// axclk_gen_div_s (S)
		  40,		// axclk_gen_div_f (F)
		  73		// axclk_gen_div_t (T)
	#else
		   2,		// axclk_gen_div_s (S)
		  46,		// axclk_gen_div_f (F)
		  63		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1920x1080p50
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		2640,		// htotal_size
		 160,		// hactive_start
		2080,		// hactive_end
		  45,		// hsync_start
		   1,		// hsync_end
		1125,		// vtotal_size
		  42,		// vactive_start
		1122,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   1,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   2,		// axclk_gen_div_s (S)
		   6,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   2,		// axclk_gen_div_s (S)
		   8,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1920x1080p30
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		2200,		// htotal_size
		 160,		// hactive_start
		2080,		// hactive_end
		  45,		// hsync_start
		   1,		// hsync_end
		1125,		// vtotal_size
		  42,		// vactive_start
		1122,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   2,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1920x1080p25
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		2640,		// htotal_size
		 160,		// hactive_start
		2080,		// hactive_end
		  45,		// hsync_start
		   1,		// hsync_end
		1125,		// vtotal_size
		  42,		// vactive_start
		1122,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   2,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},

	{	// 1920x1080p24
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		2750,		// htotal_size
		 160,		// hactive_start
		2080,		// hactive_end
		  45,		// hsync_start
		   1,		// hsync_end
		1125,		// vtotal_size
		  42,		// vactive_start
		1122,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   2,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   5,		// axclk_gen_div_s (S)
		   1,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   5,		// axclk_gen_div_s (S)
		   5,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
	{	// 1280x960p60
		  20,		// hdpulse_pos
		  10,		// vdpulse_pos
		   0,		// vdpulse_pos_bot
		2200,		// htotal_size
		 160,		// hactive_start
		2080-640,		// hactive_end
		  45,		// hsync_start
		   1,		// hsync_end
		1125,		// vtotal_size
		  42+120,		// vactive_start
		1122,		// vactive_end
		   6,		// vsync_start
		   1,		// vsync_end
		   0,		// vactive_start_bot
		   0,		// vactive_end_bot
		   0,		// vsync_start_bot
		   0,		// vsync_end_bot
		   0,		// vsync_bot_fld_pos
	
		   4,		// pre_div_vclk (P)
		  22,		// post_div_vclk (M)
		   1,		// post_scale_vclk (S)

	#if defined(SYSTEM_USE_MCLK189)
		   2,		// axclk_gen_div_s (S)
		   6,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#else
		   2,		// axclk_gen_div_s (S)
		   8,		// axclk_gen_div_f (F)
		  11		// axclk_gen_div_t (T)
	#endif
	},
};


	
// default value for srcVideo format
ROMDATA MDIN_SRCVIDEO_ATTB defMDINSrcVideo[]		= {
//	 Htot					                   H/V Polarity & ScanType                                       Hact  Vact
#if defined(IN_960H_MODE)	// input 960H mode, modified on 29Feb2012
	//{858, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_INTR,  720,  480},	// 960x480i60
	//{1200, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_INTR,  960,  576},	// 960x576i50
	{2360, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_INTR,  960,  480},	// 960x480i60
	{2376, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_INTR,  960,  576},	// 960x576i50
#else
	{ 858, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_INTR,  720,  480},	// 720x480i60
	{ 864, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_INTR,  720,  576},	// 720x576i50
#endif	
	{ 858, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG,  720,  480},		// 720x480p60
	{ 864, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG,  720,  576},		// 720x576p50
	{1650, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  720},		// 1280x720p60
	{1980, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  720},		// 1280x720p50
	{2200, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_INTR, 1920, 1080},		// 1920x1080i60
	{2640, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_INTR, 1920, 1080},		// 1920x1080i50
	{2200, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1920, 1080},	// 1920x1080p60
	{2640, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1920, 1080},	// 1920x1080p50
//	{1100, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 960, 1080},	// 1920x1080p60
	{1650, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280, 960},	// 1280x960p30
	{1650, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280, 320},	// 1280x320p60	

	{ 800, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG,  640,  480},	// 640x480p60
	{1056, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG,  800,  600},	// 800x600p60
	{1344, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG, 1024,  768},	// 1024x768p60
	{1688, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280, 1024},	// 1280x1024p60

	{1664, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  720},	// 1280x720pRGB
	{1800, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  960},	// 1280x960p60
	{1792, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1360,  768},	// 1360x768p60
	{1904, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1440,  900},	// 1440x900p60
	{1250, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1024,  512},	// 1024x518p60
#if VGA_SOURCE_EXTENSION == 1
	{ 832, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG,  640,  480},	// 640x480p72
	{ 840, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG,  640,  480},	// 640x480p75
	{1024, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG,  800,  600},	// 800x600p56
	{1040, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG,  800,  600},	// 800x600p72
	{1056, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG,  800,  600},	// 800x600p75
	{1328, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG, 1024,  768},	// 1024x768p70
	{1312, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1024,  768},	// 1024x768p75
	{1600, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1152,  864},	// 1152x864p75
	{1680, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  800},	// 1280x800p60
#endif
};

// default value for outVideo format
ROMDATA MDIN_OUTVIDEO_ATTB defMDINOutVideo[]		= {
//	 Htot					                   H/V Polarity & ScanType                                       Hact  Vact
	// TV
	{ 858, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_INTR,  720,  480},		// 720x480i60
	{ 864, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_INTR,  720,  576},		// 720x576i50
#if defined(IN_960H_MODE)	// input 960H mode, modified on 29Feb2012
	{1144, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG,  960,  480},	// 960x480p60
	{1200, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG,  960,  576},	// 960x576p50
#else
	{ 858, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG,  720,  480},	// 720x480p60
	{ 864, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_NEGATIVE_HSYNC|MDIN_NEGATIVE_VSYNC|MDIN_SCANTYPE_PROG,  720,  576},	// 720x576p50
#endif	
	
	{1650, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  720},		// 1280x720p60
	{1650, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  720},		// 1280x720p59.94
	{1980, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  720},		// 1280x720p50
	
	{3300, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  720},		// 1280x720p30
	{3960, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  720},		// 1280x720p25
	{3300, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280,  720},		// 1280x720p24
	
	{2200, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_INTR, 1920, 1080},		// 1920x1080i60
	{2200, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_INTR, 1920, 1080},		// 1920x1080i59.94
	{2640, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_INTR, 1920, 1080},		// 1920x1080i50
	
	{2200, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1920, 1080},	// 1920x1080p60
	{2200, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1920, 1080},	// 1920x1080p59.94
	{2640, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1920, 1080},	// 1920x1080p50
	
	{2640, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1920, 1080},	// 1920x1080p30
	{2640, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1920, 1080},	// 1920x1080p25
	{2750, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1920, 1080},	// 1920x1080p24

	{2200, MDIN_POSITIVE_HACT|MDIN_POSITIVE_VACT|MDIN_POSITIVE_HSYNC|MDIN_POSITIVE_VSYNC|MDIN_SCANTYPE_PROG, 1280, 960},	// 1280x960p60

};

#if defined(SYSTEM_USE_MDIN340)||defined(SYSTEM_USE_MDIN380)
// default value for hdmi-Video format
ROMDATA MDIN_HTXVIDEO_FRMT defMDINHTXVideo[]		= {
//		MDIN-format (wide(0)-4:3, wide(1)-4:3/16:9, wide(2)-16:9)
//	  id1 id2 sub wide|rep    pixel   freq  Htot  Vtot     x    y   Hact  Vact                 BT656
//	{{  6,  7, 0, (1<<4)|1}, { 2700,  6000, 1716,  525}, {238,  18,  720,  240}, {3, 124, 3, 114,  15,  38,  4,  429}}, // 1440x480i@60(6,7)
	{{  6,  7, 0, (1<<4)|1}, { 2700,  6000, 1716,  264}, {119,  18,  720,  240}, {3,  62, 2, 114,  15,  19,  4,  429}}, // 1440x480i@60(6,7) // 28Dec2011
//	{{ 21, 22, 0, (0<<4)|1}, { 2700,  5000, 1728,  625}, {264,  22,  720,  288}, {3, 126, 3, 138,  19,  24,  2,  432}}, // 1440x576i@50(21,22)
	{{ 21, 22, 0, (0<<4)|1}, { 2700,  5000, 1728,  313}, {132,  22,  720,  288}, {3,  63, 3, 138,  19,  12,  2,  432}}, // 1440x576i@50(21,22) // 28Dec2011
	{{  2,  3, 0, (1<<4)|0}, { 2700,  6000,  858,  525}, {122,  36,  720,  480}, {0,  62, 6,  60,  30,  16,  9,    0}}, // 720x480p@60(2,3)
	{{ 17, 18, 0, (1<<4)|0}, { 2700,  5000,  864,  625}, {132,  44,  720,  576}, {0,  64, 5,  68,  39,  12,  5,    0}}, // 720x576p@50(17,18)
	
	{{  4,  0, 0, (2<<4)|0}, { 7425,  6000, 1650,  750}, {260,  25, 1280,  720}, {0,  40, 5, 220,  20, 110,  5,    0}}, // 1280x720p@60(4)
	{{  4,  0, 0, (2<<4)|0}, { 7418,  5994, 1650,  750}, {260,  25, 1280,  720}, {0,  40, 5, 220,  20, 110,  5,    0}}, // 1280x720p@59.94(4)
	{{ 19,  0, 0, (2<<4)|0}, { 7425,  5000, 1980,  750}, {260,  25, 1280,  720}, {0,  40, 5, 220,  20, 440,  5,    0}}, // 1280x720p@50(19)
	
	{{ 62,  0, 0, (2<<4)|0}, { 7425,  3000, 3300,  750}, {260,  25, 1280,  720}, {0,  40, 5, 220,  20, 1760,  5,    0}}, // 1280x720p@30(62)
	{{ 61,  0, 0, (2<<4)|0}, { 7425,  2500, 3960,  750}, {260,  25, 1280,  720}, {0,  40, 5, 220,  20, 2420,  5,    0}}, // 1280x720p@25(61)
	{{ 60,  0, 0, (2<<4)|0}, { 5940,  2400, 3300,  750}, {260,  25, 1280,  720}, {0,  40, 5, 220,  20, 1760,  5,    0}}, // 1280x720p@24(60)
	
	{{  5,  0, 0, (2<<4)|0}, { 7418,  6000, 2200, 1125}, {192,  20, 1920,  540}, {0,  44, 5, 148,  15,  88,  2, 1100}}, // 1920x1080i@60(5)
	{{  5,  0, 0, (2<<4)|0}, { 7425,  5994, 2200, 1125}, {192,  20, 1920,  540}, {0,  44, 5, 148,  15,  88,  2, 1100}}, // 1920x1080i@59.94(5)
	{{ 20,  0, 0, (2<<4)|0}, { 7425,  5000, 2640, 1125}, {192,  20, 1920,  540}, {0,  44, 5, 148,  15, 528,  2, 1320}}, // 1920x1080i@50(20)
	
	{{ 16,  0, 0, (2<<4)|0}, {14850,  6000, 2200, 1125}, {192,  41, 1920, 1080}, {0,  44, 5, 148,  36,  88,  4,    0}}, // 1920x1080p@60(16)
	{{ 16,  0, 0, (2<<4)|0}, {14850,  5994, 2200, 1125}, {192,  41, 1920, 1080}, {0,  44, 5, 148,  36,  88,  4,    0}}, // 1920x1080p@59.94(16)
	{{ 31,  0, 0, (2<<4)|0}, {14850,  5000, 2640, 1125}, {192,  41, 1920, 1080}, {0,  44, 5, 148,  36, 528,  4,    0}}, // 1920x1080p@50(31)

	{{ 34,  0, 0, (2<<4)|0}, {7425,  3000, 2200, 1125}, {192,  41, 1920, 1080}, {0,  44, 5, 148,  36,  88,  4,    0}}, // 1920x1080p@30(34)
	{{ 33,  0, 0, (2<<4)|0}, {7425,  2500, 2640, 1125}, {192,  41, 1920, 1080}, {0,  44, 5, 148,  36, 528,  4,    0}}, // 1920x1080p@25(33)
	{{ 32,  0, 0, (2<<4)|0}, {7425,  2400, 2750, 1125}, {192,  41, 1920, 1080}, {0,  44, 5, 148,  36, 638,  4,    0}}, // 1920x1080p@24(32)
		
	{{ 16,  0, 0, (2<<4)|0}, {14850,  6000, 2200, 1125}, {192,  41, 1280, 960}, {0,  44, 5, 148,  36,  88,  4,    0}}, // 1920x1080p@60(16)
		
//	{{  1,  0, 0, (0<<4)|0}, { 2517,  6000,  800,  525}, {144,  35,  640,  480}, {0,  96, 2,  48,  33,  16, 10,    0}}, // 640x480@60(1)
//	{{ 66,  0, 0, (0<<4)|0}, { 3150,  7500,  840,  500}, {184,  19,  640,  480}, {0,  64, 3, 120,  16,  16,  1,    0}}, // 640x480@75
//	{{ 69,  0, 0, (0<<4)|0}, { 4000,  6032, 1056,  628}, {216,  27,  800,  600}, {0, 128, 4,  88,  23,  40,  1,    0}}, // 800x600@60
//	{{ 71,  0, 0, (0<<4)|0}, { 4950,  7500, 1056,  625}, {240,  24,  800,  600}, {0,  80, 3, 160,  21,  16,  1,    0}}, // 800x600@75
//	{{ 73,  0, 0, (0<<4)|0}, { 6500,  6000, 1344,  806}, {296,  35, 1024,  768}, {0, 136, 6, 160,  29,  24,  3,    0}}, // 1024x768@60
//	{{ 75,  0, 0, (0<<4)|0}, { 7875,  7503, 1312,  800}, {272,  31, 1024,  768}, {0,  96, 3, 176,  28,  16,  1,    0}}, // 1024x768@75
//	{{ 85,  0, 0, (0<<4)|0}, {10800,  6002, 1688, 1066}, {360,  41, 1280, 1024}, {0, 112, 3, 248,  38,  48,  1,    0}}, // 1280x1024@60
//	{{ 86,  0, 0, (0<<4)|0}, {13500,  7503, 1688, 1066}, {392,  41, 1280, 1024}, {0, 144, 3, 248,  38,  16,  1,    0}}, // 1280x1024@75

//	{{ 88,  0, 0, (2<<4)|0}, { 8550,  6002, 1792,  795}, {368,  24, 1360,  768}, {0, 112, 6, 256,  18,  64,  3,    0}}, // 1360x768@60
//	{{ 108,  0, 0, (2<<4)|0}, {8575,  5996, 1792,  798}, {356,  27, 1366,  768}, {0, 143, 3, 213,  24,  70,  3,    0}}, // 1366x768@60
//	{{ 109,  0, 0, (2<<4)|0}, {12175,  5998, 1864,  1089}, {376,  36, 1400,  1050}, {0, 144, 4, 232,  32,  88,  3,    0}}, // 1400x1050@60
//	{{ 78,  0, 0, (0<<4)|0}, {16200,  6000, 2160, 1250}, {496,  49, 1600, 1200}, {0, 192, 3, 304,  46,  64,  1,    0}}, // 1600x1200@60

//	{{108,  0, 0, (2<<4)|0}, {10650,  5989, 1904,  934}, {384,  31, 1440,  900}, {0, 152, 6, 232,  25,  80,  3,    0}}, // 1440x900@60
//	{{109,  0, 0, (2<<4)|0}, {13675,  7498, 1936,  942}, {400,  39, 1440,  900}, {0, 152, 6, 248,  33,  96,  3,    0}}, // 1440x900@75
//	{{110,  0, 0, (2<<4)|0}, {14625,  5995, 2240, 1089}, {456,  36, 1680, 1050}, {0, 176, 6, 280,  30, 104,  3,    0}}, // 1680x1050@60

//	{{111,  0, 0, (2<<4)|0}, {11900,  5988, 1840, 1080}, {112,  27, 1680, 1050}, {0,  32, 6,  80,  21,  48,  3,    0}}, // 1680x1050@RB
//	{{112,  0, 0, (2<<4)|0}, {13850,  5993, 2080, 1111}, {112,  28, 1920, 1080}, {0,  32, 5,  80,  23,  48,  3,    0}}, // 1920x1080@RB
//	{{113,  0, 0, (2<<4)|0}, {15400,  5995, 2080, 1235}, {112,  32, 1920, 1200}, {0,  32, 6,  80,  26,  48,  3,    0}}, // 1920x1200@RB

////		Video-format (60Hz)
////	  id1 id2 sub wide|rep    pixel   freq  Htot  Vtot     x    y   Hact  Vact                 BT656
//	{{  8,  9, 1, (1<<4)|1}, { 2700,  6000, 1716,  262}, {238,  18, 1440,  240}, {0, 124, 3, 114,  15,  38,  4,    0}}, // 8,9(1) 1440 x 240p
//	{{  8,  9, 2, (1<<4)|1}, { 2700,  6000, 1716,  263}, {238,  18, 1440,  240}, {0, 124, 3, 114,  15,  38,  4,    0}}, // 8,9(2) 1440 x 240p
//	{{ 10, 11, 0, (1<<4)|1}, { 5400,  6000, 3432,  525}, {476,  18, 2880,  480}, {0, 248, 3, 228,  15,  76,  4, 1716}}, // 10,11 2880 x 480p
//	{{ 12, 13, 1, (1<<4)|1}, { 5400,  6000, 3432,  262}, {476,  18, 2880,  240}, {0, 248, 3, 228,  15,  76,  4,    0}}, // 12,13(1) 2280 x 240p
//	{{ 12, 13, 2, (1<<4)|1}, { 5400,  6000, 3432,  263}, {476,  18, 2880,  240}, {0, 248, 3, 228,  15,  76,  4,    0}}, // 12,13(2) 2280 x 240p
//	{{ 14, 15, 0, (1<<4)|0}, { 5400,  6000, 1716,  525}, {244,  36, 1440,  480}, {0, 124, 6, 120,  30,  32,  9,    0}}, // 14, 15 1140 x 480p

////		Video-format (50Hz)
////	  id1 id2 sub wide|rep    pixel   freq  Htot  Vtot     x    y   Hact  Vact                 BT656
//	{{ 23, 24, 1, (1<<4)|1}, { 2700,  5000, 1728,  312}, {264,  22, 1440,  288}, {0, 126, 3, 138,  19,  24,  2,    0}}, // 23,24(1) 1440 x 288p
//	{{ 23, 24, 2, (1<<4)|1}, { 2700,  5000, 1728,  313}, {264,  22, 1440,  288}, {0, 126, 3, 138,  19,  24,  2,    0}}, // 23,24(2) 1440 x 288p
//	{{ 23, 24, 3, (1<<4)|1}, { 2700,  5000, 1728,  314}, {264,  22, 1440,  288}, {0, 126, 3, 138,  19,  24,  2,    0}}, // 23,24(3) 1440 x 288p
//	{{ 25, 26, 0, (1<<4)|1}, { 5400,  5000, 3456,  625}, {528,  22, 2880,  576}, {0, 252, 3, 276,  19,  48,  2, 1728}}, // 25, 26 2880 x 576p
//	{{ 27, 28, 1, (1<<4)|1}, { 5400,  5000, 3456,  312}, {528,  22, 2880,  288}, {0, 252, 3, 276,  19,  48,  2,    0}}, // 27,28(1) 2880 x 288p
//	{{ 27, 28, 2, (1<<4)|1}, { 5400,  5000, 3456,  313}, {528,  22, 2880,  288}, {0, 252, 3, 276,  19,  48,  3,    0}}, // 27,28(2) 2880 x 288p
//	{{ 27, 28, 3, (1<<4)|1}, { 5400,  5000, 3456,  314}, {528,  22, 2880,  288}, {0, 252, 3, 276,  19,  48,  4,    0}}, // 27,28(3) 2880 x 288p
//	{{ 29, 30, 0, (1<<4)|0}, { 5400,  5000, 1728,  625}, {264,  44, 1440,  576}, {0, 128, 5, 136,  39,  24,  5,    0}}, // 29,30 1440 x 576p

////		Video-format (etcHz)
////	  id1 id2 sub wide|rep    pixel   freq  Htot  Vtot     x    y   Hact  Vact                 BT656
//	{{ 32,  0, 0, (2<<4)|0}, { 7417,  2400, 2750, 1125}, {192,  41, 1920, 1080}, {0,  44, 5, 148,  36, 638,  4,    0}}, // 32(2) 1920 x 1080p
//	{{ 33,  0, 0, (2<<4)|0}, { 7425,  2500, 2640, 1125}, {192,  41, 1920, 1080}, {0,  44, 5, 148,  36, 528,  4,    0}}, // 33(3) 1920 x 1080p
//	{{ 34,  0, 0, (2<<4)|0}, { 7417,  3000, 2200, 1125}, {192,  41, 1920, 1080}, {0,  44, 5, 148,  36, 528,  4,    0}}, // 34(4) 1920 x 1080p
//	{{ 35, 36, 0, (1<<4)|0}, {10800,  5994, 3432,  525}, {488,  36, 2880,  480}, {0, 248, 6, 240,  30,  64, 10,    0}}, // 35, 36 2880 x 480p@59.94/60Hz
//	{{ 37, 38, 0, (1<<4)|0}, {10800,  5000, 3456,  625}, {528,  44, 2880,  576}, {0, 256, 5, 272,  40,  48,  5,    0}}, // 37, 38 2880 x 576p@50Hz
//	{{ 39,  0, 0, (2<<4)|0}, { 7200,  5000, 2304, 1250}, {352,  62, 1920, 1080}, {0, 168, 5, 184,  87,  32, 24,    0}}, // 39 1920 x 1080i@50Hz
//	{{ 40,  0, 0, (2<<4)|0}, {14850, 10000, 2640, 1125}, {192,  20, 1920, 1080}, {0,  44, 5, 148,  15, 528,  2, 1320}}, // 40 1920 x 1080i@100Hz
//	{{ 41,  0, 0, (2<<4)|0}, {14850, 10000, 1980,  750}, {260,  25, 1280,  720}, {0,  40, 5, 220,  20, 400,  5,    0}}, // 41 1280 x 720p@100Hz
//	{{ 42, 43, 0, (1<<4)|0}, { 5400, 10000,  864,  144}, {132,  44,  720,  576}, {0,  64, 5,  68,  39,  12,  5,    0}}, // 42, 43, 720 x 576p@100Hz
//	{{ 44, 45, 0, (1<<4)|1}, { 5400, 10000,  864,  625}, {264,  22, 1440,  576}, {0,  63, 3,  69,  19,  12,  2,  432}}, // 44, 45, 720 x 576i@100Hz, pix repl
//	{{ 46,  0, 0, (2<<4)|0}, {14835, 11988, 2200, 1125}, {192,  20, 1920, 1080}, {0,  44, 5, 149,  15,  88,  2, 1100}}, // 46, 1920 x 1080i@119.88/120Hz
//	{{ 47,  0, 0, (2<<4)|0}, {14835, 11988, 1650,  750}, {260,  25, 1280,  720}, {0,  40, 5, 220,  20, 110,  5, 1100}}, // 47, 1280 x 720p@119.88/120Hz
//	{{ 48, 49, 0, (1<<4)|0}, { 5400, 11988,  858,  525}, {122,  36,  720,  480}, {0,  62, 6,  60,  30,  16, 10,    0}}, // 48, 49 720 x 480p@119.88/120Hz
//	{{ 50, 51, 0, (1<<4)|1}, { 5400, 11988,  858,  525}, {119,  18,  720,  480}, {0,  62, 3,  57,  15,  19,  4,  491}}, // 50, 51 720 x 480i@119.88/120Hz
//	{{ 52, 53, 0, (1<<4)|0}, {10800, 20000,  864,  625}, {132,  44,  720,  576}, {0,  64, 5,  68,  39,  12,  5,    0}}, // 52, 53, 720 x 576p@200Hz
//	{{ 54, 55, 0, (1<<4)|1}, {10800, 20000,  864,  625}, {132,  22,  720,  576}, {0,  63, 3,  69,  19,  12,  2,  432}}, // 54, 55, 1440 x 720i @200Hz, pix repl
//	{{ 56, 57, 0, (1<<4)|0}, {10800, 24000,  858,  525}, {122,  36,  720,  480}, {0,  62, 6,  60,  30,  16,  9,    0}}, // 56, 57, 720 x 480p @239.76/240Hz
//	{{ 58, 59, 0, (1<<4)|1}, {10800, 24000,  858,  525}, {119,  18,  720,  480}, {0,  62, 3,  57,  15,  19,  4,  429}}, // 58, 59, 1440 x 480i @239.76/240Hz, pix repl

};
#endif	/* #if defined(SYSTEM_USE_MDIN340)||defined(SYSTEM_USE_MDIN380) */

// -----------------------------------------------------------------------------
// Exported function Prototype
// -----------------------------------------------------------------------------
/*  FILE_END_HERE */
