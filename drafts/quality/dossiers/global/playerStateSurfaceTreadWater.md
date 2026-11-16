# playerStateSurfaceTreadWater (global, src/global/D5E10.c)
## Sites
global:806D8B08:goto:ud694d / #2 / #3  goto: cases 0, 1 and default (case 2 + out-of-range) skip the post-switch block (ramp target reset + playerClampWaterSurfaceHeight) and land on the single jal actorUpdateModelMatrix at 0x7ea0.
## Attempts
2026-11-09..11-11 CleanD5E10/CleanGlobalD5E10: return-duplicated tails -> fdiff 1 (+32 bytes); settle flag -> re-colours (111 lines); permuter on the return-duplicated tail -> no zero.
2026-11-14 HackplayerStateSurfaceTreadWater anthropic/claude-opus-5-5:high: nested switch (outer case 3..8 group with inner switch + tail) -> variants full=219; range if around two switches -> full=491; 3 int->f32 casts removed -> fdiff 0; waterLevel temp folded -> fdiff 0; ++/-- -> fdiff 0.
2026-11-16 HackplayerStateSurfaceTreadWater2 anthropic/claude-opus-5-5:high: one switch, all arms break, post-switch block behind if (u >= 3 && u < 9) on a saved u8 selector -> full=141; second switch on the saved selector with a case 3..8 group around the post-switch block -> full=147; quality sweep -> 0 hits.
## Untried ideas
none that avoid a goto: every goto-free shape either duplicates the tail call (return), adds a flag or range test, adds a second dispatch, or needs a Duff-style `if (0) { case N: }` block (Q0953, a dead-if hack).
## Evidence
0x7a4c sltiu at,t2,9 / 0x7a50 beqz -> 0x7c48 (default = case 2 code); one jump table.
0x7b38, 0x7c40, 0x7ce8: b 0x7ea0 (cases 0, 1, default); 0x7ea0 jal actorUpdateModelMatrix, the only call to it.
0x7d04, 0x7d90 (->0x7e00), 0x7dac, 0x7dc8, 0x7de4: b 0x7e04 (cases 3..7); case 8 falls into 0x7e00.
0x7e30 beqz t8 -> 0x7e90 (jal playerClampWaterSurfaceHeight), falls into 0x7ea0.
