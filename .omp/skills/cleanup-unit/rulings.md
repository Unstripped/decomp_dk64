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
- a selector local at its use
- a local holding one field read for use (Q0601)
- a pointer local to a global used for EVERY access
- a per-role local in a dropped local's or pads' slot
- declaration order chosen for the frame (9BF30)
- a subject-first symmetric `==` of two fields in fresh view-retype code (F0D0)
- bare truth tests
- a flag's natural unsigned type
- a mask written at its field's width
- a byte-view local used for every offset access beside the typed pointer (55B20 `u8 *file`)
- a constant-valued local the target converts or uses at run time in a way no literal reproduces (Q0814: CEAE0
  `li`/`mtc1`/`cvt.s.w`, every literal folds to `lui`)
- `/ 2.0` where the file family halves that way and `* 0.5` fails (126260).

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

## ORIG and LAYOUT

- `// ORIG:` replacing `// FAKE` needs the cited target-asm offset (check it; K&R declarations, -g puns, a
  per-file extern type the target proves qualify).
- FAKE → `// LAYOUT:` with line-order evidence is a drop.

The offset must show the tagged line's OWN executed operations (a wider
call-site declaration's caller-side `andi`, an extra argument register), never register numbering alone (136820 5fb2de), nor a computation
a dead test keeps alive (stays FAKE, `diagnose nohit`; 627052); pre-switch constant store: compile without it first. A `T x[1]` memory
home is ORIG only with a cited store-without-reload offset (6AD90 `swc1` 0x3910, compare on the register copy). A reused local/parameter
is ORIG when the value is stored to its own home slot (not the temp area below the named homes) and a separate local grows the frame (CEAE0
f73438, arcade ff5952), or two values spill to one home (42630 83069d#2); a shared register is not.

## Re-reads, widths, expressions, merged constructs

Load count: a field re-read (`p->f`
while a local holds it) is ordinary only when the target loads the field again; cite the loads (36880, 15050 0x170: one load, FAKE).
Width: narrow only with a byte/halfword load/store of the value or the type the code uses for it (0/1 flag u8, s16 sound ids; 7130: steer).
`(d = X) > best` whose value the target uses is ordinary C, a comma expression is not; a `volatile` pointee of a cross-thread busy-wait poll
(104F0 77df56) is ordinary, volatile locals or reads elsewhere stay FAKE. A sentinel `switch` or several steers merged into ONE tagged
construct are natural only when every case value/compare it adds is in the target (9DD70 `li a3,6`/`li t0,7`; Q0844/Q0845); else it is
invented code and the base sites stay (936B0 `case 0`, 7BBD0 `if (&flag) {}`). The lead checks the compares in the expected asm.
