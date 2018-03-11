include $(BASE_DIR)/Header.mk

MODULE  := silentdream
SRC_DIR := 
DEFINE  :=
INCLUDE := -I..
LDFLAGS := -Wl,-rpath="lib" -Wl,-rpath="build/lib" -Wl,-rpath="$(HOME)/.silentdream/lib"
LIBS    := -L$(LIBS_DIR) -lsilentDreamFw

$(call build-target, executable)

include $(BASE_DIR)/Footer.mk
