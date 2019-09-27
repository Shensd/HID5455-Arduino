#ifndef CARD_H
#define CARD_H

#include "Arduino.h"
#include "card_buffer.h"

namespace HID5455 {

class Card {
public:
    unsigned int facility_code = 0;
    unsigned int card_number   = 0;
    unsigned int oem_code      = 0;
    unsigned int issue_level   = 0;

    const unsigned int DATA_WIDTH = 0;

    const bool HAS_FACILITY_CODE = false;
    const bool HAS_CARD_NUMBER   = false;
    const bool HAS_OEM_CODE      = false;
    const bool HAS_ISSUE_LEVEL   = false;

    virtual void parse_buffer(RFID::CardBuffer* buffer) = 0;
};

}

#endif // !CARD_H