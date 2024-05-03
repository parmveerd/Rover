#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdbool.h>

typedef enum
{
    DOWN,
    UP,
    LEFT,
    RIGHT,
    CENTER,
    NONE,

} Directions;



int JoystickDirection();
bool joystickPressed();

#endif