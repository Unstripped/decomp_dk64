# eepromGetSectorOffset (global, src/global/104F0.c)
## Sites
none (no hack site)
## Attempts
2026-11-21 continue unit 1 Hack104F0 anthropic/claude-opus-5-5: K&R `unsigned char` formals -> ANSI `void eepromGetSectorOffset(u16 *offset, u8 *width, s32 field, u8 index, u8 subIndex, u8 sector)`: fdiff 0 with the stand-in (`#define PROTO_SKIP_eepromGetSectorOffset` + declaration) and fdiff 0 / cwarn 0 for the stripped copy with the regenerated header shadowed (`.scratch/Hack104F0/shadow/proto/global/104F0.h`, hunk in `header.patch`). Applied.
## Untried ideas
none
## Evidence
Callers are all in this TU (eepromSetField, eepromGetField, eepromReadChecksumBit, eepromWriteChecksumBit) and pass u8-typed values (u8 parameters, eepromGetSectorForSlot's u8 result, eepromGetField's s32 `value` holding that u8); the callee narrows its formals at entry either way (Q0826), so neither side's code changes.
