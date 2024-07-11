#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t mutex;
int balance = 10000;

void* deposit(void* arg) {
    int amount = (int)arg;
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&mutex);
        balance += amount;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* withdraw(void* arg) {
    int amount = (int)arg;
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&mutex);
        balance -= amount;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char** argv) {
    int thread_no = 1;
    if (argc > 1) {
        sscanf(strdup(argv[1]), "%d", &thread_no);
    }
    fprintf(stderr, "# of Deposit threads: %d\n", thread_no);
    fprintf(stderr, "# of Withdraw threads: %d\n", thread_no);

    pthread_mutex_init(&mutex, NULL);

    pthread_t deposit_thread_id[thread_no];
    pthread_t withdraw_thread_id[thread_no];

    for (int i = 0; i < thread_no; i++) {
        pthread_create(&deposit_thread_id[i], NULL, deposit, (void*)100);
        pthread_create(&withdraw_thread_id[i], NULL, withdraw, (void*)100);
    }

    for (int i = 0; i < thread_no; i++) {
        pthread_join(deposit_thread_id[i], NULL);
        pthread_join(withdraw_thread_id[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    printf("Final balance: %d\n", balance);

    return 0;
}

