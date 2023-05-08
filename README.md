# Colorimetric-Chlorine-Detection
This repo contains all my progress updates and code for my research project - colorimetric chlorine detection and automation

## Aim - 
  1. To create and automate a way to detect ppm concentration of chlorine in a sample.
  2. To automate the process with an LED/LDR combination with a microprocessor. 
  3. To automate dispensing of the required powder with servos and a microprocessor. 

## Source material -  
  1. https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=9639569
  
## Code 
### powder dispenser automation
```
#include <Servo.h>
#define LOAD 1
#define UNLOAD 2
char incomingByte = 0;
int vals = 0;
int flag = 0;

Servo s_load;
Servo s_unload;
int servoPin = 3;
int servoPin2 = 9;
void setup() {
  s_load.attach(servoPin);
  s_unload.attach(servoPin2);
  Serial.begin(9600);
}

void loop() {
  while (1)
    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      switch (incomingByte) {
        case '1':
          s_load.write(90);
          // s_unload.write(0);
          delay(5000);
          s_load.write(70);          
          flag = 0;
          break;
        case '2':
          // s_load.write(90);
          s_unload.write(0);
          delay(5000);
          // s_load.write(70);
          s_unload.write(90);
          flag = 1;
          break;
        default:
          if (flag == 0) {
            s_load.write(70);
            // s_unload.write(0);
          } else if (flag == 1) {
            // s_load.write(70);
            s_unload.write(90);
          }
      }
    }
}
```
### LED/LDR circuit code
```
const int greenPin = 10; 
const int bluePin = 9;
const int redPin = 11; 
const int ldr = A0;
#define BLACK 0
#define PUREBLUE 270
#define PURERED 385
#define PUREGREEN 370
#define WHITE 350
void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}
void loop()
{
  analogWrite(redPin,0);
  analogWrite(greenPin,255);
  analogWrite(bluePin,255);
  delay(1000);
  float inputVal1 = analogRead(ldr);
  Serial.print("red = ");Serial.println((inputVal1));

  analogWrite(redPin,255);
  analogWrite(greenPin,0);
  analogWrite(bluePin,255);
  delay(1000);
  float inputVal2 = analogRead(ldr);
  Serial.print("green = ");Serial.println((inputVal2));

  analogWrite(redPin,255);
  analogWrite(greenPin,255);
  analogWrite(bluePin,0);    
  delay(1000);
  float inputVal3 = analogRead(ldr);
  Serial.print("blue = ");Serial.println((inputVal3)); 

  float r = ((inputVal1)/(PURERED))*WHITE;
  float g = ((inputVal2)/(PUREGREEN))*WHITE;
  float b = ((inputVal3)/(PUREBLUE))*WHITE;
  float avg = (r + g + b)/3;
  
  Serial.print("rgb(") ;    
  Serial.print(((inputVal1)/(PURERED))*WHITE);
  Serial.print(", ");
  Serial.print(((inputVal2)/(PUREGREEN))*WHITE);
  Serial.print(", ");
  Serial.print(((inputVal3)/(PUREBLUE))*WHITE);   
  Serial.println(")");
  Serial.print("avg = "); Serial.println(avg);
    
}
```
