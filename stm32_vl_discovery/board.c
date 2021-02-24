#include "board.h"

//#include "pal.h"

pin_info_t pin_info[PIN_COUNT + 1U] = {
    { (uint8_t)8,        "pin" },
    { (uint8_t)0xFFU,                            "" }
};



void init_pins (void) {
	int pin_table_size=0;
    for(int pin=0; pin<pin_table_size ;pin++){
		init_pin();
	}
}
