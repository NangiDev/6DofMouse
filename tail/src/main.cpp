#include <Arduino.h>

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.flush();
}

int axis1, axis2 = 512;

void loop()
{
  if (Serial1.available() > 0)
  {
    // Wait for Head to request information
    // 0 = Head not ready
    // 1 = Head ready
    if (Serial1.read() == 1)
    {
      // Read Joystick
      axis1 = analogRead(A0);
      axis2 = analogRead(A1);

      // Write to Head
      Serial1.write((uint8_t *)&axis1, sizeof(int));
      Serial1.write((uint8_t *)&axis2, sizeof(int));
    }
  }
}