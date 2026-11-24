# Intent-analyst brief template (intent-first pilot, issue #2)

Fill `<...>` into `.scratch/briefs/<You>.md`; task: "Read `.scratch/briefs/<You>.md` FIRST and follow it exactly".
The matching worker then gets `brief-hack.md` plus the "Intent-first pilot" section below.

````
# Goal
Intent analysis (pilot, round 2) for matched functions of the Donkey Kong 64 (USA) decomp, repo
<repo root> (ALWAYS absolute paths under it). Read AGENTS.md first.

Functions (<seg>, <src/seg/file.c>):
- <FUNC> (line N): `<the FAKE line, verbatim>`
Each matches but carries a `// FAKE` steer (quoted above). Earlier agents treated it purely as a
codegen problem (dossier drafts/quality/dossiers/<seg>/<FUNC>.md if present; `uv run tools/quality.py
history <FUNC>`). Your job: work out what the original programmer wrote each function FOR, and what
the steered statement means in the programmer's terms, so that a second agent can try a hack-free match
from intent-level C. You do NOT write or compile candidate C: the separation is the experiment.

# Rules
- Never edit `src/`, `include/`, `knowledge/`, `drafts/` or ok-fine; never commit; never run
  `tools/dk make`, `make split`, `make expected`, `fdiff.sh`, `permute.py`, `variants.py`,
  `deadsweep.py`, `as1probe.py`. Scratch only under `.scratch/<You>/`.
- Allowed: reading src/include/asm/symbol files, the expected objects (`expected/build/<src/seg/file>.o`; objdump
  via `tools/dk`), `lsp` references, `python3 tools/quirks.py` (`func <FUNC>` first), `tools/dk python3
  tools/similar.py -s <seg> <FUNC>`, ok-fine reads (project dk64: search_concepts for the subsystem),
  and optionally the emulator (read skill://emulator first) when runtime observation settles a question.
- Never fetch or read the community DK64 decomp or any external C of this game. For libultra- or
  SDK-shaped code you MAY cite the public N64 SDK/ultralib headers already in `include/` (GBI macros,
  OS structs) as evidence of idioms the programmer had available.
- Matching validates emitted bytes only, not meaning: every claim cites evidence (file:line,
  target-asm offset, caller, runtime trace). Unverified claims are labelled [INFERENCE]; a shape that
  merely suffices for the bytes is never stated as what the original was.

# Questions, per function
1. Purpose: what callers use it for; what the fields/locals it touches mean (struct definitions, other
   writers/readers of the same fields).
2. The steered statement: what it computes in the programmer's terms; which idioms a programmer of
   this codebase (or of the SDK it builds on) would naturally use there: a GBI/OS macro, a
   MIN/MAX/CLAMP-style macro, a named constant/#define, a struct field instead of a literal, a list
   helper, a different but equivalent control structure. Find how matched siblings in this codebase
   write the same idiom (grep, similar.py) and cite them.
3. Target facts the intent-level C must reproduce (from the dossier/FAKE comment; verify offsets in
   the expected object).

# Output
Write `.scratch/<You>/intent.md`, one section per function:
```
# <FUNC>: intent
## Purpose            (paragraph, confidence high/medium/low, evidence)
## Steered statement  (meaning, evidence)
## Source hypotheses  (ranked; each: C sketch <= 12 lines, intent it expresses, target facts it must
                       reproduce, whether the dossier/history already measured an equivalent shape
                       (cite line and score); never present a tried shape as new)
## Proposed names     (only with evidence)
## Open questions
```
Final message: the path, the top hypotheses one line each, and IDO findings for the orchestrator.
````

## Section appended to the matching worker's brief-hack.md

````
# Intent-first pilot (this run)
An intent agent already analysed what the original programmer wrote these functions FOR:
read `<repo root>/.scratch/<IntentAgent>/intent.md` right after the dossier(s).
- Work its ranked source hypotheses FIRST, in order, before any codegen-only idea. For each: write the
  intent-level C, fdiff it; if it misses, diagnose why in register/offset terms (uopt_trace, as1probe)
  and try respellings that keep the same intent. Only then fall back to other ideas.
- The intent doc may state inferences as facts: treat any claim about what the ORIGINAL source was as
  inference unless it cites target-asm evidence; a shape that suffices for the bytes proves only that.
- Every ledger line on a site carries `new="intent:<hypothesis #> <what>"` (control arm: `new="control:..."`);
  a hypothesis the intent doc marks as already measured is skipped, not re-run.
- Report section `## Intent pilot`: per hypothesis, fdiff exit/score and stage reached; what the intent
  analysis changed about where you searched; where the intent doc was wrong (with evidence).
- Do not rename cross-file symbols; propose names in the report. Tag/ruling questions are the
  orchestrator's: report evidence, don't retag on your own.
````
