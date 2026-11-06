---
title: "Methodology for large functions and near-misses"
description: "Procedure and methodology for matching large IDO 5.3 functions and resolving register-allocation near-misses using uopt tracing, decomp-permuter, and NON_MATCHING parking."
origin: "ok-fine dk64/runbooks/large-functions-and-near-misses"
---
# Methodology for large functions and near-misses

Matching large functions and resolving register-allocation near-misses under IDO 5.3 requires a structured stage discipline, diagnostic tools, and careful use of the permuter and non-matching parking.

## 1. Stage Order for Non-Trivial Functions

For any non-trivial function, do not jump straight to register allocation or scheduling tricks. Work through the six stages adapted from the Nintendo 64 IDO 5.3 -O2 decompilation guide[^ootguide]:

1. **Behaviourally equivalent C:** Start from starter C emitted by `tools/m2c.py` and produce code that accurately implements the algorithm and logic.
2. **Basic-block order:** Ensure control flow constructs (`if`/`else`, loops, `switch`, early returns) produce basic blocks in the same linear order as the target assembly.
3. **Large reorderings:** Match statement and expression order within and across blocks.
4. **Same callee-saved register set and frame size:** Ensure the set of preserved registers (`$s0`–`$s7`, `$fs0`–`$fs5`) and the stack frame size (`$sp` adjustment) match the original assembly.
5. **Small reorderings:** Align local statement order, delay-slot candidates, and sub-expression evaluations.
6. **Register allocation:** Resolve temporary register assignments and scheduling.

**Reporting rule:** Agents report the stage reached, not only an instruction count. Register-allocation tricks are wasted before reaching Stage 4.

## 2. Why Large Functions Are Hard

IDO 5.3's global optimizer `uopt`[^uoptman] performs register allocation via priority-based graph coloring with live-range splitting, as formulated by Chow & Hennessy (TOPLAS 1990)[^chowhennessy].

- **Priority formula:** Priority is determined by the estimated cycle savings of a candidate live range weighted by basic-block execution frequency and normalised by the length of the live range. Candidates are processed in descending priority order.
- **Live-range splitting:** When register pressure prevents coloring an entire live range, `uopt` splits the live range across basic block boundaries and attempts to color the segments independently, spilling only constrained regions.
- **Global coupling:** Because priority computation and register coloring are global across the whole function, a small edit in one basic block (or even adding an unused local or reordering statements in one loop) alters live-range lengths and priorities, cascading register shifts into completely unrelated loops or blocks.

## 3. Diagnosing Register Allocation with `tools/uopt_trace.sh`

Before guessing local variable combinations or reordering code blindly, diagnose `uopt`'s actual allocation choices on a private copy[^uoptrace].

`tools/uopt_trace.sh` compiles using `/opt/ido5.3-trace/cc`—an IDO 5.3 `uopt` rebuilt with `tools/ido/ecvt_fcvt.patch`[^patch] inside the Docker container[^dockerfile] (emitting objects byte-identical to the production compiler without debug flags) passing `-Wo,-zdbug:LEVEL`:
- **Level 6 (`-l 6`, default):** Prints the candidate table (mapping candidate bit indices to parameter offsets `Pvreg` and local stack offsets `-Mvreg`) and the priority-based coloring trace showing which candidate live range was assigned to which hardware register, which ranges were split, and which were spilled (`not colored (-ve save)`).
- **Level 5 (`-l 5`):** Prints live ranges, interference graphs, and estimated cycle savings (`adjsave`).

Usage:
```sh
tools/uopt_trace.sh [-l LEVEL] [-s src/<seg>/<file>.c] <file.c> [FUNC]
```

Full trace listings are placed in `.scratch/trace/<file_escaped>.list`. Compare which candidate received which register against the target assembly.

The register IDs in the trace use uopt's own 1-based internal numbering (with the full lookup table in the `tools/uopt_trace.sh` header[^uoptrace]):
- **1–12:** `$v0`, `$v1`, `$a0`–`$a3`, `$t0`–`$t5` (caller-saved GPRs)
- **14–22:** `$s0`–`$s7`, `$fp` (callee-saved GPRs)
- **24–35:** FP `$f0`, `$f2`, `$f12`..`$f30` (floating-point registers)
- **Excluded:** `$t6`–`$t9` are never allocated by `uopt` (reserved as scratch temporaries for code generation).

## 3b. Scratch-register-only diffs: read ugen's output, not as1's

When fdiff shows an identical opcode stream whose only differences are `t3`–`t9` / `$f4`–`$f18` numbering from one point on, the cause is usually an instruction ugen emitted and as1 deleted (home-slot parameter reloads, `sll/sra` sign-extension of an `s32`-declared callee result, `move` chains). ugen assigns scratch registers least-recently-used, so a phantom temp shifts every later choice.

1. Emit the unscheduled listing with the same flags and `-S`: `tools/dk /opt/ido5.3/cc <make flags> -S .scratch/<copy>.c` (writes `<copy>.s` in the cwd).
2. At the first divergent instruction, read the ugen listing around it: the temp the target used is the one ugen would have picked without the extra instruction(s) listed there.
3. Fix at C level: callee return type (`s16` vs `s32`), a hidden local in a frame gap (`f64` where the `f32` version becomes a uopt candidate), operand order (`a + call() * b` vs `call() * b + a`).

`func_80622B24` went from 2046 diff lines to a match in four compiles this way after permuter runs had found nothing (details in IDO uopt notes (guide ido-uopt-statics-and-live-ranges: python3 tools/quirks.py get ido-uopt-statics-and-live-ranges)).

## 3c. Schedule/shape-only diffs: search ugen's records, then check C reachability

When registers already agree and the diff is a hoist, a delay-slot fill or an instruction order, search the record stream before trying spellings:

1. `tools/dk python3 tools/as1probe.py keep .scratch/<you>/<file>.c src/<seg>/<file>.c FUNC`, then `as1probe.py scan DIR [--rounds N] -j 6`: every single ugen-record edit (probe inserts, deletes, adjacent swaps) is assembled and scored in about a minute; hits are annotated with what C could emit them.
2. A `loc` insert is a line break and a deleted `.loc` a line join (tag the C `// LAYOUT:`); an `alias` insert needs a register holding a variable address whose noalias region ends in that block; a `live` hit points at keeping a register live there; `noop`, `bnext` and an unreferenced `label` cannot come from C.
3. If every exact edit is one C cannot emit, write the edits into the draft and switch from single-site spellings to routes that change several records at once (`scan --rounds`, liveness, webs). A scan covers single edits only, so it never shows a function is unreachable from C (`func_806F03C4`: the first probe set missed its `t9`-liveness route).

Rules and the uopt/ugen boundary checks: IDO back end records (guide ido-backend-record-pipeline: python3 tools/quirks.py get ido-backend-record-pipeline).

## 4. Permuter Tooling at Stages 5–6

Once a function reaches Stage 5 or 6 (matching frame size, callee-saved registers, and block structure), use `tools/permute.py`[^permute] to explore small reorderings, temporary assignments, and syntax variants. It automates `decomp-permuter`[^permuterdoc], which is pinned in the Docker toolchain at `/opt/decomp-permuter`[^dockerfile].

### Subcommands

1. **Setup:**
   ```sh
   tools/permute.py setup <seg> <FUNC> [--from FILE.c] [--src src/<seg>/<file>.c]
   ```
   Generates `.scratch/permuter/<seg>_<FUNC>/` containing `base.c` (from the stored draft by default), `target.o` (from the function's asm), and `compile.sh` configured with matching compilation flags, and prints the starting score.
2. **Run:**
   ```sh
   tools/permute.py run <dir> [-j N] [--seconds S]
   ```
   Runs permuter mutations. The wrapper always passes `--stack-diffs` and `--stop-on-zero`. Default parallelism is half the host CPUs.
3. **Inspect results:**
   ```sh
   tools/permute.py best <dir>
   ```
   Lists recorded candidate outputs ordered by score and prints a unified diff of the best result against `base.c`.

In a test on `func_80663BE8` (`684C0.c`, a register-only near-miss), `tools/permute.py` took the function from score 105 to 0 (full match) in 60 seconds with `-j 2`.

### Search-Hint Rule and Safety Policy

- **Mutations are NOT semantics-preserving:** Upstream permuter passes move statements across blocks, alter types, and delete single-branch `if` statements.
- **Disassembly-only scoring:** The scorer evaluates instructions and stack offsets (via `--stack-diffs`), but does not verify relocations or data symbols.
- **Search-hint contract:** A permuter output is strictly a search hint. Never paste permuter output unreviewed into `src/`. Inspect the diff, understand why `uopt` reacted favorably, and rewrite the idea into clean, readable C that faithfully preserves the original assembly's behavior.
- **Verification gates:** After adapting a hint, verify via normal gates: `tools/fdiff.sh` / `tools/objdiff.sh` OK or `TEXT OK`, followed by a full ROM build (`tools/dk make`) verifying `build/dk64.us.z64: OK`.
- **CPU sharing:** Multiple subagents share the CPU during decompilation rounds. Always supply an explicit small job count (e.g. `-j 2`) and a `--seconds` limit to avoid starving sibling tasks.

## 5. NON_MATCHING Parking

When a function resists matching despite reaching Stage 5–6, but its C implementation has been reviewed and verified to be genuinely behaviourally equivalent (the remaining diff consists solely of register allocation, instruction scheduling, or stack layout), it may be parked in `src/`:

```c
#ifdef NON_MATCHING
/* Reviewed behaviourally equivalent C */
void func_80XXXXXX(...) {
    ...
}
#else
#pragma GLOBAL_ASM("asm/...")
#endif
```

`asm-processor` drops the assembly when the dummy function is `#ifdef`'d out.

- **Build command:** `tools/dk make NON_MATCHING=1` compiles into `build_nonmatching/` without performing SHA-1 hash checks, reporting `Build complete (NON_MATCHING=1: output is not compared)`[^makefile].
- **Testing private copies:** `tools/fdiff.sh --non-matching <copy> <src> [FUNC]` compiles only the NON_MATCHING side (prints `NON_MATCHING: not a match check`).
- **Default build untouched:** The default build (`tools/dk make`) and gates remain unchanged. `make expected` and `tools/dk make progress` refuse `NON_MATCHING=1`.
- **Accounting:** Parked functions count as unmatched in decompilation progress.
- **Parking criteria:** Only park C that has been thoroughly reviewed as behaviourally equivalent. If equivalence is uncertain, retain the draft in `drafts/<seg>/<FUNC>.c` instead.

## 6. Lessons From Matching func_800254D0 (boss, 0x2290 bytes)

- **The asm diff of a long function shows only its start:** `tools/objdiff.py` (behind `fdiff.sh`/`objdiff.sh`) decides the match by comparing the complete `.text`/`.data`/`.rodata` sections and relocations, so a mismatch anywhere is reported as `FAILED`. Only the asm-differ diff and score it prints afterwards are cut off, because asm-differ's `--max-size` defaults to 1024 lines (0x1000 bytes)[^objdiff]. Beyond that point the tools still report the failure but show no diff. To locate differences there, diff the full `mips-linux-gnu-objdump -d` output of both objects.
- **Callee return types steer register allocation:** declaring a callee whose result is ignored as `s32` instead of `void` changes `v0` interference. Changing `func_806086CC` from `void` to `s32` in the boss TU took the diff from 89 to 32 instructions. Try return types for unknown callees, one per variant, and keep the TU prototype that matches.
- **Float literal arguments:** passing `0` to an `f32` parameter emits `li a3,0`. Passing `0.0f` reuses `$f0` through `mfc1`.
- **Write table lookups the way the original indexes them:** `u8 *tbl[][5]` indexed `tbl[c ? 0 : 1][i]` matched. The flattened m2c form `tbl[k * 5 + i]` renumbered temporaries across the whole function (401 to 31 register diffs).
- **Inline loads instead of m2c locals:** m2c locals such as `s32 a2 = p->unk10;` become `isvar` candidates. Writing the load inline lets every case share one CSE candidate (`{1354|n}`), and that fixed the allocation in three places. Keep the frame size with a block-scoped `s32 pad;`.
- **Switch operand casts:** `switch ((u32) a->u8field)` splits the switch operand from the later `a->u8field == K` compares into separate candidates, which changes which one reaches `v0`.
- **uopt does not pick the lowest free register:** in level-5/6 traces, the colourer picked the free register that the most still-uncoloured neighbours were forbidden from using, breaking ties toward the lowest number. A candidate can therefore get `a2` or `a3` while `v0` is free. Before concluding that priorities are wrong, check the forbidden sets of the neighbours.
- **Use the permuter for the last steps:** with the regalloc diff narrowed to one cluster, `tools/permute.py` hints showed the cause: a return-type change, and a load whose live range had to cover a particular basic block. Rewrite the hint as real C (here a block-scoped `s16 val = sp78->unk10;`); never paste permuter output.

## 7. Lessons From Matching func_8002A92C (boss `6240.c`, 0x2240 bytes)

A tracked draft that had gone stale went from 141 opcode-level diff lines to a ROM match in one session, commit `f2c122d`[^m92c]. The work was in stage order: names and prototypes first, then types, control flow, frame, and finally registers.
- **Get a full-function diff first.** asm-differ stops at 1024 lines. A throwaway script runs `mips-linux-gnu-objdump -dr` on both objects for the one function and runs `difflib` over (a) opcodes only, for stages 1–3, and (b) whole instructions, for stage 6. Reloc lines must be dropped, and immediates carrying a `R_MIPS_LO16` replaced: IDO emits `.rodata+off` where the asm has `D_xxx+0`. Note that objdump's reloc lines also match an `addr: text` regex.
- **Drafts go stale against later renames.** Callees named in `symbol_addrs*.txt` after the draft was saved (`func_80604CBC` → `sfxPlayActorSound`, `func_8002A5CC` → `bossSpawnSparkles`, …) still compile, because an undeclared extern links as a new symbol. `fdiff`/`objdiff` therefore show only a `jal` reloc-name diff, and the link fails only in the full build (`undefined reference`). Map every `func_`/`D_` in a draft against the symbol files before diffing, and copy each prototype from the matched callers in `src/`.
- **m2c float-as-int constants:** `0x43480000` passed to an `f32` parameter becomes a converted int (`lui 0x4e84`). Rewrite such constants as float literals (`200.0f`). In the same way, `ptr + 0xA4` on a typed struct pointer scales by the struct size, so write `&p->unkA4`.
- **Reading field types from the target loads:** `lbu`/`lhu`/`lw` vs `lh` show each field's real width. Fix the field types before any reordering.
- **Calls inline in arguments:** three `randomNonNegative()` calls written directly as `func_80714CC0` arguments reproduce the target. IDO spills the first result to a compiler temp below the locals and keeps the second in `s0`. Hoisting them into named locals reversed that assignment.
- **Duplicated tail jumps:** if every `case` arm in the target ends with its own reload + `b` to the switch end, write `break;` inside each `if`/`else` arm. An arm that falls through to a shared `break` jumps into the other arm's tail.
- **`a || flagGet()` condition order** decides which body IDO lays out first. m2c's `goto` into an `else` block is the inverted form.
- **Frame layout:** every declared local takes a slot in declaration order, register-resident ones included (here the `s1` state pointer). An unexplained 4-byte gap above the first `sp` local means a pointer is declared first. An extra 2-byte gap between an `f32` and an `s16` slot is another `u16` local declared there. Dropping m2c temporaries (`var_fv0`, `var_v0_3`, `temp_v0_2`) and writing the field loads inline both removed the slots and matched the reload pattern.
- **Table indexing:** `u8 *D_80035A20[][5]` with `tbl[cond ? 0 : 1][i]` produces the target's in-place `((v<<2)+v)<<2`. The flattened `tbl[v * 5 + i]` used a new register at each step. The second table symbol `D_80035A34` is `&D_80035A20[1][0]`.
- **Last v0/v1 diff:** declaring `actorMoveWithinZone` as `s32` rather than `void` moved two loads from `v0` to `v1` (see the return-type lesson above).

[^m92c]: commit `f2c122d` (`Boss/6240: match func_8002A92C`), `src/boss/6240.c`.

[^objdiff]: `tools/objdiff.py` compares whole sections and relocations (`main`, `text_matches`), then runs `/opt/asm-differ/diff.py` for display without `--max-size`. asm-differ's default is 1024 lines.

See also Decompile a function to matching C (guide decompile-function: python3 tools/quirks.py get decompile-function) and IDO matching quirks.

## Sources

[^ootguide]: https://github.com/n64decomp/oot/blob/master/docs/guides/-O2%20decompilation%20%28for%20IDO%205.3%29.md
[^uoptman]: https://techpubs.jurassic.nl/manpages_0530/cat1/uopt.html
[^chowhennessy]: https://doi.org/10.1145/88616.88621
[^uoptrace]: tools/uopt_trace.sh @ 07cd44383fbf
[^patch]: tools/ido/ecvt_fcvt.patch @ 07cd44383fbf
[^dockerfile]: Dockerfile @ 07cd44383fbf
[^permute]: tools/permute.py @ 07cd44383fbf
[^permuterdoc]: https://github.com/simonlindholm/decomp-permuter
[^makefile]: Makefile @ 07cd44383fbf
