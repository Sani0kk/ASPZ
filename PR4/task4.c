#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 5
#define ALLOCATIONS 10000

void* thread_func(void* arg) {
    for (int i = 0; i < ALLOCATIONS; ++i) {
        void* mem = malloc(1024);  // 1 KB
        if (!mem) {
            fprintf(stderr, "Thread %ld: malloc failed at iteration %d\n", (long)arg, i);
            pthread_exit(NULL);
        }
        // емулюємо обробку
        usleep(10); // 10 мікросекунд
        free(mem);
    }
    printf("Thread %ld finished successfully\n", (long)arg);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[THREAD_COUNT];

    for (long i = 0; i < THREAD_COUNT; ++i) {
        if (pthread_create(&threads[i], NULL, thread_func, (void*)i) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < THREAD_COUNT; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");
    return 0;
}
