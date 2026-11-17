# sfxUpdateSourceGroups (global, src/global/7130.c)
## Sites
global:806057F8:dead-if:f73918 dead-if: entry `if (gActivePlayerState != NULL) {}` (class 2, availability). Without it &gActivePlayerState becomes an a1 web and the tail reload (lw t1,0(t1) at 0x5fdc after sw t9 at 0x5fd8) is forwarded: full 8, 16 bytes shorter.
global:806057F8:punned-cast:u9b99d punned-cast: CLOSED as ORIG (2026-11-17): `*(s32 *)&D_80770F38` passed to n_alSndpPostEvent is the target's integer reload of the static's bits.
## Attempts
2026-11-17 2026-11-17: cleanup HacksfxUpdateSourceGroups HacksfxUpdateSourceGroups anthropic/claude-opus-5-5:high: classify by hand: `if (1) {}`, `if (actor != NULL) {}`, `;` -> 8 (= removal); `if (gActivePlayerState) {}`, `if (gActivePlayerState->camActor != NULL) {}` -> 0; guard on gPlayerSlots 15, on gPlayerSlots->actor 27
2026-11-17 2026-11-17: cleanup HacksfxUpdateSourceGroups HacksfxUpdateSourceGroups anthropic/claude-opus-5-5:high: entry dead store `camActor = gActivePlayerState->camActor;` -> 8; `camActor = NULL;` -> 8; guard moved before the tail store -> 8
2026-11-17 2026-11-17: cleanup HacksfxUpdateSourceGroups HacksfxUpdateSourceGroups anthropic/claude-opus-5-5:high: tail rewrites without the guard: assignment expression `camActor = (gActivePlayerState = ...)->camActor` -> 8; camActor local dropped -> 29; `gPlayerSlots[0].actor` -> 8
2026-11-17 2026-11-17: cleanup HacksfxUpdateSourceGroups HacksfxUpdateSourceGroups anthropic/claude-opus-5-5:high: u9b99d tagged `// ORIG:` with offsets 0x5f74/0x5f90/0x5f98 -> fdiff 0, sweep no longer lists the site
## Untried ideas
A data/bss-level change for gActivePlayerState is out of scope (shared global, other files); the 7130 .bss carve is DEFERRED (pending.md:85) and does not touch gActivePlayerState.
uopt -l trace of why an entry read of the global blocks uoptinput's tail store forwarding (Q0558 count-1 ilod rule): would explain, not remove, the guard.
## Evidence
Target 7130.o sfxUpdateSourceGroups starts 0x33c8. No load of gActivePlayerState before 0x5fc8. Tail: lui at / lui t1 at 0x5fc8/0x5fcc, sw t9,%lo(gActivePlayerState)(at) at 0x5fd8, lw t1,%lo(gActivePlayerState)(t1) at 0x5fdc (store not forwarded), lw v0,0x104(t1) at 0x5fe0.
D_80770F38 = .bss+0x148: lwc1 $f4,0x148(at) at 0x5f74, c.eq.s with D_80770D70[i] at 0x5f7c, swc1 $f4,0(v0) at 0x5f90, then lw a2,0x148(a2) at 0x5f98 and jal n_alSndpPostEvent at 0x5fa0 (a1 = 0x10).
