#include <unitest.h>
#include <stdio.h>
#include <dlinked_list.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	int num;
	char colour[50];
} node_t;

void free_node(void* n){
	free(n);
}

void main_test(){
	node_t* p3;
	node_t* n1 = malloc(sizeof(node_t));
	node_t* n2 = malloc(sizeof(node_t));
	node_t* n3 = malloc(sizeof(node_t));
	dl_list_t* dl = dl_create(free_node);

	n1->num = 19;
	strcpy(n1->colour, "black");
	n2->num = 5;
	strcpy(n2->colour, "pink");
	n3->num = 3;
	strcpy(n3->colour, "purple");

	T_ASSERT(dl);
	dl_push(dl, n3);
	T_ASSERT(dl->head == dl->end);
	p3 = dl_pop(dl);
	T_ASSERT_NUM(p3->num, 3);
	T_ASSERT_STRING(p3->colour, "purple");
	dl_push(dl, n1);
	dl_push(dl, n2);
	T_ASSERT(dl->head != dl->end);
	T_ASSERT_NUM(dl_size(dl), 2);
	dl_free(dl);
	free_node(p3);
}

int main(void){
	TEST(Double linked list,
		main_test();
	);
	return 0;
}
