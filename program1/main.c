#include "lib.h"

int WritersQueueCount = 0;
int ReadersQueueCount = 0;
int WritersLibCount = 0;
int ReaderLibCount = 0;
int ReadersCount = 0;
int WritersCount = 0;

int main(int argc, char* argv[])
{
    int c = 0;
    while((c = getopt(argc,argv, "r:w")) != -1)
    {
        switch (c)
        {
        case 'r':
            ReadersCount = atoi(optarg);
            break;
        case 'w':
            WritersCount = atoi(optarg);
            break;
        default:
            break;
        }
    }
    pthread_t threads_writers [WritersCount]; 
    pthread_t threads_readers [ReadersCount];
    pthread_mutex_t lib;
    pthread_cond_t condReader;  
    pthread_cond_t condWriter;

    pthread_mutex_init(&lib, 0);
    pthread_cond_init(&condWriter, 0);
    pthread_cond_init(&condReader, 0);

    for(int i = 0; i < ReadersCount; i++)
        pthread_create(&threads_readers[i], NULL, reader, NULL);
    
    for(int i = 0; i < WritersCount; i++)
        pthread_create(&threads_writers[i], NULL, writer, NULL);
    
    for(int i = 0; i < ReadersCount; i++)
        pthread_join(threads_readers[i] ,NULL);
    
    for(int i = 0; i < ReadersCount; i++)
        pthread_join(threads_writers[i] ,NULL);
    
    pthread_cond_destroy(&condReader);
    pthread_cond_destroy(&condWriter);
    pthread_mutex_destroy(&lib);

    return 0;
}