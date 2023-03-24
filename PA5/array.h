#ifndef ARRAY_H
#define ARRAY_H

// Include statements

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <semaphore.h>
#include <pthread.h>

// Defined variables

#define ARRAY_SIZE 100
#define MAX_NAME_LENGTH 50 //rough estimate
#define POISON "####"

// Queue struct
typedef struct array_type {
	char *elements[ARRAY_SIZE];
	int size; //replaced by semaphore
	int max;
	int head;
	int tail;

	char* poison;

	pthread_mutex_t mutex;
	sem_t el;                                    // empty
	sem_t fl;
} array; //queue system 

int  array_init(array *s);                   // initialize the array
int  array_put (array *s, char *hostname);   // place element into the array, block when full
int  array_get (array *s, char **hostname);  // remove element from the array, block when empty
// int  r(array*s);                             // designed to remove all elements
// int  front(array *s);
void array_free(array *s);                   // free the array's resources

#endif