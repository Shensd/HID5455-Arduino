#include "card_tecom27.h"

namespace HID5455 {

CardTecom27::CardTecom27(CardBuffer* buffer) {
    parse_buffer(buffer);
}

void CardTecom27::parse_buffer(CardBuffer* buffer) {
    if(buffer->data_width != DATA_WIDTH) return;

	byte* raw_buffer = buffer->get_buffer();

    // yall ever
    unsigned int facility_bits[] = {16, 20, 25, 24, 23, 19, 7, 11, 15, 4, 3};
    facility_code = buffer->get_bits(facility_bits, 11);

    unsigned int card_bits[] = {1, 2, 14, 13, 10, 27, 21, 17, 18, 22, 26, 8, 9, 12, 5, 6};
    card_number = buffer->get_bits(card_bits, 16);
}

}