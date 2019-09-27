#include "Arduino.h"
#include "card_buffer.h"

namespace RFID {

CardBuffer::CardBuffer(void) {}


void CardBuffer::clear(void) {
    memset(buffer, 0, data_width);
	data_width = 0;
}

void CardBuffer::push(bool value) {
    unsigned int position = data_width;

    if(position > MAX_WIDTH || data_width >= MAX_WIDTH) return;

    int slot = position / 8;
    int offset = 7 - (position % 8);

	// 1 read
	if(value) {
		buffer[slot] |= 1 << offset;
	}
	// 0 read
	if(!value) {
		buffer[slot] &= ~(1 << offset);
	}

    data_width++;
}

bool CardBuffer::get_bit_at(unsigned int position) {
    int slot = position / 8;
    int offset = 7 - (position % 8);

    return buffer[slot] & (1 << offset);
}

unsigned int CardBuffer::get_bit_range(unsigned int begin, unsigned int end) {
	if(begin > end) return 0;

	unsigned int total = 0;

	for(unsigned int i = begin; i < end; i++) {
		total = (total << 1) + get_bit_at(i);
	}

	return total;
}

void CardBuffer::print(void) {
	for(int i = 0; i < (data_width / 8) + 1; i++) {
		Serial.println(buffer[i], BIN);
	}
}

byte* CardBuffer::get_buffer(void) {
    return buffer;
}

}