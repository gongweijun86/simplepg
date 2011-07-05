#ifndef  _NIT_H_
#define  _NIT_H_

#include 	"ntypes.h"
#include 	"log.h"
#include 	"descriptor.h"


struct _transport_stream_loop {
	uint16_t transport_stream_id;
	uint16_t original_network_id;
	uint8_t reserved_future_use;
	uint16_t transport_descriptors_length;
	struct _transport_stream_loop* next_tsl;
	void* tsl_first_desc;
};				/* ----------  end of struct _transport_stream_loop  ---------- */

typedef struct _transport_stream_loop TSL;

struct _network_information_table {
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t reserved_future_use1;
	uint8_t reserved1;
	uint16_t section_length;
	uint16_t network_id;
	uint8_t reserved2;
	uint8_t version_number;
	uint8_t current_next_indicator;
	uint8_t section_number;
	uint8_t last_section_number;
	uint8_t reserved_future_use2;
	uint16_t network_descriptor_length;
	void* first_network_name_desc;
	uint8_t reserved_future_use3;
	uint16_t transport_stream_loop_length;
	TSL* first_tsl;
	uint32_t CRC_32;
};				/* ----------  end of struct _network_information_table  ---------- */

typedef struct _network_information_table NIT;


#define	NIT_TABLE_ID(b)			(b[0])			/*  */

#define	NIT_SECTION_SYNX(b)		((b[1] & 0x80) >> 7)			/*  */

#define	NIT_RESERVED_FUTURE_USD1(b)	((b[1] & 0x40) >> 6)			/*  */

#define	NIT_RESERVED1(b)		((b[1] & 0x30) >> 4)		    	/*  */

#define	NIT_SECTION_LENGTH(b)		(((b[1] & 0x0f) << 8) | b[2])			/*  */

#define	NIT_NETWORK_ID(b)		((b[3] << 8) | b[4])			/*  */

#define	NIT_RESERVED2(b)		((b[5] & 0xc0) >> 6)			/*  */

#define	NIT_VERSION_NUM(b)		((b[5] & 0x3e) >> 1)			/*  */

#define	NIT_CURRENT_NEXT_IND(b)			(b[5] & 0x01)			/*  */

#define	NIT_SECTION_NUM(b)		(b[6])			/*  */

#define	NIT_LST_SECTION_NUM(b)		(b[7])			/*  */

#define	NIT_RESERVED_FUTURE_USD2(b)	((b[8] & 0xf0) >> 4)			/*  */

#define	NIT_NETWORK_DESC_LENGTH(b)	(((b[8] & 0x0f) << 8)| b[9])		/*  */

#define	NIT_RESERVED_FUTURE_USD3(b)	({ \
					    int l = NIT_NETWORK_DESC_LENGTH(b); \
					    int base = 10 + l; \
					    ((b[base] & 0xf0) >> 4); \
					    })			/*  */

#define	NIT_TS_LOOP_LENGTH(b)		({ \
					    int l = NIT_NETWORK_DESC_LENGTH(b); \
					    int base = 10 + l; \
					    (((b[base] & 0x0f) << 8) | b[base + 1]); \
					    })			/*  */

//transport stream loop macros
#define	NIT_TSL_TSID(b)						((b[0] << 8) | b[1])
#define	NIT_TSL_ORIGINAL_NETWORK_ID(b)		((b[2] << 8) | b[3])
#define	NIT_TSL_RESERVED_FUTURE_USD(b)		((b[4] & 0xf0) >> 4)
#define	NIT_TSL_TRANS_DESC_LENGTH(b)		(((b[4] & 0x0f) << 8) | b[5])

#define	NIT_CRC(b)			({ \
					    int n = NIT_SECTION_LENGTH(b); \
					    int l = n - 4; \
					    int base = 3 + l; \
					    ((b[base] << 24) | (b[base + 1] << 16)| (b[base + 2] << 8) | b[base + 3]); \
					    })			/*  */

byte* parse_NIT(byte* byteptr, int this_section_length, NIT* nit);
int decode_transport_stream_loop(byte* byteptr, int this_section_length, TSL* tsl);
void free_nit(NIT* nit);
void free_tsl(NIT* nit);
//void free_network_desc(NIT* nit);

#endif   /* ----- #ifndef _NIT_H_  ----- */

