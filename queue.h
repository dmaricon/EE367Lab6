#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

typedef struct{
	Node* head;
	Node* tail;
} Queue;

void initQ(Queue* q);

void in(Queue* q,Entry e);
Entry out(Queue* q);

int isEmpty(Queue* q);

#endif
