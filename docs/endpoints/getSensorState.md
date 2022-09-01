# GET Sensor State

Get the data values (state) of a specific sensor.

| Parameter | Value | # Bytes |
|-----------|-------|-------|
| OPCODE | `0xA0` | 1 |
| DID | Device ID of sensor to get | 1 |
| PAYLOAD | `DC` | 4 |

## Example Request

```
<STX><OPCODE><DID><PAYLOAD><ETX>
```

```
[0x01][0xA1][0xC0][0x00000000][0x03]
```

Python Example:

```
serial_speed = 9600
serial_port = '/dev/tty.**'
ser = serial.Serial(serial_port, serial_speed)
ser.write(b'\x01\xA1\xC0\x00\x00\x00\x00\x03')
```

## Example Response

```
<STX><DID><D0><D1><D2><ETX>
```

Where D0, D1, and D2 are the sensors three data values (floats) represented by a little-endian encoded 4 byte hex string.

```
[0x01][0xc0][0x41cb4fac][0x4271acc2][0x00000000][0x03]
```

* The requested device is SHT40 with `did = [0xc0]`
* D0 and D1 are temperature and humidity. `[0x41cb4fac]` converted to float is `25.4139` which is the temperature value. `[0x4271acc2]` converted to float is `60.4187` which is the humidity value.
* D2 is empty as expected.
