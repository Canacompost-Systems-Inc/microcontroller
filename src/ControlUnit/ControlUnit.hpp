#include <Arduino.h>
#include "Array.hpp"
#include "Sensor.hpp"
#include "Actuator.hpp"

class ControlUnit {
 public:
  /**
   * @post State set to IDLE, buffer initialized to NULL and bufferCount to 0
   */
  ControlUnit(Array<Actuator*> configuredActuators, Array<Sensor*> configuredSensors);

  /**
   * Frees heap memory used for singleton instance
   */
  ~ControlUnit();

  /**
   * Singletons cannot be cloned.
   */
  ControlUnit(ControlUnit const &) = delete;

  /**
   * Singleton cannot be assigned
   */
  void operator=(ControlUnit const &) = delete;

  /**
   * sets array of actuators and sensors to values passed into constructor
   * 
   * @param configuredActuators array of Actuator objects
   * @param configuredSensors array of Sensor objects
   */ 
  inline static void begin(Array<Actuator*> configuredActuators, Array<Sensor*> configuredSensors) {
    ControlUnit::instance = new ControlUnit(configuredActuators, configuredSensors);
  };

  /**
   * Returns the current singleton instance 
   */
  inline static ControlUnit *get() {
    return instance;
  }

  /**
   * Main loop of control unit, called ever clock cycle. Polls sensors and handles transmissions
   */
  void loop();

 private:
  // Sizing Constants
  static const int MAX_PAYLOAD_SIZE = 4;
  static const int MAX_BUFFER_SIZE = 6;

  // Control Characters
  static const byte STX = 0x01;
  static const byte ETX = 0x03;
  static const byte ACK = 0x06;
  static const byte NAK = 0x15;

  // Opcodes
  static const byte GET_SNAPSHOT_OPCODE = 0xA0;
  static const byte GET_SENSOR_OPCODE = 0xA1;
  static const byte GET_ACTUATOR_OPCODE = 0xA2;
  static const byte SET_ACTUATOR_OPCODE = 0xB0;

  // Singleton instance
  static ControlUnit *instance;

  // States for Control unit transceiver
  enum State { IDLE, FETCH, EXECUTE };

  // ----- Loops ----- //
  /**
   * Invokes Sensor::loop() for each sensor in sensors array
   */
  void pollSensorsLoop();

  /**
   * Maps current state of transceiver to corresponding state handler
   */
  void transceiverLoop();

  // ----- Executors ----- //
  /**
   * Invokes self reporting from sensors and actuators in order (elements 0 to n).
   * @post Current sensors and actuators states will be written to Serial port
   */
  void executeGetSnapshot();

  /**
   * Invokes self reporting for sensor with specified DID
   * @post Sensor matching provided DID will report its state, NAK returned if provided DID is out 
   *   of range
   */
  void executeGetSensor();

  /**
   * Invokes self reporting actuator with specified DID
   * @post Actuator matching provided DID will report its state, NAK returned if provided DID is out 
   *   of range
   */
  void executeGetActuator();

  /**
   * Updates actuator state with specified DID
   * @post Actuator matching provided DID will be set to the defined new value (either HIGH or LOW). 
   *   NAK returned if provided DID is out of range OR if the actuator setState() function returns 
   *   false indicating failure.
   */
  void executeSetActuator();

  // ----- FSM State Handlers ----- //
  /**
   * Reads incoming bytes (if serial is available), moves to FETCH state if read byte == STX
   */
  void idleHandler();

  /**
   * Reads incoming transmission bytes into a buffer. Once a total of MAX_BUFFER_SIZE bytes 
   * (not including STX and ETX characters) is read, moves to EXECUTE state. Moves to IDLE if request 
   * is incorrectly formatted. 
   */
  void fetchHandler();

  /**
   * Invokes appropriate executor based on received opcode. Moves to IDLE after executor has
   * returned regardless if request executed successfully.
   */
  void executeHandler();

  // ----- Helpers ----- //
  /**
   * @param inDID Sensor Device ID byte to convert to element position
   * @return element position of sensor with given did. If inDID is not within sensor or
   *   actuator byte range then returns -1 indicating an error.
   */
  int calculateSensorIndexFromDID(byte inDID);

  /**
   * @param inDID Actuator Device ID byte to convert to element position
   * @return element position of actuator with given did. If inDID is not within sensor or
   *   actuator byte range then returns -1 indicating an error.
   */
  int calculateActuatorIndexFromDID(byte inDID);

  State state; // Current state of transceiver
  
  // Arrays of connected devices
  Array<Actuator*> actuators;
  Array<Sensor*> sensors;

  // Transceiver buffer of incoming bytes for current request
  byte buffer[MAX_BUFFER_SIZE];
  int bufferCount;
};