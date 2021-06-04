#include "lib.h"
void wait(int sec)
{
    int s = (rand() % sec) * (rand() % 1000000) + 1000000;
    usleep(s);
}

void writeInfo(int readerQ, int writerQ, int inR, int inW)
{
    printf("ReaderQ: %d, WriterQ: %d [in: R: %d, W: %d ]",readerQ, writerQ, inR, inW);
}
void* reader()
{



}
void* writer()
{



}
