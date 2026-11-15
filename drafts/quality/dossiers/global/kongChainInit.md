# kongChainInit (global, src/global/CC800.c)

## Sites
global:806C8220:dead-store:2d8cdb  dead-store `count = 1;` (statement between tbl8 and tbl11 copies). RETIRED: now the declaration initialiser `s32 count = 1, n = 4;`; it keeps v0=1 at 0x764 before the switch and case 3's own `li v0,1` in the delay slot at 0x810.
global:806C8220:dead-store:313bb1  dead-store `n = 4;`. RETIRED: same initialiser; it keeps v1=4 at 0x768 and offsets=tbl4 (a1=t1) at 0x7d4 before the switch.

## Attempts
2026-11-10..15  rounds 8/16/20 + Hackfunc/PermBatch/Polish/TypesOwner (opus low/high): remove/cond/permute/diagnose all nohit; dead stores kept (see quality.py history).
2026-11-15  HackkongChainInit2  anthropic/claude-opus-5-5:high  declaration-initialiser form (Q0802): every table copy and scalar default as a declaration initialiser, 64-placement grid of (count/n, chain, sign) among tbl8/tbl11/tbl4 -> only `tbl8, tbl11, tbl4, count = 1, n = 4, chain = chains, sign = 1.0f` gives fdiff 0 (a063); separate `s32 count = 1; s32 n = 4;` also 0, reversed n/count 13.
2026-11-15  HackkongChainInit2  load-bearing checks (Q0784, compile without the store): no count/n init 23; n only 23; count only 18.
2026-11-15  HackkongChainInit2  live-default forms: case 2 offsets only (count/n from the inits), 64-placement grid -> best 4 (o027: tbl8, count/n, tbl11, chain, tbl4, sign; count/n stack slots move tbl11 to sp+0x40 / tbl4 to sp+0x2C, and case 3's `count = 1` vanishes from the 0x810 delay slot). Case 2 empty + `offsets = tbl4.offsetX` initialiser, 64 placements -> best 27.
2026-11-15  HackkongChainInit2  recipe scan on the result: swap/float(1.0f, 128.0f)/width(count s8/s16) zeros are neutral spellings; springX `0.0` -> `0.0f` gives 9 (kept, ordinary double literal).

## Untried ideas
none recorded for the retired sites; the live-default form (case 2 relying on the initialisers) stays 4 away, the remaining diff being case 3's redundant `count = 1` in the 0x810 delay slot.

## Evidence
Target 0x720 (frame 0x98): tbl8 copy into sp+0x74 (0x724-0x790) interleaved with li t5,2 (0x758), li v0,1 (0x764), li v1,4 (0x768); tbl11 sp+0x48 copy loop (0x798-0x7b8); tbl4 sp+0x38 (0x7dc-0x804) with move a0,a1 (chain, 0x7d0) and move a1,t1 (offsets=tbl4, 0x7d4); lui 0x3f80 sign (0x7f8). Switch: beq kind,2 -> 0x840 (case 2 has no code), case 3 li v0,1 delay slot 0x810 / li v1,11 0x828 / move a1,t0; case 5 li v0,2 0x81c / li v1,8 / move a1,a3; default b 0xa04.
