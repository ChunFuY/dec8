#include <SoftwareSerial.h>
#include <Wire.h>
#include <BreezyArduCAM.h>
#include <SPI.h>
static const int CS = 6;
//SoftwareSerial s(2,3);
Serial_ArduCAM_FrameGrabber fg;
//byte buf[2];
/* Choose your camera */
ArduCAM_Mini_2MP myCam(CS, &fg);
//SoftwareSerial s(2,3);
byte buf[2];
void setup() {
  //Wire.setClock(25000);
  //s.begin(57600);
  Wire.begin();
  TWBR = 12;
  SPI.begin();
  Serial.begin(921600);
  //s.begin(9600);
  myCam.beginJpeg160x120();
  //while(!s);
}

void loop() {
  
  myCam.capture();

}