/**
 * \file queue_test.c
 * \author Justin Hadella (justin.hadella@gmail.com)
 * \brief Unit test for Queue ADT
 * 
 * \note
 * The Queue ADT is implemented using the List ADT.
 */
#include <criterion/criterion.h>

#include <stdio.h>
#include <stdlib.h> // free()

#include "../src/queue.h"

Queue queue;

int *item1 = NULL;
int *item2 = NULL;
int *item3 = NULL;

void
suite_setup()
{
	item1 = (int*)malloc(sizeof (int));
	item2 = (int*)malloc(sizeof (int));
	item3 = (int*)malloc(sizeof (int));

	queue_init(&queue, free);
}

void
suite_teardown()
{
	queue_destroy(&queue);
}

TestSuite(queue_tests, .init=suite_setup, .fini=suite_teardown);

Test(queue_tests, queue_enqueue_peek_dequeue)
{
	// Give out items some values
	*item1 = 1;
	*item2 = 2;
	*item3 = 3;

	cr_expect(queue_size(&queue) == 0, "empty queues's size should be 0");

	void *peek_item;

	// A queue is basically the same as a linked-list except the items will be ordered
	// in a specific way. The queue is a FIFO data structure, where the first item 
	// queued will be the first item removed. Our unit test can be simplified since we
	// just need to test the item ordering.

	cr_expect(queue_enqueue(&queue, item1) == 0, "enqueueing onto empty queue should return 0");
	cr_expect(queue_size(&queue) == 1, "queue with one enqueue should have size of 1");

	peek_item = queue_peek(&queue);
	cr_expect(item1 == peek_item, "front of queue should be first item enqueued");

	cr_expect(queue_enqueue(&queue, item2) == 0, "enqueueing onto queue should return 0");
	cr_expect(queue_size(&queue) == 2, "queue with two enqueues should have size of 2");

	cr_expect(queue_enqueue(&queue, item3) == 0, "enqueueing onto queue should return 0");
	cr_expect(queue_size(&queue) == 3, "queue with three enqueues should have size of 3");

	// Since the queue is a FIFO the data removed with match the order of entry

	void *removed;

	// The first item will be at the front still
	peek_item = queue_peek(&queue);
	cr_expect(item1 == peek_item, "front of queue should be first item enqueueed");

	cr_expect(queue_dequeue(&queue, &removed) == 0, "dequeue queue with three items should return 0");
	cr_expect(queue_size(&queue) == 2, "queue should have a size of 2");
	cr_expect(item1 == removed, "dequeueped item should be first item enqueueed");

	peek_item = queue_peek(&queue);
	cr_expect(item2 == peek_item, "front of queue should be second item enqueued");

	cr_expect(queue_dequeue(&queue, &removed) == 0, "dequeue queue with two items should return 0");
	cr_expect(queue_size(&queue) == 1, "queue should have a size of 1");
	cr_expect(item2 == removed, "dequeued item should be second item enqueueed");

	peek_item = queue_peek(&queue);
	cr_expect(item3 == peek_item, "front of queue should be third item enqueued");

	cr_expect(queue_dequeue(&queue, &removed) == 0, "dequeue queue with one item should return 0");
	cr_expect(queue_size(&queue) == 0, "queue should have a size of 0");
	cr_expect(item3 == removed, "dequeued item should be third item enqueueed");
}

