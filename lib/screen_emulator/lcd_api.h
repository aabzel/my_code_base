#ifndef LCD_API_H
#define LCD_API_H
 
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
 
#define LCD_PORT 65432U 

bool lcd_draw_pixel(uint16_t x, uint16_t y, bool status);
 
#ifdef __cplusplus
}
#endif

#endif /* LCD_API_H */
