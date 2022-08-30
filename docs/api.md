# MCU API

## Endpoints

|  | OPCODE |
|--|--------|
| [GET System Snapshot](endpoints/getSnapshot.md) | `0xA0` |
| [GET Sensor State](endpoints/getSensorState.md) | `0xA1` |
| GET Actuator State (WIP) | `0xA2` |
| SET Sensor Polling Frequency (WIP) | `0xC0` |
| SET Actuator State (WIP) | `0xC1` |

## Sensors

Each sensor can hold up to three data values (D0, D1, D2). All data values are polled at a configured polling frequency.

| Name | DID | D0 | D1 | D2 |
|------|-----|----|----|----|
| SHT40 | `0x00` | Temperature (C) | Humidity (%) | - |
| SCD41 | `0x01` | CO2 (ppm) | Temperature (C) | Humidity (%) |
| IPC10100 | `0x02` | Temperature (C) | Pressure (Pa) | - |
| DS18B20 | `0x03` | Temperature (C) | - | - |

## Actuators

WIP

## Standardization

* `STX` and `ETX` are 1 byte control characters representing the start and end of transmission.
* `OPCODE` is a 1 byte code that controls which operation to preform.
* `DID` is the 1 byte device ID in which to preform the operation to.
* `PAYLOAD` is the data passed by transmitter (variable size with minimum of 4 bytes).

### Request

Every request must follow the format below. Note that the payload is expected to be 4 bytes. If a value is not used by the operation its bytes must still be filled in the request. For example a particular endpoint may not use payload value. However the request sent must fill these bytes with any value; we call these bytes "Don't Cares" (DC).

```
<STX><OPCODE><DID><PAYLOAD><ETX>
```

### GET Response

All successful get request will have the response format below.

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
