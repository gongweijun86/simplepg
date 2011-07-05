/*
 * sdt.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include	"../include/sdt.h"

int decode_sdt_service(byte* byteptr, int this_section_length, SDT_SERVICE* sdt_service){
	byte* b = byteptr;
	int l = this_section_length;

	sdt_service->service_id = SDT_SERVICE_ID(b);
	sdt_service->reserved_future_use = SDT_SERVICE_RESERVED_USD(b);
	sdt_service->EIT_schedule_flag = SDT_SERVICE_EIT_SCHEDULE_FLAG(b);
	sdt_service->EIT_present_following_flag = SDT_SERVICE_EIT_PRESENT_FOLLOWING_FLAG(b);
	sdt_service->running_status = SDT_SERVICE_RUN_STATUS(b);
	sdt_service->free_CA_mode = SDT_SERVICE_FREE_CA_MODE(b);
	sdt_service->descriptors_loop_length = SDT_SERVICE_LOOP_LENGTH(b);

	debuglog("sdt_service->service_id:%d\t",sdt_service->service_id);
	debuglog("sdt_service->EIT_schedule_flag:%d\t",sdt_service->EIT_schedule_flag);
	debuglog("sdt_service->EIT_present_following_flag:%d\t",sdt_service->EIT_present_following_flag);
	debuglog("sdt_service->running_status:%d\t",sdt_service->running_status);
	debuglog("sdt_service->descriptors_loop_length:%d\n",sdt_service->descriptors_loop_length);
/*

		printf("sdt_service->service_id:%d\t",sdt_service->service_id);
		printf("sdt_service->EIT_schedule_flag:%d\t",sdt_service->EIT_schedule_flag);
		printf("sdt_service->EIT_present_following_flag:%d\t",sdt_service->EIT_present_following_flag);
		printf("sdt_service->running_status:%d\t",sdt_service->running_status);
		printf("sdt_service->descriptors_loop_length:%d\n",sdt_service->descriptors_loop_length);
*/

	int len = sdt_service->descriptors_loop_length;
	byte* serv_start = &b[5];

	if(len > 0){
		sdt_service->first_desc = decode_desc(serv_start,len);
	}

	b += (sdt_service->descriptors_loop_length + 5);
	l -= (sdt_service->descriptors_loop_length + 5);
	if(l > 0){
		sdt_service->next_sdt_service = (SDT_SERVICE*)malloc(sizeof(SDT_SERVICE));
		memset(sdt_service->next_sdt_service, 0, sizeof(SDT_SERVICE));
		decode_sdt_service(b, l, sdt_service->next_sdt_service);
	}

	return (sdt_service->descriptors_loop_length + 5);
}

byte*
parse_SDT(byte* byteptr, int this_section_length, SDT* sdt)
{
	byte* b = byteptr;

	sdt->table_id = SDT_TABLE_ID(b);
	sdt->section_syntax_indicator = SDT_SECTION_SYNX(b);
	sdt->reserved_future_use1 = SDT_RESERVED_FUTURE_USD1(b);
	sdt->reserved1 = SDT_RESERVED1(b);
	sdt->section_length = SDT_SECTION_LENGTH(b);
	sdt->transport_stream_id = SDT_TS_ID(b);
	sdt->reserved2 = SDT_RESERVED2(b);
	sdt->version_number = SDT_VERSION_NUM(b);
	sdt->current_next_indicator = SDT_CURRENT_NEXT_IND(b);
	sdt->section_number = SDT_SECTION_NUM(b);
	sdt->last_section_number = SDT_LST_SECTION_NUM(b);
	sdt->original_network_id = SDT_ORIGINAL_NETWORK_ID(b);
	sdt->reserved_future_use2 = SDT_RESERVED_FUTURE_USD2(b);
	sdt->CRC_32 = SDT_CRC(b);

//	printf("sdt->CRC_32:%u\n",sdt->CRC_32);

	debuglog("sdt->table_id:%d\t",sdt->table_id);
	debuglog("sdt->section_length:%d\t",sdt->section_length);
	debuglog("sdt->transport_stream_id:%d\t",sdt->transport_stream_id);
	debuglog("sdt->section_number:%d\t",sdt->section_number);
	debuglog("sdt->original_network_id:%d\n",sdt->original_network_id);
/*
	printf("sdt->table_id:%d\t",sdt->table_id);
	printf("sdt->section_length:%d\t",sdt->section_length);
	printf("sdt->transport_stream_id:%d\t",sdt->transport_stream_id);
	printf("sdt->section_number:%d\t",sdt->section_number);
	printf("sdt->original_network_id:%d\n",sdt->original_network_id);
*/

	int len = sdt->section_length - 12;
	byte* serv_start = &b[11];

	if(len > 0){
		sdt->first_sdt_service = (SDT_SERVICE*)malloc(sizeof(SDT_SERVICE));
		memset(sdt->first_sdt_service, 0, sizeof(SDT_SERVICE));
		decode_sdt_service(serv_start, len, sdt->first_sdt_service);
	}

	b += (sdt->section_length + 3);
	return b;
}

void free_sdt_service(SDT* sdt){
	SDT_SERVICE* head = sdt->first_sdt_service;
	SDT_SERVICE* temp;

	while(head != NULL){
		free_desc(head->first_desc);

		temp = head;
		head = temp->next_sdt_service;
		temp->next_sdt_service = NULL;
		free(temp);
	}
	sdt->first_sdt_service = NULL;
}

void free_sdt(SDT* sdt){
	free_sdt_service(sdt);
}


