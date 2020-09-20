#include "UltraSonic.h";
void UltraSonic::init(byte ip, byte op)
{
    echoPin = ip;
    trigPin = op;
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
}

int UltraSonic::distance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    return pulseIn(echoPin, HIGH) * 0.034 / 2;
}