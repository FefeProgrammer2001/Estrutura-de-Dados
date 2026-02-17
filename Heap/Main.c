#include "Heap.h"
#define N 10

int main(void) {
    Heap *h = heap_create();
    if(!h) {
        perror("Erro ao criar heap\n");
        return 1;
    }

    size_t *values = (size_t*)malloc(N * sizeof(size_t));
    printf("Digite os valores do vetor (TAMANHO 10):\n");
    for(int i = 0; i < N; i++) {
        printf("Valor %d: ", i+1);
        scanf("%zu", &values[i]);
    }
    printf("\n");

    for(size_t i = 0; i < N; ++i) {
        heap_push(h, values[i]);
        heap_print(h);
    }

    printf("\nRemovendo elementos em ordem crescente:\n");
    while(!heap_is_empty(h)) {
        size_t v;
        heap_pop(h, &v);
        printf("pop -> %zu\n", v);
        heap_print(h);
    }

    heap_destroy(h);
    free(values);
    return 0;
}
