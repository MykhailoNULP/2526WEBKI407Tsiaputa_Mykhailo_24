#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

// --- WiFi Configuration ---
const char* ssid = "TP-LINK3232";
const char* password = "misha1234";

WebServer server(80);

void setup() {
    Serial.begin(115200);
    delay(1000); // Give time for Serial Monitor

    // 1. Initialize LittleFS
    Serial.println("\n--- Initializing LittleFS ---");
    if(!LittleFS.begin(true)){
        Serial.println("LittleFS Mount Failed!");
        return;
    }
    Serial.println("LittleFS mounted successfully.");

    // 2. Connect to WiFi
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP()); // THIS IS WHERE YOU FIND THE IP

    // 3. Configure Web Server
    server.on("/", HTTP_GET, [](){
        if(LittleFS.exists("/index.html")){
            File file = LittleFS.open("/index.html", "r");
            server.streamFile(file, "text/html");
            file.close();
        } else {
            server.send(404, "text/plain", "404: CyberCore File Not Found");
        }
    });

    // 4. Start Server
    server.begin();
    Serial.println("HTTP server started.");
}

void loop() {
    server.handleClient();
}