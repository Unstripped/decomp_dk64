# screenWipeStart (global, src/global/2DE90.c)
## Sites
global:806291B4:other:a8594a other (FIXED 2026-11-17 CleanscreenBlurApply): `s32 sel = type;` an int copy of the K&R u8 param standing in for the real cause: `extern u8 sScreenWipeType` was the wrong width. With `extern s8 sScreenWipeType;` the plain body (switch (type), sScreenWipeType = type) matches: sp+0x18 is the cfe switch temp, stored at 0x54 and reloaded for the jump table (0xb0) and for sb sScreenWipeType (0x154).
## Attempts
2026-11-11 r17 CleanGlobal2DE90 opus-5-5:low: switch on type without the copy (permute best not 0); diagnose: sel uncoloured word home
2026-11-11 r17 Rev17L opus-5-5:low: plain sweep, no rewrite
2026-11-14 HackscreenWipeStart opus-5-5:high: copy removed, u8 K&R param (switch temp sp+24 is fed by lbu 35(sp), no andi) 40; s32 / u32 K&R param 8 (no andi, frame 24); (s32)type selector 40; s32 param with (u8)type / & 0xFF in the compare, switch and store 37-40; s32 param reassigned type = (u8)type 18; ANSI void screenWipeStart(u8 type) with the copy fdiff 0 (stand-in), without it fdiff 1
2026-11-17 CleanscreenBlurApply anthropic/claude-opus-5-5: frame/slot measurement: copy removed keeps frame 32 (sp+0x18 = cfe switch temp, store reads lbu 35(sp)) -> 40; block-scope `s32 wipeType = type;` inside the outer if 6 (frame 40, home sp+0x1c); sel assigned just before the switch 6 (frame 40); sel == 7 in the entry test 0; width scan sel u32/s8/s16 10, u8/u16 45, type u16 1. Permuter 900 s (hack-free weights) from the copy-removed body: base 995, two zeros at 2.5 and 13.5 min, both retyping `extern u8 sScreenWipeType` to `char` -> rewritten `extern s8 sScreenWipeType;`, copy removed: whole-object fdiff 0.
## Untried ideas
none open: no hack site left.
## Evidence
0x30 sw a0,32(sp) (param home), 0x34 andi t6,a0,0xff, 0x38 move a0,t6, 0x48 bnel t6,at (== 7), 0x54 sw a0,24(sp) (switch temp), 0xb0 lw t4,24(sp) (jump table), 0x154 lw t7,24(sp) / sb sScreenWipeType (0x807F5D85). screenWipeDraw reads it with lbu t6 at 0x3ec under both u8 and s8 externs. sScreenWipeActive (s8, lb at 0x28) is its neighbour byte. Without the s8 global (u8 extern, no copy; probe build at 0): no andi, == 7 reads lbu t6,35(sp) at 0x18, switch temp sw t7,24(sp) from lbu t7,35(sp) at 0x28/0x34, store reads lbu t8,35(sp) at 0x130.
