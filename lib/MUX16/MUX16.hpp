#include <Arduino.h>


class MUX16 {
 private:
  static constexpr const int LUT[16][4] = {
    {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1},
    {0, 1, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1},
    {1, 0, 0, 0}, {1, 0, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 1},
    {1, 1, 0, 0}, {1, 1, 0, 1}, {1, 1, 1, 0}, {1, 1, 1, 1}
  };

  int sigPin;
  int enablePin;
  int selectorPin[4];

 public:
  MUX16(int inSigPin, int inEnablePin, int inS3Pin, int inS2Pin, int inS1Pin, int inS0Pin):
  sigPin(inSigPin), enablePin(inEnablePin), selectorPin({inS3Pin, inS2Pin, inS1Pin, inS0Pin})  {};

  void begin();
  void select(int channel);
  void enable();
  void disable();
};