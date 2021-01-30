CORE_DIR		= $(PROJECT_ROOT)/core

CFLAGS			+= -I$(CORE_DIR) -D_GNU_SOURCE
CFLAGS			+= -I$(CORE_DIR)/furi

SOURCES		+= $(wildcard $(CORE_DIR)/*.c)
SOURCES		+= $(wildcard $(CORE_DIR)/furi/*.c)
