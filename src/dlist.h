/**
 * \file dlist.h
 * \author Justin Hadella (justin.hadella@gmail.com)
 * \brief Definitions of a generic doubly linked-list ADT
 * \version 0.1
 * \date 2023-05-11
 * \note Code based on content from "Mastering Algorithms with C" (O'Reilly 1999)
 */
#ifndef DLIST_h
#define DLIST_h

#ifdef __cplusplus
extern "C"
{
#endif

// -------------------------------------------------------------------------------------------------
// Definitions
// -------------------------------------------------------------------------------------------------

/**
 * \struct DList_Element_s
 * \brief Generic doubly linked-list element
 */
typedef struct DList_Element_s {
	void *data;                   ///< Pointer to data

	struct DList_Element_s *prev; ///< Pointer to prev element in list
	struct DList_Element_s *next; ///< Pointer to next element in list

} DList_Element;

/**
 * \struct DList
 * \brief Generic doubly linked-list
 */
typedef struct DList_s {
	int size; ///< Number of elements in list

	// int (*match)(const void *a, const void *b);

	void (*destroy)(void *data);

	DList_Element *head; ///< Pointer to first element in list
	DList_Element *tail; ///< Pointer to last element in list

} DList;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// List Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
 * \brief Function to initialize a doubly linked-list
 * 
 * \pre Must be called before list can be used by any other operation
 * 
 * The `destroy` argument provides a way to free dynamically allocated data when *dlist_destroy*
 * is called. For example, if the list contains data dynamically allocated using *malloc*, 
 * `destroy` should be set to *free* to free the data as the doubly linked-list is destroyed.
 * For a doubly linked-list containing data that should not be freed, `destroy` should be set to
 * NULL.
 * 
 * Complexity: O(1)
 * 
 * \param list    The doubly linked-list to init
 * \param destroy Function pointer to free data element memory
 */
void 
dlist_init(DList *list, void (*destroy)(void *data));

/**
 * \brief Function to destroy a doubly linked-list
 * 
 * The *dlist_destroy*` operation removes all elements from a doubly linked-list and calls the
 * function passed as `destroy` to *dlist_init* once for each element as it is removed, provided
 * `destroy` was not set to NULL.
 * 
 * \note
 * No operation is permitted after *dlist_destroy* is called unless *dlist_init* is called again.
 * 
 * Complexity: O(n)
 * 
 * \param list The doubly linked-list to destroy
 */
void
dlist_destroy(DList *list);

/**
 * \brief Function to insert an element into a doubly linked-list
 * 
 * Inserts an element just after `element` into the doubly linked-list. When inserting into an
 * empty list, `element` should point to NULL. The new element contains a pointer to `data`, so
 * the memory referenced by `data` should remain valid as long as the element remains in the list.
 * 
 * Complexity: O(1)
 * 
 * \param list    The doubly linked-list to insert element into
 * \param element Pointer to element to insert after
 * \param data    The data to insert
 * 
 * \return 0 if inserting into list was successful, otherwise -1
 */
int
dlist_insert_next(DList *list, DList_Element *element, const void *data);

/**
 * \brief Function to insert an element into a doubly linked-list
 * 
 * Inserts an element just before `element` into the doubly linked-list. When inserting into
 * an empty list, `element` should point to NULL. The new element contains a pointer to `data`,
 * so the memory referenced by `data` should remain valid as long as the element remains in the
 * list.
 * 
 * Complexity: O(1)
 * 
 * \param list    The doubly linked-list to insert element into
 * \param element Pointer to element to insert before
 * \param data    The data to insert
 * 
 * \return 0 if inserting into list was successful, otherwise -1
 */
int
dlist_insert_prev(DList *list, DList_Element *element, const void *data);

/**
 * \brief Function to remove an element from a doubly linked-list
 * 
 * Removes the element specified as `element` from the doubly linked-list. Upon return `data`
 * points to the data stored in the element that was removed.
 * 
 * Complexity: O(1)
 * 
 * \param list    The doubly linked-list to remove element from
 * \param element Pointer to element to remove
 * \param data    Pointer to data removed
 * 
 * \return 0 if inserting into list was successful, otherwise -1
 */
int
dlist_remove(DList *list, DList_Element *element, void **data);

/**
 * MACRO that evaluates to the number of elements in the doubly linked-list
 */
#define dlist_size(list) ((list)->size)

/**
 * MACRO that evaluates to the element at the head of a doubly linked-list
 */
#define dlist_head(list) ((list)->head)

/**
 * MACRO that evaluates to the element at the tail of a doubly linked-list
 */
#define dlist_tail(list) ((list)->tail)

/**
 * MACRO that determines whether element is the head of doubly linked-list
 */
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)

/**
 * MACRO that determines whether element is the tail of doubly linked-list
 */
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)

/**
 * MACRO that evaluates to the data stored in given element of a doubly linked-list
 */
#define dlist_data(element) ((element)->data)

/**
 * MACRO that evaluates to the next element given an element in a doubly linked-list
 */
#define dlist_next(element) ((element)->next)

/**
 * MACRO that evaluates to the prev element given an element in a doubly linked-list
 */
#define dlist_prev(element) ((element)->prev)

#ifdef __cplusplus
}
#endif
#endif // DLIST_h