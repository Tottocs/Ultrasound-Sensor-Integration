#ifndef ULTRASOUND_SENSOR_H
#define ULTRASOUND_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

  void US_Pin_Setup(int TrigPin, int EchoPin);
  int Get_Distance_CM(int TrigPin, int EchoPin);

#ifdef __cplusplus
}
#endif

#endif