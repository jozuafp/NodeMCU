#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h> //library Http Client

//for LED status
#include <Ticker.h>
Ticker ticker;

#define ON LOW
#define OFF HIGH

const int outputled = 2;

// Set web server port number to 80
WiFiServer server(80);


void tick() {
    //toggle state
    int state = digitalRead(outputled);  // get the current state of GPIO1 pin
    digitalWrite(outputled, !state);     // set pin to the opposite state
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
    Serial.println("Entered config mode");
    Serial.println(WiFi.softAPIP());
    //if you used auto generated SSID, print it
    Serial.println(myWiFiManager->getConfigPortalSSID());
    //entered config mode, make led toggle faster
    ticker.attach(0.2, tick);
}

void setup() {
    Serial.begin(115200);

    // Initialize the output variables as outputs
    pinMode(outputled, OUTPUT);

    // Set outputs to LOW
    digitalWrite(outputled, OFF);

    ticker.attach(0.6, tick);

    WiFiManager wifiManager;

    // If you want to erase all the stored information, run it once
    wifiManager.resetSettings();
    // set custom ip for portal
    //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
    ////set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
    wifiManager.setAPCallback(configModeCallback);

    wifiManager.setMinimumSignalQuality();

    Serial.println("Connected Device...");

    // connect to AP WiFi
    if (!wifiManager.autoConnect("OkeRelay")) {
        Serial.println("failed to connect and hit timeout");
        //reset and try again, or maybe put it to deep sleep
        ESP.reset();
        delay(1000);
    }

    server.begin();

    //if you get here you have connected to the WiFi
    Serial.println("Connected WiFi...");
    ticker.detach();
    digitalWrite(outputled, OFF);
}

void loop(){
}
