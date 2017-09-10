/**
 * @file linklist_item.c
 * @author Napat Rungruangbangchan
 * @date 9 September 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linklist_item.h"

llitem_node_t*  llitem_node_next(llitem_node_t* llitem_node){
	return llitem_node->next;
}

int llitem_node_islast(llitem_node_t* llitem_node){
	if(llitem_node == NULL){
		return 1;
	}
	return (llitem_node->next == NULL)?1:0;
}

llitem_t* llitem_item(llitem_node_t* llitem_node, llitem_t*	llitem_out){
	*llitem_out = llitem_node->llitem;
	return llitem_out;
}

int llitem_count(llitem_node_t* llitem_node){
	int counter = 0;
    llitem_node_t* cur = llitem_node;

    while(cur != NULL){
        counter++;
        cur = cur->next;
    }
    return counter;
}

void llitem_printall(llitem_node_t* head, FILE* output){
    llitem_node_t* cur = head;

    fprintf(stdout, "\n");
    while (cur != NULL){
        fprintf(stdout, "%s: %d\n", cur->llitem.name, cur->llitem.stockcount);
        cur = cur->next;
    }
}

int lltime_getitemid(llitem_node_t** head, llitem_t* llitem_in, int (*itemcomparator_iseq)(const llitem_t*, const llitem_t*)){
    llitem_node_t* cur = *head;
    int id = 0;

    while(cur != NULL){
    	if( (*itemcomparator_iseq)(&cur->llitem, llitem_in) ){
    		// found: id >= 0
    		return id;
    	}

    	id = id+1;
        cur = cur->next;
    }
    // not found
    return -1;
}

int lltime_getitem_byid(llitem_node_t** head, int id_in, llitem_t* llitem_in){
	int idx = 0;
    llitem_node_t* cur = *head;

    for(idx = 0; idx < id_in; idx++){
        if (cur->next == NULL){
            return -1;
        }
        cur = cur->next;
    }

    *llitem_in = cur->llitem;
    return 0;
}

llitem_node_t* llitem_addend(llitem_node_t** head, llitem_t* llitem_in){
	llitem_node_t* cur = *head;
	llitem_node_t* itemadd_pos;

	if(cur == NULL){
		cur = (llitem_node_t*)malloc(sizeof(*cur));
		memcpy(&cur->llitem, llitem_in, sizeof(*llitem_in));
		cur->next = NULL;	
		*head = cur;

		itemadd_pos = cur;	
	}else{
		while(cur->next != NULL){
			cur = cur->next;
		}

		cur->next = (llitem_node_t*)malloc(sizeof(*cur));
		memcpy(&cur->next->llitem, llitem_in, sizeof(*llitem_in));
		cur->next->next = NULL;

		itemadd_pos = cur->next;
	}

	return itemadd_pos;
}

// add begin
llitem_node_t* llitem_push(llitem_node_t** head, llitem_t* llitem_in){
	llitem_node_t* new_head;

	new_head = (llitem_node_t*)malloc(sizeof(*new_head));
	memcpy(&new_head->llitem, llitem_in, sizeof(*llitem_in));
	new_head->next 	= *head;
	*head = new_head;

	return new_head;
}

// add at position
llitem_node_t* llitem_addid(llitem_node_t** head, int id_in, llitem_t* llitem_in){
    int idx = 0;
    llitem_node_t* cur = *head;
    llitem_node_t* node_tmp;

    if (id_in == 0){
    	return llitem_push(head, llitem_in);
    }

    for(idx = 0; idx < id_in-1; idx++){
    	if (cur->next == NULL){
            return NULL;
        }
        cur = cur->next;
    }

	node_tmp = cur->next; 
	cur->next = (llitem_node_t*)malloc(sizeof(*cur));
	cur->next->llitem = *llitem_in;
	cur->next->next = node_tmp;

	return node_tmp;
}

// pop first item
int llitem_pop(llitem_node_t** head, llitem_t* llitem_out){
    llitem_node_t* next_node = NULL;

    if (*head == NULL) {
    	// list is empty
        return -1;
    }

    next_node = (*head)->next;
    if(llitem_out != NULL){
    	*llitem_out = (*head)->llitem;
    }
    free(*head);
    *head = next_node;

    return 0;
}

// remove the last
int llitem_rmend(llitem_node_t** head, llitem_t* llitem_out){
	llitem_node_t * cur;
    
    // if there is only one item in the list, remove it
    if ((*head)->next == NULL){
    	if(llitem_out != NULL){
        	*llitem_out = (*head)->llitem;
        }
        free(*head);
        *head = NULL;
        return 0;
    }

    cur = *head;
    while (cur->next->next != NULL){
        cur = cur->next;
    }

    *llitem_out = cur->next->llitem;
    free(cur->next);
    cur->next = NULL;
    return 0;
}

// remove by id
int lltime_rmbyid(llitem_node_t** head, int id_in, llitem_t* llitem_out){
    int idx = 0;
    llitem_node_t* cur = *head;
    llitem_node_t* node_tmp;

    if (id_in == 0){
    	return llitem_pop(head, llitem_out);
    }

    for(idx = 0; idx < id_in-1; idx++){
        if (cur->next == NULL){
            return -1;
        }
        cur = cur->next;
    }

    node_tmp = cur->next;
    if(llitem_out != NULL){
    	*llitem_out = node_tmp->llitem;
    }
    cur->next = node_tmp->next;
    free(node_tmp);
    node_tmp = NULL;

    return 0;
}

llitem_node_t* llitem_setitem_byid(llitem_node_t** head, int id_in, llitem_t* llitem_in){
    int idx = 0;
    llitem_node_t* cur = *head;

    for(idx = 0; idx < id_in; idx++){
        if (cur->next == NULL){
            return NULL;
        }
        cur = cur->next;
    }

    cur->llitem = *llitem_in;
	return cur;
}

llitem_node_t* llitem_setitem_bycmp(llitem_node_t** head, llitem_t* llitem_in, int (*itemcomparator_iseq)(const llitem_t*, const llitem_t*)){
    llitem_node_t* cur = *head;
    int id = 0;

    while (cur != NULL) {        
    	if( (*itemcomparator_iseq)(&cur->llitem, llitem_in) ){
    		cur->llitem = *llitem_in;
    		return cur;
    	}

    	id = id+1;
        cur = cur->next;
    }	
    return NULL;
}

////////////////////////////////////////
// example comparator functions
int llitemcompar_iseq_name(const llitem_t* item1, const llitem_t* item2){
	if(strncmp(item1->name, item2->name, ITEMNAME_MAXLEN) == 0){
		// same item
		return 1;
	}
	return 0;
}

int llitemcompar_iseq_stockcount(const llitem_t* item1, const llitem_t* item2){
	if(item1->stockcount == item2->stockcount){
		// same item
		return 1;
	}
	return 0;
}

int llitemcompar_iseq_item(const llitem_t* item1, const llitem_t* item2){
	if( (llitemcompar_iseq_name(item1, item2) == 1)
		&& (llitemcompar_iseq_stockcount(item1, item2) == 1)
	){
		// same item
		return 1;
	}
	return 0;
}

