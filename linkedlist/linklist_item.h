/**
 * @file linklist_item.h
 * @author Napat Rungruangbangchan
 * @date 9 September 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#ifndef __LINKLIST_DAT_H__
#define __LINKLIST_DAT_H__

// linked list data structure
// ------------------------------              ------------------------------
// |              |             |            \ |              |             |
// |     DATA     |     NEXT    |--------------|     DATA     |     NEXT    |
// |              |             |            / |              |             |
// ------------------------------              ------------------------------

#define ITEMNAME_MAXLEN		(20)
typedef struct llitem_s{
    char 	name[ITEMNAME_MAXLEN];
    int 	stockcount;
} llitem_t;

typedef struct llitem_node_s{	
    llitem_t	llitem;
    struct llitem_node_s* next;
} llitem_node_t;

llitem_node_t*  llitem_node_next(llitem_node_t* llitem_node);
int llitem_node_islast(llitem_node_t* llitem_node);
llitem_t* llitem_item(llitem_node_t* llitem_node, llitem_t*	llitem_out);
int llitem_count(llitem_node_t* llitem_node);

void llitem_printall(llitem_node_t* head, FILE* output);
int lltime_getitemid(llitem_node_t** head, llitem_t* llitem_in, int (*itemcomparator_iseq)(const llitem_t*, const llitem_t*));
int lltime_getitem_byid(llitem_node_t** head, int id_in, llitem_t* llitem_in);
llitem_node_t* llitem_addend(llitem_node_t** head, llitem_t* llitem_in);
llitem_node_t* llitem_push(llitem_node_t** head, llitem_t* llitem_in);
llitem_node_t* llitem_addid(llitem_node_t** head, int id_in, llitem_t* llitem_in);
int llitem_pop(llitem_node_t** head, llitem_t* llitem_out);
int llitem_rmend(llitem_node_t** head, llitem_t* llitem_out);
int lltime_rmbyid(llitem_node_t** head, int id_in, llitem_t* llitem_out);
llitem_node_t* llitem_setitem_byid(llitem_node_t** head, int id_in, llitem_t* llitem_in);
llitem_node_t* llitem_setitem_bycmp(llitem_node_t** head, llitem_t* llitem_in, int (*itemcomparator_iseq)(const llitem_t*, const llitem_t*));

#endif /* __LINKLIST_DAT_H__ */
