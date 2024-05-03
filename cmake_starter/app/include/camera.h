#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <pthread.h>
#include <stdbool.h>
// Starts the server
void camera_init(bool* isRunning);
// Shuts down the server
void camera_cleanup(void);

#endif