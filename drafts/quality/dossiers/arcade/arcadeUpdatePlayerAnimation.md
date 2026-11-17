# arcadeUpdatePlayerAnimation (arcade, src/arcade/0.c)
## Sites
- arcade:8002B390:dead-if:104665 (kept): removal 5 (D_8004C710 address v0 vs v1).
## Attempts
- 2026-11-14 opus:high: switch / inverted 76; u32 snapshot 5; D_8004A764 snapshot 50.
- 2026-11-17 2026-11-17: cleanup HackarcadeDrawStage4Background2 HackarcadeDrawStage4Background2 anthropic/claude-opus-5-5: `ArcadeEntity *ent` pointer local for every `D_8004BCD0[entIndex]` 158; state 8 inverted (`if (D_8004C71B != 0)` first, else-if 48.0f, else-if D_8004A764 == 0) 37; return-free if/else-if chain 7; `else if (D_8004A764 == 0)` 5; bare `!D_8004C71B` / `!D_8004A764` 5; variants scan of the removed form (55) best 5. Casts: `(f64)` on animTimer / 4.5, five `(f32)` int-to-float and the `(s32)` on val are not needed (fdiff 0): dropped; `val & 1` / `val & 3` instead of re-truncating animTimer 136.
## Untried ideas
- none from the local asm: D_8004A764 is shared with arcadeDrawHud and the init at line 1526, so the function-local-static fix (Q1125) does not apply; every natural respelling leaves &D_8004A764 in v0.
## Evidence
- target: `lui v1,%hi(D_8004A764)` 0x7684, `addiu v1,v1,%lo` 0x7694 (v1 held &D_8004C71B from 0x7658), `lbu t8,0(v1)` 0x769c/0x76f4, `sb t9,0(v1)` 0x770c.
- trace: guard -> address webs 182/210 both reg 2 (v1); removal -> 209 reg 2, 214 reg 1 (v0) (Q0710: the dead read only adds the web as an earlier candidate).
