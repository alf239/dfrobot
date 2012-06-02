const int sensorPin=0;
const int VOLTS_PER_UNIT=1;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int proxSens = analogRead(sensorPin);
  float volts = (float)proxSens * VOLTS_PER_UNIT; // ("proxSens" is from analog read)
  float inches = 23.897 * pow(volts,-1.1907); //calc inches using "power" trend line from Excel
  float cm = 60.495 * pow(volts,-1.1904);     // same in cm
  if (volts < .2) 
    inches = -1.0;	  // out of range    
  Serial.println(cm);
}
 
