#ifndef CONFIG_H
#define CONFIG_H

#include "Array.hpp"
#include "Sensor.hpp"

// Settings used for operation. Note you may need to clean and do a fresh rebuild if updating these constant
// values (PlatformIO seams to not rebuild the changes automatically).
namespace config {

const unsigned long DEFAULT_POLLING_INTERVAL = 5000;

/** ----- ACTUATOR STATES -----
 * Each actuator is given one of these arrays. The array represents all the possible states with the index
 * being the state id (ie: index 0 = state 0), and the value being the desired state to actuate to (with each 
 * actuator having its own domain).
 */

// Rotation in degrees of the flap arm, diverts between two output valves. Note that the total rotation angle 
// (180 degrees) is much larger than the flap can physically do. This is due to these valves having different 
// starting positions (0 degrees). By having a large window we ensure that the flap is all the way to one side
// for all valves. The flaps have a mechanical stop when closed to one size. It is assumed that the torque 
// applied is constant no matter how far past the mechanical stop we actuate too, therefore this large window
// will not negatively effect the device.
static const Array<int> FD_TWO_STATES_E7({18, 78});
static const Array<int> FD_TWO_STATES_E8({5, 70});

// Rotation in degrees of the flap arm, controls how much air passes through by diverting to an...
// TODO: dynamically calculate these so we dont need to hardcode it have a step size and two edge values (lambda func)
// Right now we use the script test/flap_diverter_degree_calculator.py to calculate these values
static const Array<int> FD_TWENTY_STATES_EB({5, 8, 12, 15, 19, 22, 26, 29, 32, 36, 39, 43, 46, 49, 53, 56, 60, 63, 67, 70});
static const Array<int> FD_TWENTY_STATES_EC({60, 63, 67, 70, 74, 77, 81, 84, 87, 91, 94, 98, 101, 104, 108, 111, 115, 118, 122, 125});

// Each element represents number of steps from the zero position (the consistant point at which the limit 
// switch is opened) to get valve into desired position for the desired state. Note these steps are calibrated
// for the TB6600 stepper motor driver with micro-steps = 1 and current = 1.0. Valve position will be wrong
// if not operated with these settings. Valves are placed roughly 3300 steps away from each other, however 
// in operation steps are skipped so in reality this doesn't hold true.
static const Array<int> ROTARY_STATES_E2({0, 3300, 6600, 9900, 13200, 16500});
static const Array<int> ROTARY_STATES_E1({2675, 5950, 9350, 12700, 16000, 19400});
static const Array<int> ROTARY_STATES_E0({900, 4200, 7500, 10800, 14100, 17400});

// Represents relay switch states, for active high 1 = ON for active low 0 = ON. Defaults to OFF.
static const Array<int> RELAY_ACTIVE_HIGH_STATES({0, 1});
static const Array<int> RELAY_ACTIVE_LOW_STATES({1, 0});

} // namespace config

#endif