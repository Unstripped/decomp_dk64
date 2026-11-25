# inputRemapButtons (global, src/global/E4090_player_input.c)
## Sites
All five sites REMOVED 2026-11-25 (continue CleaninputRemapButtons): the body is now
`while (*map) { seen |= *map; if (*map++ & buttons) { mapped |= *map; } map++; }` with only `seen`/`mapped` locals, no FAKE.
- global:806DFF34:other:80ae89 (`ghost0 = mask`): held a0 across the loop. Natural replacement: the int promotion of the loop-body load, ucvt(*map) (bit 10), is live only in the loop body once the loop test is a bare truth test; it takes a0 and emits no code (reads served from the load's v0).
- global:806DFF34:other:297e32 (`ghost1 = seen`): held a3 against buttons. Natural replacement: cfe's temp for the `*map++ & buttons` test (M -8vreg, bit 14), kept a candidate because map++ redefines its operand before the branch; it takes a3 (`and a3,v0,t0` at 0xbc8).
- global:806DFF34:dead-if:46d083 / 0e2dbc (`if (ghost1) {}` / `if (ghost0) {}`): kept the ghosts live; gone with them.
- global:806DFF34:dead-if:630c2a (`if ((u32)mask & buttons) {}`): made the and-result a CSE candidate; the cfe test temp does it instead.

## Attempts
- 2026-11-09..14 (CleanE4090, ReReview, Rev16F/J, Rev26A, CleanGlobalE4090, HackE4090InputA): removals, permuter, reconstructs, a 48-body ghost-free grid (do-while/while/for/post-increment, operand orders, u32/u16/s32 mask), K&R, held/first/pair/hit variants. All of them used `!= 0` loop tests. Best full=15: buttons coloured instead of reloaded from 2(sp).
- 2026-11-25 continue CleaninputRemapButtons anthropic/claude-opus-5-5, scored with variants.py try (full):
  - `while (*map != 0)` / `!= 0` loops:
    - mask-copy form 12; hit-var forms 7-18; index forms 22-26.
    - In every one, ucvt(*map) is live in bb0 for the `!= 0` compare. bb0 forbids a0 (buttons arrives there), so the web took a3 (`move a3,v0`) or stayed uncoloured.
  - bare `while (*map)` forms:
    - `mask = *map; seen |= mask; hit = *map & buttons;` -> 0 (a hidden re-read while mask holds the value);
    - `seen |= *map; hit = *map & buttons;` -> 0;
    - `seen |= *map; if (*map++ & buttons) mapped |= *map;` -> 0 (KEPT: no temps, no re-read of a held value);
    - hit-first order -> 3; mask-only forms (`hit = mask & buttons`) -> 12: no ilod, so they are copy-propagated.
  - Permuter 900 s from the hit-first `!= 0` form (score 635) ran as a hint search only, after the fix.

## Untried ideas
- none open: the function has no hack site left.

## Evidence
- target 0xba4 `sw a0,0(sp)` (home), 0xbb8 `lhu t9,2(sp)` (tail buttons, beqz delay slot), 0xbbc `lhu t0,2(sp)` (hoisted ucvt(buttons) in t0), 0xbc8 `and a3,v0,t0`, 0xbd4/0xbec two `addiu a1,a1,2` per pair, 0xbf0 `bnezl v0` with `or v1,v1,v0` in the slot.
- c40 trace (uopt -zdbug:5/6): seen v1, mapped a2, map a1, load v0, ucvt(load) a0 (live bb2 only), test temp a3, buttons not coloured (forbidden v0..t0), ucvt(buttons) t0: the seven webs of Q0682 with no ghost.
