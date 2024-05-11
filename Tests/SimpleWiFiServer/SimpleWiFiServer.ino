/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the RGB LED.

 If the IP address of your shield is yourAddress:
 http://yourAddress/G turns the LED GREEN
 http://yourAddress/R turns it RED
  http://yourAddress/B turns it BLUE


 This example is written for a network using WPA2 encryption. For insecure
 WEP or WPA, change the Wifi.begin() call and use Wifi.setMinSecurity() accordingly.

 Circuit:
 * WiFi shield attached
 * RGB led
 */

#include <WiFi.h>
#include <BDL.h>
BDL bdl; 
const char* ssid     = "Krishna";
const char* password = "zxcv0987";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
 bdl.begin();
    //remove this code in production as it breaks the code ,, this is only for testing right now
    // --------------------------------------------
    while(!Serial){
      delay(10);
    }
    // ---------------------------------
    
    bdl.setPixelBrightness(255 / 2);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

void loop(){
  
}
