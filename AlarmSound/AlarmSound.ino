/*
  Basic ESP8266 MQTT example

  This sketch demonstrates the capabilities of the pubsub library in combination
  with the ESP8266 board/library.

  It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.

  To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define TONE_PIN 5
#define ALARM_LED_1 14
#define ALARM_LED_2 12
#define NOTE_G3  196
#define NOTE_C3  131
// Update these with values suitable for your network.

const char* ssid = "the HOSTNIK`s";
const char* password = "hostnik235";
const char* mqtt_server = "192.168.2.200";

WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  pinMode(ALARM_LED_1, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(ALARM_LED_2, OUTPUT); 
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    alarm();
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Alarm")) {
      Serial.println("connected");
      client.subscribe("gTurn/motionSensor");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void alarm() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ALARM_LED_1, (boolean)i%2);
    digitalWrite(ALARM_LED_2, (boolean)(i+1)%2); 
    tone(TONE_PIN, NOTE_G3, 250);
    delay(250 * 1.30);
    noTone(8);
    
    tone(TONE_PIN, NOTE_C3, 250);
    delay(250 * 1.30);
    noTone(8);
  }
  digitalWrite(ALARM_LED_1, LOW);
    digitalWrite(ALARM_LED_2, LOW); 
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
