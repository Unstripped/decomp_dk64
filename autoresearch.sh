#!/usr/bin/env bash
# Remaining-work benchmark for the DK64 decomp: one weighted "debt" score over every
# decompilation and cleanup task the repo tools measure. Lower is better.
#
# Gate first: a full rebuild (every src/*.c touched, since make has no header deps) must end
# with `build/dk64.us.z64: OK`; a non-matching tree fails the benchmark (exit 1).
# Then: tools/progress.py --json (unmatched functions, asm data) and
# tools/quality.py report --json (hacks, warnings, review/exhaustion, names).
set -euo pipefail
cd "$(dirname "$0")"
out=.scratch/autoresearch
mkdir -p "$out"

find src -name '*.c' -exec touch {} +
if ! tools/dk make >"$out/make.log" 2>&1 || [ "$(tail -n 1 "$out/make.log")" != "build/dk64.us.z64: OK" ]; then
	tail -n 30 "$out/make.log" >&2
	echo "autoresearch: build is not matching" >&2
	exit 1
fi

tools/dk python3 tools/progress.py --json >"$out/progress.json"
uv run tools/quality.py report --json >"$out/quality.json"

python3 - "$out/progress.json" "$out/quality.json" <<'EOF'
import json, sys

prog = json.load(open(sys.argv[1]))["total"]
q = json.load(open(sys.argv[2]))["total"]

fake = q["FAKE"]  # every tagged FAKE kind; goto/proto-type are counted on their own rows
m = {
    "unmatched_funcs": prog["total_funcs"] - prog["matched_funcs"],
    "asm_data_bytes": prog["data_asm_bytes"],
    "fake": fake,
    "goto": q["goto"],
    "layout": q["LAYOUT"],
    "proto_type": q["proto-type"],
    "sites_open": q["sites open"],
    "unreviewed": q["functions"] - q["reviewed"],
    "cfe_warnings": q["cfe warnings"],
    "uninit_warnings": q["uninit warnings"],
    "protos_mismatch": q["protos mismatch"],
    "func_defs": q["func_ defs"],
    "m2c_names": q["m2c names"],
    "unk_fields": q["unk fields"],
    "d_refs": q["D_ refs"],
}
# Weights: decompilation > codegen hacks > ladder/review/warning debt > names.
W = {
    "unmatched_funcs": 100, "asm_data_bytes": 0.25,
    "fake": 20, "goto": 20, "layout": 10, "proto_type": 10,
    "sites_open": 5, "unreviewed": 5, "cfe_warnings": 5, "protos_mismatch": 5,
    "uninit_warnings": 2, "func_defs": 2, "m2c_names": 2,
    "unk_fields": 1, "d_refs": 1,
}
debt = sum(W[k] * v for k, v in m.items())
print(f"METRIC debt={debt:g}")
for k, v in m.items():
    print(f"METRIC {k}={v}")
EOF
