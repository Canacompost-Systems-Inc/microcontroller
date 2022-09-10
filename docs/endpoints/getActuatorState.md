# GET Actuator State

Get the current state of a specific actuator.

| Parameter | Value | # Bytes |
|-----------|-------|-------|
| OPCODE | `0xA2` | 1 |
| DID | Device ID of actuator to get | 1 |
| PAYLOAD | `DC` | 4 |

## Example Request

```
<STX><OPCODE><DID><PAYLOAD><ETX>
```

```
[0x01][0xA2][0xE0][0x00000000][0x03]
```

Python Example:

```
serial_speed = 9600
serial_port = '/dev/tty.**'
ser = serial.Serial(serial_port, serial_speed)
ser.write(b'\x01\xA2\xE0\x00\x00\x00\x00\x03')
```

## Example Response

```
<STX><DID><D0><ETX>
```

Where D0 is the actuator state (either `HIGH = [0xffffffff]` or `LOW = [0x00000000]`) represented by a 4 byte hex string.

```
[0x01][0xe0][0xffffffff][0x03]
```

* From the above response we can see that the device with `did = [0xe0]` is currently in the `HIGH` state.
