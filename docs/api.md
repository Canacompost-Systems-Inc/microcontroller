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

| DID | Type | D0 | D1 | D2 |
|------|-----|----|----|----|
| `0xC0` | SHT40 | Temperature (C) | Humidity (%) | - |
| `0xC1` | SCD41 | CO2 (ppm) | Temperature (C) | Humidity (%) |
| `0xC2` | IPC10100 | Temperature (C) | Pressure (Pa) | - |
| `0xC3` | DS18B20 | Temperature (C) | - | - |
| `0xC4` | DS18B20 | Temperature (C) | - | - |
| `0xC5` | DS18B20 | Temperature (C) | - | - |
| `0xC6` | DS18B20 | Temperature (C) | - | - |
| `0xC7` | YFS201 | Flow Rate (L/min) | - | - |
| `0xC8` | SEN0441 | H2 (ppm) | - | - |
| `0xC9` | SEN0321 | Ozone (ppm) | - | - |

## Actuators

Actuators DID's range from `0xE0` to `0xFF`. Each actuator begins in their 0th state, and can be actuated into any of their defined states via the [SET Actuator State endpoint](endpoints/setActuatorState.md).

| DID | Type | Number of States | Domain [0, ..., n] | 
|------|-----|------------------|--------------------|
| `0xE0` | Rotary Valve | 7 | 0, 1, 2, 3 ,4 ,5, 6 |
| `0xE1` | Rotary Valve | 7 | 0, 1, 2, 3 ,4 ,5, 6 |
| `0xE2` | Rotary Valve | 7 | 0, 1, 2, 3 ,4 ,5, 6 |
| `0xE3` | Flap Diverter Valve | 20 | 0&deg;, 10&deg;, 20&deg;, ..., 90&deg; |
| `0xE4` | Flap Diverter Valve | 20 | 0&deg;, 10&deg;, 20&deg;, ..., 90&deg; |
| `0xE5` | Flap Diverter Valve | 20 | 0&deg;, 10&deg;, 20&deg;, ..., 90&deg; |
| `0xE6` | Flap Diverter Valve | 20 | 0&deg;, 10&deg;, 20&deg;, ..., 90&deg; |
| `0xE7` | Flap Diverter Valve | 2 | 0&deg;, 100&deg; |
| `0xE8` | Flap Diverter Valve | 2 | 0&deg;, 100&deg; |
| `0xE9` | Relay | 2 | OFF, ON |
| `0xEA` | Flap Diverter Valve | 2 | 0&deg;, 100&deg; |
| `0xEB` | Flap Diverter Valve | 20 | 0&deg;, 5&deg;, 10&deg;, ..., 100&deg; |
| `0xEC` | Flap Diverter Valve | 20 | 0&deg;, 5&deg;, 10&deg;, ..., 100&deg; |
| `0xED` | Relay | 2 | OFF, ON |
| `0xEE` | Relay | 2 | OFF, ON |
| `0xEF` | Relay | 2 | OFF, ON |
| `0xF0` | Relay | 2 | OFF, ON |
| `0xF1` | Relay | 2 | OFF, ON |
| `0xF2` | Relay | 2 | OFF, ON |
| `0xF3` | Relay | 2 | OFF, ON |
| `0xF4` | Flap Diverter Valve | 20 | 0&deg;, 5&deg;, 10&deg;, ..., 100&deg; |
| `0xF5` | Relay | 2 | OFF, ON |
| `0xF6` | Relay | 2 | OFF, ON |
| `0xF7` | Relay | 2 | OFF, ON |
| `0xF8` | Relay | 2 | OFF, ON |
| `0xF9` | Relay | 2 | OFF, ON |
| `0xFA` | Relay | 2 | OFF, ON |
| `0xFB` | Relay | 2 | OFF, ON |

- Relays turn off/on (LOW/HIGH) the device connected to it.
- Flap Diverter Valves actuate the position of the internal flap to predefined degree. 
- Rotary Valves can be rotated to 1 out of the 6 positions. Note that `state=0` for rotary valves represents a fixed starting position and not a "valid"  position. Setting `state=0` essentially resets the valve.

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
