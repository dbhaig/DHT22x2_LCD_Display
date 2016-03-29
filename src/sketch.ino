/* 

.ino - 

Copyright (c) 2016 Don Haig (time4tux at gmail dot com)
All rights reserved.

This program is free software: you  can redistribute it and/or modify it
under the  terms of the GNU  General Public License as  published by the
Free Software Foundation,  either version 3 of the License,  or (at your
option) any later version.

This  program  is distributed  in  the  hope  that  it will  be  useful,
but  WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy  of the GNU General Public License along
with this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include "DHT.h"
#include "display.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHT1  1
#define DHT2  2
#define DHT1PIN  2
#define DHT2PIN  3

#define NO    0
#define YES   1

//Temperatue limits in degrees Celsius
#define T1_MAX  23
#define T1_MIN  18
#define T2_MAX  23
#define T2_MIN  18

//Humidity limits in percent 
#define H1_MAX  40
#define H1_MIN  10
#define H2_MAX  40
#define H2_MIN  10

// initialize objects and variables

DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);

LCD_KEYPAD display;

int displayON = YES;

void setup()
{
   dht1.begin();
   dht2.begin();

   display.begin();

   Serial.begin(9600);
   Serial.println("# Temperaturea (T) & Humidity (H)");
}

void sendDataToDisplay(int sensor, float temp, float humidity) 
{
   display.setCursor(0, sensor-1);
   display.write(byte(0));
   display.print(temp);
   display.print((char)223);
   display.print("C ");
   display.write(byte(1)); 
   display.setCursor(10, sensor-1);
   display.print(humidity);
   display.print("%");
}

void sendReadErrorMessages(int sensor) 
{
   display.setCursor(0, sensor-1);
   display.print("DHT");
   display.print(sensor);
   display.print(" Read Failed!");

   Serial.print("**DHT");
   Serial.print(sensor);
   Serial.print(" read failure!**");

   if ( sensor == 1) Serial.print("  "); else Serial.println("");
}

void sendDataToSerial(int sensor, float temp, float humidity) 
{
   Serial.print("T");
   Serial.print(sensor);
   Serial.print(":");
   Serial.print(temp);
   Serial.write(194);   //Ouput degrees symbol
   Serial.write(176);

   Serial.print("C");
   Serial.print("  H");
   Serial.print(sensor);
   Serial.print(":");
   Serial.print(humidity);
   Serial.print("%");
   Serial.print("   ");

   if ( sensor > 1)  Serial.println("");
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 
  float h1 = dht1.readHumidity();
  float h2 = dht2.readHumidity();

  // Read temperature as Celsius (the default)
  float t1 = dht1.readTemperature();
  float t2 = dht2.readTemperature();

  // Check if read failed for DHT22 #1
  if (isnan(h1) || isnan(t1)) {
     sendReadErrorMessages(DHT1);
  } else {
     sendDataToDisplay(DHT1,t1,h1);
     sendDataToSerial(DHT1,t1,h1);
  }

  // Check if read failed for DHT22 #2
  if (isnan(h2) || isnan(t2)) {
     sendReadErrorMessages(DHT2);
  } else {
     sendDataToDisplay(DHT2,t2,h2);
     sendDataToSerial(DHT2,t2,h2);
  }
  
  if ((t1 < T1_MIN) || (t1 > T1_MAX) ||
      (t2 < T2_MIN) || (t2 > T2_MAX) ||
      (h1 < H1_MIN) || (h1 > H1_MAX) ||
      (h2 < H2_MIN) || (h2 > H2_MAX)    ) {
     
     if (displayON == YES) {
        display.backlightOff();
        displayON = NO;
     } else {
        display.backlightOn();
        displayON = YES;
     }
  } else { 
     display.backlightOn();
  }

  // Wait a few seconds between measurements.
  delay(1000);

}
