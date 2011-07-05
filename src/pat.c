/*
 * pat.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include "../include/pat.h"

extern PIDList pidlist;

int decode_PAT_program(byte* byteptr, PROGRAM_MAP* program_map, int this_section_length) {
	byte* b = byteptr;
	int l = this_section_length;

	int pnum = PAT_PROGRAM_NUMBER(b);
	int re = PAT_PROGRAM_RESERVED(b);
	int pid = PAT_PMT_PID(b);

	program_map->program_number = pnum;
	program_map->pmt_PID = pid;
	program_map->reserved = re;
/*

	printf("program number:%d\t", pnum);
	printf("reserved:%d\t",re);
	printf("pid:0x%04x\n",pid);
*/
	debuglog("program number:%d\t", pnum);
	debuglog("reserved:%d\t",re);
	debuglog("pid:0x%04x\n",pid);


	set_pmt(pid,pnum,&pidlist);

	b += 4;
	l -= 4;
	if(b < b + l){
		program_map->next_program_map = (PROGRAM_MAP*)(malloc(sizeof(PROGRAM_MAP)));
		memset(program_map->next_program_map, 0, sizeof(PROGRAM_MAP));
		decode_PAT_program(b, program_map->next_program_map, l);
	}

	return (this_section_length);
}

byte* parse_PAT(byte* byteptr, int this_section_length, PAT* pat) {
	byte* b = byteptr;

	pat->table_id = PAT_TABLE_ID(b);
	pat->section_syntax_indicator = PAT_SECTION_SYNX(b);
	pat->zero = PAT_ZERO(b);
	pat->reserved1 = PAT_RESERVED1(b);
	pat->section_length = PAT_SECTION_LENGTH(b);
	pat->transport_stream_id = PAT_TRANSPORT_STREAM_ID(b);
	pat->reserved2 = PAT_RESERVED2(b);
	pat->version_number = PAT_VERSION(b);
	pat->current_next_indicator = PAT_CURRENT_NEXT_IND(b);
	pat->section_number = PAT_SECTION_NUMBER(b);
	pat->last_section_number = PAT_LAST_SESSION_NUMBER(b);
	pat->CRC_32 = PAT_CRC(b);

	//printf("pat->CRC_32:%u\n",pat->CRC_32);

	if (pat->section_length > 9) // 5 bytes past section_length for header, 4 bytes for CRC32
	{
		pat->first_program_map = (PROGRAM_MAP*)malloc(sizeof(PROGRAM_MAP));
		memset(pat->first_program_map, 0, sizeof(PROGRAM_MAP));
		decode_PAT_program(b + 8,pat->first_program_map, pat->section_length - 9);
	}

	b += pat->section_length + 3; //set b to the end of the section

	return b;
}

void free_pat_program(PAT* pat){
	PROGRAM_MAP *head, *temp;
	head = pat->first_program_map;

	while(head != NULL){
		temp = head;
		head = temp->next_program_map;
		temp->next_program_map = NULL;
		free(temp);
	}
	//free(pat->first_program_map);
	pat->first_program_map = NULL;
}

void free_pat(PAT* pat){
	free_pat_program(pat);
}













