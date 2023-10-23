#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H

#include "ESPDateTime.h"
#include <DoubleResetDetector.h>

// Number of seconds after reset during which a 
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 2
// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

extern DoubleResetDetector drd;

void setupDateTime();

#endif
