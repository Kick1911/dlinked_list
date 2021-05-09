#include <malloc.h>
#include <errno.h>
#include <dlinked_list.h>
#include <utils/lock.h>

static dl_node_t*
dl_create_node(void* data){
    dl_node_t* n = malloc(sizeof(dl_node_t));

    if(!n){ perror("dl_create failed"); return NULL; }

    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

dl_list_t*
dl_init(dl_list_t* l){
    l->lock = 0;
    l->size = 0;
    l->head = NULL;
    l->end = NULL;
    return l;
}

dl_node_t*
dl_push(dl_list_t* l, void* data){
    dl_node_t* n;

    mutex_lock(l);
    n = dl_create_node(data);
    if(!n) return NULL;

    n->data = data;
    n->next = NULL;
    n->prev = l->end;
    if (n->prev != NULL)
        n->prev->next = n;
    else
        l->head = n;
    l->end = n;
    l->size++;
    mutex_unlock(l);
    return n;
}

void*
dl_pop(dl_list_t* l){
    void* d;
    dl_node_t* n = l->end;

    if(!n) return NULL;

    mutex_lock(l);

    d = n->data;
    l->end = n->prev;
    if(l->end)
        l->end->next = NULL;
    else
        l->head = NULL;

    free(n);
    l->size--;
    mutex_unlock(l);
    return d;
}

void*
dl_pop_head(dl_list_t* l){
    void* d;
    dl_node_t* n = l->head;

    if(!n) return NULL;

    mutex_lock(l);

    d = n->data;
    l->head = n->next;
    if(l->head)
        l->head->prev = NULL;
    else
        l->end = NULL;
    l->size--;
    free(n);
    mutex_unlock(l);
    return d;
}

void*
dl_unlink(dl_list_t* l, dl_node_t* n){
    void* d;
    if(l->end == n)
        return dl_pop(l);
    if(l->head == n)
        return dl_pop_head(l);
    mutex_lock(l);
    d = n->data;
    n->prev->next = n->next;
    n->next->prev = n->prev;
    l->size--;
    free(n);
    mutex_unlock(l);
    return d;
}

void
dl_free(dl_list_t* l){
    while(dl_pop(l));
}
