#include "system.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


// (One side motor A)
#define GPIO66_P8_07_dir "/sys/class/gpio/gpio66/direction"
#define GPIO67_P8_08_dir "/sys/class/gpio/gpio67/direction"

// (One side motor B)
#define GPIO69_P8_09_dir "/sys/class/gpio/gpio69/direction"
#define GPIO68_P8_10_dir "/sys/class/gpio/gpio68/direction"

#define MAX_LENGTH 1024
static char buff[MAX_LENGTH];

void runCommand(char* command){
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");

    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
    
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)
            break;
        // printf("--> %s", buffer); // Uncomment for debugging
    }
    
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    
    if (exitCode != 0) {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}

// returns integer value of the file inputs
int readFromFileToScreen(const char *fileName)
{
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL) {
        printf("ERROR: Unable to open file (%s) for read\n", fileName);
        exit(-1);
    }
    
    // Read string (line)
    memset(buff, 0, sizeof(buff)); //clear global variable
    fgets(buff, MAX_LENGTH, pFile);

    // Close
    fclose(pFile);
    return atoi(buff);
}

void runConfig_pin(){

    // // JoyStick pins
    // runCommand("config-pin p8.14 gpio");
    // runCommand("config-pin p8.15 gpio");
    // runCommand("config-pin p8.16 gpio");
    // runCommand("config-pin p8.18 gpio");
    // runCommand("config-pin p8.17 gpio");

    // Motor pins
    runCommand("config-pin p8.10 gpio");
    runCommand("config-pin p8.09 gpio");
    runCommand("config-pin p8.08 gpio");
    runCommand("config-pin p8.07 gpio");
    write_to_file(GPIO66_P8_07_dir, "out");
    write_to_file(GPIO67_P8_08_dir, "out");
    write_to_file(GPIO68_P8_10_dir, "out");
    write_to_file(GPIO69_P8_09_dir, "out");

}


void write_number(const char* filename, int val){
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error OPENING %s.", filename);
        exit(1);
    }
    
    int writtenValue = fprintf(file, "%d" , val);
    if (writtenValue <= 0){
        printf("ERROR WRITING DATA");
        exit(1);
    }
    fclose(file);
}

// Provided by Brian Fraser
void write_to_file(const char* filename, char* value){
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error OPENING %s.", filename);
        exit(1);
    }
    
    int writtenValue = fprintf(file, "%s" , value);
    if (writtenValue <= 0){
        printf("ERROR WRITING DATA");
        exit(1);
    }
    fclose(file);
}
