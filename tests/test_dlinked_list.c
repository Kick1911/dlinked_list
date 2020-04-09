#include <unitest.h>
#include <stdio.h>
#include <dlinked_list.h>

void main_test(){
	double f = 3.14, *o;
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
	dl_free(dl);
}

int main(void){
	TEST(Double linked list,
		main_test();
	);
	return 0;
}
