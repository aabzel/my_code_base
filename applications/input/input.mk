INPUT_DIR = $(PROJECT_ROOT)input
#@echo $(error UTILS_DIR= $(UTILS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))
CFLAGS			+= -I$(INPUT_DIR)

SOURCES += $(INPUT_DIR)/input.c

