#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define HEAP_INITIAL_CAPACITY 16

#define HEAP_PARENT(i)      (((i) - 1) / 2)
#define HEAP_LEFT(i)        (2 * (i) + 1)
#define HEAP_RIGHT(i)       (2 * (i) + 2)

// Macro para fazer debug
#define HEAP_DEBUG(fmt, ...) \
    do { \
        printf("[HEAP DEBUG] " fmt "\n", ##__VA_ARGS__); \
    } while (0)

// Struct da Heap
typedef struct {
    size_t *data;
    size_t size;
    size_t capacity;
} Heap;

// Declaração das funções
Heap *heap_create(void);
void heap_destroy(Heap *h);
int  heap_push(Heap *h, size_t value);
int  heap_pop(Heap *h, size_t *out_value);
int  heap_peek(const Heap *h, size_t *out_value);
int  heap_is_empty(const Heap *h);
void heap_print(const Heap *h);

#endif
