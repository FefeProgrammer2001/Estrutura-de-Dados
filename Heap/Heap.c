#include "Heap.h"

// Faz troca dos valores apontados como 'a' e 'b'
static void heap_swap(size_t *a, size_t *b) {
    size_t tmp = *a;
    *a = *b;
    *b = tmp;
}

/* 
    Função utilizada após a inserção de um elemento em idx.
    Enquanto o elemento na posição idx for menor que o pai
    ele faz a troca entre os dois, até chegar na raíz,
    atualizando idx a cada troca
*/
static void heap_sift_up(Heap *h, size_t idx) {
    while(idx > 0) {
        size_t p = HEAP_PARENT(idx);
        if(h->data[idx] >= h->data[p]) {
            break;
        }
        HEAP_DEBUG("sift_up: swap idx=%zu (val=%zu) com p=%zu (val=%zu)", idx, h->data[idx], p, h->data[p]);
        heap_swap(&h->data[idx], &h->data[p]);
        idx = p;
    }
}

/*
    heap_sift_down é chamada após a remoção da raíz.
    Essa função compara o elemento em idx com o filho esquerdo
    e com o direito, encontrando o menor entre ele e seus filhos.
    As trocas também são feitas nessa função
*/
static void heap_sift_down(Heap *h, size_t idx) {
    while (1) {
        size_t left  = HEAP_LEFT(idx);
        size_t right = HEAP_RIGHT(idx);
        size_t smallest = idx;

        if(left < h->size && h->data[left] < h->data[smallest]) {
            smallest = left;
        }
        if(right < h->size && h->data[right] < h->data[smallest]) {
            smallest = right;
        }

        if(smallest == idx) {
            break;
        }

        HEAP_DEBUG("sift_down: swap idx=%zu (val=%zu) com child=%zu (val=%zu)", idx, h->data[idx], smallest, h->data[smallest]);
        heap_swap(&h->data[idx], &h->data[smallest]);
        idx = smallest;
    }
}

// Aloca a heap na memória
Heap *heap_create(void) {
    Heap *h = (Heap*)malloc(sizeof(Heap));
    if(!h) {
        HEAP_DEBUG("falha ao alocar Heap");
        return NULL;
    }

    h->capacity = HEAP_INITIAL_CAPACITY;
    h->size = 0;
    h->data = (size_t*)malloc(h->capacity * sizeof(size_t));
    if(!h->data) {
        HEAP_DEBUG("falha ao alocar vetor da Heap");
        free(h);
        return NULL;
    }

    HEAP_DEBUG("heap criada: capacity=%zu", h->capacity);
    return h;
}

// Desaloca a heap na memória
void heap_destroy(Heap *h) {
    if(!h) return;
    HEAP_DEBUG("heap_destroy: size=%zu capacity=%zu", h->size, h->capacity);
    free(h->data);
    free(h);
}

// Retorn NULL se a heap estiver vazia
int heap_is_empty(const Heap *h) {
    return (h == NULL || h->size == 0);
}

// Operação de inserção
int heap_push(Heap *h, size_t value) {
    if(!h) return 0;

    if(h->size == h->capacity) {
        size_t new_capacity = h->capacity * 2;
        size_t *new_data = (size_t*)realloc(h->data, new_capacity * sizeof(size_t));
        if(!new_data) {
            HEAP_DEBUG("heap_push: falha ao realocar para %zu", new_capacity);
            return 0;
        }
        h->data = new_data;
        h->capacity = new_capacity;
        HEAP_DEBUG("heap realocada: nova capacidade=%zu", h->capacity);
    }

    HEAP_DEBUG("heap_push: inserir valor=%zu na pos=%zu", value, h->size);
    h->data[h->size] = value;
    heap_sift_up(h, h->size);
    h->size++;
    return 1;
}

// Operação de remoção
int heap_pop(Heap *h, size_t *out_value) {
    if(!h || h->size == 0) {
        return 0;
    }

    if(out_value) {
        *out_value = h->data[0];
    }

    HEAP_DEBUG("heap_pop: removendo raiz=%zu", h->data[0]);

    h->size--;
    if(h->size > 0) {
        h->data[0] = h->data[h->size];
        heap_sift_down(h, 0);
    }

    return 1;
}

// Menor elemento da heap
int heap_peek(const Heap *h, size_t *out_value) {
    if(!h || h->size == 0 || !out_value) {
        return 0;
    }
    *out_value = h->data[0];
    return 1;
}

// Utilizado para debug
void heap_print(const Heap *h) {
    if(!h) {
        printf("heap NULL\n");
        return;
    }
    printf("Heap: size=%zu capacity=%zu\n", h->size, h->capacity);
    for(size_t i = 0; i < h->size; ++i) {
        printf("  [%zu] = %zu\n", i, h->data[i]);
    }
}
