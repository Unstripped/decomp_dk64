# Run inside the toolchain container: tools/dk make [target]

VERSION   := us
BASEROM   ?= donkey-kong.n64
TARGET    := dk64.$(VERSION)
BUILD_DIR := build

CROSS   := mips-linux-gnu-
AS      := $(CROSS)as
LD      := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy
PYTHON  := python3
SPLAT   := $(PYTHON) -m splat split
CC      := /opt/ido5.3/cc
ASM_PROC := $(PYTHON) /opt/asm-processor/build.py

SPLAT_YAML := $(TARGET).yaml
LD_SCRIPT  := $(BUILD_DIR)/$(TARGET).ld
ELF        := $(BUILD_DIR)/$(TARGET).elf
ROM        := $(BUILD_DIR)/$(TARGET).z64

ASFLAGS := -EB -march=vr4300 -mabi=32 -mgp32 -mfp32 -I include
# IDO 5.3 flags used by the original build (-O2 -mips2 -G 0, libultra 2.0L).
OPT_FLAGS := -O2
MIPSBIT   := -mips2
CFLAGS    := -c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -signed -woff 649,654,838,807 \
             -I include -D_FINALROM -DF3DEX_GBI_2 -DTARGET_N64
LDFLAGS := -T $(LD_SCRIPT) -Map $(ELF:.elf=.map) --no-check-sections --accept-unknown-input-arch \
           -T $(BUILD_DIR)/undefined_syms_auto.$(VERSION).txt \
           -T $(BUILD_DIR)/undefined_funcs_auto.$(VERSION).txt \
           -T undefined_syms.$(VERSION).txt
S_FILES   := $(shell find asm -name '*.s' -not -path 'asm/nonmatchings/*' 2>/dev/null)
C_FILES   := $(shell find src -name '*.c' 2>/dev/null)
BIN_FILES := $(shell find assets -name '*.bin' 2>/dev/null)
O_FILES   := $(S_FILES:%.s=$(BUILD_DIR)/%.o) $(C_FILES:%.c=$(BUILD_DIR)/%.o) $(BIN_FILES:%.bin=$(BUILD_DIR)/%.o)

.PHONY: all setup extract split check clean distclean
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:

all: check

# One-time: verify + convert the user ROM, write per-segment binaries, then split.
setup: extract split

extract:
	$(PYTHON) tools/extract.py $(BASEROM)

split:
	rm -rf asm assets $(LD_SCRIPT)
	$(SPLAT) $(SPLAT_YAML)

check: $(ROM)
	@sha1sum -c $(TARGET).sha1

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

# asm-processor splices INCLUDE_ASM'd functions into IDO's output.
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(ASM_PROC) --asm-prelude /opt/asm-processor/prelude.inc $(CC) -- $(AS) $(ASFLAGS) -- $(CFLAGS) $(OPT_FLAGS) $(MIPSBIT) -o $@ $<

$(BUILD_DIR)/%.o: %.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<

$(ELF): $(O_FILES) $(LD_SCRIPT)
	$(LD) $(LDFLAGS) -o $@

$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR)/asm $(BUILD_DIR)/assets $(BUILD_DIR)/src $(ELF) $(ROM)

distclean:
	rm -rf $(BUILD_DIR) asm assets bin baserom.$(VERSION).z64
