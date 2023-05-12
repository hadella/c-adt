/**
 * \file dlist.c
 * \author Justin Hadella (justin.hadella@gmail.com)
 * \brief Implementation of a generic doubly linked-list ADT
 * \version 0.1
 * \date 2023-05-11
 */
#include <stdlib.h>
#include <string.h>

#include "dlist.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// List Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void
dlist_init(DList *list, void (*destroy)(void *data))
{
	// Initialize the list
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

void
dlist_destroy(DList *list)
{
	void *data;

	// Remove each element in list
	while (dlist_size(list) > 0) {
		if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 &&
		    list->destroy != NULL) {
			list->destroy(data);
		}
	}

	// No operations permitted a this point but clear memory as precaution
	memset(list, 0, sizeof(DList));
}

int
dlist_insert_next(DList *list, DList_Element *element, const void *data)
{
	DList_Element *new_element;

	// Do not allow a NULL element unless the list is empty
	if (element == NULL && dlist_size(list) != 0) {
		return -1;
	}

	// Allocate storage for the element
	if ((new_element = (DList_Element *)malloc(sizeof(DList_Element))) ==
	    NULL) {
		return -1;
	}

	// Insert the element into the linked-list
	new_element->data = (void *)data;

	if (dlist_size(list) == 0) {
		// Insert into empty list

		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	} else {
		// Insert into non-empty list

		new_element->next = element->next;
		new_element->prev = element;

		if (element->next == NULL) {
			list->tail = new_element;
		} else {
			element->next->prev = new_element;
		}

		element->next = new_element;
	}

	// Adjust the size
	list->size++;

	return 0;
}

int
dlist_insert_prev(DList *list, DList_Element *element, const void *data)
{
	DList_Element *new_element;

	// Do not allow a NULL element unless the list is empty
	if (element == NULL && dlist_size(list) != 0) {
		return -1;
	}

	// Allocate storage for the element
	if ((new_element = (DList_Element *)malloc(sizeof(DList_Element))) ==
	    NULL) {
		return -1;
	}

	// Insert the element into the linked-list
	new_element->data = (void *)data;

	if (dlist_size(list) == 0) {
		// Insert into empty list

		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	} else {
		// Insert into non-empty list

		new_element->next = element;
		new_element->prev = element->prev;

		if (element->prev == NULL) {
			list->head = new_element;
		} else {
			element->prev->next = new_element;
		}

		element->prev = new_element;
	}

	// Adjust the size
	list->size++;

	return 0;
}

int
dlist_remove(DList *list, DList_Element *element, void **data)
{
	// Do not allow a NULL element or removal from empty list
	if (element == NULL || dlist_size(list) == 0) {
		return -1;
	}

	// Remove the element from the linked-list

	*data = element->data;

	if (element == list->head) {
		// Remove from the head of the list

		list->head = element->next;

		if (list->head == NULL) {
			list->tail = NULL;
		} else {
			element->next->prev = NULL;
		}
	} else {
		// Remove from somewhere but the head

		element->prev->next = element->next;

		if (element->next == NULL) {
			list->tail = element->prev;
		} else {
			element->next->prev = element->prev;
		}
	}

	// Free storage allocated by the abstract datatype
	free(element);

	// Adjust the size of the list
	list->size--;

	return 0;
}