TARGET_DIR = ./targets
SRC_DIR = ./src

SRCS_CPP = $(wildcard $(SRC_DIR)/*.cpp)
TARGETS_CPP = $(SRCS_CPP:$(SRC_DIR)/%.cpp=$(TARGET_DIR)/%)

SRCS_C = $(wildcard $(SRC_DIR)/*.c)
TARGETS_C = $(SRCS_C:$(SRC_DIR)/%.c=$(TARGET_DIR)/%)

CP = g++
CC = gcc
CFLAGS = -Wall -g

all:$(TARGETS_CPP) $(TARGETS_C) 
$(TARGETS_CPP): $(TARGET_DIR)%: $(SRC_DIR)%.cpp
	$(CP) $< $(CFLAGS) -o $@

$(TARGETS_C): $(TARGET_DIR)%: $(SRC_DIR)%.c
	$(CC) $< $(CFLAGS) -o $@

.PHONY:clean all
clean:
	del targets\*.exe