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

GLOBAL_TARGET     := dk64.global.$(VERSION)
GLOBAL_SPLAT_YAML := $(GLOBAL_TARGET).yaml
GLOBAL_LD_SCRIPT  := $(BUILD_DIR)/global.ld
GLOBAL_ELF        := $(BUILD_DIR)/global.elf
GLOBAL_BIN        := $(BUILD_DIR)/global.bin
GLOBAL_TEXT_BIN   := $(BUILD_DIR)/global.text.bin
GLOBAL_DATA_BIN   := $(BUILD_DIR)/global.data.bin
GLOBAL_SHA1       := $(GLOBAL_TARGET).sha1

# Inflated text size of the global code segment (from bin/layout.json).
GLOBAL_TEXT_SIZE  := 1347936

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

GLOBAL_LDFLAGS := -T $(GLOBAL_LD_SCRIPT) -Map $(GLOBAL_ELF:.elf=.map) --no-check-sections --accept-unknown-input-arch \
                  --allow-multiple-definition \
                  -T $(BUILD_DIR)/undefined_syms_auto.global.txt \
                  -T $(BUILD_DIR)/undefined_funcs_auto.global.txt \
                  -T undefined_syms.$(VERSION).txt \
                  --just-symbols=$(ELF)

BOOT_S_FILES   := $(shell find asm -name '*.s' -not -path 'asm/nonmatchings/*' -not -path 'asm/global/*' 2>/dev/null)
BOOT_C_FILES   := $(shell find src -name '*.c' -not -path 'src/global/*' 2>/dev/null)
BIN_FILES      := $(shell find assets -name '*.bin' 2>/dev/null)
O_FILES        := $(BOOT_S_FILES:%.s=$(BUILD_DIR)/%.o) $(BOOT_C_FILES:%.c=$(BUILD_DIR)/%.o) $(BIN_FILES:%.bin=$(BUILD_DIR)/%.o)

GLOBAL_S_FILES := $(shell find asm/global -name '*.s' -not -path 'asm/global/nonmatchings/*' 2>/dev/null)
GLOBAL_C_FILES := $(shell find src/global -name '*.c' 2>/dev/null)
GLOBAL_O_FILES := $(GLOBAL_S_FILES:%.s=$(BUILD_DIR)/%.o) $(GLOBAL_C_FILES:%.c=$(BUILD_DIR)/%.o)

# Suppress o32 odd single-precision FP register warnings in global asm.
$(GLOBAL_O_FILES): ASFLAGS += -W

.PHONY: all setup extract split check clean distclean
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:

all: check

# One-time: verify + convert the user ROM, write per-segment binaries, then split.
setup: extract split

extract:
	$(PYTHON) tools/extract.py $(BASEROM)

bin/segments/global.bin: bin/segments/global.text.bin bin/segments/global.data.bin
	cat $^ > $@

split: bin/segments/global.bin
	rm -rf asm assets $(LD_SCRIPT) $(GLOBAL_LD_SCRIPT)
	$(SPLAT) $(SPLAT_YAML)
	$(SPLAT) $(GLOBAL_SPLAT_YAML)

check: $(ROM) $(GLOBAL_TEXT_BIN) $(GLOBAL_DATA_BIN)
	@sha1sum -c $(TARGET).sha1
	@sha1sum -c $(GLOBAL_SHA1)

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

$(GLOBAL_ELF): $(GLOBAL_O_FILES) $(GLOBAL_LD_SCRIPT) $(ELF)
	$(LD) $(GLOBAL_LDFLAGS) -o $@

$(GLOBAL_BIN): $(GLOBAL_ELF)
	$(OBJCOPY) -O binary $< $@

$(GLOBAL_TEXT_BIN): $(GLOBAL_BIN)
	head -c $(GLOBAL_TEXT_SIZE) $< > $@

$(GLOBAL_DATA_BIN): $(GLOBAL_BIN)
	tail -c +$$(($(GLOBAL_TEXT_SIZE) + 1)) $< > $@

clean:
	rm -rf $(BUILD_DIR)/asm $(BUILD_DIR)/assets $(BUILD_DIR)/src $(ELF) $(ROM) $(GLOBAL_ELF) $(GLOBAL_BIN) $(GLOBAL_TEXT_BIN) $(GLOBAL_DATA_BIN) $(BUILD_DIR)/global.map

distclean:
	rm -rf $(BUILD_DIR) asm assets bin baserom.$(VERSION).z64
