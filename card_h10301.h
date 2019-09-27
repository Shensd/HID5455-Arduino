#ifndef CARD_H10301_H
#define CARD_H10301_H

#include <card.h>

namespace HID5455 {

class CardH10301 : public Card {
public:
    const unsigned int DATA_WIDTH = 26;

    const bool HAS_FACILITY_CODE = true;
    const bool HAS_CARD_NUMBER   = true;
    const bool HAS_OEM_CODE      = false;
    const bool HAS_ISSUE_LEVEL   = false;

    CardH10301(void) = default;
    CardH10301(HID5455::CardBuffer* buffer);

    void parse_buffer(CardBuffer* buffer);
};

}

#endif // !CARD_H10301_H