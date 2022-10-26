#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define N 5

pthread_mutex_t mtx;
pthread_cond_t chopstick[N];

void *philosopher(void*);
void eat(int);
void think(int);
int main()
{
   int i, a[N];
   pthread_t tid[N];

   /* BEGIN PROTECTION MECHANISM */
   //pthread_mutex_init(&mtx, NULL);

   //for (i = 0; i < N; i++)
	   //pthread_cond_init(&chopstick[i], NULL);
   /* END PROTECTION MECHANISM */

   for (i = 0; i < 5; i++)
   {
      a[i] = i;
      pthread_create(&tid[i], NULL, philosopher, (void*) &a[i]);
   }

   for (i = 0; i < 5; i++)
      pthread_join(tid[i], NULL);
}

void *philosopher(void *num)
{
   int phil = *(int*) num;
   std::cout << "Philosopher " << phil << " has entered room\n";
	  
   while (1)
   {
      std::cout << "Philosopher " << phil << " takes fork " << phil
                << " and " << (phil + 1) % N<< " up\n";
      /* PROTECTION MECHANISM */
      //pthread_cond_wait(&chopstick[phil], &mtx);
      //pthread_cond_wait(&chopstick[(phil + 1) % N], &mtx);
			  
      eat(phil);
      sleep(2);

       /* PROTECTION MECHANISM */
      //pthread_cond_signal(&chopstick[phil]);
      //pthread_cond_signal(&chopstick[(phil + 1) % N]);
      std::cout << "Philosopher " << phil << " puts fork " << phil
                << " and " << (phil + 1) % N << " down\n";

	  think(phil);
	  sleep(1);
   }
}

void eat(int phil)
{
   std::cout << "Philosopher " << phil << " is eating\n";
}

void think(int phil)
{
   std::cout<< "Philosopher " << phil << " is thinking\n";
}
