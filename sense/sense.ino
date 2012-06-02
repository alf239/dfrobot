#include <Chassis.h>
#include <Sonic.h>
#include <Servo.h> 
#include <CmdMessenger.h>
#include <Base64.h>
#include <Streaming.h>
#include <stdlib.h>

Chassis chassis; 
Servo head; 
Sonic sonic(8);

char field_separator = ',';
char command_separator = ';';

CmdMessenger cmdMessenger = CmdMessenger(Serial, field_separator, command_separator);

enum
{
  kCOMM_ERROR    = 000, // Lets Arduino report serial port comm error back to the PC (only works for some comm errors)
  kACK           = 001, // Arduino acknowledges cmd was received
  kARDUINO_READY = 002, // After opening the comm port, send this cmd 02 from PC to check arduino is ready
  kERR           = 003, // Arduino reports badly formatted cmd, or cmd not recognised

  kREADING       = 004,

  kSEND_CMDS_END, // Mustnt delete this line
};

messengerCallbackFunction messengerCallbacks[] = 
{
  move_head, // 005
  forward,   // 006
  ch_stop,   // 007
  NULL
};

void move_head()
{
  cmdMessenger.sendCmd(kACK, "head()");
  while (cmdMessenger.available())
  {
    int pos = cmdMessenger.readInt();
    head.write(pos);
  }
}

void forward()
{
  cmdMessenger.sendCmd(kACK, "forward()");
  chassis.ahead(255);
}

void ch_stop()
{
  cmdMessenger.sendCmd(kACK, "ch_stop()");
  chassis.stop();
}

void arduino_ready()
{
  cmdMessenger.sendCmd(kACK, "Arduino ready");
}

void unknownCmd()
{
  cmdMessenger.sendCmd(kERR, "Unknown command");
}

void attach_callbacks(messengerCallbackFunction* callbacks)
{
  int i = 0;
  int offset = kSEND_CMDS_END;
  while (callbacks[i])
  {
    cmdMessenger.attach(offset+i, callbacks[i]);
    i++;
  }
}

void setup() {
  Serial.begin(9600);   
  head.attach(9);
  chassis.attach(4, 5, 6, 7);

  cmdMessenger.print_LF_CR();
  cmdMessenger.attach(kARDUINO_READY, arduino_ready);
  cmdMessenger.attach(unknownCmd);
  attach_callbacks(messengerCallbacks);
  arduino_ready();
}

void loop()
{
  cmdMessenger.feedinSerialData();
  int l = sonic.distanceCm();
  char value[6];
  itoa(l, value, 10);
  cmdMessenger.sendCmd(kREADING, value);
  delay(100);
}

