include Define.mk

all:$(OBJS_DIR) $(LIBS_DIR) $(PLUGIN_DIR) silentdream pre_install

$(OBJS_DIR):
	-mkdir -p $@ 

$(LIBS_DIR):
	-mkdir -p $@ 

$(PLUGIN_DIR):
	-mkdir -p $@ 

clean:
	@make silentdream TARGET:=clean

silentdream:
	@make -C$(BASE_DIR)/src $(TARGET)
	@make -C$(BASE_DIR)/src/main $(TARGET)
	@make -C$(BASE_DIR)/apps/hello $(TARGET)


######################
pre_install:$(BUILD_DIR)/conf
	@cp conf/* $< -rf

$(BUILD_DIR)/conf:
	@-mkdir -p $@

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
