# playerUpdateCommon (global, src/global/CEAE0.c)

## Sites
- global:806CA5F8:dead-if:c17942 dead-if (was 8ce181, `if (gCurrentActor && gCurrentActor) {}` until 2026-11-17): `if (gCurrentActor) {}` before the first statement. Its ilod makes the gCurrentActor load {817|0} candidate bit 0, ahead of the attacker var {800|0}. That keeps the gActivePlayerActor pointer web coloured into v1 at 0xf14-0xf2c; removing it gives s0 (adjsave tie order, Q0199). One read is enough.
- global:806CA5F8:other:81cda0 other: `(u32)attackerIndex != gActivePlayerState->playerIndex`. The cast makes the local a ucvt isop numbered after the field's, so the compare at 0xe54 is `beq t2,v0`; without it the compare is `beq v0,t2` (Q0715). A (u32) on the field side instead gives the same code: any unsigned compare does.
- global:806CA5F8:other:318197 other (was 8b0fd9, a cast on all three addresses until 2026-11-17): `&((PlayerStruct *)gPlayerSlots)[gCurrentPlayerIndex].headX` on the first argument only; headY/headZ are plain. The identity cast builds uadd(load, idx*size). Cast-free spellings build uadd(idx*size, load) and rotate the t7/t8/t0 scratch ring from 0x12d0 (Q0717). Only the first address needs it.
- (removed 2026-11-17) global:806CA5F8:goto:u933fb / u36185 / u72d9b / u72d9b#2: the heavyImpact dispatch is now `switch (heavyImpact) { default: ...; case 1: ...; case 2: ... }`.

## Attempts
- 2026-11-09 .. 2026-11-14 (rounds 2-36, opus-5-5 :low/:xhigh): see `uv run tools/quality.py history playerUpdateCommon`. Removals, cond/classify/recipe, uopt_trace diagnoses, permuter runs (all hack swaps), goto-hand switch/if-chain forms, natural reconstructs (1175+).
- 2026-11-14 HackplayerUpdateCommon (anthropic/claude-opus-5-5:high), after the PadInputState/PlayerStruct typings:
  - fresh sweep: all nohit;
  - variants.py scan on each single-removal copy: no zero; best is the float-suffix noise at the removal score.
  - 8b0fd9:
    - PlayerStruct *slot snapshot: function-scope first/last 79, block-scoped 79, also feeding the camProjectToScreen headY 240.
    - `&(gPlayerSlots + i)->headX`: 37 (same as plain).
  - 81cda0:
    - u8 selfIndex snapshot before/after: 269.
    - s32 attackerIndex: 43.
    - inverted if/else: 17.
    - `!(==)`: 1.
  - 8ce181:
    - `Actor *attacker = gCurrentActor` initialiser: 24.
    - state assignment first: 26.
  - Coupled removals: 8ce181+81cda0 25, 8ce181+8b0fd9 61, 81cda0+8b0fd9 38, all three 62, all three + slot local 103.
- 2026-11-17 cleanup HackplayerUpdateCommon2 (anthropic/claude-opus-5-5):
  - gotos removed, fdiff OK:
    - `switch (heavyImpact)` in body order (default first), plus `dist = sqrtf(SQ(camX - nodeX) + SQ(camY - nodeY) + SQ(camZ - nodeZ))` with the dx/dy locals gone.
    - dist, fx and flags are declared into the freed unreferenced homes (sp+116/96/80), so every referenced home stays.
  - Frame budget: the locals were 56 bytes, and the switch temp fits only at 55 or less.
    - s8 flags: full=1 (the load becomes `lb +1` instead of `lh`).
    - char snd: full=2.
    - inlining dy alone: 29.
  - SQ orders in the goto form:
    - X+Y+Z: 0.
    - Z+X+Y: 6.
    - Z+(X+Y): 34.
    - keeping dz or dx as a local: 29.
  - If-chains:
    - `if (h != 1 && h != 2) {default} else if (h == 1) ...`: 4 (redundant `h == 1` retest at 0x1138, not threaded).
    - nested `!=` ifs: 108.
    - plain else-if: 12.
  - Declaration orders: flags last (below projY): 4. fx/dist swapped between sp+116 and sp+96: 0.
  - 8ce181:
    - removal 24.
    - `gActivePlayerState = (attacker = gCurrentActor)->customState`: 27.
    - `attacker->customState`: 27.
  - 81cda0:
    - removal 1.
    - s16 local: 1.
    - function-scope s8 declared last: 1.
    - function-scope s8 after the u8 locals: 22.
  - 8b0fd9:
    - removal 37.
    - `PlayerStruct *slots = gPlayerSlots` block local: 162.
  - All three FAKE removed on the switch/SQ body: 62.
  - `(f32)effectTimer` removal: 34. It is a real cvt.s.w + cvt.d.s, so it stays.
- 2026-11-17 cleanup HackplayerUpdateCommon3 (anthropic/claude-opus-5-5), fdiff OK:
  - 8ce181 -> c17942: `if (gCurrentActor) {}` (one read) matches, so the second read was dropped.
    - attacker = gCurrentActor moved below the D_807463B8 flag stores (no dead test): 428. The entry `sw s0,100(sp)` at 0x838 pins it to the top.
    - gActivePlayerState assignment first, re-measured on the switch/SQ body: 26.
  - 8b0fd9 -> 318197: per-argument cast test. Cast on headX alone: 0. On headY or headZ alone, or both: 37. Two casts dropped.
    - headX as `&(gPlayerSlots + i)->headX`, `&(*(gPlayerSlots + i)).headX`, `&(i + gPlayerSlots)->headX`: 37 each.
  - 81cda0:
    - `attackerIndex != (u32)gActivePlayerState->playerIndex`: 0 (an unsigned compare, still a cast).
    - `(s8)` field cast: 2 (lb instead of lbu). `!(==)`: 1. xor compare: 237.
    - attackerIndex assigned in the test (`(attackerIndex = ...) >= 0`): 1 plain, 0 with the cast.
    - A u32 bitfield playerIndex is ruled out: CC800/201B0 store it with a byte store.
  - Reconstruct: natural body (all three removed) 62; with the assignment-in-test local 62.

## Untried ideas
- A field-type change for PlayerState.attackerPlayerIndex/playerIndex was ruled out: playerIndex is already u8 (stored as a byte in CC800/201B0), and the s8 side needs the `>= 0` test.
- 81cda0: a natural unsigned operand would fix it (a field-side (u32) matches too). Nothing on either side is unsigned int in the known types.
- c17942: one natural statement that reads gCurrentActor once in a test before `attacker = gCurrentActor` and emits no code would fix it. No such statement is known yet.
- 318197: only the first address (headX) needs a non-leaf base. A natural spelling of just that argument would fix it.

## Evidence
- 0xe54: target `beq t2,v0` (field operand first).
- 0xf14-0xf2c: gActivePlayerActor in v1 (target) vs s0 (dead test removed).
- 0x12d0-0x12ec: gCurrentPlayerIndex/gPlayerSlots in t8/t7 ring order (target) vs rotated (cast removed).
- Frame 0x78. Referenced homes are sp+112/108 (screenX/Y), 104-107 (u8 impacts), 100 (attacker), 92/88/84 (node), 76/72 (proj). sp+116, 96, 80 and the area below 72 are never addressed, so their locals (dist/fx/flags/snd) are register-only.
- 0x10bc/0x10c4: `cvt.s.w` then `cvt.d.s` for effectTimer (the (f32) cast is real).
