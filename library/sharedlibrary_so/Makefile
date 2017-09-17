
TOP_DIR = $(shell pwd)
export TOP_DIR

include $(TOP_DIR)/*.mk
COMMON_FLAG += 

OUTPUT_DIR=${PWD}/output
INSTALL_PATH=~/tmp
# STATIC_LIBS_DIR := <somewhere>/lib
# STATIC_LIBS := $(STATIC_LIBS_DIR)/lib$(PLATFORM).a
DYNAMIC_LIBS_DIR := $(TOP_DIR)/output/lib
LIB_FLAGS := $(COMMON_FLAG) -lsystemcall -L$(DYNAMIC_LIBS_DIR)  -I$(TOP_DIR)/lib/libsystemcall/include
INCLUDE_DIR := $(LIB_SYSTEMCALL_INCL)

BIN = app_linked_dynamic_so

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: libs $(BIN) output
	
$(BIN): $(OBJS) 	
	$(CC) -o $@ $(OBJS) $(STATIC_LIBS)  $(LIB_FLAGS) $(INCLUDE_DIR) 

makedir: .FORCE
	mkdir -p $(OUTPUT_DIR)
	mkdir -p $(INSTALL_PATH)

output: makedir	
	mv $(BIN) $(OBJS) $(OUTPUT_DIR)

clean: .FORCE
	rm -rf *.out *.o $(BIN) $(OUTPUT_DIR)

install: makedir
	cp $(OUTPUT_DIR)/$(BIN) $(INSTALL_PATH)/$(BIN)

%.o: %.c
	$(CC) $(LIB_FLAGS) -c -o $@ $< $(INCLUDE_DIR)

libs: libsystemcall

libsystemcall: .FORCE
	make -C ./lib/libsystemcall/

.FORCE:
