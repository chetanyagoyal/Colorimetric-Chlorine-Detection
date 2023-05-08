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