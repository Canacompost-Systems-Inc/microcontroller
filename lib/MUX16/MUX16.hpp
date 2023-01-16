#ifndef MUX16_H
#define MUX16_H

#include <Arduino.h>

// Tested with cd74HC4067 16-channel analog MUX using the SDA line as the signal line
class MUX16 {
 private:
  // States of the selector pins for each channel, indexed by selected channel number
  static const int LUT[16][4];

  int enablePin; // assumed active low
  int selectorPin[4]; // [S3, S2, S1, S0]

 public:
  MUX16(int inEnablePin, int inS3Pin, int inS2Pin, int inS1Pin, int inS0Pin):
    enablePin(inEnablePin), selectorPin{inS3Pin, inS2Pin, inS1Pin, inS0Pin}  {};

  void begin();

  /**
   * Selects the channel to be read from the MUX16
   * 
   * @param channel int between 0 and 15 representing the respective channel
   */
  void select(int channel);

  /**
   * Enables signal output from the MUX16, assumes active low
   */
  void enable();

  /**
   * Disables signal output from the MUX16
   */
  void disable();
};

#endif