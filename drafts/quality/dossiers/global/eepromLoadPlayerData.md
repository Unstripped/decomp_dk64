# eepromLoadPlayerData (global, src/global/104F0.c)
## Sites
global:8060DC3C:other:c3c889 other -> ORIG: eepromClearSlotData(slot & 0xFF, 0) - the target executes andi a0,s5,0xff at 0x24e0 on the already narrowed slot (andi s5,a0,0xff at 0x2470); the callee is K&R and unprototyped, so only a source mask produces it
## Attempts
2026-11-10..12: plain (move a0,s5), permutes (same mask back)
2026-11-14 HackeepromClearSlotData: ANSI u8 callee (changes eepromSetCurrentSlot and eepromValidateSaveSlots), (u8)/(s32) casts (no code), s32/u32/int slot parameter with (u8)slot (entry andi lost); classified ORIG
## Evidence
eepromSetCurrentSlot passes its u32 slot with move a0,t6 at 0x1058 (no narrowing at an unprototyped call); eepromValidateSaveSlots' (u8)i & 0xFF calls emit two andi (0x14ec/0x14f4, 0x1630).
