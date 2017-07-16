/**
 * LM92 Library
 * Kerry D. Wong
 * http://www.kerrywong.com
 * 1/2014
 *
 * Read temperature in Celsius.
 */

#include <LM92.h>
#include <Wire.h>
#include <ThingSpeak.h>

#include <ESP8266WiFi.h>
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>        //https://github.com/tzapu/WiFiManager

// const char* ssid     = "papaya";
// const char* password = "papaya2014";
// int status = WL_IDLE_STATUS;
WiFiClient  client;


LM92 lm92(0,1);  //address 1, 0

unsigned long myChannelNumber = 297575;
const char * myWriteAPIKey = "95P28PYJT1I8PKUY";

uint32_t sleep_time_s = 2 * 60 * 1000000;

void setup()
{
      // We start by connecting to a WiFi network
    Serial.begin(9600);
    WiFiManager wifiManager;
    wifiManager.autoConnect("ESP8266");
    Serial.println("connected...yeey :)");
    Wire.begin();

    lm92.enableFaultQueue(true); //optional, make readings more tolerent to inteference
    lm92.ResultInCelsius = true;  //change to Celsius mode

    ThingSpeak.begin(client);

}

void loop()
{
    float temperatura = lm92.readTemperature();
    Serial.println(temperatura);
    ThingSpeak.writeField(myChannelNumber, 1, temperatura, myWriteAPIKey);
    //delay(20000);
    ESP.deepSleep(sleep_time_s, WAKE_RF_DEFAULT);
}
