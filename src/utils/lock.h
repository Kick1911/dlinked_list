#ifndef _LOCK_H
#define _LOCK_H
#include <dlinked_list.h>

static void
mutex_lock(dl_list_t* l){
    while(l->lock){
        __asm__ ("pause"); /* Does not seem to be working */
    }
    l->lock = 1;
}

static void
mutex_unlock(dl_list_t* l){
    l->lock = 0;
}

#endif

