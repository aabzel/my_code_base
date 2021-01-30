WIN_UTILS_DIR = $(PROJECT_ROOT)win_utils
#@echo $(error UTILS_DIR= $(UTILS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))
CFLAGS			+= -I$(WIN_UTILS_DIR)
OPT += -DWIN_UTILS
#SOURCES += $(WIN_UTILS_DIR)/bit_utils.c
#SOURCES += $(WIN_UTILS_DIR)/convert.c
#SOURCES += $(WIN_UTILS_DIR)/float_utils.c
#SOURCES += $(WIN_UTILS_DIR)/str_ops.c
#SOURCES += $(WIN_UTILS_DIR)/utils.c

SOURCES += $(wildcard $(WIN_UTILS_DIR)/*.c)
