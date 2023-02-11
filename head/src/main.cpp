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
  Serial.println("<Head is ready>");
  Serial1.flush();
  Serial1.write(1);
}

int tailX, tailY;
int coords[DOF] = {512, 512, 512, 512, 512, 512};
char charCoords[DOF * 4];

void loop()
{
  if (Serial1.available() >= (long)sizeof(myInts.combined))
  {
    Serial1.write(0);
    Serial1.readBytes((byte *)&myInts.combined, sizeof(myInts.combined));

    coords[0] = analogRead(A0);
    coords[1] = analogRead(A1);
    coords[2] = analogRead(A2);
    coords[3] = analogRead(A3);
    coords[4] = myInts.values[0];
    coords[5] = myInts.values[1];

    sprintf(charCoords, "%d;%d;%d;%d;%d;%d\n", coords[0], coords[1], coords[2], coords[3], coords[4], coords[5]);
    Serial.print(charCoords);

    // Serial.print(sizeof(charCoords));

    Serial1.write(1);
  }
}
