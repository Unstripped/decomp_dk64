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
extern s32 D_807F6C28;
extern MapChunk *D_807F6C18;
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
void *func_80610FE8(s32);

void mapChunkAllocLists(MapHeader *arg0) {
    s32 temp;
    s32 count;
    s32 size;

    temp = D_807F6C28 = *(s32 *)(arg0->unk64 + (u8 *)arg0);
    if (temp >= 2) {
        count = temp & 0xFF;
    } else {
        count = 1;
    }
    size = count * 4;
    D_8076A0B4 = (s32)func_80610FE8(size);
    D_8076A0B8 = (s32)func_80610FE8(size);
    D_8076A0BC = (s32)func_80610FE8(size);
    D_8076A0C0 = (s32)func_80610FE8(size);
    D_8076A0C4 = (s32)func_80610FE8(size);
    D_8076A0C8 = (s32)func_80610FE8(size);
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
extern MapGridPoint *D_807F6C24;
extern struct MapCell *D_807F70B0;
extern struct MapBox *D_807F70B4;

void lightSetTargetColor(f32, f32, f32, s16);
void lightCopyTargetColors(s16);
void func_80651904(s32, s32, void *, s32 *, s32, s32);
void func_80651C2C(s32, void *);

#ifdef NON_MATCHING
void func_80650ECC(MapData *arg0) {
    u8 *q;
    u8 *p;
    s32 base;
    u8 buf[0xE54];
    s32 count;
    s32 i;
    s32 j;
    s32 total;
    s32 val;
    s32 off;
    s32 colOff;
    u8 *w;
    u8 *w4;

    D_807F70AC = 0;
    D_807F713A = 0;
    D_807F70AB = 0;
    if (D_807F6C28 != 0) {
        D_807F7138 = arg0->unkC;
        D_807F7074 = func_80610FE8(0x40);
        guScale(D_807F7074, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
        off = arg0->unk58;
        D_807F70AC = *(s32 *)((u8 *)arg0 + off);
        D_807F70B0 = (struct MapCell *)((u8 *)arg0 + off + 4);
        off = arg0->unk5C;
        D_807F70B4 = (struct MapBox *)((u8 *)arg0 + off + 4);
        off = arg0->unk60;
        D_807F6C14 = (MapGridVectors *)((u8 *)arg0 + off);
        base = arg0->unk34;
        w = (u8 *)arg0 + arg0->unk64;
        p = (u8 *)arg0 + arg0->unk68;
        off = arg0->unk6C;
        D_807F6C20 = *(s32 *)((u8 *)arg0 + off);
        D_807F6C1C = (u8 *)arg0 + off + 4;
        D_807F6C2C = func_80610FE8(D_807F6C20);
        off = arg0->unk70;
        D_807F6C10 = *(s32 *)((u8 *)arg0 + off);
        D_807F6C0C = (u8 *)arg0 + off + 4;
        for (i = 0; i < D_807F6C10; i++) {
            if (((MapRelocEntry *)D_807F6C0C)[i].unk8 != -1) {
                ((MapRelocEntry *)D_807F6C0C)[i].unk8 += (s32)arg0 + base;
            }
            if (((MapRelocEntry *)D_807F6C0C)[i].unkC != -1) {
                ((MapRelocEntry *)D_807F6C0C)[i].unkC += (s32)arg0 + base;
            }
        }
        D_807F6C18 = func_80610FE8(D_807F6C28 * 0x1C8);
        w4 = w + 4;
        i = 0;
        if (D_807F6C28 > 0) {
            colOff = 0;
            do {
                count = 0;
                D_807F6C18[i].unk0 = 0;
                D_807F6C18[i].unk1 = 0;
                D_807F6C18[i].unk14 = 0;
                D_807F6C18[i].unk1C = 0;
                D_807F6C18[i].unk24 = 0;
                D_807F6C18[i].unk7 = 4;
                D_807F6C18[i].unk54 = *(s32 *)(p + 0x2C) + D_807F5DE8;
                D_807F6C18[i].unk58 = D_807F6C18[i].unk54;
                lightSetTargetColor(p[0] / 255.0, p[1] / 255.0, p[2] / 255.0, (s16)i);
                lightCopyTargetColors((s16)i);
                D_807F6C18[i].unk6 = p[3];
                p += 0xC;
                D_807F6C18[i].unk5 = p[-8];
                D_807F6C18[i].unk3 = *(s32 *)(p - 4);
                val = *(s32 *)p;
                if (val != -1) {
                    val += (s32)arg0 + base;
                    *(s32 *)p = val;
                }
                p += 8;
                D_807F6C18[i].unk2C = val;
                D_807F6C18[i].unk3C = *(s32 *)(p - 4);
                total = D_807F6C18[i].unk3C;
                if (D_807F6C18[i].unk5 == 2) {
                    D_807F713A = 1;
                    func_80651904(D_807F6C18[i].unk2C, D_807F6C18[i].unk3C, buf, &count, 0, i);
                }
                val = *(s32 *)p;
                if (val != -1) {
                    val += (s32)arg0 + base;
                    *(s32 *)p = val;
                }
                p += 8;
                D_807F6C18[i].unk30 = val;
                D_807F6C18[i].unk40 = *(s32 *)(p - 4);
                total += D_807F6C18[i].unk40;
                if (D_807F6C18[i].unk5 == 2) {
                    func_80651904(D_807F6C18[i].unk30, D_807F6C18[i].unk40, buf, &count, 1, i);
                }
                val = *(s32 *)p;
                if (val != -1) {
                    val += (s32)arg0 + base;
                    *(s32 *)p = val;
                }
                p += 8;
                D_807F6C18[i].unk34 = val;
                D_807F6C18[i].unk44 = *(s32 *)(p - 4);
                total += D_807F6C18[i].unk44;
                if (D_807F6C18[i].unk5 == 2) {
                    func_80651904(D_807F6C18[i].unk34, D_807F6C18[i].unk44, buf, &count, 2, i);
                }
                val = *(s32 *)p;
                if (val != -1) {
                    val += (s32)arg0 + base;
                    *(s32 *)p = val;
                }
                p += 8;
                D_807F6C18[i].unk38 = val;
                D_807F6C18[i].unk48 = *(s32 *)(p - 4);
                total += D_807F6C18[i].unk48;
                D_807F6C18[i].unk8 = D_807F6C18[i].unk2C + ((total >> 3) << 3);
                D_807F6C18[i].unkC = D_807F6C18[i].unk2C;
                D_807F6C18[i].unk10 = D_807F6C18[i].unk8;
                if (D_807F6C18[i].unk5 == 2) {
                    func_80651904(D_807F6C18[i].unk38, D_807F6C18[i].unk48, buf, &count, 3, i);
                }
                D_807F6C18[i].unk5C = *(s32 *)(p + 4);
                p += 8;
                D_807F6C18[i].unk60 = 0;
                D_807F6C18[i].unk64 = 0;
                D_807F6C18[i].unk78 = *(s32 *)(w4 + colOff) + (s32)w;
                D_807F6C18[i].unk7C = *(s32 *)(w4 + colOff + 0xC) + (s32)w;
                D_807F6C18[i].unk80 = *(s16 *)(w4 + colOff + 4);
                D_807F6C18[i].unk82 = *(s16 *)(w4 + colOff + 6);
                D_807F6C18[i].unk84 = *(s16 *)(w4 + colOff + 8);
                D_807F6C18[i].unk86 = *(s16 *)(w4 + colOff + 0xA);
                D_807F6C18[i].unk28 = -1;
                if (count != 0) {
                    D_807F6C18[i].unk4C = func_80610FE8(count * 0x24);
                    memcpy(D_807F6C18[i].unk4C, buf, count * 0x24);
                    j = 0;
                    for (j = 0; j < count; j++) {
                        ((u8 *)D_807F6C18[i].unk4C)[j * 0x24 + 2] = 0xFF;
                    }
                }
                D_807F6C18[i].unk50 = count;
                colOff += 0xC;
                i++;
            } while (i < D_807F6C28);
        }
        D_807F6C24 = func_80610FE8(D_807F6C20 / 2 * 0x30);
        for (i = 0; i < D_807F6C20 / 2; i++) {
            func_80651C2C(i, (u8 *)D_807F6C24 + i * 0x30);
        }
        D_807F7079 = 1;
        D_807F7078[0] = 1;
        q = D_807F707A;
        do {
            *q++ = 1;
            *q++ = 1;
            *q++ = 1;
            *q++ = 1;
        } while (q != &D_807F70AA);
        D_807F70AA = 0;
    } else {
        D_807F6C18 = NULL;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80650ECC.s")
#endif

#ifdef NON_MATCHING
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

void func_80651708(s32 arg0) {
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
        var_v1->unk8 = func_80610FE8(var_a1 * 0x12);
        var_v1->unkC = var_a1;
        if (var_v1->unk4 >= 3) {
            var_a3 = 1;
            var_a2 = 2;
            var_v0 = 0x24;
            var_a1 = 0xC;
            do {
                temp_lo = var_a3 * 6;
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
                var_v0 += 0x12;
                *(s16 *)((var_v1->unk8 + var_v0) - 0x14) = *(s16 *)(var_v1->unk0 + var_a1 + 4);
                var_a1 += 6;
            } while (var_a2 < var_v1->unk4);
        }
    }
    var_v1->unk12 = -0x8000;
    var_v1->unk10 = 0x7FFF;
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651708.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651904.s")

s32 mapChunkIsInUse(s16 arg0) {
    s32 var_v0;
    s32 var_v1;

    var_v1 = (arg0 + 1) != 0;
    if (var_v1 != 0) {
        if (D_807F6C18[arg0].unk3 != 0) {
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651C2C.s")

struct MapCell;

void mapChunkResetFlags(void) {
    s32 i;
    s32 j;

    for (i = 0; i < D_807F6C28; i++) {
        D_807F6C18[i].unk1 = 0;
        D_807F6C18[i].unk2 = 1;
        D_807F6C18[i].unk4 = 0;
    }
    for (j = 0; j < D_807F70AC; j++) {
        ((u8 *)D_807F70B0)[j * 0x1C + 0x19] = 0;
    }
}

void mapChunkClearBounds(void) {
    s32 i;

    for (i = 0; i < D_807F6C28; i++) {
        D_807F6C18[i].unk0 = 0;
        D_807F6C18[i].unk68 = 0;
        D_807F6C18[i].unk6C = 0;
        D_807F6C18[i].unk70 = 0;
        D_807F6C18[i].unk74 = 0;
    }
    for (i = 0; i < D_807F6C20; i++) {
        D_807F6C1C[i * 0xA + 8] = 0;
        D_807F6C2C[i] = 0;
    }
}

s32 mapChunkContainsPoint(s16 arg0, s16 arg1, s16 arg2) {
    MapChunk *entry;

    entry = (MapChunk *)((s32)D_807F6C18 + arg2 * 0x1C8);
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

s32 func_806303C4(s32, s32, s32, f32, f32, f32, s32, s32, s32, s32, s32);
s32 func_80630324(s32, s32);
s16 func_806531B8(f32, f32, f32, s32);

void mapChunkUpdateEntryNode(MapActorEntry *arg0) {
    s32 temp_v1;
    s32 *sp40;
    s16 *level;

    arg0->unk20 = func_806531B8(arg0->unk4, arg0->unk8, arg0->unkC, arg0->unk20);
    temp_v1 = func_80630324(arg0->unk24, arg0->unk0) & 0xFF;
    if (arg0->unk24 == 0) {
        *(s16 *)(arg0->unk0 + 0x12C) = arg0->unk20;
    }
    level = &arg0->unk20;
    switch (temp_v1) {
    case 0:
        sp40 = (s32 *)((u8 *)D_807F6C18 + *level * 0x1C8 + 0x14);
        break;
    case 1:
        sp40 = (s32 *)((u8 *)D_807F6C18 + *level * 0x1C8 + 0x1C);
        break;
    }
    *sp40 = func_806303C4(*sp40, arg0->unk24, arg0->unk0, arg0->unk4, arg0->unk8, arg0->unkC, arg0->unk1C, arg0->unk1E, arg0->unk22, *level, 0);
}

#ifdef NON_MATCHING
void func_806307CC(s32, s32, s32, s32, u8 *);

void func_806524A0(s32 arg0, u8 arg1) {
    u8 flag;
    s32 i;

    flag = 0;
    for (i = 0; i < D_807F6C28 && !flag; i++) {
        func_806307CC(D_807F6C18[i].unk14, arg0, 0, arg1, &flag);
        if (!flag) {
            func_806307CC(D_807F6C18[i].unk1C, arg0, 0, arg1, &flag);
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806524A0.s")
#endif

s32 func_80630588(s32, s32, s32, u8 *);

u8 mapChunkPurgeNodeList(s32 arg0, s16 *arg1, u8 arg2) {
    u8 flag;
    s32 i;

    flag = 0;
    for (i = 0; i < D_807F6C28 && (!flag || arg2); i++) {
        D_807F6C18[i].unk14 = func_80630588(D_807F6C18[i].unk14, arg0, 0, &flag);
        if (flag) {
            *arg1 = i;
        }
        if (!flag || arg2) {
            D_807F6C18[i].unk1C = func_80630588(D_807F6C18[i].unk1C, arg0, 0, &flag);
            if (flag) {
                *arg1 = i;
            }
        }
    }
    return flag;
}

extern s32 D_807F6C80;
extern s16 D_807F6C58[];
struct MapCell;
struct MapBox;
extern u8 D_807F7140;

void func_806307AC(s32);
s32 func_8063070C(s32);
s32 func_80630890(s32, f32, f32, f32, void *);
void func_806323C0(s32);
s32 func_8063A38C(s32, s32, f32, f32, f32);
void func_8063B4C0(void *, s32);
s32 mapNodeBoxContainsPoint(void *, f32, f32);
s32 func_80653804(void *, f32, f32);
void func_80652FDC(f32, f32, f32, s16, s16, s16 *);
s32 func_806533C4(f32, f32, f32);
s32 mapChunkFindNodeAtPoint(f32, f32, f32, s16, u8 *, f32 *);

void mapChunkClearNodeFlags(u8 arg0) {
    s32 i;

    i = 0;
    if (D_807F6C28 > 0) {
        do {
            if ((D_807F6C18[i].unk0 == 1) || arg0) {
                func_806307AC(D_807F6C18[i].unk14);
                func_806307AC(D_807F6C18[i].unk1C);
            }
            i += 1;
        } while (i < D_807F6C28);
    }
}

void mapChunkFreeNodeLists(u8 arg0) {
    s32 i;

    i = 0;
    if (D_807F6C28 > 0) {
        do {
            if ((D_807F6C18[i].unk0 == 1) || arg0) {
                D_807F6C18[i].unk14 = func_8063070C(D_807F6C18[i].unk14);
                D_807F6C18[i].unk1C = func_8063070C(D_807F6C18[i].unk1C);
            }
            i += 1;
        } while (i < D_807F6C28);
    }
}

void mapChunkRebuildNodeLists(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    s32 var_s3;
    s32 var_s1;

    var_s3 = 0;
    if (D_807F6C28 > 0) {
        var_s1 = 0;
        do {
            if (D_807F6C18[var_s1].unk0 == 1 || arg3) {
                D_807F6C18[var_s1].unk14 = func_80630890(D_807F6C18[var_s1].unk14, arg0, arg1, arg2, (void *)((u8 *)&D_807F6C18[var_s1] + 0x18));
                D_807F6C18[var_s1].unk1C = func_80630890(D_807F6C18[var_s1].unk1C, arg0, arg1, arg2, (void *)((u8 *)&D_807F6C18[var_s1] + 0x20));
            }
            var_s3 += 1;
            var_s1 += 1;
        } while (var_s3 < D_807F6C28);
    }
}

void mapChunkResolveNodeAssets(void) {
    s32 i;

    i = 0;
    if (D_807F6C28 > 0) {
        do {
            func_806323C0(D_807F6C18[i].unk14);
            func_806323C0(D_807F6C18[i].unk1C);
            i += 1;
        } while (i < D_807F6C28);
    }
}

#ifdef NON_MATCHING
void func_80652A08(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    s32 var_v1;
    s32 var_s0;
    s32 var_s1;
    void *temp_v0;

    var_v1 = D_807F6C28;
    var_s1 = 0;
    if (var_v1 > 0) {
        var_s0 = 0;
        do {
            if (((MapChunk *)((u8 *)D_807F6C18 + var_s0))->unk0 == 1 || arg3) {
                if (((MapChunk *)((u8 *)D_807F6C18 + var_s0))->unk6 != 0) {
                    ((MapChunk *)((u8 *)D_807F6C18 + var_s0))->unk24 = 0;
                } else {
                    ((MapChunk *)((u8 *)D_807F6C18 + var_s0))->unk24 = func_8063A38C(((MapChunk *)((u8 *)D_807F6C18 + var_s0))->unk14, ((MapChunk *)((u8 *)D_807F6C18 + var_s0))->unk1C, arg0, arg1, arg2);
                }
                var_v1 = D_807F6C28;
            }
            var_s1 += 1;
            var_s0 += 0x1C8;
        } while (var_s1 < var_v1);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652A08.s")
#endif

typedef struct MapNode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ struct MapNode *unk14;
    /* 0x18 */ u8 pad18[6];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ u8 unk24;
} MapNode; /* 0x28 */

#ifdef NON_MATCHING
void func_80652B04(void) {
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    void *node;
    void *next;

    D_807F7140 = 0;
    var_s3 = 0;
    if (D_807F6C28 > 0) {
        var_s4 = 0;
        do {
            if (((MapChunk *)((u8 *)D_807F6C18 + var_s4))->unk1 != 0) {
                var_s2 = 1;
            } else {
                var_s2 = 0;
            }
            node = (void *)((MapChunk *)((u8 *)D_807F6C18 + var_s4))->unk14;
            if (node != NULL) {
                do {
                    next = ((MapNode *)node)->unk14;
                    func_8063B4C0(node, var_s2 & 0xFF);
                    node = next;
                } while (next != NULL);
            }
            var_s3 += 1;
            var_s4 += 0x1C8;
        } while (var_s3 < D_807F6C28);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652B04.s")
#endif

#ifdef NON_MATCHING
#define MAP_CHUNK_AT(o) ((MapChunk *)((u8 *)D_807F6C18 + (o)))

extern s32 func_80668E9C(s32, s16, f32, f32, f32, s32);

s32 func_80652BC8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    s32 result;
    s32 i;
    s16 x;
    s16 y;
    u8 mode;
    void *ptr;
    MapNode *node;

    result = 0;
    mode = func_80630324(1, 0);
    i = 0;
    if (D_807F6C28 > 0) {
        x = (s16)(s32)(arg1 * 6.0f);
        node = ptr;
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
                            result = (result | func_80668E9C(arg0, node->unk1E, arg1, arg2, arg3, arg4)) & 0xFF;
                        }
                        node = node->unk14;
                    } while (node != NULL);
                }
            }
            i++;
        } while (i < D_807F6C28);
        ptr = node;
    }
    return result;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652BC8.s")
#endif

#ifdef NON_MATCHING
s32 func_80652DB4(f32 arg0, f32 arg1, f32 arg2) {
    s16 *var_v1;
    s16 temp_t1;
    s16 temp_v0;
    s32 i;

    i = 0;
    if (D_807F6C28 == 0) {
        return 0xFF;
    }
    temp_v0 = func_806531B8(arg0, arg1, arg2, 0);
    if (D_807F6C80 > 0) {
        var_v1 = &D_807F6C58[i];
        do {
            temp_t1 = *var_v1;
            var_v1++;
            if (temp_v0 == temp_t1) {
                return 1;
            }
        } while ((u32)var_v1 < (u32)&D_807F6C58[D_807F6C80]);
    }
    return 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652DB4.s")
#endif

s32 mapChunkIsVisible(s16 arg0) {
    s32 var_v1;

    if (D_807F6C28 == 0) {
        return 0xFF;
    }
    if (D_807F6C18[arg0].unk1 != 0) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1 & 0xFF;
}

s32 mapChunkIsActive(s16 arg0) {
    s32 var_v1;

    if (D_807F6C28 == 0) {
        return 0xFF;
    }
    if (D_807F6C18[arg0].unk0 == 1) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1 & 0xFF;
}

s32 mapChunkIsVisibleForPlayer(s16 arg0, s16 arg1) {
    s32 var_v1;

    if (D_807F6C28 == 0) {
        return 1;
    }
    if (D_807F6C18[arg1].unk1 & (1 << arg0)) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1 & 0xFF;
}

s16 mapChunkFindAtPoint(f32 arg0, f32 arg1, f32 arg2, s16 arg3) {
    s16 temp;

    func_80652FDC(arg0, arg1, arg2, arg3, -1, &temp);
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

#ifdef NON_MATCHING
void func_80652FDC(f32 arg0, f32 arg1, f32 arg2, s16 arg3, s16 arg4, s16 *arg5) {
    s16 temp_v1;
    s32 var_s1;

    var_s1 = 0;
    if (D_807F70AC > 0) {
        do {
            if ((arg3 == D_807F70B0[var_s1].unk0) && (arg4 == D_807F70B0[var_s1].unk4)) {
                temp_v1 = D_807F70B0[var_s1].unk2;
                if (((f32)D_807F70B4[temp_v1].unk0 <= arg0) && (arg0 <= (f32)D_807F70B4[temp_v1].unk6) && ((f32)D_807F70B4[temp_v1].unk2 <= arg1) && (arg1 <= (f32)D_807F70B4[temp_v1].unk8) && ((f32)D_807F70B4[temp_v1].unk4 <= arg2) && (arg2 <= (f32)D_807F70B4[temp_v1].unkA)) {
                    *arg5 = temp_v1;
                    func_80652FDC(arg0, arg1, arg2, arg3, temp_v1, arg5);
                }
            }
            var_s1 += 1;
        } while (var_s1 < D_807F70AC);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652FDC.s")
#endif

#ifdef NON_MATCHING
s16 func_806531B8(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    s16 sp70[200];
    f32 sp200;
    u8 sp207;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 var_fs0;
    s16 var_s1;
    s16 var_s3;
    s32 var_s0;
    s32 var_s1_2;
    s32 var_s2;
    void *temp_v0;
    u8 *var_s0_2;

    var_s2 = 0;
    if (D_807F6C28 == 0) {
        return -1;
    }
    temp_fs0 = arg0 * 6.0f;
    temp_fs1 = arg1 * 6.0f;
    temp_fs2 = arg2 * 6.0f;
    if (mapChunkFindNodeAtPoint(temp_fs0, temp_fs1, temp_fs2, arg3, &sp207, &sp200) != 0) {
        if (sp207 == 0) {
            return arg3;
        }
        sp70[0] = arg3;
        var_s2 = 1;
        *(f32 *)&sp70[2] = sp200;
    }
    var_s0 = 0;
    var_s1 = 0;
    if (D_807F6C28 > 0) {
        do {
            if (arg3 != var_s1) {
                if (mapChunkFindNodeAtPoint(temp_fs0, temp_fs1, temp_fs2, var_s1, &sp207, &sp200) != 0) {
                    if (sp207 == 0) {
                        var_s0 = 1;
                    } else {
                        temp_v0 = (u8 *)sp70 + var_s2 * 8;
                        *(s16 *)temp_v0 = var_s1;
                        var_s2 += 1;
                        var_s1 += 1;
                        *(f32 *)((u8 *)temp_v0 + 4) = sp200;
                    }
                } else {
                    var_s1 += 1;
                }
            } else {
                var_s1 += 1;
            }
        } while ((var_s0 == 0) && (var_s1 < D_807F6C28));
    }
    if (var_s0 != 0) {
        return var_s1;
    }
    var_fs0 = *(f32 *)&sp70[2];
    if (var_s2 == 0) {
        return arg3;
    }
    var_s3 = sp70[0];
    var_s1_2 = 0;
    if (var_s2 > 0) {
        var_s0_2 = (u8 *)sp70;
        do {
            var_s1_2 += 1;
            if (func_806533C4(var_fs0, *(f32 *)(var_s0_2 + 4), temp_fs1) != 0) {
                var_fs0 = *(f32 *)(var_s0_2 + 4);
                var_s3 = *(s16 *)var_s0_2;
            }
            var_s0_2 += 8;
        } while (var_s1_2 != var_s2);
    }
    return var_s3;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806531B8.s")
#endif

#ifdef NON_MATCHING
s32 func_806533C4(f32 arg0, f32 arg1, f32 arg2) {
    s32 var_v0;
    s32 var_v1;
    f32 var_fv0;
    f32 var_fv1;

    var_v0 = 0;
    if (arg0 <= arg2) {
        var_v0 = 1;
    } else if ((arg0 - arg2) < 60.0f) {
        var_v0 = 1;
    }
    var_v1 = 0;
    if (arg1 <= arg2) {
        var_v1 = 1;
    } else if ((arg1 - arg2) < 60.0f) {
        var_v1 = 1;
    }
    if (var_v0 != 0 || var_v1 != 0) {
        if (var_v1 != 0) {
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
        return 0;
    }
    return 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806533C4.s")
#endif

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

    temp_v0 = (MapChunk *)((u8 *)D_807F6C18 + arg3 * 0x1C8);
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
            if ((mapNodeBoxContainsPoint(var_s0, arg0, arg2) != 0) && (func_80653804(var_s0, arg0, arg2) != 0)) {
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

#ifdef NON_MATCHING
s32 func_80653804(void *arg0, f32 arg1, f32 arg2) {
    f64 lead0;
    f64 lead1;
    f64 lead2;
    f64 lead3;
    f64 spA0;
    f64 sp98;
    f64 sp90;
    f64 sp88;
    f64 pad2;
    f64 pad3;
    f64 pad4;
    f64 pad5;
    f64 pad6;
    f64 pad7;
    f64 pad8;
    f64 sp38;
    f64 fs1;
    f64 fs2;
    f64 fs3;
    f64 fs4;
    f64 fs5;
    f64 ft4;
    f64 ft5;
    f64 fa0;
    f64 fa1;
    f64 fv0;
    f64 fv1;
    f64 fs0;
    s32 sgn1;
    s32 sgn2;
    s32 flag;
    s32 i;

    fs3 = arg1;
    fs4 = arg2;
    fs5 = ((MapCollisionNode *)arg0)->unk0;
    sp38 = ((MapCollisionNode *)arg0)->unkC;
    fs1 = (fs5 + ((f64)(((MapCollisionNode *)arg0)->unk4 + ((MapCollisionNode *)arg0)->unk2) * 0.5)) * 0.5;
    fs2 = (sp38 + ((f64)(((MapCollisionNode *)arg0)->unk10 + ((MapCollisionNode *)arg0)->unkE) * 0.5)) * 0.5;
    ft5 = sp88;
    ft4 = sp90;
    fa1 = sp98;
    fa0 = spA0;
    flag = 0;
    i = 0;
    do {
        switch (i) {
        default:
            fv0 = (fs3 - ft4) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - ft4) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 0:
            ft4 = fs5;
            ft5 = sp38;
            fa1 = (f64)(((MapCollisionNode *)arg0)->unkE - ((MapCollisionNode *)arg0)->unkC);
            fa0 = (f64)(((MapCollisionNode *)arg0)->unk2 - ((MapCollisionNode *)arg0)->unk0);
            fv0 = (fs3 - fs5) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - fs5) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 1:
            ft4 = fs5;
            ft5 = sp38;
            fa1 = (f64)(((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkC);
            fa0 = (f64)(((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk0);
            fv0 = (fs3 - fs5) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - fs5) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 2:
            ft4 = (f64)((MapCollisionNode *)arg0)->unk2;
            ft5 = (f64)((MapCollisionNode *)arg0)->unkE;
            fa0 = (f64)(((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk2);
            fa1 = (f64)(((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkE);
            fv0 = (fs3 - ft4) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - ft4) * fa1) - ((fs2 - ft5) * fa0);
            break;
        }
        i++;
        sgn1 = -1;
        if (fv1 <= fv0) {
            sgn1 = 1;
        }
        sgn2 = -1;
        if (fs0 >= 0.0) {
            sgn2 = 1;
        }
        if (sgn2 != sgn1) {
            flag = 1;
        }
    } while (i != 3);
    sp88 = ft5;
    sp90 = ft4;
    sp98 = fa1;
    spA0 = fa0;
    return (flag == 0) & 0xFF;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80653804.s")
#endif


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

extern MapPlayer *D_807FC924;
extern u8 D_807FC929;

void mapChunkActivate(s16 arg0) {
    D_807F6C18[arg0].unk0 = 1;
    D_807F6C18[arg0].unk1 |= 1 << D_807FC929;
    D_807F6C18[arg0].unk68 = D_807FC924[D_807FC929].unk270;
    D_807F6C18[arg0].unk6C = D_807FC924[D_807FC929].unk272;
    D_807F6C18[arg0].unk70 = D_807FC924[D_807FC929].unk274;
    D_807F6C18[arg0].unk74 = D_807FC924[D_807FC929].unk276;
}


void mapChunkSetIndexOverride(s8 arg0) {
    D_807F70AB = arg0;
}

void func_8062AD28(f32, f32, f32, void *, void *);
void func_8062AC68(Mtx *);
void func_8062A944(f32, f32, f32);
void mapUpdateFogDistance(f32 *, s16);
void mapChunkClearBounds();
void mapChunkActivate(s16);
void func_806547A8(f32, f32, f32);
void mapChunkRenderNodes(f32, f32, f32);
void mapTriggerApplyZones(f32, f32, f32);
void func_80656F14(s16, s32, s16, s16, s16, s16, f32, f32, f32);
void func_8065F678(f32, f32, f32, u8);
void actorCalculateTargetDistancesAndAngles(f32, f32, f32);
void func_80655410(f32, f32, f32);
extern u8 D_807F5E20[];
extern u8 D_807F5E68[];
extern u8 D_807444FC;
extern f32 D_807F5FB4;
extern f32 D_807F5FB0;
extern u8 D_807F6C08;

void mapChunkFrameUpdate(f32 arg0, f32 arg1, f32 arg2) {
    D_807FC924[D_807FC929].unk290 = func_806531B8(arg0, arg1, arg2, D_807FC924[D_807FC929].unk290);
    if (D_807F70AB != 0) {
        D_807FC924[D_807FC929].unk290 = *(s16 *)((u8 *)D_807FC924[D_807FC929].unk4 + 0x12C);
    }
    mapUpdateFogDistance(&D_807FC924[D_807FC929].unk288, D_807FC924[D_807FC929].unk290);
    D_807F7138 = (s16)(s32)D_807FC924[D_807FC929].unk288;
    func_8062A944(D_807F5FB4, D_807F5FB0, (f32)D_807F7138);
    func_8062AC68((Mtx *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + (D_807444FC << 6) + 8));
    func_8062AD28(arg0, arg1, arg2, &D_807F5E68, &D_807F5E20);
    mapChunkClearBounds();
    mapChunkActivate(D_807FC924[D_807FC929].unk290);
    func_806547A8(arg0, arg1, arg2);
    D_807F6C80 = 0;
    D_807F6C08 = 0;
    func_80656F14(D_807FC924[D_807FC929].unk290, 0, D_807FC924[D_807FC929].unk270, D_807FC924[D_807FC929].unk272, D_807FC924[D_807FC929].unk274, D_807FC924[D_807FC929].unk276, arg0, arg1, arg2);
    mapChunkRenderNodes(arg0, arg1, arg2);
    func_8065F678(arg0, arg1, arg2, D_807FC929);
    actorCalculateTargetDistancesAndAngles(arg0, arg1, arg2);
    func_80655410(arg0, arg1, arg2);
}

extern s32 func_8066B0F8(s32, s32, s32, s32);

#ifdef NON_MATCHING
u8 *func_80653DF0(u8 *arg0, u8 *arg1, s16 arg2) {
    s32 count;
    u8 *p;
    s32 temp_v0;
    s32 zero;
    u32 tag;

    p = arg0;
    zero = 0;
    count = zero;
    if ((p != arg1) && (arg2 > zero)) {
        do {
            tag = *(u32 *)p;
            if ((tag >> 0x18) == 0xFD) {
                temp_v0 = *(s32 *)(p + 4);
                if (((u32)(temp_v0 * 0x10) >> 0x1C) == zero) {
                    *(s32 *)(p + 4) = func_8066B0F8(0x19, temp_v0, zero, zero);
                    count++;
                }
                if (zero) {
                }
            }
            p += 8;
        } while ((p != arg1) && (count < arg2));
    }
    return p;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80653DF0.s")
#endif


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
    D_807F6C18[arg0].unk7 |= 8;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80653FA4.s")

extern void func_80654418(f32, f32, f32);
extern void func_80655258(f32, f32, f32, s32);

void mapChunkRenderNodes(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 off;

    func_80654418(arg0, arg1, arg2);
    i = 0;
    off = 0;
    while (i < D_807F70AC) {
        i++;
        D_807F70B0[off].unk18 = 0;
        off += 1;
    }
    func_80655258(arg0, arg1, arg2, -1);
    mapTriggerApplyZones(arg0, arg1, arg2);
}

#ifdef NON_MATCHING
extern f32 D_807F5FAC;
extern s32 D_807482F4;
extern u8 D_807F7148[];
void func_8062FF10(f32 (*)[4], f32 (*)[4]);
void func_806545D4(s32, s32, s32, s32, f32, f32, f32, u8, void *, void *, void *);

void func_80654418(f32 arg0, f32 arg1, f32 arg2) {
    f32 spF8[4][4];
    f32 spB8[4][4];
    u8 sp84[0x34];
    s32 i;
    s32 off;
    u8 *p;

    func_8062A944(D_807F5FB4, D_807F5FB0, D_807F5FAC);
    guMtxL2F(spF8, (Mtx *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + (D_807444FC << 6) + 8));
    func_8062FF10(spB8, spF8);
    off = 0;
    i = 0;
    while (i < D_807F6C28) {
        p = (u8 *)D_807F6C18 + off;
        if (p[0] == 1) {
            func_806545D4(*(s32 *)(p + 0x68), *(s32 *)(p + 0x6C), *(s32 *)(p + 0x70), *(s32 *)(p + 0x74),
                          arg0, arg1, arg2, D_807FC929, spB8, p + 0x88, sp84);
        }
        if (i == D_807482F4) {
            memcpy(D_807F7148, (u8 *)D_807F6C18 + off + 0x88, 0x140);
        }
        i++;
        off += 0x1C8;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654418.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806545D4.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806547A8.s")

typedef struct MapTrigger {
    s16 unk0[10];
    s16 unk14[16];
    u8 unk34;
    s16 unk36[16];
    u8 unk56;
} MapTrigger;

extern void *D_807F70B8[];
extern u8 D_807F7048[];
extern u8 D_807F7058;

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654CCC.s")

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

#ifdef NON_MATCHING
s32 func_80654FEC(void *arg0, f32 arg1, f32 arg2) {
    f64 lead0;
    f64 lead1;
    f64 lead2;
    f64 lead3;
    f64 spA0;
    f64 sp98;
    f64 sp90;
    f64 sp88;
    f64 pad2;
    f64 pad3;
    f64 pad4;
    f64 pad5;
    f64 pad6;
    f64 pad7;
    f64 pad8;
    f64 sp38;
    f64 fs1;
    f64 fs2;
    f64 fs3;
    f64 fs4;
    f64 fs5;
    f64 ft4;
    f64 ft5;
    f64 fa0;
    f64 fa1;
    f64 fv0;
    f64 fv1;
    f64 fs0;
    s32 sgn1;
    s32 sgn2;
    s32 flag;
    s32 i;

    fs3 = arg1;
    fs4 = arg2;
    fs5 = ((MapCollisionNode *)arg0)->unk0;
    sp38 = ((MapCollisionNode *)arg0)->unkC;
    fs1 = (fs5 + ((f64)(((MapCollisionNode *)arg0)->unk4 + ((MapCollisionNode *)arg0)->unk2) * 0.5)) * 0.5;
    fs2 = (sp38 + ((f64)(((MapCollisionNode *)arg0)->unk10 + ((MapCollisionNode *)arg0)->unkE) * 0.5)) * 0.5;
    ft5 = sp88;
    ft4 = sp90;
    fa1 = sp98;
    fa0 = spA0;
    flag = 0;
    i = 0;
    do {
        switch (i) {
        default:
            fv0 = (fs3 - ft4) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - ft4) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 0:
            ft4 = fs5;
            ft5 = sp38;
            fa1 = (f64)(((MapCollisionNode *)arg0)->unkE - ((MapCollisionNode *)arg0)->unkC);
            fa0 = (f64)(((MapCollisionNode *)arg0)->unk2 - ((MapCollisionNode *)arg0)->unk0);
            fv0 = (fs3 - fs5) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - fs5) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 1:
            ft4 = fs5;
            ft5 = sp38;
            fa1 = (f64)(((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkC);
            fa0 = (f64)(((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk0);
            fv0 = (fs3 - fs5) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - fs5) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 2:
            ft4 = (f64)((MapCollisionNode *)arg0)->unk2;
            ft5 = (f64)((MapCollisionNode *)arg0)->unkE;
            fa0 = (f64)(((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk2);
            fa1 = (f64)(((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkE);
            fv0 = (fs3 - ft4) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - ft4) * fa1) - ((fs2 - ft5) * fa0);
            break;
        }
        i++;
        sgn1 = -1;
        if (fv1 <= fv0) {
            sgn1 = 1;
        }
        sgn2 = -1;
        if (fs0 >= 0.0) {
            sgn2 = 1;
        }
        if (sgn2 != sgn1) {
            flag = 1;
        }
    } while (i != 3);
    sp88 = ft5;
    sp90 = ft4;
    sp98 = fa1;
    spA0 = fa0;
    return (flag == 0) & 0xFF;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654FEC.s")
#endif

#ifdef NON_MATCHING

s32 func_8062DBDC(s16, s16, s16, s16, s16, s16, f32, f32, f32, f32, void *);
void func_80655258(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    s32 i;
    MapBox *box;
    s32 off;

    i = 0;
    if (D_807F70AC > 0) {
        off = 0;
        do {
            if (arg3 == ((MapCell *)((u8 *)D_807F70B0 + off))->unk4) {
                if (D_807F6C18[((MapCell *)((u8 *)D_807F70B0 + off))->unk0].unk0 == 1) {
                    box = (MapBox *)D_807F70B4;
                    if (func_8062DBDC(box[((MapCell *)((u8 *)D_807F70B0 + off))->unk2].unk0,
                                      box[((MapCell *)((u8 *)D_807F70B0 + off))->unk2].unk2,
                                      box[((MapCell *)((u8 *)D_807F70B0 + off))->unk2].unk4,
                                      box[((MapCell *)((u8 *)D_807F70B0 + off))->unk2].unk6,
                                      box[((MapCell *)((u8 *)D_807F70B0 + off))->unk2].unk8,
                                      box[((MapCell *)((u8 *)D_807F70B0 + off))->unk2].unkA,
                                      arg0, arg1, arg2, D_807F5FAC,
                                      (u8 *)&D_807F6C18[((MapCell *)((u8 *)D_807F70B0 + off))->unk0] + 0x88) != 0) {
                        ((MapCell *)((u8 *)D_807F70B0 + off))->unk18 = 1;
                        ((MapCell *)((u8 *)D_807F70B0 + off))->unk19 = 1;
                    }
                    if (((MapCell *)((u8 *)D_807F70B0 + off))->unk18 != 0) {
                        func_80655258(arg0, arg1, arg2, ((MapCell *)((u8 *)D_807F70B0 + off))->unk2);
                    }
                }
            }
            i++;
            off += 0x1C;
        } while (i < D_807F70AC);
    }
}

#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655258.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655410.s")

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


void func_80636164(s32, u8);
void func_80636210(s32, u8);
s32 func_8065E81C(s32, s32);
void heapFree(void *);

void mapChunkFreeIdleBuffers(void) {
    s32 i;
    s32 off;
    MapChunkDraw *eff;

    if (D_807F713A != 0) {
        func_8065E81C(0, 0x190);
    }
    i = 0;
    off = 0;
    while (i < D_807F6C28) {
        eff = (MapChunkDraw *)((u8 *)D_807F6C18 + off);
        if (eff->unk3 != 0 && eff->unk5 != 2 && eff->unk4 == 0) {
            if (((MapChunkDraw *)D_807F6C18)[i].unk60[D_807444FC] != NULL) {
                heapFree(((MapChunkDraw *)D_807F6C18)[i].unk60[D_807444FC]);
                ((MapChunkDraw *)D_807F6C18)[i].unk60[D_807444FC] = NULL;
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
        eff = &((MapChunkDraw *)D_807F6C18)[D_807F70AA];
        node = eff->unk14;
        if (node) {
            do {
                func_80636164(node->unk0, node->unk24);
                func_80636210(node->unk0, node->unk24);
                node = node->unk14;
            } while (node);
            eff = &((MapChunkDraw *)D_807F6C18)[D_807F70AA];
        }
        node = eff->unk1C;
        if (node) {
            do {
                func_80636164(node->unk0, node->unk24);
                func_80636210(node->unk0, node->unk24);
                node = node->unk14;
            } while (node);
        }
    }
    D_807F70AA++;
    if (D_807F6C28 == D_807F70AA) {
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

#define MAP_CHUNK_TILE_AT(i) (((MapChunkTile *)D_807F6C18)[(i)])

extern u8 D_807F5FEC;
extern void *D_807F5DEC;
extern s32 D_807FBB64;
extern u8 D_807F6009;
extern s32 D_807F600C;
extern s32 D_807F5FFC;
extern Gfx D_2000180;

u32 osVirtualToPhysical(void *);
Gfx *func_8062CEA8(Gfx *, void *, s32);
Gfx *func_8062EDA8(Gfx *, u8);
void func_8062EE48(u8);
s32 func_80656B98();
Gfx *func_8063A968(Gfx *, s32);
Gfx *func_8065D994(Gfx *, s16);
Gfx *func_80630B70(Gfx *, s32, s32, s32, f32, s32, s16, s32);
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
    flag = (D_807F5FEC != 0) && (((MapPlayerFog *)D_807FC924)[D_807FC929].unk27C == 45.0);
    gDPPipeSync(gfx++);
    if (arg5 & 0x10) {
        gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
        gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
        gfx = func_8062CEA8(gfx, arg1, 1);
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
                func_8062EE48(idx);
                MAP_CHUNK_TILE_AT(idx).unk2 = 0;
            }
            gDPPipeSync(gfx++);
            gDPSetScissor(gfx++, G_SC_NON_INTERLACE, MAP_CHUNK_TILE_AT(idx).tile.w.unk68, MAP_CHUNK_TILE_AT(idx).tile.w.unk6C, MAP_CHUNK_TILE_AT(idx).tile.w.unk70, MAP_CHUNK_TILE_AT(idx).tile.w.unk74);
            mapSetClipBounds(MAP_CHUNK_TILE_AT(idx).tile.h.unk6A, MAP_CHUNK_TILE_AT(idx).tile.h.unk6E, MAP_CHUNK_TILE_AT(idx).tile.h.unk72, MAP_CHUNK_TILE_AT(idx).tile.h.unk76);
            gfx = fogRender(gfx);
            if (arg5 & 0x10) {
                gfx = func_8062EDA8(gfx, idx);
                if (MAP_CHUNK_TILE_AT(idx).unk2C != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)MAP_CHUNK_TILE_AT(idx).unk58));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = (Gfx *)func_80656B98(gfx, idx, 0);
                    gDPPipeSync(gfx++);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
                if (MAP_CHUNK_TILE_AT(idx).unk34 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)MAP_CHUNK_TILE_AT(idx).unk58));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = (Gfx *)func_80656B98(gfx, idx, 2);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
            }
            gDPPipeSync(gfx++);
            if (!(D_807FBB64 & 0x01000000)) {
                gfx = func_8065D994(gfx, idx);
            }
            gfx = func_8063A968(gfx, MAP_CHUNK_TILE_AT(idx).unk24);
            D_807F6009 = 0xFF;
            if (flag != 0) {
                dl = MAP_CHUNK_TILE_AT(idx).unk18;
            } else {
                dl = MAP_CHUNK_TILE_AT(idx).unk14;
            }
            gfx = func_80630B70(gfx, dl, arg2, arg3, arg4, arg5, idx, flag);
            if (arg5 & 0x10) {
                gSPClearGeometryMode(gfx++, 0xFFFFFFFF);
                gSPSetGeometryMode(gfx++, 0x200004);
                gfx = fogRender(gfx);
                gfx = func_8062EDA8(gfx, idx);
                if (MAP_CHUNK_TILE_AT(idx).unk30 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)MAP_CHUNK_TILE_AT(idx).unk58));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = (Gfx *)func_80656B98(gfx, idx, 1);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gDPPipeSync(gfx++);
                }
                if (MAP_CHUNK_TILE_AT(idx).unk38 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)MAP_CHUNK_TILE_AT(idx).unk58));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = (Gfx *)func_80656B98(gfx, idx, 3);
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
        gfx = func_8062CEA8(gfx, arg1, 2);
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
            gfx = func_80630B70(gfx, dl, arg2, arg3, arg4, arg5, idx, flag);
            if (D_807FBB64 & 0x01000000) {
                gfx = func_8065D994(gfx, idx);
            }
        }
    }
    if (arg5 & 0x10) {
        gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
        gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
        gfx = func_8062CEA8(gfx, arg1, 3);
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(gfx++);
    }
    gDPPipeSync(gfx++);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, D_807FC924[D_807FC929].unk270, D_807FC924[D_807FC929].unk272, D_807FC924[D_807FC929].unk274, D_807FC924[D_807FC929].unk276);
    mapSetClipBounds(D_807FC924[D_807FC929].unk270, D_807FC924[D_807FC929].unk272, D_807FC924[D_807FC929].unk274, D_807FC924[D_807FC929].unk276);
    D_807F600C = 0;
    gfx = func_80630B70(gfx, D_807F5FFC, arg2, arg3, arg4, arg5, -1, 0);
    func_8065D994(gfx, -1);
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


#ifdef NON_MATCHING
s32 func_80656B98(arg0, arg1, arg2)
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
    WRITE_GFX(gfx++, 0xE7000000, 0);
    if (((MapChunkEffect *)D_807F6C18)[arg1].unk5 != 2) {
        switch (arg2) {
        case 0:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)D_807F6C18)[arg1].unk2C));
            break;
        case 1:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)D_807F6C18)[arg1].unk30));
            break;
        case 2:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)D_807F6C18)[arg1].unk34));
            break;
        case 3:
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffect *)D_807F6C18)[arg1].unk38));
            break;
        }
    } else {
        for (i = 0; i < ((MapChunkEffect *)D_807F6C18)[arg1].unk50; i++) {
            if (((MapChunkEffectEntry *)((MapChunkEffect *)D_807F6C18)[arg1].unk4C)[i].unk4[arg2] == -1) {
                continue;
            }
            found = 0;
            node = D_807F70B0;
            do {
                if (node->unk2 == ((MapChunkEffectEntry *)((MapChunkEffect *)D_807F6C18)[arg1].unk4C)[i].unk0) {
                    found = 1;
                } else {
                    node++;
                }
            } while (found == 0);
            if (node->unk18 == 0) {
                continue;
            }
            if ((((MapChunkEffectEntry *)((MapChunkEffect *)D_807F6C18)[arg1].unk4C)[i].unk2 & (1 << arg2)) == 0) {
                continue;
            }
            WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)D_807F6C18)[arg1].unk4C)[i].unk14[arg2]));
            WRITE_GFX(gfx++, 0xE7000000, 0);
            WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)D_807F6C18)[arg1].unk4C)[i].unk4[arg2]));
            WRITE_GFX(gfx++, 0xE7000000, 0);
        }
    }
    return (s32)gfx;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80656B98.s")
#endif

void mapChunkEffectSetFlag(s16 arg0, s16 arg1, u8 arg2, u8 arg3) {
    s32 i = 0;
    MapChunkEffect *slot = (MapChunkEffect *)D_807F6C18 + arg0;

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80656F14.s")

extern u8 D_807F7070;
extern u8 D_807F7060[];

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



extern void func_80657CB0(s32, f32, f32, f32, f32 *, f32 *, f32 *);
extern void mapGridPointBuildVectors(s32, f32, f32, f32, MapGridQuad *);
extern s32 func_8065776C(u8 *);

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

    sp40 = (f32)D_807F6C24[arg0].unk10;
    sp44 = (f32)D_807F6C24[arg0].unk8;
    sp48 = (f32)D_807F6C24[arg0].unk0;
    h = (f32)D_807F6C24[arg0].unk18;
    x = (h + (sp48 * arg1 + sp44 * arg2 + sp40 * arg3)) / D_807F6C24[arg0].unk20;
    if (x < 0.0) {
        x = 0.0 - x;
    }
    if (x > 80.0) {
        return 0;
    }
    func_80657CB0(arg0, arg1, arg2, arg3, &sp7C, &sp78, &sp74);
    mapGridPointBuildVectors(arg0, sp7C, sp78, sp74, (MapGridQuad *)sp4C);
    if (func_8065776C(sp4C)) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_8065776C.s")



void mapGridPointBuildVectors(s32 arg0, f32 arg1, f32 arg2, f32 arg3, MapGridQuad *arg4) {
    s32 k;

    switch (D_807F6C24[arg0].unk28) {
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

#ifdef NON_MATCHING
void func_80657CB0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    f32 t;
    f32 a = (f32)(-D_807F6C24[arg0].unk18);

    t = (a - ((f32)D_807F6C24[arg0].unk10 * arg3 + ((f32)D_807F6C24[arg0].unk0 * arg1 + (f32)D_807F6C24[arg0].unk8 * arg2))) / D_807F6C24[arg0].unk24;
    *arg4 = (f32)D_807F6C24[arg0].unk0 * t + arg1;
    *arg5 = (f32)D_807F6C24[arg0].unk8 * t + arg2;
    *arg6 = (f32)D_807F6C24[arg0].unk10 * t + arg3;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80657CB0.s")
#endif

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

    v = ((f32)D_807F6C24[arg0].unk18 + ((f32)D_807F6C24[arg0].unk0 * arg1 + (f32)D_807F6C24[arg0].unk8 * arg2 + (f32)D_807F6C24[arg0].unk10 * arg3)) / D_807F6C24[arg0].unk20;
    if (v < 0.0) {
        v = 0.0 - v;
    }
    return (v <= (f32)arg4) & 0xFF;
}

#ifdef NON_MATCHING
extern f32 D_807F6C88;
extern f32 D_807F6C8C;
extern f32 D_807F6C90;
extern f32 D_807F6C94;
extern f32 D_807F6C98;
extern f32 D_807F6C9C;
extern f32 D_807F6CA0;
extern f32 D_807F6CA4;
extern f32 D_807F6CA8;
extern f32 D_807F6CAC;
extern f32 D_807F6CB0;
extern f32 D_807F6CB4;
extern f32 D_807F6E68[];
extern f32 D_807F6F58[];
extern f32 D_807F6D78[];

void func_806582F8(f32 *, f32 *, s32, s32 *, s32);

s32 func_80658134(arg0, arg1, arg2, arg3)
s32 arg0;
s32 arg1;
s32 arg2;
s32 arg3;
{
    s32 n1 = 0;
    s32 n2 = 0;
    D_807F6C88 = D_807F6C14[arg0].unk0[0];
    D_807F6C8C = D_807F6C14[arg0].unk10[0];
    D_807F6C90 = D_807F6C14[arg0].unk20[0];
    D_807F6C94 = D_807F6C14[arg0].unk0[1];
    D_807F6C98 = D_807F6C14[arg0].unk10[1];
    D_807F6C9C = D_807F6C14[arg0].unk20[1];
    D_807F6CA0 = D_807F6C14[arg0].unk0[2];
    D_807F6CA4 = D_807F6C14[arg0].unk10[2];
    D_807F6CA8 = D_807F6C14[arg0].unk20[2];
    D_807F6CAC = D_807F6C14[arg0].unk0[3];
    D_807F6CB0 = D_807F6C14[arg0].unk10[3];
    D_807F6CB4 = D_807F6C14[arg0].unk20[3];
    func_806582F8(&D_807F6C88, D_807F6E68, 4, &n2, 0);
    if (n2 == 0) {
        return 0;
    }
    func_806582F8(D_807F6E68, D_807F6F58, n2, &n1, 1);
    if (n1 == 0) {
        return 0;
    }
    func_806582F8(D_807F6F58, D_807F6E68, n1, &n2, 2);
    if (n2 == 0) {
        return 0;
    }
    func_806582F8(D_807F6E68, D_807F6F58, n2, &n1, 3);
    if (n1 == 0) {
        return 0;
    }
    func_806582F8(D_807F6F58, D_807F6D78, n1, &n2, 4);
    if (n2 < 3) {
        n2 = 0;
    }
    return n2;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658134.s")
#endif

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

void func_8065850C(f32 *, f32 *, s32, f32 *);

#ifdef NON_MATCHING
void func_806582F8(f32 *arg0, f32 *arg1, s32 arg2, s32 *arg3, s32 arg4) {
    f32 sp7C[3];
    MapPlane *plane;
    MapVec3 *prev;
    MapVec3 *cur;
    s32 n;
    s32 i;
    f64 y;
    f64 z;
    f64 d;

    n = 0;
    prev = (MapVec3 *)&arg0[arg2 * 3] - 1;
    cur = (MapVec3 *)arg0;
    plane = (MapPlane *)(D_807F5E68 + (arg4 << 6));
    for (i = 0; i < arg2; i++) {
        d = plane->unk38;
        y = d + (((plane->unk20 * cur->x) + (plane->unk28 * cur->y)) + (plane->unk30 * cur->z));
        z = d + (((plane->unk20 * prev->x) + (plane->unk28 * prev->y)) + (plane->unk30 * prev->z));
        if (y >= 0.0) {
            if (z >= 0.0) {
                memcpy(arg1 + n * 3, cur, 0xC);
                n++;
            } else {
                func_8065850C((f32 *)prev, (f32 *)cur, arg4, sp7C);
                memcpy(arg1 + n * 3, sp7C, 0xC);
                n++;
                memcpy(arg1 + n * 3, cur, 0xC);
                n++;
            }
        } else if (z >= 0.0) {
            func_8065850C((f32 *)prev, (f32 *)cur, arg4, sp7C);
            memcpy(arg1 + n * 3, sp7C, 0xC);
            n++;
        }
        prev = cur++;
    }
    *arg3 = n;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806582F8.s")
#endif

#ifdef NON_MATCHING
void func_8065850C(f32 *arg0, f32 *arg1, s32 arg2, f32 *arg3) {
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_8065850C.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658624.s")

void func_80658930(u8 *);

void mapLoadNodeAsset(s32 arg0) {
    u8 *p;

    p = (u8 *)func_8066B0F8(0x14, arg0, 1, 1);
    func_80658930(p);
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
    /* 0x36 */ u8 unk36[0x20];
    /* 0x56 */ s8 unk56;
    /* 0x58 */ u8 unk58[0x10];
    /* 0x68 */ s8 unk68;
} MapNodeData;

#ifdef NON_MATCHING
void func_80658930(u8 *arg0) {
    s32 *w;
    s32 *end;
    u8 **base;
    s16 n;
    s32 i;
    s16 idx;
    u8 *p;

    end = (s32 *)&D_807F7138;
    w = (s32 *)D_807F70B8;
    do {
        *w++ = 0;
    } while (w < end);
    base = (u8 **)D_807F70B8;
    if (arg0 == NULL) {
        return;
    }
    n = *(s16 *)arg0;
    p = arg0 + 2;
    for (i = 0; i < n; i++) {
        idx = *(s16 *)p;
        p += 2;
        base[idx] = func_80610FE8(0x6C);
        ((MapNodeData *)base[idx])->unk10 = 0x7FFF;
        ((MapNodeData *)base[idx])->unk12 = -0x8000;
        ((MapNodeData *)base[idx])->unk8 = 0;
        ((MapNodeData *)base[idx])->unk4 = *(s16 *)(p - 2);
        ((MapNodeData *)base[idx])->unk0 = func_80610FE8((u32)((MapNodeData *)base[idx])->unk4 * 6);
        memcpy(((MapNodeData *)base[idx])->unk0,
               p,
               (u32)((MapNodeData *)base[idx])->unk4 * 6);
        p += ((u32)((MapNodeData *)base[idx])->unk4 * 6 / 2) * 2;
        ((MapNodeData *)base[idx])->unkE = *(s16 *)p;
        ((MapNodeData *)base[idx])->unk34 = (s8)*(s16 *)(p + 2);
        p += 4;
        memcpy(((MapNodeData *)base[idx])->unk14, p, 0x20);
        ((MapNodeData *)base[idx])->unk56 = (s8)*(s16 *)(p + 0x20);
        p += 0x22;
        memcpy(((MapNodeData *)base[idx])->unk36, p, 0x20);
        ((MapNodeData *)base[idx])->unk68 = (s8)*(s16 *)(p + 0x20);
        p += 0x22;
        memcpy(((MapNodeData *)base[idx])->unk58, p, 0x10);
        p += 0x10;
        func_80651708(idx);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658930.s")
#endif

extern s16 D_807F7358;
extern s16 D_807F735A;
extern s16 D_807F735C;
extern s16 D_807F735E;

s32 mapObjectCollectIdsByType();

s32 mapObjectCollectIdsByType(arg0, arg1, arg2)
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
extern s32 D_8076A064;

#ifdef NON_MATCHING
void func_80658C10();

void func_80658C10(arg0, arg1, arg2, arg3)
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
        p->unk4 = arg1;
        p->unk6 = arg2;
        p->unk8 = arg3;
        p->unkC = D_8076A064;
        p->unk0 = arg0;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658C10.s")
#endif

extern s32 func_80700AE4(s16, s16);
extern s32 func_807009F4(s32);

#ifdef NON_MATCHING
void func_80658CCC(void) {
    MapSearchEntry *p;

    p = (MapSearchEntry *)&D_807F7290;
    do {
        if (p->unk10 != 0) {
            if (D_8076A064 == p->unkC) {
                if ((f32)func_807009F4((s16)func_80700AE4(p->unk4, p->unk6)) <= (f32)p->unk8) {
                    p->unk11 = 1;
                } else {
                    p->unk11 = 0;
                }
            }
        }
        if ((u32)(D_8076A064 - p->unkC) >= 3) {
            p->unk10 = 0;
        }
        p++;
    } while (p != (MapSearchEntry *)&D_807F7358);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658CCC.s")
#endif

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

#ifdef NON_MATCHING
typedef struct MapPlayerPosition {
    /* 0x000 */ u8 pad0[0x21C];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
} MapPlayerPosition;

void func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
f32 sqrtf(f32);

s32 func_80658E8C(f32 arg0, f32 arg1, f32 arg2, u8 arg3, u8 arg4) {
    f32 sp44;
    f32 sp40;
    s16 x;
    s16 z;
    s16 x0;
    s16 x1;
    s16 z0;
    s16 z1;
    f32 d;

    func_80626F8C(arg0, arg1, arg2, &sp44, &sp40, 0, 1.0f, D_807FC929);
    x = (s16)sp44;
    z = (s16)sp40;
    d = sqrtf(((arg2 - ((MapPlayerPosition *)&D_807FC924[D_807FC929])->unk224) * (arg2 - ((MapPlayerPosition *)&D_807FC924[D_807FC929])->unk224))
            + (((arg0 - ((MapPlayerPosition *)&D_807FC924[D_807FC929])->unk21C) * (arg0 - ((MapPlayerPosition *)&D_807FC924[D_807FC929])->unk21C))
            + ((arg1 - ((MapPlayerPosition *)&D_807FC924[D_807FC929])->unk220) * (arg1 - ((MapPlayerPosition *)&D_807FC924[D_807FC929])->unk220))));
    if (d < 90.0f) {
        return 0;
    }
    x0 = 20;
    x1 = 20;
    z0 = 0;
    if (d >= 180.0f) {
        z1 = 50;
    } else {
        x0 = 80;
        x1 = 80;
        z0 = 130;
        z1 = 130;
        if ((d - 60.0f) / 120.0f > 0.0) {
            x0 = -60.0f * ((d - 60.0f) / 120.0f) + 80.0f;
            x1 = -60.0f * ((d - 60.0f) / 120.0f) + 80.0f;
            z0 = -130.0f * ((d - 60.0f) / 120.0f) + 130.0f;
            z1 = -80.0f * ((d - 60.0f) / 120.0f) + 130.0f;
        }
    }
    if ((x < D_807F7358 - x0 - arg3) || (D_807F735C + x1 + arg3 < x)
        || (z < D_807F735A - z0 - arg4) || (D_807F735E + z1 + arg4 < z)) {
        return 1;
    }
    return 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658E8C.s")
#endif

