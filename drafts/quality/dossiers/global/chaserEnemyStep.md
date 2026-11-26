# chaserEnemyStep (global, src/global/BA790_enemy_chaser.c)
## Sites
global:806B5A90:other:427559 other: `x` reused as the case-0x33 actorMoveWithinZone move flags (target `li s0,2` 0x298 / `move s0,zero` 0x2ac, `andi a3,s0,0xffff` 0x2b8). Untagged 2026-11-25c: R-oildrum census holds (below).
global:806B5A90:other:edb99a other: `x` reused as the case-0/4 enemyAggroStateUpdate chase script id (target `li s0,588` 0x360 / `li s0,589` 0x370, `move a2,s0` 0x378). Untagged 2026-11-25c: R-oildrum census holds (below).
Local renamed `x` -> `tmp` 2026-11-25c (director condition attached to the ACDC0 `radius` census: a role-neutral scratch name, so the old name no longer reads as the R5 steer). Its declaration (line 41) keeps one `// ORIG:` comment: the role list (case 0x33 move flags, case 0/4 chase script id, case 0x37 fade step and light step) plus the home evidence (two values spill to one home, rulings.md:100) and the census result. Its frame clause was corrected 2026-11-25c (hidden-reuse check below): a fade or light local grows the frame 0x50 -> 0x58 (declared before `tmp`) or keeps it (after), it never shrinks it to 0x48 on this body.

## Attempts
2026-11-18c Polishglobal9DD70: tagged both lines FAKE (Q1517): a moveFlags/chaseScriptId local (top or block scope) or the inline ternary gives .text 2912 (target 2928).
2026-11-25c LeverScout28 (per brief): splitting x's register-only roles removes the 64(sp) home and shrinks the frame 0x50 -> 0x48 (split 93; 111-variant scan of the split best 69).
2026-11-25c continue-lead-2 CleanchaserEnemyStep anthropic/claude-opus-5-5: R-oildrum census, 141 bodies scored with variants.py try on the base body (scores `full`), each diff read with deadsweep score --diff. No body matches (only BASE = 0). Results below -> both sites untagged; copy fdiff exit 0, clint uninit exit 0.
2026-11-25c CleanchaserEnemyStep: variants.py scan --max 0 (130 one-edit variants each) of the moveFlags split copy (s32 after x, base 88): best 65 (`step` s32 -> s16), no zero; of the scriptId split copy (s32 after x, base 179): best 108 (`size` s32 -> s16), no zero.
2026-11-25c CleanchaserEnemyStep (resumed after the harness restart): director hidden-reuse check (`.scratch/lead3/hidden_reuse_msg.md`) of every other local: none found (table below). Fade/light split census of `tmp`'s two ORIG roles (254 bodies, census3/, scores census3/try3.txt, diffs diffs3/): no body matches; the ORIG comment's frame clause corrected (comment only, fdiff 0). Ledger `ledger3_BA790_enemy_chaser.txt` (1 review line, base 15b7686a).

### Census part 1 (frame proof): a local of its own for the role, every position
Function-scope slots: before `ret`, after each of `ret yawDiff step lightRadius x alpha angle size` (9 slots), each plain and `register`.
Block scope: move flags in a `case 0x33: { ... }` block, a bare block over lines 93-98, a bare block over lines 93-101; script id in the `if (gGameMode != 1) {` block, a `case 0: case 4: { ... }` block, a bare block over lines 111-116; each plain and `register`.
| role | type | positions | full | what moved |
|---|---|---|---|---|
| move flags | s32 | 8 function slots (all but after ret) + 3 block scopes, plain and register (22 bodies) | 88 | frame 0x50 -> 0x48; x home stores/reloads 0x494/0x49c/0x4a0/0x4b8 and 0x618/0x61c/0x620 gone (fade x in a2, light x in a register); flags in v1 (`li v1,2`/`move v1,zero`, `andi a3,v1,0xffff`); every sp home -8 |
| move flags | s32 | after ret, plain and register | 79 | frame kept 0x50; x home stores/reloads gone; yawDiff home 76(sp) -> 70(sp); billboardSubmit/lightAdd argument temps renamed |
| move flags | u16 | 9 function slots + 3 block scopes, plain and register (24 bodies) | 90 | frame 0x50 -> 0x48; x home gone; flags built in a3, the target `andi a3,s0,0xffff` at 0x2b8 disappears |
| script id | s32 | 8 function slots (all but after ret) + 3 block scopes, plain and register | 179 | frame 0x50 -> 0x48; x home gone; id built in a2 (`li a2,588/589`), `move a2,s0` 0x378 gone, `beq`->`beql` at 0x350, temp ring shifted (t8->t3 ...) |
| script id | s16 | 9 function slots + 3 block scopes, plain and register | 179 | as s32 |
| script id | s32 | after ret, plain and register | 171 | frame kept 0x50; x home gone; yawDiff home 76(sp) -> 70(sp) |
| script id | u16 | 9 function slots + 3 block scopes, plain and register | 178 | frame 0x50 -> 0x48; x home gone |
| both roles | s32 | both locals after x / after size | 93 | frame 0x48, x home gone |
| both roles | s32 | both locals before ret | 87 | frame kept 0x50, x home gone |
uopt trace (-l 6): at the base, x (vreg -16, candidate 89) is one candidate over all four roles, split into pieces 89/239/240/241 `not colored (-ve save)` (the 64(sp) home) and 242 coloured 14 (s0); with the move flags split off, x (candidate 108) is coloured whole (5) and the flags local (89) gets 2: no home.

### Census part 2 (no-local proof): every spelling without a local for the role
| role | spelling | full |
|---|---|---|
| move flags | `gCurrentActor->subState ? 0 : 2` inline (also `(...) ? 0 : 2`, `!= 0 ? 0 : 2`) | 104 |
| move flags | `gCurrentActor->subState == 0 ? 2 : 0`, `!gCurrentActor->subState ? 2 : 0` | 105 |
| move flags | `(gCurrentActor->subState == 0) << 1` | 126 |
| move flags | `!gCurrentActor->subState * 2` | 129 |
| move flags | if/else with two actorMoveWithinZone calls (`subState`, `!= 0`) | 152 |
| move flags | if/else with two calls on `subState == 0` | 153 |
| script id | `gCurrentActor->actorType == 0xB6 ? 0x24D : 0x24C`, `!= 0xB6 ? 0x24C : 0x24D` | 194 |
| script id | `0x24C + (gCurrentActor->actorType == 0xB6)` | 183 |
| script id | if/else with two enemyAggroStateUpdate calls (`==`, `!=`) | 193 |
| both | both ternaries inline | 85 |
| both | both if/else call pairs | 167 |
Every one drops the x home (frame 0x48). A direct field/array write or a pointer local does not apply: both values are only call arguments.

### Census part 3 (plausible as written)
Type: x is s32. The fade step (`step - 0x82`, `cvt.d.w` 0x4d4) and light step (`cvt.d.w` 0x638) are s32; the script id goes to enemyAggroStateUpdate(s32, s32, s32) unchanged (`move a2,s0` 0x378); the move flags are held wider than u16 and narrowed at the u16 parameter of actorMoveWithinZone (`andi a3,s0,0xffff` 0x2b8; a u16 local loses that andi), i.e. an s32 like x.
Live regions (one switch, different cases, every role stored before its read): move flags 0x298-0x2b8 (lines 93-98, case 0x33); script id 0x360-0x378 (lines 111-116, case 0/4); fade step 0x48c-0x4d4 (lines 143-153, case 0x37); light step 0x5f8-0x638 (lines 159-165, case 0x37). Disjoint.

### Hidden-reuse check (director item, 2026-11-25c): every other local
| local | type | values (lines) | target | outcome |
|---|---|---|---|---|
| `ret` | u8 | 0 (46), 1 (119) | home 79(sp): `sb zero,79(sp)` at entry | one role (return value): checked, no census |
| `yawDiff` | s16 | yaw - moveYaw or moveYaw - yaw (48/50) | home 76(sp): `sh t6/t7,76(sp)` | one role: checked |
| `step` | s32 | gCurrentActor->subState (141, 159, 170, 174) | each a fresh load after a `gCurrentActor` reload: `lbu a0,341(s0)` 0x47c, `lbu v1,341(s0)` 0x5f8, `lbu a0,341(s0)` 0x6bc, `lbu a0,341(s0)` 0x6fc | same role (R9): checked, no census |
| `lightRadius` | f32 | `(22.0 - tmp) / 20.0 * 200.0` (165), clamp 200.0f (167) | | same role (clamp): checked |
| `alpha` | u32 | one assignment (153) | | one role: checked |
| `angle` | s16 | one assignment (121) | | one role: checked |
| `size` | s32 | 0x22 or `(step * 6) & 0xFF` (149/151) | | one role: checked |
| `tmp` | s32 | move flags (94/96), script id (112/114), fade step (144/146), light step (161/163) | | flags/id: census above (untagged); fade/light: ORIG (two values spill to one home 64(sp)) |
| `aggroRange`, `unused` | s32 | parameters, never assigned | | not reused |
Result: no other untagged unrelated-role reuse; nothing tagged, no copy-only site.

### Fade/light split of `tmp` (supplementary to the ORIG; 254 bodies, current body)
Function slots: before `ret`, after each of `ret yawDiff step lightRadius tmp alpha angle size`; block scopes: `case 0x37` block, `if (step >= 2)` block, bare block over the role's lines (fade 143-153, light 160-165); each plain and `register`; types s32/s16/s8/u16/u8 (every width holds the values: fade step 0..125, light step 0..22; the target converts an s32 with `cvt.d.w` at 0x4d4/0x638). Scores: census3/try3.txt (a position group scores the same plain and `register`); diffs read (diffs3/): fade s32 before ret, after ret, after lightRadius, after tmp, every block scope; light s32 before ret, after ret, after tmp; the narrow-width block scopes listed below; rows marked "score only" were not diffed.
| role | type | position | full | what moved (deadsweep score --diff) |
|---|---|---|---|---|
| fade step | s32 | before ret, after ret/yawDiff/step/lightRadius | 74-75 | frame 0x50 -> 0x58 (`addiu sp,sp,-88`, every home +8); the fade stores/reload at 64(sp) 0x494/0x49c/0x4a0/0x4b8 gone (fade in a0, `bgez`/`move a0`) |
| fade step | s32 | after tmp/alpha/angle/size, 3 block scopes | 58 | frame kept 0x50; fade stores/reload at 64(sp) gone (fade in a0), the light step keeps 64(sp) (`sw t6/v1,64(sp)`, `lw t7,64(sp)`) |
| fade step | s16 / s8 | before ret .. after lightRadius / after tmp .. size and blocks | 18-34 / 15 | blocks (diffed s16 and register s8): frame kept 0x50, fade stores/reload at 64(sp) gone, fade narrowed in a0 (`sll a0,v0,0x10`/`sra t1,a0,0x10`; s8 0x18) |
| fade step | u16 / u8 | before ret .. after lightRadius / after tmp .. size and blocks | 114-128 / 111 | blocks (diffed register u16/u8): frame kept 0x50, fade stores/reload at 64(sp) gone, extra `andi a0,v0,0xffff`/`0xff` |
| light step | s32 | before ret, after ret/yawDiff/step/lightRadius | 54-58 | frame 0x50 -> 0x58; light stores/reload 0x618/0x61c/0x620 gone (fade stays in the home) |
| light step | s32 | after tmp/alpha/angle/size, 3 block scopes | 38 | frame kept 0x50; light stores/reload at 64(sp) gone, fade keeps 64(sp) |
| light step | s16 / s8 | function slots before tmp / after tmp and blocks | 43-60 / 40 | score only |
| light step | u16 / u8 | function slots before tmp / after tmp and blocks | 68-85 / 65 | score only |
| both steps | s32 / u8 | after tmp | 80 / 136 | score only |
No-local spellings: fade inline ternary in the alpha expression (`< 0`, `>= 0`, against 0 and 0x82) 76; fade if/else around the alpha assignment 89; light inline ternary (`>=`, `>`, `<`) 38-39; light if/else around the radius 49; `step` clamped in place (`step = 0x16`) 39; both ternaries 98. BASE 0.
Reading: no split, width or spelling reproduces the target; the frame grows (before `tmp`) or the split step leaves the shared home (after), so the shared 64(sp) home is the original's one local (rulings.md:100 ORIG leg "two values spill to one home"). Q1507's BA790 example (fade local shrinks the frame 0x50 -> 0x48, measured on the 44b87890 body) does not reproduce on the current body.

## Untried ideas
None left for the two census sites (fixed); `x` renamed `tmp` with the role list on its declaration.

## Evidence
Frame 0x50 (`addiu sp,sp,-80` at 0x0). x home 64(sp): `bgezl v0` 0x490 / `sw v0,64(sp)` 0x494, `sw zero,64(sp)` 0x49c, `sw v0,64(sp)` 0x4a0, `lw t1,64(sp)` 0x4b8; `sw t7,64(sp)` 0x618, `sw v1,64(sp)` 0x61c, `lw t8,64(sp)` 0x620. Move flags in s0: `li s0,2` 0x298, `move s0,zero` 0x2ac, `andi a3,s0,0xffff` 0x2b8, `jal actorMoveWithinZone` 0x2c4. Script id in s0: `li s0,588` 0x360, `li s0,589` 0x370, `jal enemyAggroStateUpdate` 0x374, `move a2,s0` 0x378. gCurrentActor reloaded into s0 after each call (`lui s0`/`lw s0,0(s0)`).
Quirks: Q1122, Q1507 (its BA790 frame-shrink example does not reproduce on the current body: 0x50 -> 0x58 or kept), Q1517, Q0181, Q1055 (one candidate across disjoint uses), Q0151 (`lbu a0; move v1,a0` for the step re-reads).
