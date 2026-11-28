# Tag rulings (ordinary C, steer, ORIG, LAYOUT)

Single source for whether a construct in matched C is ordinary C (untagged), a steer (`// FAKE`), source
layout (`// LAYOUT:`) or original behaviour (`// ORIG:`). Workers apply it before tagging, the lead at merge
(SKILL §5.6). Session close adds new rulings here (SKILL §6 step 5): replace or merge text, cap 150 lines.

## Ordinary C (untagged, even as the only match)

- a load-bearing guard `continue`/`break`
- a one-path store
- an index loop over a global table
- one quantity refined in place (104F0 `offset = sector << 3`)
- an assignment in a test whose values the target uses
- one macro for every recomputation
- function-local statics
- a selector local at its use, also at a narrow unsigned width when the target computes and tests that exact value (478F0
  csCmdStepSequenceProgress `u8 odd = st[1] & 1; if (odd)`: `andi` 0x7054, `beqz` 0x7068; width sensitivity alone is no swap, R6 2026-11-18c)
- a local holding one field read for use, used one or more times (Q0601): a single-use read-modify-write copy whose field the target
  loads once and uses (A2F10 `flags = actor->flags; actor->flags = flags | 4;`: `lw` 0xbc, `ori` 0xc8, `sw` 0xcc; R10 2026-11-18c; F0D0
  bossMainStep case 6 `count = byteVars[0]; if (count) byteVars[0] = count - 1;`: one `lbu` 0x1dcc, 2026-11-25c)
- a pointer local used for EVERY access to a global, an element or an embedded sub-struct (R4 2026-11-18c, offset-first `addu`; jetpac
  jetpacUpdatePlayerMovement `JetpacHead *head = &player->head` for all 72 head accesses, R-jetpac 2026-11-25c); only the steered
  lines through the local while other accesses stay direct is a hack swap (R3)
- a per-role local in a dropped local's or pads' slot, or a narrow role in an alignment hole when the value's real type is narrow (55B20
  mapChunkTraversePortals `s16 target` after two u8 homes; A6280 `s16 id` = the callee's return type; 2026-11-25c); a width picked
  only to fit a hole is a steer
- one local holding two values of the SAME role, each a real value the target uses (2F550 `denom`, divisor of `dot` in both
  `dist = dot / denom` and `t = dot / denom`: `div.d` 0x43f4/0x44f4; E550 `yo`, Q0896; R9 2026-11-18c); unrelated roles are a steer (R5)
- a loop counter reused by a later loop that reinitialises it, consecutive or not, no other role folded in, the then-unused local
  deleted (pad only if the frame needs it) (1630 noExpPakThread vsync `x = 0` = `move s0,zero` 0x204; Q1224; R7 2026-11-18c;
  non-consecutive loops: 55B20 mapChunksInitFromMapData `i`, director 2026-11-24)
- a one-case selector switch (case value + default) on a mode/selector byte the codebase switches on elsewhere, adding no compare
  beyond the target's single test (CEAE0 playerUpdateCommon `switch (gDemoPlaybackState)`: `lbu` 0x84c, `bnezl` 0x850; R3 2026-11-18c)
- declaration order chosen for the frame (9BF30)
- a subject-first symmetric `==` of two fields in fresh view-retype code (F0D0)
- bare truth tests
- a flag's natural unsigned type
- a mask written at its field's width
- a byte-view local used for every offset access beside the typed pointer (55B20 `u8 *file`)
- a constant-valued local the target converts or uses at run time in a way no literal reproduces (Q0814: CEAE0
  `li`/`mtc1`/`cvt.s.w`, every literal folds to `lui`)
- `/ 2.0` where the file family halves that way and `* 0.5` fails (126260).
- a pointer-sum operand order the target's offset-first `addu` proves (Q0813; 136820 faultDrawGlyph `xoff + (u16 *)fb + yoff`, R1 2026-11-18b).
- a cast whose conversion the target executes, never `// ORIG:` either (D5E10 playerStateStationaryInteraction `(f32)rampLevel * 0.015`:
  `cvt.s.w` +0x1c8, `cvt.d.s` +0x1e0; 42630 csCmdExec `(u32)pitch / 127.0` unsigned fixup, `(f32)cmd->a` into an s16 field; R1 2026-11-24)
- a value recomputed into the same local where the file spells it that way elsewhere (6AD90 collisionTestStaticMeshFloor
  `val = 0.0 - (...); h2 = ((2000.0 * val) - 1000.0) + offset;` as collisionTestDynamicActorFloor x3; uopt CSEs it; R4 2026-11-24);
  a textbook expression with a single-use call inline (478F0 csCmdBobbingLights lerp `a + (b - a) * (mathSinF(..) * 0.5 + 0.5)`, 2026-11-24)

## Steers (keep `// FAKE`)

- A respelling that replaces a pun but was chosen for codegen keeps its tag (Q0816).
- a trailing/`else` continue
- an empty `default:`
- a dead clamp keeper
- any other constant-valued local
- a redundant alias (a second copy of a value already in a local: a swap needing one is rejected), also a cursor copy of a parameter
  that is never read again (CC800 kongChainInit `KongChain *chain = chains;`, director 2026-11-24)
- a fully dead declaration default (every path stores the local before any read, the default returns), also when `= 0` matches too:
  Q0795 covers only initialisers live on some path (CC800 kongChainInit dc42ce `s32 count = 1; s32 n = 4;`, R1 2026-11-24b)
- a value cast chosen for codegen, also as the result cast of a one-recomputation macro: ordinary only when dropping it changes
  the computed value for some reachable input (7CA80 actorAllocate `ALIGN8_U16` `(u16)`: headerSize <= 0x188 over all 344 component
  lists, so the cast only steers registers; director 2026-11-20)
- an operand-order/width/view respelling
- a single-use local whose only effect is a frame word (copy-propagated, `{ s32 _g; }` there matches too: a pad, 36880 1a2082).
- a local reused for an UNRELATED role whose value never reaches its own home, unless it passes the census rule below (3E10
  menuDrawHighScoreTable flag + loop counter in s2, M39; 126260 commandApplyToLight `factor` = the falloff base, then
  `127.0f / dist`, not R9's same-role divisor; arcade/0 arcadeUpdateRetractableLadder `step`: register-only evidence. No longer
  steers: 3E10 menuUpdateElementTargetAndColor `radius = mathSinF(t)` (member-read colour + compound `+=` wobble, 0x96dc; 2026-11-25c)
  and ACDC0 hudPauseMenuIconUpdate wobble sines (census passed; the scratch f32 renamed from `radius`, 2026-11-25c))
- a width respelling plus a no-op value cast (F56F0 `u16 timer; index = (u8)timer - K`, declined 2026-11-18c)
- a buffer/array size changed to free a frame word: ordinary C only with a proof from the code (not game data) that every write fits;
  otherwise rejected as a behaviour change (FCCD0 slotQueueDrawLabel `text[8]`->`text[4]`: coins via F9450.c:621 and the slot-9
  golden-banana sum are uncapped; R11 2026-11-18c). Accepted: 9DD70 actorSagWaveUpdate `posOffsets[32]`->`[28]` (only callers pass
  8 and 0x1C, every write indexed below numNodes; R3 2026-11-24)

## ORIG and LAYOUT

- `// ORIG:` replacing `// FAKE` needs the cited target-asm offset (check it; K&R declarations, -g puns, a
  per-file extern type the target proves qualify).
- a target-proven per-file callee declaration keeps `// ORIG:` and the file does NOT include the shared proto header that would need a
  new `#define PROTO_SKIP_<f>` for it (boss/0 actorMoveWithinZone; R2 2026-11-24): new skips are only `// FAKE: callee prototype steer`
  or `// PROTO:` (AGENTS.md). Existing `PROTO_SKIP_<f> // ORIG:` lines paired with such a declaration stay (42630 hudSpawnCountdownTimer,
  modelAnimEntrySetUnkC, effectSetDepth).
- FAKE → `// LAYOUT:` with line-order evidence is a drop. Evidence: the statements on ONE line match in both orders; for a dependent
  pair (the second reads the first) splitting the line changes only the relative order of the two statements' own instructions
  (36880 modelPendingQueueInsert cd1810 `slots = gModelSlots; obj = slots[idx].csState;`: the split swaps only `sw t8,0x34(sp)` and
  `addu t9,t8,t7` at 0x99a0/0x99a4; R2 2026-11-24b).
- an address-compare loop exit (`&a[i] < &a[N]`) is `// ORIG:` when the target performs an ordered `sltu` (+ `bnez`/`bnezl`) against
  a hoisted end address that no index spelling emits (a literal bound unrolls or is LFTR'd to `bne`/`bnel`; Q1629): the opcode is
  the evidence, not register numbering (42630 csModelIdTableReset cc0f6b `sltu` 0x18; C0EE0 enemyGridStateStep 706cd2 `sltu` 0x4dc,
  `bnezl` 0x508; R4 2026-11-24b).
- an empty `default:` whose own block the target keeps (bound-check + gap entries branch to a distinct address) is `// ORIG:` citing
  that block (director 2026-11-18b: vsprintf 0x139c `lbu/li/move` before the loop test 0x13a8, bound check 0x4c4; EFDC0
  playerStateSetFlagsByActorType +0x16c..+0x190 before the join +0x194, no gap entries; C0EE0 enemyGridStateStep: the one reload
  `lw a3,0(t2)` at 0xa58 before the join 0xa5c, cases branch to 0xa60 because the join's first op fills their delay slot; removal
  sends bound check and gap entry to the join, 2026-11-20 f4051566; 478F0 csCmdPeriodicSfxAlloc: `beqz at,1708` 0x14f8 -> own block
  0x1708 `lw a2,4(v1)` before the join 0x170c, 2026-11-24 M5); a default at the join address stays a steer.

The offset must show the tagged line's OWN executed operations (a wider
call-site declaration's caller-side `andi`, an extra argument register), never register numbering alone (136820 5fb2de), nor a computation
a dead test keeps alive (stays FAKE, `diagnose nohit`; 627052); pre-switch constant store: compile without it first. A `T x[1]` memory
home is ORIG only with a cited store-without-reload offset (6AD90 `swc1` 0x3910, compare on the register copy). A reused local/parameter
is ORIG when the value is stored to its own home slot (not the temp area below the named homes) and a separate local grows the frame (CEAE0
f73438, arcade ff5952, arcade/0 arcadeUpdatePlayerEntity `i` sp+0x3c, frame 0x48 -> 0x50), or two values spill to one home (42630 83069d#2,
BA790 `x` sp+64); a shared register is not. An unrelated-role reuse that never reaches the home is ordinary C (untagged) only when
all three hold and the dossier records the census (R-oildrum 2026-11-25c, Q1666; Q1122; arcade/0 arcadeUpdateOilDrumEntity `n`, ACDC0
hudPauseMenuIconUpdate cf674d): (1) splitting the second role into its own local changes the frame or moves a home/spill at EVERY
declaration position (function scope before/after each declaration, block scope; `register` compiles to the same object as the plain
declaration, so one measurement covers both: DAA0 bossSpawnerUpdate `z`, 76 positions), the move caused by the new local's own
stack slot (spill temps displaced by it count: ACDC0 IconUpdate, 3E10 `t`, arcade/0 arcadeUpdateDonkeyKongStage4 `tmp`: the split's cfe home
pushes the shared switch temp -8 -> -12 and the t0 spill 0x2c -> 0x28 at all 26 positions); (2) every ordinary-C spelling without a local for it fails
(inline at each use, direct field/array write, pointer local; a function-local static always adds a .bss store, Q1680); a matching spelling that is itself a steer (a re-read the target does
not do, a value-changing width) does not fail it (3E10 `t`: stick_x read once, `lb` 0x9114); (3) the two roles share the local's type
and live in disjoint regions. Register-allocation-only evidence does not qualify: adjsave, $f0 vs $f2, or a split that keeps the frame
and every named home where the change comes only from a register reassignment, also a narrow role in an alignment hole whose only
effect is spill traffic of that reassignment (12E800 enemyAggroStateUpdate `near`, FAKE stays), or a frame change that comes only from
dropped callee-saved FPR saves (race/0 raceOpponentFollowWaypoints `vx`/`vz`: $f20/$f22, frame 0x58 -> 0x50; R1 2026-11-26). A register-only
local declared after the lowest stored local takes no frame word, so such positions always keep the frame (126260 commandApplyToLight
`factor`, DAA0 bossFollowerActorUpdate `id`, bonus/2690 bonusSearchlightSeekGameUpdate `z`/`velX`: part 1 fails, FAKE stays). BA790
chaserEnemyStep passes because the split drops the 64(sp) home stores. A register change on top of stack evidence does not disqualify
(ACDC0 3490af/dddb5b). Q1122's own `bits` failed (2): `mask |= 1 << j`; D5E10 playerStateLandRecover's frame role went inline (field
reloaded at each compare). A hidden reuse found by the census sweep that fails is tagged (bonus/2690 aim `z` b25205, R2 2026-11-26).

## Re-reads, widths, expressions, merged constructs

Load count: a field re-read (`p->f`
while a local holds it) is ordinary only when the target loads the field again; cite the loads (36880, 15050 0x170: one load, FAKE).
Width: narrow only with a byte/halfword load/store of the value or the type the code uses for it (0/1 flag u8, s16 sound ids; 7130: steer).
`(d = X) > best` whose value the target uses is ordinary C, a comma expression is not; a `volatile` pointee of a cross-thread busy-wait poll
(104F0 77df56) is ordinary, volatile locals or reads elsewhere stay FAKE. A sentinel `switch` or several steers merged into ONE construct
are natural (untagged) only when every case value/compare it adds is in the target (80150 transformBarrelUpdate `switch (gCurrentMap)`
sentinel cases; Q0844/Q0845); else it is invented code and the base sites stay (936B0 `case 0`, 7BBD0 `if (&flag) {}`, 13980
schedHandleRetrace `osRecvMesg(...) == -1 || (s32)msg == -1`, R2 2026-11-18c). A merge of several steers whose added case values the
target lacks stays one FAKE (9DD70 actorCheckAlwaysFalse e999c8 `case 6: case 7:`: as1 deletes its `li a3,6`/`li t0,7`, 0x16e0-0x1754
compares only 2/3; R8 2026-11-18c). The lead checks the compares in the expected asm.

## Split-label folds (R1-27/R2-27, director 2026-11-27)

A split splat label folds into its parent's spelling (`rename.py fold`, `fdiff --reloc-ok`) when the parent spelling, or a pointer
local the function holds for every access of that object (Q0601), reproduces the target's separate `%hi/%lo`: jetpac 4FC0
`JetpacPlayerActor *player = &jetpacGame.player;` folds D_8002F054 + D_8002F078 together as `player->head.y + player->head.boxY2`
(ordinary C, R2-27; Q1604). A new local whose only role is to reproduce a separate base symbol is a view chosen for codegen (55B20
`MapSearchEntry *e = &gMapSearchTable[2];` for D_807F72B8 while its siblings D_807F72A1/A4/B5 fail by base CSE: the labels were
distinct symbols), and a single-label fold that its siblings cannot share is no fold evidence (R1-27): the labels stay held.
