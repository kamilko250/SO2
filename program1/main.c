#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

void wait(int sec);
void writeInfo(int readerQ, int writerQ, int inR, int inW);
void* writer();
void* reader();
int WritersQueueCount = 0;
int ReadersQueueCount = 0;
int WritersLibCount = 0;
int ReadersLibCount = 0;
int ReadersCount = 0;
int WritersCount = 0;
pthread_mutex_t lib;
pthread_cond_t condReader;  
pthread_cond_t condWriter;


int main(int argc, char** argv)
{
    int c;
    if(argc >= 3 )
    {
        while((c = getopt(argc, argv, "r:w:")) != -1)
        {
            switch (c)
            {
                case 'r':
                {
                    ReadersCount = atoi(optarg);
                    printf("readers: %d\n", ReadersCount);
                    break;
                }
                case 'w':
                {
                    WritersCount = atoi(optarg);
                    printf("writers: %d\n", WritersCount);
                    break;
                }
                default:
                    break;
            }
        }
    }
    else
    {
        return -1;
    }
    pthread_t threads_writers [WritersCount]; 
    pthread_t threads_readers [ReadersCount];
    
    pthread_mutex_init(&lib, 0);
    pthread_cond_init(&condWriter, 0);
    pthread_cond_init(&condReader, 0);

 
        for(int i = 0; i < ReadersCount; i++)
            pthread_create(&threads_readers[i], NULL, reader, NULL);
    
        for(int i = 0; i < WritersCount; i++)
            pthread_create(&threads_writers[i], NULL, writer, NULL);
    
        for(int i = 0; i < ReadersCount; i++)
            pthread_join(threads_readers[i] ,NULL);
    
        for(int i = 0; i < WritersCount; i++)
            pthread_join(threads_writers[i] ,NULL);
    pthread_cond_destroy(&condReader);
    pthread_cond_destroy(&condWriter);
    pthread_mutex_destroy(&lib);

    return 0;
}
void wait(int sec)
{
    int s = (rand() % sec) * (rand() % 1000000) + 1000000;
    usleep(s);
}

void writeInfo(int readerQ, int writerQ, int inR, int inW)
{
    printf("ReaderQ: %d, WriterQ: %d [(in) R: %d, W: %d ]\n", readerQ, writerQ, inR, inW);
}
void* reader()
{
    while(1)
    {

    pthread_mutex_lock(&lib);
    ReadersQueueCount++;
    writeInfo(ReadersQueueCount, WritersQueueCount, ReadersLibCount, WritersLibCount);

    while(WritersLibCount != 0)
        pthread_cond_wait(&condReader ,&lib);

    pthread_mutex_unlock(&lib);
    ReadersLibCount++;
    ReadersQueueCount--;

    writeInfo(ReadersQueueCount, WritersQueueCount, ReadersLibCount, WritersLibCount);
    wait(1);
    pthread_mutex_lock(&lib);
    ReadersLibCount--;
    writeInfo(ReadersQueueCount, WritersQueueCount, ReadersLibCount, WritersLibCount);
    if(ReadersLibCount == 0)
        pthread_cond_signal(&condWriter);
    pthread_mutex_unlock(&lib);
    }
}
void* writer()
{
    while(1)
    {
        
    pthread_mutex_lock(&lib);
    WritersQueueCount++;
    writeInfo(ReadersQueueCount, WritersQueueCount, ReadersLibCount, WritersLibCount);
    
    while((WritersLibCount != 0) || (ReadersLibCount != 0))
    {
        pthread_cond_wait(&condWriter, &lib);
    }
    pthread_mutex_unlock(&lib);
    WritersQueueCount--;
    WritersLibCount++;

    writeInfo(ReadersQueueCount, WritersQueueCount, ReadersLibCount, WritersLibCount);
    wait(1);

    pthread_mutex_lock(&lib);
    WritersLibCount--;
    writeInfo(ReadersQueueCount, WritersQueueCount, ReadersLibCount, WritersLibCount);
    pthread_cond_signal(&condWriter);
    pthread_cond_broadcast(&condReader);
    pthread_mutex_unlock(&lib);
    }
}