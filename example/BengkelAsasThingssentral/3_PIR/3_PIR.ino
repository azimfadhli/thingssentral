#define PIR_PIN D2  // Change this to the pin you're using for the PIR sensor
#include <thingssentral.h>

String ssid = "Iot-AST";
String pass = "ast@1234";
String NodeID1 = "NPI01";


unsigned long previousMillis = 0; 
const long interval = 2000;        // Interval other task

void setup() {
  Serial.begin(115200);     // Start serial communication
  pinMode(PIR_PIN, INPUT);  // Set the PIR sensor pin as input

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
  unsigned long currentMillis = millis();  // Get the current time

  if (currentMillis - previousMillis >= interval) {
    // Here you can add other tasks or code that needs to run concurrently
    // For example, blink an LED or connect to WiFi, or any other function
    // This part of the code will not be blocked by the PIR sensor checking
    previousMillis = currentMillis;  // Save the last time you checked the sensor
  }



  // Time to check the PIR sensor
  int sensorState = digitalRead(PIR_PIN);  // Read the PIR sensor state
  if (sensorState == HIGH) {
    Serial.println("Motion Detected!");  // Print message when motion is detected

    //send data to thingssentral
    sendNode(NodeID1, String("1"));
    delay(30000); // Delay 30s to prevent overloading
  } else {
    Serial.println("No Motion");  // Print message when no motion is detected
  }

  delay(1000); //delay between motion sensing
}
