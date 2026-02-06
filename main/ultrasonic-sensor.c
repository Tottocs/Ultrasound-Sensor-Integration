#define FIRMWARE_VERSION "v.0.1"

/* 
The function, Get_Distance, uses the HCSR04 ultrasonic sensor to output a distance measurement.
It outputs a integer of units in cm. 

The function, US_Pin_Setup, requires an input pin number, corresponding to the trig pin,
as well as an output pin number, corresponding to the echo pin.
*/

#include "headers\ultrasonic-sensor.h"
#include <Arduino.h> 

//Defining constants
#define WRITE_DELAY 5
#define TRIG_PULSE_LENGTH 10 //Specified in datasheet
#define PROPAGATION_CONSTANT 0.0343/2 //speed (cm per microsecond) of sound devided by 2
#define PULSE_IN_CHECK_TIME 1000000UL

//Setting pins 
void US_Pin_Setup(int TrigPin, int EchoPin){
  pinMode(EchoPin, INPUT);
  pinMode(TrigPin, OUTPUT);
}

int Get_Distance_CM(TrigPin, EchoPin){
  //Setting variables
  long PulseDuration;
  int Distance;
  
  //Sending trig pulse
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(WRITE_DELAY);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(TRIG_PULSE_LENGTH);
  digitalWrite(TrigPin, LOW);

  //Recieving echo pulse
  PulseDuration = pulseIn(EchoPin, HIGH, PULSE_IN_CHECK_TIME);
  Distance = PulseDuration*PROPAGATION_CONSTANT;
  
  //Returning Distance in cm
  return Distance;
}