/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 9 September 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include "linklist_item.h"

////////////////////////////////////////
// Example comparator functions
int llitemcompar_iseq_name(const llitem_t *item1, const llitem_t *item2);
int llitemcompar_iseq_stockcount(const llitem_t *item1, const llitem_t *item2);
int llitemcompar_iseq_item(const llitem_t *item1, const llitem_t *item2);

int main(int argc, char * argv[]){
	int id;
	llitem_t llitem_tmp;
	llitem_node_t* llitem_head = NULL;
	llitem_node_t* llitem_node_tmp;

	printf("\n-%d-llitem_push------------------\n", __LINE__);

	sprintf(llitem_tmp.name, "cat dolls");
	llitem_tmp.stockcount = 3;
	llitem_push(&llitem_head, &llitem_tmp);

	llitem_printall(llitem_head, stdout);

	printf("\n-%d-llitem_addend------------------\n", __LINE__);

	sprintf(llitem_tmp.name, "kangaroo dolls");
	llitem_tmp.stockcount = 10;
	llitem_addend(&llitem_head, &llitem_tmp);
	
	llitem_printall(llitem_head, stdout);

	printf("\n-%d-llitem_addend------------------\n", __LINE__);

	sprintf(llitem_tmp.name, "monkey dolls");
	llitem_tmp.stockcount = 6;
	llitem_addend(&llitem_head, &llitem_tmp);

	llitem_printall(llitem_head, stdout);

	printf("\n-%d-llitem_push------------------\n", __LINE__);

	sprintf(llitem_tmp.name, "bird dolls");
	llitem_tmp.stockcount = 9;
	llitem_push(&llitem_head, &llitem_tmp);

	llitem_printall(llitem_head, stdout);

	printf("\n-%d-llitem_push------------------\n", __LINE__);

	sprintf(llitem_tmp.name, "dog dolls");
	llitem_tmp.stockcount = 2;
	llitem_push(&llitem_head, &llitem_tmp);

	llitem_printall(llitem_head, stdout);

	printf("\n-%d-llitem_addid------------------\n", __LINE__);

	id = 0;
	sprintf(llitem_tmp.name, "bat dolls");
	llitem_tmp.stockcount = 4;
	llitem_addid(&llitem_head, id, &llitem_tmp);

	id = 4;
	sprintf(llitem_tmp.name, "rat dolls");
	llitem_tmp.stockcount = 3;
	llitem_addid(&llitem_head, id, &llitem_tmp);

	id = 7;
	sprintf(llitem_tmp.name, "ant dolls");
	llitem_tmp.stockcount = 4;
	llitem_addid(&llitem_head, id, &llitem_tmp);

	// test id out of range
	id = 100;
	sprintf(llitem_tmp.name, "monkey dolls");
	llitem_tmp.stockcount = 50;
	llitem_addid(&llitem_head, id, &llitem_tmp);

	llitem_printall(llitem_head, stdout);

	printf("\n-%d-llitem_pop------------------\n", __LINE__);

	llitem_pop(&llitem_head, &llitem_tmp);
	printf("pop item name: %s, count: %d\n", llitem_tmp.name, llitem_tmp.stockcount);

	llitem_printall(llitem_head, stdout);

	printf("\n-%d-llitem_rmend------------------\n", __LINE__);

	llitem_rmend(&llitem_head, &llitem_tmp);
	printf("dequeue item name: %s, count: %d\n", llitem_tmp.name, llitem_tmp.stockcount);

	llitem_printall(llitem_head, stdout);

	printf("\n-%d-lltime_getitemid------------------\n", __LINE__);

	sprintf(llitem_tmp.name, "kangaroo dolls");
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_name);
	printf("%s is id = %d\n", llitem_tmp.name, id);

	sprintf(llitem_tmp.name, "cat dolls");
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_name);
	printf("%s is id = %d\n", llitem_tmp.name, id);

	sprintf(llitem_tmp.name, "bird dolls");
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_name);
	printf("%s is id = %d\n", llitem_tmp.name, id);

	sprintf(llitem_tmp.name, "dog dolls");
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_name);
	printf("%s is id = %d\n", llitem_tmp.name, id);

	printf("\n-%d-lltime_getitemid------------------\n", __LINE__);

	llitem_tmp.stockcount = 3;
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_stockcount);
	printf("stockcount %d is id = %d\n", llitem_tmp.stockcount, id);

	llitem_tmp.stockcount = 5;
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_stockcount);
	printf("stockcount %d is id = %d\n", llitem_tmp.stockcount, id);

	llitem_tmp.stockcount = 10;
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_stockcount);
	printf("stockcount %d is id = %d\n", llitem_tmp.stockcount, id);

	printf("\n-%d-lltime_getitemid------------------\n", __LINE__);

	sprintf(llitem_tmp.name, "kangaroo dolls");
	llitem_tmp.stockcount = 10;
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_item);
	printf("%s/%d is id = %d\n", llitem_tmp.name, llitem_tmp.stockcount, id);

	sprintf(llitem_tmp.name, "bird dolls");
	llitem_tmp.stockcount = 5;
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_item);
	printf("%s/%d is id = %d\n", llitem_tmp.name, llitem_tmp.stockcount, id);

	sprintf(llitem_tmp.name, "cat dolls");
	llitem_tmp.stockcount = 10;
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_item);
	printf("%s/%d is id = %d\n", llitem_tmp.name, llitem_tmp.stockcount, id);

	printf("\n-%d-lltime_rmbyid------------------\n", __LINE__);

	llitem_printall(llitem_head, stdout);
	
	lltime_rmbyid(&llitem_head, 1, NULL);

	llitem_printall(llitem_head, stdout);

	printf("\n-%d-lltime_getitem_byid/llitem_setitem_byid------------------\n", __LINE__);

	sprintf(llitem_tmp.name, "cat dolls");
	id = lltime_getitemid(&llitem_head, &llitem_tmp, llitemcompar_iseq_name);
	lltime_getitem_byid(&llitem_head, id, &llitem_tmp);
	llitem_tmp.stockcount = 1;
	llitem_setitem_byid(&llitem_head, id, &llitem_tmp);

	llitem_printall(llitem_head, stdout);

	printf("\n-%d-llitem_setitem_bycmp------------------\n", __LINE__);

	sprintf(llitem_tmp.name, "cat dolls");
	llitem_tmp.stockcount = 2;
	llitem_setitem_bycmp(&llitem_head, &llitem_tmp, llitemcompar_iseq_name);

	llitem_printall(llitem_head, stdout);

	printf("\n-%d-To iterate items------------------\n", __LINE__);

	for(llitem_node_tmp = llitem_head; 
		llitem_node_tmp != NULL; 
		llitem_node_tmp = llitem_node_next(llitem_node_tmp)
	){
		llitem_item(llitem_node_tmp, &llitem_tmp);
		printf("%s\n", llitem_tmp.name);
	}

	printf("\n-%d-------------------\n", __LINE__);

	return 0;
}


