#include <SPI.h>
#include <mcp_can.h>
#include <TimerOne.h>

# define pin 3

const int spiCSPin = 10;

MCP_CAN CAN(spiCSPin);

int interval, wheel, counter;
unsigned long previousMicros, usInterval, calc;

void setup()
{
  counter = 0;
  interval = 2;
  wheel = 20;

  calc = 60 / interval;
  usInterval = interval * 1000000;

  wheel = wheel * 2;

  Timer1.initialize(usInterval);
  attachInterrupt(digitalPinToInterrupt(pin), count, CHANGE);

  Timer1.attachInterrupt(output);
  
  Serial.begin(9600);

  while (CAN_OK != CAN.begin(CAN_500KBPS,MCP_8MHz))
  {
      Serial.println("CAN BUS init Failed");
      delay(100);
  }
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
  Serial.println("CAN BUS Shield Init OK!");
}

void count()
{
  if (micros() - previousMicros >= 700)
  {
    counter++;
    previousMicros = micros();
  }
}

unsigned char buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void output()
{
  
  Timer1.detachInterrupt();
  int speed = ((counter)*calc) / wheel;
  
  Serial.print("Speed : ");
  Serial.print(speed);
  Serial.print(" | ");
  Serial.print(speed / 256);
  Serial.print(" | ");
  Serial.println(speed % 256);
  buf[0] = speed / 256;
  buf[1] = speed % 256;
  CAN.sendMsgBuf(0x43, 0, 8, buf);
  counter = 0;
  Timer1.attachInterrupt(output); 
}
    
void loop()
{   
//  Serial.println("In loop");
//  CAN.sendMsgBuf(0x43, 0, 8, stmp);
//
//  double ret = analogRead(4);
//  stmp[0] = ret;
//
//  Serial.print("analog input : ");
//  Serial.println(ret);
//
//  delay(1000);
}
