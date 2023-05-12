#include <criterion/criterion.h>

#include <stdio.h>
#include <stdlib.h> // free()

#include "../src/dlist.h"

DList list;

int *item1 = NULL;
int *item2 = NULL;
int *item3 = NULL;

// static void print_dlist(const DList *list)
// {
// 	DList_Element *element;
// 	int *data;
// 	int i;

// 	// Display the linked-list
// 	fprintf(stdout, "List size is %d\n", dlist_size(list));

// 	i = 0;
// 	element = dlist_head(list);

// 	while (1) {
// 		data = dlist_data(element);
// 		fprintf(stdout, "list[%d]=%d\n", i, *data);

// 		i++;

// 		if (dlist_is_tail(element))
// 			break;
// 		else
// 			element = dlist_next(element);
// 	}
// }

void suite_setup()
{
	item1 = (int*)malloc(sizeof (int));
	item2 = (int*)malloc(sizeof (int));
	item3 = (int*)malloc(sizeof (int));

	dlist_init(&list, free);
}

void suite_teardown()
{
	dlist_destroy(&list);
}

TestSuite(list_tests, .init=suite_setup, .fini=suite_teardown);

Test(list_tests, empty)
{
	cr_expect(dlist_size(&list) == 0, "empty dlist's size should be 0");
	cr_expect(dlist_head(&list) == NULL, "empty dlist's head should be NULL");
	cr_expect(dlist_tail(&list) == NULL, "empty dlist's tail should be NULL");
}

Test(list_tests, insert_next_into_empty)
{
	// Give our item a value
	*item1 = 1;

	// List starts empty
	cr_expect(dlist_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	//    h t
	//    [1]->0
	// 0<-[ ]

	cr_expect(dlist_is_head(dlist_head(&list)) == 1, "head should be at the head of the list");
	cr_expect(dlist_is_tail(dlist_tail(&list)) == 1, "tail should be at the tail of the list");
	cr_expect(dlist_next(dlist_head(&list)) == NULL, "next should be NULL for head of one element list");
	cr_expect(dlist_next(dlist_tail(&list)) == NULL, "next should be NULL for tail of one element list");
	cr_expect(dlist_prev(dlist_head(&list)) == NULL, "prev should be NULL for head of one element list");
	cr_expect(dlist_prev(dlist_tail(&list)) == NULL, "prev should be NULL for tail of one element list");
	cr_expect(dlist_data(dlist_head(&list)) == item1, "head should be the item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item1, "tail should be the item inserted");
}

Test(list_tests, insert_prev_into_empty)
{
	// Give our item a value
	*item1 = 1;

	// List starts empty
	cr_expect(dlist_insert_prev(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	//    h t
	//    [1]->0
	// 0<-[ ]

	cr_expect(dlist_is_head(dlist_head(&list)) == 1, "head should be at the head of the list");
	cr_expect(dlist_is_tail(dlist_tail(&list)) == 1, "tail should be at the tail of the list");
	cr_expect(dlist_next(dlist_head(&list)) == NULL, "next should be NULL for head of one element list");
	cr_expect(dlist_next(dlist_tail(&list)) == NULL, "next should be NULL for tail of one element list");
	cr_expect(dlist_prev(dlist_head(&list)) == NULL, "prev should be NULL for head of one element list");
	cr_expect(dlist_prev(dlist_tail(&list)) == NULL, "prev should be NULL for tail of one element list");
	cr_expect(dlist_data(dlist_head(&list)) == item1, "head should be the item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item1, "tail should be the item inserted");
}

Test(list_tests, insert_next_at_head)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;

	// List starts empty
	cr_expect(dlist_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	//    h t
	//    [1]->0
	// 0<-[ ]

	cr_expect(dlist_insert_next(&list, dlist_head(&list), item2) == 0, "insert after head should return 0");
	cr_expect(dlist_size(&list) == 2, "list's size should be 2");
	//    h    t
	//    [1]->[2]->0
	// 0<-[ ]<-[ ]

	cr_expect(dlist_insert_next(&list, dlist_head(&list), item3) == 0, "insert after head should return 0");
	cr_expect(dlist_size(&list) == 3, "list's size should be 3");
	//    h         t
	//    [1]->[3]->[2]->0
	// 0<-[ ]<-[ ]<-[ ]

	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(dlist_next(dlist_head(&list)) != NULL, "next should be not NULL for head of three element list");
	cr_expect(dlist_next(dlist_tail(&list)) == NULL, "next should be NULL for tail of three element list");
	cr_expect(dlist_prev(dlist_head(&list)) == NULL, "prev should be NULL for head of three element list");
	cr_expect(dlist_prev(dlist_tail(&list)) != NULL, "prev should be not NULL for tail of three element list");
	cr_expect(dlist_data(dlist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(dlist_data(dlist_next(dlist_head(&list))) == item3, "middle item should be third item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item2, "tail should be the second item inserted");
}

Test(list_tests, insert_prev_at_head)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;

	// List starts empty
	cr_expect(dlist_insert_prev(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	//    h t
	//    [1]->0
	// 0<-[ ]

	cr_expect(dlist_insert_prev(&list, dlist_head(&list), item2) == 0, "insert after head should return 0");
	cr_expect(dlist_size(&list) == 2, "list's size should be 2");
	//    h    t
	//    [2]->[1]->0
	// 0<-[ ]<-[ ]

	cr_expect(dlist_insert_prev(&list, dlist_head(&list), item3) == 0, "insert after head should return 0");
	cr_expect(dlist_size(&list) == 3, "list's size should be 3");
	//    h         t
	//    [3]->[2]->[1]->0
	// 0<-[ ]->[ ]<-[ ]

	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(dlist_next(dlist_head(&list)) != NULL, "next should be not NULL for head of three element list");
	cr_expect(dlist_next(dlist_tail(&list)) == NULL, "next should be NULL for tail of three element list");
	cr_expect(dlist_prev(dlist_head(&list)) == NULL, "prev should be NULL for head of three element list");
	cr_expect(dlist_prev(dlist_tail(&list)) != NULL, "prev should be not NULL for tail of three element list");
	cr_expect(dlist_data(dlist_head(&list)) == item3, "head should be the third item inserted");
	cr_expect(dlist_data(dlist_next(dlist_head(&list))) == item2, "middle item should be second item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item1, "tail should be the first item inserted");
}

Test(list_tests, insert_next_at_tail)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;

	// List starts empty
	cr_expect(dlist_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	//    h t
	//    [1]->0
	// 0<-[ ]

	cr_expect(dlist_insert_next(&list, dlist_tail(&list), item2) == 0, "insert after tail should return 0");
	cr_expect(dlist_size(&list) == 2, "list's size should be 2");
	//    h    t
	//    [1]->[2]->0
	// 0<-[ ]<-[ ]

	cr_expect(dlist_insert_next(&list, dlist_tail(&list), item3) == 0, "insert after tail should return 0");
	cr_expect(dlist_size(&list) == 3, "list's size should be 3");
	//    h         t
	//    [1]->[2]->[3]->0
	// 0<-[ ]<-[ ]<-[ ]

	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(dlist_next(dlist_head(&list)) != NULL, "next should be not NULL for head of three element list");
	cr_expect(dlist_next(dlist_tail(&list)) == NULL, "next should be NULL for tail of three element list");
	cr_expect(dlist_prev(dlist_head(&list)) == NULL, "prev should be NULL for head of three element list");
	cr_expect(dlist_prev(dlist_tail(&list)) != NULL, "prev should be not NULL for tail of three element list");
	cr_expect(dlist_data(dlist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item3, "tail should be the second item inserted");
}

Test(list_tests, insert_prev_at_tail)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;

	// List starts empty
	cr_expect(dlist_insert_prev(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	//    h t
	//    [1]->0
	// 0<-[ ]

	cr_expect(dlist_insert_prev(&list, dlist_tail(&list), item2) == 0, "insert before tail should return 0");
	cr_expect(dlist_size(&list) == 2, "list's size should be 2");
	//    h    t
	//    [2]->[1]->0
	// 0<-[ ]<-[ ]

	cr_expect(dlist_insert_prev(&list, dlist_tail(&list), item3) == 0, "insert before tail should return 0");
	cr_expect(dlist_size(&list) == 3, "list's size should be 3");
	//    h         t
	//    [2]->[3]->[1]->0
	// 0<-[ ]<-[ ]<-[ ]

	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(dlist_next(dlist_head(&list)) != NULL, "next should be not NULL for head of three element list");
	cr_expect(dlist_next(dlist_tail(&list)) == NULL, "next should be NULL for tail of three element list");
	cr_expect(dlist_prev(dlist_head(&list)) == NULL, "prev should be NULL for head of three element list");
	cr_expect(dlist_prev(dlist_tail(&list)) != NULL, "prev should be not NULL for tail of three element list");
	cr_expect(dlist_data(dlist_head(&list)) == item2, "head should be the second item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item1, "tail should be the first item inserted");
}

Test(list_tests, remove_at_head)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;

	// Pointer to removed item
	void* removed;

	// List starts empty
	cr_expect(dlist_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	//    h t
	//    [1]->0
	// 0<-[ ]

	cr_expect(dlist_insert_next(&list, dlist_tail(&list), item2) == 0, "insert after tail should return 0");
	cr_expect(dlist_size(&list) == 2, "list's size should be 2");
	//    h    t
	//    [1]->[2]->0
	// 0<-[ ]<-[ ]

	cr_expect(dlist_insert_next(&list, dlist_tail(&list), item3) == 0, "insert after tail should return 0");
	cr_expect(dlist_size(&list) == 3, "list's size should be 3");
	//    h         t
	//    [1]->[2]->[3]->0
	// 0<-[ ]<-[ ]<-[ ]

	cr_expect(dlist_remove(&list, dlist_head(&list), &removed) == 0, "remove at head should return 0");
	cr_expect(dlist_size(&list) == 2, "list's size should be 2");
	//    h    t
	//    [2]->[3]->0
	// 0<-[ ]<-[ ]

	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(dlist_data(dlist_head(&list)) == item2, "head should be the second item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item3, "tail should be the third item inserted");
	cr_expect(removed == item1, "removed item should point to the first item inserted");

	cr_expect(dlist_remove(&list, dlist_head(&list), &removed) == 0, "remove at head should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	//    h t
	//    [3]->0
	// 0<-[ ]

	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(dlist_data(dlist_head(&list)) == item3, "head should be the third item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item3, "tail should be the third item inserted");
	cr_expect(removed == item2, "removed item should point to the first item inserted");

	cr_expect(dlist_remove(&list, dlist_head(&list), &removed) == 0, "remove at head should return 0");
	cr_expect(dlist_size(&list) == 0, "list's size should be 0");
	// List is empty, removed=[3]

	cr_expect(dlist_head(&list) == NULL, "list's head should be NULL for empty list");
	cr_expect(dlist_tail(&list) == NULL, "list's tail should be NULL for empty list");
	cr_expect(removed == item3, "removed item should point to the third item inserted");
}

Test(list_tests, remove_at_tail)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;

	// Pointer to removed item
	void* removed;

	// List starts empty
	cr_expect(dlist_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	//    h t
	//    [1]->0
	// 0<-[ ]

	cr_expect(dlist_insert_next(&list, dlist_tail(&list), item2) == 0, "insert after tail should return 0");
	cr_expect(dlist_size(&list) == 2, "list's size should be 2");
	//    h    t
	//    [1]->[2]->0
	// 0<-[ ]<-[ ]

	cr_expect(dlist_insert_next(&list, dlist_tail(&list), item3) == 0, "insert after tail should return 0");
	cr_expect(dlist_size(&list) == 3, "list's size should be 3");
	//    h         t
	//    [1]->[2]->[3]->0
	// 0<-[ ]<-[ ]<-[ ]

	cr_expect(dlist_remove(&list, dlist_tail(&list), &removed) == 0, "remove at head should return 0");
	cr_expect(dlist_size(&list) == 2, "list's size should be 2");
	//    h    t
	//    [1]->[2]->0
	// 0<-[ ]<-[ ]

	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(dlist_data(dlist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item2, "tail should be the second item inserted");
	cr_expect(removed == item3, "removed item should point to the third item inserted");

	cr_expect(dlist_remove(&list, dlist_tail(&list), &removed) == 0, "remove at head should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	//    h t
	//    [1]->0
	// 0<-[ ]

	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(dlist_data(dlist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item1, "tail should be the first item inserted");
	cr_expect(removed == item2, "removed item should point to the second item inserted");

	cr_expect(dlist_remove(&list, dlist_tail(&list), &removed) == 0, "remove at head should return 0");
	cr_expect(dlist_size(&list) == 0, "list's size should be 0");
	// List is empty, removed=[1]

	cr_expect(dlist_head(&list) == NULL, "list's head should be NULL for empty list");
	cr_expect(dlist_tail(&list) == NULL, "list's tail should be NULL for empty list");
	cr_expect(removed == item1, "removed item should point to the first item inserted");
}

Test(list_tests, remove_in_middle)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;

	// Pointer to removed item
	void* removed;

	// List starts empty
	cr_expect(dlist_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(dlist_size(&list) == 1, "list's size should be 1");
	//    h t
	//    [1]->0
	// 0<-[ ]

	cr_expect(dlist_insert_next(&list, dlist_tail(&list), item2) == 0, "insert after tail should return 0");
	cr_expect(dlist_size(&list) == 2, "list's size should be 2");
	//    h    t
	//    [1]->[2]->0
	// 0<-[ ]<-[ ]

	cr_expect(dlist_insert_next(&list, dlist_tail(&list), item3) == 0, "insert after tail should return 0");
	cr_expect(dlist_size(&list) == 3, "list's size should be 3");
	//    h         t
	//    [1]->[2]->[3]->0
	// 0<-[ ]<-[ ]<-[ ]

	// Point to middle element
	DList_Element *element = dlist_next(dlist_head(&list));

	cr_expect(dlist_remove(&list, element, &removed) == 0, "remove at middle element should return 0");
	cr_expect(dlist_size(&list) == 2, "list's size should be 2");
	//    h    t
	//    [1]->[3]->0
	// 0<-[ ]<-[ ]

	cr_expect(dlist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(dlist_tail(&list) != NULL, "list's tail should be not NULL");
	cr_expect(dlist_data(dlist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(dlist_data(dlist_tail(&list)) == item3, "tail should be the third item inserted");
	cr_expect(removed == item2, "removed item should point to the second item inserted");
}