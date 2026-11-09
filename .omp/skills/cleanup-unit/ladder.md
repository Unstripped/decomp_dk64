# The ladder (as `tools/quality.py` implements it)

`drafts/quality.jsonl` is append-only; one event per (site or function, method). `status`
computes everything below from it; this file explains what it prints.

## Sites

Key `<seg>:<VRAM8>:<kind>:<sha1(normalized code)[:6]>[#n]` (`#n` = ordinal among identical
lines of the function). Untagged sites (found by `clint.py metrics`, no `// FAKE` on the line)
have `u` as the first hash character: `global:8060ABCD:dead-if:u3f2a1`. Kinds:

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

`// LAYOUT:` lines are not sites (as1 line-order scheduling is ordinary source layout).

## Methods

|id|who|what|
|---|---|---|
|`remove`|sweep|delete removable sites: alone, all together, pairs, triples|
|`plain`|sweep|the plain rewrites of one tagged line (`^ 0`, `\| 0`, `+ 0`, `& 0xFFFFFFFF`, `(0, `, `*(T *)&x`, `(s16)(s32)`, `[i * 1]`)|
|`cond`|sweep|`!= 0`↔bare, `== 0`↔`!x` flips with removals|
|`classify`|sweep|dead-if → `if (<int local>) {}`; match = class 1 (`kept`), none = class 2|
|`consolidate`|protos.py|remove the file's declaration in favour of the shared header|
|`diagnose`|agent|uopt/as1 diagnosis; `quirks=Q....` required|
|`permute`|agent|`tools/permute.py run -j 2 --seconds ≥600`; `seconds=`, `base=`, `best=` required (a run stopped at `best=0` may be shorter)|
|`reconstruct`|agent|rewrite of the function from scratch around the steering|
|`goto-hand`|agent|structured-control rewrite of a goto|
|`views`|agent|types phase result (function-level)|
|`names`|agent|naming phase result (function-level)|
|`review`|agent|whole-function checklist (function-level, required for every function)|

Outcomes: `hit` (sweep found a match, not yet applied), `fixed` (merged), `nohit`, `kept`,
`blocked`. `kept` only for `classify` with note `class 1`, and for `goto-hand` with a note citing
the shared-tail pattern (Q0591).

## Required fresh methods per kind

|kind|exhausted when fresh|
|---|---|
|`dead-if`|`remove`, `cond`, `classify`; class 1 (`kept`) is terminal, else also `diagnose`, `permute`|
|`volatile`, `do-while0`, `dead-store`|`remove`, `cond`, `diagnose`, `permute`|
|`noop-arith`, `comma`, `punned-cast`, `other`|`plain`, `diagnose`, `permute`|
|`proto-steer`, `implicit-steer`|`consolidate`, `diagnose`|
|`goto`|`goto-hand` `kept`, or `goto-hand` + `permute`|
|`proto-type`|never (types phase: record `views` `blocked` with the reason)|

A function with 3+ non-kept sites also needs a fresh function-level `reconstruct`.

## Freshness

- `remove`, `plain`, `cond`, `classify`, `consolidate`, `views`, `names`: fresh while the
  function's `fp_local` (its source extent + the file's top-level non-function text) and `fp_hdr`
  (every `include/` header the file includes, transitively) equal the current values.
- `diagnose`, `permute`, `reconstruct`, `goto-hand`, `review`: fresh while `fp_local` is equal
  and no `knowledge/ido` file committed after the event names the function or is among the top
  8 hits for the event's note.
- A method counts through its newest fresh event unless that is `blocked`. A fresh `hit` makes
  the site OPEN `next=apply` (the sweep found a match nobody merged yet).

## Function state

EXHAUSTED = a fresh `review` event, every site fixed or exhausted, and (3+ non-kept sites) a fresh
function-level `reconstruct`. Without a fresh `review` the function is OPEN `next=review`, even
with zero sites. `status` prints per site `✓`, `stale` or `—` per required method and
`OPEN next=<first missing method>`. Sites inside `#ifdef NON_MATCHING` blocks are not tracked;
a file-scope FAKE line (a declaration) belongs to the first later function naming its symbol.

## LEDGER line format (`quality.py record --batch`)

```
<site-key|func:<seg>:<name>> <method> <outcome> [quirks=Q1,Q2] [seconds=N] [base=N] [best=N] [commit=H] [note="..."]
```
`review` note: `fake=<kept>/<removed> goto=<n> casts=<n kept> views=<ok|n left> protos=<ok|n steer> temps=<ok|n> names=<n m2c left> uninit=<0|n>`.
A site fixed in the copy no longer exists at HEAD: `record --base <copy base>` accepts its key.
