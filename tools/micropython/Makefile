# Generates MicroPython for TinyDesk Shell from a MicroPython checkout:
#
# - the interpreter sources the shell builds (third_party/micropython),
#   only with INTERPRETER=1 (when moving to another MicroPython release);
# - the headers MicroPython generates from the configuration (qstrs,
#   module and root-pointer tables, version) and the frozen Python modules,
#   into OUT (genhdr/ and frozen/).
#
# The shell's own build uses OUT=python/gen. An application that adds
# modules of its own (TinyDesk's desktop: tdui, tdapp, tinydesk) runs this
# Makefile with its C files, qstrs and manifest and its own OUT, and builds
# with that OUT instead (see python/README.md):
#
#   EXT_C          the application's module sources (MP_REGISTER_MODULE ...)
#   EXT_CFLAGS     include paths those need
#   EXT_QSTR_DEFS  a qstrdefs file of the application's (optional)
#   MANIFEST       its manifest.py (which may include the shell's)
#   MANIFEST_VARS  NAME=path pairs the manifest uses ($(TDSH_PY_DIR) and
#                  $(MPY_DIR) are always there)
#   OUT            where genhdr/ and frozen/ go
#
# Based on MicroPython's ports/embed/embed.mk. Run it through gen.sh
# (Linux or WSL: needs make, gcc and python3).

ifeq ($(MICROPYTHON_TOP),)
$(error set MICROPYTHON_TOP to a MicroPython checkout, see README.md)
endif

TDSH_ROOT := $(abspath ../..)
PORT_DIR := $(TDSH_ROOT)/python
PACKAGE_DIR := $(TDSH_ROOT)/third_party/micropython
OUT ?= $(PORT_DIR)/gen
MANIFEST ?= $(PORT_DIR)/manifest.py
INTERPRETER ?= 0
BUILD := build

include $(MICROPYTHON_TOP)/py/mkenv.mk
include $(TOP)/py/py.mk

# py.mk lists mpconfigport.h as a dependency of every generated header.
vpath mpconfigport.h $(PORT_DIR)

# Names the generator cannot see in use (see qstrdefsport.h).
QSTR_DEFS += $(PORT_DIR)/qstrdefsport.h $(EXT_QSTR_DEFS)

# The same include paths as the real builds, so the port files preprocess
# as they compile. No platform macros are defined here: code inside
# #ifdef ESP_PLATFORM / _WIN32 must not introduce qstrs. TD_PY_GENHDR turns
# on both native-code emitters (Xtensa for the ESP32, x64 for Linux), so
# the tables have the names of each.
# ssl (extmod/modtls_mbedtls.c) needs mbedTLS's headers: ESP-IDF's copy
# by default (IDF_PATH), or MBEDTLS_INC=/path/to/mbedtls/include.
MBEDTLS_INC ?= $(IDF_PATH)/components/mbedtls/mbedtls/include
ifeq ($(wildcard $(MBEDTLS_INC)/mbedtls/ssl.h),)
$(error set IDF_PATH (ESP-IDF 5.3.1) or MBEDTLS_INC to mbedTLS's include directory, for ssl)
endif
CFLAGS += -I$(MBEDTLS_INC)
CFLAGS += -DTD_PY_GENHDR -I$(PORT_DIR) -I$(TOP) -I$(BUILD) \
	-I$(TDSH_ROOT)/include $(EXT_CFLAGS) -std=gnu11

EXTMOD_C := \
	extmod/modasyncio.c \
	extmod/modbinascii.c \
	extmod/modhashlib.c \
	extmod/modheapq.c \
	extmod/modjson.c \
	extmod/modmachine.c \
	extmod/modos.c \
	extmod/modrandom.c \
	extmod/modre.c \
	extmod/modselect.c \
	extmod/modtime.c \
	extmod/modtls_mbedtls.c \
	extmod/vfs.c \
	extmod/vfs_posix_file.c \
	extmod/vfs_reader.c \
	extmod/machine_adc.c \
	extmod/machine_bitstream.c \
	extmod/machine_i2c.c \
	extmod/machine_pulse.c \
	extmod/machine_pwm.c \
	extmod/machine_spi.c \
	extmod/machine_uart.c

# Software SPI for machine.SoftSPI.
DRIVERS_C := drivers/bus/softspi.c

SHARED_C := \
	shared/readline/readline.c \
	shared/runtime/gchelper_generic.c \
	shared/runtime/interrupt_char.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c \
	shared/runtime/sys_stdio_mphal.c \
	shared/timeutils/timeutils.c

PORT_C := $(wildcard $(PORT_DIR)/*.c)

SRC_QSTR += $(EXTMOD_C) $(DRIVERS_C) $(SHARED_C) $(PORT_C) $(EXT_C)

GENHDR_OUTPUT := $(addprefix $(HEADER_BUILD)/, \
	moduledefs.h \
	mpversion.h \
	qstrdefs.generated.h \
	root_pointers.h \
	)

# Frozen modules: mpy-cross (built from the checkout) compiles them, and
# makemanifest.py writes them as C, with their own extra qstr pool.
MPY_CROSS := $(TOP)/mpy-cross/build/mpy-cross
FROZEN_C := $(BUILD)/frozen_content.c

$(MPY_CROSS):
	$(MAKE) -C $(TOP)/mpy-cross

$(FROZEN_C): $(MANIFEST) $(GENHDR_OUTPUT) $(MPY_CROSS)
	$(ECHO) "GEN $@"
	$(Q)MICROPY_MPYCROSS=$(MPY_CROSS) $(MAKE_MANIFEST) -o $@ -v "MPY_DIR=$(TOP)" -v "MPY_LIB_DIR=$(TOP)/lib/micropython-lib" -v "PORT_DIR=$(PORT_DIR)" \
		-v "TDSH_PY_DIR=$(PORT_DIR)" $(foreach v,$(MANIFEST_VARS),-v "$(v)") -b "$(BUILD)" --mpy-tool-flags="-mlongint-impl=mpz" $(MANIFEST)

.PHONY: all generated interpreter
all: generated
ifeq ($(INTERPRETER),1)
all: interpreter
endif

# The configuration's headers and frozen modules (OUT/genhdr, OUT/frozen).
generated: $(GENHDR_OUTPUT) $(FROZEN_C)
	$(ECHO) "Generated into $(OUT)"
	$(Q)$(RM) -rf $(OUT)/genhdr $(OUT)/frozen
	$(Q)$(MKDIR) -p $(OUT)/genhdr $(OUT)/frozen
	$(Q)$(CP) $(GENHDR_OUTPUT) $(OUT)/genhdr
	$(Q)$(CP) $(FROZEN_C) $(OUT)/frozen

# The interpreter's own sources. README.md (written by hand) stays.
interpreter:
	$(ECHO) "Package into $(PACKAGE_DIR)"
	$(Q)$(RM) -rf $(PACKAGE_DIR)/py $(PACKAGE_DIR)/extmod $(PACKAGE_DIR)/shared $(PACKAGE_DIR)/lib $(PACKAGE_DIR)/drivers
	$(Q)$(MKDIR) -p $(PACKAGE_DIR)/py $(PACKAGE_DIR)/extmod \
		$(PACKAGE_DIR)/shared/readline $(PACKAGE_DIR)/shared/runtime $(PACKAGE_DIR)/shared/timeutils \
		$(PACKAGE_DIR)/lib/re1.5 $(PACKAGE_DIR)/lib/crypto-algorithms $(PACKAGE_DIR)/drivers/bus
	$(Q)$(CP) $(TOP)/py/*.[ch] $(PACKAGE_DIR)/py
	$(Q)$(CP) $(addprefix $(TOP)/,$(EXTMOD_C)) $(TOP)/extmod/*.h $(PACKAGE_DIR)/extmod
	$(Q)$(CP) $(addprefix $(TOP)/,$(DRIVERS_C)) $(TOP)/drivers/bus/spi.h $(PACKAGE_DIR)/drivers/bus
	$(Q)$(CP) $(TOP)/shared/readline/readline.[ch] $(PACKAGE_DIR)/shared/readline
	$(Q)$(CP) $(addprefix $(TOP)/,$(filter shared/runtime/%,$(SHARED_C))) \
		$(TOP)/shared/runtime/gchelper.h $(TOP)/shared/runtime/interrupt_char.h \
		$(TOP)/shared/runtime/pyexec.h $(TOP)/shared/runtime/mpirq.h $(PACKAGE_DIR)/shared/runtime
	$(Q)$(CP) $(TOP)/shared/timeutils/timeutils.[ch] $(PACKAGE_DIR)/shared/timeutils
	$(Q)$(CP) $(TOP)/lib/re1.5/*.[ch] $(PACKAGE_DIR)/lib/re1.5
	$(Q)$(CP) $(TOP)/lib/crypto-algorithms/sha256.[ch] $(PACKAGE_DIR)/lib/crypto-algorithms
	$(Q)$(CP) $(TOP)/LICENSE $(PACKAGE_DIR)/LICENSE
	$(Q)cd $(PACKAGE_DIR) && { \
		echo "# Generated by tools/micropython: the MicroPython interpreter TinyDesk Shell builds."; \
		echo "# lib/re1.5 and lib/crypto-algorithms are #included by extmod/modre.c"; \
		echo "# and extmod/modhashlib.c, not built on their own. The generated headers"; \
		echo "# and frozen modules are not here: python/gen (the shell's) or an"; \
		echo "# application's own, see python/README.md."; \
		echo "set(TDSH_MICROPYTHON_SRCS"; \
		find py extmod shared drivers -name '*.c' | LC_ALL=C sort | sed 's|^|    $${TDSH_MICROPYTHON_DIR}/|'; \
		echo ")"; \
	} > sources.cmake

include $(TOP)/py/mkrules.mk
