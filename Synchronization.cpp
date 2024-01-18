/* 
 *	Author: Kaleb LuceWireman Lab3
 *	Class: CS3080 1001
 *      Template by: Dr. Rajaei
 *      Due: 11/2/23
 *
 */



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define NUM_THREADS 12		// Num Threads is 12

#define BSIZE 10		// Buffer size is 10
#define NUM_ITEMS 25		// Num Items to produce or consume

int buf[BSIZE];
int NextIn=0, NextOut=0;
int buffitems = 0;
int numitems;
int range;


void * producer(void *);	// function for producer thread
void * consumer(void *);	// function for consumer thread

pthread_t tid[NUM_THREADS];
pthread_mutex_t lock;
pthread_cond_t full;
pthread_cond_t empty;  
std::vector<int> totmin;
std::vector<int> totmax;
std::vector<double>  totavg;

int main( int argc, char *argv[3] ) 
{
	
	range = atoi(argv[2]);
	numitems =  atoi(argv[1]);
	

	int locMin = 0;
	int locMax = 0;
	double locAvg = 0.0;
	int i = 0;

	printf("\n **** Main Program creating threads ++++ \n");

	// Create threads
	for (int j = 0; j < NUM_THREADS / 2; j++){
	pthread_create(&tid[j], NULL, producer, NULL);
	i++;
	}
	for ( int j = NUM_THREADS / 2; j < NUM_THREADS; j++){
	pthread_create(&tid[j], NULL, consumer, NULL);
	i++;
	}
		

	

	// join threads;
	for (int j = 0; j < NUM_THREADS; j++)
	pthread_join(tid[j] , NULL);


	printf("\n *** main() reporting: all %d threads terminated \n\n ", i);
	
	locMin = totmin[0];
	locMax = totmax[0];

	for(int j = 0; j < NUM_THREADS / 2; j++){
	if (totmin[j] < locMin)
	locMin = totmin[j];
	if (totmax[j] > locMax)
	locMax = totmax[j];
	locAvg += totavg[j];

}
	locAvg /= 6.0;

	printf("Total Min is: %d, Total Max is: %d, Total Avg is %.2f \n" , locMin,locMax,locAvg);
	return 0; 

}  /* end main */

  

void * producer(void * parm)
{
	int num;
	int i;

	printf("\n ++++ Producer started ++++ \n");


	// loop 

	for(i = 0; i < numitems; i++){
		pthread_mutex_lock(&lock);

		while(buffitems >= 10)
		pthread_cond_wait(&empty, &lock);
		
		// produce item 
		num = (rand() % range) + 1;
		
		// place item in the buffer
		buf[NextIn] = num;
		NextIn = (NextIn + 1) % BSIZE;
		buffitems++;
		
		printf(" Produced item: %d\n", num);
		pthread_cond_signal(&full);
		

		pthread_mutex_unlock(&lock);
		// end loop
		}
	
	printf("\n +++ Producer exiting +++ \n");
	pthread_exit(0);
}    

void * consumer(void * parm)
{
	int min = 9999;
	int max = -9999;
	double avg = 0.0;
	int num;
	int i;

	printf("\n --- Consumer started --- \n");

        // loop
        	for(i = 0; i < numitems; i++){
		
		pthread_mutex_lock(&lock);
		
		while(buffitems <= 0)
		pthread_cond_wait(&full, &lock);
		
                // fetch an item from the buffer
		num = buf[NextOut];
		NextOut = (NextOut + 1) % BSIZE;
		buffitems--;
		//calc min max & avg
		if(num > max)
		max = num;

		if(num < min)
		min = num;

		avg += num;		

		printf(" Consuming item: %d\n", num);
		pthread_cond_signal(&empty);
	
		pthread_mutex_unlock(&lock);
		// end loop
		}
	avg /= (numitems * 1.0);
	printf("Consumer min: %d \n", min);
	printf("Consumer max: %d \n", max);
	printf("Consumer avg: %0.2f \n", avg);

	totmin.push_back(min);
	totmax.push_back(max);
	totavg.push_back(avg);

	printf("\n --- Consumer exiting ----\n");
	pthread_exit(0);
}


 
