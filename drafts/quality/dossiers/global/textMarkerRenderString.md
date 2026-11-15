# textMarkerRenderString (global, src/global/9DD70.c)
## Sites
(none left in .scratch/HacktextMarkerRenderString2/9DD70.c)
global:8069D424:dead-if:69922c dead-if (removed): `if (&state == 0) {}` kept state aliased so the case-1 `sb 0x13 -> 0x57(sp)` before renderAppendScaledMatrix and the `lbu/andi 0xfffe/sb 0x57(sp)` after it survived; without it uopt folded to `li t7,0x12` (0x472c).
global:8069D424:other:c7e04f other (removed): `x = actor->unk155; switch (x)` put the selector in a2 (x's web); only needed while the address test was alive.
## Attempts
2026-11-10..2026-11-14 Clean9DD70/Rev16I/Rev20B/Perm20B/Rev26B/CleanGlobal9DD70 opus low/default/xhigh: dead-if removal (fdiff 1, score 63..1070), permuter (volatile state 245; comma/new_var hacks), direct switch (a0 instead of a2, score 3..15), permuter on c7e04f best=0 = the reuse itself.
2026-11-15 cleanup HacktextMarkerRenderString2 anthropic/claude-opus-5-5:high: dead-if removed + `state = 0x13; call; state &= 0xFFFE` respelled `flags |= 0x10; call; flags &= ~1` on the entry value 3 -> fdiff 0. Measured on the way: no test 63; struct {s16 width; u8 mode; u8 state;} 63; struct {u8 mode; u8 state;} 80; struct {u8 state;} 80; u8 state[1] 139 (identical instructions, array 4-aligned at 0x5c, frame 0x68); `state ^= 1` / `state--` after the 0x13 store 63; `state += 0x10` 0.
2026-11-15 HacktextMarkerRenderString2 opus:high: after that fix `switch (actor->unk155)` directly -> fdiff 0 (selector a2); `case 6: state |= 0x20` instead of `= 0x23` -> 0 (kept for consistency).
2026-11-15 HacktextMarkerRenderString2 opus:high: review removed 9 redundant casts (all fdiff 0); locals state -> flags, mode -> font.
## Untried ideas
none (function hack-free)
## Evidence
frame 0x60; marker 0x5c(sp), x/y slots 0x58-0x5b (unused, x/y coloured a2/a3), flags 0x57(sp), font 0x56(sp), width 0x54(sp), confettiX 0x4a(sp).
0x43c8/0x43cc: li t7,3; sb t7,0x57(sp) (flags = 3 at entry).
0x4490: lbu a2,0x155(s1) unk155 selector in a2 (x's argument register for textDrawStringVtx).
0x4704/0x4714: li t6,0x13; sb t6,0x57(sp) before jal renderAppendScaledMatrix (0x4724); 0x4730-0x474c: lbu t8,0x57(sp); andi t9,t8,0xfffe; sb t9,0x57(sp).
0x46c0: li t4,0x23 (case 6) in the dispatch delay slot; 0x4888: lbu t8,0x57(sp) -> sw 0x14(sp) flags arg.
