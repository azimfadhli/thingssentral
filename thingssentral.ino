#include "thingssentral.h"

String ssid = "MyThingsSentral";
String pass = "12345678";
String nodeID = "001231010101";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println(".");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("Wifi connected, IP ");
  Serial.println(WiFi.localIP());
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(APIlinkRead);
  Serial.println(readNode(nodeID));
  Serial.println(APIlinkSent);
  sendNode(nodeID, "123");

  delay(5000);

  Serial.println(readNode(nodeID));
  sendNode(nodeID, "456");

  delay(5000);
}
