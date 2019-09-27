#include "card_h10301.h"

namespace HID5455 {

CardH10301::CardH10301(CardBuffer* buffer) {
    parse_buffer(buffer);
}

void CardH10301::parse_buffer(CardBuffer* buffer) {
    if(buffer->data_width != DATA_WIDTH) return;
    
    // currently unused, but noted
    char parity_a = buffer->get_bit_at(0);
    char parity_b = buffer->get_bit_at(26);

	byte* raw_buffer = buffer->get_buffer();

    facility_code = buffer->get_bit_range(1, 9);
    card_number = buffer->get_bit_range(9, 25);
}

}