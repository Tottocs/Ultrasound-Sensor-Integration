#define FIRMWARE_VERSION "v.1.0"

/* 
The function, Get_Distance, uses the HCSR04 ultrasonic sensor to output a distance measurement.
It outputs a integer of units in cm. 

The function, US_Pin_Setup, requires an input pin number, corresponding to the trig pin,
as well as an output pin number, corresponding to the echo pin.
*/

#include "headers\ultrasonic-sensor.h"
#include <Arduino.h>
#include <stdint.h>

//Defining constants
#define WRITE_DELAY 5
#define TRIG_PULSE_LENGTH 10 //Specified in datasheet
#define HALF_SPD_SOUND 171
#define MAG_SHIFT 10000

#define PULSE_IN_TIMEOUT 20UL //Max recordable distance 350 cm

//Internal pin numbers
static int _TrigPin;
static int _EchoPin;

//Ultrasonic sensor variables
volatile unsigned long EchoStart = 0;
volatile unsigned long EchoDuration = 0;
volatile bool EchoComplete = false;

//Internal interrupt function
void Echo_ISR() {
  //Serial.println("ISR");
  //Checks for High input
  if (digitalRead(_EchoPin) == HIGH) {
    EchoStart = micros();
  } else {
    EchoDuration = micros() - EchoStart;
    EchoComplete = true;
  }
}

//Callable functions

//Setup
void US_Setup(int TrigPin, int EchoPin){
  //Setting pins
  _TrigPin = TrigPin;
  _EchoPin = EchoPin;

  pinMode(_EchoPin, INPUT);
  pinMode(_TrigPin, OUTPUT);
  
  //Interrupt pin
  attachInterrupt(digitalPinToInterrupt(_EchoPin), Echo_ISR, CHANGE);
}

unsigned long Get_Distance_CM(void){
  //Setting variables
  unsigned long Distance;

  EchoComplete = false;

  //Sending trig pulse
  digitalWrite(_TrigPin, LOW);
  delayMicroseconds(WRITE_DELAY);
  digitalWrite(_TrigPin, HIGH);
  delayMicroseconds(TRIG_PULSE_LENGTH);
  digitalWrite(_TrigPin, LOW);

  /*
  unsigned long timeout = millis();
  while (!EchoComplete) {
      if (millis() - timeout > PULSE_IN_TIMEOUT)
          return -1;
  }
  */

  //Converting echo pulse duration to cm
  Distance = (EchoDuration*HALF_SPD_SOUND)/MAG_SHIFT;

  return Distance;
}