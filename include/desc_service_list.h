/*
 * desc_service_list.h
 *
 *  Created on: Jun 24, 2011
 *      Author: orion
 */

#ifndef _DESC_SERVICE_LIST_H_
#define _DESC_SERVICE_LIST_H_

#include	"ntypes.h"
#include	"log.h"
#include	"structure.h"

struct _service_list_desc_item{
	uint16_t service_id;
	uint8_t service_type;
};

typedef struct _service_list_desc_item ServiceListItem;

struct _service_list_desc{
	uint8_t descriptor_tag;
	uint8_t descriptor_length;
	void* next_desc;
};

typedef struct _service_list_desc ServiceListDesc;

#define SLD_DESC_TAG(b)				(b[0])
#define SLD_DESC_LEN(b)				(b[1])

#define SLD_DESC_ITEM_ID(b)			((b[0] << 8) | b[1])
#define SLD_DESC_ITEM_TYPE(b)		(b[2])

int decode_servicelist_desc(byte* byteptr, int this_section_length,ServiceListDesc* desc_servicelist);
int decode_servicelist_item(byte* byteptr, int this_section_length,ServiceListItem* item_servicelist);

void free_servicelist_desc(ServiceListDesc* head);
#endif /* _DESC_SERVICE_LIST_H_ */
