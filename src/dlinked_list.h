#ifndef _DLINKED_LIST_H
#define _DLINKED_LIST_H
#include <stddef.h>

typedef struct dl_node{
    void* data;
    struct dl_node* prev;
    struct dl_node* next;
} dl_node_t;

typedef struct{
    int lock;
    size_t size;
    dl_node_t* head;
    dl_node_t* end;
} dl_list_t;

/*
 * Initialises the Double linked list.
 * NOTE: Does not malloc the dl_list_t structure
 */
dl_list_t* dl_init(dl_list_t*);

/*
 * Append to the list
 * This function can only fail on malloc.
 * @return Double linked list node else NULL (malloc failed)
 */
dl_node_t* dl_push(dl_list_t* l, void* data);

/*
 * Removes the tail of the list
 * @return data that was passed into dl_push
 */
void* dl_pop(dl_list_t* l);

/*
 * Removes the head of the list
 * @return data that was passed into dl_push
 */
void* dl_pop_head(dl_list_t* l);

/*
 * Removes node from anywhere in the list
 * @return data that was passed into dl_push
 */
void* dl_unlink(dl_list_t* l, dl_node_t* n);

/*
 * Free the double linked list
 * NOTE: Does not free the dl_list_t structure
 */
void dl_free(dl_list_t* l);

#endif

