#ifndef _DLINKED_LIST_H
#define _DLINKED_LIST_H
#include <stddef.h>

typedef struct dl_node{
    void* data;
    struct dl_node* prev;
    struct dl_node* next;
} dl_node_t;

typedef struct{
    size_t size;
    dl_node_t* head;
    dl_node_t* end;
} dl_list_t;

#define DL_HEAD(l) ((dl_list_t*)(l))->head
#define DL_PEAK(l) ((dl_list_t*)(l))->end
#define DL_SIZE(l) ((dl_list_t*)(l))->size
#define DN_NEXT(n) ((dl_node_t*)(n))->next
#define DN_PREV(n) ((dl_node_t*)(n))->prev
#define DN_DATA(n) ((dl_node_t*)(n))->data

dl_list_t* dl_create();
dl_node_t* dl_push(dl_list_t* l, void* data);
void* dl_pop(dl_list_t* l);
void* dl_unlink(dl_list_t* l, dl_node_t* n);
void dl_free(dl_list_t* l);

#endif

