#include <Arduino.h>
#include <ESPmDNS.h>

#include "ESPAsyncWebServer.h"

#include "indexHtml.h"

// Config
const int shutterPin = 27;
const int focusPin = 33;

AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi Failed!\n");
    return;
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP().toString());

  esp_err_t err = mdns_init();
  if (err)
  {
    printf("MDNS Init failed: %d\n", err);
    return;
  }
  mdns_hostname_set(DNS_NAME);

  pinMode(shutterPin, OUTPUT);
  pinMode(focusPin, OUTPUT);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", indexHtml); });

  server.on("/shutter", HTTP_POST, [](AsyncWebServerRequest *request)
            {
    digitalWrite(shutterPin, HIGH);
    delay(500);
    digitalWrite(shutterPin, LOW);
    request->send(200); });

  server.on("/focus", HTTP_POST, [](AsyncWebServerRequest *request)
            {
    digitalWrite(focusPin, HIGH);
    delay(500);
    digitalWrite(focusPin, LOW);
    request->send(200); });

  server.begin();
}

void loop()
{
  // noop
}
