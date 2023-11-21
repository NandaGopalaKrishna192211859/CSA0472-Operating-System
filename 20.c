#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, writeMutex;
int readersCount = 0;  
void *reader(void *arg) {
    int readerID = *(int *)arg;

    while (1) {
        
        sem_wait(&mutex);
        readersCount++;

        if (readersCount == 1) {
           
            sem_wait(&writeMutex);
        }

        sem_post(&mutex);

        
        printf("Reader %d is reading.\n", readerID);
        sleep(1);

        
        sem_wait(&mutex);
        readersCount--;

        if (readersCount == 0) {
            
            sem_post(&writeMutex);
        }

        sem_post(&mutex);

        
        sleep(2);
    }
}

void *writer(void *arg) {
    int writerID = *(int *)arg;

    while (1) {
        
        sem_wait(&writeMutex);

        
        printf("Writer %d is writing.\n", writerID);
        sleep(1);

        
        sem_post(&writeMutex);

        
        sleep(2);
    }
}

int main() {
    pthread_t readerThreads[NUM_READERS], writerThreads[NUM_WRITERS];
    int readerIDs[NUM_READERS], writerIDs[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&writeMutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        readerIDs[i] = i + 1;
        pthread_create(&readerThreads[i], NULL, reader, &readerIDs[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIDs[i] = i + 1;
        pthread_create(&writerThreads[i], NULL, writer, &writerIDs[i]);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readerThreads[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeMutex);

    return 0;
}
