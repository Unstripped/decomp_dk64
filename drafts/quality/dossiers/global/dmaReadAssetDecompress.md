# dmaReadAssetDecompress (global), src/global/FE40.c

## Sites
- global:8060B140:other:2e1167 other: FIXED 2026-11-16 (HackdmaReadAssetDecompress2). Was `(decompressFlag1 & 0xFF) & 0x80` line 24, whose redundant mask made ugen emit `and $8,$25,255` (rec 19). as1 deleted that and renamed the `lbu` onto `$8`, which shifted the later ring temps. Now `u8 useScratch = decompressFlag1 & 0x80; if (useScratch)` gives the same record, and `size` was dropped to make room for its home.
- global:8060B140:warning:0b7e03 / 0b7e03#2: W709 lines 61/64, `&dst` (void **) passed as u8 ** to gunzip. Still open (EXHAUSTED).
- global:8060B140:warning:0b7e03#3 / #4: removed (dmaBuf is now u8 *).

## Attempts
- 2026-11-14 U HackdmaReadAssetDecompress anthropic/claude-opus-5-5: sweep plain/recipe nohit (no rewrite/removal).
- same: hand removal `decompressFlag1 & 0x80`: fdiff 1, 8 regalloc lines (lbu t9/andi t0/lw t1,t3; else-arm lw t6). A variants scan around it: best full=32, no zero.
- same: `(s8)flag1 < 0`, `(u8)flag1 & 0x80`, `(flag1 & 0x80) != 0`, `0x80U`, `(u8)0x80`, `(s32)flag1`, `(s32)(u8)flag1`, `flag1 >> 7`, `== 0x80`: all fdiff 1.
- same: `u8 flags = decompressFlag1;` / `u8 useScratch = decompressFlag1 & 0x80;` local: frame 0x68 -> 0x70, fdiff 1.
- same: `(u8)(decompressFlag1 & 0x80)`: fdiff 0, but it is the same redundant mask in another spelling. Not applied.
- same: dmaBuf/dstStart/ptr retyped `u8 *`: fdiff 0, removes 2 of 4 W709.
- same: `u8 *out` cursor local, `void *dst` kept: fdiff 1. The target passes `&dst` (home slot sp+0x6c), and the local lands at sp+0x58.
- same: param `u8 *dst` (PROTO_SKIP + declaration): fdiff 0, but the callers gain W709 (5A50.c x4, 6AD90.c x5), net +7. Rejected.
- 2026-11-16 U HackdmaReadAssetDecompress2 anthropic/claude-opus-5-5:high: more bit-test spellings, all fdiff 1 (full=63 unless noted): `(u32)`/`(u16)`/`(s16)` casts, `!!`, `!(..==0)`, `> 0`, `1 << 7`, `0x80 & flag1`, ternary (69), `>= 0x80`/`> 0x7F` (65, sltiu), `/ 128` (66). `(flag1 >> 7) & 1` and `(u8)(flag1 >> 7)` have the right ring but emit sra/andi 1 (3 lines). `% 256` gives 6 lines.
- same: `u8 flags = decompressFlag1` (declared first or last) is copy-propagated, so it emits no `and 255` (frame 0x70).
- same: frame accounting. cfe Mmt 32 (7 named homes plus the switch selector temp at -32 = 0x48). uopt Mmt 40: 0x40/0x44 are 2 temp words with no code. In the target, 0x60 (size) and 0x64 (count) are never accessed. A `u8 useScratch = decompressFlag1 & 0x80` result local gives the exact ring (s32: fdiff 1), but it needs a home word.
- same: FIXED. Dropped `size` (the loop test and rem read `*sizePtr`, which the target reloads every iteration anyway) and declared `u8 useScratch` in its place (2nd): fdiff 0, uninit 0 (only the pre-existing allocBuf). Dropping `rem` (written inline twice) instead also gives fdiff 0. useScratch declared last: fdiff 1 (it shifts the dmaBuf home).
- same: `for (count = 0, ptr = dmaBuf; ...; count++)` replaces the LAYOUT join with fdiff 0 (alt copy). Not applied, because the ladder counts comma expressions as non-ordinary C. The `ptr = dmaBuf;` + `for (count = 0; ...)` and separate-line while forms are fdiff 1.

## Untried ideas
- W709: none that is a real type. gunzip's `u8 **` matches all 6 other callers (1630 x2, main, 450, 6AD90 x2, 70FD0 all hold u8 *). dst must stay void * (callers pass ALBankFile *, &s32, &u64, CollisionStaticTri *). The target passes dst's own home (0x204 `addiu a1,sp,0x6c`), so a cursor local cannot replace it.

## Evidence
- Target 0x48 `lbu t0,0x77(sp)`, 0x54 `andi t1,t0,0x80`, 0x3c `lw t7,0x6c(sp)`. Gunzip/inflate calls at 0x204/0x218/0x23c/0x254 use `addiu a1,sp,0x6c`. 0x294 `lw t4,0x6c(sp)` / 0x29c `lw t5,0x58(sp)`, `subu t6,t4,t5`.
- Frame 0x68: saves 0x28-0x3c; homes count 0x64, size->useScratch 0x60, dmaBuf 0x5c, dstStart 0x58, rem 0x54, allocBuf 0x50, ptr 0x4c; switch temp 0x48; uopt temps 0x40/0x44 have no code.
- Loop 0x114/0x120: `lw t2,0x70(sp); lw v1,0(t2)` reloads *sizePtr after each osRecvMesg. 0x148 `subu v0,v1,t3` reuses that load for rem.
