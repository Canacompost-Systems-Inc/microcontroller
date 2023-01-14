#include "ControlUnit.hpp"

// Initialize singleton instance
ControlUnit *ControlUnit::instance = nullptr;

ControlUnit::ControlUnit(Array<Actuator*> configuredActuators, Array<Sensor*> configuredSensors) {
  actuators = configuredActuators;
  sensors = configuredSensors;
  state = IDLE;
  buffer[MAX_BUFFER_SIZE] = { NULL };
  bufferCount = 0;
}

ControlUnit::~ControlUnit() {
  delete ControlUnit::instance;
}

void ControlUnit::loop() {
  transceiverLoop();
  pollSensorsLoop();
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
  int arrayPosition = calculateSensorIndexFromDID(did);

  if (arrayPosition >= 0 && arrayPosition < sensors.getSize()) {
    sensors.read(arrayPosition)->report();
  } else {
    Serial.write(NAK);
  }
}

void ControlUnit::executeGetActuator() {
  byte did = buffer[1];
  int arrayPosition = calculateActuatorIndexFromDID(did);

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

  int arrayPosition = calculateActuatorIndexFromDID(did);
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

  // Do random print TODO:remove
  randomSeed(analogRead(0));
  if (random(100) > 50) {
    Serial.print("Hello");
  }

  state = IDLE;
}

int ControlUnit::calculateSensorIndexFromDID(byte searchDid) {
  for (int i = 0; i < sensors.getSize(); i++) {
    if (sensors.read(i)->getDid() == searchDid) {
      return i;
    }
  }

  // DID was not found
  return -1;
}

int ControlUnit::calculateActuatorIndexFromDID(byte searchDid) {
  for (int i = 0; i < actuators.getSize(); i++) {
    if (actuators.read(i)->getDid() == searchDid) {
      return i;
    }
  }

  // DID was not found
  return -1;
}