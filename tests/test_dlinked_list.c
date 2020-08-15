#include <unitest.h>
#include <stdio.h>
#include <dlinked_list.h>
#include <malloc.h>

void test_push_pop(){
	void* ptr;
	double f = 3.14, *o, total = 0.0;
	dl_list_t* dl = dl_create();

	T_ASSERT(dl);
	dl_push(dl, &f);
	T_ASSERT(dl->head == dl->end);
	o = dl_pop(dl);
	T_ASSERT_FLOAT(*o, 3.14);
	dl_push(dl, &f);
	dl_push(dl, &f);
	dl_push(dl, &f);
	T_ASSERT(dl->head != dl->end);
	T_ASSERT_NUM(dl_size(dl), 3);
	/** Iterate through elements */
	ptr = dl_head(dl);
	do{
		o = dl_data(ptr);
		total += *o;
	}while( (ptr = dl_next(ptr)) );
	T_ASSERT_FLOAT(total, 9.42);

	/* Clean up */
	while(dl_pop(dl));
	T_ASSERT_NUM(dl_size(dl), 0);
	dl_free(dl);
}

void unlinking(){
	int count;
	void* mid, *head, *end, *n2, *n4, *ptr;
	dl_list_t* dl = dl_create();

	head = dl_push(dl, (void*)1);
	n2 = dl_push(dl, (void*)2);
	mid = dl_push(dl, (void*)3);
	n4 = dl_push(dl, (void*)4);
	end = dl_push(dl, (void*)5);

	T_ASSERT_NUM(dl_size(dl), 5);
	dl_unlink(dl, mid);
	T_ASSERT_NUM(dl_size(dl), 4);

	/* All nodes are connected */
	count = 0;
	ptr = dl_head(dl);
	while( dl_next(ptr) && (ptr = dl_next(ptr)) ) count++;
	T_ASSERT_NUM(ptr, end);
	T_ASSERT_NUM(count + 1, 4);

	dl_unlink(dl, head);
	T_ASSERT_NUM(dl_size(dl), 3);
	T_ASSERT_NUM(dl_head(dl), n2);

	dl_unlink(dl, end);
	T_ASSERT_NUM(dl_size(dl), 2);
	T_ASSERT_NUM(dl_peek(dl), n4);

	/* All nodes are connected */
	count = 0;
	ptr = dl_head(dl);
	while( dl_next(ptr) && (ptr = dl_next(ptr)) ) count++;
	T_ASSERT_NUM(ptr, n4);
	T_ASSERT_NUM(count + 1, 2);

	/* Clean up */
	while(dl_pop(dl));
	T_ASSERT_NUM(dl_size(dl), 0);
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
