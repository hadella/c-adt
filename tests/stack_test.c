/**
 * \file stack_test.c
 * \author Justin Hadella (justin.hadella@gmail.com)
 * \brief Unit test for Stack ADT
 * 
 * \note
 * The Stack ADT is implemented using the List ADT.
 */
#include <criterion/criterion.h>

#include <stdio.h>
#include <stdlib.h> // free()

#include "../src/stack.h"

Stack stack;

int *item1 = NULL;
int *item2 = NULL;
int *item3 = NULL;

void
suite_setup()
{
	item1 = (int*)malloc(sizeof (int));
	item2 = (int*)malloc(sizeof (int));
	item3 = (int*)malloc(sizeof (int));

	stack_init(&stack, free);
}

void
suite_teardown()
{
	stack_destroy(&stack);
}

TestSuite(stack_tests, .init=suite_setup, .fini=suite_teardown);

Test(stack_tests, stack_push_peek_pop)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;

	cr_expect(stack_size(&stack) == 0, "empty stacks's size should be 0");

	void *peek_item;

	// A stack is basically the same as a linked-list except the items will be ordered
	// in a specific way. The stack is a LIFO data structure, where the last item pushed
	// onto the stack will be the first item removed. Our unit test can be simplified
	// since we just need to test the item ordering.

	cr_expect(stack_push(&stack, item1) == 0, "pushing onto empty stack should return 0");
	cr_expect(stack_size(&stack) == 1, "stack with one push should have size of 1");

	peek_item = stack_peek(&stack);
	cr_expect(item1 == peek_item, "top of stack should be last item pushed");

	cr_expect(stack_push(&stack, item2) == 0, "pushing onto stack should return 0");
	cr_expect(stack_size(&stack) == 2, "stack with two pushes should have size of 2");

	peek_item = stack_peek(&stack);
	cr_expect(item2 == peek_item, "top of stack should be last item pushed");

	cr_expect(stack_push(&stack, item3) == 0, "pushing onto stack should return 0");
	cr_expect(stack_size(&stack) == 3, "stack with three pushes should have size of 3");

	peek_item = stack_peek(&stack);
	cr_expect(item3 == peek_item, "top of stack should be last item pushed");

	// Now let's start to pop the stack. We should see reverse order

	void *removed;

	cr_expect(stack_pop(&stack, &removed) == 0, "pop stack with three items should return 0");
	cr_expect(stack_size(&stack) == 2, "stack should have a size of 2");
	cr_expect(item3 == removed, "popped item should be last item pushed");

	cr_expect(stack_pop(&stack, &removed) == 0, "pop stack with two items should return 0");
	cr_expect(stack_size(&stack) == 1, "stack should have a size of 1");
	cr_expect(item2 == removed, "popped item should be second item pushed");

	cr_expect(stack_pop(&stack, &removed) == 0, "pop stack with one item should return 0");
	cr_expect(stack_size(&stack) == 0, "stack should have a size of 0");
	cr_expect(item1 == removed, "popped item should be first item pushed");
}
