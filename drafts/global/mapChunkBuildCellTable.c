// mapChunkBuildCellTable (src/global/55B20.c): Map55 r8: stage 4, 152/152 insns, frame ok, full 127 (was 130) / shape 2 (pure colouring). New lever: three pre-defs before the do loop (key = 0; cidx = 0; cfound = 0; FAKE) change uopt candidate numbering: 130 -> 127; any 3-subset containing cidx+cfound ('key'|'n'|'found' + cidx + cfound) gives 127, cidx+cfound alone 143. Target colouring needs idx/key/cidx/kind*4/kind*2/chunk*456 unconstrained (<=21 neighbours; ours 22-23) and -1 coloured v0 first; ours has *count expr candidate (bit 22, v0) + found-arm addr cand. Tried (new): 4-store spellings (s32-index, u8 mul forms, unk4[k] natural: count 152/163 wrong), for/do-while unrolled -1 loop (126 but count 157), operand order of unk14 sum, swap found/else arm, volatile reload of *count, local copies of idx/cidx/unk8, init/pre-statement order grid (80 variants, all 130).
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
