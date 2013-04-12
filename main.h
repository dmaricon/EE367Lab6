#ifndef MAIN_H
#define MAIN_H

#define DEBUG

#define PAYLOAD_LENGTH 200 /* Maximum payload size */

typedef struct { /* Packet buffer */
   int srcaddr;  /* Source address */
   int dstaddr;  /* Destination addres */
   int length;   /* Length of packet */
   char payload[PAYLOAD_LENGTH + 1];  /* Payload section */
   int valid;   /* Indicates if the contents is valid */ 
   int new;     /* Indicates if the contents has been downloaded */
   int linkIndex; /* Used by switch only */
} packetBuffer;

#endif
