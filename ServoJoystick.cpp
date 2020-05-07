/*
Made by: Christopher Milian 
Purpose: To control SG90 Servo with Joystick
Started: 5/4/2020
Completed: 5/6/2020
*/

#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#include <ADCDevice.hpp>


#define SERVO_MIN_MS 0   // Define the pulse duration for minimum angle of servo
#define SERVO_MAX_MS 28  // Define the pulse duration for maximum angle of servo
#define servoPin 0       // Define the GPIO number connected to servo
#define Z_Pin 1          // Define pin for Z-axis 
ADCDevice *adc;          // Define an ADC Device class object

void servoInit(int pin){         // Initialization function for servo PMW pin
    softPwmCreate(pin, 0, 200);  // Using pin 0 (GPIO 17), position 0 degrees, and pmwRange of 200 (20ms)
}
void servoWriteMS(int pin, int ms){     // Specify the unit for pulse (5-25ms) with specific duration output by servo pin: 0.1ms
    if(ms > SERVO_MAX_MS)               // In other words, set the rotation limits to prevent going past the physical capabilities of the servo
        ms = SERVO_MAX_MS;
    if(ms < SERVO_MIN_MS)
        ms = SERVO_MIN_MS;
    softPwmWrite(pin,ms);               // This function makes the servo move
}

int main(void){
    adc = new ADCDevice();
    printf("Program is starting ... \n");
    
    if(adc->detectI2C(0x48)){   // Detect the pcf8591.
        delete adc;             // Free previously pointed memory
        adc = new PCF8591();    // If detected, create an instance of PCF8591
    }
    else if(adc->detectI2C(0x4b)){  // Detect the ads7830
        delete adc;                 // Free previously pointed memory
        adc = new ADS7830();        // If detected, create an instance of ADS7830
    }
    else{
        printf("No correct I2C address found, \n"
        "Please use command 'i2cdetect -y 1' to check the I2C address! \n"
        "Program Exit. \n");
        return -1;
    }

    wiringPiSetup();            // Setup of GPIO pins to wiringPi pin layout
    servoInit(servoPin);        // Initialize PMW pin of servo, in this case 0 (GPIO 17)
    pinMode(Z_Pin,INPUT);       // Set Z_Pin as input pin and pull-up mode
    pullUpDnControl(Z_Pin,PUD_UP);

    while(1){

        int val_Z = digitalRead(Z_Pin);  // Read digital value of axis Z
        int val_Y = adc->analogRead(0);  // Read analog value of axis X and Y
        int val_X = adc->analogRead(1);
        printf("val_X: %d  ,\tval_Y: %d  ,\tval_Z: %d \n",val_X,val_Y,val_Z);
        val_Y = (val_Y/8);
        servoWriteMS(servoPin,val_Y);
    }
    return 0;
}
