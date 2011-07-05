#ifndef  _EIT_H_
#define  _EIT_H_


#include 	"ntypes.h"
#include 	"log.h"
#include 	"descriptor.h"


struct _eit_desc {
	uint16_t event_id;
	uint16_t start_date;
	uint32_t start_time;
	uint32_t duration;
	uint8_t running_status;
	uint8_t free_CA_mode;
	uint16_t descriptors_loop_length;
	void* first_desc;
	struct _eit_desc* next_eit_desc;
};				/* ----------  end of struct _eit_desc  ---------- */

typedef struct _eit_desc EIT_DESC;

struct _event_information_table {
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t reserved_future_use1;
	uint8_t reserved1;
	uint16_t section_length;
	uint16_t service_id;
	uint8_t reserved2;
	uint8_t version_number;
	uint8_t current_next_indicator;
	uint8_t section_number;
	uint8_t last_section_number;
	uint16_t transport_stream_id;
	uint16_t original_network_id;
	uint8_t segment_last_section_number;
	uint8_t last_table_id;
	EIT_DESC* first_eit_desc;
	uint32_t CRC_32;
};				/* ----------  end of struct _event_information_table  ---------- */

typedef struct _event_information_table EIT;


#define	EIT_TABLE_ID(b)			(b[0])			/*  */

#define	EIT_SECTION_SYNX(b)		((b[1] & 0x80) >> 7)			/*  */

#define	EIT_RESERVED_FUTURE_USD1(b)	((b[1] & 0x40) >> 6)			/*  */

#define	EIT_RESERVED1(b)		((b[1] & 0x30) >> 4)			/*  */

#define	EIT_SECTION_LENGTH(b)		(((b[1] & 0x0f) << 8) | b[2])			/*  */

#define	EIT_SERVICE_ID(b)		((b[3] << 8) | b[4])			/*  */

#define	EIT_RESERVED2(b)		((b[5] & 0xc0) >> 6)	/*  */

#define	EIT_VERSION_NUM(b)		((b[5] & 0x3e) >> 1)			/*  */

#define	EIT_CURRENT_NEXT_IND(b)			(b[5] & 0x01)			/*  */

#define	EIT_SECTION_NUM(b)		(b[6])			/*  */

#define	EIT_LST_SECTION_NUM(b)		(b[7])			/*  */

#define	EIT_TS_ID(b)			((b[8] << 8) | b[9])			/*  */

#define	EIT_ORIGINAL_NETWORK_ID(b)	((b[10] << 8) | b[11])			/*  */

#define	EIT_SEG_LST_SECTION_NUM(b)	(b[12])			/*  */

#define	EIT_LST_TABLE_ID(b)		(b[13])			/*  */
/////////////////////////////////////////////////////////////
#define	EIT_DESC_EVENT_ID(b)		((b[0] << 8) | b[1])			/*  */

#define	EIT_DESC_START_DATE(b)		((b[2] << 8) | b[3] )			/*  */

#define	EIT_DESC_START_TIME(b)		((b[4] << 16) | (b[5] << 8) | b[6] )			/*  */

#define	EIT_DESC_DURATION(b)		((b[7] << 16) | (b[8] << 8) | b[9])			/*  */

#define	EIT_DESC_RUN_STATUS(b)		((b[10] & 0xe0) >> 5)			/*  */

#define	EIT_DESC_FREE_CA_MODE(b)	((b[10] & 0x10) >> 4)			/*  */

#define	EIT_DESC_LOOP_LENGTH(b)		(((b[10] & 0x0f) << 8) | b[11])			/*  */
////////////////////////////////////////////////////////////

#define	EIT_CRC(b)			({ \
					    int n = EIT_SECTION_LENGTH(b); \
					    int l = n -4; \
					    int base = 3 + l; \
					    ((b[base] << 24) | (b[base + 1] << 16) | (b[base + 2] << 8) | b[base + 3]); \
					    })			/*  */

byte* parse_EIT(byte* byteptr, int this_section_length, EIT* eit);
int decode_eit_desc(byte* byteptr, int this_section_length, EIT_DESC* desc_eit);

void free_eit_desc(EIT* eit);
void free_eit(EIT* eit);

#endif   /* ----- #ifndef _EIT_H_  ----- */

