#include <Servo.h>

#define LOAD 1
#define UNLOAD 2

// angle and load time declarations for modularity of code
const int load_servo_rest = 70;
const int unload_servo_rest = 90;
const int load_servo = 90;
const int unload_servo = 0;
const int load_time = 5000;
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
          s_load.write(load_servo);
          delay(load_time);
          s_load.write(load_servo_rest);          
          flag = 0;
          break;
        case '2': // unloading code
          s_unload.write(unload_servo);
          delay(load_time);
          s_unload.write(unload_servo_rest);
          flag = 1;
          break;
        default: // default rest case
          if (flag == 0) {
            s_load.write(load_servo_rest);
          } else if (flag == 1) {
            s_unload.write(unload_servo_rest);
          }
      }
    }
}
