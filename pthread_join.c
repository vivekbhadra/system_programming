#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Prototypes */
void * thread_func1(void *);
void * thread_func2(void *);
void manipVal(int);

int var = 0;
pthread_mutex_t m;

void * thread_func1(void *arg)
{
    printf("Hello World again\n");
    
    return NULL;
}

void * thread_func2(void *arg)
{
    printf("Hello World again and again\n");

    return NULL;
}

void manipVal(int val)
{
    pthread_mutex_lock(&m);
    var = val;
    pthread_mutex_unlock(&m);
}

int main(void)
{
    pthread_t thread1, thread2;
    int ret;

    ret = pthread_create(&thread1, NULL, thread_func1, NULL);
    if(ret < 0)
        printf("Thread creation failed\n");

    ret = pthread_create(&thread2, NULL, thread_func2, NULL);
    if (ret < 0)
        printf("Failed to create thread\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Hello world!\n");
    return 0;
}
