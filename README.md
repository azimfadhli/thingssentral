# Thingssentral Library for ESP Devices

![ESP32 and ESP8266 Compatible](https://img.shields.io/badge/ESP32%20%26%20ESP8266-Compatible-brightgreen)
![MIT License](https://img.shields.io/badge/License-MIT-blue)

A lightweight library for ESP8266 and ESP32 devices to interact with Thingsentral servers. Easily read data from and send data to Thingsentral server with support for up to 4 nodes per request.

## Features

- 📶 Simple HTTP communication with Thingsentral servers
- 📥 Read data from server nodes
- ⬆️ Send data to up to 4 nodes in a single request
- 🛠️ ESP32 and ESP8266 compatible
- 📊 Built-in error handling and diagnostics
- ⚡ IRAM_ATTR optimized for ESP32 performance

## Installation

1. Download the latest release as a ZIP file
2. In Arduino IDE: 
   - `Sketch` → `Include Library` → `Add .ZIP Library...`
3. In PlatformIO:
   - Add to `lib_deps` in your `platformio.ini`:
   ```ini
   lib_deps = 
        https://github.com/yourusername/thingssentral.git
   ```

## Usage

### 1. Configuration
```cpp
#include "thingssentral.h"

// Configure your credentials
String TSuserID = "YOUR_USER_ID";  // Replace with your Thingsentral ID
String APIlinkRead = "http://your-server.io/ReadNode?Params=tokenid|" + TSuserID + "@NodeId|";
String APIlinkSent = "http://your-server.io/postlong?data=userid|" + TSuserID;
```

### 2. Reading Data from Server
```cpp
void setup() {
  Serial.begin(115200);
  WiFi.begin("SSID", "PASSWORD");
  
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  // Read single node value
  String temperature = readNode("TEMP01");
  Serial.println("Temperature: " + temperature);
  
  // Get full server response
  String fullResponse = readNode("HUMID01", true);
  Serial.println("Full response: " + fullResponse);
}
```

### 3. Sending Data to Server
```cpp
void loop() {
  // Send single node data
  sendNode("LED01", "ON");
  
  // Send multiple nodes (up to 4)
  sendNode(
    "TEMP01", "23.5", 
    "HUMID01", "45.2",
    "PRESS01", "1013",
    "STATUS", "OK"
  );
  
  delay(60000); // Send data every minute
}
```

## API Reference

### `String readNode(String nodeID, bool fullReply = false)`
Reads data from a server node
- `nodeID`: Target node identifier
- `fullReply`: Return full server response (default: value only)
- Returns: Node value or full response string

### `String sendNode(String nodeID1, String data1, ...)`
Sends data to server nodes
- Supports 1-4 node/data pairs
- Parameters:
  - `nodeID1`: First node ID
  - `data1`: First node's data
  - `nodeID2`-`nodeID4`: Additional nodes (optional)
  - `data2`-`data4`: Additional data (optional)
- Returns: Server response string

## Error Handling
- Returns "error" string on connection failures
- Serial monitor outputs diagnostics:
  - Successful reads: `thingssentral.h: readNode: [value]`
  - Failed reads: `thingssentral.h: error, blank reply from server...`

## Requirements
- ESP32 or ESP8266
- WiFi connection
- Arduino IDE or PlatformIO
- Dependencies:
  - ESP32: `WiFi.h`, `HTTPClient.h`
  - ESP8266: `ESP8266WiFi.h`, `ESP8266HTTPClient.h`

## Example Output
```
[WiFi] Connected!
thingssentral.h: readNode: 23.5
thingssentral.h: sendNode: OK
thingssentral.h: sendNode: ACK 4 NODES
```

## Contributing
Pull requests are welcome! For major changes, please open an issue first to discuss proposed changes.

## License
[MIT License](LICENSE)
