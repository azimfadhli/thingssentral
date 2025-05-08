String TSuserID = "00123";
String APIlinkRead = "http://thingssentral.io/ReadNode?Params=tokenid|" + TSuserID + "@NodeId|";
String APIlinkSent = "http://thingssentral.io/postlong?data=userid|" + TSuserID;

////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#if defined(ESP32)
#include <WiFi.h>
#include <HTTPClient.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#else
#error "This board is not supported."
#endif

String IRAM_ATTR GET(String completedLink) {
  HTTPClient http;

#ifdef ESP32
  http.begin(completedLink);
#else
  WiFiClient client;
  http.begin(client, completedLink);
#endif

  http.GET();
  String reply = http.getString();
  http.end();
  return reply;
}



/*--------------------------------------------------*/
/*---------------- GET DATA FROM TS ----------------*/
/*--------------------------------------------------*/
// THIS FUNC WILL RETURN THE RESPONSE (STRING) FOR THE GIVEN NODE ID (STRING).
String IRAM_ATTR readNode(String __NodeID, bool _fullReply = false) {
  String _reply = GET(APIlinkRead + __NodeID);
  if (_reply == "") {
    Serial.println("thingssentral.h: error, blank reply from server. Check connection. : " + __NodeID);
    return "error";
  }

  String _valueOnly = _reply.substring(_reply.indexOf("|") + 1,
                                       _reply.indexOf("|", _reply.indexOf("|") + 1));
  Serial.println("thingssentral.h: readNode: " + _valueOnly);

  if (_fullReply) {
    return _reply;
  } else {
    return _valueOnly;
  }
}


/*--------------------------------------------------*/
/*----------------- POST DATA TO TS ----------------*/
/*--------------------------------------------------*/
// THIS FUNC WILL RETURN THE RESPONSE (STRING) FOR THE GIVEN NODE ID AND ITS RESPECTIVE DATA.
String IRAM_ATTR sendNode(String _NodeID1, String _Data1,
                          String _NodeID2 = "", String _Data2 = "",  //OPTIONAL PARAM
                          String _NodeID3 = "", String _Data3 = "",  //OPTIONAL PARAM
                          String _NodeID4 = "", String _Data4 = "")  //OPTIONAL PARAM
{
  String completedLink = APIlinkSent;
  completedLink.concat(String("@") + _NodeID1 + "|" + String(_Data1));
  if (_NodeID2 != "") completedLink.concat(String("@") + _NodeID2 + "|" + String(_Data2));
  if (_NodeID3 != "") completedLink.concat(String("@") + _NodeID3 + "|" + String(_Data3));
  if (_NodeID4 != "") completedLink.concat(String("@") + _NodeID4 + "|" + String(_Data4));

  String _reply = GET(completedLink);
  if (_reply == "") {
    Serial.println("thingssentral.h: error, blank reply from server. Check connection.");
    return "error";
  }

  Serial.println("thingssentral.h: sendNode: " + _reply);
  return _reply;
}