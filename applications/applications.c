#include "applications.h"

#include <stddef.h>

#ifdef APP_TEST
void flipper_test_app(void* p);
#endif

void display_u8g2(void* p);
void input_task(void* p);
void menu_task(void* p);
void gui_task(void* p);

 
 