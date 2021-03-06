// Author: Pham Quoc Bao
// Mail: baopq.spkt@gmail.com
// Modify 11/05/2019 by qb 
/*
 * Transfer data from server to STM32F4 
 * MAke file login auto
 * 
*/
 

#include <ESP8266WiFi.h>

const char* host = "www.baopqspkt.xyz";
String ssid;
String pass;

char ssid1[10];
char pass1[20];


void setup() {
  Serial.begin(115200);
   /* Set ESP8266 to WiFi Station mode */
  WiFi.mode(WIFI_STA);
  /* start SmartConfig */
  WiFi.beginSmartConfig();

  /* Wait for SmartConfig packet from mobile */
  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("SmartConfig done.");

  /* Wait for WiFi to connect to AP */
  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected.");
  ssid = WiFi.SSID();
  Serial.print("SSID: ");
  Serial.println(ssid);
  pass = WiFi.psk();
  Serial.print("PASSWORD: ");
  Serial.println(pass);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
//  int str_lenssid = ssid.length() + 1;   
//  int str_lenpass = pass.length() + 1;  
//  ssid.toCharArray(ssid1,str_lenssid);
//  pass.toCharArray(pass1,str_lenpass);
//  int i = 0;
//  Serial.print("ssid:");
//  for (i =0 ;i < str_lenssid;i ++)
//    Serial.print(ssid1[i]);
//  Serial.println();
//  Serial.print("pass:");
//  for (i =0 ;i < str_lenpass;i ++)
//    Serial.print(pass1[i]);
//  Serial.println();
  
 }

void loop() 
{
  
  //Serial.print("connecting to ");
  //Serial.print(host);
  //Serial.println();
  //WiFiClient client;
  
  while(Serial.available()==0);
  String ledsta;
  while (Serial.available() > 0)
    {
        ledsta = ledsta + String(char(Serial.read()));
        Serial.println(ledsta.length());
        Serial.println(ledsta); 
        //ledsta = Serial.readString();
  if(ledsta.length() == 4)
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
  
  //Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print("GET " + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  String content = "";
  while(client.connected())
  {
    int len = client.available();
    if (len > 0)
    {
      content = content + String(char(client.read())); 
      //content = client.readStringUntil('\r');
    }
  }
  if((content.length() < 200) && (content.length()>=0))
    {
      content = content.substring(162,166);
      Serial.println(content); 
    }
  else
    {
       Serial.println(content.length());
    }
  //Serial.println(content);
  if(!client.connected())
  {
    //Serial.println("Disconnectig...");
    //Serial.println();
    client.stop();
    delay(5000);
  }
  }
    }
}
