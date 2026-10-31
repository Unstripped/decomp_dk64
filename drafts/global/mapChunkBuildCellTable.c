// mapChunkBuildCellTable (src/global/55B20.c): stage 4 (MapB): unchanged parked body (full 156/shape 39). New: hill-climb over decl order + fakes + init order reached only full 122/shape 48 (fakes, not natural). Findings: target's 36 multiplier is a hoisted reg only for n*0x24 (ixa); every other x*36 is the sll3/addu/sll2 expansion, i.e. constant-36 web is live-range-split (high pressure: invariants -1,36,&cells,&chunks,kind,chunk in v0/v1/t0-t3). Ours hoists 36 to s4 for all uses. buf (a2) stays in a2 in target (n=s1); ours moves buf to s0 because n takes a2. u8 kind needs K&R definition (cfe warning only).
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
                }
                do {
                    if (key == ((MapCellOffsets *)D_807F70B0)[cidx].unk2) {
                        cfound = 1;
                    } else {
                        cidx += 1;
                    }
                } while (cfound == 0);
                if (found == 0) {
                    ((MapChunkCellRefs *)buf)[n].unk0 = key;
                    *(s32 *)((u8 *)buf + *count * 0x24 + 4) = -1;
                    *(s32 *)((u8 *)buf + *count * 0x24 + 8) = -1;
                    *(s32 *)((u8 *)buf + *count * 0x24 + 0xC) = -1;
                    *(s32 *)((u8 *)buf + *count * 0x24 + 0x10) = -1;
                    *(s32 *)((u8 *)buf + *count * 0x24 + kind * 4 + 4) = list + 8;
                    *(s32 *)((u8 *)buf + *count * 0x24 + kind * 4 + 0x14) = (((MapCellOffsets *)D_807F70B0)[cidx].unk8[kind] << 4) + D_807F6C18[chunk].unk58;
                    *count += 1;
                } else {
                    *(s32 *)((u8 *)buf + idx * 0x24 + kind * 4 + 4) = list + 8;
                    *(s32 *)((u8 *)buf + idx * 0x24 + kind * 4 + 0x14) = (((MapCellOffsets *)D_807F70B0)[cidx].unk8[kind] << 4) + D_807F6C18[chunk].unk58;
                }
            }
            list += 8;
        } while (size != 0);
    }
}
