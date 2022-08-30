# MCU API

## Endpoints

|  | OPCODE |
|--|--------|
| [GET System Snapshot](endpoints/getSnapshot.md) | `0xA0` |
| [GET Sensor State]() | `0xA1` |
| [GET Actuator State]() | `0xA2` |
| [SET Sensor Polling Frequency]() | `0xC0` |
| [SET Actuator State]() | `0xC1` |

## Sensors

| Name | DID | D0 | D1 | D2 |
|------|-----|----|----|----|
| SHT40 | `0x00` | Temperature (C) | Humidity (%) | - |
| SCD41 | `0x01` | CO2 (ppm) | Temperature (C) | Humidity (%) |
| IPC10100 | `0x02` | Temperature (C) | Pressure (Pa) | - |
| DS18B20 | `0x03` | Temperature (C) | - | - |

## Actuators
| Name | DID | D0 | D1 | D2 |
|------|-----|----|----|----|

## Standardization

### Request

```
<STX><OPCODE><DID><PAYLOAD><ETX>
```

### GET Response

```
<STX><DID><PAYLOAD><ETX>
```

### SET Response

```
<STX><ACK><ETX>
```

### Error Response

```
<STX><NAK><ETX>
```
