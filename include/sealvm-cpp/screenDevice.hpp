#ifndef SEALVM_SCREENDEVICE_HPP
#define SEALVM_SCREENDEVICE_HPP

#include <cmath>
#include <iostream>

#include "sealvm-cpp/memoryDevice.hpp"

namespace SealVM {

class ScreenDevice : public MemoryDevice {
    public:
    ScreenDevice(std::vector<uint8_t>* buffer);
    ~ScreenDevice() = default;

    // GetValue returns 0 - should not read from a ScreenDevice
    const uint8_t GetValue(const uint16_t address);

    // GetValue16 returns 0 - should not read from a ScreenDevice
    const uint16_t GetValue16(const uint16_t address);

    // SetValue does nothing - should not write single bytes to ScreenDevice
    void SetValue(const uint16_t address, const uint8_t value);

    // SetValue16 writes the given value to stdout - first 8-bits are any instructions, second 8 bits are the hex value to write
    void SetValue16(const uint16_t address, const uint16_t value);

    private:
    // moveTo moves the cursor to the given x and y coordinates
    void moveTo(const uint8_t x, const uint8_t y);

    // clearScreen clears the terminal screen
    void clearScreen();

    // setBold ensures any following characters are outputted in bold
    void setBold();

    // setRegular ensures any following characters are outputted in regular text
    void setRegular();
};

} // namespace SealVM

#endif // SEALVM_SCREENDEVICE_HPP