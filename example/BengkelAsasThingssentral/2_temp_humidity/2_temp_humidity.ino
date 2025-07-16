#include <DHT.h>
#include <thingssentral.h>

String ssid = "Iot-AST";
String pass = "ast@1234";
String NodeIDtemp = "NTH01-T";
String NodeIDhumidity = "NTH01-H";

#define DHTPIN D4      // Define the pin where the DHT11 data pin is connected
#define DHTTYPE DHT11  // Define the type of DHT sensor (DHT11 in this case)

DHT dht(DHTPIN, DHTTYPE);  // Initialize the DHT sensor

void setup() {
  Serial.begin(115200);  // Start the Serial Monitor at 115200 baud rate
  dht.begin();           // Initialize the DHT sensor

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
  // Read the humidity and temperature values
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any read failed and exit early (NaN means failure)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the results to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %\t");
  //send data to thingssentral
  sendNode(NodeIDhumidity, String(humidity));

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  //send data to thingssentral
  sendNode(NodeIDtemp, String(temperature));
  delay(30000);  // Delay 30s to prevent overloading
}
