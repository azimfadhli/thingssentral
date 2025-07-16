#include <ESP8266WiFi.h>
#include <NewPing.h>
#include <thingssentral.h>

String ssid = "Iot-AST";
String pass = "ast@1234";
String NodeID1 = "NUS01";

// Pin definitions for the HC-SR04 sensor
#define TRIGGER_PIN D1    // Trigger pin connected to D1 (GPIO5)
#define ECHO_PIN D2       // Echo pin connected to D2 (GPIO4)
#define MAX_DISTANCE 200  // Maximum distance to measure (in cm)

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  // Create a NewPing object

void setup() {
  Serial.begin(115200);  // Initialize serial monitor
  Serial.println("Ultrasonic Sensor Test");

  // Make sure the trigger and echo pins are set as outputs and inputs
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

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

  // Get the distance in cm
  unsigned int distance = sonar.ping_cm();

  if (distance > 0) {
    // Print the distance to the serial monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.print("Out of range ");
    Serial.println(distance);
  }
  
  //send data to thingssentral
  sendNode(NodeID1, String(distance));
  delay(30000);  // Delay 30s to prevent overloading
}
