# eepromGetSectionBuffer (global, src/global/104F0.c)
## Sites
none (no hack site; a908ec removed 2026-11-10)
## Attempts
2026-11-21 continue unit 1 Hack104F0 anthropic/claude-opus-5-5: pointer-sum spellings: case 1 base-first 0, case 0 offset-first 0, both `&sEepromSlotBuffer[...]` 0 (variants try); applied case 1 base-first so both cases read `sEepromSlotBuffer + offset`; whole object fdiff 0.
## Untried ideas
none
## Evidence
0x2b5c and 0x2ba8 `addu v1,t8,t9` (t8 = offset, t9 = &sEepromSlotBuffer): cfe emits the offset-first addu from either source order here, unlike the eepromSaveRecords sprintf (0x1b84) and eepromValidateSaveSlots `data` (0x14b8) sums where only offset-first matches.
