#include <Arduino.h>
#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <Preferences.h>

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
WebServer server(80);
Preferences preferences;

void setup() {
    Serial.begin(115200);
    LittleFS.begin();

    // 1. Setup AP Mode (Access Point)
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("CyberCore_Station_Mykhailo");

    // 2. Start DNS Server (Captive Portal)
    dnsServer.start(DNS_PORT, "*", apIP);

    // 3. Web Server Routes
    server.on("/", HTTP_GET, []() {
        File file = LittleFS.open("/index.html", "r");
        server.streamFile(file, "text/html");
        file.close();
    });

    server.on("/save", HTTP_POST, []() {
        String ssid = server.arg("ssid");
        String pass = server.arg("pass");
        
        preferences.begin("wifi-config", false);
        preferences.putString("ssid", ssid);
        preferences.putString("pass", pass);
        preferences.end();

        server.send(200, "text/html", "<h2>DATA RECEIVED. REBOOTING SYSTEM...</h2>");
        delay(2000);
        ESP.restart();
    });

    // 4. Captive Portal Redirect
    server.onNotFound([]() {
        server.sendHeader("Location", String("http://") + apIP.toString(), true);
        server.send(302, "text/plain", "");
    });

    server.begin();
    Serial.println("Captive Portal is LIVE.");
}

void loop() {
    dnsServer.processNextRequest();
    server.handleClient();
}