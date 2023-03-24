#include "pa4.h"

int array_init(array *s)                   // initialize the array
{
    // allocate for char array
    // https://stackoverflow.com/questions/21763341/char-array-malloc-sizeof-charlen-vs-malloc-sizeof-charlen
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        s->elements[i] = (char*)malloc(MAX_NAME_LENGTH);
    }
    
    
    // array, defined as ARRAY_SIZE, loop through and malloc each element MAX_NAME

    pthread_mutex_init(&mutex, NULL);
    sem_init(&el,0,ARRAY_SIZE);

    s->size = 0;
    s->max = ARRAY_SIZE;
    s->head = 0;
    s->tail = -1;

    // return s;

}                   
int array_put (array *s, char *hostname)   // place element into the array, block when full
{
    
    // if queue is full, function fails
    if (s->size == s->max){sem_wait(&el);}
    else
    {
        sem_post(&el);
        pthread_mutex_lock(&mutex);
        // if full, % automatically convets value to zero, circular
        s->tail = (s->tail+1)%s->max;
        //s->elements[s->tail] = (char *) malloc((sizeof hostname + 1)* sizeof(char));
        char *j = s->elements[s->tail];
        strcpy(j,hostname);
        
        // s->tail++;
        s->size++;

        pthread_mutex_unlock(&mutex);	/* release the buffer */
        
        // return s->elements[s->tail-1];
        return 0;
    }
    
    
    
}

int array_get (array *s, char **hostname)  // remove element from the array, block when empty
{
    // if queue is empty, exit
    if (s->size == 0){sem_wait(&el);}
    else
    {
        sem_post(&el);
        pthread_mutex_lock(&mutex);
        // create seperate char array to funnel value into
        strcpy(s->elements[s->head],*hostname);
        // if full, % automatically convets value to zero, circular
        s->head = (s->head + 1) % s->max; 
        s->size--;

        pthread_mutex_unlock(&mutex);
        
        return 0;

    }
}

// int r(array *s)  // remove element from the 
// {
    
//     // if queue is empty, exit
//     if (s->size == 0){return -1;}
//     else
//     {
//         pthread_mutex_lock(&mutex);
//         // create seperate char array to funnel value into
//         // strcpy(s->elements[s->head],hostname);
//         // if full, % automatically convets value to zero, circular
//         s->head = (s->head + 1) % s->max; 
//         s->size--;
//         pthread_mutex_unlock(&mutex);
        
//         return 0;

//     }
    
// }

// int front(array *s)
// {
//     return s->elements[s->head];
// }

void array_free(array *s)                   // free the array's resources
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        free(s->elements[i]);
    }
    
}

