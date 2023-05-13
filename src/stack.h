/**
 * \file stack.h
 * \author Justin Hadella (justin.hadella@gmail.com)
 * \brief Definitions of a generic stack ADT
 * \version 0.1
 * \date 2023-05-12
 * \note Code based on content from "Mastering Algorithms with C" (O'Reilly 1999)
 */
#ifndef STACK_h
#define STACK_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "list.h"

// -------------------------------------------------------------------------------------------------
// Definitions
// -------------------------------------------------------------------------------------------------

typedef List Stack;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Stack Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
 * MACRO to init the stack. Functionally same as *list_init*
 */
#define stack_init list_init

/**
 * MACRO to destroy the stack. Functionally same as *list_destroy*
 */
#define stack_destroy list_destroy

/**
 * \brief Function to push an element to the top of the stack
 * 
 * \note
 * @note
 * The stack is implemented internally as a linked-list, so a push is equivalent to
 * *list_insert_next* where the element is added to the head of the list.

 * \param stack The stack to push element onto
 * \param data  The data to push
 * 
 * \return 0 if stack push was successful, otherwise -1
 */
int
stack_push(Stack *stack, const void *data);

/**
 * \brief Function to pop an element off the top of the stack
 * 
 * \note
 * The stack is implemented internally as a linked-list, so a pop is equivalent to
 * *list_remove_next* where the element is removed from the head of the list.

 * \param stack The stack to pop the element from
 * \param data  The data popped off the stack
 * 
 * \return 0 if stack pop was successful, otherwise -1
 */
int
stack_pop(Stack *stack, void **data);

/**
 * MACRO that provides mechanism to inspect the element at top of stack
 */
#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)

/**
 * MACRO that evaluates to the number of elements in the stack
 */
#define stack_size list_size

#ifdef __cplusplus
}
#endif
#endif // STACK_h