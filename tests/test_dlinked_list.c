#include <unitest.h>
#include <stdio.h>
#include <dlinked_list.h>
#include <malloc.h>

void test_push_pop(){
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
}

void unlinking(){
    int count;
    dl_node_t* mid, *head, *end, *n2, *n4, *ptr;
    dl_list_t* dl = dl_init(NULL);

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
    dl_free(dl);
}

int main(void){
    T_SUITE(Double Linked List,
        TEST(Push and pop, test_push_pop());
        TEST(Unlinking, unlinking());
    );
    T_CONCLUDE();
    return 0;
}
