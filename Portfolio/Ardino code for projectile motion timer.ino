#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// rs pin controls where in LCDs memory the data is writing to
//en enables writing to the register rs
//v0 display pin and the D pins (high or low) are the values you're reading when you read.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int trigPin = 9; //triggers the ultrasonics sound pulses
const int echoPin = 10; // echo pin produces a pulse when the reflected signal is received.
//the length of the pulse is proportional to the time it took for the transmitted signal to be detected


long TIME;
double Velocity;
int dist1 = 0;
int dist2 = 0;
int dist = 0;





void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16,2);

}

void loop() {
  

  dist1 = ultra();
  delay(500);
  dist2 = ultra();

  Velocity = (dist2 - dist1)/0.5; //0.5 because the delay between trig and echo is 500 ms

  Serial.print("Velocity is in cm/s   :");
  Serial.println(Velocity);
  //Serial.print("Dist1: ");
  //Serial.println(dist1);
//  Serial.print("Dist2: ");
//  Serial.println(dist2);
  
  lcd.print(Velocity);
  delay(500);

  

}

float ultra()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW); // resets trig pin to low

  TIME = pulseIn(echoPin, HIGH);

  dist = TIME*0.034/2;

  lcd.setCursor(0,0);
  return dist;
}
