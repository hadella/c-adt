/**
 * \file clist.h
 * \author Justin Hadella (justin.hadella@gmail.com)
 * \brief Definitions of a generic circular linked-list ADT
 * \version 0.1
 * \date 2023-05-12
 * \note Code based on content from "Mastering Algorithms with C" (O'Reilly 1999)
 */
#ifndef CLIST_h
#define CLIST_h

#ifdef __cplusplus
extern "C"
{
#endif

// -------------------------------------------------------------------------------------------------
// Definitions
// -------------------------------------------------------------------------------------------------

/**
 * \struct CList_Element
 * \brief Generic circular linked-list element
 */
typedef struct CList_Element_s {
	void *data;                   ///< Pointer to data
	struct CList_Element_s *next; ///< Pointer to next element in list

} CList_Element;

/**
 * \struct CList
 * \brief Generic circular linked-list
 */
typedef struct CList_s {
	int size; ///< Number of elements in list

	int (*match)(const void *a, const void *b);
	void (*destroy)(void *data);

	CList_Element *head; ///< Pointer to first element in list

} CList;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// List Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
 * \brief Function to initialize a circular linked-list
 * 
 * \pre Must be called before list can be used by any other operation
 * 
 * The `destroy` argument provides a way to free dynamically allocated data when *list_destroy*
 * is called. For example, if the list contains data dynamically allocated using *malloc*, 
 * `destroy` should be set to *free* to free the data as the linked-list is destroyed. For a
 * circular linked-list containing data that should not be freed, `destroy` should be set to NULL.
 * 
 * Complexity: O(1)
 * 
 * \param list    The circular linked-list to init
 * \param destroy Function pointer to free data element memory
 */
void
clist_init(CList *list, void (*destroy)(void *data));

/**
 * \brief Function to destroy a circular linked-list
 * 
 * The *list_destroy* operation removes all elements from a circular linked-list and calls the
 * function passed as `destroy` to *clist_init* once for each element as it is removed, provided
 * `destroy` was not set to NULL.
 * 
 * \note
 * No operation is permitted after *clist_destroy* is called unless *clist_init* is called again.
 * 
 * Complexity: O(n)
 * 
 * \param list The circular linked-list to destroy
 */
void
clist_destroy(CList *list);

/**
 * \brief Function to insert an element into a circular linked-list
 * 
 * Inserts an element just after `element` into the circular linked-list. When inserting into
 * an empty list, `element` should be NULL, and the new element is inserted at the head of the
 *  list. The new element contains a pointer to `data`, so the memory referenced by `data` 
 * should remain valid as long as the element remains in the list.
 * 
 * Complexity: O(1)
 * 
 * \param list    The circular linked-list to insert element into
 * \param element Pointer to element to insert after
 * \param data    The data to insert
 * 
 * \return 0 if inserting into list was successful, otherwise -1
 */
int
clist_insert_next(CList *list, CList_Element *element, const void *data);

/**
 * \brief Function to remove an element from a circular linked list
 * 
 * Removes the element just past `element` from the circular linked-list. Upon return `data`
 * points to the data stored in the element that was removed.
 * 
 * Complexity: O(1)
 * 
 * \param list    The circular linked-list to remove lelement from
 * \param element Pointer to element to remove after
 * \param data    The data removed
 * 
 * \return 0 if inserting into list was successful, otherwise -1
 */
int
clist_remove_next(CList *list, CList_Element *element, void **data);

/**
 * MACRO that evaluates to the number of elements in the circular linked-list
 */
#define clist_size(list) ((list)->size)

/**
 * MACRO that evaluates to the element at the head of a circular linked-list
 */
#define clist_head(list) ((list)->head)

/**
 * MACRO that evaluates to the data stored in given element of a circular linked-list
 */
#define clist_data(element) ((element)->data)

/**
 * MACRO that evaluates to the next element given an element in a circular linked-list
 */
#define clist_next(element) ((element)->next)

#ifdef __cplusplus
}
#endif
#endif // CLIST_h