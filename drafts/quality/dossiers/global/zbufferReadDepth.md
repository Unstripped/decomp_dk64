# zbufferReadDepth (global, src/global/103AB0.c)
## Sites
global:80700AE4:other:0f0b91 other: `tablePtr = &table;` pointer temp; kept the element address in t1 (addu t1,t2,t6 at 0x1e14) and the sum in t0 (addu t0,t4,t5 at 0x1e2c). REMOVED 2026-11-17.
global:80700AE4:other:a3ca04 other: seven no-op `& 0xFFFF` on `(z >> 13)` advanced the ugen temp ring so the exponent lands sra t5 / andi t4 / sll t6 (0x1e08-0x1e10). REMOVED 2026-11-17.
## Attempts
2026-11-09..2026-11-13 (rounds 3, 10, 16, 17, 20, 26, 34, 36; Clean103AB0, Rev10F, Rev16K, Rev17L, CleanGlobal103AB0, Rev26B): flat `s32 words[16]` view only: table.words direct (text 5, t0/t1 swap at 0x1e14..0x1e30), entry = table.words + ..., (z>>13)&7 without masks (sra t9), *2 / <<1 / &tablePtr->words[]; permuter 600-900 s on single `& 7` mask: no output below 10; uopt_trace + as1probe keep: no natural flat shape.
2026-11-17 2026-11-17: cleanup CleanzbufferReadDepth CleanzbufferReadDepth anthropic/claude-opus-5-5: file-local `ZbufferDecodeTable` retyped to `ZbufferDecodeEntry entries[8]` ({s32 shift; s32 offset;}), `u16 exponent = (z >> 13) & 7`, `u16 mantissa = (z >> 2) & 0x7FF`, `u32 result = (mantissa << table.entries[exponent].shift) + table.entries[exponent].offset; return result >> 3;` -> fdiff exit 0, both sites removed.
  Measured on the way (variants.py try, full score): flat view + s32 exponent local + no entry pointer 2 (sra t9 only); flat + u16 exponent 11 (words[e*2]) / 14 (e<<1); flat + 0..8 masks on the exponent local: only 7 masks = 0 (1-6 rotate every temp); typed entries[] with s32/u32 exponent 12, s16 4-14, u16/u8 0; any `entry` pointer local 5+; `s32 pairs[8][2]` view behaves like entries[] (u16 exponent 0).
## Untried ideas
none open (function hack-free).
## Evidence
Target 0x1e04-0x1e30: lhu a2,0(v1); sra t5,a2,0xd; andi t4,t5,0x7; sll t6,t4,0x3; addu t1,t2,t6; lw t9,0(t1); lw t4,4(t1); sra t7,a2,0x2; andi t8,t7,0x7ff; sllv t5,t8,t9; addu t0,t4,t5; srl v0,t0,0x3.
The `sll t6,t4,0x3` is one ugen `mul $14,$12,8` for an 8-byte record stride; the flat `words[e*2]` view emits `mul 2` + `mul 4` (one more ring temp). The u16 exponent local's narrowing emits `and $12,$13,0xFFFF` after the `& 7`, which as1 deletes (Q0374), putting the sra/andi in t5/t4.
Table: D_80754BC4 (64 bytes at 0x80754BC4) = 8 pairs (shift, offset): (6,0) (5,0x20000) (4,0x30000) (3,0x38000) (2,0x3C000) (1,0x3E000) (0,0x3F000) (0,0x3F800): the N64 16-bit z-buffer exponent/mantissa decode table.
