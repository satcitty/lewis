/**************************************************************************/
/*!
    @file     imac_mma_store_demo_graphic.h
    @author   Ali Irmak Ozdagli (University of New Mexico)
    @license  BSD (see license.txt)
    This code is derived from Adafruit codes
    ----> https://www.adafruit.com/products/2019
    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
    @section  HISTORY
    v1.0  - First release
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();
const unsigned long interval = 10; // Interval between data records in milliseconds.
unsigned long previousMillis = 0; // millis() returns an unsigned long

void setup(void) {
  Serial.begin(38400); //communication speed

  if (! mma.begin()) {
    Serial.println("Couldn't start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G); // set sensor to +/- 2g
  mma.setDataRate(MMA8451_DATARATE_100_HZ); // set sensor to 100 Hz sampling rate
  
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");
//  Serial.print("Data Rate = "); Serial.print(mma.getDataRate());  
//  Serial.println("Hz");
  
}

void loop() {
  unsigned long currentMillis = millis(); // grab current time
  
  // check if "interval" time has passed
  if ( (currentMillis - previousMillis) >= interval ) {
    
    /* Get a new sensor event */ 
    sensors_event_t event;
    mma.getEvent(&event);
    
    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print(event.acceleration.x, 4);
    Serial.print("\t");
    Serial.print(event.acceleration.y, 4);
    Serial.print("\t");
    Serial.println(event.acceleration.z, 4);
    
    // save the "current" time
    previousMillis = previousMillis + interval;
  }
  
}

