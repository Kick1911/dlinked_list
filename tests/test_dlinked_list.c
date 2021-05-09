#include <unitest.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <pthread.h>
#include <dlinked_list.h>
#include <utils/lock.h>

void
test_push_pop(){
    dl_node_t* ptr;
    double f = 3.14, *o, total = 0.0;
    dl_list_t dl;

    dl_init(&dl);

    dl_push(&dl, &f);
    T_ASSERT(dl.head == dl.end);
    o = dl_pop(&dl);
    T_ASSERT_FLOAT(*o, 3.14);
    dl_push(&dl, &f);
    dl_push(&dl, &f);
    dl_push(&dl, &f);
    T_ASSERT(dl.head != dl.end);
    T_ASSERT_NUM(dl.size, 3);
    /** Iterate through elements */
    ptr = dl.head;
    do{
        o = ptr->data;
        total += *o;
    }while( (ptr = ptr->next) );
    T_ASSERT_FLOAT(total, 9.42);

    /* Clean up */
    while(dl_pop(&dl));
    T_ASSERT_NUM(dl.size, 0);
    T_ASSERT(!dl.head);
    T_ASSERT(!dl.end);
}

void
test_pop_head(){
    dl_node_t* n2, *n4;
    double f = 3.14;
    dl_list_t dl;

    dl_init(&dl);

    dl_push(&dl, &f);
    n2 = dl_push(&dl, &f);
    dl_push(&dl, &f);
    dl_push(&dl, &f);
    T_ASSERT(dl.head != dl.end);
    T_ASSERT_NUM(dl.size, 4);

    dl_pop_head(&dl);
    n4 = dl_push(&dl, &f);
    dl_pop(&dl);
    T_ASSERT(dl.head = n2);
    T_ASSERT(dl.end = n4);
    T_ASSERT_NUM(dl.size, 3);

    while(dl_pop_head(&dl));
    T_ASSERT_NUM(dl.size, 0);
    T_ASSERT(!dl.head);
    T_ASSERT(!dl.end);
}

void
unlinking(){
    int count;
    dl_list_t* dl;
    dl_node_t* mid, *head, *end, *n2, *n4, *ptr;

    dl = malloc(sizeof(*dl));
    dl_init(dl);
    head = dl_push(dl, (void*)1);
    n2 = dl_push(dl, (void*)2);
    mid = dl_push(dl, (void*)3);
    n4 = dl_push(dl, (void*)4);
    end = dl_push(dl, (void*)5);

    T_ASSERT_NUM(dl->size, 5);
    dl_unlink(dl, mid);
    T_ASSERT_NUM(dl->size, 4);

    /* All nodes are connected */
    count = 0;
    ptr = dl->head;
    while( ptr->next && (ptr = ptr->next) ) count++;
    T_ASSERT(ptr == end);
    T_ASSERT_NUM(count + 1, 4);

    dl_unlink(dl, head);
    T_ASSERT_NUM(dl->size, 3);
    T_ASSERT(dl->head == n2);

    dl_unlink(dl, end);
    T_ASSERT_NUM(dl->size, 2);
    T_ASSERT(dl->end == n4);

    /* All nodes are connected */
    count = 0;
    ptr = dl->head;
    while( ptr->next && (ptr = ptr->next) ) count++;
    T_ASSERT(ptr == n4);
    T_ASSERT_NUM(count + 1, 2);

    /* Clean up */
    while(dl_pop(dl));
    T_ASSERT_NUM(dl->size, 0);
    T_ASSERT(!dl->head);
    T_ASSERT(!dl->end);
    free(dl);
}

void*
thread(void* arg){
    dl_list_t* l = arg;
    mutex_lock(l);
    sleep(5);
    mutex_unlock(l);
    return NULL;
}

void
test_mutex(){
    double f = 3.14;
    pthread_t t;
    dl_list_t* l;

    l = malloc(sizeof(*l));
    dl_init(l);

    pthread_create(&t, NULL, thread, l);
    sleep(1);

    T_ASSERT_NUM(l->lock, 1);
    mutex_lock(l);
    pthread_join(t, NULL);
    mutex_unlock(l);
    T_ASSERT_NUM(l->lock, 0);

    dl_free(l);
    free(l);
}

int main(void){
    T_SUITE(Double Linked List,
        TEST(Push and pop, test_push_pop());
        TEST(Unlinking, unlinking());
        TEST(Pop head to tail, test_pop_head());
        TEST(Mutex lock, test_mutex());
    );
    T_CONCLUDE();
    return 0;
}
