SEA:ME 2nd Project

> Before start
> - Before following this document, You must have to do first.
> - [Assemble Pi Racer & Move](https://github.com/SEA-ME/Team-Porsche-PiRacer)

# Table of Contents

# Basics knowledge of the Hardware
## What is CAN(Controller Arean Network)?
- Standard communication protocol designed for vehicles to communicate with each other within a vehicle
- **ECUs** in the vehicle communicate using the CAN protocol
### 장점
- Multi-Master
	- All nodes are bus masters and whenever the bus is empty they can send information 
- Twisted Pair Wire
	- Strong against electrical noise due to electrically differentiated communication using two lines : CAN_H, CAN_L
	- Scalability. Only need to connect to two lines, No matter how many ECUs. 
		<img width="444" alt="image" src="https://user-images.githubusercontent.com/54701846/191264465-e9e956a9-d0fc-4817-9e90-276ba66cf1e3.png">

- Message-Oriented Protocol
	- Use ID based on message priority. Use them to distinguish messages
	- Multiple messages come in at the same time, carry out the priority ID message 
> ECU
>	- Electronic Control Unit
>	- Electronic control device used in a car

## What is Arduino?
- Micro Controller
	-  Small electronic device that can easily handle various movements such as read data from sensors or use data to control motors.
	- C language (or C++) and Arduino IDE enable simple coding
	- Consists of Regulator, Circuit Element, GPIO
	- Peripherals allow direct control of external devices
	- [More Information of Arduino](https://www.arduino.cc/en/Guide/Introduction)
> GPIO 
>	- General Purpose Input/Output
>	- Uncommitted digital signal pin on an integrated circuit or electronic circuit board which may be used as an input or output, or both, and is controllable by software.
## What is Raspberry Pi?
- Micro Processor
	- Similar to Arduino, but called Processor because it can have various OSs
	- Unlike Arduino, there is no peripheral device and controls the device using an internal transistor
	- Powerful performance in computational processing, which is useful for complex computational processing such as video and graphics
	- [Raspberry Pi official document](https://www.raspberrypi.com/documentation/computers/)

# Prepare the materials

| | | |
|---|---|---|
|Pi RacerPro & Raspberry Pi| Can Module MCP 2515 * 2| Arduino Nano(HIMALAYA|
|<img alt="image" src="https://user-images.githubusercontent.com/54701846/191284407-329db1ba-07ec-481c-b7d6-d8af2a20b35b.png"> | <img alt="image" src="https://user-images.githubusercontent.com/54701846/191287231-bbadd415-da5a-494f-8b1c-3a7ac9cfa985.png"> | <img alt="image" src="https://user-images.githubusercontent.com/54701846/191292895-c7e3e488-040f-4f88-bdb7-685f208b0c35.png">|

- Basically, These materials can make communication. After connecting, you can connect Arduino with other modules(speed sensor, temperature sensor, etc) using Breadboard.

# Make communication
## Blueprint
> Raspberry Pi <-> MCP2515 <-> MCP2515 <-> Arduino Nano <-> other modules

### Raspberry Pi <-> MCP2515

<p align="center">
<img width="400" alt="image" src="https://user-images.githubusercontent.com/54701846/191302225-40637996-c62b-4cc0-9e74-a9ba7a33abb0.png">  

| Raspberry Pi | MCP2515 |
|:---:|:---:|
|GND[20]|GND|
|GPIO25[22]|INT|
|GPIO8[24]|CS|
|GPIO10[19]|SI|
|GPIO9[21]|S0|
|GPIO11[23]|SCK|
|5V|VCC|

</p>

- VCC & 5V
  - You must find another 5Voltage socket in Pi Racer. Raspberry Pi 5V is already used for connecting Raspberry Pi & Pi Racer.

### Arduino Nano <-> MCP2515

<p align="center"> 

| | |
|:---:|:---:|
|<img width="400" alt="image" src="https://user-images.githubusercontent.com/54701846/191307758-886c282e-a346-4b50-8235-5cb4d0bf654c.png">|<img width="271" alt="image" src="https://user-images.githubusercontent.com/54701846/191308606-7ece9871-ea46-4e8d-ad3f-02b719a89957.png">  |


| Arduino Nano | MCP2515 |
|:---:|:---:|
|D2|INT|
|D13|SCK|
|D11|SI|
|D12|S0|
|D10|CS|
|GND|GND|
|5V|VCC|  

- Use Breadboard to connect Arduino and MCP2515
- Later, Sensors can be connected to Arduino with Breadboard

</p>

### MCP2515 <-> MCP2515

<p align="center"> 

| MCP2515 | MCP2515 |
|:---:|:---:|
|CAN_H|CAN_H|
|CAN_L|CAN_L|

</p>

## Send & Receive Data

### [Send sensor data to Raspberry-Pi from Arduino](./SensorDataTransmitter/index.md)
