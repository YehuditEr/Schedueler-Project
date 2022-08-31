#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

struct Queue {
    size_t capacity;    //capacity - size of array
    size_t size;        //size - number of elements in array
    void** data;        //data - array of elements
    size_t head, tail;  //pointer to head and tail of elements in array

    /*
      The queue is constructed using a pointer to the data and two integers representing
      the head and tail of the queue.

      head, tail
      |
      v
      [ ][ ][ ][ ]

      When an item is enqueued, we place it at the tail of the list and increment the tail.

      head
      |  tail
      v  v
      [a][ ][ ][ ]

      The tail is guaranteed to always point to an empty slot (if it can't point to an empty
      slot, the underlying array is resized).

      head            head
      |               |           tail
      v               v           v
      [a][b][c][d] => [a][b][c][d][ ][ ][ ][ ]

      If the tail has reached the end of the underlying array (and there is still room), it
      wraps around.

      tail
      |  head
      v  v
      [ ][b][c][d]

      When an object is dequeued we return the item pointed to by head and increment head. If
      the queue is empty, we do _not_ move head.

      tail
      |     head
      v     v
      [ ][ ][c][d]

      If, when we resize the array, head is larger than tail, we move all of head's elements to
      the end of the new array.

      tail
      |                 head
      v                 v
      [c][d][ ][ ][ ][ ][a][b]
    */
};

typedef struct Queue Queue;

void   queue_free(Queue* queue);
Queue* queue_init(void);

void* queue_dequeue(Queue* queue);
void   queue_enqueue(Queue* queue, void* item);

bool   isQueueEmpty(const Queue* queue);
void   queue_iterate(const Queue* queue, void (*fn)(void*));
size_t get_queue_size(const Queue* queue);

void print_queue(const Queue* queue, void (*fn)(void*));

#endif

