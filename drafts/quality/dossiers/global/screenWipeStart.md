# screenWipeStart (global, src/global/2DE90.c)
## Sites
global:806291B4:other:a8594a other: `s32 sel = type;` an int local holding the narrowed K&R u8 param; it is the word home sp+0x18 the target stores at 0x54 (sw a0,24(sp) after andi t6,a0,0xff / move a0,t6 at 0x34/0x38) and reloads for the jump-table index (lw t4,24(sp) at 0xb0) and for D_807F5D85 (lw t7,24(sp) at 0x154)
## Attempts
2026-11-11 r17 CleanGlobal2DE90 opus-5-5:low: switch on type without the copy (permute best not 0); diagnose: sel uncoloured word home
2026-11-11 r17 Rev17L opus-5-5:low: plain sweep, no rewrite
2026-11-14 HackscreenWipeStart opus-5-5:high: copy removed, u8 K&R param (switch temp sp+24 is fed by lbu 35(sp), no andi) 40; s32 / u32 K&R param 8 (no andi, frame 24); (s32)type selector 40; s32 param with (u8)type / & 0xFF in the compare, switch and store 37-40; s32 param reassigned type = (u8)type 18; ANSI void screenWipeStart(u8 type) with the copy fdiff 0 (stand-in), without it fdiff 1
## Untried ideas
none natural: the target needs an int local separate from the parameter home
## Evidence
0x30 sw a0,32(sp) (param home), 0x34 andi t6,a0,0xff, 0x38 move a0,t6, 0x54 sw a0,24(sp), 0xb0 lw t4,24(sp) (jump table), 0x154 lw t7,24(sp) / sb D_807F5D85. uopt -zdbug:5: sel ({1184|0}, -4vreg) is not an active candidate (memory home only).
