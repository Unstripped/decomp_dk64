# volumeTriggerUpdateAll (global, src/global/1332B0.c)
## Sites
global:8072E868:other:8202af other: REMOVED. Was `if (hooks[e->def.actions[j].hookIndex].condition == NULL || ...condition())` with the body reading hookIndex through a separate `action` pointer; the mixed spelling kept uopt from CSEing the hook address across the NULL edge, so the body reloads lh 16(s0) at the join and recomputes the address into v0.
## Attempts
2026-11-12 cleanup round 20 CleanGlobal1332B0 anthropic/claude-opus-5-5: views/names/review; plain sweep no rewrite; uopt diagnose; permute best=0 (only moved the mixing) -> kept
2026-11-12 cleanup round 20 Rev20B anthropic/claude-opus-5-5:low: hookIndex via action in the condition -> uopt CSEs the hook address (FiredX/Y bases s7/s8 -> s6/s8)
2026-11-12 cleanup round 20 Perm20B anthropic/claude-opus-5-5: permute best=0, respelling only -> kept
2026-11-14 HackvolumeTriggerUpdateAll anthropic/claude-opus-5-5:high: variants.py try scores (full=): all through e->def.actions[j] with || 27; hook pointer local in body 35 / 71 (via action); action pointer incremented 41; all via action 69; action assigned inside the if 46/45; hook pointer for the condition 32; function-pointer local for the condition 27; `fire` flag + if 7; early `if (cond != NULL && !cond()) continue;` with every access through e->def.actions[j] 0 -> applied, fdiff exit 0, clint uninit exit 0, cfe warnings 0. Same continue form through an `action` local: 69. `delayed = x == 0xA` 43, `delayed = FALSE; if (...) delayed = TRUE;` 18: the `? 1 : 0` ternary stays.
## Untried ideas
none open (function hack-free)
## Evidence
0x3e8-0x3f4: condition lh 16(s0); sll; addu t7,s3,t6; lw v0,12(t7) (condition address in a temp, dead after the test).
0x3f8: beqzl v0 with lh t8,16(s0) in the delay slot (NULL edge goes straight to the body reload); 0x408: beqzl v0 to the loop tail after jalr.
0x410-0x420: join reloads lh t8,16(s0), sll, addu v0,s3,t9: the body address is recomputed on both edges, which the early-continue shape gives (Q0773 block shape, Q0158 per-path reload).
0x42c-0x438: bne s4(10),t1 / b / li v1,1 over v1=0: `delayed = actorType == 0xA ? 1 : 0`.
