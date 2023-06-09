WORK_DIR = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build

ifdef DEBUG
CFLAGS += -Og -g
else 
CFLAGS += -O2
endif

CC = clang
CXX = clang++
CFLAGS += -I/usr/local/include -I./thirdparty -I./include
CFLAGS += -DDBG_MACRO_NO_WARNING -MMD
CXXFLAGS += $(CFLAGS)
CXXFLAGS += -std=c++17
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

C_SRCS = $(shell find src -name *.c) thirdparty/cJSON/cJSON.c
CXX_SRCS = $(shell find src -name *.cpp) 
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(C_SRCS)) \
			$(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CXX_SRCS))
DEPS = $(patsubst %.c, $(BUILD_DIR)/%.d, $(C_SRCS)) \
			$(patsubst %.cpp, $(BUILD_DIR)/%.d, $(CXX_SRCS))
BIN ?= $(BUILD_DIR)/game

$(BUILD_DIR)/%.o: %.cpp
	@echo "+ CPP $(notdir $<)"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: %.c
	@echo "+ CC $(notdir $<)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJS)
	@echo "+ LD $(notdir $^)"
	@$(CXX) $(LDFLAGS) -o $@ $^

run: $(BIN)
	@echo "running..."
	@$(BIN)

gdb: $(BIN)_gdb 
	@echo "debuging..."
	@lldb $(BIN)_gdb

$(BIN)_gdb:
	@make _gdb DEBUG=1 BIN=$(BIN)_gdb
_gdb: $(OBJS)

-include $(DEPS)

clean: 
	@rm -rf $(WORK_DIR)/build
