#include "Arduino.h"
#include "Chassis.h"

Chassis::Chassis() {
}

void Chassis::attach(int in2, int en2, int en1, int in1) {
    _in1 = in1;
    _en1 = en1;
    _en2 = en2;
    _in2 = in2;
    pinMode(_in1, OUTPUT);
    pinMode(_en1, OUTPUT);
    pinMode(_en2, OUTPUT);
    pinMode(_in2, OUTPUT);
}

void Chassis::ahead(int speed) {
    _motor1(speed, true);
    _motor2(speed, true);
}

void Chassis::back(int speed) {
    _motor1(speed, false);
    _motor2(speed, false);
}

void Chassis::left(int speed) {
    _motor1(speed, false);
    _motor2(speed, true);
}

void Chassis::right(int speed) {
    _motor1(speed, true);
    _motor2(speed, false);
}

void Chassis::stop() {
    _motor1(0, false);
    _motor2(0, false);
}

void Chassis::_motor1(int pwm, boolean reverse) {
    analogWrite(_en1, pwm);
    digitalWrite(_in1, reverse ? HIGH : LOW);
}

void Chassis::_motor2(int pwm, boolean reverse) {
    analogWrite(_en2,pwm);
    digitalWrite(_in2, reverse ? HIGH : LOW);
}

