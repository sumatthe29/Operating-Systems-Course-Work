#ifndef MULTI_LOOKUP_H
#define MULTI_LOOKUP_H

// included libraries

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>      // for mutex
#include <semaphore.h>    // for semaphores
#include <sys/syscall.h>
#include <sys/time.h>     // timekeeping utility 
#include <unistd.h>       // used to check if log file specified exists (access function op)

// additional included h files

#include "array.h"        // circular queue, utilzed in shared buffer
#include "util.h"         // provided for resolver, converts website name into ip address

// limits

// must have at least 1 thread for req, res
#define MIN_R_THREADS 1

#define MAX_INPUT_FILES 100
#define MAX_RESOLVER_THREADS 10
#define MAX_REQUESTER_THREADS 10
#define MAX_DOMAIN_NAME_LENGTH 50  // 50 worked with pa4, carrying over unless issues occur
#define MAX_IP_LENGTH INET6_ADDRSTRLEN


// Two different typestructs created for each function thread pool, contains all the values 
// passed into functions, arrays for shared buffer, etc., and mutex values for syncronization 

// struct #1: req_thread_struct contains related values to req function
// sort of like a state machine in a way
typedef struct sync_thread_struct {
    // misc 

    FILE* serviced;         // log file for requester (RETIRED/UNUSED)
    FILE* resolved;         // log file for resolver 
    
    // (array) circular queues

    int argvnum;                        // number of input files = argvc-5
    int numres;                         // number of resolver threads
    int numreq;                         // number of requester threads
    int start;                          // index fileNames array                           
    char* fileNames[MAX_INPUT_FILES];   // circular queue for file names
    array* buff;                        // circular queue for shared buffer

    // mutex

    pthread_mutex_t* shared_buffer; // mutex for shared buffer (EXCLUDED)
    pthread_mutex_t* file_queue;    // mutex for file queue (EXCLUDED) 
    pthread_mutex_t* tcount;        // (EXCLUDED)
    pthread_mutex_t* req_lock;      // mutex for writing to req_log 
    pthread_mutex_t* res_lock;      // mutex for writing to res_log

    // sem_t rq;
    // sem_t rs;

}synchro_thread_struct;



// function declarations

void* request(void* sts);
void* resolve(void* sts);



#endif