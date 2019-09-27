#ifndef CARD_BUFFER_H
#define CARD_BUFFER_H

#include "Arduino.h"
#include <string.h>

namespace RFID {

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

    void print(void);

    byte* get_buffer(void);
};

}


#endif // !CARD_BUFFER_H