/**
 * @file circularq.c
 * @author Napat Rungruangbangchan
 * @date 18 October 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>

#include "circularq.h"

#ifdef QUEUE_THREAD_LOCK
static void qlock(circularq_t *queue){
    pthread_mutex_lock(&queue->lock);
}

static void qunlock(circularq_t *queue){
    pthread_mutex_unlock(&queue->lock);
}
#endif

uint16_t circularq_create(circularq_t *queue, uint32_t size){
    if(queue == NULL){
        fprintf(stderr, "%s(%d) error\r\n", __FUNCTION__, __LINE__);
        return -1;
    }

    queue->start = (uint8_t *)malloc(size);
    if(queue->start == NULL){
        fprintf(stderr, "%s(%d) error\r\n", __FUNCTION__, __LINE__);
        return -1;
    }

    queue->end = (uint8_t *)(queue->start + size);
    queue->tail = queue->head = queue->start;

#ifdef QUEUE_THREAD_LOCK
    if(pthread_mutex_init(&queue->lock, NULL) != 0){
        fprintf(stderr, "%s(%d) error init mutex\r\n", __FUNCTION__, __LINE__);
        return 1;
    }
#endif

    // printf("size: %u\n", size);
    // printf("queue->start: %p\n", queue->start);
    // printf("queue->end: %p\n", queue->end);
    // printf("queue->tail: %p\n", queue->tail);
    return 0;
}

void circularq_destroy(circularq_t *queue){
    if(queue->start == NULL){
        return;
    }

    free(queue->start);
}

void circularq_discard(circularq_t *queue){
    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return;
    }

#ifdef QUEUE_THREAD_LOCK
     qlock(queue);
#endif

    queue->tail = queue->head = queue->start;

#ifdef QUEUE_THREAD_LOCK
    qunlock(queue);
#endif

}

uint32_t circularq_freesize(circularq_t *queue){
    uint32_t size;

    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return 0;
    }

    if(queue->tail >= queue->head){
        size = (uint32_t)((queue->end - queue->tail) +
                      (queue->head - queue->start));    
    }else{
        size = (uint32_t)(queue->head - queue->tail);   
    }

    if(size > 0){
        --size;
    }

    return size;
}

uint32_t circularq_usesize(circularq_t *queue){
    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return 0xFFFF;
    }

    if(queue->tail >= queue->head){
        return (uint32_t)(queue->tail - queue->head);   
    }else{
        return (uint32_t)((queue->end - queue->head) + (queue->tail - queue->start));    
    }
}

uint32_t circularq_size(circularq_t *queue){
    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return 0;
    }

    return (uint32_t)(queue->end - queue->start) - 1;
}

uint32_t circularq_empty(circularq_t *queue){
    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return 1;
    }
    //printf("%s(%d) head=%p tail=%p\r\n", __FUNCTION__, __LINE__, queue->head, queue->tail);
    return (queue->head == queue->tail);
}

uint32_t circularq_put(circularq_t *queue, uint8_t *buff, uint32_t size){
    uint32_t s;
    uint8_t *tail;

    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return 0;
    }

    s = size;
    if(s > circularq_freesize(queue)){
        return 0;
    }

#ifdef QUEUE_THREAD_LOCK
     qlock(queue);
#endif

    tail = queue->tail;

    while (s--){
        *tail++ = *buff++;

        if(tail == queue->end){
            tail = queue->start;
        }
            
    }

    queue->tail = tail;

#ifdef QUEUE_THREAD_LOCK
    qunlock(queue);
#endif

    return size;
}

uint32_t circularq_getfirst(circularq_t *queue, uint8_t *ch){
    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        *ch = 0;
        return 0;
    }

    if(queue->head == queue->tail){
        *ch = 0;
        return 0;
    }

    *ch = *queue->head;

    return 1;
}

uint32_t circularq_getfirstw(circularq_t *queue, uint32_t *w){
    uint8_t *head;

    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        *w = 0;
        return 0;
    }

    if(queue->head == queue->tail){
        *w = 0;
        return 0;
    }

    head = queue->head;

    *w = (uint32_t)(*(head+1) << 8) | *head;

    return 1;
}

uint32_t circularq_get(circularq_t *queue, uint8_t *buff, uint32_t size){
    uint32_t getsize;
    uint8_t *head;

    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
//      printf("!ERROR: Queue get().\r\n");
        return 0;
    }

    getsize = circularq_usesize(queue);
    if(getsize > size){
        getsize = size;
    } else if(size > getsize){
        size = getsize;
    }

#ifdef QUEUE_THREAD_LOCK
     qlock(queue);
#endif

    head = queue->head;

    while (getsize--){
        *buff++ = *head++;

        if(head == queue->end){
            head = queue->start;
        }            
    }

    queue->head = head;

#ifdef QUEUE_THREAD_LOCK
    qunlock(queue);
#endif

    return size;
}

uint32_t circularq_putch(circularq_t *queue, uint8_t ch){
    uint32_t freesize;
    uint8_t *tail;

    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return 0;
    }

    freesize = circularq_freesize(queue);

    if(freesize){
#ifdef QUEUE_THREAD_LOCK
         qlock(queue);
#endif

        tail = queue->tail;

        *tail++ = ch;
        if(tail == queue->end){
            tail = queue->start;
        }

        queue->tail = tail;

#ifdef QUEUE_THREAD_LOCK
        qunlock(queue);
#endif
        return 1;

    } else{
        return 0;
    }
}

uint32_t circularq_putw(circularq_t *queue, uint32_t w){
    uint32_t freesize;
    uint8_t *tail;

    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return 0;
    }

    freesize = circularq_freesize(queue);

    if(freesize > 4){
#ifdef QUEUE_THREAD_LOCK
         qlock(queue);
#endif

        tail = queue->tail;

        *tail++ = (uint8_t)(w & 0xFF);
        if(tail == queue->end){
            tail = queue->start;
        }

        *tail++ = (uint8_t)(w >> 8);
        if(tail == queue->end){
            tail = queue->start;
        }

        queue->tail = tail;

#ifdef QUEUE_THREAD_LOCK
    qunlock(queue);
#endif

        return 1;

    } else{
        return 0;
    }
}

uint32_t circularq_getch(circularq_t *queue, uint8_t *ch){
    uint8_t *head;

    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return 0;
    }

    if(queue->head == queue->tail){
        return 0;
    }

#ifdef QUEUE_THREAD_LOCK
     qlock(queue);
#endif

    head = queue->head;

    *ch = *head++;

    if(head == queue->end){
        head = queue->start;
    }

    queue->head = head;

#ifdef QUEUE_THREAD_LOCK
    qunlock(queue);
#endif

    return 1;
}

uint32_t circularq_getw(circularq_t *queue, uint32_t *w){
    uint8_t l, h;
    uint8_t *head;

    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return 0;
    }

    if(queue->head == queue->tail){
        return 0;
    }

#ifdef QUEUE_THREAD_LOCK
     qlock(queue);
#endif

    head = queue->head;

    l = *head++;
    if(head == queue->end){
        head = queue->start;
    }

    h = *head++;
    if(head == queue->end){
        head = queue->start;
    }

    *w = (uint32_t)(h << 8) | l;

    queue->head = head;

#ifdef QUEUE_THREAD_LOCK
    qunlock(queue);
#endif

    return 1;
}

static uint32_t internal_circularq_putdata(uint8_t is_autoreplace ,circularq_t *queue, uint8_t *dat, uint32_t size){
    uint32_t s;
    uint8_t *tail;

    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        fprintf(stderr, "%s(%d) error Qaddr(%p)\r\n", __FUNCTION__, __LINE__, queue);
        return 0;
    }

// Debug to see used size    
//fprintf(stdout, "%s(%d) freesize %d, need %d\n"
//                , __FUNCTION__, __LINE__
//                , circularq_freesize(queue)
//                , size+2
//                );
    if(is_autoreplace == 0){
        if(circularq_freesize(queue) <= (size+2)){
            fprintf(stderr, "%s(%d) error size(%u) Qaddr(%p)\r\n", __FUNCTION__, __LINE__, circularq_freesize(queue), queue);
            fprintf(stderr, "%s(%d) freesize %d, need %d\n"
                            , __FUNCTION__, __LINE__
                            , circularq_freesize(queue)
                            , size+2
                            );        
            return 0;
        }
    }else{
         uint8_t is_qfull;
        // if qfull, deQ until enough space
        do{
            if(circularq_freesize(queue) <= (size+2)){
                uint8_t dat[size*2];
                is_qfull = 1;
                // Auto deQ
                circularq_getdata(queue, dat);
            }else{
                is_qfull = 0;
            }
        }while(is_qfull == 1);       
    }

    //printf("Qsize(%u)\r\n", circularq_freesize(queue));

    //printf("%s(%d)\r\n", __FUNCTION__, __LINE__);
#ifdef QUEUE_THREAD_LOCK
     qlock(queue);
#endif
    //printf("%s(%d)\r\n", __FUNCTION__, __LINE__);
    tail = queue->tail;

    // put size
    *tail++ = (uint8_t)(size & 0xFF);
    if(tail == queue->end){
        tail = queue->start;
    }

    *tail++ = (uint8_t)(size >> 8);
    if(tail == queue->end){
        tail = queue->start;
    }

    //printf("%s(%d)\r\n", __FUNCTION__, __LINE__);
    // put data
    s = size;
    while (s--){
        *tail++ = *dat++;

        if(tail == queue->end){
            tail = queue->start;
        }
            
    }
    //printf("%s(%d)\r\n", __FUNCTION__, __LINE__);
    queue->tail = tail;

#ifdef QUEUE_THREAD_LOCK
    qunlock(queue);
#endif
    //printf("%s(%d)\r\n", __FUNCTION__, __LINE__);
    return size;
}

uint32_t circularq_putdata(circularq_t *queue, uint8_t *dat, uint32_t size){
    return internal_circularq_putdata(0 ,queue, dat, size);
}

uint32_t circularq_putdata_replace(circularq_t *queue, uint8_t *dat, uint32_t size){
    return internal_circularq_putdata(1 ,queue, dat, size);
}

uint32_t circularq_getdata(circularq_t *queue, uint8_t *dat){
    uint32_t size, s;
    uint8_t *head;

    if((queue == (circularq_t *)0) || (queue->start == (uint8_t *)0)){
        return 0;
    }

    if(queue->head == queue->tail){
        return 0;
    }

#ifdef QUEUE_THREAD_LOCK
     qlock(queue);
#endif

    head = queue->head;

    // get size
    s = *head++;
    if(head == queue->end){
        head = queue->start;
    }
    s |= ((uint32_t)(*head++) << 8);
    if(head == queue->end){
        head = queue->start;
    }

    size = s;

    if(circularq_usesize(queue) < size){
        fprintf(stderr, "%s(%d) !ERROR: circularq_getdata Qaddr(%p)\r\n", __FILE__, __LINE__, queue);
        queue->tail = queue->head = queue->start;
        return 0;
    }

    // get data
    while (s--){
        *dat++ = *head++;
        if(head == queue->end){
            head = queue->start;
        }
    }

    queue->head = head;

#ifdef QUEUE_THREAD_LOCK
    qunlock(queue);
#endif
    return size;
}
