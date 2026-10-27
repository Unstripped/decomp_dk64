#include "common.h"

typedef struct {
    void *frame;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} JetpacSprite;

typedef struct {
    JetpacSprite *sprites[2];
    f32 unk8;
    f32 unkC;
    u8 pad10[0x1C - 0x10];
    s32 unk1C;
    u8 pad20[4];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    u8 pad34[4];
    s32 unk38;
    u8 pad3C[4];
    s32 unk40;
    u8 pad44[4];
    void (*unk48)(void *, s32);
} JetpacItem;

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x14 - 0x10];
    JetpacItem items[4];
    u8 pad144[4];
    u8 unk148;
    u8 pad149[0x190 - 0x149];
    void (*unk190)(void *, s32);
} JetpacInner;

f32 jetpacRandFloat(void);
s32 func_80027250(f32, f32, f32, f32, f32, f32, f32, f32);
void func_80025700(void *, s32, s32, void *, s32);
extern s32 D_8002DC68[];
s32 jetpacRandSpawnX(void) {
    return (s32)((jetpacRandFloat() * 200.0f) + 90.0f);
}

s32 func_800274C0(void) {
    return D_8002DC68[(s32)(jetpacRandFloat() * 13.0f) % 13];
}

s32 func_80027510(JetpacItem *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 fa0;
    f32 fa1;

    fa0 = arg0->unk8;
    fa1 = arg0->unkC;
    if (arg0->unk38 == 1) {
        return 0;
    }

    if (arg5 == 0) {
        fa0 += (f32)arg0->unk24;
        fa1 += (f32)arg0->unk28;
    }

    if (arg0->unk1C >= 2) {
        if (func_80027250(fa0, fa1, arg0->unk8 + (f32)arg0->unk2C, arg0->unkC + (f32)arg0->unk30, arg1, arg2, arg3, arg4)) {
            return 1;
        }
    }

    return 0;
}

extern JetpacSprite D_8002D1A0[];
extern JetpacSprite D_8002D230[];
extern JetpacItem D_8002DC9C;
void func_80028B54(s32 *arg0);

void func_800275F4(JetpacInner *arg0) {
    s32 j;
    JetpacItem sp38 = D_8002DC9C;
    s32 i;

    for (i = 0; i < 3; i++) {
        arg0->items[i] = sp38;
        for (j = 0; j < 2; j++) {
            arg0->items[i].sprites[j] = &D_8002D1A0[i * 2 + j];
        }
    }

    func_80028B54((s32 *)arg0);
    arg0->unkC = 0;
    arg0->items[2].unk8 = 168.0f;
    arg0->items[2].unkC = 168.0f;
    arg0->items[0].unk8 = 48.0f;
    arg0->items[0].unkC = 56.0f;
    arg0->items[1].unk8 = 128.0f;
    arg0->items[1].unkC = 80.0f;
}



typedef struct {
    u8 pad0[0x344];
    s32 unk344;
} JetpacGlobal;

extern JetpacGlobal D_8002EC30;

#ifdef NON_MATCHING
typedef struct {
    u8 pad0[8];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 pad1B;
    s32 unk1C;
    u8 pad20[4];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
} J3Item;

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[4];
    s32 unkC;
    s32 unk10;
    u8 pad14[0x144 - 0x14];
    s32 unk144;
} J3Inner;

s32 jetpacCheckLedgeCollision(f32, f32, f32, f32, s32);
s32 func_80027330(f32);
extern s32 D_8002F064;
extern f32 D_8002F050;
extern f32 D_8002F054;
extern f32 D_8002F058;
extern f32 D_8002F05C;
extern s32 D_8002F06C;
extern s32 D_8002F070;
extern s32 D_8002F074;
extern s32 D_8002F078;
void flagSet(s32, s32, s32);
void func_80024E70(s32);
void func_80027D64(void *);
void func_80028340();
#endif

#ifdef NON_MATCHING
void func_80027728(J3Item *arg0) {
    J3Inner *inner = (J3Inner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);

    if (arg0->unk1C == 0) {
        return;
    }
    if (inner->unkC >= 8) {
        return;
    }
    if (arg0->unk34 < 0x14) {
        arg0->unk34 = arg0->unk34 + 1;
        return;
    }
    if (arg0->unk1C == 1) {
        arg0->unk1C = 2;
    }
    if (arg0->unk38 == 0) {
        if (arg0->unk14 > 0.0f && D_8002F064 != 4) {
            f32 x = arg0->unk8;
            s32 hit = jetpacCheckLedgeCollision((f32)arg0->unk24 + x + arg0->unk10, (f32)arg0->unk28 + arg0->unkC + arg0->unk14,
                                                (f32)arg0->unk2C + x + arg0->unk10, (f32)arg0->unk30 + arg0->unkC + arg0->unk14, 0);
            if (hit >= 0) {
                arg0->unkC = *(f32 *)((u8 *)&D_8002EC30 + hit * 0x34 + 0x354) - 16.0f;
                arg0->unk14 = 0.0f;
            } else {
                arg0->unkC = arg0->unkC + arg0->unk14;
            }
        }
        if (D_8002F064 == 3) {
            if (func_80027250(arg0->unk8 + (f32)arg0->unk24, arg0->unkC + (f32)arg0->unk28, arg0->unk8 + (f32)arg0->unk2C, arg0->unkC + (f32)arg0->unk30,
                              D_8002F050 + (f32)D_8002F06C, D_8002F054 + (f32)D_8002F070, D_8002F050 + (f32)D_8002F074,
                              D_8002F054 + (f32)D_8002F078)) {
                arg0->unk38 = 1;
                inner->unk4 += arg0->unk3C;
                func_80024E70(4);
            }
        }
    }
    if (arg0->unk38 == 1) {
        if (D_8002F064 == 4) {
            arg0->unk38 = 0;
            arg0->unk14 = 0.8f;
        } else {
            arg0->unk8 = (D_8002F050 - (f32)2 * D_8002F058 + (f32)D_8002F06C) + (D_8002F074 - D_8002F06C - arg0->unk2C + arg0->unk24) * 0.5;
            arg0->unkC = D_8002F054 - D_8002F05C + (f32)D_8002F078 - (f32)arg0->unk30;
            if (func_80027330(arg0->unk8)) {
                arg0->unk8 = 168.0f;
                arg0->unk38 = 2;
                arg0->unk14 = 0.8f;
            }
        }
    }
    if (arg0->unk38 == 2) {
        arg0->unkC = arg0->unkC + arg0->unk14;
        if (inner->unkC < 2) {
            f32 lim = (f32)(0x98 - (inner->unkC << 4));
            if (lim <= arg0->unkC) {
                arg0->unkC = lim;
                inner->unkC = inner->unkC + 1;
                func_80024E70(2);
                if (inner->unkC < 2) {
                    inner->unk10 = inner->unk10 - 1;
                } else {
                    func_80028340(inner);
                }
            }
        } else if (168.0f <= arg0->unkC) {
            inner->unkC = inner->unkC + 1;
            func_80024E70(2);
            if (inner->unkC < 8) {
                func_80028340(inner);
            } else {
                arg0->unk1C = 0;
            }
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_80027728.s")
#endif


#ifdef NON_MATCHING
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} J3Color;

extern s32 D_8002DCE8;
extern s32 D_8002F3C0;
f32 jetpacRoundFloat(f32);

void func_80027BE8(JetpacItem *arg0, s32 arg1) {
    s32 x;
    s32 y;
    JetpacInner *inner;
    J3Color sp58;
    s32 i;
    JetpacSprite **p;

    *(s32 *)&sp58 = D_8002DCE8;
    inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    if (arg0->unk1C >= 2) {
        x = (s32)arg0->unk8;
        y = (s32)jetpacRoundFloat(arg0->unkC);
        if (arg1 < 3) {
            p = arg0->sprites;
            for (i = 0; i != 2; i++, p++, y += 8) {
                if ((inner->unkC < 8 && inner->unkC + arg1 * 2 + i >= 8) || (inner->unkC == 8 && (D_8002F3C0 & 0x10))) {
                    sp58.g = 0;
                }
                if (*p != NULL) {
                    func_80025700(*p, x, y, &sp58, *(s32 *)((u8 *)arg0 + 0x20));
                }
            }
        } else {
            func_80025700(arg0->sprites[0], x, y, (u8 *)arg0 + 0x18, *(s32 *)((u8 *)arg0 + 0x20));
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_80027BE8.s")
#endif


s32 flagGet(s32, s32);
extern u8 D_8002F3C8;
extern JetpacSprite D_8002D968[];
extern JetpacItem D_8002DCEC;

void func_80027D64(void *arg0) {
    JetpacItem sp24 = D_8002DCEC;
    JetpacItem *item;
    s32 count = 5;

    if (D_8002F3C8 != 0 && *(s32 *)((u8 *)arg0 + 4) >= 5000 && flagGet(0x17B, 0) == 0 && flagGet(0x62, 2) == 0) {
        count = 6;
        sp24.unk40 = count;
    } else {
        sp24.unk40 = (s32)(jetpacRandFloat() * count) + 1;
    }

    item = (JetpacItem *)((u8 *)arg0 + 0x148);
    sp24.sprites[0] = &D_8002D968[sp24.unk40];
    *item = sp24;
    item->unk8 = (f32)func_800274C0();
    *(s32 *)((u8 *)arg0 + 0x144) = jetpacRandSpawnX();
}

#ifdef NON_MATCHING
void func_80027EC0(J3Item *arg0) {
    J3Inner *inner = (J3Inner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    s32 v;
    s32 idx;

    if (inner->unkC == 0) {
        return;
    }
    if (arg0->unk34 < inner->unk144) {
        arg0->unk34 = arg0->unk34 + 1;
        return;
    }
    if (arg0->unk1C == 1) {
        arg0->unk1C = 2;
    }
    if (arg0->unk38 == 0) {
        if (arg0->unk14 > 0.0f) {
            f32 x = arg0->unk8;
            s32 hit = jetpacCheckLedgeCollision((f32)arg0->unk24 + x + arg0->unk10, (f32)arg0->unk28 + arg0->unkC + arg0->unk14,
                                                (f32)arg0->unk2C + x + arg0->unk10, (f32)arg0->unk30 + arg0->unkC + arg0->unk14, 0);
            if (hit >= 0) {
                arg0->unkC = *(f32 *)((u8 *)&D_8002EC30 + hit * 0x34 + 0x354) - 16.0f;
                arg0->unk14 = 0.0f;
            } else {
                arg0->unkC = arg0->unkC + arg0->unk14;
            }
        }
        if (*(s32 *)((u8 *)&D_8002EC30 + 0x78C) == 2 && D_8002F064 == 3) {
            if (func_80027250(arg0->unk8 + (f32)arg0->unk24, arg0->unkC + (f32)arg0->unk28, arg0->unk8 + (f32)arg0->unk2C, arg0->unkC + (f32)arg0->unk30,
                              D_8002F050 + (f32)D_8002F06C, D_8002F054 + (f32)D_8002F070, D_8002F050 + (f32)D_8002F074,
                              D_8002F054 + (f32)D_8002F078)) {
                if (arg0->unk40 == 6) {
                    flagSet(0x62, 1, 2);
                }
                inner->unk4 += arg0->unk3C;
                func_80024E70(3);
                func_80027D64(inner);
                return;
            }
        }
    }

    switch (arg0->unk40) {
    case 6:
        arg0->unk34++;
        v = arg0->unk34 - inner->unk144;
        if (v >= 0x97) {
            func_80027D64(inner);
            return;
        }
        v = v % 24;
        if (v < 12) {
            arg0->unk1A = 0xFF;
            arg0->unk18 = 0;
            arg0->unk19 = 0;
        } else if (v < 24) {
            arg0->unk18 = 0xFF;
            arg0->unk19 = 0xFF;
            arg0->unk1A = 0;
        }
        break;
    case 1:
        arg0->unk34++;
        v = arg0->unk34 - inner->unk144;
        if (v >= 0x1C) {
            v -= 0x1C;
            arg0->unk34 = inner->unk144;
        }
        if (v < 0x1C) {
            idx = v / 4 + 1;
            if (idx & 1) {
                arg0->unk1A = 0xFF;
            } else {
                arg0->unk1A = 0;
            }
            if (idx & 2) {
                arg0->unk18 = 0xFF;
            } else {
                arg0->unk18 = 0;
            }
            if (idx & 4) {
                arg0->unk19 = 0xFF;
            } else {
                arg0->unk19 = 0;
            }
        }
        break;
    case 2:
        arg0->unk18 = 0xFF;
        arg0->unk19 = 0xFF;
        arg0->unk1A = 0;
        break;
    case 5:
        arg0->unk19 = 0xFF;
        arg0->unk18 = 0;
        arg0->unk1A = 0;
        break;
    case 3:
    case 4:
        arg0->unk34++;
        v = arg0->unk34 - inner->unk144;
        if (v >= 0x18) {
            v -= 0x18;
            arg0->unk34 = inner->unk144;
        }
        if (v < 12) {
            arg0->unk18 = 0;
            arg0->unk19 = 0;
            arg0->unk1A = 0;
        } else if (v < 24) {
            arg0->unk18 = 0;
            arg0->unk19 = 0xFF;
            arg0->unk1A = 0xFF;
        }
        break;
    }
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_80027EC0.s")
#endif



typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0xF8 - 0x14];
    JetpacItem item;
} UnkStruct_80028340;

extern JetpacItem D_8002DD38;

void func_80028340(UnkStruct_80028340 *arg0) {
    JetpacItem sp1C = D_8002DD38;
    sp1C.unk8 = (f32)func_800274C0();
    arg0->item = sp1C;
    arg0->unk10 = 3;
}


s32 func_800283EC(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    JetpacInner *inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194);
    s32 unk28 = *(s32 *)((u8 *)inner + 0x28);
    s32 i;
    JetpacItem *item;

    inner = (JetpacInner *)((u8 *)inner + 0x1C);
    if (unk28 < 2) {
        item = inner->items;
        i = 0;
        if (2 - unk28 > 0) {
            do {
                if (func_80027510(item, arg0, arg1, arg2, arg3, 1)) {
                    return 1;
                }
                i++;
                item++;
            } while (i < 2 - inner->unkC);
        }
    }

    if (func_80027510((JetpacItem *)((u8 *)inner + 0xF8), arg0, arg1, arg2, arg3, 0)) {
        return 1;
    }
    if (func_80027510((JetpacItem *)((u8 *)inner + 0x148), arg0, arg1, arg2, arg3, 0)) {
        return 1;
    }

    return 0;
}
void jetpacItemsUpdate(void) {
    u8 *player = (u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194;
    JetpacItem *item = (JetpacItem *)(player + 0x30);
    s32 i = 0;
    s32 count = 4;

    do {
        if (item->unk1C >= 2 && item->unk48 != NULL) {
            item->unk48(item, i);
        }
        i++;
        item++;
    } while (i != count);
}
void func_800285DC(void) {
    JetpacInner *inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    inner->unk190(&inner->unk148, 5);
}

void func_80028634(void) {
    JetpacInner *inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    JetpacItem *item = inner->items;
    s32 i;

    inner->unkC = 8;
    for (i = 0; i < 3; i++, item++) {
        item->unk8 = 168.0f;
        item->unkC = (f32)(i * 16) + 136.0f;
    }
}

#ifdef NON_MATCHING
extern s32 D_80770DF8[];
void func_80024E70(s32);
void func_80024F24(s32, f32);
void func_80024F64(s32);
void func_80024F9C(s32);
void func_800250A0(void);

void func_800286D0(void) {
    s32 i;
    JetpacItem *item;
    f32 spd;
    f32 y;
    f32 t;
    s32 pad;

    item = (JetpacItem *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x30);

    y = item->unkC;
    t = (y - -8.0f) / 144.0f;
    t = (t < 0.0f) ? 0.0f : ((t > 1.0f) ? 1.0f : t);

    if (*(s32 *)((u8 *)&D_8002EC30 + 0x78C) == 1) {
        if (D_80770DF8[1] == 0) {
            func_80024E70(1);
        }
        func_80024F24(1, 1.0f - t * 0.059466f);
        y = item->unkC;
        if (y >= 136.0f) {
            for (i = 0; i < 3; i++) {
                item[i].unk8 = 168.0f;
                item[i].unkC = (f32)(i * 16) + 136.0f;
            }
            func_80024F64(1);
            func_80024F9C(2);
            return;
        }
        spd = 0.4f;
    } else if (*(s32 *)((u8 *)&D_8002EC30 + 0x78C) == 4) {
        if (D_80770DF8[0] == 0) {
            func_80024E70(0);
        }
        t = 1.0f - t;
        func_80024F24(0, t * 0.059466f + 1.0f);
        y = item->unkC;
        if (y < -8.0f) {
            func_80024F64(0);
            func_800250A0();
            return;
        }
        spd = -0.4f;
    }

    t = y + spd;
    for (i = 0; i < 3; i++) {
        item[i].unkC = t;
        t += 16.0f;
    }
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_800286D0.s")
#endif


void func_80028950(void) {
    JetpacInner *inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    JetpacItem *item = inner->items;
    s32 i;

    inner->unkC = 2;
    for (i = 0; i < 3; i++, item++) {
        item->unk8 = 168.0f;
        item->unkC = (f32)(i * 16) + -8.0f;
    }
}

extern s32 D_8002DD88;
typedef struct {
    s32 v;
} J3Word;
extern JetpacSprite D_8002DC38[];
void func_800289EC(void) {
    JetpacItem *item;
    s32 pad;
    J3Word sp44;
    s32 i;

    item = (JetpacItem *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x30);
    sp44 = *(J3Word *)&D_8002DD88;
    if (116.0f > item->unkC) {
        s32 mod = ((s32)item->unkC / 3) % 2;
        s32 idx = (mod > 0) ? mod : -mod;

        func_80025700(&D_8002DC38[idx], (s32)item->unk8, (s32)((item->unkC + 48.0f) + 4.0f), &sp44, 0);
    }

    i = 0;
    do {
        item->unk48(item, i);
        i++;
        item++;
    } while (i != 3);
}

extern void *D_8002D190[];

void func_80028B54(s32 *arg0) {
    s32 x = *arg0 / 4;
    s32 i;

    for (i = 0; i < 6; i++) {
        D_8002D1A0[i].frame = D_8002D190[x % 4];
    }
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 color[4];
    u8 pad14[8];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[4];
    s32 unk30;
} JetpacLedge;

void func_80028BD0(JetpacLedge *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    arg0->unk30 = arg3;
    arg0->unk8 = 0.0f;
    arg0->unkC = 0.0f;
    arg0->unk0 = (f32)arg1;
    arg0->unk4 = (f32)arg2;
    arg0->color[0] = arg4;
    arg0->color[1] = arg5;
    arg0->color[2] = arg6;
    arg0->color[3] = 0xFF;
    arg0->unk20 = arg2;
    arg0->unk1C = arg1;
    arg0->unk28 = (arg0->unk24 = (arg3 * 8) + arg1 + 16, arg2 + 12);
}
extern JetpacLedge D_8002EF80[];
extern JetpacLedge D_8002EFB4[];
extern JetpacLedge D_8002EFE8[];
extern JetpacLedge D_8002F01C[];

void jetpacInitLedges(void) {
    func_80028BD0(D_8002EF80, 0xC0, 0x30, 4, 0, 0xBE, 0);
    func_80028BD0(D_8002EFB4, 0x20, 0x48, 4, 0, 0xBE, 0);
    func_80028BD0(D_8002EFE8, 0x78, 0x60, 2, 0, 0xBE, 0);
    func_80028BD0(D_8002F01C, 0, 0xB8, 0x1E, 0xBE, 0xBE, 0);
}
s32 jetpacCheckLedgeCollision(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    JetpacLedge *ledge = D_8002EF80;
    s32 i;

    for (i = 0; i < 4; i++, ledge++) {
        f32 fv0 = ledge->unk28;
        if (arg4 == 0) {
            fv0 -= 4.0f;
        }
        if (func_80027250(arg0, arg1, arg2, arg3, ledge->unk1C, ledge->unk20, ledge->unk24, fv0)) {
            return i;
        }
    }
    return -1;
}

typedef struct {
    u8 pad0[0x350];
    JetpacLedge ledges[4];
} J3Global;

s32 func_80028E04(s32 arg0, s32 arg1, s32 arg2) {
    JetpacLedge *l = ((J3Global *)&D_8002EC30)->ledges + arg0;

    if (arg1 < l->unk1C) {
        if (arg2 < l->unk1C) {
            return -2;
        }
        return -1;
    }
    if (l->unk24 < arg2) {
        if (l->unk24 < arg1) {
            return 2;
        }
        return 1;
    }
    return 0;
}


void func_80025700(void *, s32, s32, void *, s32);
extern void *D_8002DE68;
extern void *D_8002DE80;
extern void *D_8002DE98;
extern u8 D_8002EF90[];
extern u8 D_8002F060[];

#ifdef NON_MATCHING
void func_80028E88(void) {
    u8 *color_fp = D_8002EF90;
    u8 *color = color_fp;
    void *de80 = &D_8002DE80;
    u8 *base = (u8 *)&D_8002EC30;
    JetpacLedge *ledge = D_8002EF80;

    do {
        s32 x = (s32)*(f32 *)(base + 0x350);
        s32 y = (s32)*(f32 *)(base + 0x354);
        JetpacLedge *cur = ledge;
        s32 j;

        func_80025700(&D_8002DE68, x, y, color_fp, 0);
        j = 0;
        x += 8;
        if (cur->unk30 > 0) {
            do {
                func_80025700(de80, x, y, color, 0);
                j++;
                x += 8;
            } while (j < cur->unk30);
        }
        func_80025700(&D_8002DE98, x, y, color, 0);
        color += 0x34;
        base += 0x34;
        ledge++;
        color_fp += 0x34;
    } while (color != D_8002F060);
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_80028E88.s")
#endif

