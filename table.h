#ifndef TABLE_H
#define TABLE_H

typedef struct{
	int valid; //valid indicator
	int dstAddr; //address for host node
	int linkout; //outgoing link to host
} TableEntry;

#endif
