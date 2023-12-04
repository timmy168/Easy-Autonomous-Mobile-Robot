# Purpose
The objective of this checkpoint is to empower the robot to locate a particular 
object or a designated signal. In this phase, the robot is programmed to identify a beacon emitting two distinct IR signals using its IR sensors. With this capability, the mobile robot can navigate towards the targeted beacon.

# Design
For the sake of ease in testing and debugging, this checkpoint exclusively focuses on implementing the Arduino board. It is essential to clarify that this phase does not involve any communication with the Raspberry Pi using ROS. The Arduino code is meticulously crafted to directly detect IR signals from the beacon by connecting to Arduino pins through digital input.

Initially, the robot executes the same actions as in the previous checkpoint, engaging in tasks such as locating the light ball and avoiding obstacles through touch and light sensors. Upon the activation of the bottom touch sensor, the robot transitions into a new mode dedicated to locating the beacon with the IR sensor.

During this process, once the touch sensor on the base is no longer pressed, indicating the absence of the light ball, the mode reverts to the initial objective of finding the ball. This adaptive approach equips the robot with the capability to identify specific objects and navigate towards predefined targets.

# IR sensor
![image](https://github.com/timmy168/Easy-Autonomous-Mobile-Robot/blob/main/ckpt4/IR.png)

# Beacon
![image](https://github.com/timmy168/Easy-Autonomous-Mobile-Robot/blob/main/ckpt4/Beacon.png)
