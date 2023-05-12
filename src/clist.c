/**
 * \file clist.c
 * \author Justin Hadella (justin.hadella@gmail.com)
 * \brief Implementation of a generic circular linked-list ADT
 * \version 0.1
 * \date 2023-05-12
 */
#include <stdlib.h>
#include <string.h>

#include "clist.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// List Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void
clist_init(CList *list, void (*destroy)(void *data))
{
	// Initialize the list
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
}

void
clist_destroy(CList *list)
{
	void *data;

	// Remove each element in list
	while (clist_size(list) > 0) {
		if (clist_remove_next(list, list->head, (void**)&data) == 0 && list->destroy != NULL) {
			list->destroy(data);
		}
	}

	// No operations permitted at this point -- clear memory as precaution
	memset(list, 0, sizeof (CList));
}

int
clist_insert_next(CList *list, CList_Element *element, const void *data)
{
	CList_Element *new_element;

	// Allocate storage for the element
	if ((new_element = (CList_Element*)malloc(sizeof (CList_Element))) == NULL) {
		return -1;
	}

	// Insert the element into the linked-list
	new_element->data = (void *)data;

	if (clist_size(list) == 0) {
		// Insert into empty list

		new_element->next = new_element;
		list->head = new_element;
	} else {
		// Insert into a non-empty list

		new_element->next = element->next;
		element->next = new_element;
	}

	// Adjust the size
	list->size++;

	return 0;
}

int
clist_remove_next(CList *list, CList_Element *element, void **data)
{
	CList_Element *old_element;

	// Check for empty list!
	if (clist_size(list) == 0) {
		return -1;
	}

	*data = element->next->data;

	if (element->next == element) {
		// Remove the last element

		old_element = element->next;
		list->head = NULL;
	} else {
		// Remove an element other than the last element

		old_element = element->next;
		element->next = element->next->next;

		if (old_element == clist_head(list)) {
			list->head = old_element->next;
		}
	}

	// Free storage allocated by the abstract datatype
	free(old_element);

	// Adjust the size of the list
	list->size--;

	return 0;
}