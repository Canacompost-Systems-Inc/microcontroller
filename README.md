# CanaCompost Microcontroller

## Introduction
This repository contains the microcontroller code which will receive commands from the Integrated Computer (Jetson Nano) and then execute them by turning actuators or polling the sensors for data.

### Acronyms

* **IC** = Integrated Computer
* **MCU** = MicroController Unit

### Resources

* [API Docs](/docs/api.md): Reference on how to interface with the MCU and its devices using serial communication.
* [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html#Class_Format): Coding standard which this repo follows.
* [High-Level Architecture](https://app.nuclino.com/Canacompost-Systems/Canacompost/High-Level-Architecture-2d4dbe05-6e8d-4563-9f24-c729c32722a6): Links to high-level diagram and documentation.
* [Leo's Original Implementation](https://github.com/leomorpho/compost-manager-embedded/blob/221d68fc25802f619a93a790fc751dfb9ebc9471/src/main.cpp): The original prototype implementation.

## Getting Started

### PlatformIO 

WIP

### Arduino connected to Jetson Nano

SSH into the Jetson Nano and start the pio agent:
```
pio agent remote start
```

From your local machine, run the following if using the Mega 2560, which will compile your code locally and upload it to the remote device:
```
pio remote run --environment megaatmega2560 --target upload
```
### Arduino connected to computer

Just use Platformio in VSCode or whatever you prefer. There are guides online to help.

### How to Test

WIP