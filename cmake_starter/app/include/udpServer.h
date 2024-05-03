// udpServer.h
// Module that controls the UDP server that receives and responds to commands

#ifndef _UDPSERVER_H_
#define _UDPSERVER_H_

#include <pthread.h>
#include <stdbool.h>
extern pthread_mutex_t programFinishMutex;

// Starts the server
void server_init(bool* isRunning);
// Shuts down the server
void server_shutdown(void);

#endif