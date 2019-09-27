#include "card_p10001.cpp"

namespace HID5455 {

CardP10001::CardP10001(CardBuffer* buffer) {
    parse_buffer(buffer);
}

void CardP10001::parse_buffer(CardBuffer* buffer) {
    if(buffer->data_width != DATA_WIDTH) return;

	byte* raw_buffer = buffer->get_buffer();

    facility_code = buffer->get_bit_range(5, 17);
    card_number = buffer->get_bit_range(17, 33);
}

}