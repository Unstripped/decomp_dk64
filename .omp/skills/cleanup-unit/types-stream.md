# Types stream (`TypesOwner`)

Header and shared-type work is its own stream with ONE owner: `TypesOwner` is the only agent that
edits `include/`, always in its private batch copies; the lead gates its batches. Workers never
edit `include/`: they write the hunk to `.scratch/<A>/header-request.md` and message the lead,
which forwards it (`write agent://TypesOwner`).

## Queue

1. pending.md "Blocked owner/header changes" (oldest first, skipping items marked held or closed);
2. forwarded header requests, in arrival order.
Each batch works in `.scratch/TypesOwner/batch_<n>/` and first writes `files.txt`: every src file and
header it edits, one path per line. The lead dispatches no worker on a listed src file while the batch
is open, and a batch that reaches a file a worker holds waits until that worker's merge.

## Headers (unchanged rules)

A function defined in the agent's own file needing a new prototype type is no header request: it
retypes the definition with a stand-in (`#define PROTO_SKIP_<f>` + declaration), merged via SKILL §5.4.
A handwritten-asm function (no C owner, so no generated `include/proto/` header) gets ONE prototype in the topical game
header next to its types (render.h `func_8065C990`, OwnerAsmLightProjProto 49d39602); callers drop their local declarations.
Applying a request: carve only padding, keep landed names, list users with `uv run tools/rename.py
field --dry-run include/<h>.h <Struct> <field> zzProbe` (+ text-grep casts), skip checked-out files'
fields; snapshot and edit users, objdiff each, `clint.py layout --base HEAD include/<h>.h` → `LAYOUT
OK`, `tools/merge_gate.sh --commit "include: <what>" --stage include/<h>.h - - <src files>` (anchor
one includer). A header commit stales the automatic rungs of every function reaching the changed
declarations (`fp_hdr2`). Gate a field TYPE change apart from carves/moves: `carry --header-carve`
then plain `carry --rev <commit before> <files>` re-stamp carves, moved types, respelled declarations
and pure typedef renames, never a type change. Before committing a widely reached change, measure the stale cost with the header AND its user copies temp-swapped (header alone: users stop compiling) — full `status` before/after, then `carry --dry-run` in a temp worktree holding the commit (`cp -r asm/`: a symlink fails under dk; worktree `status` without a build ELF fails, use per-file status): functions losing fresh
non-sweep rungs AND EXHAUSTED→OPEN (r18 0xEC union: 112 re-opened, one sweep; r34 MpSettings: 357 raw, 18 after carry). Hold above ~100 non-sweep losses; sweep the rest. A header change bundled with ANY body edit stales that body's agent rungs: measure even "automatic-only" changes (r34 s8: restored the local).

## Callee-prototype batches

Callee-prototype work is prepared by `TypesOwner` in `.scratch/TypesOwner/batch_<n>/`
(owner + caller copies, `measure.json` per-file cfe before/after, `ledger/<file>.txt`; verify header edits with make's compile
and `-I include` swapped for a full `include/` copy: `fdiff.sh`/`cwarn --as` shadow-prepend, so headers nested in proto headers hit the repo's). Measure on the
checked-out workers' copies too: if any would rise, hold the batch and gate it together with those
copies after their merge. Merge owner + callers, `protos.py gen`, objdiff every includer, one gate with every `--stage`d
header; sweep + carry. A batch stales the review of every caller whose BODY it edits: those show as
`next=review` in `rank --polish` and go out as polish work.

## Gating a batch (lead)

1. The stale-cost measurement above; hold or split a batch above ~100 non-sweep losses.
2. `tools/merge_gate.sh --commit "include: <what>" --stage include/<h>.h ... - - <srcs>` (or
   `.scratch/TypesOwner/batch_<n> <base> <srcs>` when the batch holds src copies); read `GATE_OK`
   and `COMMITTED`.
3. Record the batch's ledger lines as `merge_record.py` does after its gate: `uv run tools/quality.py
   record --unit "<YYYY-MM-DD>: cleanup TypesOwner" --agent TypesOwner --base <batch base> --model <selector>
   --batch <ledger>`; `tools/dk make expected`; `quality.py sweep <srcs> -j 4 --record --unit ...`;
   `quality.py carry --rev <merge>^ --unit ... <srcs>` (plus `--header-carve` for layout-keeping carves);
   commit `drafts/quality`.
4. Remove the batch's `files.txt` (its files return to the queue); move a closed pending.md item to
   its outcome line.

## Special merges (SKILL §5)

- A copy that changed a non-static signature carries stand-in `#define PROTO_SKIP_<f>` + declarations:
  run `clint uninit --base` on the stand-in copies (after gen the base no longer parses: exit 3), strip both
  into clean copies (`.scratch/<A>/clean/`), copy EVERY clean file of the bundle over src together, one
  `protos.py gen`, restore src, compare with header.patch, then merge the clean dir with one `--stage
  include/proto/<seg>/<f>.h` per regenerated header (a partial gen misses headers: DS/90D80.h); `gen --check`
  exits 0. Shadow headers must also shadow, unchanged, every `include/*.h` that quote-includes a shadowed one.
- Bundles: strip stand-ins, apply the `.patch` (not shadow headers), merge, gen, objdiff callers
  (`--reloc-ok`), one gate. Copies keyed by the same basename (`boss/52B0` vs `race/52B0`,
  `critter/0` vs `minecart/0`) need separate dirs and gates, unless they all see the changed header (a partial gate breaks the
  others: redeclaration): then cp every copy over src, snapshot, ONE `merge_gate.sh --commit --stage <h> - - <srcs>` (2026-11-16d
  gPlayerCharacterId: critter/0, menu/0, multiplayer/0). dkd refreshes host-rewritten inputs before every job (58d28dba), so
  no `--stop` after a header swap. Generated `include/proto` output is the source of truth over a worker's header.patch. Copies
  rebuilt as HEAD + per-file patches merge with `--base HEAD` after a ledger dry-run at HEAD. Multi-part batches: one gate per
  part, lead copies = HEAD + `part<X>_src.patch`; a part whose header hunk no longer applies (an earlier part changed its context)
  takes the batch's combined header after checking its diff vs the checkout is exactly that part's hunks. Record a batch ledger
  at the MERGE commit (the base no longer compiles against the new header). A shared array extern keeps `T x[];` when users
  declared `[]` (`carry` treats `[]` -> `[N]` as a changed declaration). A user that only matches with its own declared type,
  proven by the target (52B0 s16 vs race/0 u16 gTextNumberArg), keeps it as `// ORIG:` and the extern goes into a header that
  file does not include.
- A `COMMIT_FAILED` after `GATE_OK` (concurrent `.git/index.lock`): commit the gated src by hand, then
  merge_record's steps 3-10. Commit explicit paths only; headers go in `--stage`, never as a gate file argument.
- A copy whose file changed since its base merges 3-way (`<copy-dir> <base>`); a copy retyping a shared global's
  extern: fix every other file's extern in the SAME gate (objdiff each; a file whose cfe would rise or that no
  longer compiles keeps its type and goes to pending.md).
- Data to C: merge_drafts refuses dropped `#pragma GLOBAL_ASM` data labels (lost-symbol guard): cp the copy
  over src, `merge_gate.sh --commit - -` (snapshot), steps 3-10 by hand. A yaml carve (`--stage dk64.*.yaml`)
  re-splits only the gate tree: merge_record then fails at `make expected`; once `tools/dk --status` shows
  jobs 0 (never `make split` under a running job), `make split`, touch src, `make`, `make expected`, steps 5-10.
  A renamed carved data object passes `fdiff --reloc-ok` only with its name in symbol_addrs (19A00 convention:
  non-static s-name + symbol_addrs line, staged in the gate).
- merge_drafts' "restore deleted local declaration" misses a local in a declarator list with an initialiser
  (`s32 count = 1, n = 4;` → re-inserted `s32 n;`, redeclaration): split such declarations in the copy.
- Lead records (copy-only, carry, consolidate): quality.py agent names take no `-` (`CleanupLead2`, not `CleanupLead-2`). After a
  ledger-only merge, stale automatic `consolidate` rungs get `protos.py consolidate <src> --out DIR` and one
  `<key> consolidate nohit note="protos.py consolidate at <rev>: STEER|PROTO ..."` line as the lead (a42e7e8a, 39d260d0).
