# GET System Snapshot

Get the state of all sensors and actuators connected to the MCU.

| Parameter | Value | # Bytes |
|-----------|-------|-------|
| OPCODE | `0xA0` | 1 |
| DID | `DC` | 1 |
| PAYLOAD | `DC` | 4 |

## Example Request

```
[01][A0][00][00][00][00][00][03]
```

Python Example:

```
serial_speed = 9600
serial_port = '/dev/tty.**'
ser = serial.Serial(serial_port, serial_speed)
ser.write(b'\x01\xA0\x00\x00\x00\x00\x00\x03')
```

## Example Response


```
[Sensor_i] = [DID][D0][D1][D2]
```
