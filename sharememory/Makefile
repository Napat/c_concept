
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
LIB_FLAGS := $(COMMON_FLAG)

BIN_1 = shmem_1
BIN_2 = shmem_2

SRCS_1 = $(wildcard *.c)
SRCS_1 := $(filter-out mainapp_2.c, $(SRCS_1))
OBJS_1 = $(patsubst %.c,%.o,$(SRCS_1))

SRCS_2 = $(wildcard *.c)
SRCS_2 := $(filter-out mainapp_1.c, $(SRCS_2))
OBJS_2 = $(patsubst %.c,%.o,$(SRCS_2))

all: $(BIN_1) $(BIN_2) output
	
$(BIN_1): $(OBJS_1) 	
	$(CC) $(OBJS_1) $(STATIC_LIBS) -o $@ $(LIB_FLAGS)

$(BIN_2): $(OBJS_2) 	
	$(CC) $(OBJS_2) $(STATIC_LIBS) -o $@ $(LIB_FLAGS)

makedir: .FORCE
	mkdir -p $(OUTPUT_DIR)
	mkdir -p $(INSTALL_PATH)

output: makedir	
	mv $(BIN_1) $(OBJS_1) $(OUTPUT_DIR)
	mv $(BIN_2) $(OBJS_2) $(OUTPUT_DIR)

clean: .FORCE
	rm -rf *.out *.o $(BIN_1) $(BIN_2) $(OUTPUT_DIR)

install: makedir
	cp $(OUTPUT_DIR)/$(BIN_1) $(INSTALL_PATH)/$(BIN_1)
	cp $(OUTPUT_DIR)/$(BIN_2) $(INSTALL_PATH)/$(BIN_2)

%.o: %.c
	$(CC) $(LIB_FLAGS) -c -o $@ $<

.FORCE:
