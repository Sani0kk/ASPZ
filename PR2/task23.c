#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MEMORY_POOL_SIZE 1024 * 1024 // 1MB

typedef struct block {
    size_t size;
    struct block *next;
    int is_free;
} block_t;

static char memory_pool[MEMORY_POOL_SIZE];
static block_t *free_list = NULL;

void init_memory_pool() {
    free_list = (block_t *)memory_pool;
    free_list->size = MEMORY_POOL_SIZE - sizeof(block_t);
    free_list->next = NULL;
    free_list->is_free = 1;
}

void split_block(block_t *curr, size_t size) {
    block_t *new_block = (block_t *)((char *)curr + sizeof(block_t) + size);
    new_block->size = curr->size - size - sizeof(block_t);
    new_block->next = curr->next;
    new_block->is_free = 1;
    curr->size = size;
    curr->next = new_block;
}

void *my_malloc(size_t size) {
    if (!free_list) {
        init_memory_pool();
    }

    block_t *curr = free_list;
    while (curr) {
        if (curr->is_free && curr->size >= size) {
            if (curr->size > size + sizeof(block_t)) {
                split_block(curr, size);
            }
            curr->is_free = 0;
            return (void *)(curr + 1);
        }
        curr = curr->next;
    }
    return NULL; // Недостатньо пам'яті
}

void my_free(void *ptr) {
    if (!ptr) {
        return;
    }

    block_t *curr = (block_t *)ptr - 1;
    curr->is_free = 1;

    // Об'єднання вільних блоків
    block_t *temp = free_list;
    while (temp) {
        if (temp->is_free && temp->next && temp->next->is_free) {
            temp->size += temp->next->size + sizeof(block_t);
            temp->next = temp->next->next;
        }
        temp = temp->next;
    }
}

int main() {
    int *arr1 = (int *)my_malloc(10 * sizeof(int));
    if (arr1) {
        printf("Виділено пам'ять для arr1\n");
        for (int i = 0; i < 10; i++) {
            arr1[i] = i;
        }
        my_free(arr1);
        printf("Звільнено пам'ять для arr1\n");
    }

    double *arr2 = (double *)my_malloc(20 * sizeof(double));
    if (arr2) {
        printf("Виділено пам'ять для arr2\n");
        my_free(arr2);
        printf("Звільнено пам'ять для arr2\n");
    }

    return 0;
}
