#include "thread_processor.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>

// Mutex for synchronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* processSubfield(void *arg) {
    EventData *events = (EventData*)arg;
    // Your processing logic here
    pthread_exit(NULL);
}

void processThreads(EventData *events, int num_events, int num_threads, const char *subfield, const char **subfield_values) {
    pthread_t threads[num_threads];
    int events_per_thread = num_events / num_threads;
    int remainder = num_events % num_threads;
    int start = 0;

    for (int i = 0; i < num_threads; i++) {
        int count = events_per_thread + (i < remainder ? 1 : 0);
        pthread_create(&threads[i], NULL, processSubfield, &events[start]);
        start += count;
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}

