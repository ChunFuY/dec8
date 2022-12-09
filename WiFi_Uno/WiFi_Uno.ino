#include <QueueArray.h>
#include <Wire.h>
//MAC Address:  50:02:91:DC:E7:3E
#include <ESP8266WiFi.h>
#include <espnow.h>
QueueArray<uint8_t> tempQueue;
uint8_t broadcastAddress[] = {0x50,0x02,0x91,0xDC,0xE7,0x3E};
#include <SoftwareSerial.h>
const int Rx = D3;
const int Tx = D4;
SoftwareSerial s (Rx, Tx);
typedef struct SensorData{
  float f;
}SensorData;

bool status;
typedef struct CameraData{
  uint8_t by[4];
}CameraData;
CameraData Ctemp;
SensorData receivedData;
uint8_t startByte;
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&Ctemp, incomingData,sizeof(incomingData));
  status = true;
  Wire.beginTransmission(9);
  //Wire.write(1);
  Wire.write(Ctemp.by,4);
  Wire.endTransmission();
  
  /*
  for(int i = 0; i < sizeof(Ctemp); i++)
  {
    //tempQueue.push(Ctemp.by[i]);
//Serial.println(Ctemp.by[i]);
    //s.write(Ctemp.by[i]);    
    
    Wire.beginTransmission(9);
    //Wire.write(1);
    Wire.write(Ctemp.by[i]);
    Wire.endTransmission();
    
    //s.write(Ctemp.by[i]);
  }
  */
  delay(10);
  /*
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  String temp = encode(receivedData.b, receivedData.f);
  //s.println(temp);
  //Serial.println(recvstr);
  s.print(temp);
  Serial.println(receivedData.b);
  Serial.println(receivedData.f);
  */
}
 
void setup() {
  Wire.begin();
  Serial.begin(921600);
  s.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    //Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  Wire.requestFrom(9,2);
  
  while(Wire.available())
  {
    uint8_t temp1 = Wire.read();
    uint8_t temp2 = Wire.read();
    //Serial.print(temp1);
    //Serial.print(" ");
    //Serial.print(temp2);
    //Serial.println();    
//Serial.print(temp1);
    if(temp1 == 1)
    {
    Serial.println("Success");
    startByte = temp2;
    //startByte = Wire.read();
    Serial.println(startByte);
    esp_now_send(broadcastAddress,(uint8_t*) &startByte, sizeof(startByte));
    }

  }
  /*
  if(status)
  {
    for(int i =0; i < sizeof(Ctemp); ++i)
    {
      s.write(Ctemp.by[i]);
      delay(5);      
    }
    status = false;
  }
  */
  /*
  if(s.available())
  {
    startByte = s.read();
    Serial.print("sent");
    esp_now_send(broadcastAddress,(uint8_t*) &startByte, sizeof(startByte));
  }
  */
  //sendmsg.str = "test";
  //esp_now_send(broadcastAddress,(uint8_t*) &sendmsg, sizeof(sendmsg));
  //delay(1000);
  /*
  while(!tempQueue.isEmpty())
  {
    uint8_t temp = tempQueue.pop();
    s.write(temp);
  }
  */
}


String encode(bool b, float i)
{
  String return_value = "";
  if(b == true)
  {
    return_value += '1'; 
  }
  else{
    return_value += '0';
  }
  String temp = String(i,3);
  return_value += temp;
  return_value += '\n';
  Serial.println(return_value);
  return return_value;

}