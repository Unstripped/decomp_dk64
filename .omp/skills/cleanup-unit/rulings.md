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
  loads once and uses (A2F10 `flags = actor->flags; actor->flags = flags | 4;`: `lw` 0xbc, `ori` 0xc8, `sw` 0xcc; R10 2026-11-18c)
- a pointer local to a global used for EVERY access, also block-scoped to an element (3E10 `MenuUiRgba *color = sMenuKongColors + idx;`
  for all three reads, offset-first `addu` 0x96dc; R4 2026-11-18c)
- a per-role local in a dropped local's or pads' slot
- one local holding two values of the SAME role, each a real value the target uses (2F550 `denom`, divisor of `dot` in both
  `dist = dot / denom` and `t = dot / denom`: `div.d` 0x43f4/0x44f4; E550 `yo`, Q0896; R9 2026-11-18c); unrelated roles are a steer (R5)
- a loop counter reused by a CONSECUTIVE loop that reinitialises it, no other role folded in, the then-unused local deleted (pad only if
  the frame needs it) (1630 noExpPakThread vsync `x = 0` = `move s0,zero` 0x204; Q1224; R7 2026-11-18c)
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

## Steers (keep `// FAKE`)

- A respelling that replaces a pun but was chosen for codegen keeps its tag (Q0816).
- a trailing/`else` continue
- an empty `default:`
- a dead clamp keeper
- any other constant-valued local
- a redundant alias (a second copy of a value already in a local: a swap needing one is rejected)
- a value cast chosen for codegen
- an operand-order/width/view respelling
- a single-use local whose only effect is a frame word (copy-propagated, `{ s32 _g; }` there matches too: a pad, 36880 1a2082).
- a local reused for an UNRELATED role whose value never reaches its own home (3E10 menuUpdateElementTargetAndColor `radius =
  mathSinF(t)`: the sine is used from f0, R5 2026-11-18c; 3E10 menuDrawHighScoreTable flag + loop counter in s2, M39; 126260
  commandApplyToLight `factor` = the falloff base, then `127.0f / dist`, not R9's same-role divisor); ACDC0
  hudPauseMenuIconUpdate `sc` is the same construct, untagged: tag it in the next ACDC0 pass
- a width respelling plus a no-op value cast (F56F0 `u16 timer; index = (u8)timer - K`, declined 2026-11-18c)
- a buffer/array size changed to free a frame word: ordinary C only with a proof from the code (not game data) that every write fits;
  otherwise rejected as a behaviour change (FCCD0 slotQueueDrawLabel `text[8]`->`text[4]`: coins via F9450.c:621 and the slot-9
  golden-banana sum are uncapped; R11 2026-11-18c)

## ORIG and LAYOUT

- `// ORIG:` replacing `// FAKE` needs the cited target-asm offset (check it; K&R declarations, -g puns, a
  per-file extern type the target proves qualify).
- FAKE → `// LAYOUT:` with line-order evidence is a drop.
- an empty `default:` whose own block the target keeps (bound-check + gap entries branch to a distinct address) is `// ORIG:` citing
  that block (director 2026-11-18b: vsprintf 0x139c `lbu/li/move` before the loop test 0x13a8, bound check 0x4c4; EFDC0
  playerStateSetFlagsByActorType +0x16c..+0x190 before the join +0x194, no gap entries); a default at the join address stays a steer.

The offset must show the tagged line's OWN executed operations (a wider
call-site declaration's caller-side `andi`, an extra argument register), never register numbering alone (136820 5fb2de), nor a computation
a dead test keeps alive (stays FAKE, `diagnose nohit`; 627052); pre-switch constant store: compile without it first. A `T x[1]` memory
home is ORIG only with a cited store-without-reload offset (6AD90 `swc1` 0x3910, compare on the register copy). A reused local/parameter
is ORIG when the value is stored to its own home slot (not the temp area below the named homes) and a separate local grows the frame (CEAE0
f73438, arcade ff5952, arcade/0 arcadeUpdatePlayerEntity `i` sp+0x3c, frame 0x48 -> 0x50), or two values spill to one home (42630 83069d#2,
BA790 `x` sp+64); a shared register is not. Near miss, stays FAKE until ruled: a split that keeps the frame but displaces a temp
spill (arcade/0 arcadeUpdateOilDrumEntity `n`: only the count stored to its home 0x24; a slot local moves the a1 spill 0x1c -> 0x18).

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
