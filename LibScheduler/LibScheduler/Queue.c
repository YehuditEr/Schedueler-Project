#include "pch.h"
#include "Queue.h"

#include "Definitions.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>



void queue_free(Queue* queue) {
    assert(queue);
    free(queue->data);
    free(queue);
}

Queue* queue_init(void) {
    Queue* queue = calloc(1, sizeof * queue);
    assert(queue);
    queue->capacity = MAX_TASKS;
    queue->size = 0;
    queue->data = calloc(queue->capacity, sizeof * queue->data);
    assert(queue->data);
    queue->head = 0;
    queue->tail = 0;
    return queue;
}

void* queue_dequeue(Queue* queue) {
    assert(queue);
    if (queue->size == 0) {
        return NULL;
    }
    void* item = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
    return item;
}

void queue_enqueue(Queue* queue, void* item) {
    assert(queue);
    assert(item);
    queue->data[queue->tail] = item;
    // Resize the underlying array if we've reached capacity.
    if (queue->size == queue->capacity) {
        printf("The queue full!!!");
        //exit(-1);
        size_t scale = 2;
        void** tmp = realloc(queue->data, scale * queue->capacity * sizeof * tmp);
        assert(tmp);
        if (queue->head > queue->tail) {
            for (size_t i = queue->head; i < queue->capacity; ++i) {
                tmp[i + queue->capacity] = tmp[i];
                tmp[i] = NULL;
            }
            queue->head += queue->capacity;
        }
        queue->capacity *= scale;
        queue->data = tmp;
    }

    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->size++;

}

bool isQueueEmpty(const Queue* queue) {
    assert(queue);
    return queue->size == 0;
}

void queue_iterate(const Queue* queue, void (*fn)(void*)) {
    assert(queue);
    assert(fn);

    if (queue->size == 0) {
        return;
    }
    for (size_t i = 0; i < queue->size; ++i) {
        void* x = queue->data[(i + queue->head) % queue->capacity];
        fn(x);
    }
}

size_t get_queue_size(const Queue* queue) {
    assert(queue);
    return queue->size;
}

void print_queue(const Queue* queue, void (*fn)(void*)) {
    queue_iterate(queue, fn);
}