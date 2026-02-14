#ifndef ULTRASOUND_SENSOR_H
#define ULTRASOUND_SENSOR_H

  void US_Setup(int TrigPin, int EchoPin);
  unsigned long Get_Distance_CM(void);

#endif