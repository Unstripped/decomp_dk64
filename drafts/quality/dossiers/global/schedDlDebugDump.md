# schedDlDebugDump (global, src/global/13980.c)

## Sites
global:8060FAE4:other:782b9f (removed): arg spelled `(OSContPad *)((u8 *)&D_807F0564 + 4)` so uopt does not CSE `lda D_807F0568` (arg) with the `.button` read into one saved register; target 0xea0 `lui a0` + `addiu a0,a0,4` and 0xeac `lui v0` / `lhu v0` are separate.
global:8060FAE4:other:484717 (removed): `s32` copy of `.button` keeps the zero-extended `lhu` value in v0 so `buttons |= D_JPAD` is `ori t8,v0,0x400` at 0xed0 (ori/sll fill the load delay of `lb a1` before `beqz a1`).
global:8060FAE4:dead-if:9a3ebd (removed): dead read at the opcode-branch head fixed the as1 order of the three zero moves at 0x11a4 (`move s0,zero` i, `move v1,zero` colorIdx, `bne a0,at`, `move s2,zero` found).
global:8060FAE4:dead-if:44401f (kept): second consumer of the `D_807F05A4` load at 0xf68 makes it a shared ugen node in v0; without it the load takes ring temp t0 and every later ring temp shifts by one.
global:8060FAE4:punned-cast:839be1 + global:8060FAE4:dead-if:fd7de6 (kept, coupled): two `ilod`s of `&sPageAddr` make the 0x1018 load a shared node (`lui v0` / `lw s5,%lo(sPageAddr)(v0)`); a plain read keeps the s5 hint (`lui s5`), score 2.

## Attempts
2026-11-15 U HackschedDlDebugDump2 anthropic/claude-opus-5-5:high: struct {s32; OSContPad} at 0x807F0564 -> IDO 8-aligns the 12-byte record (.bss+0xa8, .bss 0xc0): rejected.
2026-11-15 U HackschedDlDebugDump2 anthropic/claude-opus-5-5:high: 16-byte file-local struct {u32 retraceCount; s32 taskDone; OSContPad pad;} D_807F0560 over 0x807F0560-0x807F0570 -> fdiff --reloc-ok RELOC-EQUIV OK, raw words differ only in LO16 addends (0xc98, 0xea8, 0xeb0); 782b9f retired.
2026-11-15 U HackschedDlDebugDump2 anthropic/claude-opus-5-5:high: OSContPad D_807F0568[1], static D_807F0568, (&x)->button, (OSContPad *)/(void *) casts of the natural arg -> 9-10.
2026-11-15 U HackschedDlDebugDump2 anthropic/claude-opus-5-5:high: frame slot census: ret 0x58, buf 0x64..0x87, done 0x88, mode 0x8c; one 4-byte local must sit between i and ret -> raw renamed held, tag dropped (fdiff 0). Re-read `buttons = D_807F0568.button | D_JPAD` -> 93 (ugen `or $3,$2,1024` writes v1, so as1 cannot hoist ori/sll above `beqz a1`); ternary 126.
2026-11-15 U HackschedDlDebugDump2 anthropic/claude-opus-5-5:high: colorIdx/found init placement matrix (colorIdx 3 x found 4 positions) without the 9a3ebd dead read -> 0 for colorIdx just above `if (mode != 0)` and found just above the for loop (also colorIdx after the RDPPIPESYNC if); 9a3ebd retired.
2026-11-15 U HackschedDlDebugDump2 anthropic/claude-opus-5-5:high: static u32 sPageAddr (casts moved to the read) -> 0 with the ilod pair, 2 with plain reads; seven statics at file scope in .data order -> 145-167.
2026-11-15 U HackschedDlDebugDump2 anthropic/claude-opus-5-5:high: D_807F05A4 as u8 * (15050.c type) -> 0 with 44401f, 79 without; U_JPAD stores swapped 81.
2026-11-15 U HackschedDlDebugDump2 anthropic/claude-opus-5-5:high: reconstruct (struct carve, held, init placement, no dead reads) -> 81; for-init loop forms 81; cur before faultFontInit 177.

## Untried ideas
A natural second consumer of the `D_807F05A4` load inside the U_JPAD block that emits no code (target has only `sw zero,sPageMode` and `sw v0,sPageAddr` there). (this run)
A natural second `ilod` of `&sPageAddr` in the block before the inner loop (`mode = sPageMode; cur = sPageAddr;` then the `done` test). (this run)
Whether the D_807F0560 struct carve lets schedMain drop its own `if (D_807F0560.retraceCount == 0) {}` steer in combination with other edits there (sweep's plain removal: nohit). (this run)

## Evidence
0xea0 `lui a0,%hi(D_807F0564)` / 0xea8 `addiu a0,a0,%lo(D_807F0564)+4`; 0xeac `lui v0` / 0xeb0 `lhu v0,%lo(D_807F0568)(v0)`.
0xebc `sll v1,v0,16` / 0xec0 `sra t6,v1,16` / 0xed0 `ori t8,v0,0x400` / 0xed4 `sll t9,t8,16` before `beqz a1` at 0xed8, `sra v1,t9,16` at 0xee0.
0xf68 `lui v0,%hi(D_807F05A4)` / 0xf6c `lw v0` / 0xf74 `sw zero,sPageMode` / 0xf7c `sw v0,sPageAddr`.
0x1018 `lui v0,%hi(sPageAddr)` / 0x101c `lw s5,%lo(sPageAddr)(v0)` just before `bnez t5` (done test) at 0x1020.
Frame 0xb8: ret 0x58, buf 0x64, done 0x88, mode 0x8c; slots 0x5c/0x60 (i, held) and 0xac (pad) are unused filler slots.

## Lead ruling (Lead5, 2026-11-15)
484717 -> 452b17: `held` is a single-use copy temp (held = ...button; buttons = held;) kept for codegen (lhu v0 for ori at 0xed0, slot between i and ret): a steer per the copy-temp ruling, kept tagged.
