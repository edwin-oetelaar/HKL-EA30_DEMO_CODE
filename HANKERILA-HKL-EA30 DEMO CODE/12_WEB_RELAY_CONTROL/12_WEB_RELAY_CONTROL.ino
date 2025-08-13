/* This program implements the function of the web side control relay. When the relay is closed, it is green and when it is opened, it is red */
/*hold on key "S2",it will set the board to AP mode -"HANKERILA-EA30"
input IP 192.168.4.1 ,it will enter to config wifi .
After the configuration is successful, restart EA30 and enter the new IP address(SSD1306 will display) again. The control page is displayed */
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PCF8574.h>

// Set the hotspot name and password in AP mode
const char *apSsid = "HANKERILA-EA30";
const char *apPassword = "";

// GPIO0 pins
const int resetPin = 0;


WebServer server(80);

// Store the list of WiFi networks
String scanNetworksID = "";

// Use the Preferences library to save and read the WiFi configuration
Preferences preferences;

// Define the width and height of the SSD1306 display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


PCF8574 pcf8574(0x22, 4, 5);

// Functions that handle client requests
void handleRoot() {
  String html = "<html><head><style>";
  html += "body { text-align: center; font-family: Arial, sans-serif; }";
  html += "h1 { margin-top: 20px; }";
  html += "select, input[type='password'] { width: 80%; height: 40px; margin: 10px auto; display: block; font-size: 16px; }";
  html += "input[type='submit'] { width: 50%; height: 40px; margin: 20px auto; display: block; font-size: 20px; }";
  html += "</style></head><body>";
  html += "<h1>WiFi Configuration</h1>";
  html += "<form method='POST' action='/connect'>";
  html += "<label for='ssid'>Select WiFi Network:</label><br>";
  html += "<select name='ssid' id='ssid'>";
  html += scanNetworksID;
  html += "</select><br>";
  html += "<label for='pass'>Password:</label><br>";
  html += "<input type='password' name='pass' id='pass'><br>";
  html += "<input type='submit' value='Connect'>";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

void handleConnect() {
  String ssid = server.arg("ssid");
  String pass = server.arg("pass");


  preferences.putString("ssid", ssid);
  preferences.putString("pass", pass);

  WiFi.begin(ssid.c_str(), pass.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

// Display the IP address on the SSD1306 display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();

  server.send(200, "text/html", "<html><body><h1>Connected!</h1></body></html>");
}

void handleRelayControl() {
  String html = "<html><head><style>";
  html += "body { text-align: center; font-family: Arial, sans-serif; }";
  html += "h1 { margin-top: 20px; }";
  html += ".button-container { display: flex; justify-content: center; margin-top: 20px; }";
  html += ".button { width: 15%; height: 40px; margin: 5px; display: inline-block; font-size: 16px; border: 1px solid #000; }";
  html += ".button.on { background-color: green; }";
  html += ".button.off { background-color: red; }";
  html += ".bottom-buttons { display: flex; justify-content: center; margin-top: 20px; }";
  html += ".bottom-button { width: 20%; height: 40px; margin: 10px; display: inline-block; font-size: 16px; border: 1px solid #000; }";
  html += "</style></head><body>";
  html += "<h1>Relay Control</h1>";
  html += "<h2>red is on | green is off</h2>";
  html += "<div class='button-container'>";
  for (int i = 4; i < 7; i++) {
    bool state = pcf8574.digitalRead(i);
    html += "<button class='button ";
    html += state ? "on" : "off";
    html += "' onclick='toggleRelay(" + String(i) + ")'>Relay " + String(i-3) + "</button>";
  }
  html += "</div>";
  html += "<div class='bottom-buttons'>";
  html += "<button class='bottom-button' onclick='toggleRelay(\"allon\")'>All On</button>";
  html += "<button class='bottom-button' onclick='toggleRelay(\"alloff\")'>All Off</button>";
  html += "</div>";
  html += "<script>";
  html += "function toggleRelay(id) {";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/relay?id=' + id, true);";
  html += "  xhr.send();";
  html += "  xhr.onreadystatechange = function() {";
  html += "    if (xhr.readyState == 4 && xhr.status == 200) {";
  html += "      location.reload();";
  html += "    }";
  html += "  };";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleRelay() {
  String relayId = server.arg("id");
  if (relayId == "allon") {
    for (int i = 4; i < 7; i++) {
      pcf8574.digitalWrite(i, LOW); // all on
    }
  } else if (relayId == "alloff") {
    for (int i = 4; i < 7; i++) {
      pcf8574.digitalWrite(i, HIGH); // all off
    }
  } else {
    int relayNum = relayId.toInt();
    if (relayNum >= 4 && relayNum <= 6) {
      bool state = pcf8574.digitalRead(relayNum);
      pcf8574.digitalWrite(relayNum, !state); 
    }
  }
  server.send(200, "text/html", "OK");
}

void setup() {
  Serial.begin(115200);


  preferences.begin("wifi", false);


  Wire.begin(4, 5); // GPIO4(SDA) GPIO15(SCL)
  for (int i = 4; i < 7; i++) {
    pcf8574.pinMode(i, OUTPUT);
  }

  
  pcf8574.begin();


  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  // display.display();
  delay(100); 
  display.clearDisplay();


  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("HANKERILA");
  display.display();

 
  String savedSsid = preferences.getString("ssid", "");
  String savedPass = preferences.getString("pass", "");

 // Try to connect to a saved WiFi network
  if (savedSsid != "") {
    WiFi.begin(savedSsid.c_str(), savedPass.c_str());
    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
      delay(500);
      Serial.print(".");
      retryCount++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(savedSsid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());

    // Display the IP address on the SSD1306 display
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("IP: ");
      display.println(WiFi.localIP());
      display.display();

     // Set the server route
      server.on("/", handleRelayControl);
      server.on("/relay", handleRelay);

      // Start the server
      server.begin();
      Serial.println("HTTP server started");
      return;
    }
  }

// If the saved WiFi network cannot be connected, enter AP mode
  WiFi.softAP(apSsid, apPassword);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Display the IP address of AP mode on the SSD1306 display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("IP: ");
  display.println(myIP);
  display.display();

// Scan the WiFi network
  int n = WiFi.scanNetworks();
  if (n == 0) {
    scanNetworksID = "No networks found";
  } else {
    for (int i = 0; i < n; ++i) {
      scanNetworksID += "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";
    }
  }

// Set the server route
  server.on("/", handleRoot);
  server.on("/connect", handleConnect);


  server.begin();
  Serial.println("HTTP server started");


  pinMode(resetPin, INPUT);
}

void loop() {
  server.handleClient();

 
  static unsigned long resetStartTime = 0;
  if (digitalRead(resetPin) == LOW) {
    if (resetStartTime == 0) {
      resetStartTime = millis();
    } else if (millis() - resetStartTime >= 5000) {
      // Clear the saved WiFi configuration
      preferences.clear();
      // Reset information is displayed on the SSD1306 display
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("WIFI reset done");
      display.println("IP is 192.168.4.1");
      display.display();
      // Restart the device
      ESP.restart();
    }
  } else {
    resetStartTime = 0;
  }
}
