#include "switch.h"

void switchInit(switchState* sstate,int switchid)
{
	int i;
	sstate->switchid = switchid;
	initQ(&(sstate->packetQueue));
	for(i=0;i<NUMHOSTS;i++)
		sstate->fTable[i].valid = 0;
}

void switchMain(switchState* state)
{
	while(1){
		
	}
}
