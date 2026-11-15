# actorConfigLookup (global, src/global/8F050.c)
## Sites
- global:8068A3A0:do-while0:5c6932: REMOVED. It is an as1 line join (`i = 0; do {`), now tagged `// LAYOUT:`.
- global:8068A3A0:dead-if:fdc560 `if (actorType && actorType && actorType) {}`:
  - The dead test makes actorType candidate bit 0, so it keeps a0. Without it, actorType is bit 16, next takes a0, and actorType gets `move a2,a0`.
  - Only the order of actorType against next's `ustr` matters (found v1, outIndex a1, i v0 colour the same either way).
## Attempts
- rounds 15/16 (opus:low): diagnose/permute both (the permuter only re-adds dead uses / re-joins the line).
- 2026-11-14 U HackactorConfigLookup:
  - as1probe scan on the split copy: the only full=0 edits are the line join
  - init orders: 10; for/break: 14
  - fdc560: uopt -l 6 bit comparison
  - 10 body shapes, including early continue and one-case switch: 8-20
  - variants scan: 8
- 2026-11-15 U HackactorConfigLookup2, compare first in the loop (actorType gets a0, next a2, and as1 still hoists `addiu a2,v0,1` above the bnel):
  - `i = next` in the else arm: that block becomes `i = i + 1`, so IV elim strength-reduces `cfg[i]` to a pointer walk (`lh t6,0(t0); addiu t0,t0,20`): 11. With u16 i, IV elim is blocked but `andi v0,a2,0xffff` is added: 6.
  - `i = next` after the if: `next = i + 1; *outIndex = next;` forms one tree, so `i + 1` becomes a 2-use expression candidate (bit 24) on a3. The cfg base moves to t0 and `move v0,a2` moves into the beqz slot: 7.
  - Other compare-first shapes: `if (!found) i = next` 8; `i = next = i + 1` 14; `!=` arms swapped 19; rotated `i = next` at the loop top 17.
  - Boolean temps: a `match` temp before `next = i + 1` is its own candidate and sends actorType back to a2 (13). `found = (a == b)` computes the flag with xor/sltiu (5).
  - K&R definition, `register`/`const` actorType, actorType as s16/u16/s8/u32 (PROTO_SKIP copy): 8-14.
## Untried ideas
- fdc560: a compare-first body whose else arm keeps `next = i + 1` in a different basic block from both `*outIndex = next` and `i = next`, with no added code. This avoids the IV and the 2-use `i + 1` candidate. No natural spelling is known.
## Evidence
- leaf; table base a3 (lui at 0x50, addiu at 0x5c)
- move v0,zero at 0x60
- stride 20 via multu
- outIndex stored in the bnel delay slot
- `addiu a2,v0,1` at 0x6c comes before the compare; the found arm has `move a2,v0` in the b delay slot at 0x8c
