#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_ALARMS 3

static int shared_alarm_count = 0;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *alarm_worker(void *arg) {
    int id = *(int *)arg;

    sleep(id + 1);

    pthread_mutex_lock(&lock);
    shared_alarm_count++;
    printf("Thread %d: alarm event handled. Shared count = %d\n",
           id, shared_alarm_count);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void) {
    pthread_t threads[MAX_ALARMS];
    int ids[MAX_ALARMS] = {1, 2, 3};

    printf("Thread + Mutex demonstration\n");

    for (int i = 0; i < MAX_ALARMS; i++)
        pthread_create(&threads[i], NULL, alarm_worker, &ids[i]);

    for (int i = 0; i < MAX_ALARMS; i++)
        pthread_join(threads[i], NULL);

    printf("All alarm threads completed.\n");
    pthread_mutex_destroy(&lock);
    return 0;
}
