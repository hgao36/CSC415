#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define NUM_THREADS 10
int global = 0;

/**	
 * Can use the following struct for
 * the nanosleep function.
 * the first value is sleep time in seconds
 * the second vaue is sleep time in nanoseconds.
 * 
 * struct timespec ts = {2, 0 };
 * 
 * you can call nano sleep as nanosleep(&ts, NULL);
*/

struct timespec ts = {2, 0};

void thread_Fun(void *arg);

struct thread_node{
	pthread_t tid;
	int thread_id;
};


int main() {

	struct thread_node thread[NUM_THREADS];
	int rc,i;
	

	fprintf(stderr, "Thread Program for test race condition executing.\n");

	for(i = 0 ; i < 10; i++){

		thread[i].thread_id = i + 1;
		rc = pthread_create(&thread[i].tid, NULL, (void *)thread_Fun, (void *) &thread[i].thread_id);
		if(rc < 0){
			fprintf(stderr, "%s\n", "pthread_create errer.");
		}
	}

	for(i = 0; i < 10; i++){
		pthread_join(thread[i].tid, 0);
	}

	fprintf(stderr, "Result is %d\n", global);
}

void thread_Fun(void* arg){
	int local_sum = global;
	int *ptr = (int *) arg;
	int index = *ptr;

	fprintf(stderr, "Hello, I am thread # %d .\n", index);
	
	nanosleep(&ts,NULL);

	fprintf(stderr, "This is thread # %d with local value: %d.\n", index, local_sum);
	local_sum += 10;

	//nanosleep(&ts,NULL);
	
	fprintf(stderr, "This is thread # %d with final local value: %d.\n", index, local_sum);
	global = local_sum;
	
	pthread_exit(0);
}


