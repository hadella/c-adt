#include <criterion/criterion.h>

#include <stdlib.h> // free()

#include "../src/list.h"

List list;

int *item1 = NULL;
int *item2 = NULL;
int *item3 = NULL;

void
suite_setup()
{
	item1 = (int*)malloc(sizeof (int));
	item2 = (int*)malloc(sizeof (int));
	item3 = (int*)malloc(sizeof (int));

	list_init(&list, free);
}

void
suite_teardown()
{
	list_destroy(&list);
}

TestSuite(list_tests, .init=suite_setup, .fini=suite_teardown);

Test(list_tests, empty)
{
	cr_expect(list_size(&list) == 0, "empty list's size should be 0");
	cr_expect(list_head(&list) == NULL, "empty list's head should be NULL");
	cr_expect(list_tail(&list) == NULL, "empty list's tail should be NULL");
}

Test(list_tests, insert_into_empty)
{
	// Give our item a value
	*item1 = 1;

	cr_expect(list_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(list_size(&list) == 1, "list's size should be 1");
	cr_expect(list_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(list_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(list_is_head(&list, list_head(&list)) == 1, "head should be at the head of the list");
	cr_expect(list_is_tail(list_tail(&list)) == 1, "tail should be at the tail of the list");
	cr_expect(list_next(list_head(&list)) == NULL, "next should be NULL for head of one element list");
	cr_expect(list_next(list_tail(&list)) == NULL, "next should be NULL for tail of one element list");
	cr_expect(list_data(list_head(&list)) == item1, "head should be the item inserted");
	cr_expect(list_data(list_tail(&list)) == item1, "tail should be the item inserted");
}

Test(list_tests, insert_after_head)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;

	cr_expect(list_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(list_size(&list) == 1, "list's size should be 1");
	cr_expect(list_insert_next(&list, list_head(&list), item2) == 0, "insert after head should return 0");
	cr_expect(list_size(&list) == 2, "list's size should be 2");
	cr_expect(list_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(list_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(list_next(list_head(&list)) != NULL, "next should be not NULL for head of two element list");
	cr_expect(list_next(list_tail(&list)) == NULL, "next should be NULL for tail of two element list");
	cr_expect(list_data(list_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(list_data(list_tail(&list)) == item2, "tail should be the second item inserted");
}

Test(list_tests, insert_twice_at_head)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;

	cr_expect(list_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(list_size(&list) == 1, "list's size should be 1");
	cr_expect(list_insert_next(&list, NULL, item2) == 0, "insert after head should return 0");
	cr_expect(list_size(&list) == 2, "list's size should be 2");
	cr_expect(list_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(list_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(list_next(list_head(&list)) != NULL, "next should be not NULL for head of two element list");
	cr_expect(list_next(list_tail(&list)) == NULL, "next should be NULL for tail of two element list");
	cr_expect(list_data(list_head(&list)) == item2, "head should be the second item inserted");
	cr_expect(list_data(list_tail(&list)) == item1, "tail should be the first item inserted");
}

Test(list_tests, insert_twice_at_tail)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;

	cr_expect(list_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(list_size(&list) == 1, "list's size should be 1");
	cr_expect(list_insert_next(&list, list_tail(&list), item2) == 0, "insert after tail should return 0");
	cr_expect(list_size(&list) == 2, "list's size should be 2");
	cr_expect(list_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(list_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(list_next(list_head(&list)) != NULL, "next should be not NULL for head of two element list");
	cr_expect(list_next(list_tail(&list)) == NULL, "next should be NULL for tail of two element list");
	cr_expect(list_data(list_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(list_data(list_tail(&list)) == item2, "tail should be the second item inserted");
}

Test(list_tests, remove_at_head)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;

	// Pointer to removed item
	void* removed;

	cr_expect(list_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(list_size(&list) == 1, "list's size should be 1");
	cr_expect(list_insert_next(&list, NULL, item2) == 0, "insert after head should return 0");
	cr_expect(list_size(&list) == 2, "list's size should be 2");
	cr_expect(list_remove_next(&list, NULL, &removed) == 0, "remove at head should return 0");
	cr_expect(list_size(&list) == 1, "list's size should be 1");
	cr_expect(list_data(list_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(removed == item2, "removed item should point to the second item inserted");
}

Test(list_tests, remove_after_head)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;

	// Pointer to removed item
	void* removed;

	cr_expect(list_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(list_size(&list) == 1, "list's size should be 1");
	cr_expect(list_insert_next(&list, NULL, item2) == 0, "insert after head should return 0");
	cr_expect(list_size(&list) == 2, "list's size should be 2");
	cr_expect(list_remove_next(&list, list_head(&list), &removed) == 0, "remove at head should return 0");
	cr_expect(list_size(&list) == 1, "list's size should be 1");
	cr_expect(list_data(list_head(&list)) == item2, "head should be the second item inserted");
	cr_expect(removed == item1, "removed item should point to the first item inserted");
}

Test(list_tests, add_and_remove)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;

	// Pointer to removed item
	void* removed;

	cr_expect(list_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(list_size(&list) == 1, "list's size should be 1");
	cr_expect(list_insert_next(&list, NULL, item2) == 0, "insert after head should return 0");
	cr_expect(list_size(&list) == 2, "list's size should be 2");

	cr_expect(list_remove_next(&list, NULL, &removed) == 0, "remove at head should return 0");
	cr_expect(list_size(&list) == 1, "list's size should be 1");
	cr_expect(list_data(list_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(removed == item2, "removed item should point to the second item inserted");

	cr_expect(list_remove_next(&list, NULL, &removed) == 0, "remove at head should return 0");
	cr_expect(list_size(&list) == 0, "list's size should be 0");
	cr_expect(list_head(&list) == NULL, "head should be NULL");
	cr_expect(removed == item1, "removed item should point to the first item inserted");
}
