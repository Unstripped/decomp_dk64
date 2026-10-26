#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern void *D_807FC924;

void func_807248B0(Actor *arg0, f32 arg1) {
    arg0->unk4->unk34 = arg1;
    arg0->unk4->unk38 = arg1;
    arg0->unk4->unk3C = arg1;
    if (arg0->unk140 != NULL) {
        arg0->unk15E = (u32)((f32)arg0->unk140->unkC * arg1 * 0.5);
    }
}

void *func_80610FE8(s32);
void heapClearBlock(void *);
void heapFreeDeferred(void *);
void func_8072E7DC(s32, void *);
void func_8067AB20(void *, void *, s32, s32, s16 *, s32);

void func_80724994(u8 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    s16 *sp24;
    void *sp20;

    sp24 = func_80610FE8(8);
    heapFreeDeferred(sp24);
    sp24[0] = arg1;
    sp24[1] = arg2;
    sp24[2] = arg3;
    sp24[3] = arg4;
    func_8072E7DC(0xB, &sp20);
    func_8067AB20(0, sp20, 0x01000000, arg0, sp24, 0);
}

s32 func_80724A20(void) {
    s32 found;
    s16 i;

    found = 0;
    i = 0;
    if (D_807FBB70.unk254 > 0) {
        do {
            if (D_807FBB70.unk258[i] == 3) {
                found = 1;
                D_807FBB40->unk154 = D_807FBB70.unk278[i][1];
                D_807FBB40->unk155[0] = 0;
            }
            i++;
        } while (found == 0 && i < D_807FBB70.unk254);
    }
    return found;
}

typedef struct A1Item {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 pad7[3];
} A1Item;

typedef struct A1Group {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ A1Item *unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[0xB];
} A1Group; // size = 0x24

typedef struct A1Table {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ A1Group *unk4;
} A1Table;

extern A1Table *D_80755690;

void func_80724A9C(u8 arg0, u8 arg1, u8 arg2) {
    A1Group *group;
    s16 i;
    u8 idx;

    group = D_80755690->unk4;
    for (i = 0; i < D_80755690->unk0;) {
        idx = arg1;
        if (group->unk18 == arg0) {
            if (idx < group->unk10) {
                if (arg2 != 0) {
                    group->unk14[idx].unk6 |= 0x80;
                } else {
                    group->unk14[idx].unk6 &= 0xFF7F;
                }
            }
            return;
        }
        i++;
        group++;
    }
}

void func_80724B5C(u8 arg0, u8 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    A1Group *group;
    s16 i;
    u8 idx;

    group = D_80755690->unk4;
    for (i = 0; i < D_80755690->unk0;) {
        idx = arg1;
        if (group->unk18 == arg0) {
            if (idx < group->unk10) {
                *arg2 = group->unk14[idx].unk0;
                *arg3 = group->unk14[idx].unk2;
                *arg4 = group->unk14[idx].unk4;
            }
            return;
        }
        i++;
        group++;
    }
}

typedef struct A1View {
    /* 0x00 */ u8 pad0[0xB8];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x2A];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
} A1View;

extern A1View *D_807FBD6C;
#define A1ACT ((A1View *)D_807FBB40)

void func_80724C2C(s16 arg0) {
    s16 angle;

    angle = (D_807FBD6C->unkEE + 0x800) & 0xFFF;
    A1ACT->unkEE = angle;
    A1ACT->unkE6 = angle;
    A1ACT->unkB8 = arg0;
}

extern struct C1NodeList *D_80755694;
void func_80728300(void *, void *, void *);

void func_80724C78(void *arg0) {
    func_80728300(arg0, D_80755690, D_80755694);
}

typedef struct A1Sub4 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u8 *unk1C;
    /* 0x20 */ struct A1Entry10 *unk20;
    /* 0x24 */ struct A1Entry10 *unk24;
} A1Sub4;

typedef struct A1Entry10 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ f32 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} A1Entry10;

#define A1SUB4 ((A1Sub4 *)D_807FBB40->unk4)

void func_80724CA4(s16 arg0, s16 arg1) {
    u8 *table;

    A1SUB4->unk1C = func_80610FE8(arg1 * 8 + 8);
    heapClearBlock(A1SUB4->unk1C);
    table = A1SUB4->unk1C;
    table[0] = 0x7F;
    table[1] = arg0;
    table[arg1 << 3] = 0;
}

void func_80724D28(s16 arg0, s16 arg1) {
    A1Entry10 *table;

    A1SUB4->unk24 = func_80610FE8(arg1 * 0x10 + 0x10);
    heapClearBlock(A1SUB4->unk24);
    table = A1SUB4->unk24;
    table[0].unk0 = arg0;
    table[0].unk1 = arg0 + 1;
    ((u8 *)table)[arg1 << 4] = 0xFF;
}

void func_80724DB0(s16 arg0, s16 arg1) {
    A1Entry10 *table;

    A1SUB4->unk20 = func_80610FE8(arg1 * 0x10 + 0x10);
    heapClearBlock(A1SUB4->unk20);
    table = A1SUB4->unk20;
    table[0].unk4 = 1.0f;
    table[0].unk8 = 1.0f;
    table[0].unkC = 1.0f;
    table[0].unk0 = arg0;
    table[0].unk1 = arg0;
    ((u8 *)table)[arg1 << 4] = 0xFF;
}

typedef struct C1SpawnEntry {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 pad4[0xA];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 padF[9];
} C1SpawnEntry; // size = 0x18

extern C1SpawnEntry D_8075EB80[];

typedef struct A1Tbl18 {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 pad0E[0xA];
} A1Tbl18;

typedef struct A1Cam {
    /* 0x0 */ u8 pad0[2];
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ s16 unk6;
} A1Cam;

typedef struct A1Plr {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x98];
    /* 0x2B4 */ f32 unk2B4;
    /* 0x2B8 */ f32 unk2B8;
    /* 0x2BC */ f32 unk2BC;
} A1Plr;

typedef struct A1S90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x14];
    /* 0x24 */ u8 unk24;
} A1S90;

typedef struct A1S98 {
    /* 0x00 */ u8 pad0[0x44];
    /* 0x44 */ u8 unk44;
} A1S98;

f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
s16 func_806CC190(s16, s16, f32);
extern u8 D_807444EC;
#define A1PLR ((A1Plr *)D_807FC924)
#define A1DC90 ((A1S90 *)D_807FDC90)
#define A1DC98 ((A1S98 *)D_807FDC98)
#define A1CAM(a) ((A1Cam *)((A1Sub4 *)(a)->unk4)->unk1C)

void func_80724E48(u8 arg0) {
    f32 angle;
    f32 sp38;
    f32 sp34;
    A1Cam *sp30;
    f32 sp2C;
    f32 sp28;
    s32 pitchArg;
    s16 res;

    sp38 = 0.0f;
    angle = 0.0f;
    if (arg0 == 8) {
        pitchArg = 0x46;
        sp34 = D_807FBB4C->unkE6 * 3.1415927f * (1.0 / 2048.0);
        sp30 = A1CAM(D_807FBB4C);
        sp28 = 1.0431069f;
    } else {
        sp34 = D_807FBB40->unkE6 * 3.1415927f * (1.0 / 2048.0);
        sp30 = A1CAM(D_807FBB40);
        pitchArg = ((A1Tbl18 *)D_8075EB80)[A1DC98->unk44].unkD;
        sp28 = ((A1Tbl18 *)D_8075EB80)[A1DC98->unk44].unkC * 4 * 3.1415927f * (1.0 / 2048.0);
        if (pitchArg == 0xFF) {
            pitchArg = 0x3E8;
        }
    }
    if ((s32)sp30 != 0) {
        sp2C = (f64)(u32)sp30->unk4 / 65535.0 * 6.2831854820251465;
        if (D_807444EC == 1 && arg0 != 5 && arg0 != 7) {
            arg0 = 6;
        }
        switch (arg0) {
            case 8:
                sp38 = mathCalculatePitchAngle(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, D_807FBB4C->unk7C, D_807FBB4C->unk80, D_807FBB4C->unk84, pitchArg);
                angle = mathAngleBetweenPointsRad(D_807FBB40->unk7C, D_807FBB40->unk84, D_807FBB4C->unk7C, D_807FBB4C->unk84) - sp34;
                break;
            case 7:
                sp38 = mathCalculatePitchAngle(D_807FDC94->unk7C, D_807FDC94->unk80, D_807FDC94->unk84, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, pitchArg);
                angle = mathAngleBetweenPointsRad(D_807FDC94->unk7C, D_807FDC94->unk84, D_807FBB40->unk7C, D_807FBB40->unk84) - sp34;
                break;
            case 6:
                sp38 = mathCalculatePitchAngle(A1PLR->unk210, A1PLR->unk214, A1PLR->unk218, D_807FBB40->unk7C, D_807FBB40->unk80 + (u32)D_807FBB40->unk15E, D_807FBB40->unk84, pitchArg);
                angle = mathAngleBetweenPointsRad(A1PLR->unk210, A1PLR->unk218, D_807FBB40->unk7C, D_807FBB40->unk84) - sp34;
                break;
            case 0:
                sp38 = mathCalculatePitchAngle(A1PLR->unk2B4, A1PLR->unk2B8, A1PLR->unk2BC, D_807FBB40->unk7C, D_807FBB40->unk80 + (u32)D_807FBB40->unk15E, D_807FBB40->unk84, pitchArg);
            case 1:
                angle = mathAngleBetweenPointsRad(A1PLR->unk2B4, A1PLR->unk2BC, D_807FBB40->unk7C, D_807FBB40->unk84) - sp34;
                break;
            case 2:
                angle = A1DC90->unk24 * 2 * 0.017453292f;
                break;
            case 3:
                sp38 = mathCalculatePitchAngle(A1DC90->unkA, A1DC90->unkC, A1DC90->unkE, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, pitchArg);
                angle = mathAngleBetweenPointsRad(A1DC90->unkA, A1DC90->unkE, D_807FBB40->unk7C, D_807FBB40->unk84) - sp34;
                break;
        }
        if (angle < 0.0f) {
            angle += 6.2831855f;
        }
        if (sp28 != 0.0f) {
            if (sp28 < angle && angle <= 3.1415927f) {
                angle = sp28;
                if (sp2C > 3.1415927f) {
                    angle = sp28 + 6.2831855f;
                }
            } else if (angle < 6.2831855f - sp28 && angle > 3.1415927f) {
                angle = 6.2831855f - sp28;
                if (sp2C < 3.1415927f) {
                    angle = angle - 6.2831855f;
                }
            }
        }
        if (angle > 3.1415927f) {
            angle -= 6.2831855f;
        }
        if (sp2C > 3.1415927f) {
            sp2C -= 6.2831855f;
        }
        res = func_806CC190((s32)(sp2C * 2048.0 / 3.1415927410125732), (s32)(angle * 2048.0 / 3.1415927410125732), 5.0f);
        sp30->unk2 = (u32)(sp38 / 6.2831855f * 65535.0);
        sp30->unk4 = (u32)(res / 4095.0 * 65535.0);
        sp30->unk6 = 0;
    }
}

#ifdef NON_MATCHING
s32 func_807255A8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, f32 *arg8, f32 *arg9) {
    f32 a1;
    f32 b1;
    f32 c1;
    f32 a2;
    f32 b2;
    f32 c2;
    f32 d1;
    f32 d2;
    f32 d3;
    f32 d4;
    f32 det;
    f32 half;
    f32 y;
    f32 two;
    s16 ix;

    a1 = arg3 - arg1;
    b1 = arg0 - arg2;
    c1 = arg2 * arg1 - arg0 * arg3;
    d3 = arg4 * a1 + b1 * arg5 + c1;
    d4 = arg6 * a1 + b1 * arg7 + c1;
    if (d3 != 0.0f && d4 != 0.0f && ((s32)((u32)d3 ^ (u32)d4)) >= 0) {
        return 0;
    }
    a2 = arg7 - arg5;
    b2 = arg4 - arg6;
    c2 = arg6 * arg5 - arg4 * arg7;
    d1 = arg0 * a2 + b2 * arg1 + c2;
    d2 = arg2 * a2 + b2 * arg3 + c2;
    if (d1 != 0.0f && d2 != 0.0f && ((s32)((u32)d1 ^ (u32)d2)) >= 0) {
        return 0;
    }
    det = a1 * b2 - a2 * b1;
    if (det == 0.0f) {
        return 2;
    }
    two = 2.0f;
    if (det < 0.0f) {
        half = -det / two;
    } else {
        half = det / two;
    }
    if (b1 * c2 < b2 * c1) {
        *arg8 = ((b1 * c2 - b2 * c1) - half) / det;
    } else {
        *arg8 = ((b1 * c2 - b2 * c1) + half) / det;
    }
    if (a2 * c1 < a1 * c2) {
        y = ((a2 * c1 - a1 * c2) - half) / det;
    } else {
        y = ((a2 * c1 - a1 * c2) + half) / det;
    }
    *arg9 = y;
    ix = (s32)*arg8;
    if ((ix == arg0 && (s16)(s32)y == arg1) || (ix == arg2 && (s16)(s32)y == arg3) || (ix == arg4 && (s16)(s32)y == arg5) || (ix == arg6 && (s16)(s32)y == arg7)) {
        return 3;
    }
    return 1;
}

#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807255A8.s")
#endif

u8 func_80725B38(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 ret;

    ret = arg0 >= arg2;
    if (ret != 0) {
        ret = arg4 >= arg0;
        if (ret != 0) {
            ret = arg1 >= arg3;
            if (ret != 0) {
                ret = arg5 >= arg1;
            }
        }
    }
    return ret;
}

s32 func_807255A8(s16, s16, s16, s16, s16, s16, s16, s16, f32 *, f32 *);

typedef struct A1PolyVert {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} A1PolyVert;

typedef struct A1Poly {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 count;
    /* 0xA */ u8 padA[2];
    /* 0xC */ A1PolyVert *verts;
} A1Poly;

u8 func_80725BA4(s16 arg0, s16 arg1, A1Poly *arg2) {
    s32 res;
    f32 sp68;
    f32 sp64;
    s16 hits;
    s16 i;
    u8 edgeHits;

    hits = 0;
    if (func_80725B38(arg0, arg1, arg2->unk0, arg2->unk2, arg2->unk4, arg2->unk6)) {
        edgeHits = 0;
        i = 1;
        if (arg2->count >= 2) {
            do {
                if (i + 1 != arg2->count) {
                    res = func_807255A8(arg0, arg1, -0x8000, -0x8000, arg2->verts[i].x, arg2->verts[i].z, arg2->verts[i + 1].x, arg2->verts[i + 1].z, &sp68, &sp64);
                } else {
                    res = func_807255A8(arg0, arg1, -0x8000, -0x8000, arg2->verts[i].x, arg2->verts[i].z, arg2->verts[1].x, arg2->verts[1].z, &sp68, &sp64);
                }
                hits += res != 0;
                if (res == 3) {
                    edgeHits++;
                }
                i++;
            } while (i < arg2->count);
        }
        if (edgeHits != 0 && !(edgeHits & 1) && hits == edgeHits) {
            hits--;
        }
    }
    return hits & 1;
}

void func_8061F2B8(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);

s32 func_80725DC0(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6) {
    f32 outX;
    f32 outY;
    f32 outZ;

    func_8061F2B8(arg4, 0.0f, arg5, arg0, 0.0f, arg1, arg2, 0.0f, arg3, &outX, &outY, &outZ);
    return ((outX - arg4) * (outX - arg4) + (outZ - arg5) * (outZ - arg5) < (f32)(arg6 * arg6)) & 0xFF;
}

typedef struct C1ActorView {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 pad5E[0xC];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x30];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x3C];
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[0x26];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ void *unk174;
} C1ActorView;

typedef struct C1Link {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ C1ActorView *unk1C;
} C1Link;

typedef struct C1Node {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 padA[7];
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 pad15[3];
    /* 0x18 */ C1ActorView *unk18;
    /* 0x1C */ C1Link *unk1C;
    /* 0x20 */ u8 (*unk20)[2];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 pad26[0x16];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 unk42;
    /* 0x43 */ u8 unk43;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45;
    /* 0x46 */ u16 unk46;
} C1Node; // size = 0x48

typedef struct C1NodeList {
    /* 0x0 */ s16 count;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ C1Node *nodes;
} C1NodeList;

#define C1ACT44 ((C1ActorView *)D_807FBB44)

extern C1NodeList *D_80755694;
s32 actorSpawn(s32, s32);
void func_80726744(void *, void *);

typedef struct F1Ent {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 flags;
    /* 0x7 */ u8 radius;
    /* 0x8 */ u8 height;
    /* 0x9 */ u8 pad9;
    /* 0xA */ s16 unkA;
} F1Ent; // size = 0xC? (stride 0xA)

typedef struct F1Tbl {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 count8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ u8 *entsC;
    /* 0x10 */ s16 count10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ u8 *ents14;
} F1Tbl;

#define F1ENT(t, i) ((F1Ent *)((t)->ents14 + (i) * 0xA))


s32 func_80725DC0(s16, s16, s16, s16, s16, s16, s16);
#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80725ED4.s")

typedef struct F1Pt6 {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} F1Pt6;


s32 func_80726164(Actor *arg0, s16 arg1, s16 arg2, s16 arg3, F1Tbl *arg4) {
    s32 res;
    f32 f1;
    f32 f2;
    f32 x;
    f32 y;
    f32 z;
    s16 i;
    s16 cross;
    u8 edges;

    cross = 0;
    edges = 0;
    x = arg0->unk7C;
    y = arg0->unk80 + (f32)(u32)arg0->unk15E;
    z = arg0->unk84;
    for (i = 1; i < arg4->count8; i++) {
        if ((i + 1) != arg4->count8) {
            res = func_807255A8(arg1, arg3, -0x8000, -0x8000, ((F1Pt6 *)arg4->entsC)[i].x, ((F1Pt6 *)arg4->entsC)[i].z, ((F1Pt6 *)arg4->entsC)[i + 1].x, ((F1Pt6 *)arg4->entsC)[i + 1].z, &f1, &f2);
        } else {
            res = func_807255A8(arg1, arg3, -0x8000, -0x8000, ((F1Pt6 *)arg4->entsC)[i].x, ((F1Pt6 *)arg4->entsC)[i].z, ((F1Pt6 *)arg4->entsC)[1].x, ((F1Pt6 *)arg4->entsC)[1].z, &f1, &f2);
        }
        cross += (res != 0);
        if (res == 3) {
            edges++;
        }
    }
    if (edges != 0) {
        if (!(edges & 1) && (cross == edges)) {
            cross--;
        }
    }
    res = 1;
    if (cross & 1) {
        for (i = 0; res && i < arg4->count10; i++) {
            if (!(F1ENT(arg4, i)->flags & 0x80)) {
                if (((F1ENT(arg4, i)->flags & 0x7F) == 0) || ((F1ENT(arg4, i)->flags & 0x7F) == 5)) {
                    if (func_80725DC0((s32)x, (s32)z, arg1, arg3, F1ENT(arg4, i)->x, F1ENT(arg4, i)->z, F1ENT(arg4, i)->radius) != 0) {
                        if (((f32)F1ENT(arg4, i)->y <= y) && (y <= (f32)(F1ENT(arg4, i)->height + F1ENT(arg4, i)->y))) {
                            res = 0;
                        }
                    }
                }
            }
        }
    } else {
        res = 0;
    }
    return res;
}

#ifdef NON_MATCHING
void func_806755A8(s32, s32, s32, s32, void *, void *);

s32 func_807264B0(Actor *arg0, s32 arg1, s32 arg2, F1Tbl *arg3) {
    f32 x;
    f32 y;
    f32 z;
    s16 i;
    s32 found;
    F1Ent *e;

    arg0->unkF4 = 0;
    arg0->unkF6 = 0xFFF;
    found = 0;
    x = arg0->unk7C;
    y = arg0->unk80;
    z = arg0->unk84;
    for (i = 0; i < arg3->count10; i++) {
        e = F1ENT(arg3, i);
        if (!((e->flags & 0xFFFF) & 0x80)) {
            if (((e->flags & 0x7F) == 0) || ((e->flags & 0x7F) == 1) ||
                (((e->flags & 0x7F) == 5) && ((f64)arg0->unkB8 < (f64)(u32)((u8 *)D_807FDC9C)[0xD] * 1.4))) {
                if (((f32)e->y <= y) && (y <= (f32)(e->y + e->height))) {
                    if (e->flags) {
                    }
                    if (((x - (f32)e->x) * (x - (f32)e->x)) + ((z - (f32)e->z) * (z - (f32)e->z)) < (f32)(e->radius * e->radius)) {
                        func_806755A8((s32)x, (s32)z, e->x, e->z, &arg0->unkF4, &arg0->unkF6);
                        found = 1;
                        arg0->unkFC = 1;
                        arg0->unkFD = 1;
                    }
                }
            }
        }
    }
    return found;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807264B0.s")
#endif

typedef struct F1Pt {
    /* 0x0 */ u8 pad0[2];
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
} F1Pt;

void func_807266E8(Actor *arg0, F1Pt *arg1) {
    arg0->unk7C = arg1->unk4;
    arg0->unk80 = arg1->unk6;
    arg0->unk8C = arg1->unk6;
    arg0->unk84 = arg1->unk8;
    arg0->unkE6 = arg1->unk2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80726744.s")

u8 func_80726DEC(u8, u8);

u8 func_80726D7C(u8 arg0) {
    return func_80726DEC(arg0, 5) || func_80726DEC(arg0, 6);
}

u8 func_80726DC0(u8 arg0) {
    return func_80726DEC(arg0, 7);
}

u8 func_80726DEC(u8 arg0, u8 arg1) {
    s16 i;
    C1Node *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (node->unk13 == arg0) {
            return node->unk42 == arg1;
        }
    }
    return 0;
}

void func_80726E60(u16 arg0, u8 arg1) {
    s16 i;
    C1Node *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (node->unk42 == 5) {
            if (node->unk18->unk5C & arg0) {
                node->unk18->unk154 = arg1;
            }
        }
    }
}

#ifdef NON_MATCHING
void actorDespawn(void *);
void actorQueueDelayedCallback(void *, s32, s32, s32, s32, s32, s32);
void func_8061CFCC(void *);

void func_80726EE0(u8 arg0) {
    s16 i;
    C1Node *node;
    s32 mode;
    u32 sel;

    mode = arg0;
    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (node->unk46 & 0x80) {
            continue;
        }
        sel = mode;
        if ((node->unk42 == 5) && (node->unk18->unk5C & 2)) {
            actorQueueDelayedCallback(node->unk18, 0, 8, 0, 0, 0, 1);
        } else if ((node->unk42 == 6) && (node->unk18->unk5C & 2)) {
            node->unk42 = 7;
            node->unk24 = node->unk14 * 0x1E;
            func_8061CFCC(node->unk18);
            actorDespawn(node->unk18);
        }
        switch (sel) {
            case 0:
            case 1:
                node->unk46 |= 2;
                break;
            case 2:
                node->unk46 &= ~2;
                break;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80726EE0.s")
#endif

Actor *func_807270C0(s16, u16);

void func_8072707C(s16 arg0, u8 arg1, u16 arg2) {
    C1ActorView *a = (C1ActorView *)func_807270C0(arg0, arg2);

    if (a != NULL) {
        a->unk154 = arg1;
        a->unk155 = 0;
    }
}

void actorRegisterActive(void *);

Actor *func_807270C0(s16 arg0, u16 arg1) {
    s16 i;
    C1Node *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (arg0 == node->unk13) {
            if (node->unk42 == 5) {
                node->unk46 |= arg1;
                return (Actor *)node->unk18;
            } else if ((node->unk42 == 6) && (arg1 & 0x400)) {
                actorRegisterActive(node->unk18);
                node->unk42 = 5;
                return (Actor *)node->unk18;
            }
        }
    }
    return 0;
}

u8 func_80727194(C1ActorView *arg0) {
    s16 i;
    C1Node *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if ((arg0 == node->unk18) && (node->unk42 == 5)) {
            return node->unk13;
        }
    }
    return 0;
}

Actor *func_807271F4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6) {
    s16 i;
    C1Node *node;
    C1SpawnEntry *entry;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if ((arg0 == node->unk13) && (node->unk42 != 5)) {
            entry = &D_8075EB80[node->unk44];
            if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                node->unk46 |= 4;
                func_80726744(D_807FBB44, node);
                if (arg1 != 0) {
                    C1ACT44->unk7C = arg1;
                    C1ACT44->unk80 = arg2;
                    C1ACT44->unk84 = arg3;
                    C1ACT44->unkEE = arg4;
                    C1ACT44->unkE6 = arg4;
                }
                C1ACT44->unkB8 = arg5;
                C1ACT44->unkC0 = arg6;
                C1ACT44->unk6A = 0;
                return D_807FBB44;
            }
        }
    }
    return 0;
}

typedef struct C1Pt {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 pad6[4];
} C1Pt; // size = 0xA

typedef struct C1Tbl98 {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ u8 (*unk20)[2];
} C1Tbl98;

typedef struct C1TblA0 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 *unk14;
} C1TblA0;

extern C1TblA0 *D_807FDCA0;
f32 mathAngleBetweenPointsDeg(s32, s32, s16, s16);
s32 func_80611A44(void);

#define C1PTS ((C1Pt *)D_807FDCA0->unk14)
#define C1PT(i) ((C1Pt *)(D_807FDCA0->unk14 + (i)))

#define C1IDX (((C1Tbl98 *)D_807FDC98)->unk20[arg1][0] * 0xA)

void func_807273A8(s16 arg0, u8 arg1) {
    u8 tbl;
    s16 sp34;

    tbl = ((C1Tbl98 *)D_807FDC98)->unk20[arg1][0];
    sp34 = (s16)(s32)((mathAngleBetweenPointsDeg((s32)D_807FDC94->unk7C, (s32)D_807FDC94->unk84, C1PTS[tbl].x, C1PTS[tbl].z) * 4096.0f) / 360.0f);
    if (func_807271F4(arg0, C1PTS[tbl].x, C1PTS[tbl].y, C1PTS[tbl].z, sp34, ((func_80611A44() >> 0xF) % 100) + 0x64, ((func_80611A44() >> 0xF) % 100) + 0xC8) != 0) {
        C1ACT44->unk154 = 0x17;
        C1ACT44->unk155 = 0;
    }
}

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_8072752C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8) {
    s16 sp46;
    f32 sp40;
    s32 dx;
    s32 dy;
    s32 dz;

    dx = arg4 - arg1;
    dy = arg5 - arg2;
    dz = arg6 - arg3;
    sp46 = mathAngleBetweenPoints2D((f32)arg4, (f32)arg6, (f32)arg1, (f32)arg3);
    sp40 = sqrtf((f32)((dx * dx) + (dy * dy) + (dz * dz)));
    dy = (s32)(sqrtf((f32)((dx * dx) + (dz * dz))) / (sp40 / (f32)arg7));
    if (func_807271F4(arg0, arg1, arg2, arg3, sp46, dy, arg8) != 0) {
        C1ACT44->unk154 = 0x17;
        C1ACT44->unk155 = 0;
    }
}

extern s32 D_8076A0A8;
s32 func_807317FC(s16, s16);

void func_80727678(void) {
    s32 pad;
    s16 sp4A;
    C1Node *node;
    s16 j;
    s16 *ptr;
    C1SpawnEntry *entry;

    node = D_80755694->nodes;
    for (sp4A = 0; sp4A < D_80755694->count; sp4A++, node++) {
        for (j = 0; j < D_807FBB70.unk254; j++) {
            ptr = D_807FBB70.unk278[j];
            if (node->unk13 == *ptr) {
                switch (D_807FBB70.unk258[j]) {
                    case 1:
                        if ((node->unk42 == 0) && (func_807317FC(((s16 *)&D_8076A0A8)[1], node->unk13) != 0) && (entry = &D_8075EB80[node->unk44], actorSpawn(entry->unk0, entry->unk2) != 0)) {
                            func_80726744(D_807FBB44, node);
                        } else if ((node->unk42 == 3) && (func_807317FC(((s16 *)&D_8076A0A8)[1], node->unk13) != 0)) {
                            entry = &D_8075EB80[node->unk44];
                            if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                                func_80726744(D_807FBB44, node);
                                C1ACT44->unk154 = 0x36;
                            }
                        }
                        break;
                    case 2:
                        if (node->unk42 == 7) {
                            node->unk42 = node->unk12;
                        }
                        break;
                    case 3:
                    case 4:
                        if (node->unk42 == 5) {
                            func_8067AB20(D_807FBB40, node->unk18, 0x01000000, D_807FBB70.unk258[j] & 0xFF, ptr, 0);
                        }
                        break;
                }
            }
        }
    }
}

extern u8 D_80755698[];
extern Struct807FD580 *D_807FD580;

void func_807278C0(C1Node *arg0) {
    u8 temp_v0;

    if ((D_8076A0A8 == 0x30) && (D_807FD580->unk1F0 & 0x100000) && (temp_v0 = arg0->unk0, (D_80755698[temp_v0] != 0xA))) {
        switch (temp_v0) {
            case 28:
                arg0->unk44 = 0x63;
                return;
            case 9:
                arg0->unk44 = 0x54;
                return;
            case 44:
                arg0->unk44 = 0x67;
                return;
        }
    } else {
        arg0->unk44 = arg0->unk0;
    }
}

typedef struct C1State90 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ C1ActorView *unk4;
    /* 0x08 */ u8 pad8[0x10];
    /* 0x18 */ u16 unk18;
} C1State90;

typedef struct C1Sub174 {
    /* 0x00 */ u8 pad0[0xD4];
    /* 0xD4 */ s16 unkD4;
} C1Sub174;

typedef struct C1PlayerView {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ C1ActorView *unk4;
    /* 0x008 */ u8 pad8[0x208];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xD4];
} C1PlayerView; // size = 0x2F0

#define C1S90 ((C1State90 *)D_807FDC90)
#define C1PLAYERS ((C1PlayerView *)D_807FC924)
#define C1ACT40 ((C1ActorView *)D_807FBB40)

extern s16 D_8076A0AA;
extern s32 D_807FBB64;
extern u8 D_807FC928;
void actorDeregisterActive(void *);
void actorDespawn(void *);
void func_8061CFCC(void *);
s16 func_806531B8(f32, f32, f32, s32);
u8 func_80727F20(C1Node *, s32);
u8 func_80728004(C1Node *, s32);
u8 func_807280C8(C1Node *, s32);
u8 func_8072818C(C1Node *, s32);
void sfxStopChannel(s32, s32);
void sfxStopSlotSound(void *, s32);

void func_80727958(void) {
    s16 i;
    C1Node *node;
    s32 dist;
    u8 active;
    s32 best;
    s16 p;
    C1SpawnEntry *entry;
    C1ActorView *pa;
    f32 dz;
    f32 dx;
    s32 d;
    C1Sub174 *sub;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        active = (node->unk42 >= 5) && (node->unk42 < 7);
        if (active) {
            D_807FDC90 = (Struct807FDC90 *)node->unk18->unk174;
        }
        dist = D_8075EB80[node->unk44].unkE * 0x64;
        dist = dist * dist;
        if (active) {
            node->unk40 = node->unk18->unk12C;
        }
        if ((dist == 0) || (node->unk46 & 4) || (D_807FBB64 & 0x100)) {
            dist = 0x7FFFFFFF;
        }
        if (active && (node->unk18->unk154 == 0x3B)) {
            func_8061CFCC(node->unk18);
            actorDespawn(node->unk18);
            node->unk42 = 0;
        } else if (active && (node->unk18->unk154 == 0x3C)) {
            func_8061CFCC(node->unk18);
            actorDespawn(node->unk18);
            node->unk42 = node->unk12;
            node->unk46 &= 0xFFFB;
        } else if ((node->unk42 == 7) && (node->unk24 != 0)) {
            if (!(node->unk46 & 2)) {
                node->unk24 -= 1;
                if (node->unk24 == 0) {
                    node->unk43 += 1;
                    node->unk42 = node->unk12;
                    node->unk40 = func_806531B8((f32)node->unk4, (f32)node->unk6, (f32)node->unk8, 0);
                    func_807278C0(node);
                    entry = &D_8075EB80[node->unk44];
                    if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                        func_80726744(D_807FBB44, node);
                        C1ACT44->unk154 = 0x36;
                        node->unk46 |= 1;
                    }
                }
            }
        } else if (node->unk42 == 2) {
            if ((func_80727F20(node, dist) != 0) && (func_807317FC(D_8076A0AA, node->unk13) != 0)) {
                func_807278C0(node);
                entry = &D_8075EB80[node->unk44];
                if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                    func_80726744(D_807FBB44, node);
                }
            }
        } else if (active && (node->unk18->unk154 == 0x40)) {
            node->unk42 = 7;
            node->unk24 = node->unk14 * 0x1E;
            if (node->unk1C->unk1C == node->unk18) {
                node->unk1C->unk1C = 0;
            }
            func_8061CFCC(node->unk18);
            actorDespawn(node->unk18);
        } else if (active) {
            best = 0xF423F;
            if ((C1S90->unk4->unk5C & 1) && (C1S90->unk4->unk154 == 0x67)) {
                if ((node->unk18->unk5C & 2) && (node->unk42 == 5)) {
                    if ((node->unk18->unk154 != 0x16) && (node->unk18->unk154 != 0x37) && !(node->unk46 & 0x40)) {
                        node->unk18->unk154 = 0x16;
                        node->unk18->unk155 = 0;
                    }
                }
            }
            if (D_807FC928 >= 2) {
                for (p = 0; p < D_807FC928; p++) {
                    sub = (C1Sub174 *)C1PLAYERS[0].unk4->unk174;
                    dz = C1ACT40->unk84 - C1PLAYERS[p].unk4->unk84;
                    dx = C1ACT40->unk7C - C1PLAYERS[p].unk4->unk7C;
                    d = (s32)((dz * dz) + (dx * dx));
                    if ((d < best) || (sub->unkD4 != 0)) {
                        pa = C1PLAYERS[p].unk4;
                        best = d;
                        C1S90->unk4 = pa;
                    }
                }
            }
            if (node->unk42 == 6) {
                if (func_8072818C(node, dist) != 0) {
                    actorDespawn(node->unk18);
                    node->unk42 = node->unk12;
                } else if (func_80728004(node, dist) != 0) {
                    actorRegisterActive(node->unk18);
                    node->unk42 = 5;
                    node->unk46 |= 0x8000;
                }
            } else if ((node->unk42 == 5) && (func_807280C8(node, dist) != 0)) {
                if ((node->unk18->unk154 != 0x16) && (node->unk18->unk154 != 0x37)) {
                    if (node->unk18->unk58 == 0xF8) {
                        sfxStopChannel(0x42, 0);
                    }
                    sfxStopSlotSound(node->unk18, 0);
                    sfxStopSlotSound(node->unk18, 1);
                    actorDeregisterActive(node->unk18);
                    node->unk42 = 6;
                    C1S90->unk18 = 0;
                }
            }
        }
    }
}

s32 mapChunkIsVisibleForPlayer(s32, s16);

u8 func_80727F20(C1Node *arg0, s32 arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = C1PLAYERS[0].unk218 - arg0->unk8;
    dx = C1PLAYERS[0].unk210 - arg0->unk4;
    dy = C1PLAYERS[0].unk214 - arg0->unk6;
    ret = 0;
    if (((dz * dz) + ((dx * dx) + (dy * dy))) < arg1) {
        ret = 1;
    }
    if (ret) {
        ret = D_80755698[arg0->unk44] == 6;
        if (!ret) {
            ret = (arg0->unk46 & 0x20) != 0;
            if (!ret) {
                ret = mapChunkIsVisibleForPlayer(0, arg0->unk40) != 0;
            }
        }
    }
    return ret;
}

u8 func_80728004(C1Node *arg0, s32 arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = C1PLAYERS[0].unk218 - arg0->unk18->unk84;
    dx = C1PLAYERS[0].unk210 - arg0->unk18->unk7C;
    dy = C1PLAYERS[0].unk214 - arg0->unk18->unk80;
    ret = 0;
    if (((dz * dz) + ((dx * dx) + (dy * dy))) < arg1) {
        ret = 1;
    }
    if (ret) {
        ret = (arg0->unk18->unk5C & 0x40) != 0;
        if (!ret) {
            ret = (arg0->unk46 & 0x20) != 0;
            if (!ret) {
                ret = mapChunkIsVisibleForPlayer(0, arg0->unk40) != 0;
            }
        }
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807280C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_8072818C.s")

typedef struct C1Entry24 {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[3];
} C1Entry24; // size = 0x24

typedef struct C1Entry24List {
    /* 0x0 */ s16 count;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ C1Entry24 *unk4;
} C1Entry24List;

typedef struct C1Holder {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 padF[0xD];
    /* 0x1C */ C1Entry24 *unk1C;
} C1Holder;

#define C1TBL ((C1Entry24List *)D_80755690)

void func_8072827C(C1Holder *arg0) {
    s16 i;
    C1Entry24 *entry;

    entry = C1TBL->unk4;
    i = 0;
    if (C1TBL->count > 0) {
        do {
            entry->unk1C = 0;
            entry->unk20 = 0;
            if (entry->unk18 == arg0->unkE) {
                arg0->unk1C = entry;
                break;
            }
            i++;
            entry++;
        } while (i < C1TBL->count);
    }
    if (arg0->unk1C == 0) {
        arg0->unk1C = C1TBL->unk4;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80728300.s")

void animSetLoopLimit(void *, s32, s32);
void animSetFinished(void *, s32, s32);
void animSetFrameAndSubframe(void *, s32, s32, f32);
void animSetSpeed(void *, s32, f32);
void animSetLoopMode(void *, s32, s32);
void animSetDirection(void *, s32, s32);
void animSetEndFrame(void *, s32, s32);
void animClearStartFrame(void *, s32);
s32 animIsPlaying(void *, s32);
extern u32 D_8076A064;


u8 func_8072881C(u8 arg0, u32 *arg1) {
    u8 ret;

    ret = 0;
    if ((arg0 & 0x80) || (((*arg1 + 0x32) < D_8076A064) && (((func_80611A44() >> 0xF) % 1000) >= 0x3C1) && (animIsPlaying(D_807FBB40, arg0) == 0))) {
        arg0 &= 0x7F;
        animSetSpeed(D_807FBB40, arg0, 1.0f);
        animSetLoopMode(D_807FBB40, arg0, 1);
        animSetDirection(D_807FBB40, arg0, 0);
        animSetEndFrame(D_807FBB40, arg0, 3);
        animClearStartFrame(D_807FBB40, arg0);
        animSetFrameAndSubframe(D_807FBB40, arg0, 0, 0.0f);
        animSetLoopLimit(D_807FBB40, arg0, 2);
        *arg1 = D_8076A064;
        ret = 1;
    }
    return ret;
}


void func_80728950(u8 arg0) {
    animSetLoopLimit(D_807FBB40, arg0, 1);
    animSetFinished(D_807FBB40, arg0, 1);
    animSetFrameAndSubframe(D_807FBB40, arg0, 2, 0.0f);
}

void func_807289B0(u8 arg0, u8 arg1) {
    animSetFrameAndSubframe(D_807FBB40, arg0, arg1, 0.0f);
}

#ifdef NON_MATCHING
typedef struct A2PtrPair {
    void *p[2];
} A2PtrPair;

typedef struct A2BytePair {
    u16 w;
} A2BytePair;

typedef struct A2B44 {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ u8 pad84[0xDB];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
} A2B44;

extern A2PtrPair D_80755794;
extern u16 D_8075579C;
extern u8 D_8071FB34[];
extern u8 D_8071FB54[];
extern u8 D_8071FC0C[];
extern u8 D_8071FC40[];
extern u8 D_8071FC58[];
extern u8 D_8071FFA0[];
extern void *D_8074E880[];
extern s32 D_807F5D10;
#define A2B44V ((A2B44 *)D_807FBB44)

u32 func_806119A0(void);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80614EBC(void *, s32);
void func_8061F0B0(s32, s32, s32);
void func_8067DF44(f32, f32, f32, f32, u8, u8);
void func_80686390(void *, f32, f32, f32, f32);
void func_8068B80C(s16);
void func_8071495C(void);
void func_80714950(s32);
void func_8071496C(s16);
void func_8071498C(void *);
void func_80714998(u8);
void func_807149A8(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714A28(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
void func_8071720C(void);
void func_80717404(void);
void func_80717D4C(void);
void func_80718BF4(void);
void actorSpawnEffectChild(f32, f32, f32, f32, f32, void *, u8);
void effectSpawnBoneDefault(void *, s16, f32, f32, f32, f32, s32);
void effectSpawnMultiTierRing(f32, s32, f32, f32, f32);

void func_807289E8(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    A1Group *group;
    s16 x;
    s16 y;
    s16 z;
    s16 i;
    f32 ox0;
    f32 oy0;
    f32 oz0;
    A2PtrPair fx6;
    s16 gap6;
    u8 idx6[2];
    volatile u8 sel6;
    s16 gapA;
    s16 gapB;
    s16 ang6;
    f32 scale8;
    f32 kx8;
    f32 kz8;
    s32 gapD;
    f32 ox10;
    f32 oy10;
    s8 jx;
    s8 jy;
    s8 jz;
    f32 kx14;
    f32 ky14;
    f32 kz14;

    group = D_80755690->unk4;
    x = group->unk14[arg1].unk0;
    y = group->unk14[arg1].unk2;
    z = group->unk14[arg1].unk4;
    switch (arg0) {
        case 0:
            for (i = 0; i < arg3; i++) {
                ox0 = (f32)((func_80611A44() >> 0xF) % 0x8000 % 40 - 20.0);
                oy0 = (f32)((func_80611A44() >> 0xF) % 0x8000 % 20);
                oz0 = (f32)((func_80611A44() >> 0xF) % 0x8000 % 40 - 20.0);
                func_807149C8(0xE6, 0xE6, 0xE6, 0xC8);
                func_8071498C(func_80717D4C);
                func_80714950(-(i * 20));
                func_807149B8(1);
                func_80714998(arg2);
                func_80714CC0(D_8071FFA0, 1.5f, (f32)x + ox0, (f32)y + oy0, (f32)z + oz0);
            }
            return;
        case 7:
            break;
        case 1:
            effectSpawnMultiTierRing(0.36f, 1, (f32)x, (f32)(y + 5), (f32)z);
            func_8061F0B0(D_807F5D10, 0x14, 0xF);
            return;
        case 2:
            func_8068B80C(arg0);
            return;
        case 3:
            actorSpawnEffectChild((f32)x, (f32)y, (f32)z, arg2 * 0.01, arg3 * 0.01, NULL, 0);
            return;
        case 4:
            func_8067DF44((f32)x, (f32)y, (f32)z, arg2 * 0.01, 0, 0);
            return;
        case 5:
            if (arg2 != 0x14) {
                actorSpawn(0x104, 0);
                A2B44V->unk160 = arg3;
            }
            switch (arg2) {
                case 0:
                    A2B44V->unk7C = 450.0f;
                    A2B44V->unk80 = 500.0f;
                    A2B44V->unk15F = 0x14;
                    break;
                case 1:
                    A2B44V->unk7C = 820.0f;
                    A2B44V->unk80 = 500.0f;
                    A2B44V->unk15F = 0x15;
                    break;
                case 10:
                    func_80609140(0x3F3, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    A2B44V->unk15F = 0;
                    A2B44V->unk7C = 500.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 11:
                    func_80609140(0x3F4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    A2B44V->unk15F = 0x89;
                    A2B44V->unk7C = 600.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 12:
                    func_80609140(0x3F4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    A2B44V->unk15F = 0x47;
                    A2B44V->unk7C = 600.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 13:
                    A2B44V->unk15F = 0x23;
                    A2B44V->unk7C = 600.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 20:
                    actorSpawn(0x92, 0x73);
                    func_80614EBC(D_807FBB44, 0x42A);
                    return;
                case 30:
                case 31:
                case 32:
                case 33:
                case 34:
                case 35:
                    A2B44V->unk15F = arg2;
                    A2B44V->unk7C = 500.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
            }
            break;
        case 15:
            actorSpawn(0x92, 0x73);
            func_80614EBC(D_807FBB44, 0x42A);
            return;
        case 6:
            for (i = 0; i < arg3; i++) {
                fx6 = D_80755794;
                *(A2BytePair *)idx6 = *(A2BytePair *)&D_8075579C;
                sel6 = (func_80611A44() >> 0xF) % 2;
                ang6 = mathAngleBetweenPoints2D((f32)((A1Item *)(group->unk14 + arg2))->unk0, (f32)((A1Item *)(group->unk14 + arg2))->unk4, (f32)x, (f32)z);
                func_807149B8(1);
                func_807149FC(idx6[sel6]);
                func_8071498C(func_80717404);
                func_80714950((ang6 << 16) + 3);
                func_80714CC0(((void **)&fx6)[sel6], (f32)((func_80611A44() >> 0xF) % 1000 * 0.0005 + 0.2), (f32)x, (f32)(y + 10), (f32)z);
            }
            return;
        case 12:
            func_807149A8(0x7D0);
            func_80714998(1);
            func_80714CC0(D_8071FC0C, arg2 * 0.01, (f32)x, (f32)y, (f32)z);
            return;
        case 8:
            scale8 = arg2 * 0.01;
            for (i = 0; i < arg3; i++) {
                kx8 = ((func_80611A44() >> 0xF) % 0x8000 % 40 - 20.0) * scale8;
                kz8 = ((func_80611A44() >> 0xF) % 0x8000 % 40 - 20.0) * scale8;
                func_807149A8(0x7D0);
                func_807149B8(1);
                func_80714CC0(D_8071FB54, scale8 * 1.3, (f32)x + kx8, (f32)y, (f32)z + kz8);
                func_807149C8(0xD2, 0xD2, 0xD2, 0xC8);
                effectSpawnBoneDefault(NULL, 0, scale8 * 1.2, (f32)x + kx8, (f32)y, (f32)z + kz8, -0xB4);
            }
            return;
        case 9:
            for (i = 0; i < arg2; i++) {
                func_80714998(2);
                func_8071498C(func_8071720C);
                func_807149B8(1);
                func_80714950(1);
                func_8071496C(i * 3);
                func_80714CC0(D_8074E880[(func_80611A44() >> 0xF) % 1000 % 3], arg3 * 0.01, (f32)x, (f32)y, (f32)z);
            }
            return;
        case 10:
            for (i = 0; i < arg2; i++) {
                ox10 = (f32)((func_80611A44() >> 0xF) % 300);
                oy10 = (f32)((func_80611A44() >> 0xF) % 200);
                func_8071495C();
                func_80714CC0(D_8071FB34, arg3 * 0.01, ox10, oy10, -10.0f);
            }
            return;
        case 11:
            for (i = 0; i < arg2; i++) {
                jx = (func_806119A0() / 10000 % 200) / 10.0 - 10.0;
                jy = (func_806119A0() / 10000 % 200) / 10.0 - 7.0;
                jz = (func_806119A0() / 10000 % 200) / 10.0 - 10.0;
                func_807149B8(1);
                func_807149FC(2);
                func_80714950(0x64);
                func_8071498C(func_80717D4C);
                func_8071496C(i / 7);
                func_80714CC0(D_8071FC58, arg3 * 0.01, (f32)(x + jx), (f32)(y + jy), (f32)(z + jz));
            }
            return;
        case 13:
            func_80686390(NULL, arg2 * 0.01, (f32)x, (f32)y, (f32)z);
            return;
        case 14:
            for (i = 0; i < arg2; i++) {
                kx14 = (f32)(func_806119A0() / 10000 % 200) / 10.0 - 5.0;
                ky14 = (f32)(func_806119A0() / 10000 % 200) / 10.0 - 5.0;
                kz14 = (f32)(func_806119A0() / 10000 % 200) / 10.0 - 5.0;
                func_807149B8(1);
                func_80714950(2);
                func_807149FC(-1);
                func_8071498C(func_80718BF4);
                func_80714A28(4);
                func_80714CC0(D_8071FC40, 0.0f, (f32)x + kx14, (f32)y + ky14, (f32)z + kz14);
            }
            break;
    }
}

#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807289E8.s")
#endif



void func_80729AA4(u8 arg0) {
    Actor *a;

    a = func_807270C0(arg0, 0);
    if (a == 0) {
        a = D_807FBB4C;
    }
    a->unk6A |= 0x100;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/D_8075EB80.s")
