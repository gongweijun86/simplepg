#ifndef  _TSPH_H_
#define  _TSPH_H_

#include	"ntypes.h"
#include 	"log.h"
#include 	"pidlist.h"


struct _transport_stream_packet_head {
	uint8_t sync;
	uint8_t transport_error_indicator;
	uint8_t payload_unit_start_indicator;
	uint8_t transport_priority;
	uint16_t PID;
	uint8_t transport_scrambling;
	uint8_t adaptation_field_control;
	uint8_t continuity_counter;
};				/* ----------  end of struct transport_stream_packet_head  ---------- */

typedef struct _transport_stream_packet_head TSPH;

/*
 * macros for accessing mpeg-2 ts packets headers
 * b => ts packets' first address
 */

#define TS_SYNC_BYTE(b)		(b[0])
#define TS_ERROR(b)			((b[1] & 0x80) >> 7)
#define TS_PAYLOAD_START(b)	((b[1] & 0x40) >> 6)
#define TS_PRIORITY(b)		((b[1] & 0x20) >> 5)
#define TS_PID(b)			(((b[1] & 0x1f) << 8) | b[2])

#define TS_SCRAMBLING(b)	((b[3] & 0xc0) >> 6)
#define TS_ADAPT_CTL(b)		((b[3] & 0x30) >> 4)
#define TS_CONT_COUNT(b)	(b[3] & 0x0f)

byte* parse_TS(byte *sec_start,int this_section_length,TSPH *tsph);

#endif   /* ----- #ifndef _TSPH_H_  ----- */

