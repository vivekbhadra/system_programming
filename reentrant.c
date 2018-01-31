#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Prototypes */
void * thread_func1(void *);
void * thread_func2(void *);
void manipVal(void *);

int var = 0;
pthread_mutex_t m;

typedef struct thread_data {
    int a;
    int b;
    int res;
}thread_data_t;

void * thread_func1(void *arg)
{
    char buff[1024];
    thread_data_t * data = malloc(sizeof(thread_data_t));

    data->a = 20;
    data->b = 30;

    manipVal(data);
    sprintf(buff, "%d\n", data->res);
    write(2, buff, 4);

    free(data);

    return NULL;
}

void * thread_func2(void *arg)
{
    char buff[1024];
    thread_data_t * data = malloc(sizeof(thread_data_t));
    data->a = 50;
    data->b = 10;

    manipVal(data);

    sprintf(buff, "%d\n", data->res);
    write(2, buff, 4);

    free(data);

    return NULL;
}

void manipVal(void *data)
{
    thread_data_t *temp = (thread_data_t *)data;
    temp->res = temp->a * temp->b;
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

    return 0;
}
