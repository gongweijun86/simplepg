/*
 * structure.h
 *
 *  Created on: 2011-4-7
 *      Author: orion
 */

#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include	"ntypes.h"
#include	"log.h"
#include	"pat.h"
#include	"pmt.h"
#include	"nit.h"
#include	"sdt.h"
#include	"eit.h"
#include	"tsph.h"
#include	"pidlist.h"

#include	"epg.h"
/*-----------------------------------------------------------------------------
 * 函数声明 
 *-----------------------------------------------------------------------------*/

bool file_get_packet_start();
long set_stream_to_packet(uint packet, uint offset,FILE* f);

bool iserror(FILE* f);
int check_file(FILE *f);
void handle_packet(long packet,FILE* f);
int get_total_packet(FILE* f);

#endif /* _STRUCTURE_H_ */
