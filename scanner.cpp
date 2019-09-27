#include "Arduino.h"
#include "scanner.h"
#include <string.h>

// https://en.wikipedia.org/wiki/Wiegand_interface
// https://www.hidglobal.com/sites/default/files/hid-understanding_card_data_formats-wp-en.pdf
// https://telaeris.com/blog/down-and-dirty-with-wiegand/

namespace HID5455 {

Scanner::Scanner(pin pin_data, pin pin_clock, pin pin_green_led, pin pin_beeper) {
	Scanner::pin_data = pin_data;
	Scanner::pin_clock = pin_clock;
    Scanner::pin_green_led = pin_green_led;
    Scanner::pin_beeper = pin_beeper;
}

void Scanner::init(void) {
    digitalWrite(pin_beeper, HIGH);
    digitalWrite(pin_green_led, HIGH);
}

void Scanner::morse(char* beep_str, int len) {
    const int TIME_UNIT = 100;

    const int DIT = TIME_UNIT * 1;
    const int DAH = TIME_UNIT * 3;

    const int IN_LETTER_REST  = TIME_UNIT;
    const int OUT_LETTER_REST = TIME_UNIT * 2;
    const int WORD_REST       = TIME_UNIT * 6;
    
    digitalWrite(pin_beeper, HIGH);
    digitalWrite(pin_green_led, HIGH);
    for(int i = 0; i < len; i++) {
        switch(beep_str[i]) {
            case '.':
                digitalWrite(pin_beeper, LOW);
                digitalWrite(pin_green_led, LOW);
                delay(DIT);
                break;
            case '-':
                digitalWrite(pin_beeper, LOW);
                digitalWrite(pin_green_led, LOW);
                delay(DAH);
                break;
            case ' ':
                delay(OUT_LETTER_REST);
                break;
            case '/':
                delay(WORD_REST);
                break;
        }
        digitalWrite(pin_beeper, HIGH);
        digitalWrite(pin_green_led, HIGH);
        delay(IN_LETTER_REST);
    }

    digitalWrite(pin_beeper, HIGH);
    digitalWrite(pin_green_led, HIGH);

}

void Scanner::save_our_souls(void) {
    char* sos = "... --- .../";
    while(true) {
        morse(sos, strlen(sos));
    }
}

void Scanner::wait_for_card(CardBuffer* buffer) {
	const unsigned int STREAM_END_THREASHOLD = 250;
	
	int read_position = 0;
	
	bool current_bit_read = false;
	bool stream_active = false;
	
	unsigned int gap_timer = 0;
	
	while(true) {
		if(stream_active && read_position > buffer->MAX_WIDTH) {
			break;
		}

		int data_value = digitalRead(Scanner::pin_data);
		int clock_value = digitalRead(Scanner::pin_clock);

		// if both high no data is being sent
		if(clock_value == HIGH && data_value == HIGH)    {
			current_bit_read = false;
			gap_timer++;
		
			// if we are outside of the gap timer threashold and a 
			// stream is active, that means the stream is finished
			if(gap_timer >= STREAM_END_THREASHOLD && stream_active) {
				break;
			}
	
			continue;
		}
		
		// The current bit as been read, don't read again 
		// until another double high is read
		if(current_bit_read) continue;
		
		// reset gap timer 
		gap_timer = 0;
		current_bit_read = true;
		stream_active = true;
	
		// 0 sent
		if(data_value == LOW) {
			buffer->push(0);
		}
		// 1 sent
		if(clock_value == LOW) {
			buffer->push(1);
		}
		read_position++;
	}
}

void Scanner::try_read_card(CardBuffer* buffer) {
    int data_value = digitalRead(Scanner::pin_data);
    int clock_value = digitalRead(Scanner::pin_clock);

    if(clock_value == HIGH && data_value == HIGH) return;

    wait_for_card(buffer);
}

Card Scanner::buffer_to_card(CardBuffer* buffer) {
    
}

}