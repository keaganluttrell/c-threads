#include <pthread.h>
#include <stdio.h>

#define THREAD_COUNT 10

int counter = 0;
pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALIZER;

void *thread_tgt(void *vargs) {

    int t = pthread_mutex_lock(&counter_lock);
    if (t != 0) {
        printf("pthread mutex lock failed");
    }

    for (int i = 0; i < 1000000; i++) {
        counter += 1;
    }

    pthread_mutex_unlock(&counter_lock);
    printf("Counter is %d\n", counter);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t threads[THREAD_COUNT];
    pthread_mutex_init(&counter_lock, NULL);
    int i;
    for (i = 0; i < THREAD_COUNT; i++) {

        if (pthread_create(&threads[i], NULL, thread_tgt, NULL)) {
            printf("pthread_create error\n");
            return 1;
        }
    }

    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
