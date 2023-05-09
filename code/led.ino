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
