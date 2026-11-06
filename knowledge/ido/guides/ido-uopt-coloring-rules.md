---
title: "IDO uopt coloring rules: classification, candidate order, costs and spill slots"
description: "Source-derived IDO allocation rules and concrete applications from four diff-class campaign matches, with failed diagnostics kept distinct from matches."
origin: "ok-fine dk64/notes/ido-uopt-coloring-rules"
---
# IDO uopt coloring rules

These rules were derived from the local uopt decompilation under `.scratch/ido/src/uopt/` and checked against IDO 5.3 traces during the 2026-11-05 diff-class campaign. The source checkout is compiler evidence, not tracked DK64 source; its local paths and line ranges are retained below as non-code provenance. Cross-version source is a model to confirm with the actual compiler, not a claim that every 7.1 implementation detail is identical to 5.3. Four landed matches demonstrate applications; failed probes below remain explicitly failed.[^rules]

Read with staged near-miss finishing (guide staged-near-miss-finishing: python3 tools/quirks.py get staged-near-miss-finishing), backend records (guide ido-backend-record-pipeline: python3 tools/quirks.py get ido-backend-record-pipeline), temp slots (guide ido-uopt-temp-slots: python3 tools/quirks.py get ido-uopt-temp-slots), and matching quirks.

## Classification and coloring order

- `isconstrained` returns true for **every range of a non-leaf function**, not only ranges crossing calls. For a leaf it tests `numintf >= regsinclass[class-1]`. The normal integer threshold is **22**, or **21 with a reserved frame pointer**. This is the count of neighboring candidate live ranges, not `regsleft`, the number of forbidden registers, or overlapping machine instructions. Do not add a call just to force classification.[^uoptreg2][^uoptinit]
- `intfering` intersects the ranges' `livebbs`: any shared basic block creates an edge. A computation that disappears after allocation can still contribute an edge. A forbidden register need not contain a physically live value at the eventual instruction after code motion/copy elimination.[^uoptreg2][^menu-steps]
- **Constrained first:** descending positive `adjsave`; ties use the smallest candidate bit because the ascending-bit scan updates its winner with strict `>`. Nonpositive-saving ranges may remain uncolored. **Unconstrained afterward:** ascending candidate-bit order, not descending priority. Raising an unconstrained range's priority cannot move it into the first phase.[^uoptreg2]
- For the selected range, choose the cheapest legal register, with register number resolving equal costs. The forbidden set contains precolored register uses in live blocks plus earlier-colored interfering ranges. Call-save costs and first-use costs are separate from the forbidden set: a legal register can still lose on cost.[^uoptreg2]

## Candidate bits mean creation order of the final chain

`newbit` returns `bitposcount++`. It is neither declaration/name order nor hash-bucket order. `codeimage` walks statements; a variable-store destination is interned before its assigned RHS. `exprimage` visits operand 1, then operand 2, then interns the parent. A new variable also consumes an assignment bit. Equivalent expressions can reuse old chains; expressions rebuilt by propagation get later bits. An early syntactic look-alike does not pin the final optimized candidate.[^uoptutil][^uoptitab]

In `controllerUpdate`, the original halfword-offset form's pad address/load were rebuilt as bits 214/215, after held-address bit 140. Canonical byte-address spelling created the final address/load earlier, but alone left the wrong register because high-priority `k` still occupied `a2`. This distinguished a tie-order issue from a separate interference-owner issue. Declaration shuffles could not solve both.[^rules][^match-controller]

## Priority length and first callee-save cost

`compute_save` sums frequency-weighted loads/stores, subtracts required reload/save costs, then divides by live-unit plus reaching-block length compressed as `n > 2 ? ((n-2)>>2)+2 : n`. A no-code CFG block can cross this denominator boundary and lower a priority without adding an important new edge.[^uoptreg2]

Without profile feedback, `globalcolor` sets `firstUseCost = clamp(movcostused * curstaticno * 0.25, 4, 60)`, adding it for a not-yet-used callee-save register. The usual `movcostused` is 1; `curstaticno` counts allocated CFG nodes, including nodes later optimized away. Thus ghosts have three distinct global effects: interference edges, priority denominators and first-use cost.[^uoptreg2][^uoptinit][^rules]

A failed `lightSampleColorAtPosition` experiment made this observable: 81 nodes gave first-use 20.25, removing FP guards left 61 and cost 15.25. Delta ranges crossing `sqrtf` paid caller save/reload cost 20, so they switched from caller-save to callee-save registers and displaced color channels without increased delta priority. A diagnostic recovered target saved colors yet worsened full 94→147. Correct colors are not a match.[^rules]

## Spill slots are not coloring or emission order

The pipeline runs `localcolor`, then `spilltemps`, then `globalcolor`, then reemission. `spilltemps` visits ascending **final** candidate bits in `coloreditems`, forbids slots used by lower-bit chains sharing PRE/SCM regions, and takes the first free slot of the same size. A newly allocated slot is aligned to `min(size,8)`. Expressions later register-colored can still reserve slots and leave holes. `spilltemplodstr` emits the preassigned offset and raises the high-water mark; it does not allocate the slot.[^uoptmain][^uoptreg2][^rules]

Declared-variable homes and compiler-expression templocs are different. Early exact expression ownership can reorder templocs without adding a declared home, but changes to packing/reuse can change the whole frame. A `gfxDrawTexturedTileGrid` probe moved final candidate 584→119 and the desired relative spill -372→-284, but shrank the frame 472→456 and regressed full 90→166. Level-4 PRE output alone is insufficient to simulate packing: `makelivranges` can add later region expressions, and block-local `gettemp` allocation is distinct.[^rules]

## Interference relocation: the cell-table match

The leaf `mapChunkBuildCellTable` match (`4b41ecee`) is the concrete constrained/unconstrained example:[^match-celltable]

1. The sentinel -1 was already constrained; both search indices had exactly 22 neighbors. Remove the early global double-test to remove one edge from those indices, changing their classification.
2. Relocate the needed whole-loop interference to a loop-varying `(size & list)` double-test **after `list += 8`**, where the search indices are dead. Before the increment it creates an unwanted temporary/move; a new global ghost can create a whole-loop address candidate and restore the unwanted edges.
3. Remove the `cidx`/`cfound` entry predefinitions, preserve the key's first appearance, and place `cfound = 0` immediately after `cidx = 0`. This orders the now-unconstrained candidates.
4. Remove two later global dead tests between sentinel stores, lowering that address candidate below `kind`; this resolves the last v1/t0 swap (full 9→0).

The deliberate dead tests/zero-index constructs remain tagged FAKE. This is a demonstrated matching mechanism, not a recovered original-source claim. No uninitialized read is justified by a ghost.[^rules][^match-celltable]

## Other landed applications and ownership cautions

- `menuCharacterSelectUpdateActor` (`8c95be4d`) matched by **removing** the dead `temp_s1->unk4` test before a join. The old guard consumed a ugen ring step; an extra no-code constraint can be the obstruction rather than the solution.[^match-character]
- `controllerUpdate` (`30847bb7`) first improved full 17→6 by changing the entry button-copy owner away from the timer-index web and retaining a mode CFG guard without the cross-block mode-value web. Final C uses `pad = &D_807ECD10[padIdx]`, defines the byte offset before the initial button copy, and orders pressed/held computations through that offset. These are expression/ring and memory-order steps after the allocation diagnosis, not a universal candidate-priority recipe.[^match-controller]
- `menuRenderOptionDescription` (`f3bea028`) needed home/temploc ownership, full-width induction priority, real coordinate overlap, and relocated guards to reach the right allocator state. Then genuine consumed-local reuse fixed the ugen ring and a for-header source location fixed as1 scheduling. Its complete worked sequence belongs in the finishing playbook (guide staged-near-miss-finishing: python3 tools/quirks.py get staged-near-miss-finishing).[^menu-steps][^match-description]
- Diagnose the owner before adding interference. Uncolored `ldc` literals can be emitted by ugen into scratch registers, or remain immediate branch operands for as1 to expand using `at`; colored constants use a register web. The failed natural `jetpacBonusItemUpdate` route reached target timer/constant registers by leaving a constant uncolored, but remained one instruction long. Merely caching a pointer would not remove the timer's existing higher-priority interferers.[^rules]
- FP double guards are not automatically no-code: a `modelAnimEntryBuildKeyMatrix` probe retained `c.eq.s`/`bc1t`, a zero constant and spill/reload, growing text by 48 bytes. Floating fourth arguments can mark integer call-block register use without precoloring an FP range into the integer class. Inspect real emitted code and range class before treating a guard or argument as a free edge.[^rules]

## Source anchors

[^rules]: `.scratch/RegallocGroup/RULES.md`, including retained trace paths and rejected-result measurements. Scratch artifacts are local and may be removed; the durable derivations are reproduced here.
[^uoptreg2]: `.scratch/ido/src/uopt/uoptreg2.c`: `intfering` 790–804; `spilltemps` 873–989; `isconstrained` 1326–1331; `compute_save` 1400–1434; first-use clamp 1977–1983; constrained scan 2039–2078; register cost 2094–2140; unconstrained scan 2241 onward.
[^uoptinit]: `.scratch/ido/src/uopt/uoptinit.c`: `movcostused` default at 724 and integer register-class setup 954–973.
[^uoptutil]: `.scratch/ido/src/uopt/uoptutil.c`: `newbit` 955–973.
[^uoptitab]: `.scratch/ido/src/uopt/uoptitab.c`: `isearchloop` 613–624, `exprimage` 966–1007, `codeimage` 1259–1269/1311/1615.
[^uoptmain]: `.scratch/ido/src/uopt/uoptmain.c` 425–493: allocator and reemitter order.
[^menu-steps]: `.scratch/StackGroup/menuRenderOptionDescription.md`, stack/candidate maps and phase-by-phase 66→0 continuation of the earlier 85→66 improvement.
[^as1-catalogue]: `.scratch/as1group/catalogue.md`, source-record mapping and distinction between allocator and backend differences.
[^match-celltable]: Matching C in `src/global/55B20.c`, landed as `4b41ecee`; code source is pinned to the close-out HEAD.
[^match-character]: Matching C in `src/menu/3E10.c`, landed as `8c95be4d`; code source is pinned to the close-out HEAD.
[^match-controller]: Matching C in `src/global/F600.c`, landed as `30847bb7`, following improved park `548b474f`; code source is pinned to the close-out HEAD.
[^match-description]: Matching C in `src/menu/E550.c`, landed as `f3bea028`; later naming does not change the phase sequence. Code source is pinned to the close-out HEAD.
