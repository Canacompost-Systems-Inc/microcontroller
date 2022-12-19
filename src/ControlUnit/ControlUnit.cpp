#include "ControlUnit.hpp"


// Initialize singleton instance
ControlUnit *ControlUnit::instance = nullptr;

int ControlUnit::calculateArrayPositionFromDID(byte inDID) {
  static int sensorIndexOffset = 192;
  static int actuatorIndexOffset = 224;
  static int deviceListSize = 32;
  int i_inDID = (int) inDID;

  if (i_inDID >= sensorIndexOffset && i_inDID < sensorIndexOffset + deviceListSize) {
    // Sensor DID's range from 0xC0 to 0xDF, which is the ints 192 (sensor @ el 0) to 223 (sensor @ el 31)
    return (i_inDID - sensorIndexOffset);
  } else if (i_inDID >= actuatorIndexOffset && i_inDID < actuatorIndexOffset + deviceListSize) {
    // Actuator DID's range from 0xE0 to 0xFF, which is the ints 224 (actuator @ el 0) 
    // to 255 (actuator @ el 31)
    return (i_inDID - actuatorIndexOffset);
  } else {
    return -1;
  }
}

void ControlUnit::executeGetSnapshot() {
  for (int i = 0; i < sensors.getSize(); i++) {
    sensors.read(i)->report();
  }
  for (int j = 0; j < actuators.getSize(); j++) {
    actuators.read(j)->report();
  }
}

void ControlUnit::executeGetSensor() {
  byte did = buffer[1];
  int arrayPosition = calculateArrayPositionFromDID(did);

  if (arrayPosition >= 0 && arrayPosition < sensors.getSize()) {
    sensors.read(arrayPosition)->report();
  } else {
    Serial.write(NAK);
  }
}

void ControlUnit::executeGetActuator() {
  byte did = buffer[1];
  int arrayPosition = calculateArrayPositionFromDID(did);

  if (arrayPosition >= 0 && arrayPosition < actuators.getSize()) {
    actuators.read(arrayPosition)->report();
  } else {
    Serial.write(NAK);
  }
}

void ControlUnit::executeSetActuator() {
  byte did = buffer[1];
  int newState = int((unsigned char)(buffer[2]) << 24 |
    (unsigned char)(buffer[3]) << 16 |
    (unsigned char)(buffer[4]) << 8 |
    (unsigned char)(buffer[5]));

  int arrayPosition = calculateArrayPositionFromDID(did);
  bool positionInRange = (arrayPosition >= 0 && arrayPosition < actuators.getSize());

  if (positionInRange) {
    if (actuators.read(arrayPosition)->setState(newState) == true) {
      Serial.write(ACK);
    } else {
      Serial.write(NAK);
    }
  } else {
    Serial.write(NAK);
  }
}

void ControlUnit::idleHandler() {
  if (Serial.available()) {
    byte inByte = Serial.read();

    if (inByte == STX) {
      state = FETCH;
    }
  }
}

void ControlUnit::fetchHandler() {
  if (Serial.available()) {
    byte inByte = Serial.read();

    if (bufferCount == MAX_BUFFER_SIZE) {
      bufferCount = 0;

      if (inByte == ETX) {
        state = EXECUTE;
      } else {
        Serial.write(STX);
        Serial.write(NAK);
        Serial.write(ETX);
        state = IDLE;
      }
    } else {
      buffer[bufferCount] = inByte;
      bufferCount++;
    }
  }
}

void ControlUnit::executeHandler(){ 
  byte opcode = buffer[0];

  Serial.write(STX);
  switch (opcode) {
    case GET_SNAPSHOT_OPCODE:
      executeGetSnapshot();
      break;
    case GET_SENSOR_OPCODE:
      executeGetSensor();
      break;
    case GET_ACTUATOR_OPCODE:
      executeGetActuator();
      break;
    case SET_ACTUATOR_OPCODE:
      executeSetActuator();
      break;
    default:
      Serial.write(NAK);
      break;
  }
  Serial.write(ETX);

  state = IDLE;
}

void ControlUnit::pollSensorsLoop() {
  unsigned long currentTimeMs = millis();
  for (int i = 0; i < sensors.getSize(); i++) {
    sensors.read(i)->loop(currentTimeMs);
  }
}

void ControlUnit::transceiverLoop() {
  switch (state) {
    case IDLE:
      idleHandler();
      break;
    
    case FETCH:
      fetchHandler();
      break;

    case EXECUTE:
      executeHandler();
      break;
      
    default:
      break;
  }
}

ControlUnit::ControlUnit(Array<Actuator*> configuredActuators, Array<Sensor*> configuredSensors) {
  actuators = configuredActuators;
  sensors = configuredSensors;
  state = IDLE;
  buffer[MAX_BUFFER_SIZE] = { NULL };
  bufferCount = 0;
}

void ControlUnit::loop() {
  transceiverLoop();
  pollSensorsLoop();
}