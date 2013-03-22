#include "queue.h"
#include "node.h"
#include <stdio.h>

main()
{
	Queue q;
	int i;
	Node* n;

	n = newNode();
	n->data = 5;
	printf("%d\n",n->data);

	initQ(&q);

	for(i=0;i<100;i++)
		in(&q,i);
	printf("asdf\n");
	for(i=0;i<101;i++)
		printf("%d\n",out(&q));

	while(getchar()!='\n');

	for(i=0;i<20;i++)
		in(&q,i);

	for(i=0;i<5;i++)
		printf("%d\n",out(&q));

	while(getchar()!='\n');

	for(i=0;i<15;i++)
		printf("%d\n",out(&q));
}
