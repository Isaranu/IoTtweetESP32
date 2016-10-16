/*
library for IoTtweet.com, using via api.iottweet.com
Compatible use with ESP32 WiFi and BLE chip from espressif.

Created by : IoTtweet tech. team
Date : 2016.Oct.15
*/

#include "IoTtweetESP32.h"

#define IoTtweetESP32_HOST "api.iottweet.com"
#define IoTtweetESP32_PORT 80
#define IoTtweetESP32_libVersion "v0.0.1-Alpha"

//Make a connection wifi
bool IoTtweetESP32::begin(const char *ssid, const char *passw)
{
  //Delay for chip loadin configuration.
  delay(1000);

  //Transfer variable
  _ssid = ssid;
  _passw = passw;

  int _cnt=0, _retry=1000; /*Normal retry 40 times, we set to 1000 cycle.*/
  bool _conn = false;

  //Connect WiFi
  WiFi.begin(_ssid,_passw);

  //Connecting WiFi
  while ((WiFi.status() != WL_CONNECTED) && (_cnt <= _retry))
  {
    delay(200);
    Serial.print(".");
    _cnt++;
  }

  if(WiFi.status() == WL_CONNECTED)
  {
    _conn = true;
    Serial.println("\nWiFi for IoTtweetESP32 Connected !");
    Serial.print("IP : ");
    Serial.print(WiFi.localIP());
  }else{
    _conn = false;
  }

  return _conn;
}

//Connect to api.iottweet.com & send data to dashboard
String IoTtweetESP32::WriteDashboard(const char *userid, const char *key, int slot0, int slot1, int slot2, int slot3, const char *tw, const char *twpb)
{
    //Transfer variable
    _userid = userid;
    _key = key;
    _slot0 = slot0;
    _slot1 = slot1;
    _slot2 = slot2;
    _slot3 = slot3;
    _tw = tw;
    _twpb = twpb;

    //Create connection TCP to api.iottweet.com
    WiFiClient client;

    if (client.connect(IoTtweetESP32_HOST, IoTtweetESP32_PORT))
    {
      //Start sending data package
      _str = "GET /?userid=";
      _str += _userid;
      _str += "&key=";
      _str += _key;
      _str += "&slot0=";
      _str += _slot0;
      _str += "&slot1=";
      _str += _slot1;
      _str += "&slot2=";
      _str += _slot2;
      _str += "&slot3=";
      _str += _slot3;
      _str += "&tw=";
      _str += _tw;
      _str += "&twpb=";
      _str += _twpb;
      _str += " HTTP/1.1\r\n";
      _str += "Host: api.iottweet.com\r\n";
      _str += "Connection: keep-alive\r\n\r\n";

      //Push data to api.iottweet.com
      client.print(_str);

      //Check response back
      while(client.available()){
        _response = client.readStringUntil('\r');
      }
      return _response;
    }
}

//Get IoTtweet library version information
String IoTtweetESP32::getVersion()
{
  return IoTtweetESP32_libVersion;
}
