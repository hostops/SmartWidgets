#define GPIO2 2

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "Hostnik J";
const char* password = "geslo123";
const char* mqtt_server = "192.168.137.87";
unsigned int lastMsg =  0;
WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
  pinMode(GPIO2, INPUT);     // Initialize the BUILTIN_LED pin as an output
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("MotionSensor")) {
      client.publish("gTurn/motionSensor", "Connected");
    } else {
      delay(5000);
    }
  }
}
boolean previousState = false;
int minutesCounter = 0;
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 100) {
    boolean currentState = digitalRead(GPIO2);
    minutesCounter++;
    
    //on every 0.1s - send to alarm
    if (currentState) {
      client.publish("gTurn/motionSensor", "1");
    } else {
      client.publish("gTurn/motionSensor", "0");
    }
    lastMsg = now;
    
    //on change || on 30 seconds - send to openhab
    if ((previousState ^ currentState) || (minutesCounter > 300)) {
      if (currentState) {
        client.publish("gTurn/motionSensor/openHAB", "1");
      } else {
        client.publish("gTurn/motionSensor/openHAB", "0");
      }
      previousState = currentState;
      minutesCounter=0;
    }
  }
}

