# controllerUpdate (global, src/global/F600.c)

## Sites
- global:8060AC7C:dead-if:5a6d62, e2312d, 96841b: these three dead ifs were one coupled steer. The constant 2 is live from the `switch` through the timer reset and has to colour after `padIdx`, so `padIdx` gets $s2 and `li 2` gets $s3 (target 0x454-0x464, 0x5f4). They lowered the constant's adjsave by adding blocks to its range (Q0523). REMOVED.
- global:8060AC7C:other:c0460c: `timer == 11U` forced the operand order `bnel t4,a1` (target 0x764). REMOVED.
- global:8060AC7C:other:31d0f0 `sum = padIdx * 2`: this puts the halfword offset into the checksum variable `sum`, whose uopt web is $v1, so the held address becomes `addu t0,v1,t8` (0x690-0x6b8). STILL OPEN.
- global:8060AC7C:other:4ae842 `curButtons = pad->button`: a second button web (a2 → a3 copy at 0x6e8). It keeps $s0-$s6 and frame 0x38. STILL OPEN.

## Attempts
- 2026-11-14 U HackcontrollerUpdate (strong retry):
  - Dropping the timer local and testing the re-read element is fdiff 0. c0460c is fixed.
  - Moving `padIdx = 0` after the checksum `if` and writing the case-2 loop as a `for` is fdiff 0, and removes all three dead ifs.
  - CtrlAHeld[padIdx] gives 9. An `offset` local gives 0 but keeps the pun. The single-variable button forms give 96-147.

## Untried ideas
- Find out the as1/ugen ring order that would give `padIdx * 2` $v1 without a named web (tools/ringfifo.py sim on as1probe keep). Repo source: the staged-near-miss-finishing guide.
- A permuter run on the current base (no dead ifs, padIdx init moved, for loop), with only the 31d0f0 and 4ae842 sites removed.

## Evidence
- uopt -l5 adjsave values:
  - const {2}: 8.385 with no dead ifs and do-while, 7.786 with a for loop, 7.267 with any two dead ifs plus for, or all three with do-while.
  - padIdx {1552}: 7.625 with init before the checksum `if`, 8.714 with init after it.
- uopt -l6 colouring: identical between the `sum` form and the CtrlAHeld[padIdx] form. Only the ugen temps differ (v1/t0 vs a0/a3).
