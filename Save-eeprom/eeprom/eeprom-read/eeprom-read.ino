#include <ESP8266WiFi.h>
#include <EEPROM.h>

String ssid = "";
String pass = "";
int vtssid = 0, vtpass = 0, j = 0;
int ssidlength = 0, passlength = 0;
int ena_smart = 0;

void smartconfig()
{
    WiFi.mode(WIFI_STA);
    WiFi.beginSmartConfig();
    while (!WiFi.smartConfigDone())
    {
        delay(500);
        Serial.println("Check smartconfig");
    }
    Serial.println("Waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi Connected.");
    ssid = WiFi.SSID();
    pass = WiFi.psk();
    EEPROM.begin(512);
    for (vtssid = 0; vtssid < ssid.length(); vtssid++)
        EEPROM.write(vtssid, ssid[vtssid]);
    EEPROM.commit();
    vtpass = vtssid + pass.length();
    for (; vtssid < vtpass; vtssid++)
    {
        EEPROM.write(vtssid, pass[j]);
        j++;
    }
    EEPROM.commit();
    EEPROM.write(100, ssid.length());
    EEPROM.commit();
    EEPROM.write(104, pass.length());
    EEPROM.commit();
    Serial.println("Done Write");
}
/*void readeeprom()
{
    int lan = 0;
    EEPROM.begin(512);
    ssidlength = EEPROM.read(100);
    passlength = EEPROM.read(104);
    Serial.println(ssidlength);
    Serial.println(passlength);
    char *ssid1 = (char *)malloc(ssidlength);
    char *pass1 = (char *)malloc(passlength);
    pass1 = "";
    String valpass = "";
    String valssid = "";

    for (vtssid = 0; vtssid < ssidlength; vtssid++)
    {
        //Serial.println(vtssid);
        valssid = valssid + (char)EEPROM.read(vtssid);
    }
    vtpass = vtssid + passlength;
    //Serial.println(vtpass);
    for (; vtssid < vtpass; vtssid++)
    {
        //Serial.print(vtssid);
        //Serial.println(valpass);
        valpass = valpass + (char)EEPROM.read(vtssid);
    }

    for (vtssid = 0; vtssid < valssid.length(); vtssid++)
    {
        *(ssid1 + vtssid) = valssid[vtssid];
    }
    for (vtpass = 0; vtpass < valpass.length(); vtpass++)
    {
        *(pass1 + vtpass) = valpass[vtpass];
    }
    Serial.println("ssid1:");
    Serial.println(ssid1);
    Serial.println("pass1:");
    Serial.println(pass1);
    WiFi.begin(ssid1,pass1);
    ssid1 = "";
    pass1 = "";
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Check EEPROM");
        //lan++;
        //if (lan == 3)
        //{
            //ena_smart = 1;
            //break;
        //}
    }
}*/
void setup()
{
    Serial.begin(115200);
    
    int lan = 0;
    EEPROM.begin(512);
    ssidlength = EEPROM.read(100);
    passlength = EEPROM.read(104);
    Serial.println(ssidlength);
    Serial.println(passlength);
    char *ssid1 = (char *)malloc(ssidlength);
    char *pass1 = (char *)malloc(passlength);
    String valpass = "";
    String valssid = "";

    for (vtssid = 0; vtssid < ssidlength; vtssid++)
    {
        valssid = valssid + (char)EEPROM.read(vtssid);
    }
    vtpass = vtssid + passlength;
    for (; vtssid < vtpass; vtssid++)
    {
        valpass = valpass + (char)EEPROM.read(vtssid);
    }

    for (vtssid = 0; vtssid < valssid.length(); vtssid++)
    {
        *(ssid1 + vtssid) = valssid[vtssid];
    }
    for (vtpass = 0; vtpass < valpass.length(); vtpass++)
    {
        *(pass1 + vtpass) = valpass[vtpass];
    }
    Serial.println("ssid1:");
    Serial.println(ssid1);
    Serial.println("pass1:");
    Serial.println(pass1);
    
    WiFi.begin(ssid1,pass1);
    ssid1 = "";
    pass1 = "";
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Check EEPROM");
        //lan++;
        //if (lan == 3)
        //{
            //ena_smart = 1;
            //break;
        //}
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
