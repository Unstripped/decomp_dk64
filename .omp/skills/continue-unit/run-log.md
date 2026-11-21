# Continue-unit run log

One row per unit (keep the last ~10). Debt from `bash autoresearch.sh` at start and end; stream deltas
from `uv run tools/debt.py --from .scratch/autoresearch/quality.json --progress .scratch/autoresearch/progress.json`.

|Date|Start → end debt|decomp|hack|polish|names|Slots (model)|Lesson|
|---|---|---|---|---|---|---|---|
|2026-11-20 (baseline)|17390|0|4710|568|12112|-|harness + debt.py + names stream added; no unit run yet|
|2026-11-20/21 unit 1|17390 → 6609|0|4710 → 4595|568 → 520|12112 → 1494|6 (opus-5-5 xhigh): 16 names, 1 types, 2 review, 10 hack, 1 uninit|names first (70% of debt, hack/polish EXHAUSTED); 6 names windows (~1360 renames) carried with header-carve; re-measuring knowledge-staled hack rungs removed 5 FAKE; uninit reads are original flow (36880: 34/34 kept); LAYOUT lines are not sites (rulings): do not chase|
|2026-11-21 unit 2|6609 → 5419|0|4595 → 4530|520 → 553|1494 → 326|6 (opus-5-5 xhigh): 10 lever transfers + 3 re-diagnoses, 9 names, 1 union carve, 1 types, 1 folds, 1 scout|lever transfers yield ~20% (2/10; Q1593 switch respelling); check each lever's precondition on the target asm first. Filing knowledge reopens the named functions' other sites: send them to the idle worker that holds the traces. Header edits (union members, renamed fields) stale automatic rungs that header-carve cannot carry: one `quality.py sweep --record` over the hack files (~1 min) restores them. Names residue is now held items; decoding sprite sheets / ROM text tables gave the evidence for ~150 asset names|
