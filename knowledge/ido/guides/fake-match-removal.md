---
title: "Removing fake matches (codegen hacks) from matched C"
description: "Remove IDO codegen hacks using natural C, private whole-object comparisons and the unchanged full-ROM checksum; failed local probes are not impossibility proofs."
origin: "ok-fine dk64/runbooks/fake-match-removal"
---
# Removing fake matches

A fake match is byte-identical C containing constructs retained only to steer IDO register allocation or scheduling. Tags expose that maintenance debt; deleting tags, parking a matched function, or substituting another hack does not remove it.[^agents]

## Procedure

1. Inventory tagged lines by file and enclosing function. Separate matched C from `NON_MATCHING` bodies; a matching-ROM build does not compile the latter. Treat line counts as an inventory metric, not a count of semantic defects. Review suspicious untagged constructs separately; not every `volatile`, cast, local or loop is a hack.[^report][^agents]
2. Start from a matching ROM and `make expected`. Use private copies from an explicit base. Change one dependency group at a time and retain cumulative successes; independent files can be investigated concurrently with `fdiff.sh`, without running shared full builds or re-splits.[^fdiff][^gate]
3. Test direct removal, then reconstruct real source structure: redundant traversal aliases, local lifetimes, actual loops, correct types and meaningful intermediate computations. A register-only mismatch calls for a uopt trace. For a scheduling mismatch, `as1probe.py keep` / `scan` identifies backend differences; translate a diagnostic into real C work, never commit altered ugen records.[^agents][^backend]
4. Compare the entire private object, not only a reduced-TU scorer. `TEXT OK` still requires checking relocations and data in the full ROM. Integrate and run `tools/merge_gate.sh` or the matching build with unchanged hashes; the gate can be used without `--commit`.[^fdiff][^gate]
5. After several natural alternatives stop improving, preserve the original tagged construct and record the exact remaining instruction/register/frame difference plus the alternatives tested. This is a local blocker, not proof that no natural C exists. No substitute dead guards, no-op expressions, artificial volatile, false prototypes or source-layout hacks qualify as a removal.[^agents][^backend]
6. Report verified removals separately from parked exclusions, failed attempts and unattempted sites. Inspect proposed source deltas before integration; a disappearing comment alone is not a result.[^report]

## Diagnostic distinctions

- Empty guards may emit no instruction yet alter register allocation or the placement of a hoisted load. `tools/deadsweep.py` intentionally searches these constructs and tags its output; it is not a natural-source cleanup tool.[^deadsweep]
- Removing an explicit alias can change coloring even if the optimizer produces the same load/control-flow shape. Reconstruct the natural loop before retaining a guard solely for priority.[^agents]
- A schedule-changing self-assignment can be replaced by meaningful work performed at that point; backend swaps are evidence for a dependency to investigate, not permission to encode another no-op.[^backend]
- Padding locals, synthetic volatile and line grouping have different failure signatures. Distinguish stack-frame changes from register allocation and instruction scheduling; a failed deletion does not establish the original source.[^agents]
- Reuse the shared global type already used by most of `src/`. Extend known shared structs at verified offsets rather than adding another file-local view of the same object; views of genuinely polymorphic members remain valid.[^agents]

## Historical overlay pass

The first overlay pass reviewed 385 candidate rows: 176 fixed, 154 suspicious-left-alone and 55 classified needs-human. Its separate needs-human tables contain 68 rows; those are a different metric, not 68 additional candidate outcomes. Counts are historical, and some rows cover multiple sites. The report also distinguishes 33 parked bodies from checksum-verified matched C and explicitly identifies parked edits that received syntax checks only.[^report]

Per-file findings: race (guide ido-fake-match-removal-race: python3 tools/quirks.py get ido-fake-match-removal-race), boss (guide ido-fake-match-removal-boss: python3 tools/quirks.py get ido-fake-match-removal-boss), bonus 0/12A0/9010 (guide ido-fake-match-removal-bonus-0-12A0-9010: python3 tools/quirks.py get ido-fake-match-removal-bonus-0-12A0-9010), bonus 2690 (guide ido-fake-match-removal-bonus-2690: python3 tools/quirks.py get ido-fake-match-removal-bonus-2690), bonus tail (guide ido-fake-match-removal-bonus-2690-tail: python3 tools/quirks.py get ido-fake-match-removal-bonus-2690-tail), minecart (guide ido-fake-match-removal-minecart-25f0: python3 tools/quirks.py get ido-fake-match-removal-minecart-25f0), multiplayer (guide ido-fake-match-removal-multiplayer-0: python3 tools/quirks.py get ido-fake-match-removal-multiplayer-0), critter (guide ido-fake-match-removal-critter-0: python3 tools/quirks.py get ido-fake-match-removal-critter-0). Historical type-convergence suggestions there must be checked against current shared headers.

[^report]: `reports/fake-match-overlays.md`, summary counts, caveats and original attempts.
[^gate]: `tools/merge_gate.sh`, isolated full-ROM and NON_MATCHING syntax gates; commits are optional.
[^fdiff]: `tools/fdiff.sh`, private whole-object comparison and separate NON_MATCHING compile.
[^deadsweep]: `tools/deadsweep.py`, dead-guard search and tagging.
[^backend]: `tools/as1probe.py`, diagnostic records, source interpretations and limits of single-edit scans.
[^agents]: `AGENTS.md`, matching method, codegen-debt tags and shared-type conventions.
