#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define THREAD_COUNT 10

sem_t sem;

void *signal_event() {
    printf("Doing some work...\n");
    sleep(2);
    printf("Sig event complete\n");
    sem_post(&sem);
    return NULL;
}

void *wait_for_event() {
    printf("waiting for event...\n");
    sem_wait(&sem);
    printf("event has been triggered\n");

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;

    sem_init(&sem, 0, 0);

    pthread_create(&t1, NULL, wait_for_event, NULL);
    pthread_create(&t2, NULL, signal_event, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);

    return 0;
}
