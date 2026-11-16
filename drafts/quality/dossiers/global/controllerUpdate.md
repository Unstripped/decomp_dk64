# controllerUpdate (global, src/global/F600.c)

## Sites
- global:8060AC7C:dead-if:5a6d62, e2312d, 96841b: these three dead ifs were one coupled steer. The constant 2 is live from the `switch` through the timer reset and has to colour after `padIdx`, so `padIdx` gets $s2 and `li 2` gets $s3 (target 0x454-0x464, 0x5f4). They lowered the constant's adjsave by adding blocks to its range (Q0523). REMOVED.
- global:8060AC7C:other:c0460c: `timer == 11U` forced the operand order `bnel t4,a1` (target 0x764). REMOVED.
- global:8060AC7C:other:31d0f0 `sum = padIdx * 2` + `*(u16 *)((u8 *)CtrlAHeld + sum)` pun: two effects. (a) It created the umpy padIdx*2 chain (bit 118) before the curButtons var (bit 127); both sit at adjsave 40.0 and the lower bit takes v1 (0x690 `sll v1,s2,1`). (b) Copy propagation of `sum` rebuilt the held address `uadd(CtrlAHeld, padIdx*2)` late (bit 214), after the buttons var (142); both sit at 30.0, so buttons takes a3 (0x6e8) and the held address t0 (0x698). REMOVED (2026-11-15).
- global:8060AC7C:other:4ae842 `curButtons = pad->button`: one `lhu a2,0(a1)` (0x69c) used by xor/and (0x6ac/0x6b0), the held store (0x6e0) and `move a3,a2` (0x6e8). uopt also colours the var a0 with no code (adjsave 40), which keeps pad addr in a1 and the load in a2. It is a value temp: tag dropped, temp kept. REMOVED (2026-11-15).
- `// LAYOUT` line (not a site): `buttons = curButtons; pressed = ...; CtrlAHeld[padIdx] = pad->button;` on one source line. With `buttons = curButtons` before the CtrlAHeld read, the buttons var outranks the held address. as1 can then put `move a3,a2` after `sh a2,0(t0)` (into the bnez delay slot at 0x6e8) only when no `.loc` barrier separates them (Q0183). Split onto three lines: 4 lines off.

## Attempts
- 2026-11-14 U HackcontrollerUpdate (strong retry):
  - Dropping the timer local and testing the re-read element is fdiff 0. c0460c is fixed.
  - Moving `padIdx = 0` after the checksum `if` and writing the case-2 loop as a `for` is fdiff 0, and removes all three dead ifs.
  - CtrlAHeld[padIdx] gives 9. An `offset` local gives 0 but keeps the pun. The single-variable button forms give 96-147.
- 2026-11-15 U HackcontrollerUpdate2 anthropic/claude-opus-5-5:high:
  - The level-5 trace shows the tie mechanism above. ringfifo is not relevant: v1 is uopt colour 2, not a ugen ring register.
  - `pressedOut = &CtrlAPressed[padIdx]` right after `pad` (or before it) creates padIdx*2 before curButtons: v1 is correct. Natural orders are then 4 (`buttons = curButtons` before the held read: sh/move swapped at 0x6e0/0x6e8) or 6 (after it: held a3, buttons t0).
  - Brute force over statement orders (P, PP, C, B, PR, HS) and value sources (cur, buttons, pad->button for B/PR/HS) with PP absent/first/after pad: best 4; without curButtons 96-124.
  - The held pointer local (`&CtrlAHeld[padIdx]` anywhere) gives 8-14. `held = CtrlAHeld` base pointer inside the block gives 6; in an earlier block 144-146 (kept in a register, not propagated). Repeat pointer local 24-30. Old-held value temps 85-215. buttons reused earlier (case 2, gButtonsPressed) 38-125. buttons after the gate (PRE) 116.
  - Joined lines: `buttons = curButtons; pressed = ...; CtrlAHeld[padIdx] = pad->button;` on one line with PP is fdiff 0. Any pair joined, or no PP, stays at 4 or more (1096 variants).
  - Permuter on the V4 form (no pun, CtrlAHeld[padIdx], buttons = curButtons before pressed): base 140, best 20 after 900 s. Its best output joins the same lines.
  - Final: the joined line is tagged `// LAYOUT` (AGENTS.md: a line join for as1 scheduling is not a site), so FAKE goes 2 -> 0 and the review is fixed.

## Evidence
- uopt -l5 adjsave values:
  - const {2}: 8.385 with no dead ifs and do-while, 7.786 with a for loop, 7.267 with any two dead ifs plus for, or all three with do-while.
  - padIdx {1552}: 7.625 with init before the checksum `if`, 8.714 with init after it.
  - Block 44 ties (base): padIdx*2 umpy 40.0 (bit 118, v1) vs curButtons var 40.0 (127, a0); pad addr 30.0 (125, a1), load 30.0 (129, a2), buttons var 30.0 (142, a3), held addr 30.0 (214, t0).
- ugen (as1probe keep): the base emits `move $7,$4` (buttons) after `sh $6,0($8)` (held). The split PP form emits it before, so as1 fills the bnez slot with the sh.
- uopt -l6 colouring: the sum form and the CtrlAHeld[padIdx] form produce the same sequence of colour numbers, but the candidates in it differ. Under CtrlAHeld[padIdx], curButtons (bit 125) takes v1 and padIdx*2 (bit 132) takes a0. The held address (133) takes a3 and buttons (141) takes t0. The earlier "only ugen temps differ" reading was wrong: these registers are uopt colours.
