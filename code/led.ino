
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

int redarr[20];
int greenarr[20];
int bluearr[20];
int avgarr[20];
int i = 0;

void setup() {
  // pin declarations and
  // setting baud rate as requird
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}
void loop() {
  for (int i = 0; i < 20; i++) {
    // code to flash the RGB led red and measure the reflected color
    // for the red component. Output is printed to the serial monitor
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 255);
    delay(1000);
    float inputVal1 = analogRead(ldr);
    redarr[i] = inputVal1;

    // code to flash the RGB led green and measure the reflected color
    // for the green component. Output is printed to the serial monitor
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);
    delay(1000);
    float inputVal2 = analogRead(ldr);
    greenarr[i] = inputVal2;

    // code to flash the RGB led blue and measure the reflected color
    // for the blue component. Output is printed to the serial monitor
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    delay(1000);
    float inputVal3 = analogRead(ldr);
    bluearr[i] = inputVal3;

    // normalising the measured values and finding the gray value with a simple average
    float r = ((inputVal1) / (PURERED)) * WHITE;
    float g = ((inputVal2) / (PUREGREEN)) * WHITE;
    float b = ((inputVal3) / (PUREBLUE)) * WHITE;
    avgarr[i] = (r + g + b) / 3;
  }
  float sum = 0.0;
  for (int i = 0; i < 20; i++) {
    sum += redarr[i];
  }
  delay(1000);
  Serial.println(sum/20);
  sum = 0.0;
  for (int i = 0; i < 20; i++) {
    sum += greenarr[i];
  }
  delay(1000);
  Serial.println(sum/20);
  sum = 0.0;
  for (int i = 0; i < 20; i++) {
    sum += bluearr[i];
  }
  delay(1000);
  Serial.println(sum/20);
  sum = 0.0;
  for (int i = 0; i < 20; i++) {
    sum += avgarr[i];
  }
  delay(1000);
  Serial.println(sum/20);
}
