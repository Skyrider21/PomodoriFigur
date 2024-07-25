#include <Arduino.h>
int figurMotorPin = 0; // PWM
int mainMotorPin = 1; // PWM
int melodyPin = 2; //digitalWrite
int potiPin = 3;  // AnalogRead

int timeSinceStart; 
int previousMillis = 0;

unsigned long MAX_TIME = 30UL * 60UL * 1000UL; //in ms
int MAX_POTI_VAL = 843;
int INTERVAL = 1000;
boolean run = false;

void dance(int pin){
  analogWrite(pin,90);
  delay(1000);
  analogWrite(pin,150);
  delay(1000);
  analogWrite(pin,90);
  delay(1000);
  run = false;
}

void setup(){
  pinMode(mainMotorPin,OUTPUT);
  pinMode(figurMotorPin,OUTPUT);

  analogWrite(mainMotorPin,255);
  delay(1000);
}


void loop(){
  int potiValue = analogRead(potiPin);

  if(potiValue > 0){
    timeSinceStart = millis();
    
    while(analogRead(potiPin) < 1000){
      int position = potiValue;
      run = true;
      
      timeSinceStart = millis();
      if (timeSinceStart - previousMillis >= INTERVAL){
        previousMillis = timeSinceStart;
        position += 10;//(float)MAX_TIME / (float)MAX_POTI_VAL;
        analogWrite(mainMotorPin,map((int)position,0,1000,0,225));
      }
    }     
  }
  if(run)dance(figurMotorPin); 
}