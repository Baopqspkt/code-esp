// Author: Pham Quoc Bao
// Mail: baopq.spkt@gmail.com
// Modify 11/05/2019 by qb

#include <ESP8266WiFi.h>

const char *host = "www.baopqspkt.xyz";
const char *ssid = "PT";
const char *pass = "phamquocbao";
String ledsta = "";
void setup()
{
    Serial.begin(115200);
    /* Set ESP8266 to WiFi Station mode */
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

void loop()
{
    while (Serial.available() == 0);
    while (Serial.available())
    {
        ledsta = Serial.readString();
         Serial.println("trong while");
    }
    
     if (ledsta == "0x11")
    {
        WiFiClient client;
        const int httpPort = 80;
        if (!client.connect(host, httpPort))
        {
            Serial.println("connection failed");
            delay(5000);
            return;
        }
        String url = "/getdatanextionblue.php?color=0";
        Serial.println(url);
        client.print("GET " + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
        client.stop();
        Serial.println("connection failed");
        ledsta = "";
    }
    else
    {
      Serial.print(ledsta);
    }
}
