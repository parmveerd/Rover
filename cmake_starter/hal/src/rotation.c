#include "rotation.h"
#include "system.h"


#define Rotation_Motor1_Period "/dev/bone/pwm/2/b/period"
#define Rotation_Motor2_Period "/dev/bone/pwm/2/a/period"

#define Rotation_Motor1_DutyCycle "/dev/bone/pwm/2/b/duty_cycle"
#define Rotation_Motor2_DutyCycle "/dev/bone/pwm/2/a/duty_cycle"

#define RotationEnable_Motor1 "/dev/bone/pwm/2/b/enable"
#define RotationEnable_Motor2 "/dev/bone/pwm/2/a/enable"

#define PERIOD 20000000



#define Min_Motor1 500000
#define Min_Motor2 500000

#define Max_Motor1 2500000
#define Max_Motor2 1600000
// motor one duty-cycle [500000 to 2500000]
// motor two duty-cycle [500000 to 1600000]


// connections motor 1 (bottom) connected to pwm p8.13
// connections motor 2 (up) connected to pwm p8.19
// the 5V power connected to P9.7 and P9.8 (SYS 5V pins)
// the ground wires are connected to p9.1 and p9.2

static int dutyCycle_motor1 = 1500000; // mid point for left right rotation
static int dutyCycle_motor2 = Min_Motor2; // it's on the min level, the motor only supports going up and coming down from that angle

void RotateToLeft(){
    
    int new_duty_cycle = dutyCycle_motor1 + 50000; 
    if (new_duty_cycle <= Max_Motor1) {
        dutyCycle_motor1 = new_duty_cycle;
    }
    else dutyCycle_motor1 = Max_Motor1;

    write_number(Rotation_Motor1_DutyCycle, dutyCycle_motor1);
}

void RotateToRight(){
    
    int new_duty_cycle = dutyCycle_motor1 - 50000; 
    if (new_duty_cycle >= Min_Motor1) {
        dutyCycle_motor1 = new_duty_cycle;
    }
    else dutyCycle_motor1 = Min_Motor1;

    write_number(Rotation_Motor1_DutyCycle, dutyCycle_motor1);
}

void RotateUpward(){
    int new_duty_cycle = dutyCycle_motor2 + 25000; 
    if (new_duty_cycle <= Max_Motor2) {
        dutyCycle_motor2 = new_duty_cycle;
    }
    else dutyCycle_motor2 = Max_Motor2;
    write_number(Rotation_Motor2_DutyCycle, dutyCycle_motor2);
}

void RotateDownward(){
    
    int new_duty_cycle = dutyCycle_motor2 - 25000; 
    if (new_duty_cycle >= Min_Motor2) {
        dutyCycle_motor2 = new_duty_cycle;
    }
    else dutyCycle_motor2 = Min_Motor2;

    write_number(Rotation_Motor2_DutyCycle, dutyCycle_motor2);
}

void Configure_Rotation(){
    
    runCommand("config-pin P8.13 pwm");
    runCommand("config-pin P8.19 pwm");

    write_number(Rotation_Motor1_Period, PERIOD);
    write_number(Rotation_Motor2_Period, PERIOD);
    
    write_number(Rotation_Motor1_DutyCycle, dutyCycle_motor1);
    write_number(Rotation_Motor2_DutyCycle, dutyCycle_motor2);

    write_number(RotationEnable_Motor1, 1);
    write_number(RotationEnable_Motor2, 1);
    
}
