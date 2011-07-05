#ifndef  _PMT_H_
#define  _PMT_H_


#include	"ntypes.h"
#include 	"log.h"
#include	"pidlist.h"

struct _es_info { 
	uint8_t stream_type;
	uint8_t reserved1;
	uint16_t elementary_PID;
	uint8_t reserved2;
	uint16_t ES_info_length;
	struct _es_info* next_esinfo;
};				/* ----------  end of struct _es_info  ---------- */

typedef struct _es_info ESINFO;

struct _program_map_table {
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t zero;
	uint8_t reserved1;
	uint16_t section_length;
	uint16_t program_number;
	uint8_t reserved2;
	uint8_t version_number;
	uint8_t current_next_indicator;
	uint8_t section_number;
	uint8_t last_section_number;
	uint8_t reserved3;
	uint16_t PCR_PID;
	uint8_t reserved4;
	uint16_t program_info_length;
	ESINFO* first_esinfo;
	uint32_t CRC_32;
};				/* ----------  end of struct program_map_table  ---------- */

typedef struct _program_map_table PMT;

/*
 * macros for pmt
 * b => pmt's first address
 */

#define PMT_TABLE_ID(b)				(b[0])
#define PMT_SECTION_SYNX(b)			((b[1] & 0x80) >> 7)
#define PMT_ZERO(b)					((b[1] & 0x40) >> 6)
#define PMT_RESERVED1(b)			((b[1] & 0x30) >> 4)
#define PMT_SECTION_LENGTH(b)		((b[1] & 0x0f) << 8 | b[2])
#define PMT_PROGRAM_NUMBER(b)		((b[3] << 8) | b[4])
#define PMT_RESERVED2(b)			((b[5] & 0xc0) >> 6)
#define PMT_VERSION(b)				((b[5] & 0x3e) >> 1)
#define PMT_CURRENT_NEXT_IND(b)		(b[5] & 0x01)
#define PMT_SECTION_NUMBER(b)		(b[6])
#define PMT_LAST_SECTION_NUMBER(b)	(b[7])
#define PMT_RESERVED3(b)			((b[8] & 0xe0) >> 5)
#define PMT_PCR_PID(b)				((b[8] & 0x1f) << 8 | b[9])
#define PMT_RESERVED4(b)			((b[10] & 0xf0) >> 4)
#define PMT_PROGRAM_INFO_LENGTH(b)		((b[10] & 0x0f) << 8 | b[11])


#define PMT_ESINFO_STREAM_TYPE(b)	(b[0])

#define	PMT_ESINFO_RESERVED1(b)		((b[1] & 0xe0) >> 5)		/*  */

#define	PMT_ESINFO_ELEPID(b)		((b[1] & 0x1f) << 8 | b[2])/*  */

#define PMT_ESINFO_RESERVED2(b)		(b[3] & 0xf0)				/*  */

#define	PMT_ESINFO_LENGTH(b)		((b[3] & 0x0f) << 8 | b[4])/*  */

#define	PMT_CRC(b)				({ \
						   int n = PMT_SECTION_LENGTH(b); \
						   int l = n - 4; \
						   int base = 3 + l; \
						    (b[base] << 24) | (b[base + 1] << 16) | (b[base + 2] << 8) | b[base + 3]; \
						    })/*  */

byte* parse_PMT(byte* byteptr, int this_section_length,PMT* pmt);
int decode_esinfo(byte* byteptr, int this_section_length,ESINFO* esinfo);
void free_pmt(PMT* pmt);

#endif   /* ----- #ifndef _PMT_H_  ----- */

