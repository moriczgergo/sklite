#include "config.h"
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <stdio.h>

#ifdef C_STATIC_IP
IPAddress ip(C_IP[0], C_IP[1], C_IP[2], C_IP[3]);
IPAddress gateway(C_GATEWAY[0], C_GATEWAY[1], C_GATEWAY[2], C_GATEWAY[3]);
IPAddress subnet(C_SUBNET[0], C_SUBNET[1], C_SUBNET[2], C_SUBNET[3]);
#endif

CRGB leds[C_LEDCOUNT];
ESP8266WebServer server(80);

const char* ssid = C_SSID;
const char* password = C_PASS;

uint8_t r = 255;
uint8_t g = 0;
uint8_t b = 255;
bool isOff = true;

void setup() {
  Serial.begin(9600);

  // CHANGE SETTINGS HERE:
  LEDS.addLeds<P9813, D4, D3>(leds, C_LEDCOUNT);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
#ifdef C_STATIC_IP
  WiFi.config(ip, gateway, subnet);
#endif

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected!");

  server.on("/color", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (server.args() == 0) server.send(200, "text/plain", colToHex());
    else {
      char* hex = (char*)malloc(7);
      memset(hex, 0, 7);
      server.arg(0).toCharArray(hex, 7);
      hexToCol(hex);
      leds[0] = CRGB(r, g, b);
      if (!isOff) FastLED.show();
      server.send(200, "text/plain", "");
    }
  });
  server.on("/", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (server.args() == 0) server.send(200, "text/plain", isOff ? "0" : "1");
    else {
      isOff = server.arg(0) == "0";
      if (isOff) leds[0] = CRGB(0, 0, 0);
      else leds[0] = CRGB(r, g, b);
      FastLED.show();
      server.send(200, "text/plain", "");
    }
  });

  server.begin();
  Serial.println("Server up and running...");

  Serial.println(WiFi.localIP());

  if (isOff) leds[0] = CRGB(0, 0, 0);
  else leds[0] = CRGB(r, g, b);
  FastLED.show();
}

char* colToHex() {
  char* out = (char*)malloc(7);
  memset(out, 0, 8);
  sprintf(out, "%02X%02X%02X", r, g, b);
  return out;
}

void hexToCol(char* hex) {
  long int rgb = strtoul(hex, NULL, 16);
  r = (rgb >> 16) & 255;
  g = (rgb >> 8) & 255;
  b = rgb & 255;
}

void loop() {
  server.handleClient();
}
