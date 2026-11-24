# menuUpdateLightFadeActor (menu, src/menu/E550_option_lights.c)
## Sites
menu:8003264C:other:5b6eb8 other (base line 55, removed): `s32 maxLevel = 0xFF;` steered the case-1 guard to `beq a0,v0` (255 in a0 first, fadeValue in v0) at 0x1f8; with `cur = field; if (cur != 0xFF)` uopt emits `neq $v1,$a0` -> `beq v0,a0`.
## Attempts
2026-11-09 cleanup pilot CleanE550 opus-5-5: int maxLevel / int cur,d / (cur ^ 0) -> int local and no-op arith match, s32 cur != maxLevel fails.
2026-11-11 round 9 CleanGlobal36880 opus-5-5:low: permute best=0 -> s32 maxLevel with `maxLevel != cur`, fdiff 0 (tagged FAKE 2026-11-18b PolishraceA960).
2026-11-18b PolishraceA960: literal 0xFF either side of != with the cur local -> 1 (0x1f8 only).
2026-11-24 intent pilot r2 CleanmenuUpdateLightFadeActor opus-5-5 (variants.py try scores; full=text):
- H1 role-named fn-scope `s32 target = 0xFF; level; step = MIN(target - level, 3)` -> 0. H2d same with case-3 literal -> 0.
- H2 block-scope target after lightSetFovAngles: inline MIN 2 (0x1f8 + addu t5,a0,v1 at 0x218), step statement 1, fn-scope level/step 1.
- H3 `const s32 target` -> 0; `u8 target` / `const u8 target` / u8 with case-3 literal -> 1.
- H4 `s32 step = 0xFF;` reused as step -> 0.
- Mechanism probes (fn-scope target, case-3 literal): assigned after the call 1; before lightSetFovAngles 0; block `{ s32 target = 0xFF; lightSetFovAngles(); ...}` 0; before the switch 0; target declared first 0; function-local `static const s32` 6.
- Literal with a cur local (Main levers): `(*gCurrentActor).fadeValue` 1; Actor * local for the read 17, for read+store 23; raw `*((u8 *)gCurrentActor + 0x15F)` 1; copy local only in the compare 1; decl order cur/d 1; field in the compare then `cur = field` inside 7; `(cur = field) != 0xFF` either side 1; int cur 1, u32 3, u8 8, u16 8, s16 41; 0xFFL 1, 0xFFU/0xFFUL 40; block-scope cur 1 (2 with inline MIN); `!(cur == 0xFF)` 1. variants.py scan on the literal copy: 25 variants, best 1. as1probe scan (literal copy): 1997 single edits, 0 improve.
- FIX: no level local, field read is the compare operand: `if (gCurrentActor->fadeValue != 0xFF) { gCurrentActor->fadeValue += MIN(0xFF - gCurrentActor->fadeValue, 3); }` -> fdiff 0 (also `0xFF != field`, and with a separate `step` local).
## Untried ideas
none open (site removed).
## Evidence
- 0x1e4 `lw s0,0(s1)`; 0x1e8 `li a0,255`; 0x1ec `mtc1 zero,$f6`; 0x1f0 `lbu v0,351(s0)`; 0x1f4 `li t6,1`; 0x1f8 `beq a0,v0,0x228`; 0x1fc `move v1,v0`; 0x200 `subu v0,a0,v1`; 0x204 `slti at,v0,3`; 0x20c `li a0,3` (delay slot); 0x214 `move a0,v0`; 0x218 `addu t5,v1,a0`; 0x21c `sb t5,351(s0)`; case 3 `slti at,v0,255` 0x334.
- uopt ucode (as1probe keep/ucode): with `cur` (isvar) vs 255 cfe emits `lod cur; ldc 255; neq` and uopt keeps `neq $v1,$a0`; with the field expression `ilod u8 351; cvt s32 u32; ldc 255; neq` uopt emits `neq $a0,$v1` (target order). cfe emits the same operand order in both, so uopt makes the swap; [INFERENCE] candidate ordering with isvar candidates ahead of the constant and the constant ahead of an expression (Q0474).
- A constant-valued local assigned in case 1 after the `jal lightSetFovAngles` (0x1dc) gives `neq $v1,$a0` like the literal (h2b ucode); assigned before the call it keeps source order `neq $a0,$v1` (base ucode). [INFERENCE] same-block copy propagation turns it into a literal before the operands are ordered.
- Knowledge: Q0690 (compare the global/field directly instead of a loaded local fixes the beq operand order) is the lever that removed the site; Q0756 (a value-named constant local compensating for the m2c field-copy local) is the same artefact pattern. The cur/d locals were m2c's; maxLevel compensated for cur.
