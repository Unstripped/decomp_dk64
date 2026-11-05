#include "common.h"
#include "actor.h"

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

typedef struct MapChunk {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 unk5;
    /* 0x006 */ u8 unk6;
    /* 0x007 */ u8 unk7;
    /* 0x008 */ s32 unk8;
    /* 0x00C */ s32 unkC;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ u8 pad18[0x4];
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ u8 pad20[0x4];
    /* 0x024 */ s32 unk24;
    /* 0x028 */ s32 unk28;
    /* 0x02C */ s32 unk2C;
    /* 0x030 */ s32 unk30;
    /* 0x034 */ s32 unk34;
    /* 0x038 */ s32 unk38;
    /* 0x03C */ s32 unk3C;
    /* 0x040 */ s32 unk40;
    /* 0x044 */ s32 unk44;
    /* 0x048 */ s32 unk48;
    /* 0x04C */ void *unk4C;
    /* 0x050 */ s32 unk50;
    /* 0x054 */ s32 unk54;
    /* 0x058 */ s32 unk58;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ s32 unk60;
    /* 0x064 */ s32 unk64;
    /* 0x068 */ s32 unk68;
    /* 0x06C */ s32 unk6C;
    /* 0x070 */ s32 unk70;
    /* 0x074 */ s32 unk74;
    /* 0x078 */ u32 unk78;
    /* 0x07C */ u32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ s16 unk82;
    /* 0x084 */ s16 unk84;
    /* 0x086 */ s16 unk86;
    /* 0x088 */ u8 pad88[0x140];
} MapChunk;

extern u8 D_807F7078[];
extern s32 gMapChunkCount;
extern MapChunk *gMapChunks;
extern u8 *D_807F6C1C;
extern s32 D_807F6C20;
extern u8 *D_807F6C2C;

typedef struct MapHeader {
    /* 0x000 */ u8 pad0[0x64];
    /* 0x064 */ s32 unk64;
} MapHeader;

extern s32 D_8076A0B4;
extern s32 D_8076A0B8;
extern s32 D_8076A0BC;
extern s32 D_8076A0C0;
extern s32 D_8076A0C4;
extern s32 D_8076A0C8;
void *heapAlloc(s32);

void mapChunkAllocLists(MapHeader *arg0) {
    s32 temp;
    s32 count;
    s32 size;

    temp = gMapChunkCount = *(s32 *)(arg0->unk64 + (u8 *)arg0);
    if (temp >= 2) {
        count = temp & 0xFF;
    } else {
        count = 1;
    }
    size = count * 4;
    D_8076A0B4 = (s32)heapAlloc(size);
    D_8076A0B8 = (s32)heapAlloc(size);
    D_8076A0BC = (s32)heapAlloc(size);
    D_8076A0C0 = (s32)heapAlloc(size);
    D_8076A0C4 = (s32)heapAlloc(size);
    D_8076A0C8 = (s32)heapAlloc(size);
}

typedef struct MapData {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[0x26];
    /* 0x34 */ s32 unk34;
    /* 0x38 */ u8 pad38[0x20];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
} MapData;

typedef struct MapRelocEntry {
    /* 0x0 */ u8 pad0[8];
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
} MapRelocEntry;

extern s32 D_807F5DE8;
extern s32 D_807F70AC;
extern u8 D_807F70AB;
extern s16 D_807F7138;
extern u8 D_807F713A;
extern u8 D_807F7079;
extern u8 D_807F707A[];
extern u8 D_807F70AA;
extern Mtx *D_807F7074;
extern u8 *D_807F6C0C;
extern s32 D_807F6C10;
typedef struct {
    /* 0x00 */ s64 unk0;
    /* 0x08 */ s64 unk8;
    /* 0x10 */ s64 unk10;
    /* 0x18 */ s64 unk18;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 pad29[0x7];
} MapGridPoint; /* 0x30 */

typedef struct {
    /* 0x00 */ f32 unk0[4];
    /* 0x10 */ f32 unk10[4];
    /* 0x20 */ f32 unk20[4];
} MapGridVectors;

extern MapGridVectors *D_807F6C14;
extern MapGridPoint *gMapGridTrianglePlanes;
extern struct MapCell *D_807F70B0;
extern struct MapBox *D_807F70B4;

void lightSetTargetColor(f32, f32, f32, s16);
void lightCopyTargetColors(s16);
void mapChunkBuildCellTable(s32, s32, void *, s32 *, s32, s32);
void mapGridTriangleBuildPlane(s32, void *);


#ifdef NON_MATCHING
void mapChunksInitFromMapData(MapData *arg0) {
    s32 i;
    s32 off;
    s32 base;
    u8 buf[0xE54];
    s32 count;
    u8 *p;
    u32 total;
    s32 j;
    volatile s32 colOff;  // FAKE: retains collision-header offset stack accesses
    volatile s32 w;  // FAKE: retains collision-data base stack accesses

    D_807F70AC = 0;
    D_807F713A = 0;
    D_807F70AB = 0;
    if (gMapChunkCount != 0) {
        D_807F7138 = arg0->unkC;
        D_807F7074 = heapAlloc(0x40);
        guScale(D_807F7074, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
        i = arg0->unk58;
        D_807F70AC = *(s32 *)((u8 *)arg0 + i);
        D_807F70B0 = (struct MapCell *)((u8 *)arg0 + i + 4);
        D_807F70B4 = (struct MapBox *)((u8 *)arg0 + arg0->unk5C + 4);
        D_807F6C14 = (MapGridVectors *)((u8 *)arg0 + arg0->unk60);
        base = arg0->unk34;
        off = arg0->unk64;
        j = arg0->unk68;
        i = arg0->unk6C;
        D_807F6C20 = *(s32 *)((u8 *)arg0 + i);
        D_807F6C1C = (u8 *)((u8 *)arg0 + i + 4);
        D_807F6C2C = heapAlloc(D_807F6C20);
        D_807F6C10 = *(s32 *)((u8 *)arg0 + arg0->unk70);
        D_807F6C0C = (u8 *)((u8 *)arg0 + arg0->unk70 + 4);
        for (i = 0; i < D_807F6C10; i++) {
            if (((MapRelocEntry *)D_807F6C0C)[i].unk8 != -1) {
                ((MapRelocEntry *)D_807F6C0C)[i].unk8 += (s32)((u8 *)arg0 + base);
            }
            if (((MapRelocEntry *)D_807F6C0C)[i].unkC != -1) {
                ((MapRelocEntry *)D_807F6C0C)[i].unkC += (s32)((u8 *)arg0 + base);
            }
        }
        gMapChunks = heapAlloc(gMapChunkCount * 0x1C8);
        p = (u8 *)arg0 + j;
        i = 0;
        if (gMapChunkCount > 0) {
            w = (s32)arg0 + off;
            colOff = 0;
            do {
                count = 0;
                gMapChunks[i].unk0 = 0;
                gMapChunks[i].unk1 = 0;
                if (D_807F70AC == 0) {}  // FAKE: dead statement (steers uopt colouring)
                gMapChunks[i].unk14 = 0;
                gMapChunks[i].unk1C = 0;
                gMapChunks[i].unk24 = 0;
                gMapChunks[i].unk7 = 4;
                gMapChunks[i].unk54 = *(s32 *)(p + 0x2C) + D_807F5DE8;
                gMapChunks[i].unk58 = gMapChunks[i].unk54;
                lightSetTargetColor(p[0] / 255.0, p[1] / 255.0, p[2] / 255.0, (s16)i);
                lightCopyTargetColors((s16)i);
                gMapChunks[i].unk6 = p[3];
                p += 0xC;
                gMapChunks[i].unk5 = p[-8];
                gMapChunks[i].unk3 = *(s32 *)(p - 4);
                j = *(s32 *)p;
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                gMapChunks[i].unk2C = j;
                gMapChunks[i].unk3C = *(s32 *)(p - 4);
                total = gMapChunks[i].unk3C;
                if (gMapChunks[i].unk5 == 2) {
                    D_807F713A = 1;
                    mapChunkBuildCellTable(gMapChunks[i].unk2C, gMapChunks[i].unk3C, buf, &count, 0, i);
                }
                j = *(s32 *)p;
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                gMapChunks[i].unk30 = j;
                gMapChunks[i].unk40 = *(s32 *)(p - 4);
                total += gMapChunks[i].unk40;
                if (gMapChunks[i].unk5 == 2) {
                    mapChunkBuildCellTable(gMapChunks[i].unk30, gMapChunks[i].unk40, buf, &count, 1, i);
                }
                j = *(s32 *)p;
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                gMapChunks[i].unk34 = j;
                gMapChunks[i].unk44 = *(s32 *)(p - 4);
                total += gMapChunks[i].unk44;
                if (gMapChunks[i].unk5 == 2) {
                    mapChunkBuildCellTable(gMapChunks[i].unk34, gMapChunks[i].unk44, buf, &count, 2, i);
                }
                j = *(s32 *)p;
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                gMapChunks[i].unk38 = j;
                gMapChunks[i].unk48 = *(s32 *)(p - 4);
                total += gMapChunks[i].unk48;
                gMapChunks[i].unk8 = gMapChunks[i].unk2C + ((total >> 3) << 3);
                gMapChunks[i].unkC = gMapChunks[i].unk2C;
                gMapChunks[i].unk10 = gMapChunks[i].unk8;
                if (gMapChunks[i].unk5 == 2) {
                    mapChunkBuildCellTable(gMapChunks[i].unk38, gMapChunks[i].unk48, buf, &count, 3, i);
                }
                gMapChunks[i].unk5C = *(s32 *)(p + 4);
                p += 8;
                gMapChunks[i].unk60 = 0;
                gMapChunks[i].unk64 = 0;
                if (gMapChunks == 0) {}  // FAKE: dead statement (steers uopt colouring)
                {
                    j = (w + 4) + colOff;
                    gMapChunks[i].unk78 = *(s32 *)j + w;
                    gMapChunks[i].unk7C = *(s32 *)(j + 0xC) + w;
                    gMapChunks[i].unk80 = *(s16 *)(j + 4);
                    gMapChunks[i].unk82 = *(s16 *)(j + 6);
                    gMapChunks[i].unk84 = *(s16 *)(j + 8);
                    gMapChunks[i].unk86 = *(s16 *)(j + 0xA);
                }
                gMapChunks[i].unk28 = -1;
                if (count != 0) {
                    gMapChunks[i].unk4C = heapAlloc(count * 0x24);
                    memcpy(gMapChunks[i].unk4C, buf, count * 0x24);
                    for (j = 0; j < count; j++) {
                        ((u8 *)(gMapChunks[i].unk4C))[j * 0x24 + 2] = 0xFF;
                    }
                }
                gMapChunks[i].unk50 = count;
                colOff += 12;
                i++;
            } while (i < gMapChunkCount);
        }
        gMapGridTrianglePlanes = heapAlloc(D_807F6C20 / 2 * 0x30);
        for (i = 0; i < D_807F6C20 / 2; i++) {
            mapGridTriangleBuildPlane(i, (u8 *)gMapGridTrianglePlanes + i * 0x30);
            if (D_807F70AA == 0) {}  // FAKE: dead statement (steers uopt colouring)
        }
        D_807F7079 = 1;
        D_807F7078[0] = 1;
        p = D_807F707A;
        do {
            *p++ = 1;
            if (D_807F707A) {}  // FAKE: dead statement (steers uopt colouring)
            *p++ = 1;
            *p++ = 1;
            *p++ = 1;
        } while (p != &D_807F70AA);
        D_807F70AA = 0;
    } else {
        gMapChunks = NULL;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/mapChunksInitFromMapData.s")
#endif

typedef struct MapNodeEntry {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x2];
    /* 0x08 */ u8 *unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[0x2];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} MapNodeEntry;

extern void *D_807F70B8[];
void heapFree(void *);

void mapFaceBuildTriangleFan(s32 arg0) {
    MapNodeEntry *var_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;
    s32 temp_lo;
    u8 *var_a0_2;

    var_v1 = D_807F70B8[arg0];
    if (var_v1->unk8 != 0) {
        heapFree(var_v1->unk8);
    }
    var_a1 = var_v1->unk4 - 2;
    if (var_a1 < 0) {
        var_a1 = 0;
    }
    if (var_a1 != 0) {
        var_v1->unk8 = heapAlloc(var_a1 * 0x12);
        var_v1->unkC = var_a1;
        if (var_v1->unk4 >= 3) {
            var_a3 = 1;
            var_a2 = 2;
            var_v0 = 0x24;
            var_a1 = 0xC;
            do {
                temp_lo = var_a3 * 6;
                if (var_a1 && var_a1) {}  // FAKE: deadsweep: steers uopt coloring (keeps unk4 temp in a0)
                var_a3 = var_a2;
                *(s16 *)(var_v1->unk8 + var_v0 - 0x24) = *(s16 *)(var_v1->unk0 + 0);
                var_a2 += 1;
                *(s16 *)(var_v1->unk8 + var_v0 - 0x1E) = *(s16 *)(var_v1->unk0 + 2);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x18) = *(s16 *)(var_v1->unk0 + 4);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x22) = *(s16 *)(var_v1->unk0 + temp_lo);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x1C) = *(s16 *)(var_v1->unk0 + temp_lo + 2);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x16) = *(s16 *)(var_v1->unk0 + temp_lo + 4);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x20) = *(s16 *)(var_v1->unk0 + var_a1);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x1A) = *(s16 *)(var_v1->unk0 + var_a1 + 2);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x14) = *(s16 *)(var_v1->unk0 + var_a1 + 4);
                var_v0 += 0x12;
                var_a1 += 6;
            } while (var_a2 < var_v1->unk4);
        }
    }
    var_v1->unk10 = 0x7FFF; var_v1->unk12 = -0x8000;  // FAKE: same-line stores flip the store scheduling order
    var_a2 = 0;
    if (var_v1->unk4 > 0) {
        var_a0_2 = var_v1->unk0;
        do {
            if (var_v1->unk12 < *(s16 *)(var_a0_2 + 2)) {
                var_v1->unk12 = *(s16 *)(var_a0_2 + 2);
            }
            if (*(s16 *)(var_a0_2 + 2) < var_v1->unk10) {
                var_v1->unk10 = *(s16 *)(var_a0_2 + 2);
            }
            var_a2 += 1;
            var_a0_2 += 6;
        } while (var_a2 < var_v1->unk4);
    }
}


#ifdef NON_MATCHING
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/mapChunkBuildCellTable.s")
#endif

s32 mapChunkIsInUse(s16 arg0) {
    s32 var_v0;
    s32 var_v1;

    var_v1 = (arg0 + 1) != 0;
    if (var_v1 != 0) {
        if (gMapChunks[arg0].unk3 != 0) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        var_v1 = var_v0 != 0;
    }
    return var_v1 & 0xFF;
}

void mapByteArraySet(s16 arg0, s8 arg1) {
    D_807F7078[arg0] = arg1;
}

void mapObjectSetByte(s16 arg0, u8 arg1, u8 arg2) {
    D_807F6C1C[(u32)(arg0 * 2) * 0xA + arg1 * 0xA + 9] = arg2;
}

f32 sqrtf(f32);

void mapGridTriangleBuildPlane(s32 arg0, void *arg1p) {
    s64 a2v;
    s64 a1v;
    s64 a0v;
    s64 b2v;
    s64 b1v;
    s64 b0v;
    s64 x;
    s64 y;
    s64 z;

    a0v = (s64)(D_807F6C14[arg0].unk0[0] - D_807F6C14[arg0].unk0[1]);
    a1v = (s64)(D_807F6C14[arg0].unk10[0] - D_807F6C14[arg0].unk10[1]);
    a2v = (s64)(D_807F6C14[arg0].unk20[0] - D_807F6C14[arg0].unk20[1]);
    b0v = (s64)(D_807F6C14[arg0].unk0[0] - D_807F6C14[arg0].unk0[2]);
    b1v = (s64)(D_807F6C14[arg0].unk10[0] - D_807F6C14[arg0].unk10[2]);
    b2v = (s64)(D_807F6C14[arg0].unk20[0] - D_807F6C14[arg0].unk20[2]);
    ((MapGridPoint *)arg1p)->unk0 = a1v * b2v - a2v * b1v;
    ((MapGridPoint *)arg1p)->unk8 = a2v * b0v - a0v * b2v;
    ((MapGridPoint *)arg1p)->unk10 = a0v * b1v - a1v * b0v;
    ((MapGridPoint *)arg1p)->unk18 = (s64)-(((f32)((MapGridPoint *)arg1p)->unk0 * D_807F6C14[arg0].unk0[1] + (f32)((MapGridPoint *)arg1p)->unk8 * D_807F6C14[arg0].unk10[1]) + (f32)((MapGridPoint *)arg1p)->unk10 * D_807F6C14[arg0].unk20[1]);
    ((MapGridPoint *)arg1p)->unk24 = (f32)(((MapGridPoint *)arg1p)->unk0 * ((MapGridPoint *)arg1p)->unk0 + ((MapGridPoint *)arg1p)->unk8 * ((MapGridPoint *)arg1p)->unk8 + ((MapGridPoint *)arg1p)->unk10 * ((MapGridPoint *)arg1p)->unk10);
    ((MapGridPoint *)arg1p)->unk20 = sqrtf(((MapGridPoint *)arg1p)->unk24);
    x = ((MapGridPoint *)arg1p)->unk0 >= 0 ? ((MapGridPoint *)arg1p)->unk0 : 0 - ((MapGridPoint *)arg1p)->unk0;
    y = ((MapGridPoint *)arg1p)->unk8 >= 0 ? ((MapGridPoint *)arg1p)->unk8 : 0 - ((MapGridPoint *)arg1p)->unk8;
    z = ((MapGridPoint *)arg1p)->unk10 >= 0 ? ((MapGridPoint *)arg1p)->unk10 : 0 - ((MapGridPoint *)arg1p)->unk10;
    if ((z >= x) && (z >= y)) {
        ((MapGridPoint *)arg1p)->unk28 = 0;
    }
    if ((y >= x) && (y >= z)) {
        ((MapGridPoint *)arg1p)->unk28 = 1;
    }
    if ((x >= y) && (x >= z)) {
        ((MapGridPoint *)arg1p)->unk28 = 2;
    }
}

struct MapCell;

void mapChunkResetFlags(void) {
    s32 i;
    s32 j;

    for (i = 0; i < gMapChunkCount; i++) {
        gMapChunks[i].unk1 = 0;
        gMapChunks[i].unk2 = 1;
        gMapChunks[i].unk4 = 0;
    }
    for (j = 0; j < D_807F70AC; j++) {
        ((u8 *)D_807F70B0)[j * 0x1C + 0x19] = 0;
    }
}

void mapChunkClearBounds(void) {
    s32 i;

    for (i = 0; i < gMapChunkCount; i++) {
        gMapChunks[i].unk0 = 0;
        gMapChunks[i].unk68 = 0;
        gMapChunks[i].unk6C = 0;
        gMapChunks[i].unk70 = 0;
        gMapChunks[i].unk74 = 0;
    }
    for (i = 0; i < D_807F6C20; i++) {
        D_807F6C1C[i * 0xA + 8] = 0;
        D_807F6C2C[i] = 0;
    }
}

s32 mapChunkContainsPoint(s16 arg0, s16 arg1, s16 arg2) {
    MapChunk *entry;

    entry = (MapChunk *)((s32)gMapChunks + arg2 * 0x1C8);
    if (entry->unk1 == 0) {
        return 0;
    }
    if ((arg0 >= entry->unk68) && (arg1 >= entry->unk6C) && (entry->unk70 >= arg0) && (entry->unk74 >= arg1)) {
        return 1;
    }
    return 0;
}

typedef struct MapActorEntry {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ f32 unk4;
    /* 0x008 */ f32 unk8;
    /* 0x00C */ f32 unkC;
    /* 0x010 */ u8 pad10[0xC];
    /* 0x01C */ s16 unk1C;
    /* 0x01E */ s16 unk1E;
    /* 0x020 */ s16 unk20;
    /* 0x022 */ u8 unk22;
    /* 0x023 */ u8 pad23[0x1];
    /* 0x024 */ u8 unk24;
} MapActorEntry;

s32 renderEntryAddOrUpdate(s32, s32, s32, f32, f32, f32, s32, s32, s32, s32, s32);
s32 renderEntryIsTranslucent(s32, s32);
s16 mapChunkFindByPosition(f32, f32, f32, s16);

void mapChunkUpdateEntryNode(MapActorEntry *arg0) {
    s32 temp_v1;
    s32 *sp40;
    s16 *level;

    arg0->unk20 = mapChunkFindByPosition(arg0->unk4, arg0->unk8, arg0->unkC, arg0->unk20);
    temp_v1 = renderEntryIsTranslucent(arg0->unk24, arg0->unk0) & 0xFF;
    if (arg0->unk24 == 0) {
        *(s16 *)(arg0->unk0 + 0x12C) = arg0->unk20;
    }
    level = &arg0->unk20;
    switch (temp_v1) {
    case 0:
        sp40 = (s32 *)((u8 *)gMapChunks + *level * 0x1C8 + 0x14);
        break;
    case 1:
        sp40 = (s32 *)((u8 *)gMapChunks + *level * 0x1C8 + 0x1C);
        break;
    }
    *sp40 = renderEntryAddOrUpdate(*sp40, arg0->unk24, arg0->unk0, arg0->unk4, arg0->unk8, arg0->unkC, arg0->unk1C, arg0->unk1E, arg0->unk22, *level, 0);
}

void renderEntrySetDistanceOverride(s32, s32, s32, u8, u8 *);

void mapChunkMarkRenderEntry(s32 arg0, u8 arg1) {
    u8 flag;
    s32 i;

    flag = 0;
    for (i = 0; i < gMapChunkCount && !flag; i++) {
        renderEntrySetDistanceOverride(gMapChunks[i].unk14, arg0, 0, arg1, &flag);
        if (!flag) {
            renderEntrySetDistanceOverride(gMapChunks[i].unk1C, arg0, 0, arg1, &flag);
        }
    }
}

s32 renderEntryRemove(s32, s32, s32, u8 *);

u8 mapChunkPurgeNodeList(s32 arg0, s16 *arg1, u8 arg2) {
    u8 flag;
    s32 i;

    flag = 0;
    for (i = 0; i < gMapChunkCount && (!flag || arg2); i++) {
        gMapChunks[i].unk14 = renderEntryRemove(gMapChunks[i].unk14, arg0, 0, &flag);
        if (flag) {
            *arg1 = i;
        }
        if (!flag || arg2) {
            gMapChunks[i].unk1C = renderEntryRemove(gMapChunks[i].unk1C, arg0, 0, &flag);
            if (flag) {
                *arg1 = i;
            }
        }
    }
    return flag;
}

s32 D_807F6C80;
s32 D_807F6C84; // unreferenced word between the chunk count and D_807F6C88
f32 D_807F6C88[12];
extern s16 D_807F6C58[];
struct MapCell;
struct MapBox;
extern u8 D_807F7140;

void renderEntryListClearTouched(s32);
s32 renderEntryListPurgeUntouched(s32);
s32 renderEntryListSortByDistance(s32, f32, f32, f32, void *);
void modelNodeListSyncFlags(s32);
s32 spriteListBuildDisplayChain(s32, s32, f32, f32, f32);
s32 mapNodeBoxContainsPoint(void *, f32, f32);
s32 mapNodeTriangleContainsPoint(void *, f32, f32);
void mapCellFindAtPoint(f32, f32, f32, s16, s16, s16 *);
s32 mapFloorHeightIsBetter(f32, f32, f32);
s32 mapChunkFindNodeAtPoint(f32, f32, f32, s16, u8 *, f32 *);

void mapChunkClearNodeFlags(u8 arg0) {
    s32 i;

    i = 0;
    if (gMapChunkCount > 0) {
        do {
            if ((gMapChunks[i].unk0 == 1) || arg0) {
                renderEntryListClearTouched(gMapChunks[i].unk14);
                renderEntryListClearTouched(gMapChunks[i].unk1C);
            }
            i += 1;
        } while (i < gMapChunkCount);
    }
}

void mapChunkFreeNodeLists(u8 arg0) {
    s32 i;

    i = 0;
    if (gMapChunkCount > 0) {
        do {
            if ((gMapChunks[i].unk0 == 1) || arg0) {
                gMapChunks[i].unk14 = renderEntryListPurgeUntouched(gMapChunks[i].unk14);
                gMapChunks[i].unk1C = renderEntryListPurgeUntouched(gMapChunks[i].unk1C);
            }
            i += 1;
        } while (i < gMapChunkCount);
    }
}

void mapChunkRebuildNodeLists(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    s32 var_s3;
    s32 var_s1;

    var_s3 = 0;
    if (gMapChunkCount > 0) {
        var_s1 = 0;
        do {
            if (gMapChunks[var_s1].unk0 == 1 || arg3) {
                gMapChunks[var_s1].unk14 = renderEntryListSortByDistance(gMapChunks[var_s1].unk14, arg0, arg1, arg2, (void *)((u8 *)&gMapChunks[var_s1] + 0x18));
                gMapChunks[var_s1].unk1C = renderEntryListSortByDistance(gMapChunks[var_s1].unk1C, arg0, arg1, arg2, (void *)((u8 *)&gMapChunks[var_s1] + 0x20));
            }
            var_s3 += 1;
            var_s1 += 1;
        } while (var_s3 < gMapChunkCount);
    }
}

void mapChunkResolveNodeAssets(void) {
    s32 i;

    i = 0;
    if (gMapChunkCount > 0) {
        do {
            modelNodeListSyncFlags(gMapChunks[i].unk14);
            modelNodeListSyncFlags(gMapChunks[i].unk1C);
            i += 1;
        } while (i < gMapChunkCount);
    }
}

void mapChunkBuildSpriteChains(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    s32 i;

    i = 0;
    if (gMapChunkCount > 0) {
        do {
            if (gMapChunks[i].unk0 == 1 || arg3) {
                if (gMapChunks[i].unk6 != 0) {
                    gMapChunks[i].unk24 = 0;
                } else {
                    gMapChunks[i].unk24 = spriteListBuildDisplayChain(gMapChunks[i].unk14, gMapChunks[i].unk1C, arg0, arg1, arg2);
                }
            }
            i += 1;
        } while (i < gMapChunkCount);
    }
}

typedef struct MapNode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ struct MapNode *unk14;
    /* 0x18 */ u8 pad18[6];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ u8 unk24;
} MapNode; /* 0x28 */

void modelPendingQueueInsert(void *, u8);

void mapChunkUpdateModelNodes(void) {
    u8 flag;
    s32 i;
    void *node;
    void *next;

    D_807F7140 = 0;
    i = 0;
    if (gMapChunkCount > 0) {
        do {
            if (gMapChunks[i].unk1 != 0) {
                flag = 1;
            } else {
                flag = 0;
            }
            node = (void *)gMapChunks[i].unk14;
            if (node != NULL) {
                do {
                    next = ((MapNode *)node)->unk14;
                    modelPendingQueueInsert(node, flag);
                    node = next;
                } while (next != NULL);
            }
            i += 1;
        } while (i < gMapChunkCount);
    }
}

#define MAP_CHUNK_AT(o) ((MapChunk *)((u8 *)gMapChunks + (o)))

extern s32 func_80668E9C(s32, s16, f32, f32, f32, s32);

s32 mapChunkCheckActorCollision(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    MapNode *node;
    s32 i;
    u8 pad;
    u8 mode;
    s32 result;
    s16 x;
    s16 y;

    result = 0;
    mode = renderEntryIsTranslucent(1, 0);
    i = 0;
    if (gMapChunkCount > 0) {
        x = (s16)(s32)(arg1 * 6.0f);
        do {
            if ((x >= MAP_CHUNK_AT(i * 0x1C8)->unk80 - 0x32) &&
                ((y = (s16)(s32)(arg2 * 6.0f)) >= MAP_CHUNK_AT(i * 0x1C8)->unk82 - 0x32) &&
                (MAP_CHUNK_AT(i * 0x1C8)->unk84 + 0x32 >= x) &&
                (MAP_CHUNK_AT(i * 0x1C8)->unk86 + 0x32 >= y)) {
                switch (mode) {
                case 0:
                    node = (MapNode *)MAP_CHUNK_AT(i * 0x1C8)->unk14;
                    break;
                case 1:
                    node = (MapNode *)MAP_CHUNK_AT(i * 0x1C8)->unk1C;
                    break;
                }
                if (node != NULL) {
                    do {
                        if (node->unk24 == 1) {
                            result |= func_80668E9C(arg0, node->unk1E, arg1, arg2, arg3, arg4);
                            result &= 0xFF;
                        }
                        node = node->unk14;
                    } while (node != NULL);
                }
            }
            i++;
        } while (i < gMapChunkCount);
    }
    return result;
}

s32 mapPointIsInRenderedChunk(f32 arg0, f32 arg1, f32 arg2) {
    s16 *pad;
    s32 i;
    s16 chunk;

    i = 0;
    if (gMapChunkCount == 0) {
        return 0xFF;
    }
    chunk = mapChunkFindByPosition(arg0, arg1, arg2, 0);
    if (D_807F6C80 > 0) {
        do {
            if (chunk == D_807F6C58[i]) {
                return 1;
            }
            i++;
            if (D_807F6C80 > 0) {} // FAKE: second read of D_807F6C80 inside the loop makes IDO strength-reduce the index (end pointer)
        } while (i < D_807F6C80);
    }
    return 0;
}

s32 mapChunkIsVisible(s16 arg0) {
    s32 var_v1;

    if (gMapChunkCount == 0) {
        return 0xFF;
    }
    if (gMapChunks[arg0].unk1 != 0) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1 & 0xFF;
}

s32 mapChunkIsActive(s16 arg0) {
    s32 var_v1;

    if (gMapChunkCount == 0) {
        return 0xFF;
    }
    if (gMapChunks[arg0].unk0 == 1) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1 & 0xFF;
}

s32 mapChunkIsVisibleForPlayer(s16 arg0, s16 arg1) {
    s32 var_v1;

    if (gMapChunkCount == 0) {
        return 1;
    }
    if (gMapChunks[arg1].unk1 & (1 << arg0)) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1 & 0xFF;
}

s16 mapChunkFindAtPoint(f32 arg0, f32 arg1, f32 arg2, s16 arg3) {
    s16 temp;

    mapCellFindAtPoint(arg0, arg1, arg2, arg3, -1, &temp);
    return temp;
}

typedef struct MapBox {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
} MapBox;

typedef struct MapCell {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x12];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 pad1A[0x2];
} MapCell; /* 0x1C */

void mapCellFindAtPoint(f32 arg0, f32 arg1, f32 arg2, s16 arg3, s16 arg4, s16 *arg5) {
    s32 i;
    s16 id;
    MapBox *box;

    i = 0;
    if (D_807F70AC > 0) {
        do {
            if ((arg3 == D_807F70B0[i].unk0) && (arg4 == D_807F70B0[i].unk4)) {
                id = D_807F70B0[i].unk2;
                if (id) {} // FAKE: raises id's adjsave so the table address is not hoisted into a saved register
                box = (MapBox *)((u8 *)D_807F70B4 + id * 12);
                if (box && box) {} // FAKE: keeps box's live range apart from the hoisted cell table address
                if (((f32)box->unk0 <= arg0) && (arg0 <= (f32)box->unk6) && ((f32)box->unk2 <= arg1) && (arg1 <= (f32)box->unk8) && ((f32)box->unk4 <= arg2) && (arg2 <= (f32)box->unkA)) {
                    *arg5 = id;
                    mapCellFindAtPoint(arg0, arg1, arg2, arg3, id, arg5);
                }
            }
            i++;
        } while (i < D_807F70AC);
    }
}

typedef struct {
    /* 0x0 */ s16 id;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ f32 dist;
} MapChunkCandidate;

s16 mapChunkFindByPosition(f32 arg0, f32 arg1, f32 arg2, s16 arg3) {
    s32 best;
    s32 count;
    u8 flag;
    f32 dist;
    MapChunkCandidate cand[50];
    s32 pad1;
    s32 i;
    s32 pad2;
    s32 found;

    count = 0;
    if (gMapChunkCount == 0) {
        return -1;
    }
    arg0 *= 6.0f;
    arg1 *= 6.0f;
    arg2 *= 6.0f;
    if (mapChunkFindNodeAtPoint(arg0, arg1, arg2, arg3, &flag, &dist) != 0) {
        if (flag == 0) {
            return arg3;
        }
        cand[0].id = arg3;
        count = 1;
        cand[0].dist = dist;
    }
    found = 0;
    i = 0;
    if (gMapChunkCount > 0) {
        do {
            if (arg3 != i) {
                if (mapChunkFindNodeAtPoint(arg0, arg1, arg2, i, &flag, &dist) != 0) {
                    if (flag == 0) {
                        found = 1;
                    } else {
                        cand[count].id = i;
                        cand[count].dist = dist;
                        count++;
                        i++;
                    }
                } else {
                    i++;
                }
            } else {
                i++;
            }
        } while (found == 0 && i < gMapChunkCount);
    }
    if (found != 0) {
        return i;
    }
    arg0 = cand[0].dist;
    if (count == 0) {
        return arg3;
    }
    best = cand[0].id;
    for (i = 0; i < count; i++) {
        if (mapFloorHeightIsBetter(arg0, cand[i].dist, arg1) != 0) {
            arg0 = cand[i].dist;
            best = cand[i].id;
        }
    }
    return best;
}

s32 mapFloorHeightIsBetter(f32 arg0, f32 arg1, f32 arg2) {
    s32 var_v0;
    s32 var_v1;
    f32 var_fv0;
    f32 var_fv1;

    if (arg0 <= arg2) {
        var_v0 = 1;
    } else if ((arg0 - arg2) < 60.0f) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    if (arg1 <= arg2) {
        var_v1 = 1;
    } else if ((arg1 - arg2) < 60.0f) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    if (var_v0 == 0 && var_v1 == 0) {
        return 0;
    }
    if (var_v1 == 0) {
        return 0;
    }
    if (var_v0 == 0) {
        return 1;
    }
    if (arg2 < arg0) {
        var_fv0 = arg0 - arg2;
    } else {
        var_fv0 = arg2 - arg0;
    }
    if (arg2 < arg1) {
        var_fv1 = arg1 - arg2;
    } else {
        var_fv1 = arg2 - arg1;
    }
    if (var_fv0 < var_fv1) {
        return 0;
    }
    return 1;
}

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13[1];
} MapCollisionNode; /* 0x14 */

s32 mapChunkFindNodeAtPoint(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, f32 *arg5) {
    MapCollisionNode *var_s0;
    MapCollisionNode *temp_s1;
    MapChunk *temp_v0;

    temp_v0 = (MapChunk *)((u8 *)gMapChunks + arg3 * 0x1C8);
    if (arg0 < (f32)temp_v0->unk80) {
        return 0;
    }
    if (arg2 < (f32)temp_v0->unk82) {
        return 0;
    }
    if ((f32)temp_v0->unk84 < arg0) {
        return 0;
    }
    if ((f32)temp_v0->unk86 < arg2) {
        return 0;
    }
    var_s0 = (MapCollisionNode *)temp_v0->unk78;
    temp_s1 = (MapCollisionNode *)temp_v0->unk7C;
    if (var_s0 != temp_s1) {
        do {
            if ((mapNodeBoxContainsPoint(var_s0, arg0, arg2) != 0) && (mapNodeTriangleContainsPoint(var_s0, arg0, arg2) != 0)) {
                if (var_s0->unk12 & 1) {
                    *arg4 = 0;
                } else {
                    *arg4 = 1;
                    *arg5 = (f32)var_s0->unk6;
                }
                return 1;
            }
            var_s0++;
        } while (var_s0 != temp_s1);
    }
    return 0;
}

s32 mapNodeBoxContainsPoint(void *arg0, f32 arg1, f32 arg2) {
    f32 temp_fa1;
    f32 temp_fv1;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv0_4;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_v1;
    s16 temp_v0;
    MapCollisionNode *box;

    box = arg0;
    temp_v1 = box->unk2;
    temp_v0 = box->unk0;
    if (temp_v0 < temp_v1) {
        var_fv0 = (f32) temp_v0;
    } else {
        var_fv0 = (f32) temp_v1;
    }
    temp_fv1 = (f32) box->unk4;
    if (!(var_fv0 < temp_fv1)) {
        var_fv0 = temp_fv1;
    }
    if (arg1 < var_fv0) {
        return 0;
    }
    temp_a1 = box->unkC;
    temp_a2 = box->unkE;
    if (temp_a1 < temp_a2) {
        var_fv0_2 = (f32) temp_a1;
    } else {
        var_fv0_2 = (f32) temp_a2;
    }
    temp_fa1 = (f32) box->unk10;
    if (!(var_fv0_2 < temp_fa1)) {
        var_fv0_2 = temp_fa1;
    }
    if (arg2 < var_fv0_2) {
        return 0;
    }
    if (temp_v1 < temp_v0) {
        var_fv0_3 = (f32) temp_v0;
    } else {
        var_fv0_3 = (f32) temp_v1;
    }
    if (!(temp_fv1 < var_fv0_3)) {
        var_fv0_3 = temp_fv1;
    }
    if (var_fv0_3 < arg1) {
        return temp_v1 * 0;
    }
    if (temp_a2 < temp_a1) {
        var_fv0_4 = (f32) temp_a1;
    } else {
        var_fv0_4 = (f32) temp_a2;
    }
    if (!(temp_fa1 < var_fv0_4)) {
        var_fv0_4 = temp_fa1;
    }
    if (var_fv0_4 < arg2) {
        return 0;
    }
    return 1;
}

s32 mapNodeTriangleContainsPoint(void *arg0, f32 arg1, f32 arg2) {
    f64 cz;
    f64 mx;
    f64 cx;
    f64 mz;
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f64 c;
    f64 lead0; // FAKE: unused pad local, keeps the 0xC8 frame and the dx/dz/ox/oz home slots
    u16 flag;
    s32 i;

    flag = 0;
    mx = (((MapCollisionNode *)arg0)->unk4 + ((MapCollisionNode *)arg0)->unk2) * 0.5;
    mz = (((MapCollisionNode *)arg0)->unk10 + ((MapCollisionNode *)arg0)->unkE) * 0.5;
    cx = (((MapCollisionNode *)arg0)->unk0 + mx) * 0.5;
    cz = (((MapCollisionNode *)arg0)->unkC + mz) * 0.5;
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            dx = ((MapCollisionNode *)arg0)->unk2 - ((MapCollisionNode *)arg0)->unk0;
            dz = ((MapCollisionNode *)arg0)->unkE - ((MapCollisionNode *)arg0)->unkC;
            ox = ((MapCollisionNode *)arg0)->unk0;
            oz = ((MapCollisionNode *)arg0)->unkC;
            break;
        case 1:
            dx = ((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk0;
            dz = ((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkC;
            ox = ((MapCollisionNode *)arg0)->unk0;
            oz = ((MapCollisionNode *)arg0)->unkC;
            break;
        case 2:
            dx = ((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk2;
            dz = ((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkE;
            ox = ((MapCollisionNode *)arg0)->unk2;
            oz = ((MapCollisionNode *)arg0)->unkE;
            break;
        }
        mx = (arg1 - ox) * dz; // mx/mz reused as the two cross products
        mz = (arg2 - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        if ((mz <= mx ? 1 : -1) != (c >= 0.0 ? 1 : -1)) {
            flag = 1;
        }
    }
    return (flag == 0) & 0xFF;
}


typedef struct {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x270 - 0x8];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ s16 unk278;
    /* 0x27A */ s16 unk27A;
    /* 0x27C */ u8 pad27C[0x288 - 0x27C];
    /* 0x288 */ f32 unk288;
    /* 0x28C */ u8 pad28C[4];
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8 pad292[0x2F0 - 0x292];
} MapPlayer;

extern MapPlayer *gPlayerSlots;
extern u8 gCurrentPlayerIndex;

void mapChunkActivate(s16 arg0) {
    gMapChunks[arg0].unk0 = 1;
    gMapChunks[arg0].unk1 |= 1 << gCurrentPlayerIndex;
    gMapChunks[arg0].unk68 = gPlayerSlots[gCurrentPlayerIndex].unk270;
    gMapChunks[arg0].unk6C = gPlayerSlots[gCurrentPlayerIndex].unk272;
    gMapChunks[arg0].unk70 = gPlayerSlots[gCurrentPlayerIndex].unk274;
    gMapChunks[arg0].unk74 = gPlayerSlots[gCurrentPlayerIndex].unk276;
}


void mapChunkSetIndexOverride(s8 arg0) {
    D_807F70AB = arg0;
}

void frustumOrientPolyNormals(f32, f32, f32, void *, void *);
void frustumCornersTransformByInverse(Mtx *);
void frustumCalculateCornerRays(f32, f32, f32);
void mapUpdateFogDistance(f32 *, s16);
void mapChunkClearBounds();
void mapChunkActivate(s16);
void mapTriggerCollectZonesAtPoint(f32, f32, f32);
void mapChunkRenderNodes(f32, f32, f32);
void mapTriggerApplyZones(f32, f32, f32);
void mapChunkTraversePortals(s16, s32, s32, s32, s32, s32, f32, f32, f32);
void effectWaterUpdateMeshes(f32, f32, f32, u8);
void actorCalculateTargetDistancesAndAngles(f32, f32, f32);
void mapChunksApplyLights(f32, f32, f32);
extern u8 D_807F5E20[];
extern u8 D_807F5E68[];
extern u8 D_807444FC;
extern f32 D_807F5FB4;
extern f32 D_807F5FB0;
extern u8 D_807F6C08;

void mapChunkFrameUpdate(f32 arg0, f32 arg1, f32 arg2) {
    gPlayerSlots[gCurrentPlayerIndex].unk290 = mapChunkFindByPosition(arg0, arg1, arg2, gPlayerSlots[gCurrentPlayerIndex].unk290);
    if (D_807F70AB != 0) {
        gPlayerSlots[gCurrentPlayerIndex].unk290 = *(s16 *)((u8 *)gPlayerSlots[gCurrentPlayerIndex].unk4 + 0x12C);
    }
    mapUpdateFogDistance(&gPlayerSlots[gCurrentPlayerIndex].unk288, gPlayerSlots[gCurrentPlayerIndex].unk290);
    D_807F7138 = (s16)(s32)gPlayerSlots[gCurrentPlayerIndex].unk288;
    frustumCalculateCornerRays(D_807F5FB4, D_807F5FB0, (f32)D_807F7138);
    frustumCornersTransformByInverse((Mtx *)((u8 *)gPlayerSlots + gCurrentPlayerIndex * 0x2F0 + (D_807444FC << 6) + 8));
    frustumOrientPolyNormals(arg0, arg1, arg2, &D_807F5E68, &D_807F5E20);
    mapChunkClearBounds();
    mapChunkActivate(gPlayerSlots[gCurrentPlayerIndex].unk290);
    mapTriggerCollectZonesAtPoint(arg0, arg1, arg2);
    D_807F6C80 = 0;
    D_807F6C08 = 0;
    mapChunkTraversePortals(gPlayerSlots[gCurrentPlayerIndex].unk290, 0, gPlayerSlots[gCurrentPlayerIndex].unk270, gPlayerSlots[gCurrentPlayerIndex].unk272, gPlayerSlots[gCurrentPlayerIndex].unk274, gPlayerSlots[gCurrentPlayerIndex].unk276, arg0, arg1, arg2);
    mapChunkRenderNodes(arg0, arg1, arg2);
    effectWaterUpdateMeshes(arg0, arg1, arg2, gCurrentPlayerIndex);
    actorCalculateTargetDistancesAndAngles(arg0, arg1, arg2);
    mapChunksApplyLights(arg0, arg1, arg2);
}

extern s32 assetLoad(s32, s32, s32, s32);

u8 *mapChunkLoadAssetRefs(u8 *arg0, u8 *arg1, s16 arg2) {
    s32 count;
    s32 kind;
    s32 b;

    count = 0;
    if ((arg0 != arg1) && (arg2 > 0)) {
        do {
            kind = *(u32 *)arg0 >> 0x18;
            if (kind == 0xFD) {
                if (((u32)(*(s32 *)(arg0 + 4) * 0x10) >> 0x1C) == 0) {
                    b = *(s32 *)(arg0 + 4);
                    *(s32 *)(arg0 + 4) = assetLoad(0x19, b, 0, 0);
                    count++;
                }
                if (arg0 && arg0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            arg0 += 8;
        } while ((arg0 != arg1) && (count < arg2));
    }
    return arg0;
}


extern void collisionBstLookupByHash(u32, u32 *, u32 *);
extern s32 assetFreeBuffer(void *, s32, s32);

void mapChunkReleaseAssets(u8 *arg0, u8 *arg1) {
    s32 pad[2];
    u32 sp44;
    u32 sp40;
    u32 temp_a0;
    u32 x1;

    if (arg0 != arg1) {
        do {
            if ((x1 = (*(u32 *)arg0 >> 0x18)) == 0xFD) {
                if (sp40) {
                }
                temp_a0 = *(u32 *)(arg0 + 4);
                if ((temp_a0 >= 0x80000000U) && (temp_a0 < 0xA0000000U)) {
                    collisionBstLookupByHash(temp_a0, &sp44, &sp40);
assetFreeBuffer((void *)*(u32 *)(arg0 + 4), 0x542, 0x22); *(u32 *)(arg0 + 4) = sp40;
                }
            }
            arg0 += 8;
        } while (arg0 != arg1);
    }
}

void mapChunkSetFlagBit3(s16 arg0) {
    gMapChunks[arg0].unk7 |= 8;
}

extern u32 D_807FBB68;
extern s32 gFrameCounter;
s16 mapObjectCollectIdsByType();

void mapChunkUpdateAssetStreaming(void) {
    s32 i;
    s32 j;
    s8 buf[0x10];
    u8 flags[0x34];
    s8 idx;
    s16 n;

    if (!(D_807FBB68 & 0x100)) {
        for (i = 0; i < gMapChunkCount; i++) {
            flags[i] = 0;
        }
        for (i = 0; i < gMapChunkCount; i++) {
            if (gMapChunks[i].unk1 != 0) {
                flags[i] = 1;
                gMapChunks[i].unk28 = gFrameCounter;
                if (!(gMapChunks[i].unk7 & 4)) {
                    gMapChunks[i].unk8 = (s32)mapChunkLoadAssetRefs((u8 *)gMapChunks[i].unk8, (u8 *)gMapChunks[i].unk10, 0x270F);
                    gMapChunks[i].unk7 |= 4;
                    gMapChunks[i].unk7 &= 0xFFFC;
                }
                n = mapObjectCollectIdsByType((s8)i, buf, 0x10);
                for (j = 0; j < n; j++) {
                    idx = buf[j];
                    if (flags[idx] == 0) {
                        if (gMapChunks[idx].unk1 == 0) {
                            if (!(gMapChunks[idx].unk7 & 4)) {
                                gMapChunks[idx].unk8 = (s32)mapChunkLoadAssetRefs((u8 *)gMapChunks[idx].unk8, (u8 *)gMapChunks[idx].unk10, 5);
                                if (gMapChunks[idx].unk8 == gMapChunks[idx].unk10) {
                                    gMapChunks[idx].unk7 &= 0xFFFD;
                                    gMapChunks[idx].unk7 |= 4;
                                } else {
                                    gMapChunks[idx].unk7 |= 2;
                                }
                                gMapChunks[idx].unk7 &= 0xFFFE;
                            }
                            flags[idx] = 1;
                        }
                    }
                }
            }
        }
        for (i = 0; i < gMapChunkCount; i++) {
            if (flags[i] == 0) {
                if (gMapChunks[i].unk7 & 8) {
                    if (!(gMapChunks[i].unk7 & 4)) {
                        gMapChunks[i].unk8 = (s32)mapChunkLoadAssetRefs((u8 *)gMapChunks[i].unk8, (u8 *)gMapChunks[i].unk10, 5);
                        if (gMapChunks[i].unk8 == gMapChunks[i].unk10) {
                            gMapChunks[i].unk7 &= 0xFFFD;
                            gMapChunks[i].unk7 |= 4;
                        } else {
                            gMapChunks[i].unk7 |= 2;
                        }
                        gMapChunks[i].unk7 &= 0xFFFE;
                    }
                } else if (!(gMapChunks[i].unk7 & 1) && (u32)(gFrameCounter - gMapChunks[i].unk28) >= 3U) {
                    mapChunkReleaseAssets((u8 *)gMapChunks[i].unkC, (u8 *)gMapChunks[i].unk8);
                    gMapChunks[i].unk8 = gMapChunks[i].unkC;
                    gMapChunks[i].unk7 |= 1;
                    gMapChunks[i].unk7 &= ~6;
                }
            }
            gMapChunks[i].unk7 &= ~8;
        }
    }
}

extern void mapChunkBuildClipFrusta(f32, f32, f32);
extern void mapCellUpdateVisibility(f32, f32, f32, s32);

void mapChunkRenderNodes(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 off;

    mapChunkBuildClipFrusta(arg0, arg1, arg2);
    i = 0;
    off = 0;
    while (i < D_807F70AC) {
        i++;
        D_807F70B0[off].unk18 = 0;
        off += 1;
    }
    mapCellUpdateVisibility(arg0, arg1, arg2, -1);
    mapTriggerApplyZones(arg0, arg1, arg2);
}

extern f32 D_807F5FAC;
extern s32 D_807482F4;
extern u8 D_807F7148[];
void matrix4Invert(f32 (*)[4], f32 (*)[4]);
void mapScreenRectBuildFrustum(s32, s32, s32, s32, f32, f32, f32, u8, void *, void *, void *);

void mapChunkBuildClipFrusta(f32 arg0, f32 arg1, f32 arg2) {
    f32 spF8[4][4];
    f32 spB8[4][4];
    s32 i;
    u8 sp84[0x30];

    frustumCalculateCornerRays(D_807F5FB4, D_807F5FB0, D_807F5FAC);
    guMtxL2F(spF8, (Mtx *)((u8 *)gPlayerSlots + gCurrentPlayerIndex * 0x2F0 + (D_807444FC << 6) + 8));
    matrix4Invert(spB8, spF8);
    for (i = 0; i < gMapChunkCount; i++) {
        if (gMapChunks[i].unk0 == 1) {
            mapScreenRectBuildFrustum(gMapChunks[i].unk68, gMapChunks[i].unk6C, gMapChunks[i].unk70, gMapChunks[i].unk74,
                          arg0, arg1, arg2, gCurrentPlayerIndex, spB8, &gMapChunks[i].pad88, sp84);
            if (i == D_807482F4) {
                memcpy(D_807F7148, &gMapChunks[i].pad88, 0x140);
            }
        }
    }
}

typedef struct FrustumCorners {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
} FrustumCorners;

extern FrustumCorners D_807F5DF0;
#define FrustPlayer ((MapPlayer *)((u8 *)gPlayerSlots + arg7 * 0x2F0))
void mapScreenRectBuildFrustum(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, void *arg8, void *arg9, void *arg10) {
    s32 i;
    f32 q; // FAKE: named quotient (steers FP colouring: quotients take f0)
    f32 a;
    f32 uv2;
    f32 uv1;
    f32 uv0;
    f32 m[4][3];

    q = ((f32)(arg0 - FrustPlayer->unk270)) / (f32)FrustPlayer->unk278;
    a = (q * (D_807F5DF0.unkC - D_807F5DF0.unk0)) + D_807F5DF0.unk0;
    q = ((f32)(arg2 - FrustPlayer->unk270)) / (f32)FrustPlayer->unk278;
    uv2 = (q * (D_807F5DF0.unkC - D_807F5DF0.unk0)) + D_807F5DF0.unk0;
    q = ((f32)(arg1 - FrustPlayer->unk272)) / (f32)FrustPlayer->unk27A;
    uv1 = ((D_807F5DF0.unk1C - D_807F5DF0.unk4) * q) + D_807F5DF0.unk4;
    q = ((f32)(arg3 - FrustPlayer->unk272)) / (f32)FrustPlayer->unk27A;
    uv0 = ((D_807F5DF0.unk1C - D_807F5DF0.unk4) * q) + D_807F5DF0.unk4;
    m[0][0] = uv2; m[0][1] = uv0; m[0][2] = D_807F5DF0.unk8;
    m[1][0] = a; m[1][1] = uv0; m[1][2] = D_807F5DF0.unk14;
    m[2][0] = uv2; m[2][1] = uv1; m[2][2] = D_807F5DF0.unk20;
    m[3][0] = a; m[3][1] = uv1; m[3][2] = D_807F5DF0.unk2C;
    for (i = 0; i < 4; i++) {
        guMtxXFMF((float (*)[4])arg8, m[i][0], m[i][1], m[i][2], &((f32 (*)[3])arg10)[i][0], &((f32 (*)[3])arg10)[i][1], &((f32 (*)[3])arg10)[i][2]);
    }
    frustumOrientPolyNormals(arg4, arg5, arg6, arg9, arg10);
}
#undef FrustPlayer

typedef struct MapTriangle {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
} MapTriangle;

typedef struct MapZone {
    u8 pad0[8];
    s32 unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    u8 pad14[0x44];
    s16 unk58[8];
    u8 unk68;
} MapZone;

extern void *D_807F70B8[];
extern u8 D_807F7048[];
extern u8 D_807F7058;
extern u8 D_807F7060[];
extern u8 D_807F7070;

s32 mapTriangleBoundsContainPoint(MapTriangle *, f32, f32);
s32 mapTriangleContainsPoint(void *, f32, f32);
f32 mapTriangleHeightAtPoint(MapTriangle *, f32, f32);

void mapTriggerCollectZonesAtPoint(f32 arg0, f32 arg1, f32 arg2) {
    s32 pad[10]; // FAKE: frame size
    MapZone **p;
    MapZone *zone;
    MapTriangle *node;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 found;
    f32 h;

    D_807F7058 = 0;
    D_807F7070 = 0;
    for (p = (MapZone **)D_807F70B8, i = 0; i != 0x20; i++) {
        if (*p != NULL) {
            zone = *p;
            if ((f32)zone->unk10 <= arg1 && arg1 <= (f32)(zone->unk12 + zone->unkE)) {
                node = (MapTriangle *)((u8 *)zone->unk8);
                for (j = 0; j < zone->unkC; j++, node++) {
                    if (mapTriangleBoundsContainPoint(node, arg0, arg2) != 0 && mapTriangleContainsPoint(node, arg0, arg2) != 0) {
                        h = mapTriangleHeightAtPoint(node, arg0, arg2);
                        if (h <= arg1 && arg1 <= (f32)zone->unkE + h) {
                            k = 0;
                            if (D_807F7058 != 0x10) {
                                D_807F7048[D_807F7058] = i;
                                D_807F7058++;
                            }
                            for (; k < zone->unk68; k++) {
                                found = 0;
                                n = 0;
                                while (!found && n < D_807F7070) {
                                    if (D_807F7060[n] == zone->unk58[k]) {
                                        found = 1;
                                    } else {
                                        n++;
                                    }
                                }
                                if (!found && n != 0x10) {
                                    D_807F7060[D_807F7070] = zone->unk58[k];
                                    D_807F7070++;
                                }
                            }
                        }
                    }
                }
            }
        }
        p++;
    }
}

typedef struct MapTrigger {
    s16 unk0[10];
    s16 unk14[16];
    u8 unk34;
    s16 unk36[16];
    u8 unk56;
} MapTrigger;


void mapCellSetFlag(s32, u8);

void mapTriggerApplyZones(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 j;
    s32 done;
    s16 *val;
    MapTrigger *trig;
    u8 idx;

    done = 0;
    i = 0;
    while (i < D_807F7058) {
        idx = D_807F7048[i];
        if (D_807F70B8[idx] != 0) {
            trig = (MapTrigger *)D_807F70B8[idx];
            if (!done) {
                if (trig->unk56 != 0) {
                    done = 1;
                    val = trig->unk36;
                    for (j = 0; j < D_807F70AC; j++) {
                        *((u8 *)D_807F70B0 + j * 0x1C + 0x18) = 0;
                    }
                    for (j = 0; j < trig->unk56; j++) {
                        mapCellSetFlag(*val, 1);
                        val++;
                    }
                } else {
                    val = trig->unk14;
                    if (!trig->unk56) {
                    }
                    for (j = 0; j < trig->unk34; j++) {
                        mapCellSetFlag(*val, 0);
                        val++;
                    }
                }
            }
        }
        i++;
    }
}

void mapCellSetFlag(s32 arg0, u8 arg1) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    while (!found && i < D_807F70AC) {
        if (arg0 == ((MapCell *)D_807F70B0)[i].unk2) {
            ((MapCell *)D_807F70B0)[i].unk18 = arg1;
            if (arg1 != 0) {
                ((MapCell *)D_807F70B0)[i].unk19 = 1;
            }
            found = 1;
        }
        i++;
    }
    for (i = 0; i < D_807F70AC; i++) {
        if (arg0 == ((MapCell *)D_807F70B0)[i].unk4) {
            mapCellSetFlag(((MapCell *)D_807F70B0)[i].unk2, arg1);
        }
    }
}

f32 mapTriangleHeightAtPoint(MapTriangle *arg0, f32 arg1, f32 arg2) {
    f32 ret;
    f64 d68;
    f64 d02;
    f64 q;
    f64 d04;
    f64 d6A;
    f64 t;
    f64 dCE;
    f64 N1;
    f64 N2;
    f64 N3;
    f64 dC10;
    f64 N3b;

    d02 = (f64)(arg0->unk0 - arg0->unk2);
    d68 = (f64)(arg0->unk6 - arg0->unk8);
    dCE = (f64)(arg0->unkC - arg0->unkE);
    d04 = (f64)(arg0->unk0 - arg0->unk4);
    d6A = (f64)(arg0->unk6 - arg0->unkA);
    dC10 = (f64)(arg0->unkC - arg0->unk10);
    N1 = d68 * dC10 - dCE * d6A;
    N2 = dCE * d04 - d02 * dC10;
    N3b = d02 * d6A - d68 * d04;  // FAKE: separate named web for the q term (N3 below recomputes it for t)
    q = -((f64)arg0->unkE * N3b + (N1 * (f64)arg0->unk2 + N2 * (f64)arg0->unk8));
    if (N2 * 2000.0 > 0.01 || N2 * 2000.0 < -0.01) {
        N3 = d02 * d6A - d68 * d04;  // FAKE: second web of the same product
        t = N1 * arg1 + N2 * -1000.0 + N3 * arg2 + q;
        t = t / (N2 * 2000.0);
        if (t < 0.0) {
            t = 0.0 - t;
        }
        ret = (f32)(2000.0 * t - 1000.0);
    } else {
        ret = -32768.0f;
    }
    return ret;
}

s32 mapTriangleBoundsContainPoint(MapTriangle *arg0, f32 arg1, f32 arg2) {
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;

    minX = (arg0->unk0 < arg0->unk2) ? (f32)arg0->unk0 : (f32)arg0->unk2;
    minX = (minX < (f32)arg0->unk4) ? minX : (f32)arg0->unk4;
    minZ = (arg0->unkC < arg0->unkE) ? (f32)arg0->unkC : (f32)arg0->unkE;
    minZ = (minZ < (f32)arg0->unk10) ? minZ : (f32)arg0->unk10;
    maxX = (arg0->unk0 > arg0->unk2) ? (f32)arg0->unk0 : (f32)arg0->unk2;
    maxX = (maxX > (f32)arg0->unk4) ? maxX : (f32)arg0->unk4;
    maxZ = (arg0->unkC > arg0->unkE) ? (f32)arg0->unkC : (f32)arg0->unkE;
    maxZ = (maxZ > (f32)arg0->unk10) ? maxZ : (f32)arg0->unk10;
    if (arg1 < minX || arg1 > maxX || arg2 < minZ || arg2 > maxZ) {
        return 0;
    }
    return 1;
}

s32 mapTriangleContainsPoint(void *arg0, f32 arg1, f32 arg2) {
    f64 cz;
    f64 mx;
    f64 cx;
    f64 mz;
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f64 c;
    f64 lead0; // FAKE: unused pad local, keeps the 0xC8 frame and the dx/dz/ox/oz home slots
    u16 flag;
    s32 i;

    flag = 0;
    mx = (((MapCollisionNode *)arg0)->unk4 + ((MapCollisionNode *)arg0)->unk2) * 0.5;
    mz = (((MapCollisionNode *)arg0)->unk10 + ((MapCollisionNode *)arg0)->unkE) * 0.5;
    cx = (((MapCollisionNode *)arg0)->unk0 + mx) * 0.5;
    cz = (((MapCollisionNode *)arg0)->unkC + mz) * 0.5;
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            dx = ((MapCollisionNode *)arg0)->unk2 - ((MapCollisionNode *)arg0)->unk0;
            dz = ((MapCollisionNode *)arg0)->unkE - ((MapCollisionNode *)arg0)->unkC;
            ox = ((MapCollisionNode *)arg0)->unk0;
            oz = ((MapCollisionNode *)arg0)->unkC;
            break;
        case 1:
            dx = ((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk0;
            dz = ((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkC;
            ox = ((MapCollisionNode *)arg0)->unk0;
            oz = ((MapCollisionNode *)arg0)->unkC;
            break;
        case 2:
            dx = ((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk2;
            dz = ((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkE;
            ox = ((MapCollisionNode *)arg0)->unk2;
            oz = ((MapCollisionNode *)arg0)->unkE;
            break;
        }
        mx = (arg1 - ox) * dz; // mx/mz reused as the two cross products
        mz = (arg2 - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        if ((mz <= mx ? 1 : -1) != (c >= 0.0 ? 1 : -1)) {
            flag = 1;
        }
    }
    return (flag == 0) & 0xFF;
}

s32 mapBspBoxInFrustum(s16, s16, s16, s16, s16, s16, f32, f32, f32, f32, void *);

void mapCellUpdateVisibility(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    s32 idx;
    s32 i;
    s32 off;

    i = 0;
    if (D_807F70AC > 0) {
        off = 0; do { // FAKE: scheduling (joins the loop preheader store)
            if (arg3 == ((MapCell *)((u8 *)D_807F70B0 + off))->unk4) {
                if (gMapChunks[((MapCell *)((u8 *)D_807F70B0 + off))->unk0].unk0 == 1) {
                    idx = ((MapCell *)((u8 *)D_807F70B0 + off))->unk2;
                    if (mapBspBoxInFrustum(D_807F70B4[idx].unk0, D_807F70B4[idx].unk2, D_807F70B4[idx].unk4,
                                      D_807F70B4[idx].unk6, D_807F70B4[idx].unk8, D_807F70B4[idx].unkA,
                                      arg0, arg1, arg2, D_807F5FAC,
                                      (u8 *)&gMapChunks[((MapCell *)((u8 *)D_807F70B0 + off))->unk0] + 0x88) != 0) {
                        ((MapCell *)((u8 *)D_807F70B0 + off))->unk18 = 1;
                        ((MapCell *)((u8 *)D_807F70B0 + off))->unk19 = 1;
                    }
                    if (((MapCell *)((u8 *)D_807F70B0 + off))->unk18 != 0) {
                        mapCellUpdateVisibility(arg0, arg1, arg2, ((MapCell *)((u8 *)D_807F70B0 + off))->unk2);
                    }
                }
            }
            i++;
            off += 0x1C;
        } while (i < D_807F70AC);
    }
}

typedef struct MapChunkCellMatrices {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[0x12];
    /* 0x14 */ void *unk14[2];
    /* 0x1C */ u8 pad1C[0x8];
} MapChunkCellMatrices;

typedef struct MapCellView {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8[2];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10[2];
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 pad1A[2];
} MapCellView;

typedef struct MapChunkLightView {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 unk5;
    /* 0x006 */ u8 pad6[0x46];
    /* 0x04C */ MapChunkCellMatrices *unk4C;
    /* 0x050 */ u8 pad50[4];
    /* 0x054 */ u8 *unk54;
    /* 0x058 */ u8 *unk58;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ void *unk60[4];
    /* 0x070 */ u8 pad70[0x158];
} MapChunkLightView;

void matrixCacheResetStats(void);
void lightClearActiveCount(void);
s32 lightCollectVolumesInBounds(f32, f32, f32, s16, s16, s16, s16, s16, s16, s32, u8 *);
void *matrixCacheLookup(s32, s32, s16, u8);
void *matrixCacheInsert(s32, s32, s16, u8, s32, u8);
void func_8065C990(void *, void *, s32, void *, s32, s32);
void effectWaterApplyLights(f32, f32, f32);
extern f32 D_807F7EEC;
extern f32 D_807F7EF0;
extern f32 D_807F7EF4;
extern s32 D_807FBB60;
extern u8 D_807F78C0;

#define MAP_CHUNK_LIGHT ((MapChunkLightView *)gMapChunks)
#define MAP_CELL_VIEW ((MapCellView *)D_807F70B0)
void mapChunksApplyLights(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 obj;
    void *matrix;
    u8 *src;
    s16 key;
    s32 pad0;
    MapChunkCellMatrices *node;
    s16 boxIdx;
    s32 j;
    s32 k;
    s32 nodeIdx;
    s32 found;
    u8 hit;
    s32 pad1;
    u8 q;
    u8 flag;
    flag = 0;
    matrixCacheResetStats();
    lightClearActiveCount();
    for (i = 0; i < gMapChunkCount; i++) {
        if ((MAP_CHUNK_LIGHT[i].unk3 != 0) && (MAP_CHUNK_LIGHT[i].unk0 == 1) && (MAP_CHUNK_LIGHT[i].unk4 == 0)) {
            MAP_CHUNK_LIGHT[i].unk4 = 1;
            if (MAP_CHUNK_LIGHT[i].unk5 == 2) {
                flag = 0;
                for (k = 0; k < D_807F70AC; k++) {
                    if ((i == MAP_CELL_VIEW[k].unk0) && (MAP_CELL_VIEW[k].unk19 != 0)) {
                        for (j = 0; j < 2; j++) {
                            if (MAP_CELL_VIEW[k].unk10[j] != 0) {
                                boxIdx = MAP_CELL_VIEW[k].unk2;
                                obj = lightCollectVolumesInBounds(arg0, arg1, arg2, D_807F70B4[boxIdx].unk0, D_807F70B4[boxIdx].unk2, D_807F70B4[boxIdx].unk4, D_807F70B4[boxIdx].unk6, D_807F70B4[boxIdx].unk8, D_807F70B4[boxIdx].unkA, i, &hit);
                                nodeIdx = 0;
                                found = 0;
                                key = MAP_CELL_VIEW[k].unk2; node = MAP_CHUNK_LIGHT[i].unk4C;  // FAKE: same-line statements steer scheduling
                                do {
                                    if (key == node->unk0) {
                                        found = 1;
                                    } else {
                                        nodeIdx += 1;
                                        node += 1;
                                    }
                                } while (found == 0);
                                if (D_807FBB60 & 0x10) {
                                    q = j;
                                    MAP_CHUNK_LIGHT[i].unk4C[nodeIdx].unk14[j] = matrixCacheLookup(obj, i, boxIdx, q);
                                    if (MAP_CHUNK_LIGHT[i].unk4C[nodeIdx].unk14[j] == NULL) {
                                        MAP_CHUNK_LIGHT[i].unk4C[nodeIdx].unk14[j] = matrixCacheInsert(obj, i, boxIdx, q, MAP_CELL_VIEW[k].unk10[j], hit);
                                        src = MAP_CHUNK_LIGHT[i].unk54 + MAP_CELL_VIEW[k].unk8[j] * 0x10;
                                        memcpy(MAP_CHUNK_LIGHT[i].unk4C[nodeIdx].unk14[j], src, MAP_CELL_VIEW[k].unk10[j] * 0x10);
                                        matrix = MAP_CHUNK_LIGHT[i].unk4C[nodeIdx].unk14[j];
                                        D_807F7EEC = ((f32 *)D_8076A0B4)[i];
                                        D_807F7EF0 = ((f32 *)D_8076A0B8)[i];
                                        D_807F7EF4 = ((f32 *)D_8076A0BC)[i];
                                        func_8065C990(matrix, (u8 *)matrix + MAP_CELL_VIEW[k].unk10[j] * 0x10, 1, &D_807F78C0, obj, MAP_CHUNK_LIGHT[i].unk3 == 1);
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (flag == 0) {
                    obj = lightCollectVolumesInBounds(arg0, arg1, arg2, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -1, &hit);
                    flag = 1;
                }
                if (MAP_CHUNK_LIGHT[i].unk60[D_807444FC] == NULL) {
                    MAP_CHUNK_LIGHT[i].unk60[D_807444FC] = heapAlloc(MAP_CHUNK_LIGHT[i].unk5C);
                }
                memcpy(MAP_CHUNK_LIGHT[i].unk60[D_807444FC], MAP_CHUNK_LIGHT[i].unk54, MAP_CHUNK_LIGHT[i].unk5C);
                D_807F7EEC = ((f32 *)D_8076A0B4)[i];
                D_807F7EF0 = ((f32 *)D_8076A0B8)[i];
                D_807F7EF4 = ((f32 *)D_8076A0BC)[i];
                if (D_807FBB60 & 0x10) {
                    func_8065C990((s32)MAP_CHUNK_LIGHT[i].unk60[D_807444FC], (s32)MAP_CHUNK_LIGHT[i].unk60[D_807444FC] + MAP_CHUNK_LIGHT[i].unk5C, 1, &D_807F78C0, obj, MAP_CHUNK_LIGHT[i].unk3 == 1);  // FAKE: s32 args steer the arg0 register (callee takes void * here)
                }
            }
            MAP_CHUNK_LIGHT[i].unk58 = MAP_CHUNK_LIGHT[i].unk60[D_807444FC];
        }
    }
    effectWaterApplyLights(arg0, arg1, arg2);
}
#undef MAP_CHUNK_LIGHT
#undef MAP_CELL_VIEW

typedef struct {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 unk5;
    /* 0x006 */ u8 pad6[0x0E];
    /* 0x014 */ MapNode *unk14;
    /* 0x018 */ u8 pad18[4];
    /* 0x01C */ MapNode *unk1C;
    /* 0x020 */ u8 pad20[0x40];
    /* 0x060 */ void *unk60[4];
    /* 0x070 */ u8 pad70[0x158];
} MapChunkDraw;


void modelSlotFreeTexAnimBuffers(s32, u8);
void modelSlotFreeAssetTextures(s32, u8);
s32 matrixCacheEvict(s32, s32);
void heapFree(void *);

void mapChunkFreeIdleBuffers(void) {
    s32 i;
    s32 off;
    MapChunkDraw *eff;

    if (D_807F713A != 0) {
        matrixCacheEvict(0, 0x190);
    }
    i = 0;
    off = 0;
    while (i < gMapChunkCount) {
        eff = (MapChunkDraw *)((u8 *)gMapChunks + off);
        if (eff->unk3 != 0 && eff->unk5 != 2 && eff->unk4 == 0) {
            if (((MapChunkDraw *)gMapChunks)[i].unk60[D_807444FC] != NULL) {
                heapFree(((MapChunkDraw *)gMapChunks)[i].unk60[D_807444FC]);
                ((MapChunkDraw *)gMapChunks)[i].unk60[D_807444FC] = NULL;
            }
        }
        i++;
        off += 0x1C8;
    }
}

void mapChunkReleaseAndAdvance(void) {
    MapChunkDraw *eff;
    MapNode *node;

    if (!mapChunkIsVisible(D_807F70AA)) {
        eff = &((MapChunkDraw *)gMapChunks)[D_807F70AA];
        node = eff->unk14;
        if (node) {
            do {
                modelSlotFreeTexAnimBuffers(node->unk0, node->unk24);
                modelSlotFreeAssetTextures(node->unk0, node->unk24);
                node = node->unk14;
            } while (node);
            eff = &((MapChunkDraw *)gMapChunks)[D_807F70AA];
        }
        node = eff->unk1C;
        if (node) {
            do {
                modelSlotFreeTexAnimBuffers(node->unk0, node->unk24);
                modelSlotFreeAssetTextures(node->unk0, node->unk24);
                node = node->unk14;
            } while (node);
        }
    }
    D_807F70AA++;
    if (gMapChunkCount == D_807F70AA) {
        D_807F70AA = 0;
    }
}

extern s16 D_807F6C30[];

s32 mapNodeIdListContains(s16 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        if (arg0 == D_807F6C30[i]) {
            return 1;
        }
        continue;
    }
    return 0;
}

extern s16 D_807F6BF0[];

typedef struct {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 pad3[0x11];
    /* 0x014 */ s32 unk14;
    /* 0x018 */ s32 unk18;
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ s32 unk20;
    /* 0x024 */ s32 unk24;
    /* 0x028 */ u8 pad28[0x4];
    /* 0x02C */ s32 unk2C;
    /* 0x030 */ s32 unk30;
    /* 0x034 */ s32 unk34;
    /* 0x038 */ s32 unk38;
    /* 0x03C */ u8 pad3C[0x1C];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xC];
    /* 0x068 */ union {
        struct {
            /* 0x068 */ s32 unk68;
            /* 0x06C */ s32 unk6C;
            /* 0x070 */ s32 unk70;
            /* 0x074 */ s32 unk74;
        } w;
        struct {
            /* 0x068 */ s16 pad68;
            /* 0x06A */ s16 unk6A;
            /* 0x06C */ s16 pad6C;
            /* 0x06E */ s16 unk6E;
            /* 0x070 */ s16 pad70;
            /* 0x072 */ s16 unk72;
            /* 0x074 */ s16 pad74;
            /* 0x076 */ s16 unk76;
        } h;
    } tile;
    /* 0x078 */ u8 pad78[0x1C8 - 0x78];
} MapChunkTile;

typedef struct {
    /* 0x000 */ u8 pad0[0x8];
    /* 0x008 */ s32 unk8;
} MapChunkArg;

typedef struct {
    /* 0x000 */ u8 pad0[0x27C];
    /* 0x27C */ f32 unk27C;
    /* 0x280 */ u8 pad280[0x2F0 - 0x280];
} MapPlayerFog;

#define MAP_CHUNK_TILE_AT(i) (((MapChunkTile *)gMapChunks)[(i)])

extern u8 D_807F5FEC;
extern void *D_807F5DEC;
extern s32 D_807FBB64;
extern u8 D_807F6009;
extern s32 D_807F600C;
extern s32 D_807F5FFC;
extern Gfx D_2000180;

u32 osVirtualToPhysical(void *);
Gfx *mapViewDrawPass(Gfx *, void *, s32);
Gfx *mapChunkEmitSegmentCommands(Gfx *, u8);
void mapChunkAnimateTextures(u8);
s32 mapChunkEmitLayerDisplayLists();
Gfx *spriteListRender(Gfx *, s32);
Gfx *billboardRenderQueued(Gfx *, s16);
Gfx *renderEntryListBuildDisplayList(Gfx *, s32, s32, s32, f32, s32, s16, s32);
Gfx *func_80027034(Gfx *);
Gfx *effectWaterRenderSurfaces();
Gfx *fogRender(Gfx *);
Gfx *renderDepthSortedTargets(Gfx *);
void mapSetClipBounds();

void mapChunksRender(Gfx *gfx, void *arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    s32 i;
    s32 idx;
    s32 dl;
    u8 flag;

    idx = 0;
    flag = (D_807F5FEC != 0) && (((MapPlayerFog *)gPlayerSlots)[gCurrentPlayerIndex].unk27C == 45.0);
    gDPPipeSync(gfx++);
    if (arg5 & 0x10) {
        gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
        gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
        gfx = mapViewDrawPass(gfx, arg1, 1);
        if (((MapChunkArg *)arg1)->unk8 != -1) {
            gDPPipeSync(gfx++);
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkArg *)arg1)->unk8));
        }
        gfx = effectWaterRenderSurfaces(gfx, 0, 0);
        for (i = 0; i < D_807F6C08; i++) {
            if (((MapRelocEntry *)D_807F6C0C)[D_807F6BF0[i]].unk8 != -1) {
                gDPPipeSync(gfx++);
                gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapRelocEntry *)D_807F6C0C)[D_807F6BF0[i]].unk8));
            }
            if (((MapRelocEntry *)D_807F6C0C)[D_807F6BF0[i]].unkC != -1) {
                gDPPipeSync(gfx++);
                gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapRelocEntry *)D_807F6C0C)[D_807F6BF0[i]].unkC));
            }
        }
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    for (i = D_807F6C80 - 1; i >= 0; i--) {
        idx = D_807F6C58[i];
        if (MAP_CHUNK_TILE_AT(idx).unk0 == 1) {
            if (MAP_CHUNK_TILE_AT(idx).unk2 != 0) {
                mapChunkAnimateTextures(idx);
                MAP_CHUNK_TILE_AT(idx).unk2 = 0;
            }
            gDPPipeSync(gfx++);
            gDPSetScissor(gfx++, G_SC_NON_INTERLACE, MAP_CHUNK_TILE_AT(idx).tile.w.unk68, MAP_CHUNK_TILE_AT(idx).tile.w.unk6C, MAP_CHUNK_TILE_AT(idx).tile.w.unk70, MAP_CHUNK_TILE_AT(idx).tile.w.unk74);
            mapSetClipBounds(MAP_CHUNK_TILE_AT(idx).tile.h.unk6A, MAP_CHUNK_TILE_AT(idx).tile.h.unk6E, MAP_CHUNK_TILE_AT(idx).tile.h.unk72, MAP_CHUNK_TILE_AT(idx).tile.h.unk76);
            gfx = fogRender(gfx);
            if (arg5 & 0x10) {
                gfx = mapChunkEmitSegmentCommands(gfx, idx);
                if (MAP_CHUNK_TILE_AT(idx).unk2C != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)MAP_CHUNK_TILE_AT(idx).unk58));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = (Gfx *)mapChunkEmitLayerDisplayLists(gfx, idx, 0);
                    gDPPipeSync(gfx++);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
                if (MAP_CHUNK_TILE_AT(idx).unk34 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)MAP_CHUNK_TILE_AT(idx).unk58));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = (Gfx *)mapChunkEmitLayerDisplayLists(gfx, idx, 2);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
            }
            gDPPipeSync(gfx++);
            if (!(D_807FBB64 & 0x01000000)) {
                gfx = billboardRenderQueued(gfx, idx);
            }
            gfx = spriteListRender(gfx, MAP_CHUNK_TILE_AT(idx).unk24);
            D_807F6009 = 0xFF;
            if (flag != 0) {
                dl = MAP_CHUNK_TILE_AT(idx).unk18;
            } else {
                dl = MAP_CHUNK_TILE_AT(idx).unk14;
            }
            gfx = renderEntryListBuildDisplayList(gfx, dl, arg2, arg3, arg4, arg5, idx, flag);
            if (arg5 & 0x10) {
                gSPClearGeometryMode(gfx++, 0xFFFFFFFF);
                gSPSetGeometryMode(gfx++, 0x200004);
                gfx = fogRender(gfx);
                gfx = mapChunkEmitSegmentCommands(gfx, idx);
                if (MAP_CHUNK_TILE_AT(idx).unk30 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)MAP_CHUNK_TILE_AT(idx).unk58));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = (Gfx *)mapChunkEmitLayerDisplayLists(gfx, idx, 1);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gDPPipeSync(gfx++);
                }
                if (MAP_CHUNK_TILE_AT(idx).unk38 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)MAP_CHUNK_TILE_AT(idx).unk58));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = (Gfx *)mapChunkEmitLayerDisplayLists(gfx, idx, 3);
                    gDPPipeSync(gfx++);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
            }
        }
    }
    if (arg5 & 0x10) {
        gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
        gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
        gfx = mapViewDrawPass(gfx, arg1, 2);
        if (D_807FBB64 & 0x1000) {
            gDPPipeSync(gfx++);
            gfx = func_80027034(gfx);
            gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }
        gfx = effectWaterRenderSurfaces(gfx, idx, 1);
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(gfx++);
        gfx = renderDepthSortedTargets(gfx);
    }
    for (i = D_807F6C80 - 1; i >= 0; i--) {
        idx = D_807F6C58[i];
        if (MAP_CHUNK_TILE_AT(idx).unk0 == 1) {
            gDPPipeSync(gfx++);
            gDPSetScissor(gfx++, G_SC_NON_INTERLACE, MAP_CHUNK_TILE_AT(idx).tile.w.unk68, MAP_CHUNK_TILE_AT(idx).tile.w.unk6C, MAP_CHUNK_TILE_AT(idx).tile.w.unk70, MAP_CHUNK_TILE_AT(idx).tile.w.unk74);
            mapSetClipBounds(MAP_CHUNK_TILE_AT(idx).tile.h.unk6A, MAP_CHUNK_TILE_AT(idx).tile.h.unk6E, MAP_CHUNK_TILE_AT(idx).tile.h.unk72, MAP_CHUNK_TILE_AT(idx).tile.h.unk76);
            D_807F6009 = 0xFF;
            if (flag != 0) {
                dl = MAP_CHUNK_TILE_AT(idx).unk20;
            } else {
                dl = MAP_CHUNK_TILE_AT(idx).unk1C;
            }
            gfx = renderEntryListBuildDisplayList(gfx, dl, arg2, arg3, arg4, arg5, idx, flag);
            if (D_807FBB64 & 0x01000000) {
                gfx = billboardRenderQueued(gfx, idx);
            }
        }
    }
    if (arg5 & 0x10) {
        gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
        gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
        gfx = mapViewDrawPass(gfx, arg1, 3);
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(gfx++);
    }
    gDPPipeSync(gfx++);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, gPlayerSlots[gCurrentPlayerIndex].unk270, gPlayerSlots[gCurrentPlayerIndex].unk272, gPlayerSlots[gCurrentPlayerIndex].unk274, gPlayerSlots[gCurrentPlayerIndex].unk276);
    mapSetClipBounds(gPlayerSlots[gCurrentPlayerIndex].unk270, gPlayerSlots[gCurrentPlayerIndex].unk272, gPlayerSlots[gCurrentPlayerIndex].unk274, gPlayerSlots[gCurrentPlayerIndex].unk276);
    D_807F600C = 0;
    gfx = renderEntryListBuildDisplayList(gfx, D_807F5FFC, arg2, arg3, arg4, arg5, -1, 0);
    billboardRenderQueued(gfx, -1);
}

typedef struct {
    /* 0x000 */ u8 pad0[0x5];
    /* 0x005 */ u8 unk5;
    /* 0x006 */ u8 pad6[0x26];
    /* 0x02C */ s32 unk2C;
    /* 0x030 */ s32 unk30;
    /* 0x034 */ s32 unk34;
    /* 0x038 */ s32 unk38;
    /* 0x03C */ u8 pad3C[0x10];
    /* 0x04C */ u8 *unk4C;
    /* 0x050 */ s32 unk50;
    /* 0x054 */ u8 pad54[0x174];
} MapChunkEffect;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3[0x1];
    /* 0x04 */ s32 unk4[4];
    /* 0x14 */ s32 unk14[4];
} MapChunkEffectEntry;


s32 mapChunkEmitLayerDisplayLists(arg0, arg1, arg2)
u32 *arg0;
s32 arg1;
u8 arg2;
{
    MapChunkEffectEntry *entry;
    struct MapCell *node;
    Gfx *gfx;
    s32 i;
    s32 found;

    gfx = (Gfx *)arg0;
    if (arg0 == 0) {} // FAKE: rs
    gDPPipeSync(gfx++);
    if (((MapChunkEffect *)gMapChunks)[arg1].unk5 != 2) {
        switch (arg2) {
        case 0:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk2C));
            break;
        case 1:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk30));
            break;
        case 2:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk34));
            break;
        case 3:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk38));
            break;
        }
    } else {
        for (i = 0; i < ((MapChunkEffect *)gMapChunks)[arg1].unk50; i++) {
            gfx = (Gfx *)((u32)gfx | 0); // FAKE: extra gfx reference (raises its colouring priority above the packet pointers)
            if (((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk4[arg2] == -1) {
                continue;
            }
            found = 0;
            node = (struct MapCell *)D_807F70B0; arg0 = (u32 *)&((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i]; do { // LAYOUT: keeps lh a0 before lw v0 // FAKE: arg0 reuse preserves the entry pointer's parameter precolor
                if (((MapChunkEffectEntry *)arg0)->unk0 == node->unk2) {
                    found = 1;
                } else {
                    node++;
                }
            } while (found == 0);
            if (*(u32 *)&D_807F70B0 == 0) {} // FAKE: integer-typed ghost keeps the bound in t1 without coloring the node pointer load
            if (node->unk18 == 0) {
                continue;
            }
            if ((((MapChunkEffectEntry *)arg0)->unk2 & (1 << arg2)) == 0) {
                continue;
            }
            gSPSegment(gfx++, 6, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk14[arg2]));
            gDPPipeSync(gfx++);
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk4[arg2]));
            gDPPipeSync(gfx++);
        }
    }
    return (s32)gfx;
}

void mapChunkEffectSetFlag(s16 arg0, s16 arg1, u8 arg2, u8 arg3) {
    s32 i = 0;
    MapChunkEffect *slot = (MapChunkEffect *)gMapChunks + arg0;

    for (; i < slot->unk50; i++) {
        if (arg1 == ((MapChunkEffectEntry *)slot->unk4C)[i].unk0) {
            if (arg3 != 0) {
                ((MapChunkEffectEntry *)slot->unk4C)[i].unk2 |= 1 << arg2;
            } else {
                ((MapChunkEffectEntry *)slot->unk4C)[i].unk2 &= ~(1 << arg2);
            }
            return;
        }
    }
}

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
} MapATpSlot;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 pad6[0xA];
} MapATpCand;

extern s32 actorTargetTableContainsId(s32);
void mapChunkIdListAddUniqueLimited(s32);
void mapChunkIdListAddUnique(s16);
s32 mapChunkHitListExcludes(s32);
s32 mapGridPointEmit(s32, f32, f32, f32);
s32 mapGridPointPlaneDistanceWithin(s32, f32, f32, f32, s16);
s32 mapGridQuadClipToFrustum(s32, f32, f32, f32);
void mapPolyProjectToScreenRect(s32, s32 *, s32 *, s32 *, s32 *);
void mapRectIntersect(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);
s32 mapRectOverlapTest(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);

void mapChunkTraversePortals(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    s32 s1;
    s32 poly;
    s32 i;
    s32 spC8;
    s32 spC4;
    s32 spC0;
    s32 spBC;
    s32 spB8;
    s32 spB4;
    s32 spB0;
    s32 spAC;
    s32 spA8;
    s32 spA4;
    s32 spA0;
    s32 sp9C;
    u8 sp9B;
    u8 r;
    s32 sp94;
    s32 found;
    s32 k;

    mapChunkIdListAddUnique(arg0);
    i = 0;
    if (D_807F6C20 > 0) {
        do {
            if ((arg0 == ((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk2) && (mapNodeIdListContains(((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk4, arg1) == 0)) {
                if (((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk9 != 0) {
                    ((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk8 = 1;
                    s1 = i / 2;
                    if (mapChunkHitListExcludes(s1) != 0) {
                        found = mapGridPointEmit(s1, arg6, arg7, arg8);
                        r = found;
                        if (found != 0) {
                            spB0 = arg4;
                            spB8 = arg2;
                            spB4 = arg3;
                            spAC = arg5;
                        } else if (mapGridPointPlaneDistanceWithin(s1, arg6, arg7, arg8, ((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk6) != 0) {
                            sp94 = mapGridQuadClipToFrustum(s1, arg6, arg7, arg8);
                            if (sp94 != 0) {
                                mapPolyProjectToScreenRect(sp94, &spC8, &spC4, &spC0, &spBC);
                                sp9B = mapRectOverlapTest(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC);
                            }
                        } else {
                            sp94 = 0;
                            found = 0;
                            k = 0;
                            while ((found == 0) && (k < D_807F6C10)) {
                                if ((i == ((MapATpCand *)D_807F6C0C)[k].unk2) && (((MapATpCand *)D_807F6C0C)[k].unk0 == *(s16 *)((u8 *)D_807F6C1C + i * 0xA + 4))) {
                                    found = 1;
                                } else {
                                    k++;
                                }
                            }
                            if ((found != 0) && (mapGridPointPlaneDistanceWithin(s1, arg6, arg7, arg8, ((MapATpCand *)((u8 *)D_807F6C0C + k * 0x10))->unk4) != 0)) {
                                poly = mapGridQuadClipToFrustum(s1, arg6, arg7, arg8);
                                if (poly != 0) {
                                    mapPolyProjectToScreenRect(poly, &spC8, &spC4, &spC0, &spBC);
                                    if (mapRectOverlapTest(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC) != 0) {
                                        mapChunkIdListAddUniqueLimited(k);
                                    }
                                }
                            }
                            if (actorTargetTableContainsId(i) != 0) {
                                poly = mapGridQuadClipToFrustum(s1, arg6, arg7, arg8);
                                if (poly != 0) {
                                    mapPolyProjectToScreenRect(poly, &spC8, &spC4, &spC0, &spBC);
                                    if (mapRectOverlapTest(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC) != 0) {
                                        D_807F6C2C[i] = 1;
                                    }
                                }
                            }
                        }
                        if (((sp94 != 0) && (sp9B != 0)) || r) {
                            D_807F6C2C[i] = 1;
                            s1 = ((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk4;
                            if (D_807F7078[s1] != 0) {
                                gMapChunks[s1].unk0 = 1;
                                gMapChunks[s1].unk1 |= 1 << gCurrentPlayerIndex;
                                mapRectIntersect(spB8, spB4, spB0, spAC, gMapChunks[s1].unk68, gMapChunks[s1].unk6C, gMapChunks[s1].unk70, gMapChunks[s1].unk74, &spA8, &spA4, &spA0, &sp9C);
                                gMapChunks[s1].unk68 = spA8;
                                gMapChunks[s1].unk6C = spA4;
                                gMapChunks[s1].unk70 = spA0;
                                gMapChunks[s1].unk74 = sp9C;
                                D_807F6C30[arg1] = arg0;
                                mapChunkTraversePortals(s1, arg1 + 1, spB8, spB4, spB0, spAC, arg6, arg7, arg8);
                            }
                        }
                    }
                }
            }
            i++;
        } while (i < D_807F6C20);
    }
}


s32 mapChunkHitListExcludes(s32 arg0) {
    u8 *p = D_807F7060;

    if (D_807F7070 > 0) {
        do {
            if (arg0 == *p) {
                return 0;
            } else {
                p++;
            }
        } while (p < D_807F7060 + D_807F7070);
    }
    return 1;
}


void mapChunkIdListAddUniqueLimited(s32 arg0) {
    s32 i = 0;

    while (i < D_807F6C08) {
        if (arg0 == D_807F6BF0[i]) {
            return;
        }
        i++;
    }
    if (i == 0xC) {
        return;
    }
    D_807F6BF0[D_807F6C08] = arg0;
    D_807F6C08++;
}


void mapChunkIdListAddUnique(s16 arg0) {
    s32 i = 0;

    while (i < D_807F6C80) {
        if (arg0 == D_807F6C58[i]) {
            return;
        }
        i++;
    }
    D_807F6C58[D_807F6C80] = arg0;
    D_807F6C80++;
}


typedef struct {
    /* 0x00 */ f32 unk0[4];
    /* 0x10 */ f32 unk10[4];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} MapGridQuad;



extern void mapGridPlaneProjectPoint(s32, f32, f32, f32, f32 *, f32 *, f32 *);
extern void mapGridPointBuildVectors(s32, f32, f32, f32, MapGridQuad *);
extern s32 mapGridQuadContainsPoint(u8 *);

s32 mapGridPointEmit(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 h;
    f32 x;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    u8 sp4C[0x28];
    f32 sp48;
    f32 sp44;
    f32 sp40;

    sp40 = (f32)gMapGridTrianglePlanes[arg0].unk10;
    sp44 = (f32)gMapGridTrianglePlanes[arg0].unk8;
    sp48 = (f32)gMapGridTrianglePlanes[arg0].unk0;
    h = (f32)gMapGridTrianglePlanes[arg0].unk18;
    x = (h + (sp48 * arg1 + sp44 * arg2 + sp40 * arg3)) / gMapGridTrianglePlanes[arg0].unk20;
    if (x < 0.0) {
        x = 0.0 - x;
    }
    if (x > 80.0) {
        return 0;
    }
    mapGridPlaneProjectPoint(arg0, arg1, arg2, arg3, &sp7C, &sp78, &sp74);
    mapGridPointBuildVectors(arg0, sp7C, sp78, sp74, (MapGridQuad *)sp4C);
    if (mapGridQuadContainsPoint(sp4C)) {
        return 1;
    }
    return 0;
}

typedef struct {
    f32 x[4];
    f32 y[4];
    f32 px;
    f32 py;
} MapGridQuadView;

#define Q ((MapGridQuadView *)arg0)
s32 mapGridQuadContainsPoint(u8 *arg0) {
    f32 mx;
    f32 my;
    f32 ex;
    f32 ey;
    f32 vx;
    f32 vy;
    f32 dx;
    f32 dy;
    f32 pad;
    f32 cross2;
    s32 i;

    mx = (Q->x[0] + Q->x[2]) * 0.5;
    my = (Q->y[0] + Q->y[2]) * 0.5;
    for (i = 0; i != 4; i++) {
        switch (i) {
        case 0:
            vy = Q->y[0];
            vx = Q->x[0];
            ex = Q->x[1] - vx;
            ey = Q->y[1] - vy;
            if (i && i) {} // FAKE: steers f32 web coloring/ring (dx f12, dy f14)
            break;
        case 1:
            vx = Q->x[1];
            vy = Q->y[1];
            ey = Q->y[2] - vy;
            ex = Q->x[2] - vx;
            break;
        case 2:
            vy = Q->y[2];
            vx = Q->x[2];
            ex = Q->x[3] - vx;
            ey = Q->y[3] - vy;
            if (vx * 2.0f) {} // FAKE: steers f32 web coloring/ring (dx f12, dy f14)
            break;
        case 3:
            vx = Q->x[3];
            vy = Q->y[3];
            ex = Q->x[0] - vx;
            ey = Q->y[0] - vy;
            if (!i) {} // FAKE: steers f32 web coloring/ring (dx f12, dy f14)
            break;
        }
        if (i == 0) {} // FAKE: steers f32 web coloring/ring (dx f12, dy f14)
        dx = Q->px - vx;
        if (dx * 2.0f) {} // FAKE: steers f32 web coloring/ring (dx f12, dy f14)
        dy = Q->py - vy;
        if (dx * ey - dy * ex != 0.0) {
            cross2 = (mx - vx) * ey - (my - vy) * ex;
            if (dy < 0.0f) {} // FAKE: steers f32 web coloring/ring (dx f12, dy f14)
            if (dx * ey - dy * ex > 0.0) {
                if (dx < 0.0f) {} // FAKE: steers f32 web coloring/ring (dx f12, dy f14)
                if (cross2 <= 0.0) {
                    return 0;
                }
            } else if (cross2 >= 0.0) {
                return 0;
            }
        }
    }
    return 1;
}



void mapGridPointBuildVectors(s32 arg0, f32 arg1, f32 arg2, f32 arg3, MapGridQuad *arg4) {
    s32 k;

    switch (gMapGridTrianglePlanes[arg0].unk28) {
    case 0:
        arg4->unk20 = arg1;
        arg4->unk24 = arg2;
        for (k = 0; k < 4; k++) {
            arg4->unk0[k] = D_807F6C14[arg0].unk0[k];
            arg4->unk10[k] = D_807F6C14[arg0].unk10[k];
        }
        break;
    case 1:
        arg4->unk20 = arg1;
        arg4->unk24 = arg3;
        for (k = 0; k < 4; k++) {
            arg4->unk0[k] = D_807F6C14[arg0].unk0[k];
            arg4->unk10[k] = D_807F6C14[arg0].unk20[k];
        }
        break;
    case 2:
        arg4->unk20 = arg2;
        arg4->unk24 = arg3;
        for (k = 0; k < 4; k++) {
            arg4->unk0[k] = D_807F6C14[arg0].unk10[k];
            arg4->unk10[k] = D_807F6C14[arg0].unk20[k];
        }
        break;
    }
}

void mapGridPlaneProjectPoint(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    f32 n10;
    f32 t;
    f32 n0;
    f32 n8;
    f32 a;
    a = (f32)(-gMapGridTrianglePlanes[arg0].unk18);
    n8 = (f32)gMapGridTrianglePlanes[arg0].unk8;
    n0 = (f32)gMapGridTrianglePlanes[arg0].unk0;
    n10 = (f32)gMapGridTrianglePlanes[arg0].unk10;
    t = (a - (n10 * arg3 + (n0 * arg1 + n8 * arg2))) / gMapGridTrianglePlanes[arg0].unk24;
    *arg4 = (f32)gMapGridTrianglePlanes[arg0].unk0 * t + arg1;
    *arg5 = (f32)gMapGridTrianglePlanes[arg0].unk8 * t + arg2;
    *arg6 = (f32)gMapGridTrianglePlanes[arg0].unk10 * t + arg3;
}

void mapRectIntersect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 *arg8, s32 *arg9, s32 *arg10, s32 *arg11) {
    if ((arg0 == arg2) || (arg1 == arg3)) {
        *arg8 = arg4;
        *arg9 = arg5;
        *arg10 = arg6;
        *arg11 = arg7;
        return;
    }
    if ((arg4 == arg6) || (arg5 == arg7)) {
        *arg8 = arg0;
        *arg9 = arg1;
        *arg10 = arg2;
        *arg11 = arg3;
        return;
    }
    *arg8 = (arg0 < arg4) ? arg0 : arg4;
    *arg9 = (arg1 < arg5) ? arg1 : arg5;
    *arg10 = (arg6 < arg2) ? arg2 : arg6;
    *arg11 = (arg7 < arg3) ? arg3 : arg7;
}

s32 mapRectOverlapTest(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 *arg8, s32 *arg9, s32 *arg10, s32 *arg11) {
    if (arg0 == -1) {
        return 0;
    }
    if (arg4 == -1) {
        return 0;
    }
    *arg8 = (arg4 < arg0) ? arg0 : arg4;
    *arg9 = (arg5 < arg1) ? arg1 : arg5;
    *arg10 = (arg2 < arg6) ? arg2 : arg6;
    *arg11 = (arg3 < arg7) ? arg3 : arg7;
    if (!(*arg8 < *arg10)) {
        return 0;
    }
    if (!(*arg9 < *arg11)) {
        return 0;
    }
    return 1;
}

s32 mapGridPointPlaneDistanceWithin(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4) {
    f32 v;

    v = ((f32)gMapGridTrianglePlanes[arg0].unk18 + ((f32)gMapGridTrianglePlanes[arg0].unk0 * arg1 + (f32)gMapGridTrianglePlanes[arg0].unk8 * arg2 + (f32)gMapGridTrianglePlanes[arg0].unk10 * arg3)) / gMapGridTrianglePlanes[arg0].unk20;
    if (v < 0.0) {
        v = 0.0 - v;
    }
    return (v <= (f32)arg4) & 0xFF;
}

extern f32 D_807F6E68[];
extern f32 D_807F6F58[];
extern f32 D_807F6D78[];

void mapPolyClipToFrustumPlane(f32 *, f32 *, s32, s32 *, s32);

s32 mapGridQuadClipToFrustum(s32 arg0, f32 arg1, f32 arg2, f32 arg3)
{
    s32 k;
    s32 n2;
    s32 n1;

    n1 = 0;
    n2 = 0;
    for (k = 0; k < 4; k++) {
        D_807F6C88[k * 3] = D_807F6C14[arg0].unk0[k];
        D_807F6C88[k * 3 + 1] = D_807F6C14[arg0].unk10[k];
        D_807F6C88[k * 3 + 2] = D_807F6C14[arg0].unk20[k];
    }
    mapPolyClipToFrustumPlane(D_807F6C88, D_807F6E68, 4, &n2, 0);
    if (n2 == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(D_807F6E68, D_807F6F58, n2, &n1, 1);
    if (n1 == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(D_807F6F58, D_807F6E68, n1, &n2, 2);
    if (n2 == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(D_807F6E68, D_807F6F58, n2, &n1, 3);
    if (n1 == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(D_807F6F58, D_807F6D78, n1, &n2, 4);
    if (n2 < 3) {
        n2 = 0;
    }
    return n2;
}

typedef struct MapPlane {
    /* 0x00 */ f64 unk0;
    /* 0x08 */ f64 unk8;
    /* 0x10 */ f64 unk10;
    /* 0x18 */ f64 unk18;
    /* 0x20 */ f64 unk20;
    /* 0x28 */ f64 unk28;
    /* 0x30 */ f64 unk30;
    /* 0x38 */ f64 unk38;
} MapPlane;

typedef struct MapVec3 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} MapVec3;

void mapFrustumPlaneIntersectEdge(f32 *, f32 *, s32, f32 *);

void mapPolyClipToFrustumPlane(f32 *arg0, f32 *arg1, s32 arg2, s32 *arg3, s32 arg4) {
    f32 sp7C[3];
    MapPlane *plane;
    MapVec3 *prev;
    MapVec3 *cur;
    s32 n;
    s32 i;
    f64 y;
    f64 z;

    cur = (MapVec3 *)arg0; // FAKE: gives cur an earlier candidate index than arg4 (s7/s8 colouring)
    n = 0;
    prev = arg2 - 1 + (MapVec3 *)arg0;
    plane = (MapPlane *)(D_807F5E68 + (arg4 << 6));
    for (i = 0; i < arg2; i++, prev = cur) {
        cur = i + (MapVec3 *)arg0;
        y = plane->unk38 + (((plane->unk20 * cur->x) + (plane->unk28 * cur->y)) + (plane->unk30 * cur->z));
        z = plane->unk38 + (((plane->unk20 * prev->x) + (plane->unk28 * prev->y)) + (plane->unk30 * prev->z));
        if (y >= 0.0) {
            if (z >= 0.0) {
                memcpy(n + (MapVec3 *)arg1, cur, 0xC);
                n++;
            } else {
                mapFrustumPlaneIntersectEdge((f32 *)prev, (f32 *)cur, arg4, sp7C);
                memcpy(n++ + (MapVec3 *)arg1, sp7C, 0xC);
                memcpy(n++ + (MapVec3 *)arg1, cur, 0xC);
            }
        } else if (z >= 0.0) {
            mapFrustumPlaneIntersectEdge((f32 *)prev, (f32 *)cur, arg4, sp7C);
            memcpy(n++ + (MapVec3 *)arg1, sp7C, 0xC);
        }
    }
    *arg3 = n;
}

void mapFrustumPlaneIntersectEdge(f32 *arg0, f32 *arg1, s32 arg2, f32 *arg3) {
    f32 pad[3];
    f64 *m;
    f32 x1;
    f64 s;
    f64 n;

    m = (f64 *)(D_807F5E68 + (arg2 << 6));
    n = (((m[4] * arg0[0]) + (m[5] * arg0[1])) + (m[6] * arg0[2])) + m[7];
    x1 = arg1[0];
    s = n / (((m[4] * (arg0[0] - x1)) + (m[5] * (arg0[1] - arg1[1]))) + (m[6] * (arg0[2] - arg1[2])));
    arg3[0] = arg0[0] + ((x1 - arg0[0]) * s);
    arg3[1] = arg0[1] + ((arg1[1] - arg0[1]) * s);
    arg3[2] = arg0[2] + ((arg1[2] - arg0[2]) * s);
}

typedef struct MapPolyVertex {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
} MapPolyVertex;

s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

void mapPolyProjectToScreenRect(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    f32 sp7C;
    f32 sp78;
    s16 x;
    s16 y;
    s32 i;
    u8 flag;

    *arg1 = gPlayerSlots[gCurrentPlayerIndex].unk274;
    *arg2 = gPlayerSlots[gCurrentPlayerIndex].unk276;
    *arg3 = gPlayerSlots[gCurrentPlayerIndex].unk270;
    *arg4 = gPlayerSlots[gCurrentPlayerIndex].unk272;
    flag = 0;
    for (i = 0; i < arg0; i++) {
        flag |= camProjectToScreen(((MapPolyVertex *)D_807F6D78)[i].unk0, ((MapPolyVertex *)D_807F6D78)[i].unk4, ((MapPolyVertex *)D_807F6D78)[i].unk8, &sp7C, &sp78, 0, 1.0f, gCurrentPlayerIndex); x = (s16)sp7C; y = (s16)sp78; // FAKE: same-line statements steer sra scheduling
        if (x < gPlayerSlots[gCurrentPlayerIndex].unk270) {
            x = gPlayerSlots[gCurrentPlayerIndex].unk270;
        }
        if (y < gPlayerSlots[gCurrentPlayerIndex].unk272) {
            y = gPlayerSlots[gCurrentPlayerIndex].unk272;
        }
        if (gPlayerSlots[gCurrentPlayerIndex].unk274 < x) {
            x = gPlayerSlots[gCurrentPlayerIndex].unk274;
        }
        if (gPlayerSlots[gCurrentPlayerIndex].unk276 < y) {
            y = gPlayerSlots[gCurrentPlayerIndex].unk276;
        }
        if (x < *arg1) {
            *arg1 = x;
        }
        if (y < *arg2) {
            *arg2 = y;
        }
        if (*arg3 < x) {
            *arg3 = x;
        }
        if (*arg4 < y) {
            *arg4 = y;
        }
    }
    if ((*arg1 == *arg3) || (*arg2 == *arg4) || (flag != 0)) {
        *arg1 = -1;
        *arg2 = -1;
        *arg3 = -1;
        *arg4 = -1;
    }
}

void mapNodeAssetParse(u8 *);

void mapLoadNodeAsset(s32 arg0) {
    u8 *p;

    p = (u8 *)assetLoad(0x14, arg0, 1, 1);
    mapNodeAssetParse(p);
    if (p != NULL) {
        assetFreeBuffer(p, 0xBED, 0x22);
    }
}

typedef struct MapNodeData {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14[0x20];
    /* 0x34 */ s8 unk34;
    /* 0x35 */ u8 pad35;
    /* 0x36 */ u8 unk36[0x20];
    /* 0x56 */ s8 unk56;
    /* 0x57 */ u8 pad57;
    /* 0x58 */ u8 unk58[0x10];
    /* 0x68 */ s8 unk68;
} MapNodeData;

#define MapNodeSlot (*(MapNodeData **)slot)
void mapNodeAssetParse(u8 *arg0) {
    s32 *w;
    s32 *end;
    s16 n;
    s32 i;
    s16 idx;
    u8 *p;
    s32 slot;
    void *t;

    w = (s32 *)(&D_807F70B4 + 1); end = (s32 *)&D_807F7138; // FAKE: same-line statements steer lui/addiu scheduling; the neighbour-symbol spelling keeps this address a separate web from the loop's table base
    do {
        *w++ = 0;
    } while (w < end);
    if (arg0 == NULL) {
        return;
    }
    n = *(s16 *)arg0;
    p = arg0 + 2;
    for (i = 0; i < n; i++) {
        idx = *(s16 *)p;
        p += 2;
        t = heapAlloc(0x6C);
        slot = (s32)&((MapNodeData **)D_807F70B8)[idx];
        MapNodeSlot = t;
        MapNodeSlot->unk10 = 0x7FFF;
        MapNodeSlot->unk12 = -0x8000;
        MapNodeSlot->unk8 = 0;
        MapNodeSlot->unk4 = *(s16 *)p;
        p += 2;
        MapNodeSlot->unk0 = heapAlloc((u32)MapNodeSlot->unk4 * 6);
        memcpy(MapNodeSlot->unk0, p, (u32)MapNodeSlot->unk4 * 6);
        p += ((u32)MapNodeSlot->unk4 * 6 / 2) * 2;
        MapNodeSlot->unkE = *(s16 *)p;
        MapNodeSlot->unk34 = (s8)*(s16 *)(p + 2);
        p += 4;
        memcpy(MapNodeSlot->unk14, p, 0x20);
        MapNodeSlot->unk56 = (s8)*(s16 *)(p + 0x20);
        p += 0x22;
        memcpy(MapNodeSlot->unk36, p, 0x20);
        MapNodeSlot->unk68 = (s8)*(s16 *)(p + 0x20);
        p += 0x22;
        memcpy(MapNodeSlot->unk58, p, 0x10);
        p += 0x10;
        mapFaceBuildTriangleFan(idx);
    }
}
#undef MapNodeSlot

extern s16 D_807F7358;
extern s16 D_807F735A;
extern s16 D_807F735C;
extern s16 D_807F735E;


s16 mapObjectCollectIdsByType(arg0, arg1, arg2)
s8 arg0;
u8 *arg1;
s16 arg2;
{
    s16 i;
    s16 n;
    s32 off;

    n = 0;
    if (arg0 == -1) {
        return 0;
    }
    for (i = 0; i < D_807F6C20 && n < arg2; ) {
        off = i * 10;
        if (*(s16 *)(D_807F6C1C + off + 2) == arg0) {
            arg1[n++] = *(s16 *)(D_807F6C1C + off + 4);
        }
        i++;
    }
    return n;
}

typedef struct MapSearchEntry {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ s16 unk4;
    /* 0x006 */ s16 unk6;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ u8 padA[0x2];
    /* 0x00C */ s32 unkC;
    /* 0x010 */ u8 unk10;
    /* 0x011 */ u8 unk11;
    /* 0x012 */ u8 pad12[0x2];
} MapSearchEntry;

extern u8 D_807F72A0;
extern u8 D_807F72B4;
extern MapSearchEntry D_807F72B8[];

void mapSearchTableReset(void) {
    s32 i;

    D_807F72A0 = 0;
    for (i = 0, D_807F72B4 = 0; i < 8; i++) {
        D_807F72B8[i].unk10 = 0;
    }
}

extern s32 D_807F7290;
extern s32 gFrameCounter;

void mapSearchTableAddProbe();

void mapSearchTableAddProbe(arg0, arg1, arg2, arg3)
s32 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
{
    s32 i;
    s32 found;
    MapSearchEntry *p;

    found = 0;
    i = 0;
    while ((i < 10) && !found) {
        if (((MapSearchEntry *)&D_807F7290)[i].unk10 != 0) {
            i++;
        } else {
            found = 1;
        }
    }
    if (found) {
        p = &((MapSearchEntry *)&D_807F7290)[i];
        p->unk10 = 1;
        p->unkC = gFrameCounter;
        p->unk0 = arg0;
        p->unk4 = arg1;
        p->unk6 = arg2;
        p->unk8 = arg3;
        if (found) {} // FAKE: keeps found live past the stores (p in a0, not v0)
    }
}

extern s32 zbufferReadDepth(s16, s16);
extern s32 zbufferDepthToDistance(s32);

void mapSearchTableUpdateVisibility(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (((MapSearchEntry *)&D_807F7290)[i].unk10 != 0) {
            if (gFrameCounter == ((MapSearchEntry *)&D_807F7290)[i].unkC) {
                if ((f32)zbufferDepthToDistance((s16)zbufferReadDepth(((MapSearchEntry *)&D_807F7290)[i].unk4, ((MapSearchEntry *)&D_807F7290)[i].unk6)) <= (f32)((MapSearchEntry *)&D_807F7290)[i].unk8) {
                    ((MapSearchEntry *)&D_807F7290)[i].unk11 = 1;
                } else {
                    ((MapSearchEntry *)&D_807F7290)[i].unk11 = 0;
                }
            }
        }
        if ((u32)(gFrameCounter - ((MapSearchEntry *)&D_807F7290)[i].unkC) >= 3) {
            ((MapSearchEntry *)&D_807F7290)[i].unk10 = 0;
        }
    }
}

extern u8 D_807F72A1;
extern s32 D_807F72A4;
extern u8 D_807F72B5;

u8 mapSearchTableGetValue(s32 arg0) {
    s32 i;

    if (arg0 == D_807F7290) { return D_807F72A1; } if (arg0 == D_807F72A4) { return D_807F72B5; }
    for (i = 0; i < 8; i++) {
        if (arg0 == D_807F72B8[i].unk0) {
            return D_807F72B8[i].unk11;
        }
    }
    return 0;
}


void mapSetClipBounds(arg0, arg1, arg2, arg3)
s16 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
{
    D_807F7358 = arg0;
    D_807F735A = arg1;
    D_807F735C = arg2;
    D_807F735E = arg3;
}

typedef struct MapPlayerPosition {
    /* 0x000 */ u8 pad0[0x21C];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
} MapPlayerPosition;

s32 mapPointOutsideClipBounds(f32 arg0, f32 arg1, f32 arg2, u8 arg3, u8 arg4) {
    f32 sp44;
    f32 sp40;
    s16 x;
    s16 z;
    s16 x0;
    s16 x1;
    s16 z0;
    s16 z1;
    f32 d;
    f32 t;

    camProjectToScreen(arg0, arg1, arg2, &sp44, &sp40, 0, 1.0f, gCurrentPlayerIndex);
    x = (s16)sp44;
    z = (s16)sp40;
    d = sqrtf((((f32)arg2 - ((MapPlayerPosition *)&gPlayerSlots[gCurrentPlayerIndex])->unk224) * (arg2 - ((MapPlayerPosition *)&gPlayerSlots[gCurrentPlayerIndex])->unk224))
            + (((arg0 - ((MapPlayerPosition *)&gPlayerSlots[gCurrentPlayerIndex])->unk21C) * (arg0 - ((MapPlayerPosition *)&gPlayerSlots[gCurrentPlayerIndex])->unk21C))
            + ((arg1 - ((MapPlayerPosition *)&gPlayerSlots[gCurrentPlayerIndex])->unk220) * (arg1 - ((MapPlayerPosition *)&gPlayerSlots[gCurrentPlayerIndex])->unk220))));  // FAKE: (f32)arg2 cast shifts the t5-t7 temp rotation
    if (d < 90.0f) {
        return 0;
    }
    x0 = 20;
    x1 = 20;
    z0 = 0;
    t = (d - 60.0f) / 120.0f;
    if (d >= 180.0f) {
        z1 = 50;
    } else if (t > 0.0) {
        x0 = -60.0f * t + 80.0f;
        x1 = -60.0f * t + 80.0f;
        z0 = -130.0f * t + 130.0f;
        z1 = -80.0f * t + 130.0f;
    } else {
        x0 = 80;
        x1 = 80;
        z0 = 130;
        z1 = 130;
    }
    if ((x < D_807F7358 - x0 - arg3) || (D_807F735C + x1 + arg3 < x)
        || (z < D_807F735A - z0 - arg4) || (D_807F735E + z1 + arg4 < z)) {
        return 1;
    }
    return 0;
}

