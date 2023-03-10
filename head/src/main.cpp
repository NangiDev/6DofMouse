/*
  This is the HEAD
  HEAD will connect to TAIL through serial1

  HEAD will wait for TAIL to be ready before requesting the first information.

  If HEAD requests information from TAIL,
  TAIL will read input from analog 1 and 2
  and send to HEAD via serial1

  If HEAD has not responded with a READY response TAIL wont do anything
  If computer hasn't written anything to Serial, HEAD wont don't do anything

  HEAD will only write all joystick data to the computer if requested.
*/

#include <Arduino.h>

// #define DEBUG
#define DOF 6

const HEAD_IS_READY = 1;
const HEAD_IS_NOT_READY = 0;

void setup()
{
  Serial.begin(115200); // Serial for communication with computer
  Serial1.begin(115200); // Serial to communicate with TAIL
  Serial1.flush();

  while (!Serial1.availableForWrite()){/* Wait for TAIL to start listening*/}
  Serial1.write(HEAD_IS_READY);
}

int axis1, axis2, axis3, axis4, axis5, axis6 = 512;

void loop()
{
  // Only read if serial data is avaiable
  if (Serial1.available() > 0)
  {
    // Tell TAIL that HEAD is not ready
    Serial1.write(HEAD_IS_NOT_READY);

    // Read joysticks
    axis1 = analogRead(A0);
    axis2 = analogRead(A1);
    axis3 = analogRead(A2);
    axis4 = analogRead(A3);
    // Read joystick from TAIL
    Serial1.readBytes((uint8_t *)&axis5, sizeof(int));
    Serial1.readBytes((uint8_t *)&axis6, sizeof(int));

    // Wait for computer to be ready
    if (Serial.available() > 0)
    {
      // Consume the ready message from computer
      Serial.read();
      // Write all joysticks to computer
      Serial.write((uint8_t *)&axis1, sizeof(int));
      Serial.write((uint8_t *)&axis2, sizeof(int));
      Serial.write((uint8_t *)&axis3, sizeof(int));
      Serial.write((uint8_t *)&axis4, sizeof(int));
      Serial.write((uint8_t *)&axis5, sizeof(int));
      Serial.write((uint8_t *)&axis6, sizeof(int));
      // Flush to prevent missmatching data
      Serial.flush();
    }

    // Tell TAIL that HEAD is ready
    Serial1.write(1);
  }
}
