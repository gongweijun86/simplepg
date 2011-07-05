/*
 * pmt.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include "../include/pmt.h"

extern PIDList pidlist;

int decode_esinfo(byte* byteptr, int this_section_length,ESINFO* esinfo){
	byte* b = byteptr;
	int l = this_section_length;

	esinfo->stream_type = PMT_ESINFO_STREAM_TYPE(b);
	esinfo->reserved1 = PMT_ESINFO_RESERVED1(b);
	esinfo->elementary_PID = PMT_ESINFO_ELEPID(b);
	esinfo->reserved2 = PMT_ESINFO_RESERVED2(b);
	esinfo->ES_info_length = PMT_ESINFO_LENGTH(b);

	set_known_pid(esinfo->elementary_PID, &pidlist);

	if(esinfo->ES_info_length > 0){
		// here we don't need the information of the descriptor,so we don't decode them now.
	}

	debuglog("esinfo->stream_type:%d\t",esinfo->stream_type);
	debuglog("esinfo->reserved1:%d\t",esinfo->reserved1);
	debuglog("esinfo->elementary_PID:0x%04x\t",esinfo->elementary_PID);
	debuglog("esinfo->reserved2:%d\t",esinfo->reserved2);
	debuglog("esinfo->ES_info_length:%d\n",esinfo->ES_info_length);
/*
	printf("esinfo->stream_type:%d\t",esinfo->stream_type);
	printf("esinfo->reserved1:%d\t",esinfo->reserved1);
	printf("esinfo->elementary_PID:0x%04x\t",esinfo->elementary_PID);
	printf("esinfo->reserved2:%d\t",esinfo->reserved2);
	printf("esinfo->ES_info_length:%d\n",esinfo->ES_info_length);
*/

	b += (5 + esinfo->ES_info_length);
	l -= (5 + esinfo->ES_info_length);
	if(b < b + l){
		esinfo->next_esinfo = (ESINFO*)(malloc(sizeof(ESINFO)));
		memset(esinfo->next_esinfo, 0, sizeof(ESINFO));
		decode_esinfo(b, l, esinfo->next_esinfo);
	}


	return (esinfo->ES_info_length + 5);
}

byte*
parse_PMT(byte* byteptr, int this_section_length,PMT* pmt)
{
	byte* b = byteptr;
	//int l = this_section_length;

	pmt->table_id = PMT_TABLE_ID(b);
	pmt->section_syntax_indicator = PMT_SECTION_SYNX(b);
	pmt->zero = PMT_ZERO(b);
	pmt->reserved1 = PMT_RESERVED1(b);
	pmt->section_length = PMT_SECTION_LENGTH(b);
	pmt->program_number = PMT_PROGRAM_NUMBER(b);
	pmt->reserved2 = PMT_RESERVED2(b);
	pmt->version_number = PMT_VERSION(b);
	pmt->current_next_indicator = PMT_CURRENT_NEXT_IND(b);
	pmt->section_number = PMT_SECTION_NUMBER(b);
	pmt->last_section_number = PMT_LAST_SECTION_NUMBER(b);
	pmt->reserved3 = PMT_RESERVED3(b);
	pmt->PCR_PID = PMT_PCR_PID(b);
	pmt->reserved4 = PMT_RESERVED4(b);
	pmt->program_info_length = PMT_PROGRAM_INFO_LENGTH(b);
	pmt->CRC_32 = PMT_CRC(b);

	debuglog("pmt->table_id:%d\t",pmt->table_id);
	debuglog("pmt->section_length:%d\t",pmt->section_length);
	debuglog("pmt->program_number:%d\t",pmt->program_number);
	debuglog("pmt->current_next_indicator:%d\t",pmt->current_next_indicator);
	debuglog("pmt->section_number:%d\t",pmt->section_number);
	debuglog("pmt->last_section_number:%d\t",pmt->last_section_number);
	debuglog("pmt->PCR_PID:%d\t",pmt->PCR_PID);
	debuglog("pmt->program_info_length:%d\n",pmt->program_info_length);
/*
	printf("pmt->table_id:%d\t",pmt->table_id);
	printf("pmt->section_length:%d\t",pmt->section_length);
	printf("pmt->program_number:%d\t",pmt->program_number);
	printf("pmt->current_next_indicator:%d\t",pmt->current_next_indicator);
	printf("pmt->section_number:%d\t",pmt->section_number);
	printf("pmt->last_section_number:%d\t",pmt->last_section_number);
	printf("pmt->PCR_PID:%d\t",pmt->PCR_PID);
	printf("pmt->program_info_length:%d\n",pmt->program_info_length);
*/

	if(pmt->program_info_length > 0){
		//here the descriptor does no meaning for us,so we don't decode them.
	}

	int len = pmt->section_length - pmt->program_info_length - 13;
	byte* esinfo_start = &b[12 + pmt->program_info_length];

	if(len > 0){
		pmt->first_esinfo = (ESINFO*)malloc(sizeof(ESINFO));
		memset(pmt->first_esinfo, 0, sizeof(ESINFO));
		decode_esinfo(esinfo_start, len, pmt->first_esinfo);
	}

	b += (pmt->section_length + 3);

	return b;
}

void free_pmt_esinfo(PMT* pmt){
	ESINFO *head, *temp;
	head = pmt->first_esinfo;

	while(head != NULL){
		temp = head;
		head = temp->next_esinfo;
		temp->next_esinfo = NULL;
		free(temp);
	}
	//free(pmt->first_esinfo);
	pmt->first_esinfo = NULL;
}

void free_pmt(PMT* pmt){
	free_pmt_esinfo(pmt);
}
