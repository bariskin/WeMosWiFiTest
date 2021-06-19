/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ESP8266FtpServer.h>
#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

/* Set these to your desired credentials. */
const byte relay1 = 0;   //GPIO0
//const byte relay2 = 3;
//const byte relay3 = 5;
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer HTTP(80);
FtpServer FtpServer;

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
//void handleRoot() {
//  server.send(200, "text/html", "<h1>You are connected</h1>");
//  server.send(200, "text/html", "<h1> Tast input pin value:  </h1>");
//}


String relay_switch(void){
 
 byte state;
  if(digitalRead(relay1)){
      state = 0;
    }
    else {
      state = 1;
     }

   digitalWrite(relay1,state);
   Serial.println(String(state));
   return String(state);
}


void setup() {

  pinMode(relay1,OUTPUT);
  digitalWrite(relay1, LOW);
  //pinMode(relay2,OUTPUT);
  //digitalWrite(relay2, LOW);
  //pinMode(relay3,OUTPUT);
  //digitalWrite(relay3, LOW);
  
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  SPIFFS.begin(); // init file system
  HTTP.begin();   // init web server 
  //FtpServer.begin("relay", "relay");
  
  Serial.print("\nMy IP to connect via Web_bowser or FTP");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("\n");
  
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 // server.on("/", handleRoot);
 // server.begin();
 // Serial.println("HTTP server started");

 HTTP.on("/relay_switch", [](){
    HTTP.send(200,"text/plain", relay_switch());
  });
}

void loop() {
    HTTP.handleClient();

}
