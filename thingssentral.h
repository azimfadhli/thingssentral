#pragma once
#include <WiFi.h>
#include <HTTPClient.h>

// for later update
/* #if defined(ESP8266)

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error "This board is not supported."
#endif*/

class thingssentral {
public:

  /*--------------------------------------------------*/
  /*---------------- GET DATA FROM TS ----------------*/
  /*--------------------------------------------------*/

  //FUNCTION DEFINITION
  //String readNode(String __NodeID, bool _repeat = false);

  // THIS FUNC WILL RETURN THE RESPONSE (STRING) FOR THE GIVEN NODE ID (STRING).
  String ICACHE_RAM_ATTR readNode(String __NodeID, bool _repeat = false) {
    HTTPClient http;
    //WiFiClient client;
    String completedLink = String("http://thingssentral.io/ReadNode?Params=tokenid|@NodeId|")
                            + __NodeID;

    http.begin(completedLink);
    http.GET();
    String _reply = http.getString();
    http.end();

    if (_reply == "") {
      Serial.println("BEBUG: error bro: " + __NodeID);
      if (_repeat == false) {
        return "e";
      } else {
        WiFi.disconnect();
        delay(1000);
        //wifiConnect();
        delay(1000);
        return readNode(__NodeID, true);
      }
    }
    //Serial.print("BEBUG: Full reply for: " + __NodeID + "\t==" + _reply + "==\t\t>");
    //Serial.println(_reply.substring(__NodeID.length() + 1, __NodeID.length() + 2));
    return _reply.substring(__NodeID.length() + 1, __NodeID.length() + 2);
  }


  /*--------------------------------------------------*/
  /*----------------- POST DATA TO TS ----------------*/
  /*--------------------------------------------------*/

  //FUNCTION DEFINITION
  /* String sendNode(String _NodeID1, String _Data1,
                  String _NodeID2 = "", String _Data2 = "",   //OPTIONAL PARAM
                  String _NodeID3 = "", String _Data3 = "",   //OPTIONAL PARAM
                  String _NodeID4 = "", String _Data4 = "");  //OPTIONAL PARAM
 */

  // THIS FUNC WILL RETURN THE RESPONSE (STRING) FOR THE GIVEN NODE ID AND ITS RESPECTIVE DATA.
  String ICACHE_RAM_ATTR sendNode(String _NodeID1, String _Data1,
                                  String _NodeID2 = "", String _Data2 = "",  //OPTIONAL PARAM
                                  String _NodeID3 = "", String _Data3 = "",  //OPTIONAL PARAM
                                  String _NodeID4 = "", String _Data4 = "")  //OPTIONAL PARAM
  {
    String completedLink = String("http://thingssentral.io/postlong?data=userid|");
    completedLink.concat(String("@") + _NodeID1 + "|" + String(_Data1));
    if (_NodeID2 != "") completedLink.concat(String("@") + _NodeID2 + "|" + String(_Data2));
    if (_NodeID3 != "") completedLink.concat(String("@") + _NodeID3 + "|" + String(_Data3));
    if (_NodeID4 != "") completedLink.concat(String("@") + _NodeID4 + "|" + String(_Data4));

    HTTPClient http;

    http.begin(completedLink);
    http.GET();
    String _reply = http.getString();
    http.end();

    Serial.println("Response: " + _reply);

    return _reply;
  }
};