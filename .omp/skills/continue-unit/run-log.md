# Continue-unit run log

One row per unit (keep the last ~10). Debt from `bash autoresearch.sh` at start and end; stream deltas
from `uv run tools/debt.py --from .scratch/autoresearch/quality.json --progress .scratch/autoresearch/progress.json`.

|Date|Start → end debt|decomp|hack|polish|names|Slots (model)|Lesson|
|---|---|---|---|---|---|---|---|
|2026-11-20 (baseline)|17390|0|4710|568|12112|-|harness + debt.py + names stream added; no unit run yet|
|2026-11-20/21 unit 1|17390 → 6609|0|4710 → 4595|568 → 520|12112 → 1494|6 (opus-5-5 xhigh): 16 names, 1 types, 2 review, 10 hack, 1 uninit|names first (70% of debt, hack/polish EXHAUSTED); 6 names windows (~1360 renames) carried with header-carve; re-measuring knowledge-staled hack rungs removed 5 FAKE; uninit reads are original flow (36880: 34/34 kept); LAYOUT lines are not sites (rulings): do not chase|
