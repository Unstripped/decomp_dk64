// mapChunkBuildCellTable (src/global/55B20.c): CellTable, base 9b5df902: stage 6 register-allocation near miss, retained NON_MATCHING park (not matched). Final full-TU active-object comparison: 152 instructions, frame 0x28, saved s0-s7, normalized full=78 text=78 reloc=0 shape=0; exactly 78 positional instruction mismatches. Improved prior full127/text127/shape2. Current idx=v0,cidx=v1,found=s5,n=s6,cell pointers=s7,key=s3,cfound=s4,-1=t2; target idx=t5,cidx=s3,found=s0,n=s1,cell=s2,key=t4,-1=v0. New lever: buf[*count].unk4[(kind & 0)+i] retains nested uixa through uopt and removes high-priority repeated-count-load allocation; four ordinary constant indices instead select multu and lose four instructions. Assigning the command word to existing key before the opcode test preserves the target scratch-ring phase without a u64-address FAKE. Two dead D_807F70B0 tests preserve t0 global-address coloring. Exhausted count arithmetic/type/index grids, explicit/shared loop pointers and indexed bases, width/scope/lifetime/predef permutations, global-load casts, coordinated invariant locals, operand/store ordering, memory qualifiers, deadsweep, multiple annealing searches and exhaustive no-op deletion. Permuter ANSI probe -j2 --seconds600: 44316 iterations, best score580, hint generalized to natural key assignment; K&R setup mangled body and was rejected. No semantic-changing permutation retained. Full-TU active fdiff: FAILED: Section .text content mismatch (built: 33520 bytes, expected: 33520 bytes); normalized target relocations agree. Parked --non-matching compile succeeds (existing warnings); plain final copy fdiff exact output OK. Final copy .scratch/CellTable/55B20.c; full-object score .scratch/CellTable/final_object_score.json. No new names, externs, or prototype changes.
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
                    ((MapChunkCellRefs *)buf)[*count].unk14[kind] = (((MapCellOffsets *)D_807F70B0)[cidx].unk8[kind] << 4) + gMapChunks[chunk].unk58;
                    *count += 1;
                } else {
                    ((MapChunkCellRefs *)buf)[idx].unk4[kind] = list + 8;
                    ((MapChunkCellRefs *)buf)[idx].unk14[kind] = (((MapCellOffsets *)D_807F70B0)[cidx].unk8[kind] << 4) + gMapChunks[chunk].unk58;
                }
            }
            list += 8;
        } while (size != 0);
    }
}
