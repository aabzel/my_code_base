APP_DIR		= $(PROJECT_ROOT)/applications

INCDIR		+= -I$(APP_DIR)
SOURCES	+= $(APP_DIR)/applications.c

BUILD_MENU =1
ifeq ($(BUILD_MENU), 1)
    APP_INPUT	= 1
    APP_GUI		= 1
endif

ifeq ($(APP_GUI), 1)
    CFLAGS		+= -DAPP_GUI
	INCDIR		+= -I$(APP_DIR)/gui
    SOURCES	+= $(wildcard $(APP_DIR)/gui/*.c)
    SOURCES	+= $(wildcard $(APP_DIR)/gui/modules/*.c)
endif

ifeq ($(APP_INPUT), 1)
    #@echo $(error APP_INPUT= $(APP_INPUT))
	INCDIR		+= -I$(APP_DIR)/input
    CFLAGS		+= -DAPP_INPUT
    SOURCES	+= $(APP_DIR)/input/input.c
endif

ifeq ($(BUILD_MENU), 1)
#@echo $(error BUILD_MENU=$(BUILD_MENU))
    APP_INPUT	= 1
    APP_GUI		= 1
    CFLAGS		+= -DBUILD_MENU
	INCDIR		+= -I$(APP_DIR)/menu
    SOURCES	+= $(wildcard $(APP_DIR)/menu/*.c)
    #SOURCES	+= $(wildcard $(APP_DIR)/app-loader/*.c)
endif





