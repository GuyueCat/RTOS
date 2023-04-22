TOOL_PRE :=
CC := ${TOOL_PRE}gcc
AR := ${TOOL_PRE}ar
BIN := freertos-simulator
BUILD_DIR := build

ROOT_DIR := $(abspath ${CURDIR}/..)
PROJ_DIR := $(abspath ${CURDIR})
FREERTOS_DIR := ${ROOT_DIR}/freertos_kernel

# include header file
INCLUDE_DIRS := -I${PROJ_DIR}/arch
INCLUDE_DIRS += -I${PROJ_DIR}/project
INCLUDE_DIRS += -I${FREERTOS_DIR}/Source/include
INCLUDE_DIRS += -I${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix
INCLUDE_DIRS += -I${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix/utils

# include source file
SOURCE_FILES := $(wildcard ${PROJ_DIR}/arch/*.c)
SOURCE_FILES += $(wildcard ${PROJ_DIR}/project/*.c)
SOURCE_FILES += $(wildcard ${FREERTOS_DIR}/Source/*.c)
SOURCE_FILES += ${FREERTOS_DIR}/Source/portable/MemMang/heap_3.c
SOURCE_FILES += ${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
SOURCE_FILES += ${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix/port.c

CFLAGS := -ggdb3 -O0 -g
LDFLAGS := -ggdb3 -O0 -pthread -lpcap

OBJ_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

DEP_FILE = $(OBJ_FILES:%.o=%.d)

${BIN} : $(BUILD_DIR)/$(BIN)

${BUILD_DIR}/${BIN} : ${OBJ_FILES}
	@echo "Building $@ ..."
	@-mkdir -p ${@D}
	@$(CC) $^ $(CFLAGS) $(INCLUDE_DIRS) ${LDFLAGS} -o $@

-include ${DEP_FILE}

.PHONY: all clean execute

all:
${BUILD_DIR}/%.o : %.c
	@echo "Building $< ..."
	@-mkdir -p $(@D)
	@$(CC) $(CFLAGS) ${INCLUDE_DIRS} -MMD -c $< -o $@

execute:
	./${BUILD_DIR}/${BIN}

clean:
	-rm -rf $(BUILD_DIR)







