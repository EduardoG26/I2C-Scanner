// SPDX-FileCopyrightText: 2023 Carter Nelson for Adafruit Industries
//
// SPDX-License-Identifier: MIT
// --------------------------------------
// i2c_scanner
//
// Modified from https://playground.arduino.cc/Main/I2cScanner/
// Modified Eduardo de Mier, 2025, ...
// --------------------------------------

#include <Wire.h>

// Set I2C bus Speed in baud
#define SPEED 100000

// Set I2C bus to use: Wire, Wire1, etc.
#define WIRE Wire

void setup() {
  WIRE.begin();
  WIRE.setClock(SPEED);

  Serial.begin(9600);
  while (!Serial)
     delay(10);
  Serial.println("\n*** I2C Scanner ***");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of the Write.endTransmisstion 
    // to see if a device acknowledges the address.
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission();

    if (error == 0) // No error? 
    {
      if (!nDevices)
        Serial.print("I2C device found at address");
      Serial.print(" 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print(" >> error at 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" <<");
    }
  }

  if (nDevices == 0)
    Serial.println("No I2C devices found.\n");
  else
    Serial.println(" done.\n");

  delay(1000);           // wait N seconds for next scan
}
