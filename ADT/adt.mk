ADT_DIR = $(PROJECT_ROOT)ADT
#@echo $(error UTILS_DIR= $(UTILS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR			+= -I$(ADT_DIR)

OPT += -DADT
 
#SOURCES += $(wildcard $(ADT_DIR)/*.c)
