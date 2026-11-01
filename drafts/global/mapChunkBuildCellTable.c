// mapChunkBuildCellTable (src/global/55B20.c): stage 4 (W2Map): full 118/shape 22 (was 156/39): ixa form for buf[n].unk0/kind stores, 8 deadsweep fakes (hill-climb). Target facts: only the n*36 ixa multiply uses the hoisted 36 (multu s1,t3); the 6 other x*36 are sll3/addu/sll2 expansions (constant-36 web uncoloured/immediate), key reuses t4 of the cmd-word load, saved regs s0..s7 = found,n,ptr,cidx,cfound,kind*4,kind*2,chunk*456, temps = -1,kind,&70B0,&6C18,chunk,36,key,idx; ours colours cidx/products into temps and size into s0. Tried: named cmd/k4/k2/cb locals, key reused for cmd, 9-multiplier row pointers (hoists li 9), unrolled j loop (identical code), u32/0x24U typed multipliers, decl-order perms, ~3 hill-climbs.
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
        if (size != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        do {
            idx = 0;
            found = 0;
            size -= 8;
            if ((((MapDlCommand *)list)->unk0 >> 24) == 0) {
                n = *count;
                key = ((MapDlCommand *)list)->unk4;
                if (chunk > size) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                cidx = 0;
                cfound = 0;
                if (n > 0) {
                    do {
                        if (key == ((MapChunkCellRefs *)buf)[idx].unk0) {
                            found = 1;
                        } else {
                            idx += 1;
                        }
                    } while (idx < n && found == 0);
                    if (D_807F70B0 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
                do {
                    if (key == ((MapCellOffsets *)D_807F70B0)[cidx].unk2) {
                        cfound = 1;
                    } else {
                        if (size && size) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        if (!buf) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        cidx += 1;
                    }
                } while (cfound == 0);
                if (gMapChunks) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (found == 0) {
                    ((MapChunkCellRefs *)buf)[n].unk0 = key;
                    ((s32 *)((u8 *)buf + *count * 0x24))[1] = -1;
                    *(s32 *)((u8 *)buf + *count * 0x24 + 8) = -1;
                    ((MapChunkCellRefs *)buf)[*count].unk4[2] = -1;
                    if (gMapChunks) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    *(s32 *)((u8 *)buf + (*count << 5) + *count * 4 + 16) = -1;
                    ((MapChunkCellRefs *)buf)[*count].unk4[kind] = list + 8;
                    *(s32 *)((u8 *)buf + *count * 0x24 + kind * 4 + 20) = (((MapCellOffsets *)D_807F70B0)[cidx].unk8[kind] << 4) + gMapChunks[chunk].unk58;
                    if (D_807F70B0 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
