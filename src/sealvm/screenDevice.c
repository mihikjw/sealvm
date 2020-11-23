#include "sealvm/screenDevice.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "sealvm/defines.h"

void clearScreen();
void setBold();
void setRegular();
void moveTo(uint8_t x, uint8_t y);

ErrCode SD_SetValue16(ScreenDevice* this, const uint16_t address, const uint16_t value) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address > MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }

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
    uint8_t y = floor(address / 16) + 1; // this conversion is fine and intended
    moveTo(x * 2, y);
    fprintf(stdout, "%c\n", charVal);
    return NO_ERR;
}

ScreenDevice* NewScreenDevice() {
    ScreenDevice* result = malloc(sizeof(ScreenDevice));
    if (!result) {
        return NULL;
    }

    result->SetValue16 = &SD_SetValue16;
    return result;
}

void clearScreen() { printf("\x1b[2J"); }

void setBold() { printf("\x1b[1m"); }

void setRegular() { printf("\x1b[0m"); }

void moveTo(const uint8_t x, const uint8_t y) { printf("\x1b[%i;%iH", y, x); }