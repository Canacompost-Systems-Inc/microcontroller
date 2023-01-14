import serial

HEX_BUFF_TEMPLATE = bytearray([1, 0, 0, 0, 0, 0, 0, 3])
GET_SNAPSHOT_OPCODE = 160
GET_SENSOR_OPCODE = 161
GET_ACTUATOR_OPCODE = 162
SET_ACTUATOR_OPCODE = 176

# Add serial ports connected to MCU here
serial_ports = [
  # macos/linux
  '/dev/tty.usbmodem14101',
  '/dev/ttyACM0',
  # Windows
  'COM3'
  ]

port_index = 0
serial_speed = 9600

while True:
  if port_index >= len(serial_ports):
    print('ERR: Could not connect to MCU, please check the configured serial ports')
    exit()

  try:
    ser = serial.Serial(serial_ports[port_index], serial_speed, timeout=None)
    print('Connected to ' + serial_ports[port_index])
    break
  except(serial.SerialException):
    port_index += 1

def loop() -> bool:
  try: 
    query = input('>> ').lower()
    segmented_query = argsParser(query)

    command = segmented_query[0]
    if command == 'q':
      return False

    device_id = segmented_query[1]

    if len(segmented_query) == 3:
      arg = segmented_query[2]

    if command == 'get':
      runGet(device_id)
    elif command == 'set':
      runSet(device_id, arg)
    else: 
      print('ERR: invalid command')

  except Exception as e:
    print('ERR: ' + str(e))

  return True

def argsParser(q):
  seg_buff = [''] * 3
  temp_seg = q.split(' ')

  for i, seg in enumerate(temp_seg):
    seg_buff[i] = seg

  return seg_buff

def runGet(s_did: str):
  buff = HEX_BUFF_TEMPLATE
  
  if s_did == 'all':
    buff[1] = GET_SNAPSHOT_OPCODE
  else:
    did = int(s_did, 16)

    if did >= 192 and did <= 223:
      buff[1] = GET_SENSOR_OPCODE
    elif did >= 224 and did <= 255:
      buff[1] = GET_ACTUATOR_OPCODE
    else:
      print("ERR: device id is invalid")
      return

    buff[2] = did

  communicate(buff)

def runSet(s_did, s_arg):
  buff = HEX_BUFF_TEMPLATE
  buff[1] = SET_ACTUATOR_OPCODE
  buff[2] = int(s_did, 16)

  # Convert arg into 4 bytes
  i = 3
  arg = int(s_arg)
  for byte in arg.to_bytes(4, 'big'):
    buff[i] = byte
    i += 1

  communicate(buff)

def communicate(bytes: bytearray):
  data = ''
  state = 0
  ser.write(bytes)

  while True:
    byte = ser.read()
    # Uncomment to see all returned bytes
    # print(byte)

    if state == 0:
      if byte == b'\x01':
          state = 1

    if state == 1:
      data = data + byte.hex() + ' '
      if byte == b'\x03' and ser.in_waiting == 0:
        print(data)
        break

if __name__ == '__main__' :
  while True:
    if not loop():
      break