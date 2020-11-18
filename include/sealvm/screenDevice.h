#ifndef SEALVM_SEALVM_SCREENDEVICE_H
#define SEALVM_SEALVM_SCREENDEVICE_H

#include <stdint.h>

#include "sealvm/errors.h"

typedef struct ScreenDevice {
    // SetValue16 outputs the given value to the terminal, first 8-bits are instruction flags, latter 8 bits are hex value to write
    ErrCode (*SetValue16)(struct ScreenDevice*, const uint16_t address, const uint16_t value);
} ScreenDevice;

// NewScreenDevice is a constructor for ScreenDevice
ScreenDevice* NewScreenDevice();

#endif // SEALVM_SEALVM_SCREENDEVICE_H