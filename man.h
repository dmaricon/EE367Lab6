#ifndef MAN_H
#define MAN_H

#include "link.h"

typedef struct{ /* Connection used by the manager to a host */ 
   int toHost[2]; /* Pipe link to host */
   int fromHost[2]; /*  Pipe link from host */
} managerLink;

typedef struct {
   int numlinks;
   managerLink link[NUMHOSTS];
} manLinkArrayType;

/* 
 * Main loop for the manager.  It repeatedly gets comand from
 * the user and then executes the command
 */
void manMain(manLinkArrayType * manLinkArray);

#endif
