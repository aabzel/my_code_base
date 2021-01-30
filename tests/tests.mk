TESTS_DIR = $(PROJECT_ROOT)tests
#@echo $(error UTILS_DIR= $(UTILS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))
CFLAGS			+= -I$(TESTS_DIR)

SOURCES += $(TESTS_DIR)/uTests.c
SOURCES += $(TESTS_DIR)/test_convert.c

