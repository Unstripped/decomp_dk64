# dmaReadAssetDecompress (global), src/global/FE40.c

## Sites
- global:8060B140:other:2e1167 other: `(decompressFlag1 & 0xFF) & 0x80` line 24. The redundant mask makes ugen emit `and $8,$25,255` (rec 19), which as1 deletes by renaming the `lbu` onto `$8`. That shifts the line-24/25/27 temps to t0/t1/t2/t4 and the `dmaBuf = dst` else-arm load to t7.
- global:8060B140:warning:0b7e03 / 0b7e03#2: W709 lines 62/65, `&dst` (void **) passed as u8 ** to gunzip.
- global:8060B140:warning:0b7e03#3 / #4: removed (dmaBuf is now u8 *).

## Attempts
- 2026-11-14 U HackdmaReadAssetDecompress anthropic/claude-opus-5-5: sweep plain/recipe nohit (no rewrite/removal).
- same: hand removal `decompressFlag1 & 0x80`: fdiff 1, 8 regalloc lines (lbu t9/andi t0/lw t1,t3; else-arm lw t6). variants scan around it: best full=32, no zero.
- same: `(s8)flag1 < 0`, `(u8)flag1 & 0x80`, `(flag1 & 0x80) != 0`, `0x80U`, `(u8)0x80`, `(s32)flag1`, `(s32)(u8)flag1`, `flag1 >> 7`, `== 0x80`: all fdiff 1.
- same: `u8 flags = decompressFlag1;` / `u8 useScratch = decompressFlag1 & 0x80;` local: frame 0x68 -> 0x70, fdiff 1.
- same: `(u8)(decompressFlag1 & 0x80)`: fdiff 0, but it is the same redundant mask in another spelling; not applied (copy c4/).
- same: dmaBuf/dstStart/ptr retyped `u8 *`: fdiff 0, removes 2 of 4 W709.
- same: `u8 *out` cursor local, `void *dst` kept (tA/): fdiff 1, because the target passes `&dst` (home slot sp+0x6c) and the local lands at sp+0x58.
- same: param `u8 *dst` (tB/, PROTO_SKIP + declaration): fdiff 0, but the callers gain W709: 5A50.c 74/81/120/123 (ALBankFile *, &D_8076D200 s32) and 6AD90.c 1090/2029/2242/2277/2280 (CollisionStaticTri *, &header u64, D_807F9520, D_807F9528[]). That is net +7, so it was rejected.

## Untried ideas
- A natural C source of the extra `and 255` that does not grow the frame. No candidate is known (a u8 local costs 8 bytes of frame).
- Retyping caller storage so it matches `u8 *dst`. The caller types (ALBankFile, u64 header, s32 table) look real, so this is unlikely.

## Evidence
- Target 0x48 `lbu t0,0x77(sp)`, 0x54 `andi t1,t0,0x80`, 0x3c `lw t7,0x6c(sp)`. Gunzip/inflate calls at 0x204/0x218/0x23c/0x254 use `addiu a1,sp,0x6c`. 0x294 `lw t4,0x6c(sp)` / 0x29c `lw t5,0x58(sp)`, `subu t6,t4,t5`.
