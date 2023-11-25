CC=g++
CFlags=-Werror -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wno-unused-function -Wno-unused-but-set-variable -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=leak -fsanitize=undefined -fsanitize-address-use-after-scope

all: dataStorage

dataStorage: controller storage


controller:
	

storage: 


clean: 
	rm -rf *.o dataStorage 