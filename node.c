#include "node.h"
#include <stdlib.h>

Node* newNode()
{
	return (Node*)malloc(sizeof(Node));
}

void deleteNode(Node* nodeptr)
{
	free(nodeptr);
}

