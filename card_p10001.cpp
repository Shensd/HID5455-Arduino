#include "card_p10001.cpp"

namespace RFID {

CardP10001::CardP10001(RFID::CardBuffer* buffer) {
    parse_buffer(buffer);
}

void CardP10001::parse_buffer(RFID::CardBuffer* buffer) {
    if(buffer->data_width != DATA_WIDTH) return;
    
    // currently unused, but noted
    char parity_a = buffer->get_bit_at(0);
    char parity_b = buffer->get_bit_at(26);

	byte* raw_buffer = buffer->get_buffer();

    facility_code = buffer->get_bit_range(1, 9);
    card_number = buffer->get_bit_range(9, 25);
}

}