//program iverts queue

#include "stdafx.h"
#include <malloc.h>
#include <conio.h>


#define LENGTH 100


struct Item
{
	int info;
	Item* previous;
	Item* next;
};


struct Queue
{
	Item* head;
	Item* tail;
	int amount;
};


Queue* initialize(Queue* queue);

Queue* addItem(Queue* queue, int info);

Queue* invert(Queue* queue);

void print(const Queue* queue);

Queue* removeItem(Queue* queue);

Queue* remove(Queue* queue);


int main()
{
	Queue* queue = NULL;

	queue = initialize(queue);

	for (int i = 1; i < LENGTH; i++)
		addItem(queue, i);

	printf("Initial queue order:\n");
	print(queue);
	
	invert(queue);

	printf("\n\nInverted queue order:\n");
	print(queue);

	queue = remove(queue);
	
	_getch();
	return 0;
}


Queue* initialize(Queue* queue)
{
	if (queue == NULL)
	{
		queue = (Queue*)malloc(sizeof(Queue));
		*queue = { NULL, NULL, 0 };
	}

	return queue;
}


Queue* addItem(Queue* queue, int info)
{
	Item* item = (Item*)malloc(sizeof(Item));

	item->info = info;
	item->previous = NULL;
	item->next = NULL;

	if (queue->head == NULL)
		queue->head = queue->tail = item;

	else
	{
		queue->tail->next = item;
		item->previous = queue->tail;
		queue->tail = item;
	}

	queue->amount++;

	return queue;
}


Queue* invert(Queue* queue)
{
	if (queue->head == NULL)
		return queue;

	Item* fromHead = (Item*)malloc(sizeof(Item));
	Item* fromTail = (Item*)malloc(sizeof(Item));

	fromHead = queue->head;
	fromTail = queue->tail;

	int offsetFromCenter = queue->amount / 2;
	while (offsetFromCenter > 0)
	{
		int buffer = fromHead->info;
		fromHead->info = fromTail->info;
		fromTail->info = buffer;

		fromHead = fromHead->next;
		fromTail = fromTail->previous;

		offsetFromCenter--;
	}

	return queue;
}


void print(const Queue* queue)
{
	Item* item = (Item*)malloc(sizeof(Item));

	item = queue->head;
	while (item != NULL)
	{
		printf("%d\t", item->info);
		item = item->next;
	}
	free(item);
}


Queue* removeItem(Queue* queue)
{
	if (queue->head == NULL)
		return queue;

	if (queue->head == queue->tail)
	{
		free(queue->head);
		queue->head = queue->tail = NULL;
	}

	else
	{
		Item* item = (Item*)malloc(sizeof(Item));

		item = queue->head;
		queue->head = item->next;
		queue->head->previous = NULL;
		free(item);
	}

	queue->amount--;

	return queue;
}


Queue* remove(Queue* queue)
{
	while (queue->head != NULL)
		removeItem(queue);

	free(queue);

	return NULL;
}

