#include <Arduino.h>
typedef uint8_t byte;
#ifndef ULTRA_H
#define ULTRA_H
class UltraSonic
{
private:
  byte echoPin;
  byte trigPin;

public:
  void init(byte ip, byte op);
  int distance();
};
#endif
