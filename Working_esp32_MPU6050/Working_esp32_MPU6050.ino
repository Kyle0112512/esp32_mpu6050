//
//    FILE: GY521_pitch_roll_yaw.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo pitch roll yaw
//    DATE: 2020-08-06


#include "GY521.h"
#include "Arduino.h"
#include "heltec.h"

GY521 sensor(0x68);

uint32_t counter = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);


  Wire1.begin();

  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);\
  
  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }
  sensor.setAccelSensitivity(2);  // 8g
  sensor.setGyroSensitivity(1);   // 500 degrees/s

  sensor.setThrottle();
  Serial.println("start...");

  // set calibration values from calibration sketch.
  sensor.axe = 0;
  sensor.aye = 0;
  sensor.aze = 0;
  sensor.gxe = 0;
  sensor.gye = 0;
  sensor.gze = 0;
}

void drawFontFaceDemo() {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(0, 0, "Hello world");
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->drawString(0, 10, "Hello world");
    Heltec.display->setFont(ArialMT_Plain_24);
    Heltec.display->drawString(0, 26, "Hello world");
}

void loop()
{
  delay(10);
  sensor.read();
  float pitch = sensor.getPitch()+ 0.139/10*counter + 3.7;
  float roll  = sensor.getRoll()- 0.0427/10*counter;
  float yaw   = sensor.getYaw()+ 0.0034/10*counter;

  if (counter % 10 == 0)
  {
    Serial.println("\nCNT\tPITCH\tROLL\tYAW");
  }

   // clear the display
  Heltec.display->clear();
  drawFontFaceDemo();
  
  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(10, 128, String(millis()));
  // write the buffer to the display
  Heltec.display->display();

  delay(10);//time for the display to catch up
  
  Serial.print(counter);
  Serial.print('\t');
  Serial.print(pitch, 3);
  Serial.print('\t');
  Serial.print(roll, 3);
  Serial.print('\t');
  Serial.print(yaw, 3);
  Serial.println();

  counter++;
}


// -- END OF FILE --
