/*
 * =====================================================================================
 *
 *       Filename:  tdt.h
 *
 *    Description:  Time Date Table definition
 *
 *        Version:  1.0
 *        Created:  2011年06月03日 14时46分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  orion
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  _TDT_H_
#define  _TDT_H_
struct _time_date_table {
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t reserved_future_use;
	uint8_t reserved;
	uint16_t section_length;
	uint64_t UTC_time;
};				/* ----------  end of struct _time_date_table  ---------- */

typedef struct _time_date_table TDT;



#define	TDT_TABLE_ID(b)			(b[0])			/*  */

#define	TDT_SECTION_SYNX_IND(b)		((b[1] & 0x80) >> 7)			/*  */

#define	TDT_RESERVED_FUTURE_USD(b)	((b[1] & 0x40) >> 6)			/*  */

#define	TDT_RESERVED(b)			((b[1] & 0x30) >> 4)			/*  */

#define	TDT_SECTION_LENGTH(b)		(((b[1] & 0x0f) << 8) | b[2])			/*  */

#define	TDT_UTC_TIME(b)			((b[3] << 32) | (b[4] << 24) | (b[5] << 16) | (b[6] << 8) | b[7])			/*  */

#endif   /* ----- #ifndef _TDT_H_  ----- */

