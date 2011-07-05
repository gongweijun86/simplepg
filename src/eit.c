/*
 * eit.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include 	"../include/eit.h"

int decode_eit_desc(byte* byteptr, int this_section_length, EIT_DESC* desc_eit){
	byte* b = byteptr;
	int l = this_section_length;

	desc_eit->event_id = EIT_DESC_EVENT_ID(b);
	desc_eit->start_date = EIT_DESC_START_DATE(b);
	desc_eit->start_time = EIT_DESC_START_TIME(b);
	desc_eit->duration = EIT_DESC_DURATION(b);
	desc_eit->running_status = EIT_DESC_RUN_STATUS(b);
	desc_eit->free_CA_mode = EIT_DESC_FREE_CA_MODE(b);
	desc_eit->descriptors_loop_length = EIT_DESC_LOOP_LENGTH(b);
/*

	printf("desc_eit->event_id:%d\t",desc_eit->event_id);
	printf("desc_eit->start_date:%d\t",desc_eit->start_date);
	printf("desc_eit->start_time:%d\t",desc_eit->start_time);
	printf("desc_eit->duration:%d\t",desc_eit->duration);
	printf("desc_eit->running_status:%d\t",desc_eit->running_status);
	printf("desc_eit->free_CA_mode:%d\t",desc_eit->free_CA_mode);
	printf("desc_eit->descriptors_loop_length:%d\n",desc_eit->descriptors_loop_length);
*/
	debuglog("desc_eit->event_id:%d\t",desc_eit->event_id);
	debuglog("desc_eit->start_date:0x%04x\t",desc_eit->start_date);
	debuglog("desc_eit->start_time:0x%06x\t",desc_eit->start_time);
	debuglog("desc_eit->duration:0x%06x\t",desc_eit->duration);
	debuglog("desc_eit->running_status:%d\t",desc_eit->running_status);
	debuglog("desc_eit->free_CA_mode:%d\t",desc_eit->free_CA_mode);
	debuglog("desc_eit->descriptors_loop_length:%d\n",desc_eit->descriptors_loop_length);

	int len = desc_eit->descriptors_loop_length;
	byte* desc_start = &b[12];

	if(len > 0){
		desc_eit->first_desc = decode_desc(desc_start, len);
	}

	b += (desc_eit->descriptors_loop_length + 12);
	l -= (desc_eit->descriptors_loop_length + 12);
	if(l > 0){
		desc_eit->next_eit_desc = (EIT_DESC*)malloc(sizeof(EIT_DESC));
		memset(desc_eit->next_eit_desc, 0, sizeof(EIT_DESC));
		decode_eit_desc(b, l, desc_eit->next_eit_desc);
	}

	return (desc_eit->descriptors_loop_length + 12);
}

byte*
parse_EIT(byte* byteptr, int this_section_length, EIT* eit)
{
	byte* b = byteptr;

	eit->table_id = EIT_TABLE_ID(b);
	eit->section_syntax_indicator = EIT_SECTION_SYNX(b);
	eit->reserved_future_use1 = EIT_RESERVED_FUTURE_USD1(b);
	eit->reserved1 = EIT_RESERVED1(b);
	eit->section_length = EIT_SECTION_LENGTH(b);
	eit->service_id = EIT_SERVICE_ID(b);
	eit->reserved2 = EIT_RESERVED2(b);
	eit->version_number = EIT_VERSION_NUM(b);
	eit->current_next_indicator = EIT_CURRENT_NEXT_IND(b);
	eit->section_number = EIT_SECTION_NUM(b);
	eit->last_section_number = EIT_LST_SECTION_NUM(b);
	eit->transport_stream_id = EIT_TS_ID(b);
	eit->original_network_id = EIT_ORIGINAL_NETWORK_ID(b);
	eit->segment_last_section_number = EIT_SEG_LST_SECTION_NUM(b);
	eit->last_table_id = EIT_LST_TABLE_ID(b);
	eit->CRC_32 = EIT_CRC(b);
/*

	printf("eit->CRC_32:%u\n",eit->CRC_32);

	printf("eit->table_id:%d\t",eit->table_id);
	printf("eit->section_length:%d\t",eit->section_length);
	printf("eit->version_number:%d\t",eit->version_number);
	printf("eit->section_number:%d\t",eit->section_number);
	printf("eit->transport_stream_id:%d\t",eit->transport_stream_id);
	printf("eit->original_network_id:%d\t",eit->original_network_id);
	printf("eit->segment_last_section_number:%d\t",eit->segment_last_section_number);
	printf("eit->last_table_id:%d\n",eit->last_table_id);
*/

	int len = eit->section_length - 15;
	byte* evt_start = &b[14];

	if(len > 0){
		eit->first_eit_desc = (EIT_DESC*)malloc(sizeof(EIT_DESC));
		memset(eit->first_eit_desc, 0, sizeof(EIT_DESC));
		decode_eit_desc(evt_start, len, eit->first_eit_desc);
	}

	b += (eit->section_length + 3);

	return b;
}
void free_eit_desc(EIT* eit){
	EIT_DESC* head = eit->first_eit_desc;
	EIT_DESC* temp;

	while(head != NULL){
		free_desc(head->first_desc);
		temp = head;
		head = temp->next_eit_desc;
		temp->next_eit_desc = NULL;
		free(temp);
	}
	//free(eit->first_eit_desc);
	eit->first_eit_desc = NULL;
}
void free_eit(EIT* eit){
	free_eit_desc(eit);
}

