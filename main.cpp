#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

const char* ssid = "TP-LINK3232";
const char* password = "misha1234";
const int LED_PIN = 2; 

WebServer server(80);

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    LittleFS.begin();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    Serial.println("\nIP: " + WiFi.localIP().toString());

    // Serve HTML
    server.on("/", HTTP_GET, [](){
        File file = LittleFS.open("/index.html", "r");
        server.streamFile(file, "text/html");
        file.close();
    });

    // REST API Endpoint
    server.on("/api/v1/control", HTTP_POST, [](){
        if (server.hasArg("plain")) {
            String body = server.arg("plain");
            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, body);
            
            if (!error) {
                int state = doc["led"];
                digitalWrite(LED_PIN, state ? HIGH : LOW);
                server.send(200, "application/json", "{\"status\":\"success\"}");
                Serial.printf("LED State changed to: %d\n", state);
            } else {
                server.send(400, "application/json", "{\"status\":\"error\"}");
            }
        }
    });

    server.begin();
}

void loop() {
    server.handleClient();
}