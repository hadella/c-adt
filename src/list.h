/**
 * \file list.h
 * \author Justin Hadella (justin.hadella@gmail.com)
 * \brief Definitions of a generic linked-list ADT
 * \version 0.1
 * \date 2023-05-09
 * \note Code based on content from "Mastering Algorithms with C" (O'Reilly 1999)
 */

#ifndef LIST_h
#define LIST_h

#ifdef __cplusplus
extern "C"
{
#endif

// -------------------------------------------------------------------------------------------------
// Definitions
// -------------------------------------------------------------------------------------------------

/**
 * \struct List_Element
 * \brief Generic linked-list element
 */
typedef struct List_Element_s {
	void *data;                  ///< Pointer to data
	struct List_Element_s *next; ///< Pointer to next element in list

} List_Element;

/**
 * \struct List
 * \brief Generic linked-list
 */
typedef struct List_s {
	int size; ///< Number of elements in list

	// int (*match)(const void *a, const void *b);

	void (*destroy)(void *data); ///< Function pointer to destroy element

	List_Element *head; ///< Pointer to first element in list
	List_Element *tail; ///< Pointer to last element in list

} List;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// List Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
 * \brief Function to initialize a linked-list
 * 
 * \pre Must be called before the list can be used by any other operation
 * 
 * The `destroy` argument provides a way to free dynamically allocated data when *list_destroy*
 * is called. 
 * 
 * For example, if the list contains data dynamically allocated using *malloc*, `destroy` 
 * should be set to *free* to free the data as the linked-list is destroyed. For a linked-list
 * containing data that should not be freed, `destroy` should be set to NULL.
 * 
 * Complexity: O(1)
 * 
 * \param list    The linked-list to init
 * \param destroy Function pointer to free data element memory
 */
void 
list_init(List *list, void (*destroy)(void *data));

/**
 * \brief Function to destroy a linked-list
 * 
 * The *list_destroy* operation removes all elements from a linked-list and calls the function 
 * passed as `destroy` to *list_init* once for each element as it is removed, provided `destroy`
 * was not set to NULL.
 * 
 * \note
 * No operation is permitted after *list_destroy* is called unless *list_init* is called again.
 *  
 * Complexity: O(n)
 * 
 * \param list The linked-list to destroy
 */
void
list_destroy(List *list);

/**
 * \brief Function to insert an element into a linked-list
 * 
 * Inserts an element just after `element` into the linked-list. If `element` is NULL, the new
 * element is inserted at the head of the list. The new element contains a pointer to `data`, 
 * so the memory referenced by `data` should remain valid as long as the element remains in the
 * list.
 * 
 * Complexity: O(1)
 * 
 * \param list    The linked-list to insert element into
 * \param element Pointer to element to insert after
 * \param data    The data to insert
 * 
 * \return 0 if inserting into list was successful, otherwise -1
 */
int
list_insert_next(List *list, List_Element *element, const void *data);

/**
 * \brief Function to remove an element from a linked list
 * 
 * Removes the element just past `element` from the linked-list. If `element` is NULL, the 
 * element at the head of the list is removed. Upon return `data` points to the data stored
 * in the element that was removed.
 * 
 * Complexity: O(1)
 * 
 * \param list    The linked-list to remove element from
 * \param element Pointer to element to remove after
 * \param data    The data removed
 * 
 * \return 0 if inserting into list was successful, otherwise -1
 */
int
list_remove_next(List *list, List_Element *element, void **data);

/**
 * MACRO that evaluates to the number of elements in the linked-list
 */
#define list_size(list) ((list)->size)

/**
 * MACRO that evaluates to the element at the head of a linked-list
 */
#define list_head(list) ((list)->head)

/**
 * MACRO that evaluates to the element at the tail of a linked-list
 */
#define list_tail(list) ((list)->tail)

/**
 * MACRO that determines whether element is the head of linked-list
 */
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

/**
 * MACRO that determines whether element is the tail of linked-list
 */
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)

/**
 * MACRO that evaluates to the data stored in given element of a linked-list
 */
#define list_data(element) ((element)->data)

/**
 * MACRO that evaluates to the next element given an element in a linked-list
 */
#define list_next(element) ((element)->next)

#ifdef __cplusplus
}
#endif
#endif // LIST_h