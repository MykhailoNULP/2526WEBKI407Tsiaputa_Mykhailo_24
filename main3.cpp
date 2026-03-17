#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

const char* ssid = "TP-LINK3232";
const char* password = "misha1234";

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22); // SDA, SCL
    
    if(!mag.begin()) {
        Serial.println("HMC5883L not found! Check wiring.");
    }
    
    LittleFS.begin();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(500);

    server.addHandler(&ws);
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *r){ r->send(LittleFS, "/index.html", "text/html"); });
    server.begin();
}

void loop() {
    ws.cleanupClients();
    static unsigned long last = 0;
    if (millis() - last > 500) {
        last = millis();
        
        sensors_event_t event;
        mag.getEvent(&event);
        float magnitude = sqrt(pow(event.magnetic.x, 2) + pow(event.magnetic.y, 2) + pow(event.magnetic.z, 2));

        
        Serial.print("Magnetometer Reading: ");
        Serial.print(magnitude);
        Serial.println(" uT");

        JsonDocument doc;
        doc["val"] = magnitude;
        String json;
        serializeJson(doc, json);
        ws.textAll(json);
    }
}