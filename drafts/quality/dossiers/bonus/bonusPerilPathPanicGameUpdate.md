# bonusPerilPathPanicGameUpdate (bonus, src/bonus/2690.c)

## Sites
- bonus:8002A398:other:aef7f0 (other, now ORIG): `p = *gMinecartTrackPoints + (n + n + n) + 1;` keeps `addu t6,v1,v1; addu t7,t6,v1` (0x401c/0x4020) before the `sll/subu/sll` *12 chain (Q0337). Every `n * 3` spelling folds the +1 and *12 into n*36+12 and shifts the block. The target computes n + n + n itself, so this is the original spelling (Q0656/Q0708) and the line now has an `// ORIG:` comment with those offsets.
- bonus:8002A398:dead-if:f3276d (dead-if, REMOVED): `if (u) {}` between scaleX and scaleY. With the lane as a function-local static it adds a store-back `lui at; sb v1,%lo(.data+0x44)(at)` (0x408c/0x40dc in the copy). With the guard removed, the block matches. The removal is coupled with fe755f.
- bonus:8002A398:other:fe755f (other, REMOVED): `((s8 *)&sPathPanicSnapDelay)[4] = (u16)(1 - n);`. The variable at sPathPanicSnapDelay+4 (.data+0x44, 0x8002D904) is the `s8` sPathPanicFairyLane. Only this function uses it, so it becomes a function-local `static s8 sPathPanicFairyLane = 0;` (Q0761/Q0922): each access keeps its own lui/%lo pair, and the plain `sPathPanicFairyLane = 1 - n;` gives the target `lui at / subu t7,t4,v1 / sb t7,%lo(..)(at)` at 0x40f0-0x40f8. D_8002D908 and sSearchlightTargetSpeed now come after the function, so the static keeps .data+0x44 (Q0761: .data follows source order, function statics included).

## Attempts
- 2026-11-16 HackbonusPerilPathPanicGameUpdate anthropic/claude-opus-5-5:high: lane as a function-local static + plain store, both other sites kept -> extra `lui at`/`sb v1,.data+0x44` store-back at the end of the spawn block (fdiff 1).
- same: static + plain store + `if (u) {}` removed -> fdiff 3 TEXT OK, `--reloc-ok` RELOC-EQUIV OK. Raw words equal except the LO16 addends: `sb zero,68(at)`/`lb v1,68(v1)` x2/`sb t7,68(at)` against .data versus `0(...)` against sPathPanicFairyLane (.data 0x44) and `4(at)` against sPathPanicSnapDelay (.data 0x40). All resolve to .data+0x44. The HI16 words are identical (lui 0x0000), and the .data bytes are identical.
- same, static base: `n * 3 + 1`, `(n * 3 + 1)`, `3 * n + 1`, `1 + n * 3`, `&(*gMinecartTrackPoints)[n * 3 + 1]` -> text 96. `n *= 3` and `n = lane * 3` -> text 26. `p = base + 1; p += n * 3` -> text 140. `base + n + n + n + 1` (no parens) -> text 61. `n * 2 + n` -> the only diff is `sll t6,v1,1` at 0x401c. `n += n + n` and `[n + n + n + 1]` are equal to the base.
- same, static + `n + n + n` + `if (u) {}` variants: s8/s16 `n`, the init store moved first, RMW `lane = 1 - lane`, a per-role `lane` local -> all keep the store-back. `static volatile s8` -> text 76. Hoisting `n = lane` before actorSpawn -> text 28/81.
- same: permuter on the natural `n * 3` static base, 900 s, -j 2: base 2069, best 1175 (self-assignment hacks), not applied.
- 2026-11-16d HackbonusSearchlightSeekGameUpdate5 anthropic/claude-opus-5-5: aef7f0 tagged as `// ORIG:` (two addu at 0x401c-0x4020 are the line's own operations, like osTvType + osTvType in Q0656/Q0708). Code unchanged, fdiff 0, clint uninit 0, cwarn 0.

## Untried ideas
- (none)

## Evidence
- Target 0x3d44 `lui at; sb zero,%lo(lane)(at)`, 0x4000 `lui v1; lb v1,%lo(lane)(v1)`, 0x40dc `lui v1; lb v1`, 0x40f0 `lui at` ... 0x40f8 `sb t7,4(at)`: each access has its own lui/%lo pair, and no lda base is shared = function-local static (Q0761/Q0922).
- Level-5/6 trace of the matching copy (static, no `if (u) {}`; `.scratch/HackbonusPerilPathPanicGameUpdate/tr5.txt`/`tr6.txt`): the static is candidate 13 (`isvar S 166`, live bbs 1/27/28, adjsave 1.0, hasstore), "13 assigned (constrained) 2". The store-back variant (with the guard) was not traced, so why the guard adds the `sb` is unexplained.
- Permuter result: 900 s, base 2069, best 1175 (output-1175-1). It uses self-assignments `lane = lane` and `new_var = lane * 3`, which are hacks, so it was not applied. No zero.
