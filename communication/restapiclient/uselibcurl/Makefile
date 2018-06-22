
TOP_DIR = $(shell pwd)
export TOP_DIR

include $(TOP_DIR)/*.mk
COMMON_FLAG += 

OUTPUT_DIR=${PWD}/output
INSTALL_PATH=~/tmp
# STATIC_LIBS_DIR := <somewhere>/lib
# STATIC_LIBS := $(STATIC_LIBS_DIR)/lib$(PLATFORM).a
# DYNAMIC_LIBS_DIR := <somewhere>/$(PLATFORM)/lib
# LIB_FLAGS := $(COMMON_FLAG) -lpthread -lmsgsys -L$(DYNAMIC_LIBS_DIR)
LIB_FLAGS := $(COMMON_FLAG) `curl-config --cflags` `curl-config --libs`

BIN = respapiclient

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(BIN) output
	
$(BIN): $(OBJS) 	
	$(CC) $(OBJS) $(STATIC_LIBS) -o $@  $(LIB_FLAGS)

makedir: .FORCE
	mkdir -p $(OUTPUT_DIR)
	mkdir -p $(INSTALL_PATH)

output: makedir	
	mv $(BIN) $(OBJS) $(OUTPUT_DIR)

clean: .FORCE
	rm -rf *.out *.o $(BIN) $(OUTPUT_DIR)

install: makedir
	cp $(OUTPUT_DIR)/sgdbm $(INSTALL_PATH)/sgdbm

%.o: %.c
	$(CC) $(LIB_FLAGS) -c -o $@ $<

.FORCE:
