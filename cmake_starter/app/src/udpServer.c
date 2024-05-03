#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include "udpServer.h"
#include <unistd.h>
#include "controller.h"
#include "rotation.h"
#include "shutdown.h"

#define MAX_LEN 1500
#define PORT 12345
#define MAX_LEN_COMMAND 4096
#define NUM_PER_LINE 10

static pthread_t serverThread;

static bool *running; // flag for ending the program


static char* processCommand(const char* command) {
    char *response = malloc(MAX_LEN);
    // printf(command);
    if (strncmp(command, "right", strlen("right")) == 0)
    {
        snprintf(response, MAX_LEN, "right.\n");
        turnRight();    
    } else if (strncmp(command, "left", strlen("left")) == 0)
    {
        snprintf(response, MAX_LEN, "left.\n");
        turnLeft();
    
    } else if (strncmp(command, "forward", strlen("forward")) == 0)
    {
        snprintf(response, MAX_LEN, "forward.\n");
        moveForward();
    
    } else if (strncmp(command, "backward", strlen("backward")) == 0)
    {
        snprintf(response, MAX_LEN, "backward.\n");
        moveBackward();
    
    } else if (strncmp(command, "stop", strlen("stop")) == 0)
    {
        // printf("initiate_stop()\n");
        snprintf(response, MAX_LEN, "stop.\n");
        stop();    
    }

    ////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

     else if (strncmp(command, "rotation_left", strlen("rotation_left")) == 0)
    {
        snprintf(response, MAX_LEN, "left rotation.\n");
        RotateToLeft();
    }
     else if (strncmp(command, "rotation_right", strlen("rotation_right")) == 0)
    {
        snprintf(response, MAX_LEN, "right rotation.\n");
        RotateToRight();
    }
     else if (strncmp(command, "rotation_up", strlen("rotation_up")) == 0)
    {
        snprintf(response, MAX_LEN, "upward rotation.\n");
        RotateUpward();
    }
     else if (strncmp(command, "rotation_down", strlen("rotation_down")) == 0)
    {
        snprintf(response, MAX_LEN, "downward rotation.\n");
        RotateDownward();
    }

    // ////////////////////////////////////////////////////////////////////////////
    // ///////////////////////////////////////////////////////////////////////////

    else if (strncmp(command, "terminate_program", strlen("terminate_program")) == 0)
    {
        // printf("called to terminate");
        snprintf(response, MAX_LEN, "Program terminating.\n");
        shutdown_signal();
    } 
    else {
        snprintf(response, MAX_LEN, "Error: Please enter a valid command!");
    }

    return response;
}

static void* server_logic() {
    
    // Address structure learned from Brian Fraser's notes
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    // Create and bind to socket
    int socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);
    bind(socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));

    // Receive data learned from Brian Fraser's notes
    struct sockaddr_in sinRemote;
    char previousCommand[MAX_LEN_COMMAND] = " ";
    
    while (*running)
    {
        unsigned int sin_len = sizeof(sinRemote);
        char messageRx[MAX_LEN_COMMAND];

        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(socketDescriptor, &fds);

        // Set timeout to zero for non-blocking check
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        // Check if there is data available to read or if *running is false
        int ready = select(socketDescriptor + 1, &fds, NULL, NULL, &timeout);

        if (ready == -1)
        {
            // Error occurred in select
            // Handle error here
        }
        else if (ready > 0)
        {
            // Data is available to read
            int bytesRx = recvfrom(socketDescriptor, messageRx, MAX_LEN_COMMAND - 1, 0, (struct sockaddr*) &sinRemote, &sin_len);
            messageRx[bytesRx] = 0;
            // Process received data here
            
            // Check if command is a blank input
            if (strncmp(messageRx, "\n", strlen("\n")) == 0)
            {
                snprintf(messageRx, MAX_LEN_COMMAND, previousCommand);
            } else {
                snprintf(previousCommand, bytesRx, messageRx);
            }
            // printf(messageRx);
            char* messageTx = processCommand(messageRx);
            sin_len = sizeof(sinRemote);
            sendto(socketDescriptor, messageTx, strlen(messageTx), 0, (struct sockaddr*) &sinRemote, sin_len);
            free(messageTx);
        }
        else if (!*running)
        {
            // *running became false, exit the loop
            break;
        }
    }
}

void server_init(bool *isRunning) {
    running = isRunning;
    pthread_create(&serverThread, NULL, server_logic, NULL);
}

void server_shutdown(void) {
    pthread_join(serverThread, NULL);
}
