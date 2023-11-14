# Purpose
The purpose of this checkpoint is to ensure that the development environment is properly configured. In this checkpoint, the initial step is to install the operating system using the official Ubuntu Mate image file. Next, we proceed to install ROS (Robot Operating System) within the environment. Afterward, we utilize the ROS rosserial package, available on the official ROS Arduino website, to establish communication between the Raspberry Pi and Arduino.

# Design
This checkpoint encompasses two key tasks: 
(1) Utilize the SSH command to establish a remote connection from your PC to the Raspberry Pi. Use the "rosversion" command to confirm the successful installation of ROS Melodic on the Raspberry Pi. 
(2) Employ commands and libraries from the rosserial package to create a program featuring publishers and subscribers. This program facilitates bidirectional communication between the Raspberry Pi and Arduino. Specifically, the Raspberry Pi will transmit a numeric value to the Arduino, which will then multiply it by 2 and return the result to the Raspberry Pi. 

# Material
(1) RasberryPi model 3
(2) Arduino board
