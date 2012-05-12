#include <Sonic.h>
#include <Servo.h> 
#include <Chassis.h>

const int STOP = 0;
const int RIGHT = 1;
const int LEFT = 2;
const int BACK = 3;
const int FORWARD = 4;

Chassis chassis; 
Servo myservo; 
Sonic sonic(8);

int state = FORWARD;

void setup() {
  Serial.begin(9600);   

  myservo.attach(9);
  chassis.attach(4, 5, 6, 7);
}

void loop()
{
  myservo.write(60);
  delay(200);
  int l = sonic.distanceCm();
  myservo.write(120);
  delay(200);
  int r = sonic.distanceCm();
  
  switch (state) {
    case FORWARD:
      if (l < 20 && r > 20) {
        state = RIGHT;
        chassis.right(255);
      } else if (l > 20 && r < 20) {
        state = LEFT;
        chassis.left(255);
      } else if (l < 20 && r < 20) {
        state = BACK;
        chassis.back(255);
      } else {
        chassis.ahead(255);
      }
      break;
    case LEFT:
      if (r > 40) {
        state = FORWARD;
        chassis.ahead(255);
      }
      break;
    case RIGHT:
      if (l > 40) {
        state = FORWARD;
        chassis.ahead(255);
      }
      break;
    case BACK:
      if (l > 30 && r > 30) {
        state = RIGHT;
        chassis.right(255);
      }
      break;
  }
}

