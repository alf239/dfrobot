#include <Servo.h> 
 
Servo myservo; 

const int pingPin = 8;
const int servoPin = 9;

const int led1 = 2;
const int led2 = 3;

const int buttonPin = 11;

const int EN1 = 6;
const int EN2 = 5;
const int IN1 = 7;
const int IN2 = 4;

const int STOP = 0;
const int RIGHT = 1;
const int LEFT = 2;
const int BACK = 3;
const int FORWARD = 4;

int state = STOP;
int pos = 90;
// int angle_step = 15;


void setup() {
  myservo.attach(servoPin);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);   
}

void loop()
{
  int buttonState = digitalRead(buttonPin);
  digitalWrite(led2, buttonState);
  
  if (buttonState == HIGH) {
    state = state == STOP ? FORWARD : STOP;
    delay(2000);
  }

  Serial.print("state=");
  Serial.println(state);
  
  if (state == STOP) {
    stop_motor();
    delay(1000);
    return;
  }
  
  myservo.write(60);
  delay(200);
  int l = senseDistance();
  myservo.write(120);
  delay(200);
  int r = senseDistance();
  
  Serial.print("l=");
  Serial.print(l);
  Serial.print(", r=");
  Serial.println(r);

  switch (state) {
    case FORWARD:
      if (l < 20 && r > 20) {
        state = RIGHT;
        right(255);
      } else if (l > 20 && r < 20) {
        state = LEFT;
        left(255);
      } else if (l < 20 && r < 20) {
        state = BACK;
        back(255);
      } else {
        ahead(255);
      }
      break;
    case LEFT:
      if (r > 40) {
        state = FORWARD;
        ahead(255);
      }
      break;
    case RIGHT:
      if (l > 40) {
        state = FORWARD;
        ahead(255);
      }
      break;
    case BACK:
      if (l > 30 && r > 30) {
        state = RIGHT;
        right(255);
      }
  }
}

long senseDistance() {
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  return microsecondsToCentimeters(duration);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void ahead(int speed) {
    Motor1(speed, true);
    Motor2(speed, true);
}

void back(int speed) {
    Motor1(speed, false);
    Motor2(speed, false);
}

void left(int speed) {
    Motor1(speed, false);
    Motor2(speed, true);
}

void right(int speed) {
    Motor1(speed, true);
    Motor2(speed, false);
}

void stop_motor() {
    Motor1(0, false);
    Motor2(0, false);
}

void Motor1(int pwm, boolean reverse)
{
    analogWrite(EN1, pwm); //set pwm control, 0 for stop, and 255 for maximum speed
    digitalWrite(IN1, reverse ? HIGH : LOW);
}

void Motor2(int pwm, boolean reverse)
{
    analogWrite(EN2,pwm);
    digitalWrite(IN2, reverse ? HIGH : LOW);
}

