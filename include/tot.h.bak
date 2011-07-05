/*
 * =====================================================================================
 *
 *       Filename:  tot.h
 *
 *    Description:  Time Offset Table definition
 *
 *        Version:  1.0
 *        Created:  2011年06月03日 14时49分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  orion
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  _TOT_H_
#define  _TOT_H_
struct _time_offset_table {
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t reserved_future_use;
	uint8_t reserved1;
	uint16_t section_length;
	uint64_t UTC_time;
	uint8_t reserved2;
	uint16_t descriptors_loop_length;
	char* descriptors;
	uint32_t CRC_32;
};				/* ----------  end of struct _time_offset_table  ---------- */

typedef struct _time_offset_table TOT;



#define	TOT_TABLE_ID(b)			    (b[0])			/*  */

#define	TOT_SECTION_SYNX_IND(b)		    ((b[1] & 0x80) >> 7)			/*  */

#define	TOT_RESERVED_FUTURE_USD(b)	    ((b[1] & 0x40) >> 6)			/*  */

#define	TOT_RESERVED1(b)		    ((b[1] & 0x30) >> 4)			/*  */

#define	TOT_SECTION_LENGTH(b)		    (((b[1] & 0x0f) << 8) | b[2])			/*  */

#define	TOT_UTC_TIME(b)			    ((b[3] << 32) | (b[4] << 24) | (b[5] << 16) | (b[6] << 8) | b[7])			/*  */

#define	TOT_RESERVED2(b)		    ((b[8] & 0xf0) >> 4)			/*  */

#define	TOT_DESC_LOOP_LENGTH(b)		    (((b[8] & 0x0f) << 8) | b[9] )			/*  */

#define	TOT_CRC(b)			    ({ \
						int n = TOT_SECTION_LENGTH(b); \
						int l = n - 4; \
						int base = 3 + l; \
						((b[base] << 24) | (b[base + 1] << 16) | (b[base + 2] << 8) | b[base + 3]); \
						})			/*  */
#endif   /* ----- #ifndef _TOT_H_  ----- */

