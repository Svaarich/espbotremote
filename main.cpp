#include <ESP8266WiFi.h>
#include <FastBot.h>

#define WIFI_SSID "wifi name"
#define WIFI_PASS "wifi password"
#define BOT_TOKEN "bot name"

#define RELAY_PIN 4

FastBot bot(BOT_TOKEN);

char* admin_id = "your telegram chat id";

// toggle pin to toggle relay
void togglePin() {
  digitalWrite(RELAY_PIN, HIGH);
  delay(500);                 
  digitalWrite(RELAY_PIN, LOW);  
}

// wifi connect
void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}

void performAction(char* chadID) {
  bot.sendMessage("Relay is toggled.", chadID);
      togglePin();
}

// send message
void successMessage(FB_msg& msg) {
  // action name created in BotFather (like default "/start")
  if (msg.text == "/action") {
    performAction(admin_id);
  }
}

// setup actions
void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  connectWiFi();
  bot.attach(successMessage);
}

// loop
void loop() {
  bot.tick();
}