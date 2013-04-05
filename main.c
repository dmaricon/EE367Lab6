#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>
#include <fcntl.h>

#include "main.h"
#include "utilities.h"
#include "link.h"
#include "man.h"
#include "host.h"
#include "net.h"
#include "switch.h"
#include "table.h"

#define EMPTY_ADDR  0xffff  /* Indicates that the empty address */
                             /* It also indicates that the broadcast address */
#define MAXBUFFER 1000
#define PIPEWRITE 1 
#define PIPEREAD  0

void main()
{
hostState hstate;             /* The host's state */
switchState sstate;
linkArrayType linkArray;
manLinkArrayType manLinkArray;

pid_t pid;  /* Process id */
int physid; /* Physical ID of host */
int switchid;
int i;
int k;

/* 
 * Create nonblocking (pipes) between manager and hosts 
 * assuming that hosts have physical IDs 0, 1, ... 
 */
manLinkArray.numlinks = NUMHOSTS;
netCreateConnections(& manLinkArray);

/* Create links between nodes but not setting their end nodes */

linkArray.numlinks = NUMHOSTS*2;
netCreateLinks(& linkArray);

/* Set the end nodes of the links */

netSetNetworkTopology(& linkArray);

/* Create nodes and spawn their own processes, one process per node */ 

for(switchid=1;switchid<NUMSWITCHES+1;switchid++){
	pid = fork();

	if (pid == -1) {
		printf("Error:  the fork() failed\n");
		return;
	}

	if(pid==0){ // child process -- switch
		printf("Switch process started\n");
		switchInit(&sstate,switchid);

		k = netSwitchOutLink(&linkArray,switchid);
		for(i=0;i<NUMHOSTS;i++){
			sstate.linkout[i] = linkArray.link[k];
			k += 2;
		}
		
		k = netSwitchInLink(&linkArray,switchid);
		for(i=0;i<NUMHOSTS;i++){
			sstate.linkin[i] = linkArray.link[k];
			k += 2;
		}

		netCloseSwitchOtherLinks(&linkArray,switchid);

		printf("Switch loop started\n");
		switchMain(&sstate);
	}
}

for (physid = 0; physid < NUMHOSTS; physid++) {

   pid = fork();

   if (pid == -1) {
      printf("Error:  the fork() failed\n");
      return;
   }
   else if (pid == 0) { /* The child process -- a host node */

      hostInit(&hstate, physid);              /* Initialize host's state */

      /* Initialize the connection to the manager */ 
      hstate.manLink = manLinkArray.link[physid];

      /* 
       * Close all connections not connect to the host
       * Also close the manager's side of connections to host
       */
      netCloseConnections(& manLinkArray, physid);

      /* Initialize the host's incident communication links */

      k = netHostOutLink(&linkArray, physid); /* Host's outgoing link */
      hstate.linkout = linkArray.link[k];

      k = netHostInLink(&linkArray, physid); /* Host's incoming link */
      hstate.linkin = linkArray.link[k];

      /* Close all other links -- not connected to the host */
      netCloseHostOtherLinks(& linkArray, physid);

      /* Go to the main loop of the host node */
      hostMain(&hstate);
   }  
}

/* Manager */

/* 
 * The manager is connected to the hosts and doesn't
 * need the links between nodes
 */

/* Close all links between nodes */
netCloseLinks(&linkArray);

/* Close the host's side of connections between a host and manager */
netCloseManConnections(&manLinkArray);

/* Go to main loop for the manager */
manMain(& manLinkArray);

/* 
 * We reach here if the user types the "q" (quit) command.
 * Now if we don't do anything, the child processes will continue even
 * after we terminate the parent process.  That's because these
 * child proceses are running an infinite loop and do not exit 
 * properly.  Since they have no parent, and no way of controlling
 * them, they are called "zombie" processes.  Actually, to get rid
 * of them you would list your processes using the LINUX command
 * "ps -x".  Then kill them one by one using the "kill" command.  
 * To use the kill the command just type "kill" and the process ID (PID).
 *
 * The following system call will kill all the children processes, so
 * that saves us some manual labor
 */
kill(0, SIGKILL); /* Kill all processes */
}




