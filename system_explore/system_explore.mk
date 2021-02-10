SYSTEM_EXPLORE_DIR = $(PROJECT_ROOT)system_explore
#@echo $(error UTILS_DIR= $(UTILS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR			+= -I$(SYSTEM_EXPLORE_DIR)
OPT += -DSYSTEM_EXPLORE_DIR
OPT += -DTEST_HEAP_MEM

SOURCES += $(SYSTEM_EXPLORE_DIR)/system_explore.c
#SOURCES += $(MATH_DIR)/permutations.c

