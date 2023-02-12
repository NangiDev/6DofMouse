#include <Arduino.h>

// #define DEBUG
#define DOF 6

union Ints
{
  int values[2];
  long combined;
} myInts;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  delay(10);
  Serial1.flush();
  Serial1.write(1);
}

int axis1, axis2, axis3, axis4, axis5, axis6 = 512;

void loop()
{
  if (Serial1.available() >= (long)sizeof(myInts.combined))
  {
    Serial1.write(0);
    Serial1.readBytes((byte *)&myInts.combined, sizeof(myInts.combined));

    axis1 = analogRead(A0);
    axis2 = analogRead(A1);
    axis3 = analogRead(A2);
    axis4 = analogRead(A3);
    axis5 = myInts.values[0];
    axis6 = myInts.values[1];

    Serial.write((uint8_t *)&axis1, sizeof(int));
    Serial.write((uint8_t *)&axis2, sizeof(int));
    Serial.write((uint8_t *)&axis3, sizeof(int));
    Serial.write((uint8_t *)&axis4, sizeof(int));
    Serial.write((uint8_t *)&axis5, sizeof(int));
    Serial.write((uint8_t *)&axis6, sizeof(int));

    Serial1.write(1);
  }
}
