/*
 * desc_service_list.c
 *
 *  Created on: Jun 24, 2011
 *      Author: orion
 */
#include "../include/desc_service_list.h"

int decode_servicelist_desc(byte* byteptr, int this_section_length,ServiceListDesc* desc_servicelist){
	byte* b = byteptr;

	desc_servicelist->descriptor_tag = SLD_DESC_TAG(b);
	desc_servicelist->descriptor_length = SLD_DESC_LEN(b);

/*
	printf("servicelist->descriptor_tag:%d\t",desc_servicelist->descriptor_tag);
	printf("desc_servicelist->descriptor_length:%d\n",desc_servicelist->descriptor_length);
*/
	debuglog("servicelist->descriptor_tag:%d\t",desc_servicelist->descriptor_tag);
	debuglog("desc_servicelist->descriptor_length:%d\n",desc_servicelist->descriptor_length);

	int len = desc_servicelist->descriptor_length;
	byte* item_start = &b[2];
	while(len > 0){
		ServiceListItem sld_item;
		decode_servicelist_item(item_start,len,&sld_item);
		item_start += 3;
		len -= 3;
	}

	return (desc_servicelist->descriptor_length + 2);
}
int decode_servicelist_item(byte* byteptr, int this_section_length,ServiceListItem* item_servicelist){
	byte* b = byteptr;
	int l = this_section_length;

	item_servicelist->service_id = SLD_DESC_ITEM_ID(b);
	item_servicelist->service_type = SLD_DESC_ITEM_TYPE(b);

/*	printf("item_servicelist->service_id:%d\t",item_servicelist->service_id);
	printf("item_servicelist->service_type:%d\n",item_servicelist->service_type);*/
	debuglog("item_servicelist->service_id:%d\t",item_servicelist->service_id);
	debuglog("item_servicelist->service_type:%d\n",item_servicelist->service_type);

	return l;
}
void free_servicelist_desc(ServiceListDesc* head){
	free_desc(head->next_desc);
	head->next_desc = NULL;
	free(head);
	head = NULL;
}
