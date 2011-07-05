#ifndef  _PAT_H_
#define  _PAT_H_

#include	"ntypes.h"
#include	"log.h"
#include 	"pidlist.h"

struct _program_map {
	uint16_t program_number;
	uint8_t reserved;
	uint16_t pmt_PID;
	struct _program_map* next_program_map;
};				/* ----------  end of struct program_map  ---------- */

typedef struct _program_map PROGRAM_MAP;
struct _program_assocation_table {
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t zero;
	uint8_t reserved1;
	uint16_t section_length;
	uint16_t transport_stream_id;
	uint8_t reserved2;
	uint8_t version_number;
	uint8_t current_next_indicator;
	uint8_t section_number;
	uint8_t last_section_number;
	PROGRAM_MAP* first_program_map;
	uint32_t CRC_32;
};				/* ----------  end of struct program_assocation_table  ---------- */

typedef struct _program_assocation_table PAT; 


/*
 * macros for pat
 * b => pat's first address
 */
#define PAT_TABLE_ID(b)				(b[0])

#define PAT_SECTION_SYNX(b)			((b[1] & 0x80) >> 7)

#define	PAT_ZERO(b)				((b[1] & 0x40) >> 6)/*  */

#define	PAT_RESERVED1(b)			((b[1] & 0x30) >> 4)			/*  */

#define PAT_SECTION_LENGTH(b)			((b[1] & 0x0f) << 8 | b[2])

#define PAT_TRANSPORT_STREAM_ID(b)		(b[3] | b[4])

#define PAT_RESERVED2(b)			((b[5] & 0xc0) >> 6)

#define PAT_VERSION(b)				((b[5] & 0x3e) >> 1)

#define PAT_CURRENT_NEXT_IND(b)			(b[5] & 0x01)

#define PAT_SECTION_NUMBER(b)			(b[6])

#define PAT_LAST_SESSION_NUMBER(b)		(b[7])


#define PAT_PROGRAM_NUMBER(b)			((b[0] << 8) | b[1])

#define PAT_PMT_PID(b)				((b[2] & 0x1f) << 8 | b[3])

#define PAT_PROGRAM_RESERVED(b)			((b[2] & 0xe0) >> 5)

#define PAT_CRC(b)				({ \
						    int n = PAT_SECTION_LENGTH(b); \
						    int l = n - 4; \
						    int base = 3 + l; \
						    (b[base] << 24) | (b[base + 1] << 16) | (b[base + 2] << 8) | b[base + 3]; \
						    }) 

byte* parse_PAT(byte* byteptr, int this_section_length,PAT* pat);
int decode_PAT_program(byte* byteptr, PROGRAM_MAP* program_map, int this_section_length);
void free_pat_program(PAT* pat);
void free_pat(PAT* pat);

#endif   /* ----- #ifndef _PAT_H_  ----- */

