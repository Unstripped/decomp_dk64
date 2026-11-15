# inputRemapButtons

## Sites
- **`global:806DFF34:other:80ae89`** (`ghost0 = mask`) and **`global:806DFF34:other:297e32`** (`ghost1 = seen`), plus the 3 exhausted dead tests on the ghosts.
  - Together they make uopt run out of colours (Q0682). The u16 param `buttons` then gets no register and is reloaded from its home: `lhu t9,2(sp)` at 0xbb8 and `lhu t0,2(sp)` at 0xbbc.

## Attempts
- **2026-11-14, HackE4090InputA, high.** A grid of 48 ghost-free bodies:
  - loop shapes: do-while / while / for / post-increment;
  - `mask & buttons` vs `buttons & mask`;
  - return order;
  - u32 / u16 / s32 mask.

  Best full=15. In every best body the residue is `andi t6,a0,0xffff`, with buttons held in a register (a3) across the loop.
- **K&R definition** (`u16 inputRemapButtons();` + old-style params): still emits the andi, so this is not a prototype effect.
- **Other ghost-free forms:**

  | form | full |
  |---|---|
  | u16 `held` copy | 15 |
  | `u16 *first` | 15 |
  | ButtonRemap pair struct | 23 |
  | u32 `hit` temp | 15 |
  | index loop | 25 |

## Untried ideas
- A natural seventh live web that costs no instruction. Q0724's `to` pointer costs an addiu per iteration.

## Evidence
- Target: `sw a0,0(sp)` at 0xba4. No andi on buttons; two home reloads.
- The loop advances map with two `addiu a1,a1,2` per pair (0xbd4, 0xbec).
