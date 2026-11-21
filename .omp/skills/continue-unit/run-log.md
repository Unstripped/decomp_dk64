# Continue-unit run log

One row per unit (keep the last ~10). Debt from `bash autoresearch.sh` at start and end; stream deltas
from `uv run tools/debt.py --from .scratch/autoresearch/quality.json --progress .scratch/autoresearch/progress.json`.

|Date|Start → end debt|decomp|hack|polish|names|Slots (model)|Lesson|
|---|---|---|---|---|---|---|---|
|2026-11-20 (baseline)|17390|0|4710|568|12112|-|harness + debt.py + names stream added; no unit run yet|
