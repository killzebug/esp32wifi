#include "WiFi.h"
#include <WiFiClient.h>
#include <WebServer.h>
#include <cstdio>

WebServer server{};
const uint8_t ledPin = 4;
bool ledEnabled = true;
void sendPage()
{
  FILE* file = fopen("page.html","r");

  fseek(file,0,SEEK_END);
  size_t size = ftell(file);

  char* page = new char[size];
  rewind(file);
  fread(page,sizeof(char),size,file);
  server.send(200,"text/html",page);
}
void toggleLED()
{
  ledEnabled = !ledEnabled;
  digitalWrite(ledPin,ledEnabled);
}
void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);

  WiFi.begin("Freestyle");
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println("Connected");

  server.on("/", sendPage);

  server.on("/toggle",toggleLED);

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
  delay(10);
}
