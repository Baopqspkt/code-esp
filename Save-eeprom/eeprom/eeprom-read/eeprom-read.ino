// Author: Pham Quoc Bao

#include <ESP8266WiFi.h>
#include <EEPROM.h>

int ena_smart = 0;
int lan = 0;

void smartconfig()
{
    String ssid = "";
    String pass = "";
    int vtssid, vtpass;
    int j = 0;
    WiFi.disconnect();
    WiFi.beginSmartConfig();
    Serial.println("Waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi Connected.");
    ssid = WiFi.SSID();
    pass = WiFi.psk();
    Serial.print("SSID: ");
    Serial.println(ssid.length());
    Serial.print("PASS: ");
    Serial.println(pass.length());
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
//get ssid from eeprom
char* ssideeprom()
{
    int ssidlength, vtssid;
    EEPROM.begin(512);
    ssidlength = EEPROM.read(100);
    Serial.print("SSID: ");
    Serial.println(ssidlength);
    char* ssid1 = (char *)malloc(ssidlength);
    String valssid = "";
    for (vtssid = 0; vtssid < ssidlength; vtssid++)
        valssid = valssid + (char)EEPROM.read(vtssid);
    valssid.trim();
    for (vtssid = 0; vtssid < ssidlength; vtssid++)
    {
        *(ssid1 + vtssid) = valssid[vtssid];
        Serial.print("Gia tri:");
        Serial.println (*(ssid1 + vtssid));
    }
    Serial.print("ssid1:");
    Serial.println(ssid1);
    return ssid1;
}
//get pass from eeprom
char* passeeprom()
{
    int ssidlength, passlength, vtpass, vtssid;
    EEPROM.begin(512);
    ssidlength = EEPROM.read(100);
    passlength = EEPROM.read(104);
    Serial.print("SSID Length: ");
    Serial.println(ssidlength);
    Serial.print("PASS Length: ");
    Serial.println(passlength);
    char* pass1 = (char *)malloc(passlength);
    pass1 = "";
    String valpass = "";
    vtpass = ssidlength + passlength;
    Serial.print("Vtpass: ");
    Serial.println(vtpass);
    for (vtssid = ssidlength; vtssid < vtpass; vtssid++)
        valpass = valpass + (char)EEPROM.read(vtssid);
    valpass.trim();
    for (vtpass = 0; vtpass < passlength; vtpass++)
    {
        *(pass1 + vtpass) = valpass[vtpass];
        Serial.print("Gia tri:");
        Serial.println(*(pass1 + vtpass));
    }
    Serial.print("pass1:");
    Serial.println(pass1);
    return pass1;
}

void setup()
{
    const char* ssid = "";
    const char* password = "";
    Serial.begin(9600);
    ssid = ssideeprom();
    password = passeeprom();
    Serial.print("ssid: ");
    Serial.println(ssid);
    Serial.print("password: ");
    Serial.println(password);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println(".");
        lan++;
        if (lan == 100)
        {
            ena_smart = 1;
            break;
        }
    }
    if (ena_smart == 1)
        smartconfig();
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    ;
}
