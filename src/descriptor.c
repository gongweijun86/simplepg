/*
 * descriptor.c
 *
 *  Created on: Jun 23, 2011
 *      Author: orion
 */

#include "../include/descriptor.h"

void* decode_desc(byte* byteptr, int this_section_length) {
	byte* b = byteptr;
	int desc_len;
	int l = this_section_length;

	void* this_descriptor = NULL;

	switch (b[0]) {
	case 0x40: // network_name_descriptor
		//maybe NetworkNameDesc will be globle var
	{
		this_descriptor = (void*)malloc(sizeof(NetworkNameDesc));
		memset(this_descriptor, 0, sizeof(NetworkNameDesc));
		//NetworkNameDesc desc_network_name;
		desc_len = decode_network_name_desc(b, this_section_length,
				this_descriptor);
		b += desc_len;
		l -= desc_len;

		if(b < b + l){
			((NetworkNameDesc*)this_descriptor)->next_desc = decode_desc(b, l);
		}
	}
		break;
	case 0x41: {
		this_descriptor = (void*)malloc(sizeof(ServiceListDesc));
		memset(this_descriptor, 0, sizeof(ServiceListDesc));
		desc_len = decode_servicelist_desc(b, this_section_length,
				this_descriptor);
		b += desc_len;
		l -= desc_len;

		if(b < b + l){
			((ServiceListDesc*)this_descriptor)->next_desc = decode_desc(b, l);
		}
	}
		break;
	case 0x48: {
		this_descriptor = (void*)malloc(sizeof(ServiceDesc));
		memset(this_descriptor, 0, sizeof(ServiceDesc));
		desc_len = decode_service_desc(b, this_section_length,
				this_descriptor);
		b += desc_len;
		l -= desc_len;

		if(b < b + l){
			((ServiceDesc*)this_descriptor)->next_desc = decode_desc(b, l);
		}
	}
		break;
	case 0x4d: {
		this_descriptor = (void*)malloc(sizeof(ShortEventDesc));
		memset(this_descriptor, 0 ,sizeof(ShortEventDesc));
		desc_len = decode_short_evt_desc(b, this_section_length,
				this_descriptor);
		b += desc_len;
		l -= desc_len;

		if(b < b + l){
			((ShortEventDesc*)this_descriptor)->next_desc = decode_desc(b, l);
		}
	}
		break;
	default:
		// other descriptors we don't handle them,but we need their length,so we get it.
		desc_len = b[1] + 2 ;
		b += desc_len;
		l -= desc_len;

		if(b < b + l){
			this_descriptor = decode_desc(b, l);
		}
	}

	return this_descriptor;
}

void free_desc(void* phead){
	//void* this_descriptor = phead;
	byte* b = (byte*)phead;

	if(b == NULL){
	//	printf("b == NULL,should return!!!!!let's see!!!\n");
		return;
	}

	switch(b[0]){
	case 0x40:  // NetworkNameDesc
		free_network_name_desc((NetworkNameDesc*)phead);
		break;
	case 0x41: //ServiceListDesc
		free_servicelist_desc((ServiceListDesc*)phead);
		break;
	case 0x48: //ServiceDesc
		free_service_desc((ServiceDesc*)phead);
		break;
	case 0x4d: //ShortEventDesc
		free_short_evt_desc((ShortEventDesc*)phead);
		break;
	default:
		//free_desc();
		return;
	}
}

