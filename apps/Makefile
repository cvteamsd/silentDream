dirs := $(shell find . -maxdepth 1 -type d)
dirs := $(basename $(patsubst ./%,%,$(dirs)))

.PHONY:all clean target

all clean:target

target:
	@for dir in $(dirs);do \
		if [ -f $$dir/Makefile ];then \
		make -C$$dir $(TARGET) || exit "$$?"; \
		fi; \
	done;


