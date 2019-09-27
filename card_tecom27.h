#ifndef CARD_TECOM27_H
#define CARD_TECOM27_H

#include <card.h>

namespace HID5455 {

class CardTecom27 : public Card {
public:
    const unsigned int DATA_WIDTH = 27;

    const bool HAS_FACILITY_CODE = true;
    const bool HAS_CARD_NUMBER   = true;
    const bool HAS_OEM_CODE      = false;
    const bool HAS_ISSUE_LEVEL   = false;

    CardTecom27(void) = default;
    CardTecom27(CardBuffer* buffer);

    void parse_buffer(CardBuffer* buffer);
};

}

#endif // !CARD_TECOM27_H