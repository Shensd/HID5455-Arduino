#ifndef CARD_BUFFER_H
#define CARD_BUFFER_H

namespace HID5455 {

class CardBuffer {
private:
    byte buffer[6];
public:
    unsigned int data_width = 0;
    const unsigned int MAX_WIDTH = 6*8;

    CardBuffer(void);

    void clear(void);
    void push(bool value);
    bool get_bit_at(unsigned int position);
    unsigned int get_bit_range(unsigned int begin, unsigned int end);
    unsigned int get_bits(const unsigned int bits[], unsigned int len);

    void print(void);

    byte* get_buffer(void);
};

}


#endif // !CARD_BUFFER_H