/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 20 August 2017 
 * @brief 	save/load config file as json
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

#define STARTCONFIG_FILE	"cfgstart.json"

typedef enum{
	  PORT_TYPE_NONE		= 0
	, PORT_TYPE_PHYSICAL
	, PORT_TYPE_AGGREATE
	
	, PORT_TYPE_COUNT
} port_type_t;

#define PORTNAME_MAXLEN			(30)		

typedef struct monitor_s{
	char	port_name[PORTNAME_MAXLEN];
	bool 	port_enable;
	int		port_type;					// port_type_t	
} port_t;

#define SWITCHNAME_MAXLEN		(30)
#define PORT_COUNT 				(4)	// example switch 4 ports
#define TELNET_SESSION_MAX		(4)

typedef enum{ 	
	FAN_1,
	FAN_2, 

	FAN_COUNT
}fanx_t; 

typedef struct switchconfig_s{
	char	name[SWITCHNAME_MAXLEN];
	bool 	snmp_enable;
	bool 	telnet_enable[TELNET_SESSION_MAX];
	bool 	fan_enable[FAN_COUNT];
	port_t 	ports[PORT_COUNT];
} switchconfig_t;

/* config json should be look like,
{
	"name": "bangkok01",
	"snmp_enable": "true",
	"telnet_enable":{		
		"1":	"true",	
		"2":	"true",	
		"3":	"false",	
		"4":	"false"		
	},
	"fan_enable": [1, 1],
	"ports": [
		{	
			"port_name":	"port01",
			"port_enable":	"true",
			"port_type":	"PORT_TYPE_PHYSICAL"	
		},
		{	
			"port_name":	"port02",
			"port_enable":	"true",
			"port_type":	"PORT_TYPE_AGGREATE"	
		},
		{	
			"port_name":	"port03",
			"port_enable":	"true",
			"port_type":	"PORT_TYPE_AGGREATE"	
		},
		{	
			"port_name":	"port04",
			"port_enable":	"false",
			"port_type":	"PORT_TYPE_NONE"	
		},
	]
}
*/

static void setdefaultconfig(switchconfig_t *cfg){
	int counter;
	
	strncpy(cfg->name, "easyswitch", SWITCHNAME_MAXLEN);
	cfg->snmp_enable = false;
	for (counter = 0; counter < TELNET_SESSION_MAX; ++counter){
		cfg->telnet_enable[counter] = true;
	}

	for (counter = 0; counter < FAN_COUNT; ++counter){
		cfg->fan_enable[counter] = true;
	}	

	for (counter = 0; counter < PORT_COUNT; ++counter){
		port_t *port = &(cfg->ports[counter]);
		
		sprintf(port->port_name, "port%.2d", counter+1);
		port->port_enable 	= false;
		port->port_type 	= PORT_TYPE_NONE;
	}	
}

switchconfig_t *switchcfg_run(void){
	static switchconfig_t *cfg = NULL;

	if(cfg == NULL){
		cfg = calloc(1, sizeof(switchconfig_t));
		// init default value
		setdefaultconfig(cfg);
		// init thread
		// ... nothing to do...
	}
	return cfg;
}

int switchcfgrun_name_set(switchconfig_t *swcfgrun, char *in_name){
	strncpy(swcfgrun->name, in_name, SWITCHNAME_MAXLEN);
	return 0;
}

char* switchcfgrun_name(switchconfig_t *swcfgrun){
	return swcfgrun->name;
}

int switchcfgrun_snmp_enable_set(switchconfig_t *swcfgrun, bool enable){
	swcfgrun->snmp_enable = enable;
	return 0;
}

int switchcfgrun_telnet_enable_set(switchconfig_t *swcfgrun, int idx, bool enable){
	swcfgrun->telnet_enable[idx] = enable;
	return 0;
}

int switchcfgrun_fan_enable_set(switchconfig_t *swcfgrun, fanx_t idx, bool enable){
	swcfgrun->fan_enable[idx] = enable;
	return 0;
}

int switchcfgrun_port_name_set(switchconfig_t *swcfgrun, int idx, char *in_name){
	strncpy(swcfgrun->ports[idx].port_name, in_name, PORTNAME_MAXLEN);
	return 0;
}

int switchcfgrun_port_enable_set(switchconfig_t *swcfgrun, int idx, bool enable){
	swcfgrun->ports[idx].port_enable = enable;
	return 0;
}

int switchcfgrun_port_type_set(switchconfig_t *swcfgrun, int idx, port_type_t type){
	swcfgrun->ports[idx].port_type = type;
	return 0;
}

static int cfgtojsonstr(char **out_jsonstr, switchconfig_t *cfg){
	int ret = 0;
	int counter;
	char str[30];

	cJSON *root = NULL;
	cJSON *telnet_enable = NULL;
	cJSON *fan_enable = NULL;
	cJSON *ports = NULL;
	cJSON *port_info = NULL;
	cJSON *number = NULL;


	root = cJSON_CreateObject();

	// name
	cJSON_AddItemToObject(root, "name", cJSON_CreateString(cfg->name));
	
	// snmp_enable
	if(cfg->snmp_enable == true){
		cJSON_AddTrueToObject(root, "snmp_enable");
	}else{
		cJSON_AddFalseToObject(root, "snmp_enable");
	}

	// telnet_enable
	cJSON_AddItemToObject(root, "telnet_enable", telnet_enable = cJSON_CreateObject());
    for (counter = 0; counter < TELNET_SESSION_MAX; counter++){
    	sprintf(str, "%d", counter+1);
		if(cfg->telnet_enable[counter] == true){
			cJSON_AddTrueToObject(telnet_enable, str);
		}else{
			cJSON_AddFalseToObject(telnet_enable, str);
		}
	}

	// fan_enable
	cJSON_AddItemToObject(root, "fan_enable", fan_enable = cJSON_CreateArray());	
    for (counter = 0; counter < FAN_COUNT; counter++){
    	number = cJSON_CreateNumber(cfg->fan_enable[counter]);
    	cJSON_AddItemToArray(fan_enable, number);
	}	

	// ports[]
	cJSON_AddItemToObject(root, "ports", ports = cJSON_CreateArray());
    for (counter = 0; counter < PORT_COUNT; counter++){
    	port_t *port = &(cfg->ports[counter]);
    	cJSON_AddItemToArray(ports, port_info = cJSON_CreateObject());
    	
    	cJSON_AddStringToObject(port_info, "port_name", port->port_name);
    	
    	if(port->port_enable == true){
			cJSON_AddTrueToObject(port_info, "port_enable");
		}else{
			cJSON_AddFalseToObject(port_info, "port_enable");
		}

		cJSON_AddNumberToObject(port_info, "port_type", port->port_type);
	}    

	*out_jsonstr = cJSON_Print(root);

	// free everything associate with root
	// The exception is cJSON_PrintPreallocated, where return to the caller that has full responsibility of the buffer. */
	cJSON_Delete(root);	

	return ret;	
}

static int write_stringtofile(char *str, char *filename){
	FILE *fd = fopen(filename, "w");
	if (fd == NULL){
	    fprintf(stderr, "%s(%d) error opening file: %s\r\n", __FUNCTION__, __LINE__, filename);
	    return -1;
	}

	fprintf(fd, "%s\n", str);
	fclose(fd);
	return 0;
}

static int read_stringfromfile_alloc(char * filename, char ** out_pstr){
	FILE *fp = fopen(filename, "r");
	int ret = -1;

	if (fp != NULL){
	    /* Go to the end of the file. */
	    if (fseek(fp, 0L, SEEK_END) == 0){
	        /* Get the size of the file. */
	        long bufsize = ftell(fp);
	        if (bufsize == -1){ 
	        	fprintf(stderr, "%s(%d) filename: %s get size error!!\r\n", __FUNCTION__, __LINE__, filename);		
	    	}

	        /* Allocate our buffer to that size. */
	        *out_pstr = malloc(sizeof(char) * (bufsize + 1));

	        /* Go back to the start of the file. */
	        if (fseek(fp, 0L, SEEK_SET) != 0){ 
	        	fprintf(stderr, "%s(%d) filename: %s SEEK_SET error!!\r\n", __FUNCTION__, __LINE__, filename);
	        }

	        /* Read the entire file into memory. */
	        size_t newLen = fread(*out_pstr, sizeof(char), bufsize, fp);
	        if ( ferror( fp ) != 0 ){	            
				fprintf(stderr, "%s(%d) Error reading file %s\r\n", __FUNCTION__, __LINE__, filename);	            
	        } else{
	            (*out_pstr)[newLen++] = '\0'; /* Just to be safe. */
	            ret = 0;
	        }
	    }
	    fclose(fp);	    
	}else{
		fprintf(stderr, "%s(%d) filename: %s\n", __FUNCTION__, __LINE__, filename);
	}

	return ret;
}

static char* myitoa(int val, int base){
	static char buf[32] = {0};	
	int i = 30;
	
	for(; val && i ; --i, val /= base){
		buf[i] = "0123456789abcdef"[val % base];
	}
	
	return &buf[i+1];
}

static int jsonstrtorun_apply(switchconfig_t *cfg, char *jsonstr){
	int counter;
	cJSON *root 			= NULL;
	cJSON *name, *snmp_enable;
	cJSON *telnet_enable, *fan_enable, *ports;

	root 	= cJSON_Parse(jsonstr);

	// name
	name = cJSON_GetObjectItemCaseSensitive(root, "name");
	if(cJSON_IsString(name)){
	  strncpy(cfg->name, name->valuestring, SWITCHNAME_MAXLEN);
	  //fprintf(stdout, "name = %s\r\n", cfg->name);
	}else{
		fprintf(stderr, "%s(%d) error field name\r\n", __FUNCTION__, __LINE__);
	}	

	// snmp_enable
	snmp_enable = cJSON_GetObjectItemCaseSensitive(root, "snmp_enable");
	if(cJSON_IsBool(snmp_enable)){
	  cfg->snmp_enable = (snmp_enable->type==cJSON_True)?true:false;
	  //fprintf(stdout, "snmp_enable = %s\r\n", cfg->snmp_enable?"true":"false");
	}else{
		fprintf(stderr, "%s(%d) error field snmp_enable\r\n", __FUNCTION__, __LINE__);
	}	

	// telnet_enable
	telnet_enable = cJSON_GetObjectItemCaseSensitive(root, "telnet_enable");
	if(cJSON_IsObject(telnet_enable)){
		cJSON *telnet_ssx;
		for(counter = 0; counter < TELNET_SESSION_MAX; counter++){
			telnet_ssx = cJSON_GetObjectItemCaseSensitive(telnet_enable, myitoa(counter+1, 10));

			if (cJSON_IsBool(telnet_ssx)){
				cfg->telnet_enable[counter] = (telnet_ssx->type==cJSON_True)?true:false;
			}else{
				fprintf(stderr, "%s(%d) error field telnet_ssx\r\n", __FUNCTION__, __LINE__);
			}
		}
	}else{
		fprintf(stderr, "%s(%d) error field telnet_enable\r\n", __FUNCTION__, __LINE__);
	}	

	// fan_enable
	fan_enable = cJSON_GetObjectItemCaseSensitive(root, "fan_enable");
	if(cJSON_IsArray(fan_enable)){
		cJSON *fan;
		counter = 0;
		cJSON_ArrayForEach(fan, fan_enable){

			if(cJSON_IsNumber(fan)){				
				cfg->fan_enable[counter] = fan->valueint?true:false;
			}else{
				fprintf(stderr, "%s(%d) fan_enable[%d]: %d\r\n"
						, __FUNCTION__, __LINE__
						, counter, cJSON_IsNumber(fan)
						);
			}
			counter++;
		}
	}else{
		fprintf(stderr, "%s(%d) error field fan_enable\r\n", __FUNCTION__, __LINE__);
	}

	// ports
	ports = cJSON_GetObjectItemCaseSensitive(root, "ports");
	if(cJSON_IsArray(ports)){
		cJSON *port;
		cJSON *port_name, *port_enable, *port_type;

		counter = 0;
		cJSON_ArrayForEach(port, ports){
			port_name = cJSON_GetObjectItemCaseSensitive(port, "port_name");
			port_enable = cJSON_GetObjectItemCaseSensitive(port, "port_enable");
			port_type = cJSON_GetObjectItemCaseSensitive(port, "port_type");

			if(cJSON_IsString(port_name) && cJSON_IsBool(port_enable) && cJSON_IsNumber(port_type)){
				strncpy(cfg->ports[counter].port_name, port_name->valuestring, PORTNAME_MAXLEN);
				cfg->ports[counter].port_enable = (port_enable->type==cJSON_True)?true:false;
				cfg->ports[counter].port_type = port_type->valueint;
			}else{
				fprintf(stderr, "%s(%d) bad json string, please check port_name(%d)/port_enable(%d)/port_type(%d)\r\n"
						, __FUNCTION__, __LINE__
						, cJSON_IsString(port_name), cJSON_IsBool(port_enable), cJSON_IsNumber(port_type)
						);
			}
			counter++;
		}

	}else{
		fprintf(stderr, "%s(%d) error field ports\r\n", __FUNCTION__, __LINE__);
	}
	return 0;
}

int save_runtostart(switchconfig_t *cfg){
	int ret = 0;
	char *jsonstr = NULL;

	// build json string from switchconfig_t
	cfgtojsonstr(&jsonstr, cfg);
	fprintf(stdout, "\r\n%s\r\n", jsonstr);

	// save jsonstring to file STARTCONFIG_FILE
	write_stringtofile(jsonstr, STARTCONFIG_FILE);

	if(jsonstr != NULL){
		free(jsonstr);
		jsonstr = NULL;
	}
	return ret;
}

int load_starttorun(switchconfig_t *cfg){
	char * 	jsonstr 	= NULL;

	// load file to json string buf
	read_stringfromfile_alloc(STARTCONFIG_FILE, &jsonstr);
	//printf(".....%s\r\n", jsonstr);

	// set json string buf to running 
	jsonstrtorun_apply(cfg, jsonstr);

	if(jsonstr != NULL){
		free(jsonstr);
		jsonstr = NULL;
	}

	return 0;
}

static int print_runinfo(switchconfig_t *cfg){

	fprintf(stdout, "%s(%d) switch info\r\n"
					"\t name: %s\r\n"
					"\t snmp_enable: %d\r\n"
					"\t telnet_enable: %d/%d/%d/%d\r\n"
					"\t fan_enable: %d/%d\r\n"
					"\t port[0]: name:%s status:%d type:%d\r\n"
					"\t port[1]: name:%s status:%d type:%d\r\n"
					"\t port[2]: name:%s status:%d type:%d\r\n"
					"\t port[3]: name:%s status:%d type:%d\r\n"
					"\r\n"
					, __FUNCTION__, __LINE__
					, cfg->name
					, cfg->snmp_enable
					, cfg->telnet_enable[0], cfg->telnet_enable[1], cfg->telnet_enable[2], cfg->telnet_enable[3]
					, cfg->fan_enable[0], cfg->fan_enable[1]
					, cfg->ports[0].port_name, cfg->ports[0].port_enable, cfg->ports[0].port_type
					, cfg->ports[1].port_name, cfg->ports[1].port_enable, cfg->ports[1].port_type
					, cfg->ports[2].port_name, cfg->ports[2].port_enable, cfg->ports[2].port_type
					, cfg->ports[3].port_name, cfg->ports[3].port_enable, cfg->ports[3].port_type
					);

	return 0;
} 

int main(int argc, char *argv[]){

	// TODO
	// 1. bias running config with defult config and print running info	
	// 2. save running config to file name cfgstart.json
	// 3. change "some_field" of running config and print running info
	// 4. load cfgstart.json to running config and print running info

	// 1.
	fprintf(stdout, "\r\n%s(%d) ---STEP 1---\r\n", __FUNCTION__, __LINE__);
	switchcfg_run();
	print_runinfo(switchcfg_run());

	// 2.
	fprintf(stdout, "\r\n%s(%d) ---STEP 2---\r\n", __FUNCTION__, __LINE__);
	save_runtostart(switchcfg_run());

	// 3.
	fprintf(stdout, "\r\n%s(%d) ---STEP 3---\r\n", __FUNCTION__, __LINE__);
	switchcfgrun_name_set(switchcfg_run(), "bangkok01");
	switchcfgrun_snmp_enable_set(switchcfg_run(), true);
	switchcfgrun_telnet_enable_set(switchcfg_run(), 0, true);
	switchcfgrun_telnet_enable_set(switchcfg_run(), 1, true);
	switchcfgrun_telnet_enable_set(switchcfg_run(), 2, false);
	switchcfgrun_telnet_enable_set(switchcfg_run(), 3, false);
	switchcfgrun_fan_enable_set(switchcfg_run(), FAN_1, true);
	switchcfgrun_fan_enable_set(switchcfg_run(), FAN_2, false);
	switchcfgrun_port_name_set(switchcfg_run(), 0, "p1");
	switchcfgrun_port_enable_set(switchcfg_run(), 0, true);
	switchcfgrun_port_type_set(switchcfg_run(), 0, PORT_TYPE_PHYSICAL);		
	switchcfgrun_port_name_set(switchcfg_run(), 1, "p2");
	switchcfgrun_port_enable_set(switchcfg_run(), 1, false);
	switchcfgrun_port_type_set(switchcfg_run(), 1, PORT_TYPE_PHYSICAL);	
	switchcfgrun_port_name_set(switchcfg_run(), 2, "p3");
	switchcfgrun_port_enable_set(switchcfg_run(), 2, false);
	switchcfgrun_port_type_set(switchcfg_run(), 2, PORT_TYPE_AGGREATE);	
	switchcfgrun_port_name_set(switchcfg_run(), 3, "p4");
	switchcfgrun_port_enable_set(switchcfg_run(), 3, true);
	switchcfgrun_port_type_set(switchcfg_run(), 3, PORT_TYPE_AGGREATE);	
	print_runinfo(switchcfg_run());

	// 4.
	fprintf(stdout, "\r\n%s(%d) ---STEP 4---\r\n", __FUNCTION__, __LINE__);
	load_starttorun(switchcfg_run());
	print_runinfo(switchcfg_run());

	return 0;
}
