/*
  Chassis.h - Library for controlling DFRobot 4WD chassis.
*/
#ifndef Chassis_h
#define Chassis_h

#include "Arduino.h"

class Chassis
{
  public:
    Chassis();
    void attach(int in1, int en1, int en2, int in2);
    void stop();
    void ahead(int speed);
    void back(int speed);
    void left(int speed);
    void right(int speed);
  private:
    int _in1;
    int _en1;
    int _en2;
    int _in2;
    
    void _motor1(int pwm, boolean reverse);
    void _motor2(int pwm, boolean reverse);
};

#endif