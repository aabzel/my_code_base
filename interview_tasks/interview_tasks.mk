INTERVIEW_DIR = $(PROJECT_ROOT)interview_tasks
#@echo $(error UTILS_DIR= $(UTILS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))
INCDIR			+= -I$(INTERVIEW_DIR)

OPT += -DINTERVIEW_TAKSK

SOURCES += $(INTERVIEW_DIR)/dsol_tasks.c
#SOURCES += $(WIN_UTILS_DIR)/convert.c
#SOURCES += $(WIN_UTILS_DIR)/float_utils.c
#SOURCES += $(WIN_UTILS_DIR)/str_ops.c
#SOURCES += $(WIN_UTILS_DIR)/utils.c

#SOURCES += $(wildcard $(INTERVIEW_DIR)/*.c)
