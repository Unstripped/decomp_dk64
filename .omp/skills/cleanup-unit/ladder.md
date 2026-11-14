# The ladder (as `tools/quality.py` implements it)

`drafts/quality/` is append-only; one event per (site or function, method). `status`
computes everything below from it; this file explains what it prints.

## Sites

Key `<seg>:<VRAM8>:<kind>:<sha1(normalized code)[:6]>[#n]` (`#n` = ordinal among identical
lines of the function). Untagged sites (found by `clint.py metrics`, no `// FAKE` on the line)
have `u` as the first hash character: `global:8060ABCD:dead-if:u3f2a1`. A `warning` site hashes
its cfe warning code plus the line's normalized code. Kinds:

|kind|recognised by|
|---|---|
|`dead-if`|`if (...) {}` on a FAKE line, or an empty-then `if` without else (AST)|
|`volatile`|`volatile` on a FAKE line, or a volatile local (AST)|
|`do-while0`|`do {` / `while (0)` on a FAKE line|
|`dead-store`|single-assignment FAKE line whose comment says dead, kill, no-code, extra web or ghost|
|`noop-arith`|`^ 0`, `\| 0`, `& 0`, `* 0`, `+ 0` (FAKE line or AST)|
|`comma`|`(0, ` on a FAKE line|
|`punned-cast`|`*(T *)&x` (FAKE line or AST)|
|`proto-steer` / `implicit-steer`|`// FAKE: callee prototype steer` / `implicit declaration steer`|
|`proto-type`|a `// PROTO:` line|
|`goto`|every goto statement (AST), tagged or not|
|`other`|any other FAKE line; review findings (key from `sweep <copy> --copy-of <src>` output)|
|`warning`|an IDO `cfe: Warning` line of the file's matching compile (`tools/cwarn.py`), on the line it names (file-scope lines: the first later function naming the symbol); `status` shows `[W<code> <msg>]`|

`// LAYOUT:` lines are not sites (as1 line-order scheduling is ordinary source layout), nor are
`// ORIG: <what the target does at 0x<offset>>` lines (a construct the target asm really performs);
an `// ORIG` line without a cited offset stays a hack site.

## Methods

|id|who|what|
|---|---|---|
|`remove`|sweep|delete removable sites (lone dead ifs, `do {` … `} while (0);` pairs and one-line `do {} while (0);`, `(void)x`, dead stores, `volatile`): alone, all together, pairs, triples; a site with no such edit (a dead test or `do {` sharing its line with other statements) is recorded `nohit` (`no removal`)|
|`plain`|sweep|the plain rewrites of one tagged line (`^ 0`, `\| 0`, `+ 0`, `& 0xFFFFFFFF`, `(0, `, `*(T *)&x`, `(s16)(s32)`, `[i * 1]`, and the low-part puns `((T *)&x)[n]` / `*((T *)&x + n)` → `x` for n 1–9, Q0594)|
|`cond`|sweep|`!= 0`↔bare, `== 0`↔`!x` flips with removals (`no removal` without one)|
|`classify`|sweep|dead-if → `if (<int local>) {}`; match = class 1 (`kept`), none = class 2; a dead test sharing its line is `nohit` (`no guard`). By-hand removals/flips of such sites go into the `diagnose` note: the next sweep's event supersedes a hand-recorded sweep method|
|`recipe`|sweep|`tools/variants.py scan` (swapped comparison operands, float literal suffixes, local widths, adjacent declaration swaps) around the all-removal, each single removal when there are several, and each site's first plain rewrite; a zero that passes `fdiff --reloc-ok` + uninit is a `hit`; a site with no removal or plain rewrite is `nohit` (`no removal`)|
|`consolidate`|protos.py|remove the file's declaration in favour of the shared header|
|`diagnose`|agent|uopt/as1 diagnosis; `quirks=Q....` required|
|`permute`|agent / `permbatch`|optional, in no ladder: `tools/permute.py run -j 2 --seconds 900` (hack-free weights, never stops on zero) or the offline batch (`quality.py permute-candidates`, `permute.py batch`); `seconds=` (≥600 unless `best=0`), `base=`, `best=` required; the lead checks `seconds=` against `setup.json` → first `output-*` mtime and `base=` against the log `Setup: ... baseline N` (r34 corrected 6)|
|`reconstruct`|agent|rewrite of the function from scratch around the steering|
|`goto-hand`|agent|structured-control rewrite of a goto|
|`views`|agent|types phase result (function-level)|
|`names`|agent|naming phase result (function-level)|
|`review`|agent|whole-function checklist (function-level, required for every function)|
|`retype`|agent|give the declarations their real types so the warning disappears|

Outcomes: `hit` (sweep found a match, not yet applied), `fixed` (merged; a `review` with no edit is `nohit`), `nohit`, `kept`,
`blocked`. `kept` only for `classify` with note `class 1`, for `goto-hand` with a note citing
the shared-tail pattern (Q0591), and for `retype` with `note="tried <change>; fdiff=<1|3>"`.
`retype` outcomes are `fixed`, `kept` or `blocked` (note naming the missing header/owner change);
warning sites take no other method.

Tooling rules (were Q0626/Q0634/Q0638):
- `fdiff.sh <copy> <src> FUNC` prints no diff lines when a long function's first difference is past
  asm-differ's window: trust its exit code, or diff with `objdump -drz`. The permuter scores a
  commutative `beq` operand swap as 0: confirm every `best=0` output with fdiff before applying it.
- A `best=0` or review rewrite that only swaps one steer for another (`if (1) {}`, empty do-while, goto,
  `(0, x)`, `& 0xFFFFFFFFu`, a copy temp, a selector local of another width in place of a dead read) is `nohit`; keep the tagged site.
- The permuter's pycparser rejects `x * sizeof(T) + sizeof(s32)` and a one-line `p = x; do {`:
  rewrite them in the permuter base only, then translate the hint back into the copy.
- Never write `'` in a `//` comment (FAKE notes): asm-processor/cfe read it as a char literal (compile
  error); two in one comment cancel out and hide the code between them (false matches).

## Required fresh methods per kind

|kind|exhausted when fresh|
|---|---|
|`dead-if`|`remove`, `cond`, `classify`; class 1 (`kept`) is terminal, else also `recipe`, `diagnose`|
|`volatile`, `do-while0`, `dead-store`|`remove`, `cond`, `recipe`, `diagnose`|
|`noop-arith`, `comma`, `punned-cast`, `other`|`plain`, `recipe`, `diagnose`|
|`proto-steer`, `implicit-steer`|`consolidate`, `diagnose`|
|`goto`|`goto-hand` (`kept` with Q0591 evidence is terminal)|
|`proto-type`|never (types phase: record `views` `blocked` with the reason)|
|`warning`|`retype` (`fixed`; `kept` only with `note="tried <change>; fdiff=<1\|3>"`; `blocked` keeps it open)|

A function with 3+ non-kept sites (warning sites not counted) also needs a fresh function-level `reconstruct` — also when tagging pre-existing hacks lifts it to 3 (r34 3E10).

## Freshness

- `remove`, `plain`, `cond`, `classify`, `recipe`, `consolidate`, `views`, `names`: fresh while the
  function's `fp_local` (its source extent + the file's top-level non-function text) and `fp_hdr2`
  (only the `include/` declarations, types and macros the function reaches, so a regenerated
  proto header or an edited struct stales only their users; a function reaching a `##`
  token-pasting macro, whose pasted names are untracked, uses the whole-header hash instead and
  is never carried by `carry --header-carve`; plain `carry` follows a paste with a literal side
  (`GBL_c##clk` reaches every `GBL_c*`) and skips only two pasted parameters, and treats a type
  moved unchanged between the `.c` and an `include/` header as unchanged (`moved to <h>, identical`)
  and a prototype/variable declaration respelled with the same canonical type as unchanged
  (`<name> declaration respelled|moved to <h>, same type`; K&R vs prototyped is a change),
  and a file-local typedef/record/enum renamed with an otherwise identical declaration (same
  renamed text and `clint.record_layout`) as unchanged (`type <old> renamed <new>, identical`);
  events from before it fall back to
  `fp_hdr`, every included header) equal the current values. `carry --rev REV --header-carve`
  re-stamps these across header edits (REV parsed with REV's headers) for functions whose
  `fp_local` and site keys are unchanged when every reached declaration that changed is a record
  keeping size, alignment, field offsets and field types (`clint.layout_diff`, types on; padding
  carved into named fields; a padding array shrunk around them, to a shorter array or to a scalar
  of its element type, unless `sizeof` is reached or, for a scalar, the field is accessed); a
  changed prototype, macro, typedef, enum or layout keeps them stale and is listed.
- `diagnose`, `permute`, `reconstruct`, `goto-hand`, `retype`, `review`: fresh while `fp_local` is equal
  and no `knowledge/ido` file committed after the event names the function (its current or
  `func_ADDR` name). Note similarity never stales: top-8 note hits re-ran the same attempts for
  rounds (r35-36 permute: 96 ks for one fix); a retry must instead name what is new (`new=`).
  An entry naming the function whose `unit` (`quirks.py add --unit`) produced the event (a carried
  event: the event it copies) does not stale it: that unit's agents had the finding (round 34:
  Q0704-Q0719 staled 52 own-run rungs so). Tag at filing: a later `unit` edit is a new commit.
  Still write notes in concrete register/offset terms (`$s1 holds sp+0x34 across the jal`):
  the next worker reads them in `history` and the dossier.
- A method counts through its newest event by time (carried events keep their original time) if
  that is fresh and not `blocked`. A fresh `hit` makes the site OPEN `next=apply` (the sweep found
  a match nobody merged yet).
- `carry` re-stamps a body that differs only by local/param renames even beside unrelated
  file-scope edits (abee1d87, `(renames; unrelated file-scope changes only)`), and renamed fields of
  an `include/` record that keep its layout (8220de44); `--func NAME` limits it to named
  functions so a second pass never duplicates events. A fold (`D_x` → `base.field`), a renamed
  site line (new key) and a reached type change are never carried: those go to re-review.

## Function state

EXHAUSTED = a fresh `review` event, every site fixed or exhausted, and (3+ non-kept sites) a fresh
function-level `reconstruct`. Without a fresh `review` the function is OPEN `next=review`, even
with zero sites. `status` prints per site `✓`, `stale` or `—` per required method and
`OPEN next=<first missing method>`. Sites inside `#ifdef NON_MATCHING` blocks are not tracked;
a file-scope FAKE line (a declaration) belongs to the first later function naming its symbol.

## LEDGER line format (`quality.py record --batch`)

```
<site-key|func:<seg>:<name>> <method> <outcome> [quirks=Q1,Q2] [seconds=N] [base=N] [best=N] [commit=H] [note="..."] [new="..."]
```
`review` note: `fake=<kept>/<removed> goto=<n> casts=<n kept> views=<ok|n left> protos=<ok|n steer> temps=<ok|n> names=<n m2c left> uninit=<0|n> warn=<n left>`.
A site fixed in the copy no longer exists at HEAD: `record --base <copy base>` accepts its key.
Retry rule: a `diagnose`/`permute`/`reconstruct`/`goto-hand` line on a site (reconstruct: the
function) that another unit or agent already tried with that method needs `new="<what this attempt
tried that earlier ones did not>"`; `record` refuses it otherwise (a re-record of the same unit and
agent is exempt). `record --model provider/model[:level]` stores the worker's model on every event
(`rank` weighs attempts by it; older events use `drafts/quality/models.jsonl`, `backfill-models`);
`--skip-missing` drops lines whose site is gone. `tools/merge_record.py` runs both.
