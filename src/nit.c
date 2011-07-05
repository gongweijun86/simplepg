/*
 * nit.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include "../include/nit.h"


int decode_transport_stream_loop(byte* byteptr, int this_section_length,TSL* tsl) {
	byte* b = byteptr;
	int l = this_section_length;

	tsl->transport_stream_id = NIT_TSL_TSID(b);
	tsl->original_network_id = NIT_TSL_ORIGINAL_NETWORK_ID(b);
	tsl->reserved_future_use = NIT_TSL_RESERVED_FUTURE_USD(b);
	tsl->transport_descriptors_length = NIT_TSL_TRANS_DESC_LENGTH(b);
/*

	printf("transport_stream_id:%d\t", tsl->transport_stream_id);
	printf("original_network_id:%d\t", tsl->original_network_id);
	printf("reserved_future_use:%d\t", tsl->reserved_future_use);
	printf("transport_descriptors_length:%d\n",	tsl->transport_descriptors_length);
*/
	debuglog("transport_stream_id:%d\t", tsl->transport_stream_id);
	debuglog("original_network_id:%d\t", tsl->original_network_id);
	debuglog("reserved_future_use:%d\t", tsl->reserved_future_use);
	debuglog("transport_descriptors_length:%d\n",	tsl->transport_descriptors_length);

	int len = tsl->transport_descriptors_length;
	byte* desc_start = &b[6];

	if(len > 0){
		tsl->tsl_first_desc = decode_desc(desc_start, len);
	}

	b += (tsl->transport_descriptors_length + 6);
	l -= (tsl->transport_descriptors_length + 6);

	if(b < b + l){
		tsl->next_tsl = (TSL*)malloc(sizeof(TSL));
		memset(tsl->next_tsl, 0, sizeof(TSL));
		decode_transport_stream_loop(desc_start, l, tsl->next_tsl);
	}

	return (tsl->transport_descriptors_length + 6);
}

byte* parse_NIT(byte* byteptr, int this_section_length, NIT* nit) {
	byte* b = byteptr;
//	int l = this_section_length;

	nit->table_id = NIT_TABLE_ID(b);
	nit->section_syntax_indicator = NIT_SECTION_SYNX(b);
	nit->reserved_future_use1 = NIT_RESERVED_FUTURE_USD1(b);
	nit->reserved1 = NIT_RESERVED1(b);
	nit->section_length = NIT_SECTION_LENGTH(b);
	nit->network_id = NIT_NETWORK_ID(b);
	nit->reserved2 = NIT_RESERVED2(b);
	nit->version_number = NIT_VERSION_NUM(b);
	nit->current_next_indicator = NIT_CURRENT_NEXT_IND(b);
	nit->section_number = NIT_SECTION_NUM(b);
	nit->last_section_number = NIT_LST_SECTION_NUM(b);
	nit->reserved_future_use2 = NIT_RESERVED_FUTURE_USD2(b);
	nit->network_descriptor_length = NIT_NETWORK_DESC_LENGTH(b);
	nit->reserved_future_use3 = NIT_RESERVED_FUTURE_USD3(b);
	nit->transport_stream_loop_length = NIT_TS_LOOP_LENGTH(b);
	nit->CRC_32 = NIT_CRC(b);
/*

	printf("nit->CRC_32:%u\n",nit->CRC_32);

	printf("nit->table_id:%d\t",nit->table_id);
	printf("nit->section_length:%d\t",nit->section_length);
	printf("nit->version_number:%d\t",nit->version_number);
	printf("nit->section_number:%d\t",nit->section_number);
	printf("nit->network_descriptor_length:%d\t",nit->network_descriptor_length);
	printf("nit->reserved_future_use3:%d\t",nit->reserved_future_use3);
	printf("nit->transport_stream_loop_length:%d\t",nit->transport_stream_loop_length);
	printf("nit->CRC_32:%d\n",nit->CRC_32);
*/

	debuglog("nit->table_id:%d\t",nit->table_id);
	debuglog("nit->section_length:%d\t",nit->section_length);
	debuglog("nit->version_number:%d\t",nit->version_number);
	debuglog("nit->section_number:%d\t",nit->section_number);
	debuglog("nit->network_descriptor_length:%d\t",nit->network_descriptor_length);
	debuglog("nit->reserved_future_use3:%d\t",nit->reserved_future_use3);
	debuglog("nit->transport_stream_loop_length:%d\t",nit->transport_stream_loop_length);
	debuglog("nit->CRC_32:%d\n",nit->CRC_32);

	int len = nit->network_descriptor_length;
	byte* desc_start = &b[10];

	if(len > 0){
		nit->first_network_name_desc = decode_desc(desc_start, len);
	}

	len = nit->network_descriptor_length;
	int loop_len = nit->transport_stream_loop_length;
	byte* tsl_start = &b[12 + len];

	if(loop_len > 0){
		nit->first_tsl = (TSL*)malloc(sizeof(TSL));
		memset(nit->first_tsl, 0, sizeof(TSL));
		decode_transport_stream_loop(tsl_start, loop_len, nit->first_tsl);
	}

	b += (nit->section_length + 3);//set b to the end ot the section

	return (b);
}

void free_tsl(NIT* nit){
	TSL* head = nit->first_tsl;
	TSL* temp;

	while(head != NULL){
		free_desc(head->tsl_first_desc);

		temp = head;
		head = temp->next_tsl;
		temp->next_tsl = NULL;
		free(temp);
	}
	//free(nit->first_tsl);
	nit->first_tsl = NULL;
}

void free_nit(NIT* nit){
	free_desc(nit->first_network_name_desc);
	free_tsl(nit);
}








