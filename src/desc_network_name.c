/*
 * desc_network_name.c
 *
 *  Created on: Jun 24, 2011
 *      Author: orion
 */
#include "../include/desc_network_name.h"

int decode_network_name_desc(byte* byteptr, int this_section_length,NetworkNameDesc* desc_network_name){
	byte* b = byteptr;

	desc_network_name->descriptor_tag = NETWORKNAME_DESC_TAG(b);
	desc_network_name->descriptor_length = NETWORKNAME_DESC_LENGTH(b);

	desc_network_name->network_name = (char*)calloc(desc_network_name->descriptor_length + 1, sizeof(char));
	strncpy(desc_network_name->network_name, (char*)&b[2], desc_network_name->descriptor_length);

/*	printf("descriptor_tag:%d:\t",desc_network_name->descriptor_tag);
	printf("descriptor_length:%d\t",desc_network_name->descriptor_length);
	printf("network_name:%s\n",desc_network_name->network_name);*/
	debuglog("descriptor_tag:%d:\t",desc_network_name->descriptor_tag);
	debuglog("descriptor_length:%d\t",desc_network_name->descriptor_length);
	debuglog("network_name:%s\n",desc_network_name->network_name);

	return (desc_network_name->descriptor_length + 2);
}
void free_network_name_desc(NetworkNameDesc* head){
	free(head->network_name);
	head->network_name = NULL;
	free_desc(head->next_desc);
	head->next_desc = NULL;
	free(head);
	head = NULL;
}
