# HID5455 Arduino
 
An Arduino library for interacting with the HID5455 family of RFID scanners.
 
### What is this?
 
This a set of tools made for interfacing with the [HID5455 family](https://www.hidglobal.com/products/readers/hid-proximity/5455) of RFID scanners made by HID. It includes various card reading and parsing tools, along with some fun hacks for the scanner. 
 
### How do I use this?
 
The first step in using this library is to connect your scanner to the Arduino, since these scanners are made for being installed to hard wired systems they are actually quite easy to connect to our Arduino. It should be noted here that this library was created using a model 5455BGN00, so this might not fit exactly to the scanner that you have, but this library should be easily modifiable or directly usable with many other families of HID scanners. 
 
The back of the scanner should have a table indicating what wire controls what on the scanner, but by convention:
 
| Wire Color | Purpose          |
| ---------- | ---------------- | 
| Black      | Ground           |
| Green      | Data0/Data_Data  |
| White      | Data1/Data_Clock | 
| Orange     | Green LED        |
| Brown      | Red LED          |
| Yellow     | Beep Control     | 
| Blue       | Hold             |
| Violet     | Card Present     | 
 
We are most concerned about green, white, orange, and yellow. 
 
If a line is not pulled high or low, then it will stay in its neutral state, eg. if the beeper line (yellow) is never pulled either way, the beeper will stay turned off (unless a card is scanned, of course). If a line is pulled high though,this will have the element stay in the "turned off" mode until the line is pulled low. So in full summation, to use the beeper, you need to pull the line high to initialize it, then pull it low to turn it on, and pull it high to turn it off.
 
For the example here, green is attached to pin 8, white is attached to pin 9, yellow to pin 11, and orange to pin 3.
 
This repository is formatted to aid in using Github's "download as zip" button at the top of this page, it can then be loaded into the Arduino IDE as described [https://www.Arduino.cc/en/guide/libraries](here).
 
A simple program using this library will look like the following:
 
```cpp
#include <hid5455.h>
 
#define DATA_DATA 8
#define DATA_CLOCK 9
 
#define BEEP_CONTROL 11
#define GREEN_LED 3
 
// create our scanner, passing it the pins as indicated on the backside
// of the RFID scanner
HID5455::Scanner scanner(DATA_DATA, DATA_CLOCK, GREEN_LED, BEEP_CONTROL);

// Used to print information from a H10301 HID card
void print_card_hid_h10301(HID5455::CardH10301* card) {
    Serial.print("FACILITY : ");
    Serial.println(card->facility_code);
    Serial.print("CARD NUM : ");
    Serial.println(card->card_number);
}
 
void loop(void) {
    // create a card buffer for holding the read bits
    HID5455::CardBuffer buffer;
 
    // loop will pause until a card is read, once a card is read it will be 
    // fed into the buffer
    scanner.wait_for_card(&buffer);
    
    // read the card information into a H10301 card buffer, then print
    // using the function declared above
    HID5455::CardH10301 card(&buffer);
    print_card_hid_h10301(&card);
}
 
void setup(void) {
    // these pins are used for reading data from the scanner
    pinMode(DATA_DATA, INPUT);
    pinMode(DATA_CLOCK, INPUT);
 
    // these pins are used to interact with elements on the scanner, as their
    // name suggests, they control the green led and beeping elements. 
    // (In my testing the red led line did nothing, so name dropping green
    // here was done with full intent)
    pinMode(BEEP_CONTROL, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
 
    // init the scanner
    // 
    // Caution: this is an important step as it keeps the green led and 
    // beeper from being on constantly
    scanner.init();
 
    // serial speed doesn't matter, just for personal preference, but due 
    // to the high rate of data reading I found higher baud rates to be
    // more consistent for printing
    Serial.begin(57600);
}
```
 
### What card formats are supported?
 
Since the HID5455 family of scanners only supports reading of HID cards, this library also only supports the parsing of HID cards, but still captures many formats under that umbrella. 
 
The formats currently supported are:
 
| Name     | Length      | Facility? | Card #? | OEM? | Issue? |
| -------- | ----------- | --------- | ------- | ---- | ------ |
| H10301   | 26          | Yes       | Yes     | No   | No     |
| Tecom27  | 27          | Yes       | Yes     | No   | No     |
| P10001   | 40          | Yes       | Yes     | No   | No     |
 
All card classes follow the convention `Card[Name]`.
 
### Resources
 
Here are several resources that helped me develop this library, if you are also trying to reverse engineer rfid scanners or card protocols, they may be of help.
 
 * [Proxmark3](https://github.com/Proxmark/proxmark3)
 * [cardinfo.barkweb.com.au](https://cardinfo.barkweb.com.au/)
 * [Understanding Card Formats (PDF by HID)](https://www.hidglobal.com/sites/default/files/hid-understanding_card_data_formats-wp-en.pdf)

