TOOLS_DIR = $(SRC_DIR)/tools
TOOLS_INC_PATH = -I$(TOOLS_DIR)/inc

ifeq ($(PLATFORM_LINUX), 1)
TOOLS_PLATFORM_SOURCES = \
	$(TOOLS_DIR)/src/platform/tools_time_linux.c
else ifeq ($(PLATFORM_WINDOWS), 1)
TOOLS_PLATFORM_SOURCES = \
	$(TOOLS_DIR)/src/platform/tools_time_windows.c
else ifeq ($(PLATFORM_STM32F1), 1)
TOOLS_PLATFORM_SOURCES = \
	$(TOOLS_DIR)/src/platform/tools_time_stm32f1xx.c
else ifeq ($(PLATFORM_STM32F7), 1)
TOOLS_PLATFORM_SOURCES = \
	$(TOOLS_DIR)/src/platform/tools_time_stm32f7xx.c
endif

TOOLS_SOURCES = \
	$(TOOLS_PLATFORM_SOURCES) \
	$(TOOLS_DIR)/src/tools_buffer.c \
	$(TOOLS_DIR)/src/tools_cliopt.c \
	$(TOOLS_DIR)/src/tools_crc16.c \
	$(TOOLS_DIR)/src/tools_crc8.c \
	$(TOOLS_DIR)/src/tools_dtc.c \
	$(TOOLS_DIR)/src/tools_debug.c \
	$(TOOLS_DIR)/src/tools_demux.c \
	$(TOOLS_DIR)/src/tools_dlist.c \
	$(TOOLS_DIR)/src/tools_fifo.c \
	$(TOOLS_DIR)/src/tools_hashmap.c \
	$(TOOLS_DIR)/src/tools_hexdump.c \
	$(TOOLS_DIR)/src/tools_print.c \
	$(TOOLS_DIR)/src/tools_random.c \
	$(TOOLS_DIR)/src/tools_slist.c \
	$(TOOLS_DIR)/src/tools_string.c \
	$(TOOLS_DIR)/src/tools_thread.c \
	$(TOOLS_DIR)/src/tools_time.c \
	$(TOOLS_DIR)/src/tools_timer.c
