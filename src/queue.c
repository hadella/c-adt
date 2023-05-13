/**
 * \file queue.c
 * \author Justin Hadella (justin.hadella@gmail.com)
 * \brief Implementation of a generic queue ADT
 * \version 0.1
 * \date 2023-05-12
 */
#include "queue.h"

#include <stdio.h> // for NULL

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Queue Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int
queue_enqueue(Queue *queue, const void *data)
{
	return list_insert_next(queue, list_tail(queue), data);
}

int
queue_dequeue(Queue *queue, void **data)
{
	return list_remove_next(queue, NULL, data);
}
