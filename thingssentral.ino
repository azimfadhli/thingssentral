// thsi is an example immplementing "thingssentral.h"

#include "thingssentral.h"

// create object TS
thingssentral TS;

// change the wifi parameter
const char *MainNetwork_SSID = "MyUiTM";
const char *MainNetwork_PASS = "12345678";

bool num = 0;
void connectwifi();

void setup() {
  Serial.begin(115200);

  // set the user Id for things sentral
  TS.userid = "0069101";

  connectwifi();
}


void loop() {

  Serial.print("read testnode: ");
  Serial.println(TS.readNode("testnode"));

  delay(3000);

  TS.sendNode("testnode", String(num));

  num = !num;
}


void connectwifi() {
  WiFi.mode(WIFI_AP);
  WiFi.begin(MainNetwork_SSID, MainNetwork_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("Wifi connedted, IP");
  Serial.println(WiFi.localIP());
}