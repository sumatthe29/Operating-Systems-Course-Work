#include "array.h"

int array_init(array *s)                   // initialize the array
{
    // allocate for char array
    // https://stackoverflow.com/questions/21763341/char-array-malloc-sizeof-charlen-vs-malloc-sizeof-charlen
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        s->elements[i] = (char*)malloc(MAX_NAME_LENGTH);
    }
    
    
    // array, defined as ARRAY_SIZE, loop through and malloc each element MAX_NAME

    pthread_mutex_init(&s->mutex, NULL);
    sem_init(&s->el,0,ARRAY_SIZE);
    sem_init(&s->fl,0,0);

    // s->size = 0;
    // s->max = ARRAY_SIZE;
    s->head = 0;
    s->tail = -1;

    // sucess return
    return 0;

}                   
int array_put (array *s, char *hostname)   // place element into the array, block when full
{
    
    // if queue is full, function fails
    sem_wait(&s->el);
    
    pthread_mutex_lock(&s->mutex);
    // if full, % automatically convets value to zero, circular
    s->tail = (s->tail+1)%ARRAY_SIZE;
    //s->elements[s->tail] = (char *) malloc((sizeof hostname + 1)* sizeof(char));
    char *j = s->elements[s->tail];
    strcpy(j,hostname);
    
    // s->tail++;
    s->size++;

    pthread_mutex_unlock(&s->mutex);	/* release the buffer */
    sem_post(&s->fl);
    // return s->elements[s->tail-1];
    return 0;
}

int array_get (array *s, char **hostname)  // remove element from the array, block when empty
{
   
    
    // if queue is empty, exit
    sem_wait(&s->fl);
   
        
    pthread_mutex_lock(&s->mutex);

    
    // create seperate char array to funnel value into
    strcpy(*hostname,s->elements[s->head]);
    // if full, % automatically convets value to zero, circular
    s->head = (s->head + 1) % ARRAY_SIZE; 
    s->size--;

    pthread_mutex_unlock(&s->mutex);
    
    sem_post(&s->el);
        
    return 0;

    
}

void array_free(array *s)                   // free the array's resources
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        free(s->elements[i]);
    }

    //free semaphores, mutex as well
    sem_destroy(&s->el);
    sem_destroy(&s->fl);
    pthread_mutex_destroy(&s->mutex);
    
}