# effectSpriteRenderPool (global, src/global/114270.c)
## Sites
global:80710CA0:dead-if:2a0256 dead-if (kept): `if (count == 0) {}` in the state 3/5 arm. It creates the uopt candidate ucvt(count) (the u16 count promoted for `processed != count`) as candidate 34 instead of 125. uopt hoists ucvt(count) out of the loop, cannot colour it (-ve save), and spills it to a ugen spill temp. Spill temps are handed out top-down in candidate order, starting at 0x64(sp), just below the lowest cfe vreg -229. Without the guard, the texture-if's candidates come first: uilod D_807FDA1C (cand 111) and ucvt D_80755264[].count (cand 115), which are reused in the loop. They take 0x64 and 0x60, so count's slot becomes 0x5c (sw s0,0x5c(sp) at 0x19b4 and lw t6,0x5c(sp) at 0x1e4c, against 0x64 in the target).
global:80710CA0:other:03c0c4 other (fixed 2026-11-18): `i = 0x80;` placed before the texture if. It is now the declaration initialiser `s16 i = 0x80;`. Any position before the texture-if join keeps the target's entry test.

## Attempts
2026-11-11 round 14 CleanGlobal114270 opus-5-5:low: uopt_trace of the guard (flow blocks 7-8); permuter from v_nodead.c, best 8 via `D_807FDA1C ^ 0`; i = 0x80 beside the loop (a1/s0 swap at entry); permuter best 216 -> nohit
2026-11-11 round 16 Rev16K opus-5-5:low: i beside the loop (permuter), pad f32/f64[2]/none for the 0x5c/0x64 slot -> nohit
2026-11-12 round 17 Rev17L opus-5-5:low: i in the for init / after the texture if (text=25); declaration reorder / pad[2] for the count slot -> nohit
2026-11-13 round 38 CleanGlobal114270 opus-5-5:xhigh: trace6 final/nodead/imove; permuter rp_nodead (900 s, none below baseline), rp_imove best 216 -> nohit
2026-11-18 2026-11-17: cleanup CleaneffectSpriteRenderPool, CleaneffectSpriteRenderPool, anthropic/claude-opus-5-5: 03c0c4 FIXED with `s16 i = 0x80;` as a declaration initialiser (fdiff OK). The same i = 0x80 at the start of the init block, after skipNearPlayer = 0 or before gDPPipeSync also scores 0, so any position before the texture-if join works (Q1110). With i set at the loop (while / for (i = 0x7F; i >= 0 ...; i--) / for (i = 0x80; --i >= 0 ...;)) uopt folds the bltzl s5 entry test: 4 without the guard, 27 with it.
2026-11-18 (same unit): 2a0256 position and operand map on the fixed body. `count == 0` inside ANY conditional arm before the texture if matches: 3/5 arm, else arm, 0x42 arm, camState arm. As a top-level statement it fails: before the 3/5 if 34, after it 15, before gDPPipeSync 17, right before the texture if 203, after the texture if 4 (the same as removal). In the arm, `count != processed` scores 0. `1`, processed, skipTimer, `skipTimer && skipNearPlayer` and bare `if (count)` (no ucvt) all score 2 = removal; camState scores 12 and rem 8. Unrelated integer globals in the arm (D_807FDA1C, gGfxBufferIndex, D_807FDA1B, D_807FDAB4) score 2, which refutes lever 55B20/Q0530 for this site. Diagnostic only: deleting the texture if puts count back at 0x64.
2026-11-18 (same unit): permuter perm_ideclnd from the all-removed body (hack-free weights, -j 2, 900 s, base 16): the only output, best 8, respells the texture if as `(D_80755264 + D_807FDA1C)->count == 1`. count's temp moves from 0x5c to 0x60 (full=2), because one texture-if candidate stops holding a temp word, but it does not reach 0x64. This confirms the mechanism, but the spelling is a codegen-only steer -> nohit.
2026-11-18 (same unit): variants scan of the all-removed body: 63 variants, best 2 (no zero); width count s16/s32 230-236, processed s32 26.

## Untried ideas
- A real (code-emitting) read of count inside one of the four pre-texture arms that the target performs. None is visible in the asm 0x17a0-0x18a0, so this probably does not exist (asm).
- A texture-if spelling whose D_807FDA1C/.count candidates differ from the loop's (they would not hold spill temps). Every spelling tried changes the reload pattern in the loop (asm 0x1ac8 reloads D_807FDA1C per pass).

## Evidence
- Frame 0x150. Lowest cfe vreg -229 (0x6b), so the first spill temp is 0x64(sp). The target's only spill temp use is ucvt(count): `sw s0,0x64(sp)` in the beqz delay slot at 0x19bc and `lw t6,0x64(sp)` at the loop bottom 0x1e54.
- count is `lhu s0,0(t6)` at 0x1784 (the first block). s0 holds entry inside the loop (0x1a14).
- Loop entry: `li s5,127` at 0x19ac / bnel delay 0x199c, then `bltzl s5,exit` at 0x19b0 (unfolded constant test) and `beqz s0,exit` at 0x19b8 (processed = 0 folded).
- skipTimer and skipNearPlayer live at their homes 0xbe/0xbf(sp). processed is s6, i is s5, &D_807FDA1E is s7, the constant 4 is s8, mtxTemp is sp+200 and mtxScale is sp+264.
