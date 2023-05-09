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
