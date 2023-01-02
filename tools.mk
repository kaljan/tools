TOOLS_DIR = $(SRC_DIR)/tools
TOOLS_INC_PATH = -I$(TOOLS_DIR)/inc

TOOLS_PLATFORM_SOURCES = \
	$(TOOLS_DIR)/src/platform/tools_time_linux.c \
	$(TOOLS_DIR)/src/platform/tools_time_stm32f1xx.c \
	$(TOOLS_DIR)/src/platform/tools_time_stm32f7xx.c \
	$(TOOLS_DIR)/src/platform/tools_time_windows.c

TOOLS_SOURCES = \
	$(TOOLS_DIR)/src/tools_buffer.c \
	$(TOOLS_DIR)/src/tools_debug.c \
	$(TOOLS_DIR)/src/tools_fifo.c \
	$(TOOLS_DIR)/src/tools_hexdump.c \
	$(TOOLS_DIR)/src/tools_print.c \
	$(TOOLS_DIR)/src/tools_random.c \
	$(TOOLS_DIR)/src/tools_string.c \
	$(TOOLS_DIR)/src/tools_time.c \
	$(TOOLS_DIR)/src/tools_timer.c


