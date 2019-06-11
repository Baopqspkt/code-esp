#include <ESP8266WiFi.h>
#include <EEPROM.h>

char * ssid = "PT";
char * password = "phamquocbao";

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  for(int i =0; i < 2; i ++)
    EEPROM.write(i,ssid[i]);
  EEPROM.commit();
  for(int i = 3; i < 15; i ++)
    EEPROM.write(i,password[i]);
  EEPROM.commit();
  delay(100);
  Serial.println("Done Write");
 
  for (int i =0; i < 2; i ++)
  {
     Serial.print((char)EEPROM.read(i));
  }
  Serial.println();
  for(int i = 3; i < 15; i ++)
    Serial.print((char)EEPROM.read(i));
  //valpassword = valpassword +  (char)EEPROM.read(i);
  //Serial.print("Valuessid:\t");
  //Serial.print(valssid);
  //Serial.print("Valpass:\t");
  //Serial.print(valpassword);
  Serial.println();
}

void loop() {
;
}
