#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "the HOSTNIK`s";
const char* password = "hostnik235";
const char* mqtt_server = "192.168.2.200";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  int c = 0;
  String dataString;
  String data = "";
  for (int i = 0; i < length; i++) {
    data += (char)payload[i];
  }
  if (data == "ON")
    Serial.print((char)1);
  else if (data == "OFF")
    Serial.print((char)2);
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      client.publish("gTurn/sobaHostnik/mainLight", "OFF");
      client.subscribe("gTurn/sobaHostnik/mainLight");
    } else {
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 2000) {
  }
}
