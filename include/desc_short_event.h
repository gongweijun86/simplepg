/*
 * desc_short_event.h
 *
 *  Created on: Jun 24, 2011
 *      Author: orion
 */

#ifndef _DESC_SHORT_EVENT_H_
#define _DESC_SHORT_EVENT_H_

#include	"ntypes.h"
#include	"log.h"
#include	"structure.h"

struct _short_event_desc{
	uint8_t descriptor_tag;
	uint8_t descriptor_length;
	uint32_t ISO_639_language_code;
	uint8_t event_name_length;
	char* event_name;
	uint8_t text_length;
	char* text;
	void* next_desc;
};

typedef struct _short_event_desc ShortEventDesc;

#define SHORT_EVT_DESC_TAG(b)			(b[0])
#define SHORT_EVT_DESC_LENGTH(b)		(b[1])
#define SHORT_EVT_DESC_LANG(b)			((b[2] << 16) | (b[3] << 8) | b[4])
#define SHORT_EVT_DESC_NAME_LENGTH(b)	(b[5])
#define	SHORT_EVT_DESC_TEXT_LENGTH(b)	({	\
											int n = SHORT_EVT_DESC_NAME_LENGTH(b); \
											int base = n + 6; \
											b[base]; \
										})

int decode_short_evt_desc(byte* byteptr, int this_section_length,ShortEventDesc* desc_short_event);
void free_short_evt_desc(ShortEventDesc* head);

#endif /* _DESC_SHORT_EVENT_H_ */
