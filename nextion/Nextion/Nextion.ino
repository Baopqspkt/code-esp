#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5);
String readString;
int chophep = 0;
const char *host = "www.baopqspkt.xyz";
const char *ssid = "PT";
const char *pass = "phamquocbao";

void endsend()
{
    mySerial.write(0xff);
    mySerial.write(0xff);
    mySerial.write(0xff);
}

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

    while (mySerial.available())
    {
        delay(3);
        char c = (char)mySerial.read();
        readString += c;
    }
    readString.trim();

    if (readString.length() > 0)
    {
        Serial.println("Length:");
        Serial.println(readString.length());
        Serial.println(readString);
    }
    if ((readString == "11") || (readString == "01") || (readString == "12") || (readString == "02") || (readString == "13") || (readString == "03") || (readString == "14") || (readString == "04"))
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
            Serial.println(content);
            Serial.println(content.length());
        }
        else
        {
            Serial.println(content.length());
        }
        client.stop();
        if(content.substring(0,1) == "1")
        {
          String command = "den1.val=1";
          mySerial.print(command);
          endsend();
        }
        else if(content.substring(0,1) == "0")
        {
          String command = "den1.val=0";
          mySerial.print(command);
          endsend();
        }
        if(content.substring(1,2) == "1")
        {
          String command = "den2.val=1";
          mySerial.print(command);
          endsend();
        }
        else if(content.substring(1,2) == "0")
        {
          String command = "den2.val=0";
          mySerial.print(command);
          endsend();
        }
        if(content.substring(2,3) == "1")
        {
          String command = "den3.val=1";
          mySerial.print(command);
          endsend();
        }
        else if(content.substring(2,3) == "0")
        {
          String command = "den3.val=0";
          mySerial.print(command);
          endsend();
        }
        if(content.substring(3,4) == "1")
        {
          String command = "den4.val=1";
          mySerial.print(command);
          endsend();
        }
        else if(content.substring(3,4) == "0")
        {
          String command = "den4.val=0";
          mySerial.print(command);
          endsend();
        }
        chophep = 0;
        readString = "";
    }
    else
    {
        readString = "";
    }
}
