#define FIRMWARE_VERSION "v.0.1"

#include "headers\ultrasonic-sensor.h"

#define UART_BAUDRATE 9600
#define US_REFRESH_RATE 1000 

//Pins on Arduino UNO
#define US_TRIG_PIN 8 
#define US_ECHO_PIN 9 

int Distance;

void setup() {
  Serial.begin(UART_BAUDRATE);
  US_Pin_Setup(US_TRIG_PIN, US_ECHO_PIN);

}

void loop() {
  Distance = Get_Distance_CM(US_TRIG_PIN, US_ECHO_PIN);
  Serial.print("Distance:");
  Serial.print(Distance);
  Serial.print("cm\n\r");
  delay(US_REFRESH_RATE);
}
