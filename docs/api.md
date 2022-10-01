# API Docs

## Endpoints

The table below shows all the available API endpoints.

|  | OPCODE |
|--|--------|
| [GET System Snapshot](endpoints/getSnapshot.md) | `0xA0` |
| [GET Sensor State](endpoints/getSensorState.md) | `0xA1` |
| [GET Actuator State](endpoints/getActuatorState.md) | `0xA2` |
| [SET Actuator State](endpoints/setActuatorState.md) | `0xB0` |

## Sensors

Each sensor can hold up to three data values (D0, D1, D2). All data values are polled at a configured polling frequency. Sensor DID's range from `0xC0` to `0xDF`.

| Name | DID | D0 | D1 | D2 |
|------|-----|----|----|----|
| SHT40 | `0xC0` | Temperature (C) | Humidity (%) | - |
| SCD41 | `0xC1` | CO2 (ppm) | Temperature (C) | Humidity (%) |
| IPC10100 | `0xC2` | Temperature (C) | Pressure (Pa) | - |
| DS18B20 | `0xC3` | Temperature (C) | - | - |

## Actuators

Actuators DID's range from `0xE0` to `0xFF`. Each actuator begins in their 0th state, and can be actuated into any of their defined states via the [SET Actuator State endpoint](endpoints/setActuatorState.md).

| Name | DID | Number of States | Domain [0, ..., n] | 
|------|-----|------------------|--------------------|
| Relay0 | `0xE0` | 2 | `[LOW, HIGH]` |
| Relay1 | `0xE1` | 2 | `[LOW, HIGH]` |
| Relay2 | `0xE2` | 2 | `[LOW, HIGH]` |
| Relay3 | `0xE3` | 2 | `[LOW, HIGH]` |
| Relay4 | `0xE4` | 2 | `[LOW, HIGH]` |
| Relay5 | `0xE5` | 2 | `[LOW, HIGH]` |
| Relay6 | `0xE6` | 2 | `[LOW, HIGH]` |
| FlapDiverterValve0 | `0xE7` | 3 | `[LEFT, MIDDLE, RIGHT]` |

- Relays turn off/on (LOW/HIGH) the device connected to it.
- FlapDiverterValves actuate the position of the interal flap to predefined positions. 

## Standardization

### Control Characters

The below control characters used during transmission. Note that these follow the [standard control characters](https://www.geeksforgeeks.org/control-characters/) with some minor modifications.

| Name | Hex Code | Abbreviation | Description |
|------|----------|--------------|-------------|
| Start of Transmission | `0x01` | `STX` | Used to mark start of transmission |
| End of Transmission | `0x03` | `ETX` | Used to mark end of transmission |
| Acknowledge | `0x06` | `ACK` | Indicates request was completed successfully |
| Negative Acknowledge | `0x15` | `NAK` | Indicates that an error was identified in last received request |

### Request

Every request must follow the format below.

```
<STX><OPCODE><DID><PAYLOAD><ETX>
```

Where: 
* `STX` and `ETX` are 1 byte control characters representing the start and end of transmission.
* `OPCODE` is a 1 byte code that controls which operation to preform.
* `DID` is the 1 byte device ID in which to preform the operation to.
* `PAYLOAD` is 4 bytes representing some data (ex: float).

Note that all parameters must be filled in, even if it is not used by an endpoint. This ensures that each request has the same number of total bytes. For example, a particular endpoint may not use `PAYLOAD` parameter. In this case the request sent must still fill these bytes with some value; we call these bytes "Don't Cares" `DC` since they do not effect the program flow.

### GET Response

All successful get request will have the response format, or variation of it, below.

```
<STX><DID><PAYLOAD><ETX>
```

### SET Response

All successful set requests will have the response format below, where `ACK` is the control byte meaning "Acknowledge" or "Success"

```
<STX><ACK><ETX>
```

### Error Response

All failed requests will have the response format below, where `NAK` is the control byte meaning "Negative Acknowledge" or "Failure".

```
<STX><NAK><ETX>
```
