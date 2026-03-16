#include <Arduino.h>
#include <WiFi.h>
#include <HTTPSServer.hpp>
#include <SSLCert.hpp>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>

using namespace httpsserver;

const char* ssid = "TP-LINK3232";
const char* password = "misha1234";

SSLCert cert = SSLCert(); 
HTTPSServer secureServer = HTTPSServer(&cert);

void handleSecureRoot(HTTPRequest * req, HTTPResponse * res) {
    // Basic Auth Check (admin:password base64 -> YWRtaW46cGFzc3dvcmQ=)
    if (req->getHeader("Authorization") != "Basic YWRtaW46cGFzc3dvcmQ=") {
        res->setStatusCode(401);
        res->setHeader("WWW-Authenticate", "Basic realm=\"CyberCore Secure Access\"");
        res->print("401 Unauthorized - Access Denied");
        return;
    }

    res->setHeader("Content-Type", "text/html");
    res->print("<!DOCTYPE html><html><body><h1>Secure Mainframe Active</h1><p>Operator: Mykhailo</p></body></html>");
}

void setup() {
    Serial.begin(115200);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(500);
    Serial.println("\nSecure link established: " + WiFi.localIP().toString());

    // Generate RSA-2048 Certificate
    int certRes = createSelfSignedCert(cert, KEYSIZE_2048, "CN=esp32.local,O=CyberCore,C=UA");
    if (certRes != 0) {
        Serial.println("Cert generation failed!");
        return;
    }

    ResourceNode * nodeRoot = new ResourceNode("/", "GET", &handleSecureRoot);
    secureServer.registerNode(nodeRoot);

    secureServer.start();
    Serial.println("HTTPS Terminal Ready on Port 443");
}

void loop() {
    secureServer.loop();
}