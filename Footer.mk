ifndef FOOTER_MK
FOOTER_MK = 1

ifeq ($(MODULE),)
 MODULE := $(notdir $(CURDIR))
 # MODULE := $(notdir $(shell pwd))
endif

CFLAGS := -g -Werror -std=c99 -fPIC
CXXFLAGS:= -g -Werror -std=c++11 -fPIC

plugin:LIBS += -L$(LIBS_DIR) -lsilentDreamFw

vpath %.c $(SRC_DIR)
vpath %.cpp $(SRC_DIR)
SRC := $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
SRC += $(wildcard *.c)
SRC += $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp))
SRC += $(wildcard *.cpp)

OBJ_DIR := $(OBJS_DIR)/$(MODULE)

OBJ := $(SRC:.c=.o)
OBJ := $(OBJ:.cpp=.o)
OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ)))


plugin:$(PLUGIN_DIR)/lib$(MODULE).so

shared_library:$(LIBS_DIR)/lib$(MODULE).so

static_library:$(LIBS_DIR)/lib$(MODULE).a

executable:$(BUILD_DIR)/$(MODULE)

$(PLUGIN_DIR)/lib$(MODULE).so:$(OBJ)
	@$(CXX) -shared $(LDFLAGS) -o$@ $^ $(LIBS)
	@echo "  PLUGIN  \033[1m\033[32mlib$(MODULE).so\033[0m"

$(LIBS_DIR)/lib$(MODULE).so:$(OBJ)
	@$(CXX) -shared $(LDFLAGS) -o$@ $^ $(LIBS)
	@echo "  LINK    \033[1m\033[32mlib$(MODULE).so\033[0m"

$(LIBS_DIR)/lib$(MODULE).a:$(OBJ)
	@$(AR) -r $@ $^
	@echo "  AR      \033[1m\033[32mlib$(MODULE).a\033[0m"

$(BUILD_DIR)/$(MODULE):$(OBJ)
	@$(CXX) $(LDFLAGS) -o$@ $^ $(LIBS)
	@echo "  BUILD   \033[1m\033[32m$(MODULE)\033[0m"


-include $(OBJ:.o=.dep)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o:%.c |$(OBJ_DIR)
	@$(CC) $(CFLAGS) $(DEFINE) $(COMMON_INC) $(INCLUDE) -c $< -o $@ -MD -MF $(@:.o=.dep)
	@echo "  CC      $<"

$(OBJ_DIR)/%.o:%.cpp |$(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) $(DEFINE) $(COMMON_INC) $(INCLUDE) -c $< -o $@ -MD -MF $(@:.o=.dep)
	@echo "  CXX     $<"

clean:
	-rm -rf $(OBJ_DIR)

install_plugin:
	-cp $(PLUGIN_DIR)/lib$(MODULE).so ~/.silentdream/plugins/ -rf


endif
