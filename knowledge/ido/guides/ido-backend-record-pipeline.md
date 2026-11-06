---
title: "IDO back end: which records reach as1, and as1's branch-target hoist"
description: "How cfe/uopt/ugen records reach as1 (ugen labelopt deletions, uopt unal regions), the exact rule for as1 hoisting a branch target's first instruction into a stall, and how to search and verify at each boundary with as1probe."
origin: "ok-fine dk64/notes/ido-backend-record-pipeline"
---
# IDO back end: which records reach as1, and as1's branch-target hoist

Established on `func_806F03C4` (2026-11-03), whose last diff (a `lui` hoisted into the switch-dispatch stall) had survived 14 agent attempts.[^draft]

## as1's branch-target hoist

as1 moves the first scheduled instruction of a conditional branch's target block into the branching block's load-use stall when the target label has exactly ONE predecessor (no fall-through into it, one reference; jump-table `.word` entries count as references) and the moved register is dead on the other path. Any as1-visible record between the previous block's last jump and the label makes a fall-through predecessor and stops the hoist, even a record as1 later deletes: an instruction (`addu $0,$0,$0`, `move $3,$3`), a jump-to-next `b`, `.alias`/`.noalias`, `.bgnb`/`.endb`, `.frame`/`.fmask`, a data directive in text. A `.livereg` marking the moved register live before the branch (anywhere in the entry block for `func_806F03C4`: `try --insert 28:live=0x0000004E`) stops it too. `.loc` (any file/line), other `.livereg` masks, `.set`, extra unreferenced labels, the `.rdata` jump table, label numbering, and spelling the range check as `sltiu`+`beq` do not.[^as1probe] The same rule produced the target's own else-arm hoist in `func_806F03C4` case 5 (`li a3,0x1F` above `bne`), so it is original as1 behaviour, not a toolchain artefact.[^draft]

## What C can put in front of a label

- **ugen labelopt** (5.3 behaves like the 7.1 decompilation; checked by injecting ucode into uopt's output and re-running ugen 5.3): deletes jump-to-next, threads jumps through jump-only blocks (also the switch range check and table entries), deletes unreferenced labels, and after an unconditional jump deletes everything up to the next label except `unal`, `bgnb`/`endb`, `comm`, `def`, `lex`, `optn`, `sdef`.[^labelopt] At -O2 -g0 (no `bgnb`) the only as1-visible record C can leave between a block's final jump and the next label is uopt's `.alias` reset; the corpus has 181 of them (`b $X; .alias $R,$sp; $Y:`).
- **uopt `unal`**: `base_in_reg` (when a register is used as an access base) emits `.noalias R,X` only for a variable-address base (`lda`/`ilda`: an `la` of a global is noalias with `$sp`, a local's `addu sp` with `$gp`, a variable address vs a pointer when the variable's address is never taken). C runs alias mode 2 (`optinit` default; `-fortran_lang` changes it), so `pointtoheap` is false and pointer-derived bases (loaded pointers, `p + i*k`) are never noalias. At each block start, before the label, `func_00422AF0` emits `.alias` for every register whose tracked candidate differs from the next block's entry candidate.[^uoptemit][^uoptkill] A preceding function's open noalias region does not leak into the next function.
- Consequence: a fix that needs a record before a label is reachable from C only if some register holds a variable address whose region ends in the preceding block. `func_806F03C4`'s switch holds none (camera is `gPlayerSlots + i*0x2F0`, a loaded pointer), so this baseline has no alias reset to exploit. Subsequent liveness probes below identify another exact backend route, but no C realization. C reachability remains open, not disproved. Flags (`-g1`/`-g2`/`-g3`, `-Wo,-noPalias`, `-Olimit`) do not help.[^draft]

## Dead-read liveness probe (not a C match)

In the natural `func_806F03C4` binasm stream, inserting `move $t0,$t9` before dispatch, in several case blocks, or at the common join before `jal mathAngleBetweenPoints2D` produces full/text/reloc/shape scores of zero. The inserted instruction disappears in the assembled output, while the default-arm `lui $t9` stays in place. This demonstrates that instructions absent from the final disassembly can still affect cross-block scheduling through liveness. The `.livereg` GP bit for `$t9` is `0x40` (bit `31-r`). These are edited-backend diagnostic results, not matching C.[^dead-read-probe]

A source ghost-index dead test in case 4 also removes the entry hoist, but its zero shape score is misleading as a matching lead: allocation changes the default destination to `$t7`, already live in the dispatch, and changes many other registers. Restoring the target registers would remove that particular reason for suppressing the hoist. Inspect the moved register and the actual diff before treating shape-zero as independent scheduling progress.[^dead-read-probe]

The tested pointer/address-taken/union variants did not create the needed alias boundary; the tested C identity forms did not create the needed dead `$t9` read. Neither result proves that every C spelling is impossible. No C match or full-ROM gate of a replacement was obtained; the unchanged assembly-backed build passed.[^dead-read-probe]

## Method for schedule/shape-only near-misses

1. `tools/dk python3 tools/as1probe.py keep <copy.c> src/<seg>/<file>.c FUNC` keeps every phase: cfe ucode `t.B`, uopt ucode `t.O`, ugen binasm `t.G` (16-byte records[^binasm]) and its listing `t.s`. The object is `out.o`: on the macOS bind mount `t.o` and `t.O` are one file, so older runs had as1 overwrite uopt's ucode.[^as1probe]
2. `scan DIR` tries every single record edit (probes `noop`/`alias`/`loc`/`bnext`/`label`, deletes, adjacent swaps; `--rounds N` greedy) in about a minute and annotates each hit with what C could emit it: an inserted `loc` is a line break, a deleted `.loc` a line join, `alias` needs a variable-address register region, `live` points at a register-liveness route, `noop`/`bnext`/an unreferenced `label` are diagnosis only. A scan covers single edits only: hits C cannot emit are evidence for the draft, not proof that no C exists. Deletes and swaps of instructions can lower the score by changing the count: compare `n` with the target.[^as1probe]
3. One stage up: `ucode DIR` disassembles `t.O` with udis[^udis] (built in the image[^dockerfile]); to test whether a uopt record would survive ugen, copy instruction words inside `t.O` and run `/opt/ido5.3/ugen -G 0 -mips2 -EB -g0 -O2 x.O -o x.G -l x.s -t t.T` then `as1probe as1 DIR x.G`.
4. `corpus [--grep RE]` compiles every src file to ugen listings in `.scratch/ugen_corpus/` to find matched C that produced a record pattern.

A batch `scan` of all 32 NON_MATCHING parks (2026-11-03) found exact single-record fixes in two, both this missing-predecessor class: `func_806F03C4` (switch default label) and `renderModelAnimatedSlot` (full=14 in three guRotateF arms, fixed by one record before the label after a mid-function `if (...) return arg1;`, 70 records upstream: a label's predecessor count also shapes as1's cross-block scheduling further down). The other small parks differ in registers, which record edits cannot reach.[^rmas]

## Reading compiler logic

n64decomp/ido has uopt (7.1) as C, decompals/ido-matching-decomp ugen (7.1) as matching Pascal plus `binasm.h`; the IRIX 5.3 `as1`/`uopt` binaries keep dynamic symbols (`do_xbb_opt`, `schedule`, `base_noalias`, `pointtoheap`) for `mips-linux-gnu-objdump` when 5.3 may differ. Related: IDO matching quirks, near-miss methodology (guide large-functions-and-near-misses: python3 tools/quirks.py get large-functions-and-near-misses).

[^as1probe]: `tools/as1probe.py` docstring (PROBES and findings) at the cited commit.
[^draft]: `drafts/global/func_806F03C4.c` first line (blocked verdict and evidence).
[^rmas]: `drafts/global/renderModelAnimatedSlot.c` first line (scan finding at label $62).
[^dockerfile]: `Dockerfile` udis layer.
[^uoptemit]: `base_noalias`, `base_gp_noalias`, `base_sp_noalias`, `base_in_reg`, `func_00422AF0` and the `reemit` block loop.
[^uoptkill]: `pointtoheap`.
[^labelopt]: `delete_dead_code`, `localopt`, `build_flow_graph`, `delete_dead_blocks`.
[^binasm]: the `binasm` union and `itype`/`asmcodes` enums.
[^udis]: ucode disassembler built from source at commit 1fa98311.

[^dead-read-probe]: Focused compiler experiments retained under `.scratch/F806F03C4/` and `.scratch/DeadReadRoute/`; diagnostic conclusion also recorded in the working-tree draft note. Scratch paths are ephemeral; no landed matching-C claim is made.

## Diff-class attribution and C producers (2026-11-05)

The updated drafts still have no matching C route: `func_806F03C4` retains the natural five-entry table at full 4 (text 2 / reloc 2), and `renderModelAnimatedSlot` remains full 14. Pointer/addressability attempts did not provide a free alias boundary; their success-free histories are not impossibility proofs.[^draft][^rmas]

The staged finishing playbook (guide staged-near-miss-finishing: python3 tools/quirks.py get staged-near-miss-finishing) now preserves the C-to-record catalogue: real global-object address-region ends produce alias resets; referenced conditional joins produce labels; real call/return uses produce livereg; physical statement locations produce loc. Dead labels/noops/bnext remain diagnostics without a general C recipe. A for-header update location is distinct from simply deleting a loc, as the menu match demonstrates.[^diffclass26-as1-catalogue]

For `csCmdPointHitEffectSpawn`, retained uopt/ugen order is hit-store literal then argument literal. IDO 5.3 `-xbbdbg 31` plus the retained ELF candidate-scanner disassembly establish that XBB selects the first eligible source-block instruction beyond the previous selected index; it is not a constant-hash sort. In `func_806F03C4`, as1 expands the default's symbolic current-player-index load and hoists its upper-address instruction; uopt did not hoist that address candidate. These are responsible-pass conclusions, not new matches. The catalogue explicitly records that no complete as1 scheduler source was available.[^diffclass26-as1-catalogue]

Later negatives for `func_806F03C4` (2026-11-05):
- Wrapping the switch in `do {} while (0)` gives shape 0 but full 100. Dispatch leaves bb0, so case 2's `ev` piece becomes the uncoloured one, the ring shifts by one, and default's index lands in `t7` (live in dispatch). That stops the hoist only by changing registers, the same route as the case-4 ghost test; no record precedes the default label, so with target registers the hoist is expected to return (inferred, not tested).
- Moving the `.rdata` jump table to the end of `t.G` still hoists (full 4); in this test as1's `jr` liveness did not depend on table placement.
- `uoptemit.c` `base_sp_noalias` treats only an `lda`/`ilda` of `Smt` memory as noalias with `$sp` (`pointtoheap` is Pascal-only). `func_00422AF0` also resets register-pair and `$gp` aliases, which were not explored. No tested C route provides the boundary; that is not a proof that none exists.[^draft]

[^diffclass26-as1-catalogue]: `.scratch/as1group/catalogue.md`, including C/ugen examples, uopt/ugen source anchors and retained as1 ELF/XBB traces; durable reproduction in the staged finishing playbook.
