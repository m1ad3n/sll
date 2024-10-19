CC 		:= gcc
CFLAGS 	:= -std=c11 -Wall -Wno-format -Wno-switch -Wextra -pedantic
LDFLAGS :=

OUT_DIR	:= bin
SRC_DIR	:= src
TARGET	:= $(OUT_DIR)/tests

SRCS	:= $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS	:= $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

PREFIX	:= /usr/local
INCLUDE	:= $(PREFIX)/include
LIB_DIR	:= $(PREFIX)/lib

default: libsll.so libsll.a

install:
	cp libsll.so $(LIB_DIR)
	cp libsll.a $(LIB_DIR)
	cp src/sll.h $(INCLUDE)

test: $(TARGET)
$(TARGET): $(OBJS) | $(OUT_DIR)
	$(CC) -s -o $@ $(OBJS) $(LDFLAGS)

libsll.so: src/sll.c
	$(CC) -s $(CFLAGS) -fPIC -shared -o $@ $<

libsll.a: bin/sll.o
	ar rcs $@ $<

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -MMD -c -o $@ $<
	
$(OUT_DIR):
	mkdir -p $@

.PHONY: clean $(TARGET)
clean:
	@rm -rvf ./$(OUT_DIR)

-include $(wildcard $(OUT_DIR)/*.d)
