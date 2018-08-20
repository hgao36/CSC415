#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
//#include <dispatch/dispatch.h> 
#include <semaphore.h>

int bufSize, itemsPerProducer;
int itemsPerConsumer,itemsRemain;
int totalProduced = 0,totalConsumed = 0;
int Ptime, Ctime;
static int bufIndex = 0,checkIndex = 0;
int* buffer;
int* check;
int item = 1;

//dispatch_semaphore_t empty;
//dispatch_semaphore_t full;
sem_t empty;
sem_t full;

pthread_mutex_t lock;

void producer(void* id);
void consumer(void* id);
int isVaild();

struct thread_node{
	pthread_t tid;
	int id;
};



int main(int argc, char* argv[]) {
	

	struct timeval start, end;
	time_t time;
	gettimeofday(&start, NULL);

	//check the input

	if(argc != 7){
		fprintf(stderr,"Please enter 6 arguments.");
	}

	bufSize = atoi(argv[1]);
	int producerNumber = atoi(argv[2]);
	int consumerNumber = atoi(argv[3]);
	itemsPerProducer = atoi(argv[4]);
	Ptime = atoi(argv[5]);
	Ctime = atoi(argv[6]);

	int checkSize = producerNumber * itemsPerProducer;
	buffer = (int*)malloc(sizeof(int)* bufSize);

	if(buffer == NULL){
		fprintf(stderr, "Error allocating buffer size\n");
	}

	check = (int*)malloc(sizeof(int)* checkSize);

	if(check == NULL){
		fprintf(stderr, "Error allocating check size\n");
	}

	itemsPerConsumer = (producerNumber * itemsPerProducer) / consumerNumber;

	fprintf(stderr, "Input is %d, %d, %d, %d, %d, %d.\n", bufSize, producerNumber, consumerNumber, itemsPerProducer, Ptime, Ctime);

	if(pthread_mutex_init(&lock,NULL) < 0){
		fprintf(stderr, "Lock's creating failed\n");;
		return 1;
	}

	//init semaphore 
	//empty = dispatch_semaphore_create(bufSize); 
	if(sem_init(&empty,0,bufSize) < 0){
		fprintf(stderr, "semaphore init empty failed\n");
	}
	//full = dispatch_semaphore_create(0); 
	if(sem_init(&full,0,0) < 0 ){
		fprintf(stderr, "semaphore init full failed\n");
	}


	int i,rc;
	//create thread_node with tid and their id
	struct thread_node pros[producerNumber];
	struct thread_node cons[consumerNumber];


	//create producer threads
	for(i = 0; i < producerNumber; i++){
		pros[i].id = i + 1;
		rc = pthread_create(&pros[i].tid, NULL, (void *)producer, (void *) &pros[i].id);
		if(rc < 0){
			fprintf(stderr, "%s\n", "producer pthread_create error.");
			return 1;
		}
	}

	//create consumer threads
	for(i = 0; i < consumerNumber; i++){
		cons[i].id = i + 1;
		rc = pthread_create(&cons[i].tid, NULL, (void *)consumer,(void *) &cons[i].id);
		if(rc < 0){
			fprintf(stderr, "%s\n", "consumer pthread_create error.");
			return 1;
		}
	}


	//join producer threads
	for(i = 0; i < producerNumber; i++){
		rc = pthread_join(pros[i].tid, NULL);
		if(rc < 0){
			fprintf(stderr,"%s\n","producer pthread_join error.");
			return 1;
		}
	}

	//join consumer threads
	for(i = 0; i < consumerNumber; i++){
		rc = pthread_join(cons[i].tid, NULL);
		if(rc < 0){
			fprintf(stderr,"%s\n","consumer pthread_join error.");
			return 1;
		}
	}

	

	int vaild = isVaild();
	if(vaild){
		fprintf(stderr, "Producer produced and Consumer consumed matches.\n");
	}
	else{
		fprintf(stderr, "Producer produced and Consumer consumed does not match.\n");
	}


	gettimeofday(&end,NULL);

	time = (end.tv_sec*1000000 - start.tv_sec*1000000) / CLOCKS_PER_SEC;

	fprintf(stderr, "%s%ld\n","Total running time is : ", time);

	//destory the full and empty semaphores
	//dispatch_release(full);
	//dispatch_release(empty);
	sem_destroy(&full);
	sem_destroy(&empty);

	//free memory 
	//free(pros);
	//free(cons);
	free(buffer);
	free(check);
	


	return 0;
}

//producer thread function
void producer(void* id){
	int *ptr = (int *) id;
	int number = *ptr;

	int itemProduced;
	int i;
	for(i = 0; i < itemsPerProducer; i++){
		
		
		//dispatch_semaphore_wait(empty, DISPATCH_TIME_FOREVER);
		sem_wait(&empty);
		pthread_mutex_lock(&lock);
		itemProduced = item++;

		
		buffer[bufIndex++] = itemProduced;

		fprintf(stderr, "Producer #%d produced #%d\n", number , itemProduced);

		totalProduced++;
		
		pthread_mutex_unlock(&lock);
		//dispatch_semaphore_signal(full);
		sem_post(&full);
		
		sleep(Ptime);
	}
}

//consumer thread function
void consumer(void* id){
	int itemConsumed;
	int *ptr = (int *) id;
	int number = *ptr;
	int i;
	for(i = 0; i < itemsPerConsumer; i++){


		//dispatch_semaphore_wait(full, DISPATCH_TIME_FOREVER);
		sem_wait(&full);
		pthread_mutex_lock(&lock);
		
		itemConsumed = buffer[--bufIndex];

		fprintf(stderr, "Consumer #%d consumed #%d\n", number, itemConsumed);
		check[checkIndex++] = itemConsumed;   // bug fixed

		//checkIndex++;	
		totalConsumed++;

		pthread_mutex_unlock(&lock);
		//dispatch_semaphore_signal(empty);
		sem_post(&empty);
		
		sleep(Ctime);
	}

}

int comp( const void * a, const void * b){
	return (*(int*)a - *(int*)b);
}

//function to check if the check array matches the number produced 
int isVaild(){
	int i;
	//sort the check array
	qsort(check, checkIndex, sizeof(int),comp);
	//set flag to true
	int flag = 1,temp;

	//if number produced not equal to number consumced, set flag to false
	if(totalConsumed != totalProduced){
		flag = 0;
	}
	//check every element of the check array if they are all matches
	else{
		for( i = 0; i < totalProduced ; i++){
			temp = i + 1 ;
			fprintf(stderr, "Produced %d | Consumed %d\n", temp, check[i]);
			if( temp != check[i]){
				flag = 0;
			}
		}
	}
	return flag;
}


