import serial

HEX_BUFF_TEMPLATE = bytearray([1, 0, 0, 0, 0, 0, 0, 3])
GET_SNAPSHOT_OPCODE = 160
GET_SENSOR_OPCODE = 161
GET_ACTUATOR_OPCODE = 162
SET_ACTUATOR_OPCODE = 176

serial_speed = 9600
serial_port = '/dev/tty.usbmodem14101'
ser = serial.Serial(serial_port, serial_speed, timeout=None)

def argsParser(q):
  seg_buff = [''] * 3
  temp_seg = q.split(' ')

  for i, seg in enumerate(temp_seg):
    seg_buff[i] = seg

  return seg_buff

def communicate(bytes: bytearray):
  data = ''
  state = 0
  ser.write(bytes)

  while True:
    byte = ser.read()
    # print(byte)

    if state == 0:
      if byte == b'\x01':
          state = 1

    if state == 1:
      data = data + byte.hex() + ' '
      if byte == b'\x03':
        print(data)
        break

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


if __name__ == '__main__' :
  while True:
    if not loop():
      break