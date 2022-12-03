#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define NB_PHILOSOPHERS 5
pthread_t philosophers[NB_PHILOSOPHERS];

#define RIGHT(i) (( i ) % NB_PHILOSOPHERS)
#define LEFT(i) ((i + 1) % NB_PHILOSOPHERS)

#define AVAILABLE 0
#define UNAVAILABLE 1

int baguettes[NB_PHILOSOPHERS] = { 0 }; // all baguettes are initially available

int pick_up(int me) {
    // try to take first baguette
    if (baguettes[RIGHT(me)] == AVAILABLE) {
        baguettes[RIGHT(me)] = UNAVAILABLE;
    }
    else {
        return 0;
    }

    // try to take second baguette
    if (baguettes[LEFT(me)] == AVAILABLE){
        baguettes[LEFT(me)] = UNAVAILABLE;
    }
    else {
        return 0;
    }
    // both baguettes could be taken
    return 1;
}

void drop(int me) {
    baguettes[RIGHT(me)] = AVAILABLE;
    baguettes[LEFT(me)] = AVAILABLE;
}

void think(int me) {
    printf("%d is eating\n", me);
    sleep(1);
}

void eat(int me) {
    printf("%d is eating\n", me);
}

void* philosopher(int me) {
    while(1) {
        think(me);
        if (pick_up(me) == 1) {
            // this will only happen if both baguettes could be taken
            eat(me);
            drop(me);
        }
    }
}

int main(int argc, char* argv[]) {
    for(unsigned int p = 0; p < NB_PHILOSOPHERS; p++) {
        pthread_create(&philosophers[p], NULL, philosopher, p);
    }
    for(unsigned int p = 0; p < NB_PHILOSOPHERS; p++) {
        pthread_join(&philosophers[p], NULL);
    }
    return EXIT_SUCCESS;
}
