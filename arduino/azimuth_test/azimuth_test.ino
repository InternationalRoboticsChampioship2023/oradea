/*
===============================================================================================================
QMC5883LCompass.h Library Azimuth Example Sketch
Learn more at [https://github.com/mprograms/QMC5883Compas]
===============================================================================================================
v0.3 - June 12, 2019
Written by MRPrograms 
Github: [https://github.com/mprograms/]

Release under the GNU General Public License v3
[https://www.gnu.org/licenses/gpl-3.0.en.html]
===============================================================================================================
*/

//do not place near magnets
#include <QMC5883LCompass.h>

QMC5883LCompass compass;

void setup() {
  Serial.begin(9600);
  compass.init();
  compass.setCalibrationOffsets(-196.00, -374.00, 147.00);
  //compass.setCalibrationScales(0.99, 0.99, 1.02);
  //compass.setCalibrationOffsets(-645.00, 1146.00, -331.00);
  compass.setCalibrationScales(1, 1, 1);
  //compass.setCalibrationOffsets(-892.00, 1088.00, -488.00);
//compass.setCalibrationScales(0.88, 0.78, 1.72);



}

void loop() {
  int a;
  
  // Read compass values
  compass.read();

  // Return Azimuth reading
  a = compass.getAzimuth();
  
  Serial.print("A: ");
  Serial.print(a);
  Serial.println();
  
  delay(250);
}
