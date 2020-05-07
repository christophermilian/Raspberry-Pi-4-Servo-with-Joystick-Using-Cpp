# Moving a Micro Servo with a Joystick Using C++ and a Raspberry Pi 4B 

A project based on C++ that uses a Raspberry Pi 4B Rev. 1.2 board to move a micro servo with a joystick. 
For GPIO pin mapping, I used WiringPi (Made by Gordon Henderson under GNU-LGPL) to simplify. 
Link: http://wiringpi.com/

**WiringPi Note: The author has discontinued public releases of WiringPi. The last update was 2.52 for the Raspberry Pi 4B.** 

Hardware components used:
- (1) 5 pin Joystick
- (1) Tower Pro Micro Servo 9g
- (1) ADC Module (PCF8591)
- (3) 10K Resistors
- (1) Breadboard
- (21) Jumper Cables
- Raspberry Pi 4B Rev. 1.2

When compiling the code, run the following commands in terminal at the location of the file:

```
sudo bash
g++ ServoJoystick.cpp -o ServoJoystick -lwiringPi -lADCDevice
./ServoJoystick
```

This project was possible through an electronics kit I purchased from Freenove that provided me
with all of the components I used. If interested, it is the "Freenove Ultrasonic Starter Kit for Raspberry Pi" (FNK0024).
