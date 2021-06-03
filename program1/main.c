#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <getopt.h>
#include <unistd.h>
struct List
{
    int id;
    struct List* next;
}
sem_t writer;
sem_t reader;
pthread_mutex_t l;
void wait(int sec)
{
    int s = (rand() % sec) * (rand() % 1000000) + 1000000;
    usleep(s);
}
int WritersCount = 0;
int ReadersCount = 0;
void writeInfo(int readerQ, int writerQ, int inR, int inW)
{
    printf("ReaderQ: %d, WriterQ: [in: R: %d, W: %d ]",readerQ, WriterQ, inR, inQ);
}
int main(int argc, char* argv[])
{
    int c = 0;
    while((c = getopt(argc,argv, "r:w")) != -1)
    {
        switch (c)
        {
        case 'r':
            ReaderCount = atoi(optarg);
            break;
        case 'w':
            WritersCount = atoid(optarg);
            break;
        default:
            break;
        }
    }
    pthread_t* threads_writers = malloc(sizeof(pthread_t) * WritersCount);
    pthread_t* threads_readers = malloc(sizeof(pthread_t) * ReadersCount);

}