#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
 
 
 
int ReadersQ = 0, WritersQ = 0, WritersLib=0, ReadersLib=0; 
int i; 
pthread_mutex_t  Library; 
pthread_cond_t Readers, Writers; 
void ShowStatus()
{
   printf("ReaderQ: %d WriterQ: %d [In R: %d W: %d]\n", ReadersQ, WritersQ, ReadersLib, WritersLib); 
}
void *Reader( )
{ 
   while(1)
   {  
      pthread_mutex_lock(&Library);   
      ReadersQ++; 
      ShowStatus();

      while (!(WritersQ == 0)) 
         pthread_cond_wait(&Readers, &Library);  

      pthread_mutex_unlock(&Library); 
      ReadersLib++; 
      ReadersQ--; 
      ShowStatus();

      sleep(1); 

      pthread_mutex_lock(&Library); 
      ReadersLib--; 
      ShowStatus();

      if (ReadersLib == 0) 
         pthread_cond_signal(&Writers); 

      pthread_mutex_unlock(&Library); 
   }
} 
 
 
 
void *Writer() 
{ 
   while(1)
   { 
      pthread_mutex_lock(&Library); 

      WritersQ++; 
      ShowStatus();

      while (!((ReadersLib == 0) && (WritersLib == 0)))  
         pthread_cond_wait(&Writers, &Library); 

      pthread_mutex_unlock(&Library); 
      WritersQ--; 
      WritersLib++; 
      ShowStatus();

      sleep(1); 

      pthread_mutex_lock(&Library); 
      WritersLib--; 
      ShowStatus();

      if(WritersQ>0) 
         pthread_cond_signal(&Writers); 
      else 
         pthread_cond_broadcast(&Readers); 

      pthread_mutex_unlock(&Library);  
   } 
} 
 

int main(int argc, char* argv[])
{ 
   int ReadersAmount = atoi(argv[1]);
   int WritersAmount = atoi(argv[2]);   
 
   pthread_t c[ReadersAmount], p[WritersAmount]; 
 
   pthread_mutex_init(&Library, 0); 
   pthread_cond_init(&Readers, 0); 
   pthread_cond_init(&Writers, 0); 
 
   for(i=0; i<ReadersAmount; i++) 
      pthread_create(&c[i], NULL, Reader, NULL);  
   for(i=0; i<WritersAmount; i++) 
      pthread_create(&p[i], NULL, Writer, NULL); 
  
   
 
   for(i=0; i<WritersAmount; i++) 
      pthread_join(p[i], NULL); 
   for(i=0; i<ReadersAmount; i++) 
      pthread_join(c[i], NULL); 
 
   pthread_cond_destroy(&Readers); 
   pthread_cond_destroy(&Writers); 
   pthread_mutex_destroy(&Library); 
   
   return 0;  
} 