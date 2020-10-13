#include "sealvm/screenDevice.hpp"

using namespace SealVM; 

ScreenDevice::ScreenDevice(std::vector<uint8_t>* buffer): MemoryDevice(buffer){}

const uint8_t ScreenDevice::GetValue(const uint16_t address){ return 0; }

const uint16_t ScreenDevice::GetValue16(const uint16_t address){ return 0; }

void ScreenDevice::SetValue(const uint16_t address, const uint8_t value){}

void ScreenDevice::SetValue16(const uint16_t address, const uint16_t value){
    uint8_t command = (value & 0xff00) >> 8;
    switch (command) {
        case 0xff: {
            clearScreen();  
            break; 
        }
        case 0x01: {
            setBold();
            break;
        }
        case 0x02: {
            setRegular();
            break;
        }
    }
    uint8_t charVal = value & 0x00ff;
    uint8_t x = (address % 16) + 1;
    uint8_t y = std::floor(address / 16) + 1;
    moveTo(x * 2, y);
    std::cout << charVal;
}

void ScreenDevice::moveTo(const uint8_t x, const uint8_t y){ std::cout << "\x1b[" + std::to_string(y) + ";" + std::to_string(x) + "H"; }

void ScreenDevice::clearScreen() { std::cout << "\x1b[2J"; }

void ScreenDevice::setBold() { std::cout << "\x1b[1m"; }

void ScreenDevice::setRegular() { std::cout << "\x1b[0m"; }