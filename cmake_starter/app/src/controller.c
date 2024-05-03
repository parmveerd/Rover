// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "joystick.h"
#include "system.h"
#include "delaytime.h"
#include "controller.h"
#include <string.h>

// (One side motor A)
#define GPIO66_P8_07 "/sys/class/gpio/gpio66/value" 
#define GPIO67_P8_08 "/sys/class/gpio/gpio67/value"

// (One side motor B)
#define GPIO69_P8_09 "/sys/class/gpio/gpio69/value"
#define GPIO68_P8_10 "/sys/class/gpio/gpio68/value"


void moveBackward(){
        write_number(GPIO67_P8_08, 0);
        write_number(GPIO66_P8_07, 1);
        // (Motor B - backward)
        write_number(GPIO68_P8_10, 0);
        write_number(GPIO69_P8_09, 1);
}
void moveForward(){
        // (Motor A - forward)
        write_number(GPIO66_P8_07, 0);
        write_number(GPIO67_P8_08, 1);
        // (Motor B - forward)
        write_number(GPIO69_P8_09, 0);
        write_number(GPIO68_P8_10, 1);
        
}

void turnLeft(){
        write_number(GPIO67_P8_08, 0);
        write_number(GPIO66_P8_07, 1);
        // (Motor B - forward)
        write_number(GPIO69_P8_09, 0);
        write_number(GPIO68_P8_10, 1);
}
void turnRight(){
        // (Motor A - forward)
        write_number(GPIO66_P8_07, 0);
        write_number(GPIO67_P8_08, 1);
        // (Motor B - backward)
        write_number(GPIO68_P8_10, 0);
        write_number(GPIO69_P8_09, 1);
}
void stop(){
        // (Motor A - stop)
        write_number(GPIO66_P8_07, 0);
        write_number(GPIO67_P8_08, 0);
        // (Motor B - stop)
        write_number(GPIO69_P8_09, 0);
        write_number(GPIO68_P8_10, 0);
}
// static void* controller()
// {
//     // configuring the joystick pins to GPIO 
//     runConfig_pin();
//     int last_joystick_direction = -1;
//     while (true)
//     {
//         if(endProgram){
//             stop();
//             break;
//         }
//             if(joystickPressed()){
//                 int joystick_input = JoystickDirection();
//                 if((joystick_input == UP) && (last_joystick_direction != joystick_input)){
//                     printf("moving forward\n");
//                     moveForward();
//                     last_joystick_direction = joystick_input;
//                 } else if(joystick_input == DOWN  && (last_joystick_direction != joystick_input)){
//                     printf("moving backward\n");
//                     moveBackward();
//                     last_joystick_direction = joystick_input;
//                 }
//                 else if(joystick_input == CENTER  && (last_joystick_direction != joystick_input)){
//                     printf("moving backward\n");
//                     stop();
//                     last_joystick_direction = joystick_input;
//                 }
//                 else if(joystick_input == LEFT  && (last_joystick_direction != joystick_input)){
//                     printf("turn left\n");
//                     turnLeft();
//                     last_joystick_direction = joystick_input;
//                 }
//                 else if(joystick_input == RIGHT  && (last_joystick_direction != joystick_input)){
//                     printf("turn right\n");
//                     turnRight();
//                     last_joystick_direction = joystick_input;
//                 }      
//             }
//     }
// }


// void controller_init(void) {
//     pthread_create(&controlThread, NULL, controller, NULL);
// }

// void controller_shutdown(void) {
//     pthread_join(controlThread, NULL);
// }
