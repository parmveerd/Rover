// Main program to build the beat_box application
// Has main();.

#include <stdio.h>
#include "udpServer.h"
#include <stdlib.h>
#include <stdbool.h>
#include "system.h"
#include "rotation.h"
#include "camera.h"
#include "shutdown.h"
#include "xboxController.h"
static bool isRunning = true;
int main()
{
    // for car motors 
    runConfig_pin();
    init_XboxController(&isRunning);
    // for rotary motors
    Configure_Rotation();
    
    // for communication
    server_init(&isRunning);
    
    // for video streaming
    camera_init(&isRunning);
    shutdown_init(&isRunning);
    
    shutdown_wait();
    // cleanup
    shutdown_XboxController();
    server_shutdown();
    camera_cleanup();
    return 0;
}