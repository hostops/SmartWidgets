#include <SoftwareSerial.h>
#include <Servo.h>
Servo pusher;
void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == (char)1) {
      turnOn();
    }else{
      turnOff();
    }
      
  }
}

void turnOn() {
  pusher.attach(9);
  pusher.write(0);
  delay(1000);
  pusher.detach();
}
void turnOff() {
  pusher.attach(9);
  pusher.write(180);
  delay(1000);
  pusher.detach();
}
