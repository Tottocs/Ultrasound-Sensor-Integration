#define FIRMWARE_VERSION "v.0.3" // Adding buzzer implementation

/*
This code uses an ultrasonic sensor to output receice a distance measurement.
It then uses that measurement to move a servo from 0 to 90 degrees.
0 degrees corresponds to 15 cm and 90 degrees corresponds to 195 cm.
Anything below or above the limits will correspond to 0 and 90 degrees respectively.

The second integration is with a buzzer which changes the tone depending on the 
distance. This range can be changed, but initially it is from 2000 to 8000 Hz.

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

#define PWM_BUZZER_PIN 10

//MAX and MIN distances (cm)
#define MIN_DIST 15
#define MAX_DIST 195

//MAX and MIN frequencies (Hz)
#define MIN_FREQ 2000
#define MAX_FREQ 8000

//Creating Servo object
Servo clanker;

//Initialising variables
int Distance;
int ServoPos;
int BuzzerFreq;

void setup() {
  Serial.begin(UART_BAUDRATE);
  //Pin setup
  US_Pin_Setup(US_TRIG_PIN, US_ECHO_PIN); //Setting up pins for US sensor
  clanker.attach(PWM_SERVO_PIN);
  pinMode(PWM_BUZZER_PIN, OUTPUT);
}

void loop() {
  //Receiving a distance measurement from ultrasonic sensor
  Distance = Get_Distance_CM(US_TRIG_PIN, US_ECHO_PIN);

  //Implementation of servo and buzzer
  if (Distance >= MIN_DIST && Distance <= MAX_DIST){ // Between min and max distances
    ServoPos = (Distance-MIN_DIST)/2;
    BuzzerFreq = map(Distance, MIN_DIST, MAX_DIST, MIN_FREQ, MAX_FREQ);
  }
  else if (Distance > MAX_DIST){ // Above max distance
    ServoPos = (MAX_DIST-MIN_DIST)/2;
    BuzzerFreq = MAX_FREQ;
  }
  else { // Below min distance or else
    ServoPos = 0;
    BuzzerFreq = MIN_FREQ;
  }
  
  //Setting servo position
  clanker.write(ServoPos);

  //Setting buzzer frequency
  tone(PWM_BUZZER_PIN, BuzzerFreq);

  //Printing information to serial monitor
  Serial.print("Distance:");
  Serial.print(Distance);
  Serial.print("cm\n\r");
  Serial.print("Servo Position:");
  Serial.print(ServoPos);
  Serial.print(" degrees\n\r");
  Serial.print("Buzzer frequency:");  
  Serial.print(BuzzerFreq);
  Serial.print("Hz\n\r\n");
  //Refresh rate of the circuit
  delay(US_REFRESH_RATE);
}
