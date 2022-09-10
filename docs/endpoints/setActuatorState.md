# SET Actuator State

Set state of a specific Actuator (HIGH or LOW).

| Parameter | Value | # Bytes |
|-----------|-------|-------|
| OPCODE | `0xA1` | 1 |
| DID | Device ID of sensor to get | 1 |
| PAYLOAD | either `0x00000000` for `LOW` or `0x11111111` for `HIGH` | 4 |

## Example Request

```
<STX><OPCODE><DID><PAYLOAD><ETX>
```

```
[0x01][0xB0][0xE0][0x00000000][0x03]
```

Python Example:

```
serial_speed = 9600
serial_port = '/dev/tty.**'
ser = serial.Serial(serial_port, serial_speed)
ser.write(b'\x01\xB0\xE0\x00\x00\x00\x00\x03')
```

## Example Response

```
<STX><STATUS><ETX>
```

Where status is one of the following control bytes: `ACK` if set was successful, `NAK` if set failed.

```
[0x01][0x06][0x03]
```

* From the response above we can see that the actuator was set successfully.