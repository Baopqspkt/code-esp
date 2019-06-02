#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4,5);
String readString;
int chophep = 0;
const char *host = "www.baopqspkt.xyz";
const char *ssid = "PT";
const char *pass = "phamquocbao";

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600); 
   WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    Serial.println("Waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi Connected.");
}
void endsend()
{
  mySerial.write(0xff);
  mySerial.write(0xff);
  mySerial.write(0xff);
}
void loop() {

  while (mySerial.available()) {
    delay(3);  
    char c = (char)mySerial.read();
    readString += c; 
  }
  readString.trim();
  
  if (readString.length() >0) {
    Serial.println("Length:");
    Serial.println(readString.length());
    Serial.println(readString);
  }
  if ((readString == "11")||(readString == "01")||(readString == "12")||(readString == "02")||(readString == "13")||(readString == "03")||(readString == "14")||(readString == "04")) 
    {
      chophep = 1;
    }
  if (chophep == 1)
    {
      WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort))
        {
            Serial.println("connection failed");
            delay(5000);
            return;
        }
    String url = "/getdatanextion.php?color=";
    url = url + readString;
    Serial.println(url);
    client.print("GET " + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    String content = "";
    client.stop();
    chophep = 0;
    readString = "";
    }
   else
    {
      readString = "";
    }
}
