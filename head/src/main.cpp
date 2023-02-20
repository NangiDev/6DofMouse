#include <Arduino.h>

// #define DEBUG
#define DOF 6

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.flush();

  // delay(10); // Wait for Tail to start listening
  while (!Serial1.availableForWrite())
  {
  }
  Serial1.write(1);
}

int axis1, axis2, axis3, axis4, axis5, axis6 = 512;

void loop()
{
  // Only read is serial data availabe
  if (Serial1.available() > 0)
  {
    // Tell Tail that Head is not ready
    Serial1.write(0);

    // Read joysticks
    axis1 = analogRead(A0);
    axis2 = analogRead(A1);
    axis3 = analogRead(A2);
    axis4 = analogRead(A3);
    // Read joystick from Tail
    Serial1.readBytes((uint8_t *)&axis5, sizeof(int));
    Serial1.readBytes((uint8_t *)&axis6, sizeof(int));

    // Wait for receiver to be ready
    if (Serial.available() > 0)
    {
      // Consume the ready message from receiver
      Serial.read();
      // Write all joysticks over usb
      Serial.write((uint8_t *)&axis1, sizeof(int));
      Serial.write((uint8_t *)&axis2, sizeof(int));
      Serial.write((uint8_t *)&axis3, sizeof(int));
      Serial.write((uint8_t *)&axis4, sizeof(int));
      Serial.write((uint8_t *)&axis5, sizeof(int));
      Serial.write((uint8_t *)&axis6, sizeof(int));
      // Flush to prevent miss matching data
      Serial.flush();
    }

    // Tell Tail that Head is ready
    Serial1.write(1);
  }
}
