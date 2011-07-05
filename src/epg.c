/*
 * epg.c
 *
 *  Created on: Jun 29, 2011
 *      Author: orion
 */
#include	"../include/epg.h"

EPG globle_epg[128];

void update_service_provider_name(char* service_provider_name, int service_provider_name_len,EPG* epg){
	memcpy(epg->service_provider_name, service_provider_name, service_provider_name_len);
	//strcpy(epg->tvname,tvname);
}

void update_service_name(char* service_name, int service_name_len, EPG* epg){
	memcpy(epg->service_name, service_name, service_name_len);
	//strcpy(epg->tvname,tvname);
}

void update_start_date(uint32_t start_date, EPG* epg){
	epg->start_date = start_date;
}

void update_start_time(uint32_t start_time, EPG* epg){
	epg->start_time = start_time;
}

void update_duration(uint32_t duration, EPG* epg){
	epg->duration = duration;
}

void update_event_name(char* event_name, int event_name_len, EPG* epg){
	memcpy(epg->event_name, event_name, event_name_len);
	//strcpy(epg->proname,proname);
}
