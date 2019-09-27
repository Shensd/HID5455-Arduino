#ifndef CARD_H10301_H
#define CARD_H10301_H

#include "Arduino.h"
#include "card.h"

namespace RFID {

class CardH10301 : public Card {
public:
    const unsigned int DATA_WIDTH = 26;

    const bool HAS_FACILITY_CODE = true;
    const bool HAS_CARD_NUMBER   = true;
    const bool HAS_OEM_CODE      = false;
    const bool HAS_ISSUE_LEVEL   = false;

    CardH10301(void) = default;
    CardH10301(RFID::CardBuffer* buffer);

    void parse_buffer(RFID::CardBuffer* buffer);
};

}

#endif // !CARD_H10301_H