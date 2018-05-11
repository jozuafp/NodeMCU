#include <FS.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h> //library Http Client
#include <ArduinoJson.h> //library parse json

//for LED status
#include <Ticker.h>
Ticker ticker;

#define ON LOW
#define OFF HIGH

// Assign output variables to GPIO pins
// D0   = 16;
// D1   = 5;
// D2   = 4;
// D3   = 0;
// D4   = 2;
// D5   = 14;
// D6   = 12;
// D7   = 13;
// D8   = 15;
// D9   = 3;
// D10  = 1;

const int outputled    = 2;
const int outputrelay1 = 0;
const int outputrelay2 = 4;

// Set web server port number to 80
WiFiServer server(80);

//custom parameter
const char* relay_server = "http://echo.web.id/relay/relay.json";

//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
    Serial.println("Should save config");
    shouldSaveConfig = true;
}

void tick()
{
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
    pinMode(outputrelay1, OUTPUT);
    pinMode(outputrelay2, OUTPUT);

    // Set outputs to LOW
    digitalWrite(outputled, OFF);
    digitalWrite(outputrelay1, OFF);
    digitalWrite(outputrelay2, OFF);

    ticker.attach(0.6, tick);

    //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
  Serial.println("mounting FS...");

    if (SPIFFS.begin()) {
        Serial.println("mounted file system");
        if (SPIFFS.exists("/config.json")) {
            //file exists, reading and loading
            Serial.println("reading config file");
            File configFile = SPIFFS.open("/config.json", "r");
            if (configFile) {
                Serial.println("opened config file");
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                StaticJsonBuffer<200> jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                json.printTo(Serial);
                if (json.success()) {
                    Serial.println("\nparsed json");
                    if(json["relay_server"]) {
                        Serial.println("setting relay server");
                        relay_server = json["relay_server"];
                        Serial.println(relay_server);
                    } else {
                        Serial.println("no custom relay server");
                    }
                } else {
                    Serial.println("failed to load json config");
                }
            }
        }
    } else {
        Serial.println("failed to mount FS");
    }
    //end read
    Serial.println(relay_server);

    // id/name, placeholder/prompt, default, length
    WiFiManagerParameter custom_server("server", "Url Relay Server", relay_server, 128);

    // WiFiManager
    // Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;

    // If you want to erase all the stored information, run it once
    wifiManager.resetSettings();

    // set custom ip for portal
    //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    ////set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
    wifiManager.setAPCallback(configModeCallback);

    //set config save notify callback
    wifiManager.setSaveConfigCallback(saveConfigCallback);

    wifiManager.addParameter(&custom_server);

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

    //read updated parameters
   relay_server = custom_server.getValue();

    //save the custom parameters to FS
    if (shouldSaveConfig) {
        Serial.println("saving config");
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.createObject();
        json["relay_server"] = relay_server;
        File configFile = SPIFFS.open("/config.json", "w");
        if (!configFile) {
            Serial.println("failed to open config file for writing");
        }

        json.prettyPrintTo(Serial);
        json.printTo(configFile);
        configFile.close();
        //end save
    }
}

void loop(){
    
}
