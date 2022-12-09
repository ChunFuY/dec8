#include <SoftwareSerial.h>
SoftwareSerial s(2,3);
#include <Wire.h>
volatile uint8_t temp;
volatile bool status = false;
void setup() {
  // put your setup code here, to run once:
  Wire.begin(9);
  Wire.onReceive(ReceiveEvent);
  Wire.onRequest(RequestEvent);
  s.begin(115200);
  Serial.begin(921600);
}

void RequestEvent()
{
  if(Serial.available())
  {
    Wire.write(1);
    Wire.write(Serial.read());
  }
}
void ReceiveEvent(int i)
{
  //Serial.println(i);
  /*
  while(Wire.available())
  {
    status = true;
    temp = Wire.read();
  }
  */
  /*
  while (1 < Wire.available()) { // loop through all but the last
  char c = Wire.read(); // receive byte as a character
  //Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  */
  /*
  uint8_t temp1 = Wire.read();
  uint8_t temp2 = Wire.read();
  if(temp1 == 1)
  {
    Serial.println(temp2);
  }
  */
  
  while(Wire.available())
  {

    Serial.write(Wire.read());
  }
  
}
void loop() {
  // put your main code here, to run repeatedly:
if(s.available())
{
  Serial.write(s.read());
}
  /*
  while(s.available())
  {
    uint8_t temp = s.read();
    Serial.println(temp);
  }
  */
}
