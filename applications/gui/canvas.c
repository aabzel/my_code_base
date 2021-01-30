#include <stdio.h>

#include "canvas_i.h"
#include "icon_i.h"
#include "furi.h"
#include "lcd_api.h"

struct Canvas {
    u8g2_t fb;
    uint8_t offset_x;
    uint8_t offset_y;
    uint8_t width;
    uint8_t height;
};

 
Canvas* canvas_init() {
	printf("\n[d] %s()", __FUNCTION__);
    Canvas* canvas = furi_alloc(sizeof(Canvas));
    // send init sequence to the display, display is in sleep mode after this
    //u8g2_InitDisplay(&canvas->fb);
    //u8g2_SendBuffer(&canvas->fb);
    return canvas;
}

void canvas_free(Canvas* canvas) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    free(canvas);
}

void canvas_reset(Canvas* canvas) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    canvas_set_color(canvas, ColorBlack);
    canvas_set_font(canvas, FontSecondary);
}

void canvas_commit(Canvas* canvas) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
  // u8g2_SetPowerSave(&canvas->fb, 0); // wake up display
    //u8g2_SendBuffer(&canvas->fb);
}

void canvas_frame_set(
    Canvas* canvas,
    uint8_t offset_x,
    uint8_t offset_y,
    uint8_t width,
    uint8_t height) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    canvas->offset_x = offset_x;
    canvas->offset_y = offset_y;
    canvas->width = width;
    canvas->height = height;
}

uint8_t canvas_width(Canvas* canvas) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    return canvas->width;
}

uint8_t canvas_height(Canvas* canvas) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    return canvas->height;
}

void canvas_clear(Canvas* canvas) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    //u8g2_ClearBuffer(&canvas->fb);
}

void canvas_set_color(Canvas* canvas, Color color) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
  // u8g2_SetDrawColor(&canvas->fb, color);
}

void canvas_set_font(Canvas* canvas, Font font) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
  // u8g2_SetFontMode(&canvas->fb, 1);
    if(font == FontPrimary) {
       // u8g2_SetFont(&canvas->fb, u8g2_font_helvB08_tf);
    } else if(font == FontSecondary) {
       // u8g2_SetFont(&canvas->fb, u8g2_font_haxrcorp4089_tr);
    } else if(font == FontGlyph) {
       // u8g2_SetFont(&canvas->fb, u8g2_font_unifont_t_symbols);
    } else {
        furi_check(0);
    }
}

void canvas_draw_str(Canvas* canvas, uint8_t x, uint8_t y, const char* str) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    if(!str) return;
    x += canvas->offset_x;
    y += canvas->offset_y;
    //u8g2_DrawStr(&canvas->fb, x, y, str);
}

void canvas_draw_icon(Canvas* canvas, uint8_t x, uint8_t y, Icon* icon) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    if(!icon) return;
    x += canvas->offset_x;
    y += canvas->offset_y;
    //u8g2_DrawXBM(        &canvas->fb, x, y, icon_get_width(icon), icon_get_height(icon), icon_get_data(icon));
}

#if 0
void canvas_draw_icon_name(Canvas* canvas, uint8_t x, uint8_t y, IconName name) {
    furi_assert(canvas);
    const IconData* data = assets_icons_get_data(name);
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawXBM(&canvas->fb, x, y, data->width, data->height, data->frames[0]);
}
#endif

void canvas_draw_dot(Canvas* canvas, uint8_t x, uint8_t y) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    //u8g2_DrawPixel(&canvas->fb, x, y);
	lcd_draw_pixel(x,y, true);
}

void canvas_draw_box(Canvas* canvas, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    //u8g2_DrawBox(&canvas->fb, x, y, width, height);
}

void canvas_draw_frame(Canvas* canvas, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    //u8g2_DrawFrame(&canvas->fb, x, y, width, height);
}

void canvas_draw_line(Canvas* canvas, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    x1 += canvas->offset_x;
    y1 += canvas->offset_y;
    x2 += canvas->offset_x;
    y2 += canvas->offset_y;
    //u8g2_DrawLine(&canvas->fb, x1, y1, x2, y2);
}

void canvas_draw_xbm(
    Canvas* canvas,
    uint8_t x,
    uint8_t y,
    uint8_t w,
    uint8_t h,
    const uint8_t* bitmap) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
  // u8g2_DrawXBM(&canvas->fb, x, y, w, h, bitmap);
}

void canvas_draw_glyph(Canvas* canvas, uint8_t x, uint8_t y, uint16_t ch) {
	printf("\n[d] %s()", __FUNCTION__);
    furi_assert(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
  // u8g2_DrawGlyph(&canvas->fb, x, y, ch);
}
