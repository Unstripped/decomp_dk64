#include "common.h"
#include "actor.h"

typedef struct M55P3EffectBuf {
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
} M55P3EffectBuf;

extern u8 D_807F7078[];
extern s32 D_807F6C28;
extern M55P3EffectBuf *D_807F6C18;
extern u8 *D_807F6C1C;
extern s32 D_807F6C20;
extern u8 *D_807F6C2C;

typedef struct M55P1_E20 {
    /* 0x000 */ u8 pad0[0x64];
    /* 0x064 */ s32 unk64;
} M55P1_E20;

extern s32 D_8076A0B4;
extern s32 D_8076A0B8;
extern s32 D_8076A0BC;
extern s32 D_8076A0C0;
extern s32 D_8076A0C4;
extern s32 D_8076A0C8;
void *func_80610FE8(s32);

void func_80650E20(M55P1_E20 *arg0) {
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

typedef struct M50ECCMapData {
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
} M50ECCMapData;

typedef struct M50ECCReloc {
    /* 0x0 */ u8 pad0[8];
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
} M50ECCReloc;

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
    /* 0x24 */ u8 pad24[0x4];
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 pad29[0x7];
} M55P5GridPoint;

typedef struct {
    /* 0x00 */ f32 unk0[4];
    /* 0x10 */ f32 unk10[4];
    /* 0x20 */ f32 unk20[4];
} M55P5GridSrc;

extern M55P5GridSrc *D_807F6C14;
extern M55P5GridPoint *D_807F6C24;
extern struct M55P2SearchEntry *D_807F70B0;
extern struct M55P2BoxEntry *D_807F70B4;

void lightSetTargetColor(f32, f32, f32, s16);
void lightCopyTargetColors(s16);
void func_80651904(s32, s32, void *, s32 *, s32, s32);
void func_80651C2C(s32, void *);

#ifdef NON_MATCHING
void func_80650ECC(M50ECCMapData *arg0) {
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
        D_807F70B0 = (struct M55P2SearchEntry *)((u8 *)arg0 + off + 4);
        off = arg0->unk5C;
        D_807F70B4 = (struct M55P2BoxEntry *)((u8 *)arg0 + off + 4);
        off = arg0->unk60;
        D_807F6C14 = (M55P5GridSrc *)((u8 *)arg0 + off);
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
            if (((M50ECCReloc *)D_807F6C0C)[i].unk8 != -1) {
                ((M50ECCReloc *)D_807F6C0C)[i].unk8 += (s32)arg0 + base;
            }
            if (((M50ECCReloc *)D_807F6C0C)[i].unkC != -1) {
                ((M50ECCReloc *)D_807F6C0C)[i].unkC += (s32)arg0 + base;
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651708.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651904.s")

s32 func_80651B64(s16 arg0) {
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

void func_80651BC0(s16 arg0, s8 arg1) {
    D_807F7078[arg0] = arg1;
}

void func_80651BE0(s16 arg0, u8 arg1, u8 arg2) {
    D_807F6C1C[(u32)(arg0 * 2) * 0xA + arg1 * 0xA + 9] = arg2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651C2C.s")

struct M55P2SearchEntry;

void func_8065214C(void) {
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

void func_806521F8(void) {
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

s32 func_806522CC(s16 arg0, s16 arg1, s16 arg2) {
    M55P3EffectBuf *entry;

    entry = (M55P3EffectBuf *)((s32)D_807F6C18 + arg2 * 0x1C8);
    if (entry->unk1 == 0) {
        return 0;
    }
    if ((arg0 >= entry->unk68) && (arg1 >= entry->unk6C) && (entry->unk70 >= arg0) && (entry->unk74 >= arg1)) {
        return 1;
    }
    return 0;
}

typedef struct M55P1_Entry {
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
} M55P1_Entry;

s32 func_806303C4(s32, s32, s32, f32, f32, f32, s32, s32, s32, s32, s32);
s32 func_80630324(s32, s32);
s16 func_806531B8(f32, f32, f32, s32);

void func_80652374(M55P1_Entry *arg0) {
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806524A0.s")

s32 func_80630588(s32, s32, s32, u8 *);

u8 func_80652594(s32 arg0, s16 *arg1, u8 arg2) {
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
struct M55P2SearchEntry;
struct M55P2BoxEntry;
extern u8 D_807F7140;

void func_806307AC(s32);
s32 func_8063070C(s32);
s32 func_80630890(s32, f32, f32, f32, void *);
void func_806323C0(s32);
s32 func_8063A38C(s32, s32, f32, f32, f32);
void func_8063B4C0(void *, s32);
s32 func_80653684(void *, f32, f32);
s32 func_80653804(void *, f32, f32);
void func_80652FDC(f32, f32, f32, s16, s16, s16 *);
s32 func_806533C4(f32, f32, f32);
s32 func_806534E0(f32, f32, f32, s16, u8 *, f32 *);

void func_806526E0(u8 arg0) {
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

void func_80652790(u8 arg0) {
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

void func_80652858(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
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

void func_8065297C(void) {
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
            if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk0 == 1 || arg3) {
                if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk6 != 0) {
                    ((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk24 = 0;
                } else {
                    ((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk24 = func_8063A38C(((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk14, ((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk1C, arg0, arg1, arg2);
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

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ void *next;
} M55P2Node;

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
            if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s4))->unk1 != 0) {
                var_s2 = 1;
            } else {
                var_s2 = 0;
            }
            node = (void *)((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s4))->unk14;
            if (node != NULL) {
                do {
                    next = ((M55P2Node *)node)->next;
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
#define R3bEFF(o) ((M55P3EffectBuf *)((u8 *)D_807F6C18 + (o)))

typedef struct M55P3Node {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ struct M55P3Node *unk14;
    /* 0x18 */ u8 pad18[6];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ u8 unk24;
} M55P3Node;

extern s32 func_80668E9C(s32, s16, f32, f32, f32, s32);

s32 func_80652BC8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    s32 result;
    s32 i;
    s16 x;
    s16 y;
    u8 mode;
    void *ptr;
    M55P3Node *node;

    result = 0;
    mode = func_80630324(1, 0);
    i = 0;
    if (D_807F6C28 > 0) {
        x = (s16)(s32)(arg1 * 6.0f);
        node = ptr;
        do {
            if ((x >= R3bEFF(i * 0x1C8)->unk80 - 0x32) &&
                ((y = (s16)(s32)(arg2 * 6.0f)) >= R3bEFF(i * 0x1C8)->unk82 - 0x32) &&
                (R3bEFF(i * 0x1C8)->unk84 + 0x32 >= x) &&
                (R3bEFF(i * 0x1C8)->unk86 + 0x32 >= y)) {
                switch (mode) {
                case 0:
                    node = (M55P3Node *)R3bEFF(i * 0x1C8)->unk14;
                    break;
                case 1:
                    node = (M55P3Node *)R3bEFF(i * 0x1C8)->unk1C;
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

s32 func_80652E58(s16 arg0) {
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

s32 func_80652EBC(s16 arg0) {
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

s32 func_80652F24(s16 arg0, s16 arg1) {
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

s16 func_80652F9C(f32 arg0, f32 arg1, f32 arg2, s16 arg3) {
    s16 temp;

    func_80652FDC(arg0, arg1, arg2, arg3, -1, &temp);
    return temp;
}

typedef struct M55P2BoxEntry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
} M55P2BoxEntry;

typedef struct M55P2SearchEntry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x12];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[0x3];
} M55P2SearchEntry;

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
    if (func_806534E0(temp_fs0, temp_fs1, temp_fs2, arg3, &sp207, &sp200) != 0) {
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
                if (func_806534E0(temp_fs0, temp_fs1, temp_fs2, var_s1, &sp207, &sp200) != 0) {
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
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad8[0xA];
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13[1];
} M55P2CollNode;

s32 func_806534E0(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, f32 *arg5) {
    M55P2CollNode *var_s0;
    M55P2CollNode *temp_s1;
    M55P3EffectBuf *temp_v0;

    temp_v0 = (M55P3EffectBuf *)((u8 *)D_807F6C18 + arg3 * 0x1C8);
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
    var_s0 = (M55P2CollNode *)temp_v0->unk78;
    temp_s1 = (M55P2CollNode *)temp_v0->unk7C;
    if (var_s0 != temp_s1) {
        do {
            if ((func_80653684(var_s0, arg0, arg2) != 0) && (func_80653804(var_s0, arg0, arg2) != 0)) {
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

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[6];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
} M55P3Box;

s32 func_80653684(void *arg0, f32 arg1, f32 arg2) {
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
    M55P3Box *box;

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80653804.s")


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
} M55P3Player;

extern M55P3Player *D_807FC924;
extern u8 D_807FC929;

void func_80653A70(s16 arg0) {
    D_807F6C18[arg0].unk0 = 1;
    D_807F6C18[arg0].unk1 |= 1 << D_807FC929;
    D_807F6C18[arg0].unk68 = D_807FC924[D_807FC929].unk270;
    D_807F6C18[arg0].unk6C = D_807FC924[D_807FC929].unk272;
    D_807F6C18[arg0].unk70 = D_807FC924[D_807FC929].unk274;
    D_807F6C18[arg0].unk74 = D_807FC924[D_807FC929].unk276;
}


void func_80653B70(s8 arg0) {
    D_807F70AB = arg0;
}

void func_8062AD28(f32, f32, f32, void *, void *);
void func_8062AC68(Mtx *);
void func_8062A944(f32, f32, f32);
void mapUpdateFogDistance(f32 *, s16);
void func_806521F8();
void func_80653A70(s16);
void func_806547A8(f32, f32, f32);
void func_80654380(f32, f32, f32);
void func_80654A2C(f32, f32, f32);
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

void func_80653B80(f32 arg0, f32 arg1, f32 arg2) {
    D_807FC924[D_807FC929].unk290 = func_806531B8(arg0, arg1, arg2, D_807FC924[D_807FC929].unk290);
    if (D_807F70AB != 0) {
        D_807FC924[D_807FC929].unk290 = *(s16 *)((u8 *)D_807FC924[D_807FC929].unk4 + 0x12C);
    }
    mapUpdateFogDistance(&D_807FC924[D_807FC929].unk288, D_807FC924[D_807FC929].unk290);
    D_807F7138 = (s16)(s32)D_807FC924[D_807FC929].unk288;
    func_8062A944(D_807F5FB4, D_807F5FB0, (f32)D_807F7138);
    func_8062AC68((Mtx *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + (D_807444FC << 6) + 8));
    func_8062AD28(arg0, arg1, arg2, &D_807F5E68, &D_807F5E20);
    func_806521F8();
    func_80653A70(D_807FC924[D_807FC929].unk290);
    func_806547A8(arg0, arg1, arg2);
    D_807F6C80 = 0;
    D_807F6C08 = 0;
    func_80656F14(D_807FC924[D_807FC929].unk290, 0, D_807FC924[D_807FC929].unk270, D_807FC924[D_807FC929].unk272, D_807FC924[D_807FC929].unk274, D_807FC924[D_807FC929].unk276, arg0, arg1, arg2);
    func_80654380(arg0, arg1, arg2);
    func_8065F678(arg0, arg1, arg2, D_807FC929);
    actorCalculateTargetDistancesAndAngles(arg0, arg1, arg2);
    func_80655410(arg0, arg1, arg2);
}

extern s32 func_8066B0F8(s32, s32, s32, s32);

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80653DF0.s")


extern void collisionBstLookupByHash(u32, u32 *, u32 *);
extern s32 assetFreeBuffer(void *, s32, s32);

void func_80653EA8(u8 *arg0, u8 *arg1) {
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

void func_80653F68(s16 arg0) {
    D_807F6C18[arg0].unk7 |= 8;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80653FA4.s")

extern void func_80654418(f32, f32, f32);
extern void func_80655258(f32, f32, f32, s32);

void func_80654380(f32 arg0, f32 arg1, f32 arg2) {
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
    func_80654A2C(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654418.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806545D4.s")

typedef struct M55P4Cell {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x12];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 pad1A[2];
} M55P4Cell;

typedef struct M55P4Tri {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
} M55P4Tri;

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806547A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654A2C.s")

void func_80654BC0(s32 arg0, u8 arg1) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    while (!found && i < D_807F70AC) {
        if (arg0 == ((M55P4Cell *)D_807F70B0)[i].unk2) {
            ((M55P4Cell *)D_807F70B0)[i].unk18 = arg1;
            if (arg1 != 0) {
                ((M55P4Cell *)D_807F70B0)[i].unk19 = 1;
            }
            found = 1;
        }
        i++;
    }
    for (i = 0; i < D_807F70AC; i++) {
        if (arg0 == ((M55P4Cell *)D_807F70B0)[i].unk4) {
            func_80654BC0(((M55P4Cell *)D_807F70B0)[i].unk2, arg1);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654CCC.s")

s32 func_80654E84(M55P4Tri *arg0, f32 arg1, f32 arg2) {
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654FEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655258.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655410.s")

typedef struct M55P4Node {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ struct M55P4Node *unk14;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ u8 unk24;
} M55P4Node;

typedef struct {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 unk5;
    /* 0x006 */ u8 pad6[0x0E];
    /* 0x014 */ M55P4Node *unk14;
    /* 0x018 */ u8 pad18[4];
    /* 0x01C */ M55P4Node *unk1C;
    /* 0x020 */ u8 pad20[0x40];
    /* 0x060 */ void *unk60[4];
    /* 0x070 */ u8 pad70[0x158];
} M55P4Effect;


void func_80636164(s32, u8);
void func_80636210(s32, u8);
s32 func_8065E81C(s32, s32);
void heapFree(void *);

void func_80655AD0(void) {
    s32 i;
    s32 off;
    M55P4Effect *eff;

    if (D_807F713A != 0) {
        func_8065E81C(0, 0x190);
    }
    i = 0;
    off = 0;
    while (i < D_807F6C28) {
        eff = (M55P4Effect *)((u8 *)D_807F6C18 + off);
        if (eff->unk3 != 0 && eff->unk5 != 2 && eff->unk4 == 0) {
            if (((M55P4Effect *)D_807F6C18)[i].unk60[D_807444FC] != NULL) {
                heapFree(((M55P4Effect *)D_807F6C18)[i].unk60[D_807444FC]);
                ((M55P4Effect *)D_807F6C18)[i].unk60[D_807444FC] = NULL;
            }
        }
        i++;
        off += 0x1C8;
    }
}

void func_80655BF0(void) {
    M55P4Effect *eff;
    M55P4Node *node;

    if (!func_80652E58(D_807F70AA)) {
        eff = &((M55P4Effect *)D_807F6C18)[D_807F70AA];
        node = eff->unk14;
        if (node) {
            do {
                func_80636164(node->unk0, node->unk24);
                func_80636210(node->unk0, node->unk24);
                node = node->unk14;
            } while (node);
            eff = &((M55P4Effect *)D_807F6C18)[D_807F70AA];
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

s32 func_80655CF8(s16 arg0, s32 arg1) {
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

#ifdef NON_MATCHING
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
} L55DD0Effect;

typedef struct {
    /* 0x000 */ u8 pad0[0x8];
    /* 0x008 */ s32 unk8;
} L55DD0Arg1;

typedef struct {
    /* 0x000 */ u8 pad0[0x8];
    /* 0x008 */ s32 unk8;
    /* 0x00C */ s32 unkC;
} L55DD0WaterEntry;

typedef struct {
    /* 0x000 */ u8 pad0[0x27C];
    /* 0x27C */ f32 unk27C;
    /* 0x280 */ u8 pad280[0x2F0 - 0x280];
} L55DD0PlayerExtra;

#define L55DD0_EFF(i) (((L55DD0Effect *)D_807F6C18)[(i)])
#define L55DD0_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

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
Gfx *effectWaterRenderSurfaces(Gfx *, s16, s16);
Gfx *fogRender(Gfx *);
Gfx *renderDepthSortedTargets(Gfx *);
void func_80658E58();

void func_80655DD0(Gfx *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    s32 flags;
    Gfx *gfx;
    Gfx *v;
    s32 i;
    s16 idx;
    u8 flag;

    flag = (D_807F5FEC != 0);
    if (flag != 0) {
        flag = (((L55DD0PlayerExtra *)D_807FC924)[D_807FC929].unk27C == 45.0);
    }
    L55DD0_WRITE_GFX(arg0, 0xE7000000, 0);
    gfx = arg0 + 1;
    flags = arg5 & 0x10;
    if (flags != 0) {
        L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
        L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)D_807F5DE8));
        L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
        gfx = func_8062CEA8(gfx, arg1, 1);
        if (((L55DD0Arg1 *)arg1)->unk8 != -1) {
            L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
            L55DD0_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((L55DD0Arg1 *)arg1)->unk8));
        }
        gfx = effectWaterRenderSurfaces(gfx, 0, 0);
        for (i = 0; i < D_807F6C08; i++) {
            if (((L55DD0WaterEntry *)(D_807F6C0C + (D_807F6BF0[i] * 0x10)))->unk8 != -1) {
                L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
                L55DD0_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((L55DD0WaterEntry *)(D_807F6C0C + (D_807F6BF0[i] * 0x10)))->unk8));
            }
            if (((L55DD0WaterEntry *)(D_807F6C0C + (D_807F6BF0[i] * 0x10)))->unkC != -1) {
                L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
                L55DD0_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((L55DD0WaterEntry *)(D_807F6C0C + (D_807F6BF0[i] * 0x10)))->unkC));
            }
        }
        L55DD0_WRITE_GFX(gfx++, 0xDA380003, &D_2000180);
    }
    for (i = D_807F6C80 - 1; i >= 0; i--) {
        idx = D_807F6C58[i];
        if (L55DD0_EFF(idx).unk0 == 1) {
            if (L55DD0_EFF(idx).unk2 != 0) {
                func_8062EE48(idx & 0xFF);
                L55DD0_EFF(idx).unk2 = 0;
            }
            L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
            L55DD0_WRITE_GFX(gfx++, ((s32)((f32)L55DD0_EFF(idx).tile.w.unk6C * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)L55DD0_EFF(idx).tile.w.unk68 * 4.0f) & 0xFFF) << 0xC),
                        ((s32)((f32)L55DD0_EFF(idx).tile.w.unk74 * 4.0f) & 0xFFF) | (((s32)((f32)L55DD0_EFF(idx).tile.w.unk70 * 4.0f) & 0xFFF) << 0xC));
            func_80658E58(L55DD0_EFF(idx).tile.h.unk6A, L55DD0_EFF(idx).tile.h.unk6E, L55DD0_EFF(idx).tile.h.unk72, L55DD0_EFF(idx).tile.h.unk76);
            gfx = fogRender(gfx);
            if (flags != 0) {
                gfx = func_8062EDA8(gfx, idx & 0xFF);
                if (L55DD0_EFF(idx).unk2C != -1) {
                    L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
                    L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)L55DD0_EFF(idx).unk58));
                    L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
                    v = (Gfx *)func_80656B98(gfx, idx, 0);
                    L55DD0_WRITE_GFX(v++, 0xE7000000, 0);
                    L55DD0_WRITE_GFX(v++, 0xDA380003, &D_2000180);
                    gfx = v;
                }
                if (L55DD0_EFF(idx).unk34 != -1) {
                    L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
                    L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)L55DD0_EFF(idx).unk58));
                    L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
                    v = (Gfx *)func_80656B98(gfx, idx, 2);
                    L55DD0_WRITE_GFX(v++, 0xE7000000, 0);
                    L55DD0_WRITE_GFX(v++, 0xDA380003, &D_2000180);
                    gfx = v;
                }
            }
            L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
            if (!(D_807FBB64 & 0x01000000)) {
                gfx = func_8065D994(gfx, idx);
            }
            gfx = func_8063A968(gfx, L55DD0_EFF(idx).unk24);
            D_807F6009 = 0xFF;
            gfx = func_80630B70(gfx, (flag != 0) ? L55DD0_EFF(idx).unk18 : L55DD0_EFF(idx).unk14, arg2, arg3, arg4, arg5, idx, flag);
            if (flags != 0) {
                L55DD0_WRITE_GFX(gfx++, 0xD9000000, 0);
                L55DD0_WRITE_GFX(gfx++, 0xD9FFFFFF, 0x200004);
                gfx = fogRender(gfx);
                gfx = func_8062EDA8(gfx, idx & 0xFF);
                if (L55DD0_EFF(idx).unk30 != -1) {
                    L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
                    L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)L55DD0_EFF(idx).unk58));
                    L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
                    v = (Gfx *)func_80656B98(gfx, idx, 1);
                    L55DD0_WRITE_GFX(v++, 0xDA380003, &D_2000180);
                    L55DD0_WRITE_GFX(v++, 0xE7000000, 0);
                    gfx = v;
                }
                if (L55DD0_EFF(idx).unk38 != -1) {
                    L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
                    L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)L55DD0_EFF(idx).unk58));
                    L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
                    v = (Gfx *)func_80656B98(gfx, idx, 3);
                    L55DD0_WRITE_GFX(v++, 0xE7000000, 0);
                    L55DD0_WRITE_GFX(v++, 0xDA380003, &D_2000180);
                    gfx = v;
                }
            }
        }
    }
    if (flags != 0) {
        L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
        L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)D_807F5DE8));
        L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
        gfx = func_8062CEA8(gfx, arg1, 2);
        if (D_807FBB64 & 0x1000) {
            L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
            gfx = func_80027034(gfx);
            L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
        }
        gfx = effectWaterRenderSurfaces(gfx, idx, 1);
        L55DD0_WRITE_GFX(gfx++, 0xDA380003, &D_2000180);
        L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
        gfx = renderDepthSortedTargets(gfx);
    }
    for (i = D_807F6C80 - 1; i >= 0; i--) {
        idx = D_807F6C58[i];
        if (L55DD0_EFF(idx).unk0 == 1) {
            L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
            L55DD0_WRITE_GFX(gfx++, ((s32)((f32)L55DD0_EFF(idx).tile.w.unk6C * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)L55DD0_EFF(idx).tile.w.unk68 * 4.0f) & 0xFFF) << 0xC),
                        ((s32)((f32)L55DD0_EFF(idx).tile.w.unk74 * 4.0f) & 0xFFF) | (((s32)((f32)L55DD0_EFF(idx).tile.w.unk70 * 4.0f) & 0xFFF) << 0xC));
            func_80658E58(L55DD0_EFF(idx).tile.h.unk6A, L55DD0_EFF(idx).tile.h.unk6E, L55DD0_EFF(idx).tile.h.unk72, L55DD0_EFF(idx).tile.h.unk76);
            D_807F6009 = 0xFF;
            gfx = func_80630B70(gfx, (flag != 0) ? L55DD0_EFF(idx).unk20 : L55DD0_EFF(idx).unk1C, arg2, arg3, arg4, arg5, idx, flag);
            if (D_807FBB64 & 0x01000000) {
                gfx = func_8065D994(gfx, idx);
            }
        }
    }
    if (flags != 0) {
        L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
        L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)D_807F5DE8));
        L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
        v = func_8062CEA8(gfx, arg1, 3);
        L55DD0_WRITE_GFX(v++, 0xDA380003, &D_2000180);
        L55DD0_WRITE_GFX(v++, 0xE7000000, 0);
        gfx = v;
    }
    L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
    L55DD0_WRITE_GFX(gfx++, ((s32)((f32)D_807FC924[D_807FC929].unk274 * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)D_807FC924[D_807FC929].unk270 * 4.0f) & 0xFFF) << 0xC),
                ((s32)((f32)D_807FC924[D_807FC929].unk276 * 4.0f) & 0xFFF) | (((s32)((f32)D_807FC924[D_807FC929].unk272 * 4.0f) & 0xFFF) << 0xC));
    func_80658E58(D_807FC924[D_807FC929].unk270, D_807FC924[D_807FC929].unk272, D_807FC924[D_807FC929].unk274, D_807FC924[D_807FC929].unk276);
    D_807F600C = 0;
    gfx = func_80630B70(gfx, D_807F5FFC, arg2, arg3, arg4, arg5, -1, 0);
    func_8065D994(gfx, -1);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655DD0.s")
#endif

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
} M55P5EffectSlot;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3[0x1];
    /* 0x04 */ s32 unk4[4];
    /* 0x14 */ s32 unk14[4];
} M55P5EffectEntry;


#define R2P5_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

#ifdef NON_MATCHING
s32 func_80656B98(arg0, arg1, arg2)
u32 *arg0;
s32 arg1;
u8 arg2;
{
    M55P5EffectEntry *entry;
    struct M55P2SearchEntry *node;
    Gfx *gfx;
    s32 i;
    s32 found;

    gfx = (Gfx *)arg0;
    R2P5_WRITE_GFX(gfx++, 0xE7000000, 0);
    if (((M55P5EffectSlot *)D_807F6C18)[arg1].unk5 != 2) {
        switch (arg2) {
        case 0:
            R2P5_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk2C));
            break;
        case 1:
            R2P5_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk30));
            break;
        case 2:
            R2P5_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk34));
            break;
        case 3:
            R2P5_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk38));
            break;
        }
    } else {
        for (i = 0; i < ((M55P5EffectSlot *)D_807F6C18)[arg1].unk50; i++) {
            if (((M55P5EffectEntry *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk4C)[i].unk4[arg2] == -1) {
                continue;
            }
            found = 0;
            node = D_807F70B0;
            do {
                if (node->unk2 == ((M55P5EffectEntry *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk4C)[i].unk0) {
                    found = 1;
                } else {
                    node++;
                }
            } while (found == 0);
            if (node->unk18 == 0) {
                continue;
            }
            if ((((M55P5EffectEntry *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk4C)[i].unk2 & (1 << arg2)) == 0) {
                continue;
            }
            R2P5_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)((M55P5EffectEntry *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk4C)[i].unk14[arg2]));
            R2P5_WRITE_GFX(gfx++, 0xE7000000, 0);
            R2P5_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((M55P5EffectEntry *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk4C)[i].unk4[arg2]));
            R2P5_WRITE_GFX(gfx++, 0xE7000000, 0);
        }
    }
    return (s32)gfx;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80656B98.s")
#endif

void func_80656E58(s16 arg0, s16 arg1, u8 arg2, u8 arg3) {
    s32 i = 0;
    M55P5EffectSlot *slot = (M55P5EffectSlot *)D_807F6C18 + arg0;

    for (; i < slot->unk50; i++) {
        if (arg1 == ((M55P5EffectEntry *)slot->unk4C)[i].unk0) {
            if (arg3 != 0) {
                ((M55P5EffectEntry *)slot->unk4C)[i].unk2 |= 1 << arg2;
            } else {
                ((M55P5EffectEntry *)slot->unk4C)[i].unk2 &= ~(1 << arg2);
            }
            return;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80656F14.s")

extern u8 D_807F7070;
extern u8 D_807F7060[];

s32 func_806574B8(s32 arg0) {
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


void func_80657508(s32 arg0) {
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


void func_8065756C(s16 arg0) {
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
} M55P5GridDst;



extern void func_80657CB0(s32, f32, f32, f32, f32 *, f32 *, f32 *);
extern void func_80657974(s32, f32, f32, f32, M55P5GridDst *);
extern s32 func_8065776C(u8 *);

s32 func_806575D0(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
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
    func_80657974(arg0, sp7C, sp78, sp74, (M55P5GridDst *)sp4C);
    if (func_8065776C(sp4C)) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_8065776C.s")



void func_80657974(s32 arg0, f32 arg1, f32 arg2, f32 arg3, M55P5GridDst *arg4) {
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

typedef struct R3bXform {
    /* 0x00 */ s64 unk0;
    /* 0x08 */ s64 unk8;
    /* 0x10 */ s64 unk10;
    /* 0x18 */ s64 unk18;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 pad28[8];
} R3bXform;

#define R3bX ((R3bXform *)D_807F6C24)

#ifdef NON_MATCHING
void func_80657CB0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    f32 t;
    f32 a = (f32)(-R3bX[arg0].unk18);

    t = (a - ((f32)R3bX[arg0].unk10 * arg3 + ((f32)R3bX[arg0].unk0 * arg1 + (f32)R3bX[arg0].unk8 * arg2))) / R3bX[arg0].unk24;
    *arg4 = (f32)R3bX[arg0].unk0 * t + arg1;
    *arg5 = (f32)R3bX[arg0].unk8 * t + arg2;
    *arg6 = (f32)R3bX[arg0].unk10 * t + arg3;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80657CB0.s")
#endif

void func_80657E24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 *arg8, s32 *arg9, s32 *arg10, s32 *arg11) {
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

s32 func_80657F14(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 *arg8, s32 *arg9, s32 *arg10, s32 *arg11) {
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

s32 func_80658000(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4) {
    f32 v;

    v = ((f32)R3bX[arg0].unk18 + ((f32)R3bX[arg0].unk0 * arg1 + (f32)R3bX[arg0].unk8 * arg2 + (f32)R3bX[arg0].unk10 * arg3)) / R3bX[arg0].unk20;
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806582F8.s")

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

void func_806588E0(s32 arg0) {
    u8 *p;

    p = (u8 *)func_8066B0F8(0x14, arg0, 1, 1);
    func_80658930(p);
    if (p != NULL) {
        assetFreeBuffer(p, 0xBED, 0x22);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658930.s")

extern s16 D_807F7358;
extern s16 D_807F735A;
extern s16 D_807F735C;
extern s16 D_807F735E;

s32 func_80658B08();

s32 func_80658B08(arg0, arg1, arg2)
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

typedef struct R2P1bP6Entry {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ s16 unk4;
    /* 0x006 */ s16 unk6;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ u8 padA[0x2];
    /* 0x00C */ s32 unkC;
    /* 0x010 */ u8 unk10;
    /* 0x011 */ u8 unk11;
    /* 0x012 */ u8 pad12[0x2];
} R2P1bP6Entry;

extern u8 D_807F72A0;
extern u8 D_807F72B4;
extern R2P1bP6Entry D_807F72B8[];

void func_80658BD0(void) {
    s32 i;

    D_807F72A0 = 0;
    for (i = 0, D_807F72B4 = 0; i < 8; i++) {
        D_807F72B8[i].unk10 = 0;
    }
}

typedef struct R2P6aEntry {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 unkA[2];
    s32 unkC;
    u8 unk10;
    u8 unk11;
    u8 pad12[2];
} R2P6aEntry;

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
    R2P6aEntry *p;

    found = 0;
    i = 0;
    while ((i < 10) && !found) {
        if (((R2P6aEntry *)&D_807F7290)[i].unk10 != 0) {
            i++;
        } else {
            found = 1;
        }
    }
    if (found) {
        p = &((R2P6aEntry *)&D_807F7290)[i];
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
    R2P6aEntry *p;

    p = (R2P6aEntry *)&D_807F7290;
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
    } while (p != (R2P6aEntry *)&D_807F7358);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658CCC.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658DAC.s")


void func_80658E58(arg0, arg1, arg2, arg3)
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658E8C.s")
