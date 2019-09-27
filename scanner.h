#ifndef SCANNER_H
#define SCANNER_H

#include "Arduino.h"
#include "card_buffer.h"
#include "card.h"

typedef unsigned int pin;

namespace HID5455 {

class Scanner {
private:
    pin pin_data, pin_clock, pin_green_led, pin_beeper;
public:
    Scanner(pin pin_data, pin pin_clock, pin pin_green_led, pin pin_beeper);

    void init(void);

    void morse(char* morse, int morse_len);
    void save_our_souls(void);

    void wait_for_card(CardBuffer* buffer);
    void try_read_card(CardBuffer* buffer);

    Card buffer_to_card(CardBuffer* buffer);
};

}

#endif // !HID5455_H