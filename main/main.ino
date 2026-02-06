#define FIRMWARE_VERSION "v.0.2" // Adding Servo Implementation

/*
This code uses an ultrasonic sensor to output receice a distance measurement.
It then uses that measurement to move a servo from 0 to 90 degrees.
0 degrees corresponds to 15 cm and 90 degrees corresponds to 195 cm.
Anything below or above the limits will correspond to 0 and 90 degrees respectively.

The acronym US refers to "Ultrasonic" 
*/

#include "headers\ultrasonic-sensor.h" //Including custom library
#include <Servo.h>

#define UART_BAUDRATE 9600
#define US_REFRESH_RATE 500 //Refresh rate in ms

//Pins on Arduino UNO 
#define US_TRIG_PIN 8 
#define US_ECHO_PIN 9 

#define PWM_SERVO_PIN 6

//MAX and MIN distances (cm)
#define MIN_DIST 15
#define MAX_DIST 195

//Creating Servo object
Servo clanker;

//Initialising variables
int Distance;
int ServoPos;

void setup() {
  Serial.begin(UART_BAUDRATE);
  //Pin setup
  US_Pin_Setup(US_TRIG_PIN, US_ECHO_PIN); //Setting up pins for US sensor
  clanker.attach(PWM_SERVO_PIN);
}

void loop() {
  //Receiving a distance measurement from ultrasonic sensor
  Distance = Get_Distance_CM(US_TRIG_PIN, US_ECHO_PIN);

  //Implement Servo
  if (Distance >= MIN_DIST && Distance <= MAX_DIST){
    ServoPos = (Distance-MIN_DIST)/2;
  }
  else if (Distance > MAX_DIST){
    ServoPos = (MAX_DIST-MIN_DIST)/2;
  }
  else {
    ServoPos = 0;
  }

  clanker.write(ServoPos);


  //Implement buzzer

  //Printing distance to serial monitor
  Serial.print("Distance:");
  Serial.print(Distance);
  Serial.print("cm\n\r");
  Serial.print("Servo Position:");
  Serial.print(ServoPos);
  Serial.print(" degrees\n\r");

  //Refresh rate of the circuit
  delay(US_REFRESH_RATE);
}
