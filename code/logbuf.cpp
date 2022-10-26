#include <chrono>
#include <thread>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <functional>

// using namespace std;

#define MAX_LOG_LENGTH 10
#define MAX_BUFFER_SLOT 6
#define MAX_LOOPS 30

std::string logbuf[MAX_BUFFER_SLOT];

pthread_mutex_t count_mutex;
pthread_cond_t count_cv;
// sem_t _full, _empty;

int count;

void *wrlog(void *data)
{
    // sem_wait(&_empty);
    int id = *(int *)data;
    pthread_mutex_lock(&count_mutex);

    if (count == MAX_BUFFER_SLOT)
    {
        pthread_cond_signal(&count_cv);
    }

    // sem_post(&_full);
    else
    {
        logbuf[count] = std::to_string(id);
        // std::cout << "wrlog(): " << id << "\n";
        ++count;
    }
    pthread_mutex_unlock(&count_mutex);

    usleep(20);
    fflush(stdout);

    return 0;
}

void flushlog()
{
    int i;

    // std::cout << "flushlog()\n";

    pthread_cond_wait(&count_cv, &count_mutex);

    for (i = 0; i < count; i++)
    {
        std::cout << "Slot " << i << ": " << logbuf[i] << "\n";
        logbuf[i] = std::to_string(-1);
    }
    // pthread_mutex_unlock(&count_mutex);
    fflush(stdout);

    /* Reset buffer */
    count = 0;

    return;
}

void timer_start(std::function<void(void)> func, unsigned int interval)
{
    std::thread([func, interval]()
                {
        while (true)
        {
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        } })
        .detach();
}

int main()
{
    int i;
    count = 0;
    pthread_t tid[MAX_LOOPS];
    int id[MAX_LOOPS];

    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&count_cv, NULL);
    // sem_init(&_full, 0, 0);
    // sem_init(&_empty, 0, MAX_BUFFER_SLOT);

    /* Setup periodically invoke flushlog() */
    timer_start(flushlog, 50);

    /* Asynchronous invoke task writelog */
    for (i = 0; i < MAX_LOOPS; i++)
    {
        id[i] = i;
        pthread_create(&tid[i], NULL, wrlog, (void *)&id[i]);
    }
i
    for (i = 0; i < MAX_LOOPS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    sleep(5);

    return 0;
}
