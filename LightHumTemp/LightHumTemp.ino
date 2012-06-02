void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  int sensors[3];
  for (int i = 0; i < 3; i++) {
    // wait 10 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(10);                     
    sensors[i] = analogRead(i);
  }

  // print the results to the serial monitor:
  Serial.print("sensors\t" );                       
  Serial.print(sensors[0]);      
  Serial.print("\t" );                       
  Serial.print(sensors[1]);      
  Serial.print("\t" );                       
  Serial.print(sensors[2]);      
  Serial.println();   
  delay(1000);
}
