# jetpacStateGameplay (jetpac, src/jetpac/0.c)

## Sites
jetpac:800248E8:other:037cad other: the empty `items[currentItem].unk44` guard creates a uopt basic-block/liveness boundary; it emits no load or branch but keeps `player` at sp+0x1c in the target rather than promoting `&jetpacGame` to `$s0`.

## Attempts
2026-11-10 cleanup round 7 CleanJetpac0 anthropic/claude-opus-5-5:low: uopt trace showed removal splitting the `player` live range; guarded/plain call rewrites failed -> nohit.
2026-11-11 cleanup round 17 Rev17M anthropic/claude-opus-5-5:low: removal promoted `&jetpacGame` to `$s0`; an empty relocated player guard was rejected -> nohit.
2026-11-13 cleanup round 34 Consol34 anthropic/claude-opus-5-5:low: permutation found only a `do {} while (0)` wrapper -> nohit.
2026-11-14 HackjetpacUpdateStateAndInput openai-codex/gpt-5.6-sol: classified the target with as1 output and paired baseline/removal uopt traces; tested a score-selector switch, score ternary, delayed pointer declaration/assignment, a later pointer alias/reload, and `variants.py scan`; `as1probe.py scan` found only save/livereg record deletions, not a source-line join -> fdiff mismatch, original retained.

## Untried ideas
No ordinary-C rewrite remains that introduces the required uopt block without changing behavior or replacing the empty test with another dead/no-op construct.

## Evidence
At target 0x954-0x95c, the code is `lw $v0,0x1c($sp)`, `jal jetpacPlayerStateUpdate`, and delay-slot `sw $v0,0x1c($sp)`. There is no load of `currentItem` or `unk44` and no conditional branch, so the empty test is not target behavior and cannot be marked `ORIG`.
Removing it changes the function frame from 0x20 to 0x28, adds an `$s0` save/restore, retains `&jetpacGame` in `$s0`, and removes the reload/store pair around `jetpacPlayerStateUpdate`. The as1 record scan's best deltas deleted the `$s0` save or changed livereg records, confirming a uopt liveness/coloring issue rather than a `.loc` schedule join.
