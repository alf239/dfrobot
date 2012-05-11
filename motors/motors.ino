//This motor shield use Pin 6,5,7,4 to control the motor
// Simply connect your motors to M1+,M1-,M2+,M2-
// Upload the code to Arduino/Roboduino
// Through serial monitor, type 'a','s', 'w','d','x' to control the motor
// www.dfrobot.com
// Last modified on 24/12/2009

int EN1 = 6;
int EN2 = 5; //Roboduino Motor shield uses Pin 9
int IN1 = 7;
int IN2 = 4; //Latest version use pin 4 instead of pin 8

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

void setup()
{
    for (int i=4; i<=7; i++)    // For Arduino Motor Shield
        pinMode(i, OUTPUT); // set pin 4,5,6,7 to output mode

    Serial.begin(9600);   
}

void loop()
{ 
    int speed = 255;
    char val = Serial.read();
    if (val != -1)
    {
        switch (val)
        {
            case 'w':  
                Serial.println("move ahead");
                Motor1(speed, true);
                Motor2(speed, true);
                break;
            case 'x': 
                Serial.println("move back");
                Motor1(speed, false);
                Motor2(speed, false);
                break;
            case 'a': 
                Serial.println("turn left");
                Motor1(speed, false);
                Motor2(speed, true);
                break;       
            case 'd': 
                Serial.println("turn right");
                Motor1(speed, true);
                Motor2(speed, false);
                break;   
            case 's': 
                Serial.println("stop");
                Motor1(0, false);
                Motor2(0, false);
                break;
            default:
                Serial.println("oops?");
        }
    }
}

