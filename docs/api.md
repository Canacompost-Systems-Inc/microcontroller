# MCU API

## Endpoints

|  | OPCODE |
|--|--------|
| [GET System Snapshot](docs/api.md) | `0xA0` |
| [GET Sensor State]() | `0xA1` |
| [GET Actuator State]() | `0xA2` |
| [SET Sensor Polling Frequency]() | `0xC0` |
| [SET Actuator State]() | `0xC1` |

## Devices

| Name | DID | Type |
|------|-----|------|


## Standerdization

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
