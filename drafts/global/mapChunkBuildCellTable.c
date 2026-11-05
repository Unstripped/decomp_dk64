// mapChunkBuildCellTable (src/global/55B20.c): Matcher13, base 2c10d58cbaff6d352c81a3ca06a69262a175bf7f: stage 6, retained unchanged NON_MATCHING park; not matched. Best full=63 text=63 reloc=0 shape=0, 152 instructions, frame 0x28, s0-s7. Tried 83 focused variants: 28 named kind*4/kind*2/chunk*456 combinations and placement variants, 12 coordinated idx/cidx reuse of list/size/chunk parameters, 18 shared-loop-index/count-lifetime variants, 7 register-keyword combinations, and 18 named shifted-array-index variants. No score below 63. Naming chunk*456 and register keywords reproduce the baseline; explicit byte-offset kind homes change shape, and paired parameter reuse adds two instructions. uopt level 6 confirms constrained idx then cidx are colored before constants; unconstrained ranges are then colored in candidate order. Full-TU plain-C fdiff: FAILED: Section .text content mismatch (built: 33520 bytes, expected: 33520 bytes); FAILED: Relocations mismatch; TARGET CURRENT (410). Final parked copy fdiff OK; --non-matching compiles with existing warnings. Copy .scratch/Matcher13-mapChunkBuildCellTable/55B20.c. No source, prototype, type, or FAKE changes; merge no. Prior history: Matcher, base 86ca835a0a7a4dcea98f4296c53242dd2bff44ff: stage 6, improved NON_MATCHING park; not matched. Final full-TU plain-C score full=63 text=63 reloc=0 shape=0, 152 instructions, frame 0x28, saved s0-s7, 63 positional mismatches (previous draft 78; tree park 127). Readable permuter hint: insertion branch (gMapChunks + chunk)->unk58 instead of gMapChunks[chunk].unk58 moves invariant candidate order (78->64); reverse the two terms of the existing-entry unk14 sum (64->63). Remaining idx=v0/cidx=v1 before constant webs, -1=t2 (target idx=t5/cidx=s3/-1=v0). Tried scalar parameter reuse (list/size/chunk for six locals), pointer parameter reuse with shared/individual loops and indexed seeds, integer-typed global ghosts and reversed comparisons, aggregate locals, copied-parameter/global ghost lifetimes, 405 typed-constant deadsweep inserts, 512 mixed address spellings, 64 chunk/sum forms, and greedy deletion of every dead-only FAKE; no further gain. uopt levels 5/6 confirm index candidates color before constants. as1probe keep + scan --rounds 2: 1568 first-round record edits, zero improvements, stopped. ANSI permuter -j2 --seconds600: 45231 iterations, best410; reviewed 32 hint subsets, retained only the two natural expression changes (no new FAKEs). Full-TU fdiff exact: FAILED: Section .text content mismatch (built: 33520 bytes, expected: 33520 bytes); also FAILED: Relocations mismatch, but normalized target-function reloc=0. Final parked copy fdiff OK; --non-matching compile succeeds with existing warnings. Copy .scratch/Matcher-mapChunkBuildCellTable/55B20.c; evidence .scratch/Matcher-mapChunkBuildCellTable/full-object-score.json. No new names, externs, or prototype edits. Historical prior attempt note follows: CellTable, base 9b5df902: stage 6 register-allocation near miss, retained NON_MATCHING park (not matched). Final full-TU active-object comparison: 152 instructions, frame 0x28, saved s0-s7, normalized full=78 text=78 reloc=0 shape=0; exactly 78 positional instruction mismatches. Improved prior full127/text127/shape2. Current idx=v0,cidx=v1,found=s5,n=s6,cell pointers=s7,key=s3,cfound=s4,-1=t2; target idx=t5,cidx=s3,found=s0,n=s1,cell=s2,key=t4,-1=v0. New lever: buf[*count].unk4[(kind & 0)+i] retains nested uixa through uopt and removes high-priority repeated-count-load allocation; four ordinary constant indices instead select multu and lose four instructions. Assigning the command word to existing key before the opcode test preserves the target scratch-ring phase without a u64-address FAKE. Two dead D_807F70B0 tests preserve t0 global-address coloring. Exhausted count arithmetic/type/index grids, explicit/shared loop pointers and indexed bases, width/scope/lifetime/predef permutations, global-load casts, coordinated invariant locals, operand/store ordering, memory qualifiers, deadsweep, multiple annealing searches and exhaustive no-op deletion. Permuter ANSI probe -j2 --seconds600: 44316 iterations, best score580, hint generalized to natural key assignment; K&R setup mangled body and was rejected. No semantic-changing permutation retained. Full-TU active fdiff: FAILED: Section .text content mismatch (built: 33520 bytes, expected: 33520 bytes); normalized target relocations agree. Parked --non-matching compile succeeds (existing warnings); plain final copy fdiff exact output OK. Final copy .scratch/CellTable/55B20.c; full-object score .scratch/CellTable/final_object_score.json. No new names, externs, or prototype changes.
typedef struct MapDlCommand {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ s32 unk4;
} MapDlCommand;

typedef struct MapChunkCellRefs {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ s32 unk4[4];
    /* 0x14 */ s32 unk14[4];
} MapChunkCellRefs; /* 0x24 */

typedef struct MapCellOffsets {
    /* 0x00 */ u8 pad0[0x2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[0x4];
    /* 0x08 */ s16 unk8[4];
    /* 0x10 */ u8 pad10[0xC];
} MapCellOffsets; /* 0x1C */

void mapChunkBuildCellTable(list, size, buf, count, kind, chunk)
s32 list;
s32 size;
void *buf;
s32 *count;
u8 kind;
s32 chunk;
{
    s32 n;
    s32 key;
    s32 found;
    s32 idx;
    s32 cfound;
    s32 cidx;

    key = 0;  // FAKE: pre-defs fix uopt candidate numbering (key, cidx, cfound colour order)
    cidx = 0;  // FAKE: pre-defs fix uopt candidate numbering (key, cidx, cfound colour order)
    cfound = 0;  // FAKE: pre-defs fix uopt candidate numbering (key, cidx, cfound colour order)
    if (size != 0) {
        do {
            idx = 0;
            found = 0;
            size -= 8;
            key = ((MapDlCommand *)list)->unk0;
            if (((u32)key >> 24) == 0) {
                n = *count;
                key = ((MapDlCommand *)list)->unk4;
                if (buf == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                cfound = 0;
                if (n > 0) {
                    if (D_807F70B0 && D_807F70B0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    do {
                        if (key == ((MapChunkCellRefs *)buf)[idx].unk0) {
                            found = 1;
                        } else {
                            idx += 1;
                        }
                    } while (idx < n && found == 0);
                }
                cidx = 0;
                do {
                    if (key == ((MapCellOffsets *)D_807F70B0)[cidx].unk2) {
                        cfound = 1;
                    } else {
                        cidx += 1;
                    }
                } while (cfound == 0);
                if (found == 0) {
                    ((MapChunkCellRefs *)buf)[n].unk0 = key;
                    if (size && size) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    ((MapChunkCellRefs *)buf)[*count].unk4[(kind & 0) + 1 - 1] = -1;  // FAKE: zero index keeps the stride in uixa, avoiding a count-load candidate
                    if (D_807F70B0 != 0) {} // FAKE: keeps the global-address range ahead of constant webs
                    ((MapChunkCellRefs *)buf)[*count].unk4[(kind & 0) + 2 - 1] = -1;  // FAKE: zero index keeps the stride in uixa, avoiding a count-load candidate
                    if (D_807F70B0 == 0) {} // FAKE: keeps the global-address range ahead of constant webs
                    ((MapChunkCellRefs *)buf)[*count].unk4[(kind & 0) + 3 - 1] = -1;  // FAKE: zero index keeps the stride in uixa, avoiding a count-load candidate
                    ((MapChunkCellRefs *)buf)[*count].unk4[(kind & 0) + 4 - 1] = -1;  // FAKE: zero index keeps the stride in uixa, avoiding a count-load candidate
                    ((MapChunkCellRefs *)buf)[*count].unk4[kind] = list + 8;
                    ((MapChunkCellRefs *)buf)[*count].unk14[kind] = (((MapCellOffsets *)D_807F70B0)[cidx].unk8[kind] << 4) + (gMapChunks + chunk)->unk58;
                    *count += 1;
                } else {
                    ((MapChunkCellRefs *)buf)[idx].unk4[kind] = list + 8;
                    ((MapChunkCellRefs *)buf)[idx].unk14[kind] = gMapChunks[chunk].unk58 + (((MapCellOffsets *)D_807F70B0)[cidx].unk8[kind] << 4);
                }
            }
            list += 8;
        } while (size != 0);
    }
}
