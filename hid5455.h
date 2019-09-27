#ifndef HID5455_H
#define HID5455_H

#include "Arduino.h"
#include "card_buffer.h"
#include <string.h>

// https://en.wikipedia.org/wiki/Wiegand_interface
// https://www.hidglobal.com/sites/default/files/hid-understanding_card_data_formats-wp-en.pdf
// https://telaeris.com/blog/down-and-dirty-with-wiegand/

typedef unsigned int pin;

namespace RFID {

struct card_hid_h10301 {
    boolean parity_a : 1;
    boolean parity_b : 1;
    boolean : 0;
    
    unsigned int facility;
    unsigned int card_number;
};

class HID5455 {
private:
    pin pin_data, pin_clock, pin_green_led, pin_beeper;
public:
    HID5455(pin pin_data, pin pin_clock, pin pin_green_led, pin pin_beeper);

    void init(void);

    void morse(char* morse, int morse_len);
    void save_our_souls(void);
    void wait_for_card(CardBuffer* buffer);
    Card buffer_to_card(CardBuffer* buffer);
};

}

#endif // !HID5455_H