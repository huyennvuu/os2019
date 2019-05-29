#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void produce(item *i) 
{
	while ((first + 1) % BUFFER_SIZE == last)
	{}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}

item *consume() 
{
	item *i = malloc(sizeof(item));
	while (first == last) 
	{}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}

int main()
{
	item ga;
	ga.type = 'c'; // chien
	ga.amount = 2;
	ga.unit = 'c'; // can

	item khoai;
	khoai.type = 'c'; // chien
	khoai.amount = 1; 
	khoai.unit = 'c'; //vcan

	produce(&ga);
	printf("First value after add ga: %d\n",first);
	printf("Last value after add ga: %d\n",last);
	
	
	produce(&khoai);
	printf("First value after add khoai: %d\n",first);
	printf("Last value after add khoai: %d\n",last); 
	
	item* pfree = consume();
	free(pfree);

	printf("First value after consume: %d\n",first);
	printf("Last value after consume: %d\n",last); 
	

	return 0;
}