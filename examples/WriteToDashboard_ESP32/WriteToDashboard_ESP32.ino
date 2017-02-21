
/*
 * This example demonstrate how to write data from your "Internet of Things" to IoTtweet dashboard
 * coding from IoTtweet.com
 * Created : 2017.Feb.14
 * By Isaranu Janthong
 * IoTtweet Founder.
 * Visit us at : www.iottweet.com
 */

#include <IoTtweetESP32.h>

const char *userid = "your-user-id";            //IoTtweet account user ID (6 digits, included zero pre-fix)
const char *key = "your-iot-key";               //IoTtweet registered device key in "MY IOT Garage"
const char *ssid = "your-ssid";                 //Your-WiFi-router-SSID
const char *password = "your-wifi-password";            //Your-WiFi-password

float data0, data1, data2, data3;                        //Your sending data variable.
String private_tweet = "Hello Node32s";                  //Your private tweet meassage to dashboard
String public_tweet = "Welceome IoTtweetESP32.h";        //Your public tweet message to dashboard

IoTtweetESP32 myiot;  //naming your devices

void setup() {
  
  Serial.begin(115200);

  //Get IoTtweet Library version
  String libvers = myiot.getVersion();
  Serial.println("IoTtweet Library vesion : " + String(libvers));

  //Connect WiFi
  Serial.println("\nConnect wifi...");
  bool conn = myiot.begin(ssid,password);

    if(!conn)
    {
      Serial.println("WiFi connection failed.");
    }else
    {
      Serial.println("WiFi connected !");
     }

}  

void loop() {

  //Example data generating
  data0 = random(20,80);
  data1 = random(30,70);
  data2 = random(40,60);
  data3 = random(50,55);

  //Send data from your iot to Dashboard
  String response = myiot.WriteDashboard(userid,key,data0,data1,data2,data3,private_tweet,public_tweet);
  Serial.println(response);   //Show response JSON from www.iottweet.com
  
  //Waiting storage data on IoTtweet cloud 15 sec.
  delay(15000);
}
