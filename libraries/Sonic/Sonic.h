/*
  Sonic.h - Library for reading a PING))) sensor
*/
#ifndef Sonic_h
#define Sonic_h

#include "Arduino.h"

class Sonic
{
    public:
        Sonic(int pin);
        long distanceCm();
    private:
        long microsecondsToCentimeters(long microseconds);
        int _pin;
};

#endif