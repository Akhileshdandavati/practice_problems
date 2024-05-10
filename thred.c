#include <stdio.h>
#include <pthread.h>

int n = 0;
pthread_mutex_t lock;
void *producers(void *arg)
{
    for (int i = 0; i < 1000; i++)
    {
        pthread_mutex_lock(&lock);
        n++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *consumers(void *arg)
{
    for (int i = 0; i < 1000; i++)
    {
        pthread_mutex_lock(&lock);
        n--;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    int p = 5;
    int c = 3;

    pthread_t producer[p];
    pthread_t consumer[c];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < p; i++)
    {
        pthread_create(&producer[i], NULL, producers, NULL);
    }

    for (int i = 0; i < c; i++)
    {
        pthread_create(&consumer[i], NULL, consumers, NULL);
    }

    for (int i = 0; i < p; i++)
    {
        pthread_join(producer[i], NULL);
    }

    for (int i = 0; i < c; i++)
    {
        pthread_join(consumer[i], NULL);
    }
    pthread_mutex_destroy(&lock);

    printf("Value of 'n' after all threads have finished is :%d\n", n);

    return 0;
}