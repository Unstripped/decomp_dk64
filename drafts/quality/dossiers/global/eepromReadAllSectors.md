# eepromReadAllSectors (global, src/global/104F0.c)
## Sites
none (no hack site)
## Attempts
2026-11-21 continue unit 1 Hack104F0 anthropic/claude-opus-5-5: dropped the `(u8)` cast on the osEepromRead address argument: the prototype `s32 osEepromRead(OSMesgQueue *, u8, u8 *)` (include/PR/os_eeprom.h) narrows `sector` itself; variants try 0, whole object fdiff 0. Applied.
## Untried ideas
none
## Evidence
none needed (identical object)
