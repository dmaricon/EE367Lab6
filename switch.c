#include <stdio.h>
#include "switch.h"
#include "main.h"
#include "table.h"
#include "link.h"

#define DEBUG

void switchInit(switchState* sstate,int switchid)
{
	int i;
	sstate->switchid = switchid;
	initQ(&(sstate->packetQueue));
	for(i=0;i<TABLESIZE;i++)
		sstate->fTable[i].valid = 0;
}

void switchMain(switchState* sstate)
{
	packetBuffer tmpbuff;
	int i,j;
	int received;
	while(1){
		//check incoming links for packets
		for(i=0;i<NUMHOSTS;i++){
			linkReceive(&(sstate->linkin[i]),&tmpbuff);

			//if packet is received, update table and store in packet queue
			if(tmpbuff.valid && tmpbuff.new){

				tmpbuff.linkIndex = i;
				//check forwarding table for sender's address
				for(j=0;j<TABLESIZE &&
					!(sstate->fTable[j].valid==1 &&
						sstate->fTable[j].dstAddr == tmpbuff.srcaddr);j++);
				//if found and valid, update linkout
				if(j<TABLESIZE)
					sstate->fTable[j].linkout = i;
				//otherwise make a new entry
				else
					for(j=0;j<TABLESIZE && sstate->fTable[j].valid==1;j++);
						if(j!=TABLESIZE){
							sstate->fTable[j].valid = 1;
							sstate->fTable[j].dstAddr = tmpbuff.srcaddr;
							sstate->fTable[j].linkout = i;
						}

				in(&(sstate->packetQueue),tmpbuff);
#ifdef DEBUG
				printf("Forwarding Table:\n");
				printf("D L\n");
				for(j=0;j<TABLESIZE;j++){
					if(sstate->fTable[j].valid)
					printf("%d %d\n",sstate->fTable[j].dstAddr,sstate->fTable[j].linkout);
				}
#endif
			}
		}
		//check packet queue for transmissions, and transmit one
		if(!isEmpty(&(sstate->packetQueue))){
			tmpbuff = out(&(sstate->packetQueue));
			
			//check table for destination address
			for(i=0;i<TABLESIZE &&
				!(sstate->fTable[i].valid &&
					sstate->fTable[i].dstAddr == tmpbuff.dstaddr);i++);
			//if found, send along link
			if(i<TABLESIZE)
				linkSend(&(sstate->linkout[i]),&tmpbuff);
			//otherwise send on all links
			else{
				for(i=0;i<NUMHOSTS;i++)
					if(i!=tmpbuff.linkIndex)
						linkSend(&(sstate->linkout[i]),&tmpbuff);
			}
		}
		usleep(10000);
	}
}
