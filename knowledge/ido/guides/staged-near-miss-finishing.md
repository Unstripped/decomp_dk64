---
title: "Finish near-misses in compiler stages, not spelling grids"
description: "Diff-class dispatch and staged uopt/ugen/as1 diagnosis, with the menu 85-to-zero and controller 17-to-zero worked examples and explicit unparked verification."
origin: "ok-fine dk64/runbooks/staged-near-miss-finishing"
---
# Staged near-miss finishing

Use this for count/frame-exact IDO 5.3 near-misses after ordinary C spelling grids stop teaching anything. The 2026-11-05 diff-class campaign produced four landed matches by separating allocator, stack, ugen and as1 questions. The method is not “add more ghosts”: identify the first compiler boundary that diverges, derive that pass's rule, and change its input without discarding already-correct constraints.[^ledger][^rules]

## Entry and handoff contract

1. Start a private whole-file copy from a named commit and the best saved draft. Record instruction count separately from normalized diff rows (relocations add rows); retain the frame, saved-register set and observed stack offsets. Recheck which body the comparison actually compiled.[^agents]
2. If grids stall, assign work by **diff class**, with a compiler-source derivation required before further edits: constrained coloring/forbidden sets, named homes/expression spills, ugen scratch sequence, or as1 cross-block scheduling. Reuse the allocator reference (guide ido-uopt-coloring-rules: python3 tools/quirks.py get ido-uopt-coloring-rules); do not assume all similar-looking assembly differences belong to one pass.[^rules][^as1-catalogue]
3. Keep a shared `.scratch/` note per function: base commit, best plain-C body, stage and full/text/reloc/shape/count/frame, candidate table/slot map, phase captures, successful and rejected routes. Give the paths and one evidence-backed next step to the next agent. Preserve a useful exact-stack or exact-color alternative even if its full score is worse; it isolates a solved subproblem.[^menu-steps]

## Diagnose from the front to the back

| First wrong artifact | Question and evidence | Safe next move |
|---|---|---|
| C/cfe homes or instruction count | Actual types, hidden temps, named versus repeated expressions; full-TU comparison | Fix structure/storage first; do not mask a narrowed induction or smaller real buffer with a lower score. |
| uopt ranges/colors | `uopt_trace.sh -l 5/6`: final chain bits, constrained status, priority, forbidden set and assigned register | Change the actual edge owner, candidate creation, or genuine lifetime; measure collateral changes to priority/first-use costs. |
| uopt expression homes | Final `coloreditems`, PRE/SCM regions, named-local boundary and slot reuse | Change expression ownership/order; check the entire frame, not just the one desired offset. |
| ugen record registers | `as1probe.py keep`, then ucode/disassembly of kept phases | Follow expression consumers/conversions and temp lifetimes; source declarations alone need not control scratch order. |
| as1 instruction placement | Compare ugen order with final code; retain exact record-level proof | Map the needed record to real C, or document that no producer is known. A record edit is never itself a C match. |

The allocation/slot rules and their source anchors live in the coloring reference (guide ido-uopt-coloring-rules: python3 tools/quirks.py get ido-uopt-coloring-rules); tool semantics and normal verification are in AGENTS.md. Capture before changing C so a negative result explains a mechanism rather than only another score.[^agents][^rules]

## Worked example: menuRenderOptionDescription, 85→0

The earlier campaign reached 85→66; this phase retained 66→51→35→31→27→14→10→0, with the final change divisible into 10→3→0. The frame stays 0xE8 and the completed comparison has 417 normalized rows; these rows are not a count of machine instructions. Older notes' lower scores sometimes hid the wrong induction type.[^menu-steps][^match-description]

| Step | Deciding observation and retained C change |
|---|---|
| 66→51 | Alpha's expression spill was at 0x4C instead of 0x60. Inline `yy`/`yyo`, reuse the cursor instead of a named `textDl`, and temporarily reuse storage for the two preloop OtherMode packets. This moves the named-home boundary without blind padding. |
| 51→35 | The target recurrence/compare has no 16-bit mask: use full-width `s32 x`. Separate induction from later text coordinates and use the existing tagged head guard to raise x priority above packet ranges. Share the load-tile/postloop packet lifetime to preserve its forbidden edges. A proven source-line join improves 37→35. |
| 35→31 | Carry the offset through x to supply v1 interference for `off`; allocation reaches t0. This is an intermediate FAKE, not the eventual solution. An exact-stack alternative scored 33 but perturbed six preheader scratch choices; preserve it as a diagnostic, not the best park. |
| 31→27 | Restore normal preloop macros; reuse consumed `arg1` for Combine. Cast the two existing byte ghosts to `s8`: their shared expression belongs to a later conversion instead of the early unsigned load, restoring alpha's first temploc while yy/yyo stay correct. All observed offsets now match without the scratch regression. |
| 27→14 | Replace the fake x-to-off carrier by a genuine coordinate lifetime: compute x from screen center, define `off`, then use x in `xx = x * 4`. This supplies v1 interference without making the raw byte load itself part of x's web, fixing that t0 load and its arithmetic chain. |
| 14→10 | Move both existing signed-byte guards directly after the outer loop and use initialized xo as their second operand. Merging the width/prim/Combine allocator block gives Combine the missing v0/v1 exclusions. Both xo uses preserve its priority length (62.8) while x stays 304; moving guards alone shortened xo and stole the row-mask register. |
| 10→3 | The residual call mismatch begins in ugen, not uopt. Compute final y into xo, then reuse the consumed font-height local for xx. The real dependency makes y truncation precede argument setup, fixing seven scratch/forwarding differences without a new guard. |
| 3→0 | Put the inner recurrence in a `for` header. The ugen `.loc` for its update points backward to the header instead of the later do/while tail, letting as1 emit the target `li at,204` and `move v1,t0` earlier while keeping xo's move in the branch delay slot. Merely deleting `.loc`, swapping tail updates or using while did not match. |

The final consumed-local reuse (historical local names before the naming pass) is only three statements:

```c
xo = (s32)((f64)off + (f64)spC0 * 0.5);
spC0 = xx;
return hudDrawScaledText(dl, (s16)spC0, (s16)(xo * 4), .5f, spC4);
```

The resulting ugen ring is t6 truncation scratch → t7 a1 sign-extension scratch → t8/t9 y extension → t6 string load. As1 forwards the multiply/shift chain into the target `mfc1 a2; sll t8,a2,18; sra a2,t8,16`. The worker's retained plain-C whole-file fdiff was OK and reduced full/text/reloc/shape were all zero; the merged unparked C landed in `f3bea028`. Existing FAKE/LAYOUT tags remain; the finish did not add a new dead guard.[^menu-steps][^match-description]

## Worked example: controllerUpdate, 17→6→0

The initial allocation puzzle had two independent causes: propagation rebuilt pad address/load candidates after held-address, and the initial button-copy range overlapped the high-priority inner timer-index range `k`, occupying the desired register. Merely changing candidate order fixed neither the whole graph nor the schedule. An explicit pointer-increment alternative got the key colors but scored 23 instead of the retained 17, so it was not promoted to a match.[^rules][^controller-steps]

The 17→6 park (`548b474f`) retained a mode CFG constraint without a cross-block mode-value web, computed the six-byte offset through `sum`, and moved the initial button copy from `k` to `padOffset`. Final commit `30847bb7` instead spells the actual pad as `&D_807ECD10[padIdx]`, defines the byte offset before loading the initial button value, and preserves that load in `padOffset`/`buttons`; pressed and held accesses use explicit byte-offset addresses before the later buttons assignment. This makes expression consumers and source store order agree with the target rather than adding another allocator ghost.[^match-controller]

That landed match supplied the menu finisher's next experiment: **genuine consumer ordering can control the ugen ring after the allocator is correct**. Do not use an exact-color trace as proof that later stages match.[^menu-steps][^match-controller]

Two smaller examples complete the campaign evidence: `mapChunkBuildCellTable` (`4b41ecee`) crossed the leaf constrained threshold by relocating an edge to the outer tail, then ordered the unconstrained indices; `menuCharacterSelectUpdateActor` (`8c95be4d`) matched by deleting a dead field test that consumed an unwanted ring step. These are opposite interventions justified by different evidence, not interchangeable tricks.[^match-celltable][^match-character]

## C-to-ugen/as1 record catalogue

| Required backend input | Established C producer | Limit |
|---|---|---|
| `.noalias R,$sp`, then `.alias R,$sp` between an unconditional branch and the next label | A surviving actual global-object address whose tracked region ends at the arm exit; matched jetpac ledge/score updates provide examples. | Loaded pointers or arithmetic on them do not establish that variable-address region; scalar addresses may fold away. |
| Referenced label immediately before a compare | A real conditional assignment/clamp whose join is referenced. | Unreferenced labels and jump-to-next vanish in ugen labelopt. |
| `.livereg` | Real call argument/return liveness. | An injected mask diagnoses a needed live value; it is not arbitrary-join C syntax. |
| `.loc` | Physical statement location, including a for-header update location. | A line break/join changes records; `.loc` is not a fall-through predecessor and cannot substitute for an alias reset. |
| `bnext`, dead label, no-op instruction | No general matched-C producer established. | Backend-only probes remain diagnostics, not a reason to edit assembly or compiler flags. |

uopt tracks variable-address bases and emits Uunal resets before labels when the next block's entry candidate differs; ugen labelopt deletes ordinary dead instructions/jump-to-next. The surviving alias reset can provide as1 an apparent fall-through predecessor, stopping unique-predecessor target hoisting. Consult backend pipeline (guide ido-backend-record-pipeline: python3 tools/quirks.py get ido-backend-record-pipeline) for the distinction between record reachability and a finished source route.[^as1-catalogue]

For `csCmdPointHitEffectSpawn`, optimized ucode and ugen keep the hit-store literal before the call-argument literal. The actual as1 XBB trace moves eligible source-block instructions in that order: the 5.3 candidate scanner returns the first eligible instruction beyond its previous index, not a literal-hash priority. For `func_806F03C4`, ugen retains the index load under default; as1 expands that load and hoists only its `lui`. Changing uopt first-appearance order is therefore not the responsible-pass fix. Both still lack a known C route; the catalogue's backend success proofs are not matches. No complete as1 scheduler source was available: these conclusions combine retained 5.3 ELF disassembly and `-xbbdbg 31` traces, not invented source evidence.[^as1-catalogue]

## Completion evidence and stopping

- A default fdiff of a **parked** function compares its assembly branch. `OK` does not validate the C; `--non-matching` is explicitly only a compilation check. Put the final C **UNPARKED** into the private whole-file copy and compare that same form, including relocation targets/own-data caveats, before claiming a match.[^agents][^menu-steps]
- The integrator must confirm the merged function really is unparked, then run the full-ROM gate. A still-parked function passes the ROM gate too, so the ROM gate must never be the only evidence of an unpark. Only the full plain-C file plus the ROM gate completes the match.[^agents][^menu-steps]
- Keep the best count/frame-exact park if the derived route regresses elsewhere. Do not promote a shorter score with a wrong count/type/capacity; do not confuse a phase proof with end-to-end completion. Record rejected routes so the next agent does not repeat them.[^rules][^menu-steps]

[^agents]: AGENTS.md comparison, parking, stage-order and matching-build contracts; decomp-unit dispatch/brief/merge procedure at the source HEAD.
[^ledger]: `drafts/attempts.jsonl`, unit `2026-11-05: diff-class groups`: 67 attempts, four matched outcomes, eight park improvements and 55 unmatched attempts across 24 C targets.
[^rules]: `.scratch/RegallocGroup/RULES.md`, preserved as the linked durable coloring reference.
[^controller-steps]: `.scratch/RegallocGroup/controllerUpdate.md`, allocator alternatives and rejected exact-color route; later landed transitions are grounded in the matching source commit.
[^menu-steps]: `.scratch/StackGroup/menuRenderOptionDescription.md`, full stack/candidate/phase derivation; first retained state is 66 following the earlier 85→66 improvement.
[^as1-catalogue]: `.scratch/as1group/catalogue.md`: C record producers, uopt/ugen source anchors and retained as1 5.3 ELF/XBB-trace evidence. Local scratch is not a tracked DK64 source dependency.
[^match-celltable]: `src/global/55B20.c`, match `4b41ecee`, source pinned to close-out HEAD.
[^match-character]: `src/menu/3E10.c`, match `8c95be4d`, source pinned to close-out HEAD.
[^match-controller]: `src/global/F600.c`, improved park `548b474f` and match `30847bb7`, source pinned to close-out HEAD.
[^match-description]: `src/menu/E550.c`, match `f3bea028`, source pinned to close-out HEAD; subsequent local/parameter naming preserves the mechanism.
