# GET System Snapshot

Get the state of all sensors and actuators connected to the MCU.

| Parameter | Value | # Bytes |
|-----------|-------|-------|
| OPCODE | `0xA0` | 1 |
| DID | `DC` | 1 |
| PAYLOAD | `DC` | 4 |

## Example Request

```
<STX><OPCODE><DID><PAYLOAD><ETX>
```

```
[0x01][0xA0][0x00][0x00000000][0x03]
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
<STX><DID_0><D0><D1><D2>...<DID_n><D0><D1><D2><ETX>
```

```
[0x01][0x00][0x41d18c90][0x425813ec][0x00000000][0x01][0x446f8000][0x41e8bd68][0x423e9e70][0x03]
```

* In this example two devices are connected to the MCU.
* The first device with `did = [0x00]` is SHT40, so D0 and D1 are temperature and humidity. `[0x41d18c90]` converted to float is `26.1936` which is the temperature value. `[0x425813ec]` converted to float is `54.0195` which is the humidity value. 
* The second device with `did = [0x01]` is SCD41, so D0, D1, and D2, are CO2, temperature, and humidity.
