/*
  This is the TAIL
  TAIL will connect to HEAD through serial1
  If HEAD has not responded with a READY response TAIL wont do anything

  If HEAD requests information from TAIL,
  TAIL will read input from analog 1 and 2
  and send to HEAD via serial1
*/

#include <Arduino.h>
void setup()
{
  // Serial.begin(115200); // Serial for debugging
  Serial1.begin(115200); // Seral to communicate with HEAD
  Serial1.flush();
}

int axis1, axis2 = 512;
const HEAD_IS_READY = 1

void loop()
{
  if (Serial1.available() > 0)
  {
    // Wait for Head to request information
    // 0 = Head not ready
    // 1 = Head ready
    if (Serial1.read() == HEAD_IS_READY)
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