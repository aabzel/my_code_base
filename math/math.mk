MATH_DIR = $(PROJECT_ROOT)math
#@echo $(error UTILS_DIR= $(UTILS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))
INCDIR			+= -I$(MATH_DIR)
OPT += -DMATH
#OPT += -DCOMBINATIONS
OPT += -DPERMUTATIONS

SOURCES += $(MATH_DIR)/algorithms.c
#SOURCES += $(MATH_DIR)/permutations.c

