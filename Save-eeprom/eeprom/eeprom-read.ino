#include <ESP8266WiFi.h>
#include <EEPROM.h>

String ssid = "PT";
String password = "phamquocbao";
int vtssid = 0, vtpass = 0, j = 0;
int ssidlength = 0, passlength = 0;
char *ssid1 = (char *)malloc(sizeof(ssid));
char *pass1 = (char *)malloc(sizeof(password));
void setup()
{
    Serial.begin(115200);
    /*EEPROM.begin(512);
    for (vtssid = 0; vtssid < ssidlength; vtssid++)
        EEPROM.write(vtssid, ssid[vtssid]);
    EEPROM.commit();
    vtpass = vtssid + password.length();
    for (; vtssid < vtpass; vtssid++)
    {
        EEPROM.write(vtssid, password[j]);
        j ++;
    }
    EEPROM.commit();
    EEPROM.write(100,ssidlength);
    EEPROM.commit();
    EEPROM.write(104,password.length());
    EEPROM.commit();*/

    ssidlength = EEPROM.read(100);
    passlength = EEPROM.read(104);
    delay(100);
    Serial.println("Done Write");
    String valpass = "";
    String valssid = "";

    for (vtssid = 0; vtssid < ssidlength; vtssid++)
        valssid = valssid + (char)EEPROM.read(vtssid);
    for (; vtssid < vtpass; vtssid++)
        valpass = valpass + (char)EEPROM.read(vtssid);

    for (vtssid = 0; vtssid < ssidlength; vtssid++)
    {
        *(ssid1 + vtssid) = valssid[vtssid];
    }
    for (vtpass = 0; vtpass < passlength; vtpass++)
    {
        *(pass1 + vtpass) = valpass[vtpass];
    }

    Serial.print("ssid1:\t");
    Serial.println(ssid1);
    Serial.print("pass1:\t");
    Serial.print(pass1);
    Serial.println();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid1, pass1);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    ;
}
