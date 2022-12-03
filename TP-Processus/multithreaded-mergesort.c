#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // don't forget to compile with -pthread
#include <time.h>

typedef unsigned int index;
typedef unsigned int length;

void merge(int array[], index start, index middle, index final);
void *merge_sort(int array[], index start, index final);

void *merge_sort(int array[], index start, index final)
{
  if (start < final)
  {
    index middle = floor((start + final) / 2);
    merge_sort(array, start, middle);
    merge_sort(array, middle + 1, final);
    merge(array, start, middle, final);
  }
}

void merge(int array[], index start, index middle, index final)
{
  length countL = middle - start + 1;
  int *arrayL = malloc(countL * sizeof(int));
  index currentL, currentR;
  for (currentL = 0; currentL < countL; currentL++)
    arrayL[currentL] = array[start + currentL];

  length countR = final - middle;
  int *arrayR = malloc(countR * sizeof(int));
  for (currentR = 0; currentR < countR; currentR++)
    arrayR[currentR] = array[middle + 1 + currentR];

  currentL = 0;
  currentR = 0;
  index current;
  for (current = start; current <= final && currentL < countL && currentR < countR; current++)
  {
    if (arrayL[currentL] <= arrayR[currentR])
    {
      array[current] = arrayL[currentL];
      currentL++;
    }
    else
    { // arrayL[currentL] > arrayR[currentR]
      array[current] = arrayR[currentR];
      currentR++;
    }
  }

  // If <arrayL> was completely consumed, copy the remainder of <arrayR> over the remainder of <array>
  if (currentL >= countL)
    while (currentR < countR)
    {
      array[current] = arrayR[currentR];
      current++;
      currentR++;
    }

  // If <arrayR> was completely consumed, copy the remainder of <arrayL> over the remainder of <array>
  if (currentR >= countR)
    while (currentL < countL)
    {
      array[current] = arrayL[currentL];
      current++;
      currentL++;
    }

  free(arrayL);
  free(arrayR);
}

// function to calculate time elapsed between two timestamps
long int nanos_between(struct timespec *final, struct timespec *start)
{
  time_t seconds = final->tv_sec - start->tv_sec;
  long int nanoseconds = final->tv_nsec - start->tv_nsec;
  return seconds * 1e9 + nanoseconds;
}

int tableau[] = {2, 27, 3, 49, 98, 12, 4, 1, 42};
int longueur = sizeof(tableau) / sizeof(int);

void show(int array[], length count)
{
  for (index i = 0; i < count; i++)
    printf("%d ", array[i]);
  printf("\n");
}

void *multiThreadMerge(int numberOfThreads, int threadsAlreadyCreated, index startIndex, index endIndex)
{

  index middle = floor((startIndex + endIndex) / 2);

  if (numberOfThreads > threadsAlreadyCreated)
  {
    // threads initialization
    pthread_t subThread1;
    pthread_t subThread2;

    // create two more threads (one level lower)
    pthread_create(&subThread1, NULL, multiThreadMerge(numberOfThreads, threadsAlreadyCreated * 2, startIndex, middle), NULL);
    pthread_create(&subThread2, NULL, multiThreadMerge(numberOfThreads, threadsAlreadyCreated * 2, middle + 1, endIndex), NULL);

    // merge what the two children threads have done
    merge(tableau, 0, middle, endIndex);
  }
  else
  {
    // merge sort
    merge_sort(tableau, 0, middle);
    merge_sort(tableau, middle + 1, endIndex);
    merge(tableau, startIndex, middle, endIndex);
  }
}

int main(int argc, char *argv[])
{
  struct timespec start, final;
  // get time before execution
  clock_gettime(CLOCK_REALTIME, &start);

  show(tableau, longueur);

  // change the first parameter to the number of threads of the last level we want
  multiThreadMerge(8, 1, 0, longueur - 1);

  show(tableau, longueur);

  // get time after execution
  clock_gettime(CLOCK_REALTIME, &final);

  // print elapsed time
  printf("Time elapsed: %ld ns\n", nanos_between(&final, &start));
  return EXIT_SUCCESS;
}
