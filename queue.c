#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void initQ(Queue* q)
{
	q->head = q->tail = NULL;
}

void in(Queue* q,Entry e)
{
	Node* new = newNode();
	new->data = e;
	new->next = NULL;

	if(isEmpty(q))
		q->head = new;
	else
		q->tail->next = new;
	q->tail = new;
}

Entry out(Queue* q)
{
	Node* node;
	Entry data;

	if(isEmpty(q)){
		printf("ERROR: Queue is empty!\n");
		return;
	}

	node = q->head;
	data = node->data;
	q->head = q->head->next;
	deleteNode(node);
	return data;
}

int isEmpty(Queue* q)
{
	return(q->head==NULL);
}

