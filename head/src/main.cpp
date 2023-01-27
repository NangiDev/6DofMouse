#include <Arduino.h>

#define DEBUG
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

  Serial.println("<Head is ready>");
  Serial1.flush();
  Serial1.write(1);
}

int tailX, tailY;
int coords[DOF] = {512, 512, 512, 512, 512, 512};

void calculate()
{
}

void loop()
{
  if (Serial1.available() >= (long)sizeof(myInts.combined))
  {
    Serial1.write(0);
    Serial1.readBytes((byte *)&myInts.combined, sizeof(myInts.combined));

    coords[0] = analogRead(A0);
    coords[1] = analogRead(A2);
    coords[2] = myInts.values[0];
    coords[3] = analogRead(A1);
    coords[4] = analogRead(A3);
    coords[5] = myInts.values[1];

#if defined(DEBUG)
    coords[0] = random(0, 1024);
    coords[3] = random(0, 1024);
    coords[1] = random(0, 1024);
    coords[4] = random(0, 1024);

    Serial.println("\tJoystick 0");
    Serial.print("\t\tX: ");
    Serial.println(coords[0]);
    Serial.print("\t\tY: ");
    Serial.println(coords[3]);
    Serial.println();
    Serial.println("\tJoystick 1");
    Serial.print("\t\tX: ");
    Serial.println(coords[1]);
    Serial.print("\t\tY: ");
    Serial.println(coords[4]);
    Serial.println();
    Serial.println("\tJoystick 2");
    Serial.print("\t\tX: ");
    Serial.println(coords[2]);
    Serial.print("\t\tY: ");
    Serial.println(coords[5]);
    Serial.println();
    Serial.println("== Asking for more coordiates ==");
    delay(1000);
#endif // DEBUG

    Serial1.write(1);
    calculate();
  }
}
