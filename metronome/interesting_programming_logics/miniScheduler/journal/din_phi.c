#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left  = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    int low   = (left < right) ? left : right;
    int high  = (left < right) ? right : left;

    while(1) {
        // think
        printf("Philosopher %d thinking\n", id);
        sleep(1);

        // pick lower fork first
        pthread_mutex_lock(&forks[low]);
        printf("Philosopher %d picked fork %d\n", id, low);

        // pick higher fork
        pthread_mutex_lock(&forks[high]);
        printf("Philosopher %d picked fork %d\n", id, high);

        // eat
        printf("Philosopher %d EATING\n", id);
        sleep(1);

        // put down
        pthread_mutex_unlock(&forks[high]);
        pthread_mutex_unlock(&forks[low]);
        printf("Philosopher %d put down forks\n", id);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // initialize forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_mutex_init(&forks[i], NULL);

    // create philosophers
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL,
                      philosopher, &ids[i]);
    }

    // wait forever
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);

    return 0;
}
