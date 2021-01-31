LEET_CODE_DIR = $(PROJECT_ROOT)leet_code
#@echo $(error LEET_CODE_DIR= $(LEET_CODE_DIR))

INCDIR			+= -I$(LEET_CODE_DIR)

OPT += -DLEET_CODE
CPP_SOURCES += $(LEET_CODE_DIR)insert_interval.cpp
 
#SOURCES += $(wildcard $(LEET_CODE_DIR)/*.c)
