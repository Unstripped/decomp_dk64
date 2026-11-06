---
title: "vsprintf IDO codegen quirks (3D20.c pass)"
description: "The natural shared-initialization fix that matched vsprintf, its readonly string ownership, and historical IDO experiments."
origin: "ok-fine dk64/notes/vsprintf-ido-quirks"
---
# vsprintf IDO codegen quirks

## Matching resolution (2026-11-04)

`vsprintf` is matching C in `src/boot/3D20.c`, not a NON_MATCHING park. The full ROM gate and checkout build both pass. The tracked draft was removed.[^target]

The last normalized difference was four diff lines in one `%p` scheduling hunk: `li s4,120` and `addiu ra,sp,379` occupied the wrong order around the unconditional branch. A backend-record swap was known to fix it, but local assignment permutations and joining the pointer-arm source lines did not. Move `end = &nbuf[0x7F]` out of the five numeric arms and put it once at their shared `numout` label. IDO moves the common initialization back into predecessors with the target schedule; this natural consolidation reaches full=0 without a new FAKE construct. All uses of `end` in this function are in the shared numeric-output path.[^target]

A reduced-TU score of zero was not the whole-object gate: leaving the three standalone string pragmas duplicated compiler-emitted literals, and the literal encounter order put `(null)` before the empty string. The matching C explicitly owns `D_80010360[4] = ""`, `D_80010364[8] = "(null)"`, and `D_8001036C[8] = "(nil)"` as const unsigned-char arrays, references them instead of literals, and removes their old pragmas. This preserves names, order and padding. `fdiff.sh` then reports TEXT OK; the full ROM hash is the deciding check.[^target]

## Historical compiler experiments (2026-10-19)

These observations describe earlier candidate bodies, not constraints on every possible matching implementation.[^experiment]

- FP constant multiplies were not folded in the tested loop. A variable initialized to 10.0 reproduced the first literal guard; `s = 1.0; while (s * 10.0 <= v)` emitted a multiply.
- Each `volatile double` read generated a load, preventing the target's shared load.
- Taking a nonvolatile double's address for a byte sign test caused stack reloads in reduced tests, but the full candidate behaved differently.
- A tested unsigned-char digit local added masking and changed the frame; an int local was closer.
- A sixth double grew that early candidate's frame. This was candidate-specific, not a general local-count invariant.

The old 5152-versus-5120-byte draft and temporary path are superseded by the committed match.

## Sources

[^target]: src/boot/3D20.c @ fdcf8f98590a
[^experiment]: urn:ok-fine:pasted:vsprintf-pass3-ido-microtests
