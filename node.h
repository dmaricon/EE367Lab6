#ifndef NODE_H
#define NODE_H

#include "main.h"

typedef int Entry;

typedef struct Node{
	Entry data;
	struct Node* next;
} Node;

Node* newNode();
void deleteNode(Node* nodeptr);

#endif
