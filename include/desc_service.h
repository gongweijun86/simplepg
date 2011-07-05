/*
 * desc_service.h
 *
 *  Created on: Jun 24, 2011
 *      Author: orion
 */

#ifndef _DESC_SERVICE_H_
#define _DESC_SERVICE_H_

#include	"ntypes.h"
#include	"log.h"
#include	"structure.h"

struct _service_desc{
	uint8_t descriptor_tag;
	uint8_t descriptor_length;
	uint8_t service_type;
	uint8_t service_provider_name_length;
	char* provider_name;
	uint8_t service_name_length;
	char* service_name;
	void* next_desc;
};

typedef struct _service_desc ServiceDesc;

#define SERV_DESC_TAG(b)					(b[0])
#define SERV_DESC_LENGTH(b)					(b[1])
#define SERV_DESC_SERV_TYPE(b)				(b[2])
#define SERV_DESC_SERV_PRO_NAME_LENGTH(b)	(b[3])
#define SERV_DESC_SERV_NAME_LENGTH(b)		({	\
											int n = SERV_DESC_SERV_PRO_NAME_LENGTH(b); \
											int base = n + 4; \
											b[base]; \
											})

int decode_service_desc(byte* byteptr, int this_section_length,ServiceDesc* desc_service);
void free_service_desc(ServiceDesc* head);

#endif /* _DESC_SERVICE_H_ */
