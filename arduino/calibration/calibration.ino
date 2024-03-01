/*
QMC5883LCompass.h Library Calibration Example Sketch
Learn more at [https://github.com/mprograms/QMC5883LCompass]

Upload this calibration sketch onto your Arduino to provide calibration for your QMC5883L chip.
After upload, run the serial monitor and follow the directions.
When prompted, copy the last line into your project's actual sketch.

===============================================================================================================
Release under the GNU General Public License v3
[https://www.gnu.org/licenses/gpl-3.0.en.html]
===============================================================================================================











                                          UTILITY SKETCH
                                    NO SERVICABLE PARTS BELOW












*/
#include <QMC5883LCompass.h>
#include <SPI.h>
#include <SD.h>
QMC5883LCompass compass;
File myFile;
void setup() {
  Serial.begin(9600);
  compass.init();
  SD.begin(10);
  myFile = SD.open("test.txt", FILE_WRITE);
  
  Serial.println("This will provide calibration settings for your QMC5883L chip. When prompted, move the magnetometer in all directions until the calibration is complete.");
  Serial.println("Calibration will begin in 5 seconds.");
  delay(1000);

  Serial.println("CALIBRATING. Keep moving your sensor...");
  compass.calibrate();

  Serial.println("DONE. Copy the lines below and paste it into your projects sketch.);");
  Serial.println();
  String a;
  a+= "compass.setCalibrationOffsets(";
  a+=String(compass.getCalibrationOffset(0));
  a+=", ";
  a+=String(compass.getCalibrationOffset(1));
  a+=", ";
  a+=String(compass.getCalibrationOffset(2));
  a+=");";
  myFile.println(a);
  String b;
  b+= "compass.setCalibrationScales(";
  b+=String(compass.getCalibrationScale(0));
  b+=", ";
  b+=String(compass.getCalibrationScale(1));
  b+=", ";
  b+=String(compass.getCalibrationScale(2));
  b+=");";
  myFile.println(b);
  myFile.close();
}

void loop() {
  delay(1000);
}
