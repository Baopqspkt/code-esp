#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5);

int chophep = 0;
const char *host = "www.baopqspkt.xyz";
const char *ssid = "PT";
const char *pass = "phamquocbao";
String ledsta = "0000";
String getdata = "1111";

void setup()
{
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

void loop()
{
    if (ledsta != getdata)
    {
        ledsta = getdata;
        if (ledsta.length() > 0)
        {
            WiFiClient client;
            const int httpPort = 80;
            if (!client.connect(host, httpPort))
            {
                Serial.println("connection failed");
                delay(5000);
                return;
            }
            String url = "/getstate.php?color=" + ledsta;
            Serial.println(url);
            client.print("GET " + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
            String content = "";
            while (client.connected())
            {
                int len = client.available();
                if (len > 0)
                {
                    content = content + String(char(client.read()));
                }
            }
            if ((content.length() < 200) && (content.length() >= 0))
            {
                content = content.substring(162, 166);
                //Serial.println(content);
                //Serial.println(content.length());
            }
            else
            {
                Serial.println(content.length());
            }
            client.stop();
            if (content.substring(0, 1) == "1")
            {
                String command = "0x11";
                mySerial.print(command);
            }
            else if (content.substring(0, 1) == "0")
            {
                String command = "0x01";
                mySerial.print(command);
            }
            if (content.substring(1, 2) == "1")
            {
                String command = "0x12";
                mySerial.print(command);
            }
            else if (content.substring(1, 2) == "0")
            {
                String command = "0x02";
                mySerial.print(command);
            }
            if (content.substring(2, 3) == "1")
            {
                String command = "0x13";
                mySerial.print(command);
            }
            else if (content.substring(2, 3) == "0")
            {
                String command = "0x03";
                mySerial.print(command);
            }
            if (content.substring(3, 4) == "1")
            {
                String command = "0x14";
                mySerial.print(command);
            }
            else if (content.substring(3, 4) == "0")
            {
                String command = "0x04";
                mySerial.print(command);
            }
            chophep = 0;
            getdata = "";
        }
    }
    while (mySerial.available())
    {
        delay(3);
        char c = (char)mySerial.read();
        getdata += c;
    }
    getdata.trim();

    if (getdata.length() > 0)
    {
        Serial.println("Length:");
        Serial.println(getdata.length());
        Serial.println(getdata);
    }
}
