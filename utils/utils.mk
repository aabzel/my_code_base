UTILS_DIR = $(PROJECT_ROOT)utils
#@echo $(error UTILS_DIR= $(UTILS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))
CFLAGS			+= -I$(UTILS_DIR)

SOURCES += $(UTILS_DIR)/bit_utils.c
SOURCES += $(UTILS_DIR)/convert.c
SOURCES += $(UTILS_DIR)/float_utils.c
SOURCES += $(UTILS_DIR)/str_ops.c
SOURCES += $(UTILS_DIR)/utils.c
