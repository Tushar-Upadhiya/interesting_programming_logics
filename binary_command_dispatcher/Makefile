CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -MMD -MP

BUILD_DIR =build
TARGET = $(BUILD_DIR)/parser

SRCS = main.c cmd_dispatcher.c  
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ 

$(BUILD_DIR)/%.o: %.c 
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)


.PHONY: all clean
clean:
	rm -rf $(BUILD_DIR)
