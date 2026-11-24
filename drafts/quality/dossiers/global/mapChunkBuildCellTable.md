# mapChunkBuildCellTable (global, src/global/55B20_map_chunk.c)
## Sites
- global:80651904:dead-if:4f3f72 `if ((size & list) && (size & list)) {}` after `list += 8` (kept). The second `size & list` is a redundant
  expression, so uopt makes `uand{size}{list}` a colouring candidate (cand 107, live bb22-23, after both searches end). It interferes with
  exactly the ten whole-loop candidates: size (P4, a1), list (P0, a0), count (P12, a3), buf (P8, a2), kind (P19, v1), chunk (P20, t2), the
  -1 constant (v0), 0x24 (t3), lda gMapCells (t0), lda gMapChunks (t1). That is their 22nd neighbour: they become constrained and are
  coloured first by priority into v0/v1/a0-a3/t0-t3. idx, cidx, kind*4, kind*2 and chunk*0x1C8 stay at 21 neighbours (unconstrained), so the
  leftovers go key t4, idx t5, found s0, n s1, search pointers s2, cidx s3, cfound s4, kind*4 s5, kind*2 s6, chunk*0x1C8 s7.
  - Without it every candidate has 21 neighbours (all unconstrained): key v0, idx v1, buf/count copied to s1/s0 at entry, lda
    gMapChunks/gMapCells s7/s6, -1 s5, 0x24 s4 (removal 94).
- global:80651904:other:6ec28a (pre-existing, tagged 2026-11-24) `key = ((MapDlCommand *)list)->w1; // FAKE:` key first holds the w0
  command word (opcode test 0xb38) and is reused for the w1 cell id (0xb58); both values share t4. The per-role split (u32 cmd for w0)
  gives 43 with 4f3f72 kept and 38 without it (43 on the final while-loop body): cmd is a bb2 candidate, idx (zeroed in bb2) reaches 22
  neighbours and takes v1 (Q1031). The two sites are coupled (Q0602): reuse + guard 0, split + guard 43, split alone 38/43, reuse alone 94.
## Attempts
- 2026-11-09..13 rounds 2/9/10/14/16/17/24/35 (opus low/xhigh): removal, uopt traces (constrained candidates, a2/a3 copies into s1/s0),
  permuter runs (best 165 with `do {} while (0)` before `list += 8`; 80 with `(*(buf + n)).id` plus `if (gMapChunks && gMapChunks &&
  gMapChunks) {}`; 0 only with `if (w1 && w1 && w1) {}` after the found/else branch). Original match 4b41ecee relocated an earlier global
  double-test to this loop-varying one (ido-uopt-coloring-rules#6).
- 2026-11-24 (session 2026-11-24) CleanmapChunksInitFromMapDatac anthropic/claude-opus-5-5 (re-measure after the 0b183a6c file-scope edits;
  body unchanged, fdiff 0):
  - removal 94 (text 94, shape 10).
  - Operand classification at the same spot: `if (1)`, `size`, `list`, `kind`, `count`, `key && key`, `size && size`, `list && list`,
    `kind && kind`, `buf && buf`, `chunk && chunk`, `list && size`, `1 && 1`, one-term `size & list`: all 94 (= removal);
    `*count && *count` 100; `size && size && size` 97; `(size & list) || (size & list)` and `(list & size) && (list & size)` 0;
    three-term `(size & list)` 3. So it is neither a block split nor a variable-availability guard: only a redundant expression (a CSE
    candidate) live after both searches works.
  - Per-role `u32 cmd` local for w0 (key holds only w1): 38 (text 36, shape 0). cmd is a candidate live only in bb2; it gives the ten
    their 22nd neighbour but also idx (assigned in bb2): idx becomes constrained and takes v1 (adjsave 66.0), kind t0, gMapCells t1,
    gMapChunks t2, chunk t3, 0x24 t4, n t5, key s1. cmd as s32, declared first/before/after key: 38; idx/found zeroed before the load: 42.
  - `MapDlCommand *list` K&R retype with `list++`/`(s32)(list + 1)`: 94. `MapDlCommand *cmd` walker from list: 74 (initialised before the
    `if`: 75). `next = list + 8` local for both stores and the increment: 133. `while (size != 0)` loop, `size -= 8` at the bottom,
    u32 size, u32 key: 94 each (cmd + size at the bottom 38). `w0` tested in place without a local: 158.
  - Four explicit `buf[*count].dl[i] = -1` stores: 111 (with cmd 59). `buf[*count].id = key`: 104 (with cmd 91).
  - variants.py scan: removal body (120 variants) best 79 (`list` s32 -> u8/u16, a K&R width change, not behaviour-preserving);
    cmd body (136 variants) best 38.
  - Review (applied, fdiff 0): the outer `if (size != 0) do {} while (size != 0)` and the buf search `if (n > 0) do {} while (idx < n
    && found == 0)` are plain `while` loops (the same code; the cell search stays a do-while, it has no pre-test). On that body: removal
    94, cmd split 43 with the guard kept and 43 without it.
  - The key reuse is tagged (6ec28a, Sites): pre-existing hidden steer, R5.
  - Permuter (hack-free weights, -j 2, 900 s) from the cmd body with the guard removed: permuter baseline 210, best 190 (one output:
    `*count` re-read for the `n > 0` test, the search bound and the id store instead of n; a different load set, no zero).
## Untried ideas
- A natural candidate live only in bb22-25 (the join, `list += 8`, the loop test), where idx/cidx/kind*4/kind*2/chunk*0x1C8 are dead:
  anything in bb2 (the loop top) also reaches idx and found, which are zeroed there (cmd split above).
## Evidence
- Frame 0x28, eight s registers. Preheader 0xb0c-0xb28: lda gMapChunks t1, lda gMapCells t0, 0x24 t3, chunk `lw t2,0x3c(sp)`, kind
  `lbu v1,0x3b(sp)` (K&R u8 read from its arg slot), -1 v0.
- Loop top 0xb2c-0xb40: `lw t4,0(a0)` (w0 in key's register t4), `move t5,zero` (idx), `move s0,zero` (found), `srl t6,t4,0x18`, `bnez`,
  `addiu a1,a1,-8` (size -= 8) in the delay slot: idx/found are zeroed in the same uopt block as the w0 test.
- w1 reuses t4 (`lw t4,4(a0)` 0xb58); n `lw s1,0(a3)` 0xb48; the 4-entry `dl[k] = -1` loop is unrolled (0xc00-0xc4c, `*count` reloaded
  before every store); `list + 8` is computed in each arm (0xc38, 0xcd8) and again in the back-branch delay slot (0xd18).
- uopt -l5 (base): neighbour counts 22 for size/list/count/buf/kind/chunk/-1/0x24/lda gMapCells/lda gMapChunks, 21 for idx/cidx/
  kind*4/kind*2/chunk*0x1C8, 20 for key/found/n/cfound, 19 for the two search pointers; cand 107 (`uand`) has 10 neighbours.
