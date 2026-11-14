# playerTakeDamage (global, src/global/EFDC0.c)
## Sites
- global:806EEAF8:other:ce589c: the empty `case 0x2B: break;` at the end of the second queuedState switch. Classified ORIG.
## Evidence
- bound check: addiu t6,v0,-43 at 0x4360; sltiu at,t6,13 at 0x4364; beqz at 0x4368 -> 0x46bc
- jtbl .rodata+0x210, 13 entries:
  - 0x2B, 0x2C, 0x2D, 0x30, 0x31, 0x33-0x36 -> 0x46bc (exit)
  - 0x2E, 0x2F -> 0x4398
  - 0x32 -> 0x4494
  - 0x37 -> 0x469c
- 0x2B points at the exit, so it shares no case body. Q0344: an exit-pointing empty case is written after the last case.
## Attempts
- CleanEFDC0, Rev17N (opus:low): diagnose, permute (removal 3234/2195).
- 2026-11-14 U: classified ORIG, tagged with offsets.
