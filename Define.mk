ifndef DEFINE_MK
DEFINE_MK = 1

export BASE_DIR := $(shell pwd)
export FRAMEWORK_DIR := $(BASE_DIR)/src
export BUILD_DIR := $(BASE_DIR)/build
export LIBS_DIR := $(BUILD_DIR)/lib
export PLUGIN_DIR := $(BUILD_DIR)/plugins
export OBJS_DIR := $(BASE_DIR)/objs

endif
