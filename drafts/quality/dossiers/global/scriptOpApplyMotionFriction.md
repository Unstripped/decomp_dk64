# scriptOpApplyMotionFriction (global, src/global/19A00.c)
## Sites
global:80615E74:other:215242 other: `if ((u32)current == imm)` (FAKE, removed 2026-11-17f): the u32 cast of the s16 copy local `current` (= motion->frameIndex) made uopt emit `bne a0(imm),v1(frameIndex)` at .text 0x11d4 instead of `bne v1,a0`
## Attempts
2026-11-13 cleanup round 38 CleanGlobal19A00 anthropic/claude-opus-5-5:xhigh: sweep plain/recipe nohit; diagnose: cast -> uequ{ucvt(ucvt imm lbu)}{ucvt current lh} -> bne a0,v1, no cast -> uequ{current}{ucvt imm} -> bne v1,a0 (full=1), colouring identical; permuter best=0 only `(current ^ 0) == imm` (noop-arith steer) -> nohit
2026-11-17f 2026-11-17: cleanup CleanscriptOpApplyMotionFriction CleanscriptOpApplyMotionFriction anthropic/claude-opus-5-5: drop `current`, read `motion->frameIndex` inline in the test and both arms -> fdiff 0 (FAKE 1 -> 0). Other spellings scored with variants.py try: `imm == motion->frameIndex` (inline) full=1, `imm == current` full=1, `current == imm` full=1, s32 current full=2, `current = motion->frameIndex;` kept plus `motion->frameIndex == imm` full=33 (either operand order), current assigned only in the then arm with the else arm inline full=40
## Untried ideas
none left (site fixed)
## Evidence
- 19A00.o .text: 0x11c8 `lbu a0,47(sp)` (imm), 0x11cc `lbu t7,46(sp)` (imm2), 0x11d0 `lh v1,12(v0)` (frameIndex, one load), 0x11d4 `bne a0,v1`, delay 0x11d8 `addu t8,v1,t7` (else arm frameIndex + imm2, hoisted)
- then arm: 0x11dc `mtc1 v1,$f4` / 0x11e8 `cvt.s.w` and 0x11ec `sh v1,30(v0)` reuse the same v1 load (CSE of inline field reads; no separate local needed)
- 0x121c `sub.s $f8,$f2,$f0` + 0x1220 `neg.s`: the `-(target - currentF)` else of the frameFrac if is real target behaviour
- uopt trace of the fixed copy: `uequ{1057|0 ucvt imm}{906|0 uilod motion+0xC}`: with both sides isop the right source operand comes first regardless of candidate number (12E800 2026-11-17f lever); `imm == motion->frameIndex` flips it
