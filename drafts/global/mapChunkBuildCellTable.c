// mapChunkBuildCellTable (src/global/55B20.c): MapChunkPair revisit 9: stage 4 park, 152/152 insns, frame 0x28 ok, full=127 text=127 reloc=0 shape=2 (pure colouring). All 152 instructions in exact 1-to-1 opcode correspondence with target. Diagnosis: target allocates 8 callee-saved registers: found in s0, n in s1, cell ptr in s2 (shared across both loops), cidx in s3, cfound in s4, kind*4 in s5, kind*2 in s6, chunk*456 in s7; temporary/caller-saved registers: -1 in v0, kind in v1, &D_807F70B0 in t0, &gMapChunks in t1, chunk in t2, 36 in t3, key in t4, idx in t5. In our build, *count expression candidate (bit 22) takes v0 (adjsave 120.0), displacing -1 to t1 and cascading across s0..s7. Tested clean C without FAKEs (full 149), natural 4-store spellings, pointer iteration vs array indexing.
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
            if ((((MapDlCommand *)list)->unk0 >> 24) == 0) {
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
                    *(s32 *)((u8 *)buf + (((*count << 3) + *count) << 2) + 4) = -1;
                    *(s32 *)((u8 *)buf + (((*count << 3) + *count) << 2) + 8) = -1;
                    *(s32 *)((u8 *)buf + (((*count << 3) + *count) << 2) + 12) = -1;
                    *(s32 *)((u8 *)buf + (((*count << 3) + *count) << 2) + 16) = -1;
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
