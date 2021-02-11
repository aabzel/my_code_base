ADT_DIR = $(PROJECT_ROOT)ADT
#@echo $(error UTILS_DIR= $(UTILS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR			+= -I$(ADT_DIR)

OPT += -DADT
SOURCES += $(ADT_DIR)/linked_list.c
SOURCES += $(ADT_DIR)/lifo_char.c
 
#SOURCES += $(wildcard $(ADT_DIR)/*.c)
