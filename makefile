CC ?= gcc
CFLAGS = -Werror -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wno-unused-function -Wno-unused-but-set-variable -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=leak -fsanitize=undefined -fsanitize-address-use-after-scope
INCLUDE_FLAG = -I
SOURCES = src
HEADERS = include
TARGET = target
BIN = bin
EXECUTABLE = dataStorage

COMMON = $(SOURCES)/common/data_structures
COMMON_DEPS = $(wildcard $(HEADERS)/common/data_structures/*.h)
#CONTROLLER=
#STORAGE=

DEPS = COMMON_DEPS

#all: dataStorage main

#dataStorage: controller storage common




controller:
	#$(CC) $(SOURCE)/controller/

storage:

#common:
#	$(CC) $(COMMON)/linked_list.c -c  -o


#main:
#	$(CC) $(SOURCES)/A.c -o $(EXECUTABLE)

check_list: $(COMMON_DEPS)
	$(CC) -o $(TARGET)/hello $(COMMON)/linked_list.c $(SOURCES)/A.c


create_target_dir:
	mkdir $(TARGET)

check_macro:
	$(CC) -E $(SOURCES)/A.c $(TARGET)/hello

clean: 
	rm -rf target/* dataStorage