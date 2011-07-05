/*
 * pidlist.h
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#ifndef _PIDLIST_H_
#define _PIDLIST_H_


#include "ntypes.h"

struct _pid_list
{
	uint PID[8192];
	uint prognum[8192];
};

typedef struct _pid_list PIDList;

void init_pidlist(PIDList* pidlist);
bool is_known_pid(uint pid,PIDList* pidlist);
void set_known_pid(uint pid,PIDList* pidlist);
bool is_pmt(uint pid,PIDList* pidlist);
void set_pmt(uint pid,uint prognum,PIDList* pidlist);
bool is_si(uint pid,PIDList* pidlist);
void set_si(uint pid,PIDList* pidlist);


#endif /* _PIDLIST_H_ */
