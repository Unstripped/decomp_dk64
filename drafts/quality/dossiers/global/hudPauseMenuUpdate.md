# hudPauseMenuUpdate (global, src/global/ACDC0.c)

## Sites

global:806A8158:dead-if:a7bed8 dead-if: FIXED in `.scratch/HackhudPauseMenuUpdate2/ACDC0.c` (pending the ACDC0 .data carve). The dead entry read `if (sPauseSaveCooldown) {}` existed only to stop uopt building one lda address web for the extern global; as a function-local `static s8` the variable keeps a lui/%lo pair per access and the read is unnecessary.
global:806A8158:dead-if:3a273f (older key of the same site): entry read of D_807505D4 keeps its address unpointerised so the end decrement/clamp uses fresh lui pairs and the s8 truncation (0xf64-0xf8c) (KEPT until 2026-11-15).

## Attempts

2026-11-10..12 (low, medium): as1probe, permutes (self-assignment, *0 fold)
2026-11-14 HackhudPauseMenuUpdate opus-5-5:high: end respellings (29-34), snapshot locals (58-64), pointer local (48), mid test as !x / switch / <= 0 (29-30)
2026-11-14 PermBatch1114c opus-5-5:high: permbatch 900 s hack-free weights (nohit)
2026-11-15 HackhudPauseMenuUpdate2 anthropic/claude-opus-5-5:high: `static s8 sPauseSaveCooldown = 0;` at the top of the function, extern and dead read removed -> objdump -drz: every .text word equal, 12 HI16/LO16 relocs name `.data` instead of `sPauseSaveCooldown` (fdiff exit 1 only for the new 16-byte .data and reloc names); clint uninit 0. Needs the ACDC0 .data carve (`.scratch/HackhudPauseMenuUpdate2/carve-request.md`, ROM 0x1551E0-0x155300), verified byte-exact in `.scratch/HackhudPauseMenuUpdate2/carve/ACDC0.c`.
2026-11-15 HackhudPauseMenuUpdate2 review: dropped the redundant `(f64)` in `(f32)((f64)(f32)flag * 0.9)` (text words equal).

## Untried ideas

none: site fixed.

## Evidence

0x260/0x264 `lui at` / `sb zero,%lo(sPauseSaveCooldown)(at)` (init), 0x798-0x7e8 cooldown test and `li t8,45` store, 0xf64 `lui t7` / 0xf68 `lb t7` / 0xf74 `addiu t8,t7,-1` / 0xf84 `sb t8` / 0xf8c `sb zero`: every access its own lui/%lo pair = function-local static (Q0761).
Data order: ACDC0 file-scope data 0x807504E0-0x807505D4, then statics sPauseSaveCooldown (0x807505D4, hudPauseMenuUpdate), D_807505D8 (hudPauseMenuBuildPage), D_807505F8 (hudDrawTwoOptionMenu, two separate lui pairs at 0x4e64/0x4ed0): statics after file-scope data in function order.
