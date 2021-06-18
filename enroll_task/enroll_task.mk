ENROLL_TASK_DIR = $(PROJECT_ROOT)enroll_task
#@echo $(error UTILS_DIR= $(UTILS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))
INCDIR			+= -I$(ENROLL_TASK_DIR)
OPT += -DENROLL_TASKS


SOURCES += $(ENROLL_TASK_DIR)/evbox_task.c
SOURCES += $(ENROLL_TASK_DIR)/evbox_task_test.c




