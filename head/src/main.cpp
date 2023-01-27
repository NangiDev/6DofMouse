#include <Arduino.h>

#define DEBUG

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("<Head is ready>");
  Serial1.flush();
  Serial1.write(1);
}

union Ints
{
  int values[2];
  long combined;
} myInts;

int tailX, tailY;

void loop()
{
  if (Serial1.available() >= (long)sizeof(myInts.combined))
  {
    Serial1.write(0);
    Serial1.readBytes((byte *)&myInts.combined, sizeof(myInts.combined));

    int tailX = myInts.values[0];
    int tailY = myInts.values[1];

#if defined(DEBUG)
    Serial.print("\tX: ");
    Serial.println(tailX);
    Serial.print("\tY: ");
    Serial.println(tailY);
    Serial.println();
    Serial.println("== Asking for more coordiates ==");
    delay(1000);
#endif // DEBUG

    Serial1.write(1);
  }
}
