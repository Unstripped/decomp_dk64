# audioCheckAiLength (global, src/global/6710.c)

## Sites
global:80602104:other:c2f866 other: `s32 zero = 0` index on D_807454E8[zero] (Q0099) kept a separate lui/%lo pair per access (t7 for the load at 0x70c/0x710, at for the store at 0x714/0x720) instead of &D_807454E8 coloured $v0. FIXED.

## Attempts
2026-11-10 Rev10F anthropic/claude-opus-5-5:xhigh: review/plain/diagnose/permute; best=0 only via pointer temp for the read with a direct store (rejected).
2026-11-12 Rev19B anthropic/claude-opus-5-5:low: permute: char new_var do-while store loop (worse hack).
2026-11-15 HackaudioCheckAiLength anthropic/claude-opus-5-5:high: D_807454E8[2] -> function-local `static s32 sAiIdleFlag = 1;`, zero local and index removed -> fdiff exit 3 TEXT OK + RELOC-EQUIV; fdiff --reloc-ok exit 0 (whole object); clint uninit 0.

## Untried ideas
none left (site fixed).

## Evidence
- Target 0x70c lui t7 / 0x710 lw t7,0(t7) / 0x714 lui at / 0x720 sw zero,0(at): HI16/LO16 against D_807454E8, offset 0 only.
- No reference to D_807454E8+4 anywhere: grep of asm/, src/, include/, symbol_addrs*.txt; build/global.map only defines D_807454E8 at 0x807454e8.
- 6710.c `.data 0x807452C0-0x807454F0`: D_807454E8 is the last object (.data+0x228); expected .data size 0x230, align 16.
- Stand-in object: .data size 0x230, bytes identical (0x228 = 1, 0x22c = 0 from section padding); .bss 0x30a0 unchanged; text words equal except LO16 addend 0x228 against `.data` vs 0 against D_807454E8 (same final address).
- Quirks: Q0922, Q0761 (function-local static = native S var, lui/%lo pair per access), Q0838/Q0947 (statics emitted after file-scope objects), Q0099 (old FAKE).
