#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_VL53L0X.h"

#define TCAADDR 0x70

/* Assign a unique ID to this sensor at the same time */
//Adafruit_HMC5883_Unified mag1 = Adafruit_HMC5883_Unified(1);

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}


void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Distance sensor Test"); Serial.println("");
  
  /* Initialise the 1st sensor */
  tcaselect(2);
  if(!lox1.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no VL53L0X detected ... Check your wiring!");
    while(1);
  }
  
  /* Initialise the 2nd sensor */
  tcaselect(6);
  if(!lox2.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no VL53L0X detected ... Check your wiring!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
  tcaselect(2);

  tcaselect(7);
=
}

void loop(void) 
{
  VL53L0X_RangingMeasurementData_t measure;
  //Start first sensor
  tcaselect(2);

  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
 Serial.print("Reading measurement from first Distance sensor... ");
  lox1.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(500);

  //Start second sensor
  tcaselect(7);
  //lox2.getEvent(&event);
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  Serial.print("Reading measurement from first Distance sensor... ");
  lox2.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(500);
}
