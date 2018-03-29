/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 18 August 2017 
 * @brief 	Test cJSON library
 *			More: https://github.com/DaveGamble/cJSON
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

// Example: Create json string 
// {
//     "name": "ASUS (\"Monitor\") MX34VQ",
//     "monitor": {
//         "type":       		"IPS",
//         "width":      		3440,
//         "height":     		1440,
//         "interlace_vga":  	false,
//         "frame rate": 		100
//     }
// }
typedef struct monitor_s {
	char	type[30];
	int		width;
	int		height;
	bool	interlace_vga;
	double 	framerate;
} monitor_t;

typedef struct buyitem_s {
	char 		name[30];
	monitor_t	monitor;
} buyitem_t;

static void example_build_jsonstr(char **out_jsonstr){
	cJSON *root = NULL;
	cJSON *fmt = NULL;
	
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("ASUS (\"Monitor\") MX34VQ"));
	cJSON_AddItemToObject(root, "monitor", fmt = cJSON_CreateObject());
	cJSON_AddStringToObject(fmt, "type", "IPS");
	cJSON_AddNumberToObject(fmt, "width", 3440);
	cJSON_AddNumberToObject(fmt, "height", 1440);
	cJSON_AddFalseToObject (fmt, "interlace_vga");
	cJSON_AddNumberToObject(fmt, "frame rate", 100);

	*out_jsonstr = cJSON_Print(root); // auto allocate memory ** need to call cJSON_free() to free memory**

	// free everything associate with root
	// The exception is cJSON_PrintPreallocated, where return to the caller that has full responsibility of the buffer. */
	cJSON_Delete(root);	
	root = NULL;

	return;
}

static void example01(){
	char *jsonstr = NULL;
	
	example_build_jsonstr(&jsonstr);
	fprintf(stdout, "%s(%d) test create json string: \r\n"
					"%s\r\n"
					, __FUNCTION__, __LINE__, jsonstr
					);

	cJSON_Minify(jsonstr);

	fprintf(stdout, "%s(%d) after minify json string: \r\n"
					"%s\r\n",
			__FUNCTION__, __LINE__, jsonstr);

	cJSON_free(jsonstr);
	jsonstr = NULL;

	return;	
}

static int alltxtfromfile_alloc(char * filename, char ** out_pstr){
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
			*out_pstr = (char *)malloc(sizeof(char) * (bufsize + 1));

			/* Go back to the start of the file. */
	        if (fseek(fp, 0L, SEEK_SET) != 0){ 
	        	fprintf(stderr, "%s(%d) filename: %s SEEK_SET error!!\r\n", __FUNCTION__, __LINE__, filename);
	        }

	        /* Read the entire file into memory. */
	        size_t newLen = fread(*out_pstr, sizeof(char), bufsize, fp);
	        if ( ferror( fp ) != 0 ){	            
				fprintf(stderr, "%s(%d) Error reading file %s\r\n", __FUNCTION__, __LINE__, filename);	            
	        } else {
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

static void example02(){
	char * 	jsonstr 	= NULL;
	cJSON * root 		= NULL;
	cJSON * monitor 	= NULL;

	cJSON *name , *type, *width, *height, *interlace_vga, *framerate;
	buyitem_t btime;

	alltxtfromfile_alloc("data.json", &jsonstr);
	//printf("%s(%d)\r\n%s.....\r\n", __FUNCTION__, __LINE__, jsonstr);

	root 	= cJSON_Parse(jsonstr);
	monitor = cJSON_GetObjectItemCaseSensitive(root, "monitor");
	
	name 			= cJSON_GetObjectItemCaseSensitive(root, 	"name");
	type 			= cJSON_GetObjectItemCaseSensitive(monitor, "type");
	width 			= cJSON_GetObjectItemCaseSensitive(monitor, "width");
	height 			= cJSON_GetObjectItemCaseSensitive(monitor, "height");
	interlace_vga 	= cJSON_GetObjectItemCaseSensitive(monitor, "interlace_vga");
	framerate 		= cJSON_GetObjectItemCaseSensitive(monitor, "frame rate");

	// name
	if (cJSON_IsString(name)){
	  strncpy(btime.name, name->valuestring, 30);
	  fprintf(stdout, "name = %s\r\n", btime.name);
	}

	// type
	if (cJSON_IsString(type)){
	  strncpy(btime.monitor.type, type->valuestring, 30);
	  fprintf(stdout, "type = %s\r\n", btime.monitor.type);
	}

	// width
	if (cJSON_IsNumber(width)){
	  btime.monitor.width = width->valueint;
	  fprintf(stdout, "width = %d\r\n", btime.monitor.width);
	}

	// height
	if (cJSON_IsNumber(height)){
	  btime.monitor.height = height->valueint;
	  fprintf(stdout, "height = %d\r\n", btime.monitor.height);
	}

	// interlace_vga
	if (cJSON_IsBool(interlace_vga)){
	  btime.monitor.interlace_vga = (interlace_vga->type==cJSON_True)?true:false;
	  fprintf(stdout, "interlace_vga = %s\r\n", btime.monitor.interlace_vga?"true":"false");
	}

	// framerate
	if (cJSON_IsNumber(framerate)){
	  btime.monitor.framerate = framerate->valuedouble;
	  fprintf(stdout, "framerate = %lf\r\n", btime.monitor.framerate);
	}

	// free everything associate with root
	// The exception is cJSON_PrintPreallocated, where return to the caller that has full responsibility of the buffer. */
	cJSON_Delete(root);
	root = NULL;

	if(jsonstr != NULL){
		free(jsonstr);
		jsonstr = NULL;
	}
}

int main(int argc, char * argv[]){

	// Example01: build json string (similar with serialize c structure to json string) 
	// & howto minify json string
	fprintf(stdout, "\r\nExample 01\r\n");
	example01();

	// Example02: read json & deserialize to C Structures
	fprintf(stdout, "\r\nExample 02\r\n");
	example02();

	return 0;
}
