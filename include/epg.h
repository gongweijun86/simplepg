/*
 * epg.h
 *
 *  Created on: Jun 29, 2011
 *      Author: orion
 */

#ifndef _EPG_H_
#define _EPG_H_

#include 	<time.h>
#include	<string.h>
#include	<stdint.h>

struct _epg{
	char service_provider_name[256];
	char service_name[256];
	uint32_t start_date;
	uint32_t start_time;
	uint32_t duration;
	char event_name[256];
};

typedef struct _epg EPG;

void update_service_provider_name(char* service_provider_name, int service_provider_name_len, EPG* epg);
void update_service_name(char* service_name, int service_name_len, EPG* epg);
void update_start_date(uint32_t start_date, EPG* epg);
void update_start_time(uint32_t start_time, EPG* epg);
void update_duration(uint32_t duration, EPG* epg);
void update_event_name(char* event_name, int event_name_len, EPG* epg);


#endif /* _EPG_H_ */
