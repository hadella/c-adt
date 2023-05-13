#include <criterion/criterion.h>

#include <stdio.h>
#include <stdlib.h> // free()

#include "../src/clist.h"

CList list;

int *item1 = NULL;
int *item2 = NULL;
int *item3 = NULL;
int *item4 = NULL;

// static void print_clist(const CList *list)
// {
// 	CList_Element *element;
// 	int *data;
// 	int size;
// 	int i;

// 	fprintf(stdout, "List size is %d (circling twice)\n", clist_size(list));

// 	size = clist_size(list);
// 	element = clist_head(list);

// 	i = 0;
// 	while (i < size * 2) {
// 		data = clist_data(element);
// 		fprintf(stdout, "list[%d]=%d\n", (i % size), *data);
// 		element = clist_next(element);
// 		i++;
// 	}
// }

void suite_setup()
{
	item1 = (int*)malloc(sizeof (int));
	item2 = (int*)malloc(sizeof (int));
	item3 = (int*)malloc(sizeof (int));
	item4 = (int*)malloc(sizeof (int));

	clist_init(&list, free);
}

void suite_teardown()
{
	clist_destroy(&list);
}

TestSuite(list_tests, .init=suite_setup, .fini=suite_teardown);

Test(list_tests, empty)
{
	cr_expect(clist_size(&list) == 0, "empty dlist's size should be 0");
	cr_expect(clist_head(&list) == NULL, "empty dlist's head should be NULL");
}

Test(list_tests, delete_empty)
{
	void *removed = NULL;
	cr_expect(clist_remove_next(&list, clist_head(&list), &removed) == -1, "remove from empty list should return -1");
	cr_expect(clist_remove_next(&list, NULL, &removed) == -1, "remove from empty list should return -1");
}

Test(list_tests, insert_into_empty)
{
	// Give our item a value
	*item1 = 1;

	// List starts empty
	cr_expect(clist_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	//    h
	// ->[1]->
	// |______|

	cr_expect(clist_size(&list) == 1, "list's size should be 1");
	cr_expect(clist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(clist_data(clist_head(&list)) == item1, "head should be the item inserted");
}

Test(list_tests, insert_after_head)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;
	*item4 = 4;

	// List starts empty
	cr_expect(clist_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	//    h
	// ->[1]->
	// |______|

	cr_expect(clist_size(&list) == 1, "list's size should be 1");
	cr_expect(clist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(clist_data(clist_head(&list)) == item1, "head should be the item inserted");

	cr_expect(clist_insert_next(&list, clist_head(&list), item2) == 0, "insert into empty list should return 0");
	//    h
	// ->[1]->[2]->
	// |___________|

	cr_expect(clist_size(&list) == 2, "list's size should be 1");
	cr_expect(clist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(clist_data(clist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(clist_data(clist_next(clist_head(&list))) == item2, "head should be the second item inserted");

	cr_expect(clist_insert_next(&list, clist_head(&list), item3) == 0, "insert into empty list should return 0");
	//    h
	// ->[1]->[3]->[2]->
	// |________________|

	cr_expect(clist_size(&list) == 3, "list's size should be 1");
	cr_expect(clist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(clist_data(clist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(clist_data(clist_next(clist_head(&list))) == item3, "head should be the third item inserted");

	cr_expect(clist_insert_next(&list, clist_head(&list), item4) == 0, "insert into empty list should return 0");
	//    h
	// ->[1]->[4]->[3]->[2]->
	// |_____________________|

	cr_expect(clist_size(&list) == 4, "list's size should be 1");
	cr_expect(clist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(clist_data(clist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(clist_data(clist_next(clist_head(&list))) == item4, "head should be the fourth item inserted");

	// See a pattern?
}

Test(list_tests, insert_in_order)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;
	*item4 = 4;

	// List starts empty
	CList_Element *element = NULL;
	cr_expect(clist_insert_next(&list, element, item1) == 0, "insert into empty list should return 0");
	//    h
	// ->[1]->
	// |______|

	cr_expect(clist_size(&list) == 1, "list's size should be 1");
	cr_expect(clist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(clist_data(clist_head(&list)) == item1, "head should be the item inserted");

	element = clist_head(&list);
	cr_expect(clist_insert_next(&list, element, item2) == 0, "insert into empty list should return 0");
	//    h
	// ->[1]->[2]->
	// |___________|

	cr_expect(clist_size(&list) == 2, "list's size should be 1");
	cr_expect(clist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(clist_data(clist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(clist_data(clist_next(clist_head(&list))) == item2, "head should be the second item inserted");

	element = clist_next(clist_head(&list));
	cr_expect(clist_insert_next(&list, element, item3) == 0, "insert into empty list should return 0");
	//    h
	// ->[1]->[2]->[3]->
	// |________________|

	cr_expect(clist_size(&list) == 3, "list's size should be 1");
	cr_expect(clist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(clist_data(clist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(clist_data(clist_next(clist_head(&list))) == item2, "head should be the second item inserted");
	cr_expect(clist_data(clist_next(clist_next(clist_head(&list)))) == item3, "head should be the third item inserted");

	element = clist_next(clist_next(clist_head(&list)));
	cr_expect(clist_insert_next(&list, element, item4) == 0, "insert into empty list should return 0");
	//    h
	// ->[1]->[2]->[3]->[4]->
	// |_____________________|

	cr_expect(clist_size(&list) == 4, "list's size should be 1");
	cr_expect(clist_head(&list) != NULL, "list's head should be not NULL");
	cr_expect(clist_data(clist_head(&list)) == item1, "head should be the first item inserted");
	cr_expect(clist_data(clist_next(clist_head(&list))) == item2, "head should be the second item inserted");
	cr_expect(clist_data(clist_next(clist_next(clist_head(&list)))) == item3, "head should be the third item inserted");
	cr_expect(clist_data(clist_next(clist_next(clist_next(clist_head(&list))))) == item4, "head should be the fourth item inserted");
	
	// See a pattern?
}

Test(list_tests, remove_at_head)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;
	*item4 = 4;

	// Pointer to removed item
	void* removed;

	// List starts empty
	cr_expect(clist_insert_next(&list, NULL, item1) == 0, "insert into empty list should return 0");
	cr_expect(clist_size(&list) == 1, "list's size should be 1");
	//    h
	// ->[1]->
	// |______|

	cr_expect(clist_insert_next(&list, clist_head(&list), item2) == 0, "insert into empty list should return 0");
	cr_expect(clist_size(&list) == 2, "list's size should be 2");
	//    h
	// ->[1]->[2]->
	// |___________|

	cr_expect(clist_insert_next(&list, clist_head(&list), item3) == 0, "insert into empty list should return 0");
	cr_expect(clist_size(&list) == 3, "list's size should be 3");
	//    h
	// ->[1]->[3]->[2]->
	// |________________|

	cr_expect(clist_insert_next(&list, clist_head(&list), item4) == 0, "insert into empty list should return 0");
	cr_expect(clist_size(&list) == 4, "list's size should be 4");
	//    h
	// ->[1]->[4]->[3]->[2]->
	// |_____________________|

	cr_expect(clist_remove_next(&list, clist_head(&list), &removed) == 0, "remove after head of list should return 0");
	//    h
	// ->[1]->[3]->[2]->
	// |________________|

	cr_expect(clist_size(&list) == 3, "list's size should be 3");
	cr_expect(removed == item4, "removed item should point to the fourth item inserted");

	cr_expect(clist_remove_next(&list, clist_head(&list), &removed) == 0, "remove after head of list should return 0");
	//    h
	// ->[1]->[2]->
	// |___________|

	cr_expect(clist_size(&list) == 2, "list's size should be 2");
	cr_expect(removed == item3, "removed item should point to the third item inserted");

	cr_expect(clist_remove_next(&list, clist_head(&list), &removed) == 0, "remove after head of list should return 0");
	//    h
	// ->[1]->
	// |______|

	cr_expect(clist_size(&list) == 1, "list's size should be 1");
	cr_expect(removed == item2, "removed item should point to the second item inserted");

	cr_expect(clist_remove_next(&list, clist_head(&list), &removed) == 0, "remove after head of list should return 0");
	// List is empty

	cr_expect(clist_size(&list) == 0, "list's size should be 0");
	cr_expect(removed == item1, "removed item should point to the first item inserted");
	cr_expect(clist_head(&list) == NULL, "empty dlist's head should be NULL");
}
