#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_SIZE 10

typedef struct 
{
	char type;
	int amount;
	char unit;
}item;

item buffer[BUFFER_SIZE];
int first = 0;
int last =0;
sem_t sem;

void produce(item *i) 
{
	while ((first + 1) % BUFFER_SIZE == last)
	{}
	sem_wait(&sem);
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
	sem_post(&sem);	
}

item *consume() 
{
	item *i = malloc(sizeof(item));
	while (first == last) 
	{}
	sem_wait(&sem); 	
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	sem_post(&sem);	
	return i;
}

void* add(void* food)
{
  item ga;
	ga.type = 'c'; // chien
	ga.amount = 2;
	ga.unit = 'c'; // can

	item khoai;
	khoai.type = 'c'; // chien
	khoai.amount = 1; 
	khoai.unit = 'c'; // can

	item coca;
	coca.type = 't'; // tuoi
	coca.amount = 2;
	coca.unit = 'l'; // lon 

  produce(&ga);
	printf("First value after add ga: %d\n",first);
	printf("Last value after add ga: %d\n",last);

  produce(&khoai);
	printf("First value after add khoai: %d\n",first);
	printf("Last value after add khoai: %d\n",last); 
	
  produce(&coca);
	printf("First value after add coca: %d\n",first);
	printf("Last value after add coca: %d\n",last); 
	
  return NULL;
}

void* eat(void* food)
{
  int i;
  for(i=0 ; i<2 ; i++)
  {
    item* pfree = consume();
	  free(pfree);

	  printf("First value after consume: %d\n",first);
	  printf("Last value after consume: %d\n",last); 
  }  

  return NULL;
}

int main()
{
	sem_init (&sem, 0, 1);

	pthread_t addThread;
	pthread_create(&addThread,NULL,add,NULL);
	pthread_join(addThread,NULL);

	pthread_t eatThread;
	pthread_create(&eatThread,NULL,eat,NULL);
	pthread_join(eatThread,NULL);

	sem_destroy(&sem);

	return 0;
}