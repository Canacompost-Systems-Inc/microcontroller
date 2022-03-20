# Introduction
This repository contains the microcontroller code which will receive commands from the Integrated Computer (Jetson Nano) and then execute them by turning actuators or polling the sensors for data.

A high-level diagram and documentation can be found here: [High-Level Architecture](https://app.nuclino.com/Canacompost-Systems/Canacompost/High-Level-Architecture-2d4dbe05-6e8d-4563-9f24-c729c32722a6).

## Acronyms
IC = Integrated Computer

MCU = MicroController Unit

# How to Build

TODO

# How to Test

TODO

# Design

1. [High-Level Architecture](https://app.nuclino.com/Canacompost-Systems/Canacompost/High-Level-Architecture-2d4dbe05-6e8d-4563-9f24-c729c32722a6)
2. [Leo's Original Implementation](https://github.com/leomorpho/compost-manager-embedded/blob/221d68fc25802f619a93a790fc751dfb9ebc9471/src/main.cpp)

# Protocol

## Transport Layer
The protocol on top of serial will adhere to the format, where one set of brackets is 1-byte:

From IC to MCU:

`[Number of Bytes][Command][Payload 1 of N] ... [Payload N of N]`

Then from MCU back to IC:

`[CRC-8/32][CRC-16/32][CRC-24/32][CRC-32/32]`

This is an unsigned CRC-32: https://stackoverflow.com/a/30092291

The IC will do the same CRC-32 calculation and if they match return one-byte `0xFF` to acknowledge receipt. Otherwise it will return `0x00` for retry, but anything other than the acknowledgement byte will trigger a resend.

## Application Layer

On top of this transport layer, we'll need to do a few things:
1. Configure polling frequency of the sensors
2. Configure the actuator state
3. Ask for updates on the sensors (pull style updates from the perspective of the IC)

### Example Configuration

For the below examples we assume the MCU is connected to:
* Bioreactor-1
    * Connected to Shared-Air & Heater-1
* Bioreactor-2
    * Connected to Shared-Air & Heater-2

Both Bioreactors are connected to the shared air infrastructure, which is then connected to:
* Radiator
* Dehumidifier
* Sensors
* Spectrometer

So then the IC needs to sample the air on Bioreactor-1: The IC will ask the MCU to close the actuators for Bioreactor-2 and open the actuators for Bioreactor-1. The IC will know ahead of time which these actuators are.

If climate control is to be done, the same process as above must be completed.

**⚠️ Risk for Climate Control and Sampling**: Given only one bioreactor can be hooked up at a time, sampling and climate control will compete for time. With 9 Bioreactors each Bioreactor has 1/9th the time to be hooked up to the shared air and have it's climate controlled.

### Configure Polling Frequency

We'll use 'P' to configure polling frequency.

`[4]['P'][SENSOR-NUM][INTERVAL-SECONDS]`

### Configure Actuator State

`[4]['A'][ACTUATOR-NUM][STATE]`

### Ask for Sensor Updates
`[2]['p']`

### Ask for Actuator State

`[2]['a']`

### Ask for All State

`[2]['S']`

### Response Format

Let's say the IC asks the MCU for "All State";

IC to MCU:

`[2]['S']`

MCU to IC:

The above turns into the hex value 0x0253, which will then give the following CRC back:
`[0x81][0x8D][0x70][0x33]`

IC to MCU:

`[0xFF]` indicating CRC32's match, acknowledging the receipt.

Then the MCU will respond to the request:

From MCU to IC:

`[19]['a'][1][0x0]['a][2][0x0]['a'][3][0x1]['a'][4][0x1]['o'][1][0x23]['m'][1][0xf1]`

Breaking this down, first we have the number of bytes.

Then we have `['a']` which denotes the type is actuator, followed by `[1]` which denotes the actuator number, and then finally you have `[0x0]` which is the actuator state.

The next payload we have the next actuator. Both of these actuators (1 & 2) could represent Bioreactor-1 being cut off from the shared air infrastructure.

Then the following two payloads are for actuators perhaps around Bioreactor-2 and they're both "on" or open representing Bioreactor-2 being connected to the shared air infrastructure. Actuators 3 & 4.

Then we have `['o'][1][0x23]` which is the oxygen sensor 1 which has a state of 0x23 = 25.

Finally we have `['m'][1][0xf1]` which is the methane sensor 1 which has a state of 0xf1 = 241.

Finally the IC responds to the MCU with a CRC-32.

`[Bytes 8/32][Bytes 16/32][Bytes 24/32][Bytes 32/32]`

And then the MCU replies to the IC:

`[0xFF]` indicating CRC32's match, acknowledging the receipt.
