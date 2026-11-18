# displayListResolveTextureImages (global, src/global/2F550.c)

## Sites
global:8062F3A0:comma:ee3261 comma: FIXED 2026-11-17. `(w >> 24) == (0, 0xFD)` kept the compare variable-first (bnel t6,s2 at 0x4b7c); the empty statement after the inner if kept end ($s1) coloured before the hoisted 0xFD constant ($s2). Replaced by `opcode = cmd->words.w0 >> 24; if (opcode != G_SETTIMG) continue;`.

## Attempts
2026-11-09..13 (rounds 9-35, see `quality.py history`): plain 0xFD, `0xFD == (w >> 24)`, permuter (best=0 only with op temp + value-named 0xFD local + dead if, or comma + do {} while (0)), uopt_trace colouring diagnoses.
2026-11-17 2026-11-17: cleanup CleandisplayListResolveTextureImages CleandisplayListResolveTextureImages anthropic/claude-opus-5-5: fdiff scores of hand variants (lower is closer):
- plain `== 0xFD`, `;` kept -> 10 (bnel s2,t6 only); comma kept, `;` removed -> 38 (0xFD $s1, end $s2); both removed -> 43
- `opcode = cmd->words.w0 >> 24; if (opcode == G_SETTIMG) {...}` -> 38 (order fixed, colouring wrong); same plus `;` -> 0 (still the `;` steer)
- `w` kept, guard `if ((w >> 24) != G_SETTIMG) continue;` -> 10 (colouring fixed, order flipped)
- `w = w0; op = w >> 24;` + guard -> 10 (copy-propagated back to the expression, constant-first again)
- no local, guard -> 50 (w0 load in t6, not v0); one-case `switch` -> 50; `(u32)G_SETTIMG` -> 43; `while` loop -> 43
- `opcode == G_SETTIMG && SEGMENT_NUMBER(w1) == 0` in one if -> 38; `_SHIFTR(w0, 24, 8)` -> 125 (andi 0xff kept)
- opcode local + top guard continue -> 0 (KEPT, final); opcode + two guards -> 0; opcode if + inner `!= 0` continue -> 0; `s32 opcode` + guard -> 0
- inner test spelled `SEGMENT_NUMBER(cmd->words.w1) == 0` (mbi.h:93, same sll/srl) -> 0

## Untried ideas
none left: no hack sites remain.

## Evidence
Target (expected/build/src/global/2F550.o): `beq a0,a1` guard at 0x4b68; `li s2,253` hoisted at 0x4b70; loop `lw v0,0(s0)` / `srl t6,v0,0x18` / `bnel t6,s2` at 0x4b74-0x4b7c; w1 read once (`lw v0,4(s0)` 0x4b84) reused as a1 at 0x4b9c; `bnel s0,s1` loop test at 0x4bb0 with the next `lw v0,0(s0)` in its delay slot. cmd $s0, end $s1, 0xFD $s2.
uopt_trace -l 5/6 (copies in .scratch/CleandisplayListResolveTextureImages/v/tr5_*.txt):
- Compare node: base comma `uequ{561|0}{253|0}`; plain `uequ{253|0}{561|0}` (constant-first canonicalisation, Q0474/Q0185); opcode local `uneq{375|0}{253|0}` (the local stays left, ugen copy-propagates it to the srl temp t6).
- Colouring order 0 (cmd, 14=$s0), 7, 14, then end (bit 2, adjsave 3.67) vs 0xFD (bit 27): guard / `;` forms give 0xFD live blocks [3..8], adjsave 3.33 -> end first ($s1), 0xFD $s2; if-block form without `;` gives [3..6], adjsave 5.0 -> 0xFD first ($s1), end $s2 (end's forbidden set gains 15). Q0773/Q1240: an early continue adds the same blocks as a dead statement in the hit block.
