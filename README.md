# Wireless Environmental Monitoring Platform

<img width="4624" height="2604" alt="rn_image_picker_lib_temp_3451f50a-21aa-435d-9f39-d2db277a8afb" src="https://github.com/user-attachments/assets/5c99ced6-332a-4838-a1e1-a47c6f04edf2" />

A remotely operated mobile robotics platform engineered for atmospheric data acquisition and exploration. The system enables remote clontrol of the driving platform and acquisition of humidity, pressure and temperature of air. Key feature is modularity - most parts can be changed without changing others and the whole robot, allowing for diffrent configurations.

This robot was made in collaboration with @Pita5488, who programed and installed the sensors, made the final versions of the code and of the KiCad scheme, etc.



# Key features
 - wireless control
 - modularity
 - built for uneven urban terrain
 - records temperature, pressure and humidity of the air

<br>

# Architecture
## Software and digital tool and languages:
 - Arduino IDE
 - KiCad
 - C/C++
 - Python
 - VScode
 - Tinkercad

## Hardware
 - Arduino Rev 4 Wifi/BT
 - L298N engine driver
 - 18650 batteries
 - WS2812 led stripe
 - DHT11 temperature and humidity sensor
 - HC-SR04 UV distance sensor
 - BMP280 digital barometer
 - yellow 3-6V DC Motors
 - other electronic

## Construction
- wooden main corpus
- wooden electronics board
- 3D-printed wheel guides

# in depth look
## Robots pourpose
Robot's main function is to record meterological data, while being remotely controled. 
The wireless control system allows the user to reach terrains humans can't or should't because of possible danger, like vents, contruction zones, post accidents zones like labs, radioactive terrain, etc.

## About software
We used the Arduino IDE, as it suited our need. We programmed the sensors, engines, etc., in many .h files to make the project clearer.

We decided that the robot should be controlled via laptop, so we created a Python app, allowing us to do so.

## About hardware
Our hardware was mostly mounted on the electronics board on the top of the robot.

## About construction
The whole idea of the robot was 1) to be large, so that it can be used in ubran enviroment, 2) to be modular, so that we can use it for many things.

Robots size is aprox. 50 cm in lenght, 25 in width and 30 in height. We decided to use wood for large parts of the robot, since PETG would be less sturdy, and wouldn't allow us to easily use bolts to mount it.

The main corpus is entirely made out of wpieces of wood bolted togather - the top part of the main corpus and sides used to bolt guides in.

Guides are made out of PETG using a 3D-printer. They have a 45° curve, to further strenghten its abilities to manuver in unever terrain

At the very top sits the electronics board, on which we mounded electronics like Arduino, engine drives, batteries and the breadboard with sensors.

# Modularity: The key aspect of Robot's construction
From the very beggining we decided to have a modelar build of the robot.

What does it mean?

It means that you can change almost every part easily and without changing any other parts.
We used M3 bolts with nuts on guides and the electronics board with, aloowing use to swapp them simply by unscrewing a few bolts.

Each engine guide (or "leg") can be individualy changed, allowing for diffrent configurations - feature which I already use (more about this is "What's next?" senction further down).
The detachable electronics board has also already come in handy - when I needed to code or tinker around it, i just detached it and didn't have to bring the whole robot with me.
It also allows the robot to have multiple pourposes, since all it takes to completly change the electronics is to swap in the new boards, connect engines to the driver, and you are good to go.

# What's still to fix?
The main problem with the robot is it size and weight - it causes the rotation of the to be very slow and unreliable.

During our testing we understood that because of robot's size, weight and teh fact that it's a skid-steer robot, it will not rotate well in this configuration.

Which takes us to...

# What's next?
--> The 2.0 version

What I aim to acomplish now is to piece by piece change the robot, so that the movement problem will be fixed.
My engineering thesis patreon sugested to use passive wheels on the back, so that you only need to motors to control the robot.
This idea was already implemented by me - unsuprisingly it did 2 things: fix the movement issue and create new problems.
The problem was that 2 engines at which power supply don't have enough torque for the robot to rotate, as well as it showed that the main corpus of the robot is askewed.

Hence the plan is:
 - test the robot with a new power supply
 - change every wooden part to a 3D-printed one or keep it wooden, but cut wood with a laser, instead of by hand
 - if succefull with previous points - include autonomous software.

 






