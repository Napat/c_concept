/**
 * @file circularq.h
 * @author Napat Rungruangbangchan
 * @date 18 October 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#ifndef __CIRCULARQ_H__
#define __CIRCULARQ_H__

#include <stdint.h>

#define QUEUE_THREAD_LOCK
#ifdef QUEUE_THREAD_LOCK
	#include <pthread.h>
#endif

#define QUEUE_MEMCPY(dest, source, size)	memcpy((uint8_t *)dest, (uint8_t *)source, (uint32_t)size)

typedef struct circularq_s{
	uint8_t *start;
	uint8_t *end;
	uint8_t *head;
	uint8_t *tail;

#ifdef QUEUE_THREAD_LOCK
	pthread_mutex_t lock;
#endif
	
} circularq_t;

uint16_t circularq_create(circularq_t *queue, uint32_t size);
void circularq_destroy(circularq_t *queue);
void circularq_discard(circularq_t *queue);
uint32_t circularq_freesize(circularq_t *queue);
uint32_t circularq_usesize(circularq_t *queue);
uint32_t circularq_size(circularq_t *queue);
uint32_t circularq_empty(circularq_t *queue);
uint32_t circularq_put(circularq_t *queue, uint8_t *buff, uint32_t size);
uint32_t circularq_get(circularq_t *queue, uint8_t *buff, uint32_t size);
uint32_t circularq_getch(circularq_t *queue, uint8_t *ch);
uint32_t circularq_putch(circularq_t *queue, uint8_t ch);
uint32_t circularq_getfirst(circularq_t *queue, uint8_t *ch);
uint32_t circularq_getfirstw(circularq_t *queue, uint32_t *w);
uint32_t circularq_putw(circularq_t *queue, uint32_t w);
uint32_t circularq_getw(circularq_t *queue, uint32_t *w);

// Note: circularq_putdata(): size+2 bytes of qsize will be used  
uint32_t circularq_putdata(circularq_t *queue, uint8_t *dat, uint32_t size);
uint32_t circularq_putdata_replace(circularq_t *queue, uint8_t *dat, uint32_t size);
uint32_t circularq_getdata(circularq_t *queue, uint8_t *dat);

#endif /* __CIRCULARQ_H__ */
