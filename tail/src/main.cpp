#include <Arduino.h>

// #define DEBUG

union Ints
{
  int values[2];
  long combined;
} myInts;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial1.flush();
  Serial.println("<Tail is ready>");
}

int readyToWrite = 1;
bool receiverIsReadyToReceive()
{
  if (Serial1.available() > 0)
  {
    readyToWrite = Serial1.read();

#if defined(DEBUG)
    if (readyToWrite > 0)
    {
      Serial.println("== Receiver is ready! ==");
    }
    else
    {
      Serial.println("== Waiting for receiver to be ready! ==");
    }
#endif // DEBUG
  }
  return readyToWrite > 0;
}

void loop()
{
  if (receiverIsReadyToReceive())
  {
    myInts.values[0] = analogRead(A0);
    myInts.values[1] = analogRead(A1);

    // #if defined(DEBUG)
    //     myInts.values[0] = random(0, 1024);
    //     myInts.values[1] = random(0, 1024);
    // #endif // DEBUG

    Serial1.write((byte *)&myInts.combined, sizeof(myInts.combined));
    readyToWrite = 0;

#if defined(DEBUG)
    Serial.println("\tWriting: ");
    Serial.print("\t\tX: ");
    Serial.println(myInts.values[0]);
    Serial.print("\t\tY: ");
    Serial.println(myInts.values[1]);
    Serial.println();
#endif // DEBUG
  }
}
