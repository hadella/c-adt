/**
 * \file stack.c
 * \author Justin Hadella (justin.hadella@gmail.com)
 * \brief Implementation of a generic stack ADT
 * \version 0.1
 * \date 2023-05-12
 */
#include "stack.h"

#include <stdio.h> // for NULL

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Stack Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int
stack_push(Stack *stack, const void *data)
{
	return list_insert_next(stack, NULL, data);
}

int
stack_pop(Stack *stack, void **data)
{
	return list_remove_next(stack, NULL, data);
}
