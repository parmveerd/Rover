#ifndef _SYSTEM_H_
#define _SYSTEM_H_

void write_number(const char* filename, int val);
void runCommand(char* command);

// returns integer value of the file inputs
int readFromFileToScreen(const char *fileName);

void runConfig_pin();

// Provided by Brian Fraser
void write_to_file(const char* filename, char* value);
#endif