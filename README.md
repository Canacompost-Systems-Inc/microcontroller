# Canacompost Microcontroller

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

## Quickstart Guide

### PlatformIO Installation

Our project uses PlatformIO to build and deploy code to the Arduino board. The easiest (and suggested) way to get started with PlatformIO is to [install the VSCode extension for it](https://docs.platformio.org/en/stable/integration/ide/vscode.html#installation). If you wish to use a different editor than VSCode you could [install the PlatformIO core CLI separately](https://docs.platformio.org/en/latest/core/quickstart.html).

### Deployment

There are two main ways to deploy code onto the Arduino: locally via serial port, or remotely via the IC.

To deploy locally, connect your computer to the Arduino via serial port, then click the PlatformIO upload button on the lower toolbar as seen in the image below. Note you can also build without uploading using the build button. See [this documentation](https://docs.platformio.org/en/stable/integration/ide/vscode.html#quick-start) for the offical quickstart guide.

![image](https://user-images.githubusercontent.com/31080408/209387336-6565a58f-e7c9-49d6-a599-55c26d0eecb7.png)

To deploy remotely SSH into the Jetson Nano and start the pio agent:

```
pio agent remote start
```

Then From your local machine, run the following if using the Mega 2560, which will compile your code locally and upload it to the remote device:

```
pio remote run --environment megaatmega2560 --target upload
```

You can also use the PlatformIO Tab by clicking the `Remote Development / Remote Upload` button as selected below

![image](https://user-images.githubusercontent.com/31080408/209388555-9cd0f0ec-7934-4f37-8f01-23221d42a3e4.png)

### Testing

Currently there are no automated tests for the MCU. Instead a python script is provided in `test/shell.py` which allows us to manually send commands to the MCU to test its behavior. Before running this script ensure that the MCU is connected via serial port to your computer (if working locally) or the IC (if working remotely). 

Next you will need to make sure the `serial_port` variable in `shell.py` is correctly set. To find the serial port that the MCU is connected to issue the following command (MacOS and Linux): 

```
ls /dev/tty*
```

This command should return a list of paths. The path corresponding to the MCU should have one of these prefixes: `/dev/ttyUSB*` or `/dev/ttyACM*`. Once you have found the correct serial port, update the `serial_port` variable. Then you can run the testing script (note you may need to use pip to install the `serial` library):

```
python ./shell.py
```

Finally, to send commands to the MCU enter one of the following (corresponding to endpoints defined in the [API Docs](/docs/api.md)).

Get Snapshot:
```
get all 
```

Get Device:
```
get <DID> 
```

Set Device:
```
set <DID> <New_Value>
```

### Debugging

If any error is encountered during operation the MCU will continuously print the error message string. Read from the serial port using the serial monitor to fetch these error messages.
