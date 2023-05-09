# Colorimetric-Chlorine-Detection
This repo contains all my progress updates and code for my research project - colorimetric chlorine detection and automation

## Aim - 
  1. To create and automate a way to detect ppm concentration of chlorine in a sample.
  2. To automate the process with an LED/LDR combination with a microprocessor. 
  3. To automate dispensing of the required powder with servos and a microprocessor. 

## Source material -  
  1. https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=9639569
 
## Block level representation
  ![image](https://user-images.githubusercontent.com/95761876/237014930-87f8920d-980f-4b65-a1cb-f98806e12c0d.png)

## Code 
### powder dispenser automation
```c
#include <Servo.h>

#define LOAD 1
#define UNLOAD 2

// to read the incoming data for the user, used to ascertain 
// the function required  
char incomingByte = 0;

// used to detect what the previous operation carried out was
// so as to bring the relevant blade back to the closed position
int flag = 0;

Servo s_load;
Servo s_unload;

const int servoPin = 3; // for the loading motor
const int servoPin2 = 9; // for the unloading motor

void setup() { //attach servos and set baud rate for arduino
  s_load.attach(servoPin);
  s_unload.attach(servoPin2);
  Serial.begin(9600);
}

void loop() {
  while (1) // to prevent servo resets

    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      switch (incomingByte) {
        // the load motor's rest angle is 70 and not 0 due to the 
        // servo motor's configuration on the container body
        case '1': // loading code
          s_load.write(90);
          delay(5000);
          s_load.write(70);          
          flag = 0;
          break;
        case '2': // unloading code
          s_unload.write(0);
          delay(5000);
          s_unload.write(90);
          flag = 1;
          break;
        default: // default rest case
          if (flag == 0) {
            s_load.write(70);
          } else if (flag == 1) {
            s_unload.write(90);
          }
      }
    }
}
```
### LED/LDR circuit code
```c
// attaching the relevant RGB led pins to arduino PWM pins
const int greenPin = 10;
const int bluePin = 9;
const int redPin = 11;
const int ldr = A0;
// definitions for the measured absolute color readings
#define BLACK 0
#define PUREBLUE 270
#define PURERED 385
#define PUREGREEN 370
#define WHITE 350

void setup() {
  // pin declarations and
  // setting baud rate as requird
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}


void loop() {
  // code to flash the RGB led red and measure the reflected color
  // for the red component. Output is printed to the serial monitor
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  delay(1000);
  float inputVal1 = analogRead(ldr);
  Serial.print("red = ");
  Serial.println((inputVal1));

  // code to flash the RGB led green and measure the reflected color
  // for the green component. Output is printed to the serial monitor
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
  delay(1000);
  float inputVal2 = analogRead(ldr);
  Serial.print("green = ");
  Serial.println((inputVal2));

  // code to flash the RGB led blue and measure the reflected color
  // for the blue component. Output is printed to the serial monitor
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);
  delay(1000);
  float inputVal3 = analogRead(ldr);
  Serial.print("blue = ");
  Serial.println((inputVal3));

  // normalising the measured values and finding the gray value with a simple average
  float r = ((inputVal1) / (PURERED)) * WHITE;
  float g = ((inputVal2) / (PUREGREEN)) * WHITE;
  float b = ((inputVal3) / (PUREBLUE)) * WHITE;
  float avg = (r + g + b) / 3;

  //printing the output to the serial monitor
  Serial.print("rgb(");
  Serial.print(((inputVal1) / (PURERED)) * WHITE);
  Serial.print(", ");
  Serial.print(((inputVal2) / (PUREGREEN)) * WHITE);
  Serial.print(", ");
  Serial.print(((inputVal3) / (PUREBLUE)) * WHITE);
  Serial.println(")");
  Serial.print("avg = ");
  Serial.println(avg);
}
```
