
# Example of Sensor data read and Send data to Raspberry pi

## Install Arduino IDE
- [Download for ubuntu](https://ubuntu.com/tutorials/install-the-arduino-ide#1-overview)
- [Download guide for Macos](https://www.arduino.cc/en/Guide/macOS)

## Download library
- [CAN library repository](https://github.com/coryjfowler/MCP_CAN_lib)
- [Timer library download](https://playground.arduino.cc/Code/Timer1/)
### Library import in Arduino IDE
1. Download ZIP file
2. Sketch -> Include Library -> Add .ZIP library...
3. Add include line
4. compile and test

## Code example of send speed sensor data
- [This code refer this page](https://joy-it.net/files/files/Produkte/SEN-Speed/SEN-Speed-Manual-20201015.pdf)

``` c
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
  counter = 0; // setting counter to 0
  interval = 2; // 2 second interval
  wheel = 20; // number of encoder disc holes

  calc = 60 / interval; // calculate interval to one minute
  usInterval = interval * 1000000; // convert interval to micro seconds

  wheel = wheel * 2; // number of encoder disc wholes times 2

  Timer1.initialize(usInterval); // initialize timer with interval time

  // executes count, if the level on pin 3 changes
  attachInterrupt(digitalPinToInterrupt(pin), count, CHANGE);


  Timer1.attachInterrupt(output); // executes output after interval time
  
  Serial.begin(9600);

  // CAN Bus init
  while (CAN_OK != CAN.begin(CAN_500KBPS,MCP_8MHz))
  {
      Serial.println("CAN BUS init Failed");
      delay(100);
  }
  pinMode(3, INPUT); // setting pin 3 as input
  pinMode(2, OUTPUT); // setting pin 2 as output
  Serial.println("CAN BUS Shield Init OK!");
}

// counts holes on disc (with filter)
void count()
{
  if (micros() - previousMicros >= 700)
  {
    counter++;
    previousMicros = micros();
  }
}

unsigned char buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// output to serial and CAN bus
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

  // Separate speed minimal size
  buf[0] = speed / 256;
  buf[1] = speed % 256;
  CAN.sendMsgBuf(0x43, 0, 8, buf);
  counter = 0;
  Timer1.attachInterrupt(output); 
}

// Didn't use loop
void loop()
{   
}

```
