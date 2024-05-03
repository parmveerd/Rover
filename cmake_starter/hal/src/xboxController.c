#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "joystick.h"
#include "system.h"
#include <errno.h>


#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <pthread.h>
#include "controller.h"
#include "rotation.h"
#include "shutdown.h"

typedef enum
{
    Y_AXIS = 7,
    X_AXIS = 6,
} DPadState;

typedef enum
{
    BUTTON_A = 0,
    BUTTON_B = 1,
    BUTTON_X = 2,
    BUTTON_Y = 3,
    BUTTON_LB = 4,
    BUTTON_RB = 5,
    BUTTON_BACK = 6,
    BUTTON_START = 7,
} Button;

static int joystickFd = -1;
pthread_t pollingThread;

// Polling thread that controls the car based on controller input
static void *pollController();
static bool *running;

// // GPIO functions for car
// static void moveBackward();
// static void moveForward();
// static void turnLeft();
// static void turnRight();
// static void stop();

static bool connected = false;

void join(){
    joystickFd = open("/dev/input/js0", O_RDONLY);
    if(joystickFd!= -1){
        connected=true;
    }
    else connected=false;
}

void init_XboxController(bool *isRunning)
{
    running = isRunning;
    join();
    if (pthread_create(&pollingThread, NULL, pollController, NULL))
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
}

static void *pollController()
{

    struct js_event event;

    printf("-Xbone Controller Initialized-\n");

    while (*running)
    {
        // while(!connected && *running){
        //     join();
        // }
        if (!(*running)){
            break;
        }


        // Set the joystickFd as non-blocking
        int flags = fcntl(joystickFd, F_GETFL, 0);
        if (flags == -1) {
            perror("fcntl F_GETFL");
            exit(EXIT_FAILURE);
        }
        if (fcntl(joystickFd, F_SETFL, flags | O_NONBLOCK) == -1) {
            perror("fcntl F_SETFL");
            exit(EXIT_FAILURE);
        }

        // Set up the file descriptor set for select
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(joystickFd, &readfds);

        // Set timeout value
        struct timeval timeout;
        timeout.tv_sec = 1; // Timeout in seconds
        timeout.tv_usec = 0; // Additional microseconds

        // Wait for data to become available on joystickFd or timeout
        int ret = select(joystickFd + 1, &readfds, NULL, NULL, &timeout);
        if (ret == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        } else if (ret == 0) {

            // Timeout occurred
            // Handle this case (e.g., break out of the loop)
            if(!(*running)) break;

        } else {

            // Data is available to read from joystickFd
            ssize_t bytes_read = read(joystickFd, &event, sizeof(event));
            
            if (bytes_read == -1 && errno != EAGAIN && errno != EWOULDBLOCK) {
                // perror("read");
                // exit(EXIT_FAILURE);
            }
            else if (bytes_read != sizeof(event)) {
                // No data available or incomplete read
                // Handle this case accordingly
            }
            else 
            {
                // Joystick event read successfully
                // Process the event here

                // Check if it's a button press or direction input
                if (event.type == JS_EVENT_BUTTON && event.value == 1)
                {
                    switch (event.number)
                    {
                    case BUTTON_A:
                        // Handle button A press
                        RotateDownward();
                        break;
                    case BUTTON_B:
                        // Handle button B press
                        RotateToRight();
                        break;
                    case BUTTON_X:
                        // Handle button X press
                        RotateToLeft();
                        break;
                    case BUTTON_Y:
                        // Handle button Y press
                        RotateUpward();
                        break;
                    case BUTTON_START:
                        // Handle Start button press
                        // Shutdown Module
                        shutdown_signal();
                        break;
                    case BUTTON_BACK:
                        // Handle Back button press
                        break;
                    // Add more button cases as needed
                    default:
                        break;
                    }
                }
                else if (event.type == JS_EVENT_AXIS)
                {
                    if (event.number == X_AXIS || event.number == Y_AXIS)
                    {
                        if (event.number == Y_AXIS)
                        {
                            if (event.value < 0)
                            {
                                moveForward();
                            }
                            else if (event.value > 0)
                            {
                                moveBackward();
                            }
                            else{
                                stop();
                            }
                        }
                        else if (event.number == X_AXIS)
                        {
                            if (event.value < 0)
                            {
                                turnLeft();
                            }
                            else if (event.value > 0)
                            {
                                turnRight();
                            }
                            else{
                                stop();
                            }
                        }
                        else{
                                stop();
                            }
                    }
                    else{
                        stop();
                    }
                }
            }
        }
    }
}

void shutdown_XboxController()
{
    pthread_join(pollingThread, NULL);
    close(joystickFd);
}
// static void moveBackward()
// {
//     write_number(GPIO67_P8_08, 0);
//     write_number(GPIO66_P8_07, 1);
//     // (Motor B - backward)
//     write_number(GPIO68_P8_10, 0);
//     write_number(GPIO69_P8_09, 1);
// }
// static void moveForward()
// {
//     // (Motor A - forward)
//     write_number(GPIO66_P8_07, 0);
//     write_number(GPIO67_P8_08, 1);
//     // (Motor B - forward)
//     write_number(GPIO69_P8_09, 0);
//     write_number(GPIO68_P8_10, 1);
// }

// static void turnLeft()
// {
//     write_number(GPIO67_P8_08, 0);
//     write_number(GPIO66_P8_07, 1);
//     // (Motor B - forward)
//     write_number(GPIO69_P8_09, 0);
//     write_number(GPIO68_P8_10, 1);
// }
// static void turnRight()
// {
//     // (Motor A - forward)
//     write_number(GPIO66_P8_07, 0);
//     write_number(GPIO67_P8_08, 1);
//     // (Motor B - backward)
//     write_number(GPIO68_P8_10, 0);
//     write_number(GPIO69_P8_09, 1);
// }
// static void stop()
// {
//     // (Motor A - stop)
//     write_number(GPIO66_P8_07, 0);
//     write_number(GPIO67_P8_08, 0);
//     // (Motor B - stop)
//     write_number(GPIO69_P8_09, 0);
//     write_number(GPIO68_P8_10, 0);
// }
