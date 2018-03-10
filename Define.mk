ifndef $(DEFINE_MK)
DEFINE_MK = 1

BASE_DIR := $(shell pwd)
FRAMEWORK_DIR := $(BASE_DIR)/src
BUILD_DIR := $(BASE_DIR)/build
LIBS_DIR := $(BUILD_DIR)/lib
PLUGIN_DIR := $(BUILD_DIR)/plugins
OBJS_DIR := $(BASE_DIR)/objs

export BASE_DIR
export FRAMEWORK_DIR
export BUILD_DIR
export LIBS_DIR
export PLUGIN_DIR
export OBJS_DIR

endif
