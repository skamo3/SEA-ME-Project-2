SEA:ME 2nd Project

> Before start
> - Before following this document, You must have to do first.
> - [Assemble Pi Racer & Move](https://github.com/SEA-ME/Team-Porsche-PiRacer)

# Table of Contents

# Complete Architecture

![image](https://user-images.githubusercontent.com/54701846/198272218-2d9131da-847f-4fbf-a447-c06f7a264a88.png)

- Simple project architecture
  - Receive sensor data from Arduino and transfer it to Raspberry Pi using CAN Bus
  - Raspberry Pi uses the DBus server to manage the data it receives and delivers the data it needs for each application


# Basics knowledge of the Architecture
## What is CAN(Controller Area Network)?
- Standard communication protocol designed for vehicles to communicate with each other within a vehicle
- **ECUs** in the vehicle communicate using the CAN protocol
### Advantage
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

## What is D-Bus?
- System for IPC(Inter-Process Communication)
- A bus system that enables various processes with different characteristics to communicate with each other
- D-Bus is a service daemon that runs in the background that uses the bus daemon to communicate functions and communications between applications
	![image](https://user-images.githubusercontent.com/54701846/198288126-4fe57537-08c5-4fa0-919a-aa205ec3a55d.png)

  - -Bus 데몬의 2가지 유형  
    1. D-Bus System bus
       - Communicate with kernel and system-wide events
       - Any application is prevented from spoofing
    2. D-Bus Session bus
       - daemon attached to each user session
       - Used to communicate with other applications within the same system
       - Receive messages from the system bus
> Check D-bus service in terminal  
> ``` ps -ef | grep dbus-demon ```
> <img width="758" alt="image" src="https://user-images.githubusercontent.com/54701846/198288931-78f25649-1af8-42c8-a8d3-163329d950f0.png">  
> Separated by behind word
> - ```--system ``` or ```--session```
### Key Terms and Concepts
- Bus name(Service name)
  - Unique name for 1 connection
  - Automatically generated when connected to D-Bus daemon and can be set up by the user themselves
  - Names once used are non-reusable and must not be duplicated
- Object path
  - D-bus is a Peer-to-Peer protocol in which all messages sent and received are source and purposeful
  - Address used to send and receive messages
    - Written like "/org/example/Test"
  - Multiple object paths can be assigned differently than a business name
  - Object provides one or more interfaces
- Interface
  - Name of grouping Method and Signal
  - Interface is used as the namespace for each method
  - example
    ``` xml
	<?xml version="1.0" ?>
		<node name="/org/freedesktop/DBus/Example/Echo">
			<interface name="org.freedesktop.DBus.EchoDemo">
				<method name="HelloString">
					<arg type="s" name="name" direction="in"/>
					<arg type="s" name="greeting" direction="out"/>
				</method>
				<signal name="EchoCount">
					<arg type="y" name="count"/>
				</signal>
			</interface>
		</node>
	```
	> - Method
	>	- Can be called by another object
	>	- Can optionally have Input and Output
	> - Signal 
	> 	- Kind of broadcast message. Send to one object to all objects registered with that signal
  - Message
	- Data passed between processes
	- Method Call Message
	- Method Return Message
	- Error Message
	- Signal Message
	- Header and Body

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

- Raspberry-Pi and Arduino communication with CAN communicate library
### Set Can  

1. Setting CAN interface on Raspberry Pi
	- Add the following line to your /boot/config.txt file:  
		```vim
		dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=25
		dtoverlay=spi-bcm2835-overlay
		```
		- oscillator : should be set to the actual crystal frequency found on your MCP2515
		- interrupt : specifies the Raspberry PI GPIO pin number

	- Reboot your Raspberry Pi and Check this line
		```
		[   20.248951] CAN device driver interface
		[   20.499256] mcp251x spi0.0 can0: MCP2515 successfully initialized.
		```  
2. Bring up the CAN interfaces  
	2-1. Manually bring up  
	- Follow this command in terminal  
		`sudo /sbin/ip link set can0 up type can bitrate 500000  `
		- Check your CAN bus bitrate and write correct number  
	
	2-2. Automatically bring up on boot
	- Edit your `/etc/network/interfaces` file and add this line
		```vim
		auto can0
		iface can0 inet manual
			pre-up /sbin/ip link set can0 type can bitrate 500000 triple-sampling on restart-ms 100
			up /sbin/ifconfig can0 up
			down /sbin/ifconfig can0 down
		```

- Check CAN module  
	- Enter this command and check output  
	<img width="650" alt="image" src="https://user-images.githubusercontent.com/54701846/198319567-d80022c6-c79a-4935-94f9-c99f93767d45.png">  

3. CAN-utils
	- CAN-utils is a collection of extremely useful debugging tools using the SocketCAN interface
	- list of applications
		- candump : Dump can packets – display, filter and log to disk.
		- canplayer : Replay CAN log files.
		- cansend : Send a single frame.
		- cangen : Generate random traffic.
		- canbusload : display the current CAN bus utilisation.
	- Install CAN utils
		- [CAN-utils Git repository](https://github.com/linux-can/can-utils)
		- Pre-compiled binaries can be installed using:  
		` sudo apt-get install can-utils `

4. CAN data send or receive with CAN utils
	- Make random data  
	`cangen can0`
	- Receive can data and check in terminal  
	`candump can0`  
	<img width="352" alt="image" src="https://user-images.githubusercontent.com/54701846/198325409-cbf8b9e0-fdd1-4a0d-acd7-91202315d4b1.png">


> [Reference link](https://www.beyondlogic.org/adding-can-controller-area-network-to-the-raspberry-pi/)

### [Send sensor data Arduino -> Raspberry-Pi](./documents/ArduinoSendData.md)

### [Receive sensor data on Raspberry-Pi with code](./documents/RaspberryPiReceiveData.md)