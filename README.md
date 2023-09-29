# Project description
The project is to develop an embedded software on the open robotic platform “Billy” (https://github.com/TeamBilly) but remains an indepant as the project is just for educational purpose.
This robot has been designed to serve as a basis for project prototyping or support for algorithm implementation. 
For this project, the Arduino Uno which embedded an atmega382p will be used to control the DC motors to move the robot and the other sensors and actuators on it. 
It will receive its control data from a mobile application to perform a remote control of the robot. 
The communication between the robot and the mobile app is done thank to an ESP8266 which will communicate via Wi-Fi + Firebase backend with the mobile application. 
The ESP8266 and the Arduino Uno will communicate through an USART serial communication to share information. The Arduino (atmega 328p) will perform the operative action of the system as manage motor, sensors and actuators.
