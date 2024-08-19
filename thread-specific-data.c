#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

pthread_key_t key;

void array_destructor(void *arr) {
    free(arr);
    printf("array freed for thread\n");
    return;
}

void *thread_fn(void *arg) {
    int *my_array = (int *)malloc(10 * sizeof(int));
    pthread_setspecific(key, my_array);

    for (int i = 0; i < 10; i++) {
        my_array[i] = i;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d", my_array[i]);
    }
    printf("\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;

    pthread_key_create(&key, array_destructor);

    pthread_create(&t1, NULL, thread_fn, NULL);
    pthread_create(&t2, NULL, thread_fn, NULL);

    pthread_key_delete(key);

    return 0;
}
