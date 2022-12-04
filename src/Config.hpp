#ifndef CONFIG_H
#define CONFIG_H

#include "Array.hpp"
#include "Actuators/FlapDiverterValve/FlapDiverterValve.hpp"

/** ----- OPERATION SETTINGS ----- 
 * TODO: This file is not functional yet, the intent is to use this file for constants intend of cluttering 
 * the main file
 */
namespace Config {
  const unsigned long DEFAULT_POLLING_INTERVAL = 5000;
  const unsigned long FAST_POLLING_INTERVAL = 1000;
}

#endif