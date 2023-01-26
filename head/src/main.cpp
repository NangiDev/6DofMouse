#include <Arduino.h>

int RXLED = 17;

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(RXLED, OUTPUT);

  Serial.begin(9600);
  Serial.println("<Head is ready>");
}

char receivedChar;

void loop()
{
  digitalWrite(RXLED, LOW); // set the RX LED ON
  TXLED0;                   // TX LED is not tied to a normally controlled pin so a macro is needed, turn LED OFF
  delay(1000);              // wait for a second

  Serial.print("This just in ... \n");

  digitalWrite(RXLED, HIGH); // set the RX LED OFF
  TXLED1;                    // TX LED macro to turn LED ON
  delay(1000);               // wait for a second
}
