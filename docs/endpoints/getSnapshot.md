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
[0x01][0xc0][0x41dc044c][0x4257315b][0x00000000][0xc1][0x443b4000][0x41e95110][0x42490040][0x03] 
```

* In this example two devices are connected to the MCU.
* The first device with `did = [0xc0]` is SHT40, so D0 and D1 are temperature and humidity. `[0x41dc044c]` converted to float is `27.5021` which is the temperature value. `[0x4257315b]` converted to float is `53.7982` which is the humidity value. 
* The second device with `did = [0xc1]` is SCD41, so D0, D1, and D2, are CO2, temperature, and humidity.
* Note that the data values (D0, D1, D2) are encoded using "Big-Endian".