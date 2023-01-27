#include <Arduino.h>

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("<Head is ready>");
}

union Ints
{
  int values[2];
  long combined;
} myInts;

long incomingInt;
int firstInt, secondInt;

void loop()
{
  if (Serial1.available() >= sizeof(incomingInt))
  {
    Serial1.readBytes((byte *)&myInts.combined, sizeof(myInts.combined));

    int firstInt = myInts.values[0];
    int secondInt = myInts.values[1];

    Serial.println(firstInt);
    Serial.println(secondInt);
  }
  else
  {
    myInts.values[0] = 42;
    myInts.values[1] = 123;

    Serial1.write((byte *)&myInts.combined, sizeof(myInts.combined));
  }
  delay(1000);
}
