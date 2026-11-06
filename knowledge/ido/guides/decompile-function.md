---
title: "Decompile a function to matching C"
description: "Steps to convert a splat asm file to C and replace one GLOBAL_ASM function with matching IDO C, using the m2c helper, asm-differ diff.sh and the progress report."
origin: "ok-fine dk64/runbooks/decompile-function"
---
# Decompile a function to matching C

1. In the segment's splat yaml (`dk64.us.yaml`, `dk64.global.us.yaml`, `dk64.<overlay>.us.yaml`), change the file's subsegment from `asm` to `[0xOFFSET, c, dir/name]`, then `tools/dk make split`. splat creates `src/dir/name.c` with one `#pragma GLOBAL_ASM(...)` per function.[^agents]
2. Starter C: `tools/dk python3 tools/m2c.py [-s SEGMENT] FUNC` (SEGMENT `boot` default, `global`, or overlay name). It finds the asm in nonmatchings or a whole-file `.s`, adds referenced rodata files (jump tables, literals) and uses a context preprocessed from `include/common.h` (`build/m2c_ctx.c`).[^m2c]
3. Replace one pragma with C. Declare callees in headers under `include/` (extend `ultra64.h` for libultra).[^agents]
4. `tools/dk make`. On mismatch: `tools/dk ./diff.sh [-s SEGMENT] FUNC` (asm-differ; `-n` skips the rebuild, `--format plain` for non-interactive output). `diff_settings.py` diffs boot as `build/boot.bin` vs `baserom.us.z64` and global/overlays as `build/<name>.bin` vs `bin/segments/<stream>.bin`, using each segment's map file for offsets.[^diffsettings]
5. If the function does not match on the first pass (especially non-trivial functions or register-allocation near-misses), follow the methodology in Large functions and near-misses (guide large-functions-and-near-misses: python3 tools/quirks.py get large-functions-and-near-misses): diagnose priority-based register allocation with `tools/uopt_trace.sh`[^uoptrace], run `tools/permute.py`[^permute] for search hints at stages 5–6, or park reviewed behaviourally equivalent C under `#ifdef NON_MATCHING`.
6. Name the function and discovered symbols in `symbol_addrs.us.txt` (boot/global) or `symbol_addrs.<overlay>.us.txt`; re-split.[^agents]
7. `tools/dk make progress` reports matched/total function bytes per segment (`tools/progress.py --json` for machine output). Matched completion includes compiled C plus the explicitly approved generated-assembly files in `handwritten_asm.json`; C and handwritten counts are reported separately. Unlisted assembly and `GLOBAL_ASM`/`INCLUDE_ASM` placeholders remain unmatched. Totals use ELF function symbols, excluding alignment padding and data embedded in text. The registry contains classification metadata, never game data.[^progress][^handwritten] See Handwritten assembly accounting (ok-fine dk64 decisions/handwritten-assembly-progress).

Reference example: `dmaCopy` (`0x80000450`) in `src/boot/main.c`, the first matched function.[^main] See IDO matching quirks and Large functions and near-misses (guide large-functions-and-near-misses: python3 tools/quirks.py get large-functions-and-near-misses).

## Sources

[^agents]: AGENTS.md @ 90ef77a58d13
[^m2c]: tools/m2c.py @ 90ef77a58d13
[^diffsettings]: diff_settings.py @ 90ef77a58d13
[^uoptrace]: tools/uopt_trace.sh @ 90ef77a58d13
[^permute]: tools/permute.py @ 90ef77a58d13
[^progress]: tools/progress.py @ 90ef77a58d13
[^handwritten]: handwritten_asm.json @ 90ef77a58d13
[^main]: src/boot/main.c @ 90ef77a58d13
