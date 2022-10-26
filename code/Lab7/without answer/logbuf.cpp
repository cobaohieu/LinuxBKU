#include <chrono>
#include <thread>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define MAX_LOG_LENGTH 10
#define MAX_BUFFER_SLOT 6
#define MAX_LOOPS 30

string logbuf[MAX_BUFFER_SLOT];

int count;

void* wrlog(void *data)
{
    int id = *(int *) data;

    usleep(20);
    cout << "wrlog(): " << id << "\n";fflush(stdout);
 
    return 0;
}


void flushlog() 
{
    int i;

    cout << "flushlog()\n";

    for (i = 0; i < count; i++) {
       std::cout << "Slot " << i << ": " << logbuf[i] << "\n";
       logbuf[i] = std::to_string(-1);
    }
    fflush(stdout);

    /* Reset buffer */
    count = 0;

    return;

}

void timer_start(std::function<void(void)> func, unsigned int interval)
{
    std::thread([func, interval]() {
        while (true)
        {
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}

int main()
{
   int i;
   count = 0;
   pthread_t tid[MAX_LOOPS];
   int id[MAX_LOOPS];

   /* Setup periodically invoke flushlog() */
   timer_start(flushlog, 50);

   /* Asynchronous invoke task writelog */
   for (i = 0; i < MAX_LOOPS; i++) {
     id[i] = i; 
     pthread_create(&tid[i], NULL, wrlog, (void *) &id[i]);
   }

   for (i = 0; i < MAX_LOOPS; i++)
     pthread_join(tid[i], NULL);

   sleep(5);

   return 0;
}
