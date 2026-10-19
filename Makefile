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
BOOT_BIN   := $(BUILD_DIR)/boot.bin

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
GLOBAL_GZ         := $(BUILD_DIR)/global.gz

# Overlays (all at VRAM 0x80024000): name, segment-table stream id in bin/segments/, inflated text size.
OVERLAYS := multiplayer minecart bonus race critter boss arcade jetpac menu

multiplayer_SEG := ovl02
minecart_SEG    := ovl03
bonus_SEG       := ovl04
race_SEG        := ovl05
critter_SEG     := ovl06
boss_SEG        := ovl07
arcade_SEG      := ovl08
jetpac_SEG      := ovl09
menu_SEG        := ovl10

multiplayer_TEXT_SIZE := 12144
minecart_TEXT_SIZE    := 19344
bonus_TEXT_SIZE       := 39008
race_TEXT_SIZE        := 47888
critter_TEXT_SIZE     := 22512
boss_TEXT_SIZE        := 71856
arcade_TEXT_SIZE      := 57888
jetpac_TEXT_SIZE      := 28816
menu_TEXT_SIZE        := 61264

# Compressed segment ROM sizes (gzip text + data members, zero-padded).
GLOBAL_ROM_SIZE      := 0xBAA80
multiplayer_ROM_SIZE := 0x2000
minecart_ROM_SIZE    := 0x2F40
bonus_ROM_SIZE       := 0x5BC0
race_ROM_SIZE        := 0x7180
critter_ROM_SIZE     := 0x3930
boss_ROM_SIZE        := 0xA0F0
arcade_ROM_SIZE      := 0x9150
jetpac_ROM_SIZE      := 0x4750
menu_ROM_SIZE        := 0x8C90

# Compressed segments in ROM order (global + 9 overlays).
ROM_SEGMENTS := global menu multiplayer minecart bonus race critter boss arcade jetpac
ROM_GZ       := $(ROM_SEGMENTS:%=$(BUILD_DIR)/%.gz)

# Uncompressed ROM tail: table-12 raw data, then assets (written by tools/extract.py).
RAW_TAIL := bin/segments/table12.bin bin/segments/assets.bin

ASFLAGS := -EB -march=vr4300 -mabi=32 -mgp32 -mfp32 -I include
# IDO 5.3 flags used by the original build (-O2 -mips2 -G 0, libultra 2.0L).
OPT_FLAGS := -O2
MIPSBIT   := -mips2
CFLAGS    := -c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -signed -woff 649,654,838,807 \
             -I include -D_FINALROM -DF3DEX_GBI_2 -DTARGET_N64 -D_MIPS_SZLONG=32

# libultra 2.0J C sources live at src/<segment>/libultra/<ultralib dir>/<file>.c and
# take decompals/ultralib's flags for TARGET=libultra_rom VERSION=J (makefiles/ido.mk):
# Directory defaults:
#   os/: -O1 -mips2
#   gu/, mgu/: -O3 -mips2 (sinf.c, cosf.c: -O2)
#   libc/: -O3 -mips2 (ll, llbit, llcvt: -O1 -mips3 -32)
#   io/: -O2 -mips2, with -O1 overrides for routines matched at -O1
LIBULTRA_CFLAGS := -DNDEBUG -DBUILD_VERSION=VERSION_J -DBUILD_VERSION_STRING=\"2.0J\" \
                   -I include/compiler/ido -I include/PR -I include/libultra
LIBULTRA_SEGMENTS := boot global

# io/ routines that DK64 compiles with -O1 instead of directory default -O2
LIBULTRA_IO_O1 := ai aisetnextbuf devmgr pidma pigetcmdq pirawdma pirawread piread \
                  controller conteeplongread contsetch pfsisplug \
                  si siacs sirawread sirawwrite sp sprawdma spsetpc sptask sptaskyielded \
                  viblack vi vigetcurrframebuf vigetmode vigetnextframebuf visetevent visetmode visetspecial viswapbuf

define LIBULTRA_FLAGS
$(BUILD_DIR)/src/$(1)/libultra/%.o: CFLAGS += $(LIBULTRA_CFLAGS)
$(foreach dir,os debug host rmon log,$(BUILD_DIR)/src/$(1)/libultra/$(dir)/%.o: OPT_FLAGS := -O1
)
$(foreach dir,gu mgu,$(BUILD_DIR)/src/$(1)/libultra/$(dir)/%.o: OPT_FLAGS := -O3
)
$(foreach f,translate mtxcatl mtxutil normalize sinf cosf,$(BUILD_DIR)/src/$(1)/libultra/gu/$(f).o: OPT_FLAGS := -O2
)
$(BUILD_DIR)/src/$(1)/libultra/libc/%.o: OPT_FLAGS := -O3
$(foreach f,ll llbit llcvt,$(BUILD_DIR)/src/$(1)/libultra/libc/$(f).o: OPT_FLAGS := -O1
$(BUILD_DIR)/src/$(1)/libultra/libc/$(f).o: MIPSBIT := -mips3 -32
)
$(BUILD_DIR)/src/$(1)/libultra/os/initialize_isv.o: OPT_FLAGS := -O2
$(foreach f,$(LIBULTRA_IO_O1),$(BUILD_DIR)/src/$(1)/libultra/io/$(f).o: OPT_FLAGS := -O1
)
endef
$(foreach seg,$(LIBULTRA_SEGMENTS),$(eval $(call LIBULTRA_FLAGS,$(seg))))

LDFLAGS := -T $(LD_SCRIPT) -Map $(ELF:.elf=.map) --no-check-sections --accept-unknown-input-arch --no-warn-mismatch \
           -T $(BUILD_DIR)/undefined_syms_auto.$(VERSION).txt \
           -T $(BUILD_DIR)/undefined_funcs_auto.$(VERSION).txt \
           -T undefined_syms.$(VERSION).txt

GLOBAL_LDFLAGS := -T $(GLOBAL_LD_SCRIPT) -Map $(GLOBAL_ELF:.elf=.map) --no-check-sections --accept-unknown-input-arch \
                  --allow-multiple-definition \
                  -T $(BUILD_DIR)/undefined_syms_auto.global.txt \
                  -T $(BUILD_DIR)/undefined_funcs_auto.global.txt \
                  -T undefined_syms.$(VERSION).txt \
                  --just-symbols=$(ELF)

NON_BOOT_DIRS  := global $(OVERLAYS)
BOOT_S_FILES   := $(shell find asm -name '*.s' -not -path 'asm/nonmatchings/*' $(NON_BOOT_DIRS:%=-not -path 'asm/%/*') 2>/dev/null)
BOOT_C_FILES   := $(shell find src -name '*.c' $(NON_BOOT_DIRS:%=-not -path 'src/%/*') 2>/dev/null)
BIN_FILES      := $(shell find assets -name '*.bin' 2>/dev/null)
O_FILES        := $(BOOT_S_FILES:%.s=$(BUILD_DIR)/%.o) $(BOOT_C_FILES:%.c=$(BUILD_DIR)/%.o) $(BIN_FILES:%.bin=$(BUILD_DIR)/%.o)

GLOBAL_S_FILES := $(shell find asm/global -name '*.s' -not -path 'asm/global/nonmatchings/*' 2>/dev/null)
GLOBAL_C_FILES := $(shell find src/global -name '*.c' 2>/dev/null)
GLOBAL_O_FILES := $(GLOBAL_S_FILES:%.s=$(BUILD_DIR)/%.o) $(GLOBAL_C_FILES:%.c=$(BUILD_DIR)/%.o)

# Suppress o32 odd single-precision FP register warnings in global asm.
$(GLOBAL_O_FILES): ASFLAGS += -W

.PHONY: all setup extract split check progress clean distclean
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:

all: check

# One-time: verify + convert the user ROM, write per-segment binaries, then split.
# split runs in a sub-make: this make's directory cache predates the extracted files.
setup: extract
	$(MAKE) split

extract:
	$(PYTHON) tools/extract.py $(BASEROM)

OVERLAY_BINS       := $(foreach ovl,$(OVERLAYS),bin/segments/$($(ovl)_SEG).bin)
OVERLAY_LD_SCRIPTS := $(OVERLAYS:%=$(BUILD_DIR)/%.ld)

bin/segments/%.bin: bin/segments/%.text.bin bin/segments/%.data.bin
	cat $^ > $@

split: bin/segments/global.bin $(OVERLAY_BINS)
	rm -rf asm assets $(LD_SCRIPT) $(GLOBAL_LD_SCRIPT) $(OVERLAY_LD_SCRIPTS)
	$(SPLAT) $(SPLAT_YAML)
	$(SPLAT) $(GLOBAL_SPLAT_YAML)
	$(foreach ovl,$(OVERLAYS),$(SPLAT) dk64.$(ovl).$(VERSION).yaml &&) true

OVERLAY_TEXT_BINS := $(OVERLAYS:%=$(BUILD_DIR)/%.text.bin)
OVERLAY_DATA_BINS := $(OVERLAYS:%=$(BUILD_DIR)/%.data.bin)
OVERLAY_SHA1S     := $(OVERLAYS:%=dk64.%.$(VERSION).sha1)

check: $(ROM) $(GLOBAL_TEXT_BIN) $(GLOBAL_DATA_BIN) $(OVERLAY_TEXT_BINS) $(OVERLAY_DATA_BINS)
	@sha1sum -c $(GLOBAL_SHA1)
	@$(foreach sha,$(OVERLAY_SHA1S),sha1sum -c $(sha) &&) true
	@sha1sum -c $(TARGET).sha1

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

# asm-processor splices INCLUDE_ASM'd / GLOBAL_ASM'd functions into IDO's output.
C_FILES_WITH_GLOBAL_ASM := $(shell grep -l -E "(GLOBAL_ASM|INCLUDE_ASM)" $(BOOT_C_FILES) $(GLOBAL_C_FILES) 2>/dev/null)
O_FILES_WITH_GLOBAL_ASM := $(C_FILES_WITH_GLOBAL_ASM:%.c=$(BUILD_DIR)/%.o)

$(O_FILES_WITH_GLOBAL_ASM): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(ASM_PROC) $(if $(filter -O1,$(OPT_FLAGS)),-O1,-O2) --asm-prelude include/asm_prelude.inc $(CC) -- $(AS) $(ASFLAGS) -- $(CFLAGS) $(OPT_FLAGS) $(MIPSBIT) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OPT_FLAGS) $(MIPSBIT) -o $@ $<
$(BUILD_DIR)/%.o: %.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<

$(ELF): $(O_FILES) $(LD_SCRIPT)
	$(LD) $(LDFLAGS) -o $@

$(BOOT_BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@
	@test $$(stat -c %s $@) -eq 70640 || { echo "$@ size mismatch: expected 0x113F0 (70640), got $$(stat -c %s $@)"; exit 1; }

$(GLOBAL_GZ): $(GLOBAL_TEXT_BIN) $(GLOBAL_DATA_BIN) tools/compress.py
	$(PYTHON) tools/compress.py --size $(GLOBAL_ROM_SIZE) $@ $(GLOBAL_TEXT_BIN) $(GLOBAL_DATA_BIN)

$(ROM): $(BOOT_BIN) $(ROM_GZ) $(RAW_TAIL)
	cat $^ > $@
	@test $$(stat -c %s $@) -eq 33554432 || { echo "$@ size mismatch: expected 0x2000000 (33554432), got $$(stat -c %s $@)"; exit 1; }

$(GLOBAL_ELF): $(GLOBAL_O_FILES) $(GLOBAL_LD_SCRIPT) $(ELF)
	$(LD) $(GLOBAL_LDFLAGS) -o $@

$(GLOBAL_BIN): $(GLOBAL_ELF)
	$(OBJCOPY) -O binary $< $@

$(GLOBAL_TEXT_BIN): $(GLOBAL_BIN)
	head -c $(GLOBAL_TEXT_SIZE) $< > $@

$(GLOBAL_DATA_BIN): $(GLOBAL_BIN)
	tail -c +$$(($(GLOBAL_TEXT_SIZE) + 1)) $< > $@

define OVERLAY_RULE
$(1)_S_FILES := $$(shell find asm/$(1) -name '*.s' -not -path 'asm/$(1)/nonmatchings/*' 2>/dev/null)
$(1)_C_FILES := $$(shell find src/$(1) -name '*.c' 2>/dev/null)
$(1)_O_FILES := $$($(1)_S_FILES:%.s=$$(BUILD_DIR)/%.o) $$($(1)_C_FILES:%.c=$$(BUILD_DIR)/%.o)

$$($(1)_O_FILES): ASFLAGS += -W

$$(BUILD_DIR)/$(1).elf: $$($(1)_O_FILES) $$(BUILD_DIR)/$(1).ld $$(GLOBAL_ELF) $$(ELF)
	$$(LD) -T $$(BUILD_DIR)/$(1).ld -Map $$(BUILD_DIR)/$(1).map --no-check-sections --accept-unknown-input-arch \
		--allow-multiple-definition \
		-T $$(BUILD_DIR)/undefined_syms_auto.$(1).txt \
		-T $$(BUILD_DIR)/undefined_funcs_auto.$(1).txt \
		-T undefined_syms.$$(VERSION).txt \
		--just-symbols=$$(GLOBAL_ELF) \
		--just-symbols=$$(ELF) \
		-o $$@

$$(BUILD_DIR)/$(1).bin: $$(BUILD_DIR)/$(1).elf
	$$(OBJCOPY) -O binary $$< $$@

$$(BUILD_DIR)/$(1).text.bin: $$(BUILD_DIR)/$(1).bin
	head -c $$($(1)_TEXT_SIZE) $$< > $$@

$$(BUILD_DIR)/$(1).data.bin: $$(BUILD_DIR)/$(1).bin
	tail -c +$$$$(($$($(1)_TEXT_SIZE) + 1)) $$< > $$@

$$(BUILD_DIR)/$(1).gz: $$(BUILD_DIR)/$(1).text.bin $$(BUILD_DIR)/$(1).data.bin tools/compress.py
	$$(PYTHON) tools/compress.py --size $$($(1)_ROM_SIZE) $$@ $$(BUILD_DIR)/$(1).text.bin $$(BUILD_DIR)/$(1).data.bin
endef

$(foreach ovl,$(OVERLAYS),$(eval $(call OVERLAY_RULE,$(ovl))))

progress: check
	$(PYTHON) tools/progress.py

clean:
	rm -rf $(BUILD_DIR)/asm $(BUILD_DIR)/assets $(BUILD_DIR)/src $(ELF) $(ROM) $(BOOT_BIN) \
	       $(GLOBAL_ELF) $(GLOBAL_BIN) $(GLOBAL_TEXT_BIN) $(GLOBAL_DATA_BIN) $(GLOBAL_GZ) $(BUILD_DIR)/global.map \
	       $(foreach ovl,$(OVERLAYS),$(BUILD_DIR)/$(ovl).elf $(BUILD_DIR)/$(ovl).bin $(BUILD_DIR)/$(ovl).text.bin $(BUILD_DIR)/$(ovl).data.bin $(BUILD_DIR)/$(ovl).gz $(BUILD_DIR)/$(ovl).map)

distclean:
	rm -rf $(BUILD_DIR) asm assets bin baserom.$(VERSION).z64
