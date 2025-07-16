#include <Wire.h>
#include <BH1750.h>
#include <thingssentral.h>

String ssid = "Iot-AST";
String pass = "ast@1234";
String NodeID1 = "NLI01";

// Create an instance of the BH1750 sensor
BH1750 lightMeter;

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);  // SDA, SCL pins (D2 = GPIO4, D1 = GPIO5)

  // Initialize the BH1750 sensor
  if (lightMeter.begin()) {
    Serial.println("BH1750 sensor initialized.");
  } else {
    Serial.println("Error initializing BH1750 sensor.");
  }

  // connect to wifi
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
  // Read the light intensity (lux)
  float lux = lightMeter.readLightLevel();

  // Print the light intensity to the Serial Monitor
  Serial.print("Ambient Light Intensity: ");
  Serial.print(lux);
  Serial.println(" lux");

  //send data to thingssentral
  sendNode(NodeID1, String(lux));
  delay(30000);  // Delay 30s to prevent overloading
}
