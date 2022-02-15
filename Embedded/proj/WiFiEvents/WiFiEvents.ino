/*
    This sketch shows how to use WiFi event handlers.

    In this example, ESP8266 works in AP mode.
    Three event handlers are demonstrated:
    - station connects to the ESP8266 AP
    - station disconnects from the ESP8266 AP
    - ESP8266 AP receives a probe request from a station

    Written by Markus Sattler, 2015-12-29.
    Updated for new event handlers by Ivan Grokhotkov, 2017-02-02.
    This example is released into public domain,
    or, at your option, CC0 licensed.
*/

#include <ESP8266WiFi.h>
#include <stdio.h>

#ifndef APSSID
#define APSSID "esp8266"
#define APPSK  "esp8266"
#endif

const char* ssid     = APSSID;
const char* password = APPSK;

WiFiEventHandler stationConnectedHandler;
WiFiEventHandler stationDisconnectedHandler;
WiFiEventHandler probeRequestPrintHandler;
WiFiEventHandler probeRequestBlinkHandler;

bool blinkFlag,connection,disconnected;
int time_start;

void setup() {
  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  pinMode(D2, OUTPUT);

  // Don't save WiFi configuration in flash - optional
  WiFi.persistent(false);

  // Set up an access point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  // Register event handlers.
  // Callback functions will be called as long as these handler objects exist.
  // Call "onStationConnected" each time a station connects
  stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);
  // Call "onStationDisconnected" each time a station disconnects
  stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&onStationDisconnected);
  // Call "onProbeRequestPrint" and "onProbeRequestBlink" each time
  // a probe request is received.
  // Former will print MAC address of the station and RSSI to Serial,
  // latter will blink an LED.
}

void onStationConnected(const WiFiEventSoftAPModeStationConnected& evt) {
  Serial.print("Station connected: ");
  Serial.println(macToString(evt.mac));
  connection = true;
}

void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& evt) {
  Serial.print("Station disconnected: ");
  Serial.println(macToString(evt.mac));
  disconnected = true;
}


void loop() {

  delay(100);
  
  if(connection){
    connection = false;
    digitalWrite(D0, LOW);
    digitalWrite(D2, LOW);
    delay(1000);
    digitalWrite(D0,HIGH);
    digitalWrite(D2,HIGH);
    Serial.println("Power ON");
  }

//  if(disconnected){
//    disconnected = false;
//    digitalWrite(D0, LOW);
//    digitalWrite(D2, LOW);
//    delay(5500);
//    digitalWrite(D0,HIGH);
//    digitalWrite(D2,HIGH);
//    Serial.println("Power OFF");
//  }
  delay(10);
}

String macToString(const unsigned char* mac) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}
