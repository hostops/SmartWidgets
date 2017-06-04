# Smartify
Smart house system based on OpenHAB2 and eclipse smarthome framework.
It uses MQTT comunication protocol. Seminar work: http://jakob-hostnik.rf.gd/contents/OpenHAB.pdf<br/>
<br/>

######Security system
An alarm system is built with two widgets **AlarmSound** and **AlarmMotionSensor**. AlarmSound is widget which plays sound and flashing lights when AlarmMotionSensor detects motion. They comunicate over broker using MQTT.<br/>

AlarmSound controller: ESP8266 - ESP12F<br/>
AlarmMotionSensor controller: ESP8266 - ESP01<br/>
Examples: <br/>
<img src="https://raw.githubusercontent.com/jakobhostnik/SmartWidgets/master/DemoContent/video2.gif" width="300px"/><br/>
<img src="https://raw.githubusercontent.com/jakobhostnik/SmartWidgets/master/DemoContent/image2.jpg" width="300px"/><br/>
######Remote light switch system
I wanted to try ESP8266 - ESP01 as WiFi module for Arduino boards. They comunicates over serial communication. Because of technical issues it uses servomotor to turn light on and off. With simple change of program you can controll light using relay.<br/> 
**ButtonPusher**: ESP8266 - ESP01 program - It communicates to broker. When it gets data it sends signal to Arduino to turn light on/off<br/>
**ButtonPusher_Arduino: Arduino program - When it recieves data form ESP01 it turns light on/off

To turn your light on or off just push "ON" or "OFF" command to you broker in category gTurn/sobaHostnik/mainLight. You can change that name if you want.<br/>

I created OpenHAB2 implementation for remote light switch system, so you can simply manipulate light using Andorid app (OpenHAB). OpehHAB2 configuration files are in  folder **"OpenHAB2Configuration"**.<br/>

I also created Cortana implementation. You only have to install solution **CustomCortanaCommands.sln** in folder **CortanaControll**.<br/>
The command prefix is "Listen up".<br/>
So you can say "Hey Cortana listen up turn the light on/off". <br/>
All defined voice commands could be seen in **CortanaControl/CustomCortanaCommands/CustomVoiiceCommandDefinitions.xml**.<br/>

Examples: <br/>
<img src="https://raw.githubusercontent.com/jakobhostnik/SmartWidgets/master/DemoContent/video1.gif" width="300px"/><br/>
<img src="https://raw.githubusercontent.com/jakobhostnik/SmartWidgets/master/DemoContent/image1.jpg" width="300px"/><br/>
<img src="https://raw.githubusercontent.com/jakobhostnik/SmartWidgets/master/DemoContent/image3.PNG" width="300px"/><br/>
<img src="https://raw.githubusercontent.com/jakobhostnik/SmartWidgets/master/DemoContent/image4.jpg" width="300px"/><br/>
<img src="https://raw.githubusercontent.com/jakobhostnik/SmartWidgets/master/DemoContent/image5.jpg" width="300px"/><br/>
<img src="https://raw.githubusercontent.com/jakobhostnik/SmartWidgets/master/DemoContent/image6.PNG" width="300px"/><br/>
<img src="https://raw.githubusercontent.com/jakobhostnik/SmartWidgets/master/DemoContent/image7.PNG" width="300px"/><br/>
<img src="https://raw.githubusercontent.com/jakobhostnik/SmartWidgets/master/DemoContent/image8.PNG" width="300px"/><br/>
