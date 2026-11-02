// mapChunkBuildCellTable (src/global/55B20.c): Map r6: stage 4, 152/152 insns, frame ok; deadsweep full 130 / shape 2 (was 118/22 at 153 insns). Count fix: manual-shift spelling ((*count << 3) + *count) << 2 for the four -1 stores (no hoisted 36 multu), cidx = 0 right before loop 2 (folds p = D + cidx*28 init). Remaining: regalloc only (target found/cidx/cfound/n s0/s3/s4/s1, idx t5, key t4, -1 v0, kind v1, &D t0, &gM t1, chunk t2, 36 t3)
// deadsweep round 2: full=130 text=130 inserted `if (buf == 0) {}` at line 45
// deadsweep round 1: full=142 text=142 inserted `if (D_807F70B0 && D_807F70B0) {}` at line 46
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
