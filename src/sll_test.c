#include <stdio.h>
#include <string.h>
#include "sll.h"

#define RUN_TEST(x) if (x()) printf("%s \033[1;32mPASSED\033[0m\n", #x);
#define ASSERT_EQ(x, y) if (x != y) { printf("%s \033[1;31mFAILED\033[0m got = %d , wanted = %d\n", __func__, x, y); return 0; }

int sll_new_test(void) {
	sll_t* root = sll_new("hello");
	
	if (!root) return 0;
	if (memcmp(root->data, "hello", 5)) return 0;
	if (sll_get_size(root) != 1) return 0;

	sll_free(root);
	return 1;
}

struct pair {
	int x;
	int y;
};

void print_pair(void* pair) {
	fprintf(stdout, "\t%d\t%d\n", ((struct pair*)pair)->x, ((struct pair*)pair)->y);
}

int sll_struct_as_data_test(void) {
	struct pair a = {1, 2};
	struct pair b = {63, 74};
	struct pair c = {32, 91};

	sll_t* root = sll_new(&a);
	sll_insert_back(root, &b);
	sll_insert_back(root, &c);

	printf("struct pair sll print func test:\n");
	sll_debug(root, print_pair);

	ASSERT_EQ(sll_get_size(root), 3);
	ASSERT_EQ(memcmp(root->data, &a, sizeof(a)), 0);

	sll_free(root);
	return 1;
}

void print_str(void* str) {
	fprintf(stdout, "%s\n", (char*)str);
}

int sll_remove_test(void) {
	sll_t* root = sll_new("root_node");
	sll_insert_back(root, "second_node");
	sll_insert_back(root, "third_node");

	ASSERT_EQ(sll_get_size(root), 3);
	ASSERT_EQ(sll_remove(root, "second_node", 12), SLL_FINE);
	ASSERT_EQ(sll_get_size(root), 2)

	sll_remove_front(&root);
	ASSERT_EQ(memcmp(root->data, "third_node", 11), 0);

	sll_insert(root, "omg");
	ASSERT_EQ(sll_get_size(root), 2);

	ASSERT_EQ(sll_remove_back(root), SLL_FINE);
	ASSERT_EQ(sll_get_size(root), 1);

	sll_insert_back(root, "second");
	sll_insert_back(root, "third");
	sll_insert_back(root, "fourth");
	sll_insert_back(root, "fifth");

	ASSERT_EQ(sll_get_size(root), 5);

	sll_remove_at(&root, 3);
	ASSERT_EQ(sll_get_size(root), 4);
	ASSERT_EQ(memcmp(sll_at(root, 3)->data, "fifth", 6), 0);

	sll_free(root);
	return 1;
}

int sll_insert_test(void) {
	sll_t* root = sll_new("root_node");

	sll_insert_front(&root, "new_node");
	sll_insert(root, "second_node");
	sll_insert(root, "third_node");
	sll_insert(root, "fourth_node");

	ASSERT_EQ(sll_get_size(root), 5);
	ASSERT_EQ(memcmp(root->next->data, "fourth_node", 12), 0);

	sll_free(root);
	return 1;
}

int main(void) {
	
	RUN_TEST(sll_new_test);
	RUN_TEST(sll_struct_as_data_test);
	RUN_TEST(sll_remove_test);
	RUN_TEST(sll_insert_test);

	return 0;
}
