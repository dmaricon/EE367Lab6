#ifndef SWITCH_H
#define SWITCH_H

#include "queue.h"
#include "link.h"
#include "table.h"

#define TABLESIZE 100

typedef struct {
	int switchid;
	LinkInfo linkin[NUMHOSTS]; //incoming links
	LinkInfo linkout[NUMHOSTS]; // outgoing links
	Queue packetQueue; //incoming packets
	TableEntry fTable[TABLESIZE]; //forwarding table
} switchState;

void switchInit(switchState* sstate,int switchid);
void switchMain(switchState* sstate);

#endif
