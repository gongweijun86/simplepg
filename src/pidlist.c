/*
 * pidlist.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */
#include "../include/pidlist.h"

PIDList pidlist;

void
init_pidlist(PIDList* pidlist)
{
	int i = 0;
	for (i = 0; i < 0x2000; i++)
	{
		(pidlist)->PID[i] = 0;
		(pidlist)->prognum[i] = 0;
	}
	set_known_pid(0x0000, pidlist);	// PAT
	set_si(0x0000,pidlist);
	set_known_pid(0x0001, pidlist);	// CAT
	set_si(0x0001,pidlist);
	set_known_pid(0x0010, pidlist);	// NIT
	set_si(0x0010,pidlist);
	set_known_pid(0x0011, pidlist);	// SDT
	set_si(0x0011,pidlist);
	set_known_pid(0x0012, pidlist);	// EIT
	set_si(0x0012,pidlist);
	set_known_pid(0x0013, pidlist);	// RST
	set_si(0x0013,pidlist);
	set_known_pid(0x0014, pidlist);	// TOT / TDT
	set_si(0x0014,pidlist);
}

bool
is_known_pid(uint pid,PIDList* pidlist)
{
	return ((pidlist->PID[pid] & 0x8000) == 0x8000) ? true : false;	// bit 16
}

void
set_known_pid(uint pid,PIDList* pidlist)
{
	pidlist->PID[pid] |= 0x8000;	// bit 16
	return;
}

bool
is_pmt(uint pid,PIDList* pidlist)
{
	return ((pidlist->PID[pid] & 0x4000) == 0x4000) ? true : false;	// bit 15
}

void
set_pmt(uint pid,uint prognum,PIDList* pidlist)
{
	set_known_pid(pid,pidlist);	// need PSI set as well
	set_si(pid,pidlist);
	pidlist->PID[pid] |= 0x4000;	// bit 15
	pidlist->prognum[pid] = prognum;
}

bool
is_si(uint pid,PIDList* pidlist)
{
	return ((pidlist->PID[pid] & 0x2000) == 0x2000) ? true : false;	// bit 14
}

void
set_si(uint pid,PIDList* pidlist)
{
	pidlist->PID[pid] |= 0x2000;	// bit 14
	return;
}
