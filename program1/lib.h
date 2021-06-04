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