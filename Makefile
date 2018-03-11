include Define.mk

TARGET_DIRS:= $(OBJS_DIR) $(LIBS_DIR) $(PLUGIN_DIR) $(CONF_DIR)
EXTRA_DIRS := modules apps
.PHONY:all clean silentdream $(TARGET_DIRS) $(EXTRA_DIRS)

all:$(TARGET_DIRS) silentdream pre_install

clean: TARGET:=clean
clean:silentdream

silentdream:
	@make -C$(BASE_DIR)/src $(TARGET)
	@make -C$(BASE_DIR)/src/main $(TARGET)
	@make extra_target TARGET=$(TARGET)

extra_target:$(EXTRA_DIRS)

$(EXTRA_DIRS):
	@make -C$@ $(TARGET)

$(TARGET_DIRS):
	-mkdir -p $@ 

######################
pre_install:
	@cp conf/* $(CONF_DIR) -rf

install:pre_install
	@if [ ! -d ~/.silentdream ];then \
	    mkdir ~/.silentdream; \
    fi
	@cp build/* ~/.silentdream -rf
	@ln -s ~/.silentdream/silentdream -t ~/bin/ -rf
	@echo "install success!"

uninstall:
	@-rm ~/bin/silentdream
	@-rm ~/.silentdream -rf
	@echo "uninstall success!";

kill:
	-kill `ps aux|grep 'silentdream$$'|grep -v grep|awk '{print $$2}'`



