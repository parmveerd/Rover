#include "joystick.h"
#include <stdio.h>
#include <stdbool.h>
#include "system.h"

// 'Joystick output value' path definition
static const char JoystickLeft[] =  "/sys/class/gpio/gpio65/value";
static const char JoystickRight[] = "/sys/class/gpio/gpio47/value";
static const char JoystickUp[] = "/sys/class/gpio/gpio26/value";
static const char JoystickDown[] = "/sys/class/gpio/gpio46/value";
static const char JoystickCenter[] = "/sys/class/gpio/gpio27/value";

int JoystickDirection(){
    if(readFromFileToScreen(JoystickDown) == 0){
        return DOWN;
    }
    else if(readFromFileToScreen(JoystickUp) == 0){
        return UP;
    }
    else if(readFromFileToScreen(JoystickLeft) == 0){
        return LEFT; 
    }
    else if(readFromFileToScreen(JoystickRight) == 0){
        return RIGHT; 
    }
    else if(readFromFileToScreen(JoystickCenter) == 0){
        return CENTER; 
    }
    else 
        return NONE; // return for no joystick input
}

bool joystickPressed(){
    return !(JoystickDirection() == 5); // returns if joystickPressed
}
