LIB_DIR			= $(PROJECT_ROOT)/lib

# TODO: some places use lib/header.h includes, is it ok?
INCDIR			+= -I$(LIB_DIR)


# U8G2 display library
U8G2_DIR	= $(LIB_DIR)/u8g2
INCDIR		+= -I$(U8G2_DIR)
#SOURCES		+= $(U8G2_DIR)/u8x8_d_st7565.c
SOURCES		+= $(U8G2_DIR)/u8g2_d_setup.c
SOURCES		+= $(U8G2_DIR)/u8g2_intersection.c
#SOURCES		+= $(U8G2_DIR)/u8g2_setup.c
SOURCES		+= $(U8G2_DIR)/u8g2_d_memory.c
#SOURCES		+= $(U8G2_DIR)/u8x8_cad.c
#SOURCES		+= $(U8G2_DIR)/u8x8_byte.c
#SOURCES		+= $(U8G2_DIR)/u8x8_gpio.c
#SOURCES		+= $(U8G2_DIR)/u8x8_display.c
#SOURCES		+= $(U8G2_DIR)/u8x8_setup.c
SOURCES		+= $(U8G2_DIR)/u8g2_hvline.c
SOURCES		+= $(U8G2_DIR)/u8g2_line.c
SOURCES		+= $(U8G2_DIR)/u8g2_ll_hvline.c
SOURCES		+= $(U8G2_DIR)/u8g2_circle.c
SOURCES		+= $(U8G2_DIR)/u8g2_box.c
SOURCES		+= $(U8G2_DIR)/u8g2_buffer.c
SOURCES		+= $(U8G2_DIR)/u8g2_font.c
SOURCES		+= $(U8G2_DIR)/u8g2_fonts.c
#SOURCES		+= $(U8G2_DIR)/u8x8_8x8.c
SOURCES		+= $(U8G2_DIR)/u8g2_bitmap.c


SCREEN_EMULATOR_DIR = $(LIB_DIR)/screen_emulator

INCDIR += -I$(SCREEN_EMULATOR_DIR)

SOURCES += $(wildcard $(SCREEN_EMULATOR_DIR)/*.c)

