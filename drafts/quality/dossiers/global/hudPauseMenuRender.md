# hudPauseMenuRender (global, src/global/ACDC0.c)

## Sites
- **6bd641/01af71 proto-steer** (kept; not this unit's): a local `renderRotatedSprite` declaration with a u8 `siz` keeps the constant-2 web in $s8, so case 0 passes `move a3,s8`. The shared 90D80 prototype gives `li a3,2` at 0x1638/0x16b8. Owner 90D80 is blocked (pending.md round 29). The 90D80 definition masks `siz &= ~0xC000`, so a u8 owner retype is not supported by the callee either.
- **f38e4a byte-offset entry** (OPEN): `(HudTextEntry *)((u8 *)it + j * 0x18)` for the eight loop-1 reads. `(it + j)` matches except `addu v0,t7,s2` at 0x12f8 (target `addu v0,s2,t7`); `it[j]`/`&it[j]` 272.
- **eb1c3c -> e1b0a2 s64 pair** (OPEN): `(s16)(s64)(s32)(fa * flyX)`. The even/odd pair fixes the ring in loop 1 (0x12e8-0x13c4): `sll t4,s0,2` (0x1324), `mfc1 t5,$f10` (0x1344), `addu s0,t4,t5` (0x134c) (Q0583/Q0588). The no-op `(f32)` on `fa` was dropped (full=0).
- **5ed6ef (u16) y steer** (OPEN, pre-existing, tagged 2026-11-14): `y += (u16)(s32)(fa * flyY)` with s16 `y`; without the `(u16)`, full=358 (`mfc1 t4,$f4` -> t3 at 0x1350, 888 instructions).
- **fa96af (u32)off steer** (OPEN, pre-existing, tagged 2026-11-14): `off = (s16)((u32)off + offsetX * 4)`; without `(u32)` the addu at 0x1364 becomes `addu t8,t7,s0` (full=1); without the `(s16)` store narrowing (or `off +=`) full=307 (Q0374 `addu; move s0,t8`).
- **b371d1 dead-if** (OPEN): `list` is homed at 0x13C(sp). `sw v0,0x13c(sp)` at 0x126c, `lw a0,0x13c(sp)` at 0x1278. Without it, list goes to $s0 (`move s0,v0`) (Q0585).
- **498f25 dead-if** (EXHAUSTED, class 1): the dead `D_80750530` test makes uopt colour $t2 (the case-2 `gPlayerInventoryTable` address at 0x1408/0x1cec/0x1d30/0x1e44) and $t0 (case-2 `cnt`, `move t0,zero` at 0x1d44). Without it, case 2 uses t0/t1/v1 and $t2 joins the ugen ring: 425 differing lines starting at 0x12b0 (Q0583).
- FIXED earlier: fc512f (fadeInput0 initialiser), 4cca45 (y0 = 0xA0 form), 744852 (gDPSetPrimColor), 1c9898 (slide local).

## Attempts
- **2026-11-14 HackhudPauseMenuRender (claude-opus-5-5, strong retry; copy from HEAD eeeab600)**: see drafts dossier (4cca45/744852/1c9898/fc512f fixed; f38e4a/eb1c3c 140 bodies, best natural full=4; permuter 1200 s; b371d1 full=5; 498f25 ~350).
- **2026-11-14 HackhudPauseMenuRender (claude-opus-5-5:high, base e3e9fef2)**:
  - Cleanups, all fdiff OK: `(f32)fa` dropped; `pips = tab->health`, `tab->kong[...]` in cases 1/2 (tab constant-propagated, full=0 each); `s16 alpha` local instead of reusing `ang` for the case-0 prim alpha (full=0).
  - Hidden-steer probes: `(u16)(s32)` y -> `(s32)` 358 / `(s16)` 308 / `(u16)` 56; `(u32)off` -> `off` 1; `(s16)` store dropped / `off +=` 307. Tagged 5ed6ef/fa96af.
  - Variable reuse probes (kept as real homes): `i` as the case-0 label index -> separate s16/s32 local 228/220; `j` as the case-1 banana count -> separate s16 135. Case-3 block `f32 fb` shadow removed or block flattened: 7.
  - f38e4a: entry spellings on the final copy: `(it + j)`/`(j + it)`/`(it + (s32)j)` 1, `it[j]`/`&it[j]`/`it[(s32)j]` 272, `sPauseTextLists[i][j]` (with or without `it`) 264, pointer local `e = &it[j]`/`it + j` 385, `sizeof` byte offset 0 (same steer). `variants.py scan` of the `(it + j)` body (191 variants): none below 1. `it`/`j` declaration at every position: 1-9. Block-scoped loop-1 locals (`f32 fa`; `s32 off; s16 y`; s16 x/y; all three) x {byte-offset, it[j], (it + j)} x {steered, natural casts}: best 47 (fa only).
  - eb1c3c: on the `(it + j)` body, 126 combinations of x-form (7) x fa/(f32)fa x y-form (3) x offsetX form (3): best 17 (`off *= 4; off += (s16)(...)`, `(u16)(s32)` y, `off +=`).
  - b371d1: dl/list role swap (list as cursor, dl or ret returned) without the dead test: 12 (outer dl homed in its arg slot 0x1A0(sp), list in s7). `ret = dl + 1` / `ret = dl; gSPDisplayList(ret++, list)` forms 14. `list` declared at each position without the dead test: 5-7; block-scoped list 7.

## Untried ideas
- A natural 64-bit or struct-copy source for the loop-1 even/odd pair (Q0583: pairs only from 64-bit values and struct copies). Nothing in the HudTextEntry reads gives one.
- An ADD-of-base spelling of the entry address without a cast (cfe turns `it + j` and `&it[j]` into IXA, index first).
- A real later use of `list` that emits no code (Q0585), e.g. an end-of-list overflow assert compiled out; no target evidence.

## Evidence
- The prologue saves s0-s8 and $f20-$f30. Frame 0x1A0. Homes: hubWorld 0x138, list 0x13C, ret 0x140, tab 0x144, i 0x158, hud 0x15C, buf 0xA8.
- Loop 1: `li s5,24` (0x12a4) + `multu s3,s5` (0x12e8), entry address `addu v0,s2,t7` (0x12f8) shared by all eight reads.
- Case 0: `li t7,160` (0x1434), `subu s4,t7,t6` (0x147c), then `sll/sra` to s16 (0x1480/0x1488).
- Case 1: `D_80750530[j]` is not pointerised: `lui t7` (0x1b10), `addu t7,t7,s3` (0x1b18), `lb t7,%lo(0)(t7)` (0x1b5c).
- Case 2: uopt colours t0 (`cnt`), t1 (`worldIndex[i]`, 0x1d3c) and t2 (table address).
- Case 1 ternary on fields: `lwc1 $f12,4(a0)` / `lwc1 $f2,0(a0)` at 0x1bc8/0x1bcc. These are temps; their colours move with fc512f.
