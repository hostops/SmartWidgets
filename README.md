# Smartify
Smart house system based on OpenHAB2 and eclipse smarthome framework.
It uses MQTT comunication protocol.

###Security system
An alarm system is built with two widgets **AlarmSound** and **AlarmMotionSensor**. AlarmSound is widget which plays sound and flashing lights when AlarmMotionSensor detects motion. They comunicate over broker using MQTT.

AlarmSound controller: ESP8266 - ESP12F
AlarmMotionSensor controller: ESP8266 - ESP01  

###Remote light switch system
I wanted to try ESP8266 - ESP01 as WiFi module for Arduino boards. They comunicates over serial communication. Because of technical issues it uses servomotor to turn light on and off. With simple change of program you can controll light using relay. 
**ButtonPusher**: ESP8266 - ESP01 program - It communicates to broker. When it gets data it sends signal to Arduino to turn light on/off
**ButtonPusher_Arduino: Arduino program - When it recieves data form ESP01 it turns light on/off

To turn your light on or off just push "ON" or "OFF" command to you broker in category gTurn/sobaHostnik/mainLight. You can change that name if you want.

I created OpenHAB2 implementation for remote light switch system, so you can simply manipulate light using Andorid app (OpenHAB). OpehHAB2 configuration files are in  folder **"OpenHAB2Configuration"**.

I also created Cortana implementation. You only have to install solution **CustomCortanaCommands.sln** in folder **CortanaControll**.
The command prefix is "Listen up"
So you can say "Hey Cortana listen up turn the light on/off". All defined voice commands could be seen in **CortanaControl/CustomCortanaCommands/CustomVoiiceCommandDefinitions.xml**

