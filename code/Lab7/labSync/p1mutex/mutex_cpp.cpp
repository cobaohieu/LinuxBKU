#include <iostream>
#include <pthread.h>
using namespace std;

int MAX_COUNT = 1e9;
static int count = 0;

void *f_count(void *_id) {
   int i;
   int id = *(int *)(_id);

   for (i = 0; i < MAX_COUNT; i++) {
         count = count + 1;
   }
	  
   cout << "Thread " << id << ": holding " << count << "\n";
 }

int main() {
  pthread_t thread1, thread2;
  int id1,id2;

  id1=1;
  id2=2;

  /* Create independent threads each of which will execute function */
  pthread_create( &thread1, NULL, &f_count, (void *) &id1);
  pthread_create( &thread2, NULL, &f_count, (void *) &id2);

  // Wait for thread th1 finish
  pthread_join( thread1, NULL);

  // Wait for thread th1 finish
  pthread_join( thread2, NULL);

  return 0;
}
