#include "common.h"
#include "actor.h"


#ifdef NON_MATCHING
typedef struct {
    u8 pad0[4];
    u32 unk4;
    u8 pad8;
    u8 unk9;
    u8 padA[0xE];
    s16 unk18;
    s16 unk1A;
} Col6AAssetHeader;

typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
} Col6ABufferEntry;

struct CollisionBufferEntry;
extern struct CollisionBufferEntry *D_807F9514;
extern s32 D_807F9518;
extern u8 D_807F951C;
extern s32 D_8076A0A8;
extern u8 D_807F94B4;
void *func_80610FE8(s32);
void *func_8066B0F8(s32, s32, s32, s32);
s32 assetGetSize(s32, s32);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);
void gunzip(void *, void *, void *);
void heapFree(void *);

void func_80666090(Col6AAssetHeader *arg0) {
    s32 pad5C;
    void *sp58;
    void *sp54;
    void *sp50;
    u8 *var_s1;
    u8 *a3;
    u8 *a1;
    u8 *a2;
    s32 base;
    s32 i;
    void *sp34;
    s32 pad30;

    pad5C = pad30; // FAKE: reading a pad local makes uopt reserve its stack slot (frame 0x60)
    D_807F9514 = (struct CollisionBufferEntry *)func_80610FE8(0x11A8);
    D_807F9518 = (u32)(arg0->unk18 * arg0->unk1A);
    var_s1 = (u8 *)func_8066B0F8(3, D_8076A0A8, 1, 0);
    D_807F951C = 0;
    if (arg0->unk9 & 2) {
        sp58 = var_s1;
        var_s1 = func_80610FE8(arg0->unk4);
        sp34 = func_80610FE8(0x2400);
        sp54 = var_s1;
        sp50 = sp58;
        gunzip(&sp50, &sp54, sp34);
        heapFree(sp34);
        assetSetImmediateFree();
        assetFreeBuffer(sp58, 0x9D, 0x3A);
        D_807F951C = 1;
    }
    base = assetGetSize(3, D_8076A0A8);
    a3 = var_s1 + 4;
    for (i = 0; i < D_807F9518; i++) {
        ((Col6ABufferEntry *)D_807F9514)[i].unk8 = 0;
        if (D_807F9514 && D_807F9514) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        a2 = a3 + 4;
        ((Col6ABufferEntry *)D_807F9514)[i].unkC = base + (a3 - var_s1) + 4;
        a1 = var_s1 + *(u32 *)a3;
        a3 = a1;
        if (D_807F951C) {
            ((Col6ABufferEntry *)D_807F9514)[i].unk0 = (u32)a2;
            ((Col6ABufferEntry *)D_807F9514)[i].unk4 = (u32)a1;
        } else {
            ((Col6ABufferEntry *)D_807F9514)[i].unk0 = 0;
            ((Col6ABufferEntry *)D_807F9514)[i].unk4 = 0;
        }
        ((Col6ABufferEntry *)D_807F9514)[i].unk10 = a1 - a2;
    }
    if (!D_807F951C) {
        assetSetImmediateFree();
        assetFreeBuffer(var_s1, 0xC3, 0x3A);
    }
    D_807F94B4 = 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80666090.s")
#endif

extern u8 D_807F94B4;

void func_80666280(arg0)
u8 arg0;
{
    D_807F94B4 = arg0;
}

void func_80666428(Actor *, f32, f32, f32, ...);
extern u8 D_807F94B3;
extern u8 D_807F94BC;
extern f32 D_807F948C;

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);

void func_80666290(Actor *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    D_807F94BC = 0;
    D_807F94B3 = 0;
    if (((u8 *)arg0)[0xCC] != 0 && arg0->unk110 == 0 && (arg0->unk60 & 0x10)) {
        actorGetNodePos(arg0, ((u8 *)arg0)[0xCC] ^ 0, &sp3C, &sp38, &sp34); // FAKE: x ^ 0 keeps the node id in v0 (no spill)
    } else {
        sp3C = arg0->unk7C;
        sp38 = arg0->unk8C;
        sp34 = arg0->unk84;
    }
    func_80666428(arg0, sp3C, sp38, sp34, arg1, arg2, arg3, arg4, arg5);
}

void collisionCheckActorFloor(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    u8 sp3F;
    u8 sp3E;
    f32 sp38;
    f32 sp34;

    if (arg0->unk58 == 0xBC) {
        D_807F94B3 = 1;
    } else {
        D_807F94B3 = 0;
    }
    D_807F94BC = 1;
    func_80666428(NULL, arg1, arg2, arg3, &sp3F, &sp38, &sp3E, &sp34, 0);
    *arg4 = D_807F948C;
}

extern u8 D_807F94AE;
extern u8 D_807F94AF;
extern u8 D_807F94B0;
extern u8 D_807F94B7;
extern u8 D_807F951D;

void collisionClearFlags(void) {
    D_807F94AE = 0;
    D_807F94AF = 0;
    D_807F94B0 = 0;
    D_807F94B7 = 0;
}

u8 collisionGetStateByte(void) {
    return D_807F951D;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80666428.s")

extern u8 D_807F946E;
extern u8 D_807F94B1;
extern u8 D_807F94AA;
extern s16 D_807F94A2;
extern s16 D_807F94A4;

u8 collisionGetHitStatus(void) {
    return D_807F946E;
}

u8 func_80666A94(void) {
    return D_807F94AE;
}

u8 func_80666AA0(void) {
    return D_807F94AF;
}

u8 func_80666AAC(void) {
    return D_807F94B0;
}

u8 func_80666AB8(void) {
    return D_807F94B7;
}

void collisionGetCoords(s16 *arg0, s16 *arg1) {
    *arg0 = D_807F94A2;
    *arg1 = D_807F94A4;
}

u8 func_80666AE0(void) {
    return D_807F94B1;
}

u8 func_80666AEC(void) {
    return D_807F94AA;
}

extern s16 D_807F9490;
extern s16 D_807F9498;
extern u8 D_807F949E;
extern s16 D_807F94A6;
extern s16 D_807F94A8;
f32 func_80611BB4(f32, f32);

void func_80666AF8(u8 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    f32 temp_fv0_2;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fa1;
    f64 temp_fv0;
    s16 var_v0_2;
    s16 var_v0_3;
    u8 var_v0;

    arg0 = arg4;
    var_v0 = arg0;
    if (arg0 == 0xFF) {
        arg0 = 0;
        var_v0 = 0;
    }
    if (var_v0 == 0xFE) {
        arg0 = 0;
    }
    (&D_807F949E)[(((((((((arg6 & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF)] = arg0; // FAKE: nine nested &0xFF consume uopt temp numbering (t6/t7 skew)
    if (arg3 > 0.0f) {
        var_fa1 = arg3;
    } else {
        var_fa1 = -arg3;
    }
    if ((f64) var_fa1 < 0.01) {
        var_v0_2 = 0x400;
    } else {
        if (arg1 > 0.0f) {
            var_fa0 = arg1;
        } else {
            var_fa0 = -arg1;
        }
        var_v0_2 = (s16) (s32) ((func_80611BB4(var_fa0, var_fa1) / 3.1415927f) * 2048.0f);
    }
    temp_fv0 = (f64) arg1;
    if ((temp_fv0 >= 0.0) && ((f64) arg3 >= 0.0)) {
        var_v0_2 -= 0x800;
    } else if ((temp_fv0 >= 0.0) && ((f64) arg3 < 0.0)) {
        var_v0_2 = -var_v0_2;
    } else if ((temp_fv0 < 0.0) && ((f64) arg3 >= 0.0)) {
        var_v0_2 = 0x800 - var_v0_2;
    }
    if (arg5) {
        (&D_807F9490)[arg6] = var_v0_2 & 0xFFF;
    }
    D_807F94A6 = var_v0_2 & 0xFFF;
    temp_fv0_2 = sqrtf((arg1 * arg1) + (arg3 * arg3));
    if ((f64) temp_fv0_2 < 0.01) {
        var_v0_3 = 0x400;
    } else {
        if (arg2 > 0.0f) {
            var_fa0_2 = arg2;
        } else {
            var_fa0_2 = -arg2;
        }
        var_v0_3 = (s16) (s32) ((func_80611BB4(var_fa0_2, temp_fv0_2) / 3.1415927f) * 2048.0f);
    }
    if (arg5) {
        (&D_807F9498)[arg6] = var_v0_3;
    }
    D_807F94A8 = var_v0_3;
}

typedef struct {
    u8 pad[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} CollisionPlayerPosition;


extern CollisionPlayerPosition *D_807FC924;
extern u8 D_807FC929;
extern s16 D_807FD584;
extern f32 D_80752F7C[];
extern f32 D_80752F98[];
extern f32 D_80752FB4[];
extern f32 D_80752FD0[];
extern f32 D_80752FEC[];
extern f32 D_80753008[];
extern f32 D_807F9460;
extern s8 D_807F9464;

void func_80666D88(f32 arg0, f32 arg1, u8 arg2, Actor *arg3, u8 arg4) {
    f32 *var_v1;
    f32 *var_v0;
    f32 var_fa0;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv1;
    f32 diff;
    s32 temp;
    s32 flag;
    u8 temp_v0;

    flag = 1;
    if (arg0 < arg1) {
        if ((arg3 != NULL) && (arg3->unk5C & 1)) {
            temp_v0 = D_807FC924[D_807FC929].unk2C0;
            if (temp_v0 != 0) {
                if (temp_v0 != 2) {
                    var_v0 = D_80752F98; var_v1 = D_80752F7C; // FAKE: same-line join steers as1 scheduling (addiu order)
                } else {
                    var_v0 = D_80753008;
                    var_v1 = D_80752FEC;
                }
            } else {
                var_v0 = D_80752FD0;
                var_v1 = D_80752FB4;
            }
            var_fv0 = var_v0[D_807FD584];
            var_fv1 = var_v1[D_807FD584];
        } else {
            var_fv0 = 10.0f;
            var_fv1 = 20.0f;
        }
        if (arg4 != 0) {
            var_fv0 /= (f32)2;
        }
        temp = arg2;
        if (arg2 == 1) {
            var_ft4 = var_fv0 * 6.0f;
        } else {
            var_ft4 = var_fv0;
        }
        diff = arg1 - arg0;
        if (var_ft4 < diff) {
            if (flag == temp) {
                var_fa0 = var_fv1 * 6.0f;
            } else {
                var_fa0 = var_fv1;
            }
            if (diff < var_fa0) {
                D_807F9464 = flag;
                D_807F9460 = arg1 - var_fa0;
                if (arg2) {
                    D_807F9460 /= 6.0f;
                }
            }
        }
    }
}

extern f32 D_807F9468;
extern u8 D_807F946C;

s32 func_80666F04(f32 arg0, f32 arg1, u8 arg2, u8 arg3) {
    f32 var_fv0;
    s32 var_v1;

    var_v1 = 0;
    if (arg3 == 0xFF && arg0 < arg1) {
        var_fv0 = (arg2 == 1) ? 150.0 : 25.0;
        if ((arg1 - arg0) < var_fv0) {
            D_807F946C = 1;
            var_v1 = 1;
            D_807F9468 = arg1 - var_fv0;
            if (arg2) {
                D_807F9468 /= 6.0f;
            }
            D_807F9468 = (f64)D_807F9468 + 6.0;
        }
    }
    return var_v1;
}

s32 mathCheckCloserFloatThreshold(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    f32 var_fv0;
    f32 diff0;
    f32 diff1;
    s32 cond0;
    s32 cond1;

    var_fv0 = (arg3 == 1) ? 60.0 : 10.0;

    if (arg0 <= arg2) {
        cond0 = 1;
    } else if ((arg0 - arg2) < var_fv0) {
        cond0 = 1;
    } else {
        cond0 = 0;
    }

    if (arg1 <= arg2) {
        cond1 = 1;
    } else if ((arg1 - arg2) < var_fv0) {
        cond1 = 1;
    } else {
        cond1 = 0;
    }

    if (!cond0 && !cond1) {
        return 0;
    }
    if (!cond1) {
        return 0;
    }
    if (!cond0) {
        return 1;
    }

    if (arg2 < arg0) {
        diff0 = arg0 - arg2;
    } else {
        diff0 = arg2 - arg0;
    }

    if (arg2 < arg1) {
        diff1 = arg1 - arg2;
    } else {
        diff1 = arg2 - arg1;
    }

    if (diff0 < diff1) {
        return 0;
    }
    return 1;
}

extern u8 D_807F9484;
extern f32 D_807F9488;
extern u8 D_807F94B5;
extern u8 D_807F9510;
u8 collisionTestSubmeshBoundary(f32, f32, f32 *, s32);

s32 collisionCheckGroundAtPoint(f32 arg0, f32 arg1, void *arg2) {
    s32 ret;

    D_807F9484 = 0;
    D_807F9510 = 0;
    ret = collisionTestSubmeshBoundary(arg0, arg1, arg2, 0);
    D_807F94A4 = D_807F9498;
    D_807F94A2 = D_807F9490;
    return ret;
}

u8 collisionGetFloorHeight(f32 *arg0) {
    *arg0 = D_807F9488;
    return D_807F9484;
}

u8 func_80667174(void) {
    return D_807F94B5;
}

s32 func_806672B8(f32, f32, f32 *, s32);
u8 func_806679BC(f32, f32, f32 *);
extern u8 D_807F94B6;

u8 collisionTestSubmeshBoundary(f32 arg0, f32 arg1, f32 *arg2, s32 arg3) {
    u8 sp3F;
    f32 sp38;
    f32 sp34;
    f32 temp;
    u8 sp2E;
    u8 val;
    s32 var_v1;

    sp38 = *arg2;
    sp3F = func_806679BC(arg0, arg1, &sp38);
    sp34 = *arg2;
    val = func_806672B8(arg0, arg1, &sp34, arg3) * 2;
    val += sp3F;
    switch (val) {
    case 0:
        break;
    case 1:
        *arg2 = sp38;
        break;
    case 2:
        *arg2 = sp34;
        D_807F94B6 = 1;
        break;
    case 3:
        sp2E = val;
        temp = (f64)*arg2 + 4.0;
        if (mathCheckCloserFloatThreshold(sp38, sp34, temp, 0) != 0) {
            *arg2 = sp34;
            D_807F94B6 = 1;
        } else {
            *arg2 = sp38;
        }
        break;
    }
    if (val != 0) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1;
}

#ifdef NON_MATCHING
typedef struct Col6A2SubNode {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 pad4E[0x60 - 0x4E];
    /* 0x60 */ u8 unk60;
} Col6A2SubNode;
typedef struct Col6A2Node {
    /* 0x00 */ Col6A2SubNode *unk0;
    /* 0x04 */ u8 pad4[0x2C - 0x04];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[0x4A - 0x2E];
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 pad4B[0x50 - 0x4B];
    /* 0x50 */ struct Col6A2Node *next;
} Col6A2Node;

extern Col6A2Node *D_807F93C0;
u8 effectGetTableFlag(Col6A2Node *);
f32 func_806608FC(Col6A2Node *, s32, s32, u8);
s32 func_80668C30(s16 *, f32, f32);
f32 func_8066785C(s16 *, f32, f32);
s32 mathCheckCloserFloatThreshold(f32, f32, f32, u8);

s32 func_806672B8(f32 arg0, f32 arg1, f32 *arg2, s32 arg3) {
    f32 temp_fs1;
    u8 temp_s0;
    f32 pad[2]; // pad: reproduces frame 0xF8 (unused)
    f32 x[4];
    f32 y[4];
    f32 z[4];
    s16 spA0[12]; // 12 not 9: slot size so arrays start at 0xB8
    s8 sp9F; // FAKE: s8 (not u8) keeps sp9F in memory like the original (final lbu then only differs: lb)
    f32 var_fs5;
    Col6A2Node *var_s3;
    f32 var_fs0;
    f32 sp8C;
    s32 cell_x;
    s32 cell_z;

    sp9F = 0;
    var_fs5 = 999999.0f;
    var_s3 = D_807F93C0;
    sp8C = (f32)((f64)*arg2 + 4.0);
    if (var_s3 != NULL) {
        do {
            if (var_s3->unk0->unk46 <= arg0 && var_s3->unk0->unk48 <= arg1 && arg0 <= var_s3->unk0->unk4A && arg1 <= var_s3->unk0->unk4C) {
                var_fs0 = arg0 * 6.0f;
                temp_fs1 = arg1 * 6.0f;
                temp_s0 = effectGetTableFlag(var_s3);
                cell_x = (arg0 - var_s3->unk0->unk46) / (f32)var_s3->unk2C;
                cell_z = (arg1 - var_s3->unk0->unk48) / (f32)var_s3->unk2C;

                x[0] = var_s3->unk2C * cell_x + var_s3->unk0->unk46;
                z[0] = var_s3->unk2C * cell_z + var_s3->unk0->unk48;
                y[0] = func_806608FC(var_s3, x[0], z[0], temp_s0);

                x[1] = (cell_x + 1) * var_s3->unk2C + var_s3->unk0->unk46;
                z[1] = z[0];
                y[1] = func_806608FC(var_s3, x[1], z[1], temp_s0);
                x[2] = x[0];
                z[2] = (cell_z + 1) * var_s3->unk2C + var_s3->unk0->unk48;
                y[2] = func_806608FC(var_s3, x[2], z[2], temp_s0);

                x[3] = x[1];
                z[3] = z[2];
                y[3] = func_806608FC(var_s3, x[3], z[3], temp_s0);

                spA0[0] = x[0] * 6.0f;
                spA0[3] = y[0] * 6.0f;
                spA0[6] = z[0] * 6.0f;

                spA0[1] = x[1] * 6.0f;
                spA0[4] = y[1] * 6.0f;
                spA0[7] = z[1] * 6.0f;

                spA0[2] = x[3] * 6.0f;
                spA0[5] = y[3] * 6.0f;
                spA0[8] = z[3] * 6.0f;

                if (func_80668C30(spA0, var_fs0, temp_fs1) != 0) {
                    var_fs0 = func_8066785C(spA0, var_fs0, temp_fs1) / 6.0f;
                } else {
                    spA0[1] = x[2] * 6.0f;
                    spA0[4] = y[2] * 6.0f;
                    spA0[7] = z[2] * 6.0f;
                    var_fs0 = func_8066785C(spA0, var_fs0, temp_fs1) / 6.0f;
                }

                switch (var_s3->unk0->unk60) {
                case 0:
                case 2:
                case 3:
                    sp9F = 1;
                    if (var_s3->unk0->unk60 == 2 || var_s3->unk0->unk60 == 3) {
                        if ((var_fs0 < *arg2 ? *arg2 - var_fs0 : -(*arg2 - var_fs0)) < 6.0f) {
                            switch (var_s3->unk0->unk60) {
                            case 2:
                                D_807F94AF = 2;
                                break;
                            case 3:
                                D_807F94AF = 1;
                                break;
                            }
                        }
                    }
                    if (mathCheckCloserFloatThreshold(var_fs5, var_fs0, sp8C, 0) != 0) {
                        var_fs5 = var_fs0;
                    }
                    break;
                case 1:
                    if (arg3 != 0) {
                        if (((Actor *)arg3)->unk80 < var_fs0) {
                            ((Actor *)arg3)->unk6A |= 4;
                            *(s8 *)&((Actor *)arg3)->unkB0[0] = -1; // FAKE: s8 view makes the store constant -1 (u8 field folds to 0xFF)
                            if (var_s3->unk4A & 1) {
                                D_807F94B0 = 1;
                            }
                        }
                        ((Actor *)arg3)->unkAC = var_fs0;
                        ((Actor *)arg3)->unk6A |= 2;
                    }
                    D_807F9484 = 1;
                    D_807F9488 = var_fs0;
                    break;
                }
            }
            var_s3 = var_s3->next;
        } while (var_s3 != NULL);
    }
    if (sp9F != 0) {
        *arg2 = var_fs5;
    }
    return (u8)sp9F;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_806672B8.s")
#endif

f32 func_8066785C(s16 *arg0, f32 arg1, f32 arg2) {
    f64 dx01 = arg0[0] - arg0[1];
    f64 dy01 = arg0[3] - arg0[4];
    f64 dz01 = arg0[6] - arg0[7];
    f64 dx02 = arg0[0] - arg0[2];
    f64 dy02 = arg0[3] - arg0[5];
    f64 dz02 = arg0[6] - arg0[8];
    f64 nx = (dy01 * dz02) - (dz01 * dy02);
    f64 ny = (dz01 * dx02) - (dx01 * dz02);
    f64 nz = (dx01 * dy02) - (dy01 * dx02);
    f64 d = -((nx * arg0[1]) + (ny * arg0[4]) + (nz * arg0[7]));
    f64 val = ((nx * arg1) + (ny * -1000.0) + (nz * arg2) + d) / (ny * 2000.0);
    val = 0.0 - val;
    return (2000.0 * val) - 1000.0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_806679BC.s")

s32 mathCheckCloserFloatThreshold(f32, f32, f32, u8);

s32 func_80668520(f32 *arg0, f32 arg1, f32 arg2, f32 *arg3) {
    f32 diff;
    f64 val;

    val = (f64)(arg2 * 6.0f);
    if (val > 1614.0) {
        diff = val - 1614.0;
    } else {
        diff = -(val - 1614.0);
    }
    if (diff < 40.0f) {
        D_807F94AE = 1;
    }
    if (mathCheckCloserFloatThreshold(*arg0, 684.0f, arg1, 1)) {
        *arg3 = 114.0f;
        return 1;
    }
    return 0;
}

typedef struct CollisionTriS {
    s16 x[3];
    s16 y[3];
    s16 z[3];
    s16 unk12;
} CollisionTriS;

typedef struct CollisionHitEntry {
    f32 unk0;
    s16 unk4;
    u8 unk6;
    u8 unk7;
} CollisionHitEntry;

extern CollisionHitEntry D_807F94C0[];
s32 collisionCheckTriangleWindingS16();
void func_806689F0();

void collisionRecordTriangleS(CollisionTriS *arg0, f32 arg1) {
    if (D_807F9510 != 10) {
        D_807F94C0[D_807F9510].unk0 = arg1 / 6.0f;
        if (collisionCheckTriangleWindingS16(arg0)) {
            D_807F94C0[D_807F9510].unk6 = 1;
        } else {
            D_807F94C0[D_807F9510].unk6 = 2;
        }
        if (arg0->unk12 & 1) {
            D_807F94C0[D_807F9510].unk6 |= 4;
        }
        if (arg0->unk12 & 0x400) {
            D_807F94C0[D_807F9510].unk6 |= 8;
        }
        func_806689F0(0, arg0, 0);
        D_807F94C0[D_807F9510].unk4 = D_807F94A8;
        D_807F9510++;
    }
}
typedef struct CollisionBufferEntry {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
} CollisionBufferEntry;

extern CollisionBufferEntry *D_807F9514;
extern s32 D_8076A064;
extern s32 D_807F9518;
extern u8 D_807F951C;
void actorClearBufferReferences(s32);
void heapFree(void *);
void *func_80610FE8(s32);
void func_8060B140(s32, void *, void *, s32, s32, s32, s32);

void dynamicBufferAllocateEntry(s32 arg0) {
    u32 sp34;

    if (D_807F9514[arg0].unk0 == 0) {
        sp34 = D_807F9514[arg0].unk10;
        if (sp34 != 0) {
            D_807F9514[arg0].unk0 = (u32)func_80610FE8(sp34);
            D_807F9514[arg0].unk4 = D_807F9514[arg0].unk0 + (sp34 / 24) * 24;
            func_8060B140(D_807F9514[arg0].unkC, (void *)D_807F9514[arg0].unk0, &sp34, 0, 0, 0, 0);
        }
    }
    D_807F9514[arg0].unk8 = D_8076A064;
}

void dynamicBufferPurgeExpired(void) {
    s32 i;

    if (!D_807F951C) {
        for (i = 0; i < D_807F9518; i++) {
            if (D_807F9514[i].unk0 != 0 && (u32)(D_8076A064 - D_807F9514[i].unk8) >= 21) {
                actorClearBufferReferences(i);
                heapFree((void *)D_807F9514[i].unk0);
                D_807F9514[i].unk0 = 0;
                D_807F9514[i].unk4 = 0;
            }
        }
    }
}
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

void actorClearBufferReferences(s32 arg0) {
    s32 i;
    u32 min = D_807F9514[arg0].unk0;
    u32 max = D_807F9514[arg0].unk4;

    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        u32 val = actor->unk150;

        if (!(actor->unk60 & 0x2000) && val >= min && max >= val) {
            actor->unk150 = 0;
        }
    }
}

typedef struct CollisionMeshTriS {
    s16 x[3];
    s16 y[3];
    s16 z[3];
} CollisionMeshTriS;

typedef struct CrossProductStack {
    f32 cross;
    f32 v0[3];
    f32 v1[3];
} CrossProductStack;

s32 collisionCheckTriangleWindingS16(CollisionMeshTriS *arg0) {
    CrossProductStack sp;

    sp.v1[0] = arg0->x[2] - arg0->x[0];
    sp.v1[2] = arg0->z[2] - arg0->z[0];
    sp.v0[0] = arg0->x[1] - arg0->x[0];
    sp.v0[2] = arg0->z[1] - arg0->z[0];
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}

typedef struct CollisionPlaneTriS {
    s16 x[3];
    s16 y[3];
    s16 z[3];
    s16 unk12;
    u8 unk14;
} CollisionPlaneTriS;

typedef struct CrossProductStack3D {
    f32 cross[3];
    f32 v0[3];
    f32 v1[3];
} CrossProductStack3D;

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_806689F0.s")

s32 collisionCheckTriangleXZBoundsS16(CollisionMeshTriS *arg0, s32 arg1, s32 arg2) {
    s32 p0, p1, p2;
    s32 val;

    p0 = arg0->x[0];
    p1 = arg0->x[1];
    p2 = arg0->x[2];

    val = (p0 < p1) ? p0 : p1;
    if (val >= p2) {
        val = p2;
    }
    if (arg1 < val) {
        return 0;
    }

    val = (p1 < p0) ? p0 : p1;
    if (val <= p2) {
        val = p2;
    }
    if (val < arg1) {
        return 0;
    }

    p0 = arg0->z[0];
    p1 = arg0->z[1];
    p2 = arg0->z[2];

    val = (p0 < p1) ? p0 : p1;
    if (val >= p2) {
        val = p2;
    }
    if (arg2 < val) {
        return 0;
    }

    val = (p1 < p0) ? p0 : p1;
    if (val <= p2) {
        val = p2;
    }
    if (val < arg2) {
        return 0;
    }

    return 1;
}

#ifdef NON_MATCHING
s32 func_80668C30(s16 *arg0, f32 arg1, f32 arg2) {
    f64 padTop[4]; // pad: reproduces frame 0xC8 / slot layout (unused)
    f64 var_fa0, var_fa1, var_ft4, var_ft5;
    f64 padMid[1]; // pad: reproduces slot layout (unused)
    f64 var_fv0, var_fv1, var_fs0;
    f64 mid_x, mid_z;
    f64 d_arg1, d_arg2;
    f64 t0_d, t1_d;
    s32 i;
    s32 mismatch = 0;

    d_arg1 = arg1;
    d_arg2 = arg2;
    mid_x = ((f64)arg0[0] + (f64)(arg0[2] + arg0[1]) * 0.5) * 0.5;
    mid_z = ((f64)arg0[6] + (f64)(arg0[8] + arg0[7]) * 0.5) * 0.5;
    t0_d = arg0[0];
    t1_d = arg0[6];

    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            var_ft4 = t0_d;
            var_ft5 = t1_d;
            var_fa0 = (f64)(arg0[1] - arg0[0]);
            var_fa1 = (f64)(arg0[7] - arg0[6]);
            break;
        case 1:
            var_ft4 = t0_d;
            var_ft5 = t1_d;
            var_fa0 = (f64)(arg0[2] - arg0[0]);
            var_fa1 = (f64)(arg0[8] - arg0[6]);
            break;
        case 2:
            var_ft4 = (f64)arg0[1];
            var_ft5 = (f64)arg0[7];
            var_fa0 = (f64)(arg0[2] - arg0[1]);
            var_fa1 = (f64)(arg0[8] - arg0[7]);
            break;
        }

        var_fv0 = (d_arg1 - var_ft4) * var_fa1;
        var_fv1 = (d_arg2 - var_ft5) * var_fa0;
        var_fs0 = ((mid_x - var_ft4) * var_fa1) - ((mid_z - var_ft5) * var_fa0);

        if ((var_fv1 <= var_fv0 ? 1 : -1) != (var_fs0 >= 0.0 ? 1 : -1)) {
            mismatch = 1;
        }
    }

    return (mismatch == 0) & 0xFF;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80668C30.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80668E9C.s")

typedef struct CollisionTriF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
} CollisionTriF;

s32 collisionCheckTriangleWindingF32(CollisionTriF *);
void func_80669830();

void collisionRecordTriangleF(CollisionTriF *arg0, f32 arg1) {
    if (D_807F9510 != 10) {
        D_807F94C0[D_807F9510].unk0 = arg1;
        if (collisionCheckTriangleWindingF32(arg0)) {
            D_807F94C0[D_807F9510].unk6 = 1;
        } else {
            D_807F94C0[D_807F9510].unk6 = 2;
        }
        func_80669830(0, arg0, 0);
        D_807F94C0[D_807F9510].unk4 = D_807F94A8;
        D_807F9510++;
    }
}

s32 collisionCheckSurfaceFilter(u8 arg0, u8 *arg1) {
    u8 i = 0;

    do {
        if (arg1[i] != 0xFF && arg1[i] == arg0) {
            return 0;
        }
        i++;
    } while (i < 2);
    return 1;
}

typedef struct CollisionLinkedNode {
    f32 x;
    f32 y;
    f32 z;
    struct CollisionLinkedNode *next;
} CollisionLinkedNode;

typedef struct CollisionSubNodeWork {
    u8 pad0[8];
    f32 unk8;
    f32 unkC;
    u8 pad10[0x34 - 0x10];
    f32 unk34;
} CollisionSubNodeWork;

typedef struct CollisionModelEntry {
    u8 pad[0x7C];
    CollisionSubNodeWork *unk7C;
    u8 pad80[0x88 - 0x80];
    s16 unk88;
    u8 pad8A[6];
} CollisionModelEntry;

extern CollisionModelEntry *D_807F6000;

typedef struct CollisionActorWork {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x94 - 0x88];
    f32 unk94;
    f32 unk98;
    u8 pad9C[0xE6 - 0x9C];
    s16 unkE6;
    u8 padE8[0xFC - 0xE8];
    u8 unkFC;
    u8 padFD[3];
    f32 unk100;
    f32 unk104;
    f32 unk108;
    s16 unk10C;
    s8 unk10E;
    s8 unk10F;
    u8 unk110;
    u8 pad111[0x12F - 0x111];
    u8 unk12F;
} CollisionActorWork;

void func_806699C4(CollisionActorWork *, s16, s8, s8, f32, f32, f32);
void func_8066C610(s16, s8, float [4][4]);
s32 hashTableLookup();

void actorCheckNearbyNodeInteractions(arg0, arg1, arg2)
CollisionActorWork *arg0;
s16 arg1;
CollisionLinkedNode *arg2;
{
    u8 count = 0;

    if (arg2 != NULL) {
        do {
            f32 dx = arg2->x - arg0->unk7C;
            f32 dz = arg2->z - arg0->unk84;
            f32 dist;
            f32 dy;

            dx = dx * dx;
            dz = dz * dz;
            dist = sqrtf(dx + dz);
            dy = arg2->y - arg0->unk80;
            if (dist < 5.0) {
                if (dy > 0.0f) {
                    if (dy < 25.0) {
                        func_806699C4(arg0, arg1, -1, 0, arg2->x, arg2->y, arg2->z);
                        arg0->unk110 = 3;
                        arg0->unk12F = count;
                        D_807F946C = 1;
                        D_807F9468 = arg2->y - 10.0f;
                    }
                }
            }
            arg2 = arg2->next;
            count++;
        } while (arg2 != NULL);
    }
}

typedef struct CollisionPlaneTriF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
    u8 unk24;
} CollisionPlaneTriF;


#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80669830.s")

s32 collisionCheckTriangleWindingF32(CollisionTriF *arg0) {
    CrossProductStack sp;

    sp.v1[0] = arg0->x[2] - arg0->x[0];
    sp.v1[2] = arg0->z[2] - arg0->z[0];
    sp.v0[0] = arg0->x[1] - arg0->x[0];
    sp.v0[2] = arg0->z[1] - arg0->z[0];
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}

#ifdef NON_MATCHING
void matrix4Invert(float [4][4], float [4][4]);

void func_806699C4(CollisionActorWork *arg0, s16 arg1, s8 arg2, s8 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 pad2[10];
    float spB0[4][4];
    float pad[4][4];
    float sp30[4][4];

    arg0->unk10C = (arg1 + D_807F6000)->unk88;
    arg0->unk10E = (((((((((arg3 & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF); // FAKE: nine nested &0xFF shift uopt temp numbering
    arg0->unk10F = arg2;
    func_8066C610(arg1, arg2, spB0);
    matrix4Invert(sp30, spB0);
    guMtxXFMF(sp30, arg4, arg5, arg6, &arg0->unk100, &arg0->unk104, &arg0->unk108);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_806699C4.s")
#endif

void actorUpdateSubnodeRotationAndMtx(CollisionActorWork *arg0) {
    f32 pad[10];
    float sp90[4][4];
    float padMtx[4][4];
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s16 sp42;
    s16 pad40;
    CollisionSubNodeWork *sub;

    sp42 = hashTableLookup(arg0->unk10C);
    if (sp42 != -1) {
        func_8066C610(sp42, arg0->unk10F, sp90);
        sub = D_807F6000[sp42].unk7C;
        if (sub != NULL) {
            if (arg0->unkFC == 0) {
                arg0->unkE6 += (sub->unk34 * 4095.0f) / 360.0f;
                if (arg0->unkE6 >= 0x1000) {
                    arg0->unkE6 -= 0x1000;
                }
                if (arg0->unkE6 < 0) {
                    arg0->unkE6 += 0xFFF;
                }
            }
            arg0->unk100 += D_807F6000[sp42].unk7C->unk8;
            arg0->unk108 += D_807F6000[sp42].unk7C->unkC;
        }
        guMtxXFMF(sp90, arg0->unk100, arg0->unk104, arg0->unk108, &sp4C, &sp48, &sp44);
        arg0->unk94 = sp4C;
        arg0->unk98 = sp44;
        if (arg0->unkFC == 0) {
            arg0->unk7C = sp4C;
            arg0->unk84 = sp44;
        }
    }
}

typedef struct CollisionBoundingBox {
    f32 minX;
    f32 minY;
    f32 minZ;
    f32 maxX;
    f32 maxY;
    f32 maxZ;
} CollisionBoundingBox;

s32 collisionCheckBoundingBoxXZ(CollisionBoundingBox *arg0, f32 arg1, f32 arg2) {
    if (arg1 < arg0->minX) {
        return 0;
    }
    if (arg2 < arg0->minZ) {
        return 0;
    }
    if (arg0->maxX < arg1) {
        return 0;
    }
    if (arg0->maxZ < arg2) {
        return 0;
    }
    return 1;
}

s32 collisionCheckBoundingBoxY(CollisionBoundingBox *arg0, f32 arg1) {
    if (arg1 < arg0->minY) {
        return 0;
    }
    if (arg0->maxY < arg1) {
        return 0;
    }
    return 1;
}

s32 collisionCheckTriangleBoundingBoxXZ(CollisionTriF *arg0, f32 arg1, f32 arg2) {
    f32 x0, x1, x2;
    f32 z0, z1, z2;
    f32 min;
    f32 max;

    x0 = arg0->x[0];
    x1 = arg0->x[1];
    x2 = arg0->x[2];

    min = (x0 < x1) ? x0 : x1;
    if (!(min < x2)) {
        min = x2;
    }
    if (arg1 < min) {
        return 0;
    }
    max = (x1 < x0) ? x0 : x1;
    if (!(x2 < max)) {
        max = x2;
    }
    if (max < arg1) {
        return 0;
    }

    z0 = arg0->z[0];
    z1 = arg0->z[1];
    z2 = arg0->z[2];

    min = (z0 < z1) ? z0 : z1;
    if (!(min < z2)) {
        min = z2;
    }
    if (arg2 < min) {
        return 0;
    }
    max = (z1 < z0) ? z0 : z1;
    if (!(z2 < max)) {
        max = z2;
    }
    if (max < arg2) {
        return 0;
    }
    return 1;
}

#ifdef NON_MATCHING
u8 func_80669E04(CollisionTriF *arg0, f32 arg1, f32 arg2) {
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f32 x0;
    f32 x1;
    f32 x2;
    f32 z0;
    f32 z1;
    f32 z2;
    f64 cx;
    f64 cz;
    f64 a;
    f64 b;
    f64 c;
    s32 i;
    s32 outside;
    s32 sideP;
    s32 sideC;

    x1 = arg0->x[1];
    x2 = arg0->x[2];
    z2 = arg0->z[2];
    z1 = arg0->z[1];
    outside = 0;
    x0 = arg0->x[0];
    z0 = arg0->z[0];
    cx = (x0 + (f64)(x2 + x1) * 0.5) * 0.5;
    cz = (z0 + (f64)(z2 + z1) * 0.5) * 0.5;
    i = 0;
    do {
        switch (i) {
        case 0:
            dx = x1 - x0;
            dz = z1 - z0;
            ox = x0;
            oz = z0;
            break;
        case 1:
            dx = x2 - x0;
            dz = z2 - z0;
            ox = x0;
            oz = z0;
            break;
        case 2:
            dx = x2 - x1;
            dz = z2 - z1;
            ox = x1;
            oz = z1;
            break;
        }
        a = (arg1 - ox) * dz;
        b = (arg2 - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        i++;
        if (b <= a) {
            sideP = 1;
        } else {
            sideP = -1;
        }
        if (c >= 0.0) {
            sideC = 1;
        } else {
            sideC = -1;
        }
        if (sideC != sideP) {
            outside = 1;
        }
    } while (i != 3);
    return outside == 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_80669E04.s")
#endif

void gunzip(void *, void *, void *);
void heapFreeDeferred(void *);
extern void *D_80748E14;
void func_8066B5F4(void);
s32 func_8066B4D4(s32, s32, s32 *, s32 *);
s32 collisionBstLookupAndDecrementByHash();
void collisionBstDeleteByHash();
void assetSetTableEntry(s32, s32, s32);
extern s32 D_807F9678;
extern u8 D_807F967C;
extern u8 D_807F967D;
extern s32 *D_807F95A8[];
extern u8 D_80748E18[];
extern s32 *D_807FB1A0[];
s32 collisionCheckBoxTriangleWinding();
void func_8066ACA4();
typedef struct {
    void *unk0;
    void *unk4;
    u8 unk8;
} DmaQueueEntry;

typedef struct {
    u8 pad0[0x48];
    u32 unk48;
    u32 unk4C;
    u32 unk50;
} Col6C_StructA64C;

#ifdef NON_MATCHING
typedef struct {
    u8 pad0[0x24];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    u8 pad48[0x56 - 0x48];
    u8 unk56;
} Col6C_Tri;

struct CollisionBoxTriangle;
s32 collisionCheckBoxTriangleBoundsXZ(struct CollisionBoxTriangle *, f32, f32);
u8 func_8066A988(struct CollisionBoxTriangle *, f32, f32);
void func_8066A64C(s32, Actor *, Col6C_StructA64C *, f32, f32, f32);
void collisionRecordBoxTriangle(void *, f32);

extern s8 D_807F94AD;

s32 func_8066A08C(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    f32 pad;
    Col6C_Tri *hit_tri;
    f32 pad128[6];
    f64 sp108;
    f32 pad108[22];
    f32 hit_y;
    f32 padAC[4];
    Actor *hit_actor;
    f32 pad98[2];
    f32 sp8C;
    ActorEntry *entry;
    f32 sp84;
    f32 sp80;
    f32 sp78;
    f32 temp_fa1;
    f32 temp_fs1;
    f32 y;
    f32 temp_ft5;
    f64 temp_fa0;
    f64 ny;
    f64 nz;
    f64 temp_fs2;
    f64 temp_fs3;
    f64 nx;
    f64 temp_ft4;
    f64 temp_fv0;
    f64 temp_fv1;
    f64 d;
    s32 hit;
    s32 i;
    s32 j;
    Actor *actor;
    Col6C_Tri *tri;
    u16 actor_count;

    hit = 0;
    hit_y = 999999.0f;
    (void)2000.0; // FAKE: keeps the first 2000.0 rodata literal slot
    actor_count = gActiveActorCount;
    i = 0;
    if ((s32)actor_count > 0) {
        entry = gActiveActors;
        do {
            actor = entry->actor;
            if (!(actor->unk60 & 0x2000)) {
                if (actor->unk140 != NULL && arg0 != actor && (actor->unk60 & 0x10)) {
                    tri = actor->unk140->unk98;
                    j = 0;
                    if (actor->unk140->unk94 > 0) {
                        do {
                            if ((collisionCheckBoxTriangleBoundsXZ((struct CollisionBoxTriangle *)tri, arg1, arg2) != 0) &&
                                (func_8066A988((struct CollisionBoxTriangle *)tri, arg1, arg2) != 0) &&
                                (tri->unk56 != 0) &&
                                ((temp_fa1 = tri->unk24,
                                  sp8C = tri->unk28,
                                  temp_ft5 = tri->unk30,
                                  sp84 = tri->unk34,
                                  temp_fa0 = (f64)(temp_fa1 - sp8C),
                                  temp_fs1 = tri->unk3C,
                                  sp80 = tri->unk40,
                                  temp_ft4 = (f64)(temp_ft5 - sp84),
                                  temp_fv0 = (f64)(temp_fs1 - sp80),
                                  temp_fs2 = (f64)(temp_fa1 - tri->unk2C),
                                  temp_fs3 = (f64)(temp_ft5 - tri->unk38),
                                  sp78 = sp8C,
                                  temp_fv1 = (f64)(temp_fs1 - tri->unk44),
                                  nx = (temp_ft4 * temp_fv1) - (temp_fv0 * temp_fs3),
                                  ny = (temp_fv0 * temp_fs2) - (temp_fa0 * temp_fv1),
                                  nz = (temp_fa0 * temp_fs3) - (temp_ft4 * temp_fs2),
                                  d = -(((f64)sp80 * nz) + ((nx * (f64)sp78) + (ny * (f64)sp84))),
                                  0.01 < ny * 2000.0) || ny * 2000.0 < -0.01)) {
                                    if (arg0 != NULL) {
                                        if (D_807F94BC == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                                        func_80666D88(arg3, (f32)((2000.0 * (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)))) - 1000.0), 0, arg0, 0);
                                    }
                                    if (arg2) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                                    if (D_807F94BC != 0) {
                                        collisionRecordBoxTriangle(tri, (f32)((2000.0 * (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)))) - 1000.0));
                                    }
                                    if (collisionCheckBoxTriangleWinding(tri) != 0) {
                                        y = (f32)((2000.0 * (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)))) - 1000.0);
                                        if (mathCheckCloserFloatThreshold(hit_y, y, (f32)((f64)arg3 + 4.0), 0) != 0) {
                                            hit_tri = tri;
                                            hit_actor = actor;
                                            hit = 1;
                                            hit_y = y;
                                        }
                                    }
                            }
                            j++;
                            tri++;
                        } while (j < actor->unk140->unk94);
                    }
                }
            }
            i++;
            entry++;
        } while (i < (s32)gActiveActorCount);
    }

    if (hit != 0 && mathCheckCloserFloatThreshold(*arg4, hit_y, (f32)((f64)arg3 + 4.0), 0) != 0) {
        *arg4 = hit_y;
        func_8066ACA4(arg0, hit_tri, 1);
        if (hit_actor->unk68 & 8) {
            D_807F94AD = 1;
        }
        if (arg0 != NULL) {
            func_8066A64C((s32)arg0, hit_actor, (Col6C_StructA64C *)hit_tri, arg1, hit_y, arg2);
            if (D_807F94BC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
    }
    return hit;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066A08C.s")
#endif

void collisionRecordBoxTriangle(void *arg0, f32 arg1) {
    if (D_807F9510 != 0xA) {
        D_807F94C0[D_807F9510].unk0 = arg1;
        if (collisionCheckBoxTriangleWinding(arg0) != 0) {
            D_807F94C0[D_807F9510].unk6 = 1;
        } else {
            D_807F94C0[D_807F9510].unk6 = 2;
        }
        func_8066ACA4(0, arg0, 0, D_807F94C0);
        D_807F94C0[D_807F9510].unk4 = D_807F94A8;
        D_807F9510++;
    }
}

extern u8 D_807444FC;
extern Actor *D_807F9470;
extern f32 D_807F9474;
extern f32 D_807F9478;
extern f32 D_807F947C;
extern u32 D_807F9480;
extern s8 D_807F94B2;

void matrix4Invert(float [4][4], float [4][4]);

void func_8066A64C(s32 arg0, Actor *arg1, Col6C_StructA64C *arg2, f32 arg3, f32 arg4, f32 arg5) {
    float sp78[4][4];
    float sp38[4][4];
    ActorSub140 *sub;
    s32 idx;
    Mtx *mtx;

    D_807F9470 = arg1;
    sub = arg1->unk140;
    if (D_8076A064 == sub->unk88) {
        idx = D_807444FC;
    } else {
        idx = (D_807444FC ^ 1) & 0xFF;
    }
    mtx = (Mtx *)((Mtx **)&sub->unk74)[idx];
    if ((arg2->unk4C != arg2->unk48) || (arg2->unk50 != arg2->unk48)) {
        D_807F94B2 = 1;
    }
    D_807F9480 = arg2->unk48;
    if (arg2->unk48 == -1) {
        memcpy(sp78, (void *)sub->unk70, 0x40);
    } else {
        guMtxL2F(sp78, (Mtx *)(((arg2->unk48 >> 6) << 6) + (u8 *)mtx));
    }
    matrix4Invert(sp38, sp78);
    guMtxXFMF(sp38, arg3, arg4, arg5, &D_807F9474, &D_807F9478, &D_807F947C);
}

void func_8066A75C(Actor *actor, u32 arg1, f32 *arg2, f32 arg3, f32 *arg4) {
    s32 idx;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    ActorSub140 *sub;
    Mtx *mtx;
    {
        float sp28[4][4];

        sp78 = *arg2;
        sp74 = *arg4;
        sub = actor->unk140;
        if (D_8076A064 == sub->unk88) {
            idx = D_807444FC;
        } else {
            idx = D_807444FC ^ 1;
            idx = idx & 0xFF; // FAKE: split mask steers sub/idx v0/v1 allocation
        }
        mtx = ((Mtx **)&sub->unk74)[idx];
        if (arg1 == -1) {
            memcpy(sp28, (void *)sub->unk70, 0x40);
        } else {
            guMtxL2F(sp28, (Mtx *)(((arg1 >> 6) << 6) + (u8 *)mtx));
        }
        guMtxXFMF(sp28, sp78, arg3, sp74, arg2, &sp70, arg4);
    }
}

typedef struct CollisionBoxTriangle {
    u8 pad0[0x24];
    CollisionTriF tri;
} CollisionBoxTriangle;

s32 collisionCheckBoxTriangleBoundsXZ(CollisionBoxTriangle *arg0, f32 arg1, f32 arg2) {
    s32 pad;
    f32 min_z;
    f32 max_x;
    f32 x0;
    f32 x1;
    f32 min_x;
    f32 x2;
    f32 z0;
    f32 z1;
    f32 z2;
    f32 max_z;

    min_x = ((x0 = arg0->tri.x[0]) < (x1 = arg0->tri.x[1])) ? x0 : x1;
    x2 = arg0->tri.x[2];
    min_x = (min_x < x2) ? min_x : x2;

    z0 = arg0->tri.z[0];
    z1 = arg0->tri.z[1];
    min_z = (z0 < z1) ? z0 : z1;
    z2 = arg0->tri.z[2];
    min_z = (min_z < z2) ? min_z : z2;

    max_x = (x1 < x0) ? x0 : x1;
    max_x = (x2 < max_x) ? max_x : x2;

    max_z = (z1 < z0) ? z0 : z1;
    max_z = (z2 < max_z) ? max_z : z2;

    if ((arg1 < min_x) || (max_x < arg1) || (arg2 < min_z) || (max_z < arg2)) {
        return 0;
    }
    return 1;
}

#ifdef NON_MATCHING
u8 func_8066A988(CollisionBoxTriangle *arg0, f32 arg1, f32 arg2) {
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f32 x0;
    f32 x1;
    f32 x2;
    f32 z0;
    f32 z1;
    f32 z2;
    f64 cx;
    f64 cz;
    f64 a;
    f64 b;
    f64 c;
    s32 i;
    s32 outside;
    s32 sideP;
    s32 sideC;

    x1 = arg0->tri.x[1];
    x2 = arg0->tri.x[2];
    z2 = arg0->tri.z[2];
    z1 = arg0->tri.z[1];
    outside = 0;
    x0 = arg0->tri.x[0];
    z0 = arg0->tri.z[0];
    cx = (x0 + (f64)(x2 + x1) * 0.5) * 0.5;
    cz = (z0 + (f64)(z2 + z1) * 0.5) * 0.5;
    i = 0;
    do {
        switch (i) {
        case 0:
            dx = x1 - x0;
            dz = z1 - z0;
            ox = x0;
            oz = z0;
            break;
        case 1:
            dx = x2 - x0;
            dz = z2 - z0;
            ox = x0;
            oz = z0;
            break;
        case 2:
            dx = x2 - x1;
            dz = z2 - z1;
            ox = x1;
            oz = z1;
            break;
        }
        a = (arg1 - ox) * dz;
        b = (arg2 - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        i++;
        if (b <= a) {
            sideP = 1;
        } else {
            sideP = -1;
        }
        if (c >= 0.0) {
            sideC = 1;
        } else {
            sideC = -1;
        }
        if (sideC != sideP) {
            outside = 1;
        }
    } while (i != 3);
    return outside == 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066A988.s")
#endif

typedef struct CollisionBoxTriangleWork {
    u8 pad0[0x24];
    CollisionTriF tri;
} CollisionBoxTriangleWork;

s32 collisionCheckBoxTriangleWinding(CollisionBoxTriangleWork *arg0) {
    CrossProductStack sp;

    sp.v1[0] = arg0->tri.x[2] - arg0->tri.x[0];
    sp.v1[2] = arg0->tri.z[2] - arg0->tri.z[0];
    sp.v0[0] = arg0->tri.x[1] - arg0->tri.x[0];
    sp.v0[2] = arg0->tri.z[1] - arg0->tri.z[0];
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066ACA4.s")

extern s32 D_8000DDCC;
extern s32 D_807F9520;
extern s32 *D_807F9528[];
extern void *D_807F9628[];
extern s32 D_807F9680;
extern u8 D_807FB220;
extern u8 D_807FB221;
void *func_8066B0F8(s32, s32, s32, s32);

void collisionInitTables(void) {
    s32 i;
    s32 sp40;

    sp40 = 0x80;
    D_807F9520 = (s32)func_80610FE8(0x80);
    func_8060B140(D_8000DDCC, (void *)D_807F9520, &sp40, 0, 0, 0, 0);

    for (i = 0; i < 0x20; i++) {
        D_807F9528[i] = 0;
        D_807F95A8[i] = 0;
    }

    for (i = 0; i < 0x14; i++) {
        D_807F9628[i] = 0;
    }

    D_807F9680 = 0;
    D_807F967C = 0;
    D_807F9678 = 0;
    D_807F967D = 0;

    for (i = 0; i < 0x20; i++) {
        if (D_80748E18[i] != 0) {
            D_807FB1A0[i] = func_8066B0F8(0x1A, i, 1, 1);
        } else {
            D_807FB1A0[i] = NULL;
        }
    }

    D_807FB220 = 0;
    D_807FB221 = 0;
}

void assetInflateAndFree(void *arg0, void *arg1) {
    void *sp24;
    void *sp20;

    sp24 = arg0;
    sp20 = arg1;
    if (D_80748E14 == NULL) {
        D_80748E14 = func_80610FE8(0x2400);
    }
    gunzip(&sp24, &sp20, D_80748E14);
    heapFree(arg0);
}

extern DmaQueueEntry D_807FA8A0[];
extern s8 D_80746834;
extern OSMesgQueue D_807656D0;

void dmaDrainQueueAndFreeBuffer(void) {
    s32 i;

    i = 0;
    if (D_807F9680 > 0) {
        do {
            D_80746834 = 7;
            osRecvMesg(&D_807656D0, NULL, 1);
            D_80746834 = 0;
            if (D_807FA8A0[i].unk8 != 0) {
                assetInflateAndFree(D_807FA8A0[i].unk0, D_807FA8A0[i].unk4);
            }
        } while (++i < D_807F9680);
    }
    if (D_80748E14 != NULL) {
        heapFree(D_80748E14);
        D_80748E14 = NULL;
    }
    D_807F9680 = 0;
}

s32 assetGetSize(s32 arg0, s32 arg1) {
    s32 sp1C;
    s32 sp18;

    func_8066B5F4();
    func_8066B4D4(arg0, arg1, &sp1C, &sp18);
    if (sp18 == 0) {
        return 0;
    }
    return sp1C;
}

s32 assetGetCachedSizeOrResolve(s32 arg0, s32 arg1) {
    s32 sp1C;
    s32 sp18;

    if (D_80748E18[arg0] != 0) {
        sp18 = D_807FB1A0[arg0][arg1];
    } else {
        func_8066B5F4();
        func_8066B4D4(arg0, arg1, &sp1C, &sp18);
    }
    return sp18;
}

void func_8066B0DC(void) {
    D_807F967C = 1;
}

void assetSetRomTableOffset(s32 arg0) {
    D_807F9678 = arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066B0F8.s")

void assetSetImmediateFree(void) {
    D_807F967D = 1;
}

void assetFreeBuffer(void *arg0, s32 arg1, s32 arg2) {
    s32 sp1C;
    s32 sp18;

    if (collisionBstLookupAndDecrementByHash(arg0) == 0) {
        collisionBstDeleteByHash(arg0, &sp1C, &sp18);
        assetSetTableEntry(sp1C, sp18, 0);
        if (D_807F967D == 0) {
            heapFreeDeferred(arg0);
        } else {
            heapFree(arg0);
        }
    }
    D_807F967D = 0;
}

void assetSetTableEntry(s32 arg0, s32 arg1, s32 arg2) {
    if (D_807F95A8[arg0] != NULL) {
        D_807F95A8[arg0][arg1] = arg2;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066B4D4.s")

s32 assetGetTableEntry(s32 arg0, s32 arg1) {
    s32 *ptr = D_807F95A8[arg0];
    s32 ret = 0;

    if (ptr != NULL) {
        ret = ptr[arg1];
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066B5F4.s")


typedef struct CollisionBstNodeBase {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[3];
    /* 0x07 */ u8 unk7;
    /* 0x08 */ u16 pad8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ struct CollisionBstNodeBase *left;
    /* 0x18 */ struct CollisionBstNodeBase *right;
} CollisionBstNodeBase;

s32 collisionBstCountNodes(CollisionBstNodeBase *node) {
    s32 count;

    if (node == NULL) {
        return 0;
    }
    count = collisionBstCountNodes(node->left);
    return collisionBstCountNodes(node->right) + count + 1;
}

u32 collisionGetBucketIndex(u32);
void collisionBstLookupOrAssert();

void collisionBstLookupByHash(s32 arg0, s32 arg1, s32 arg2) {
    collisionBstLookupOrAssert(D_807F9628[collisionGetBucketIndex(arg0)], arg0, arg1, arg2);
}

typedef struct CollisionBstNode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x14 */ struct CollisionBstNode *left;
    /* 0x18 */ struct CollisionBstNode *right;
} CollisionBstNode;

void faultSetMessage(s32, s32, s32, s32);
void collisionQueueSearch(s32, u8 *, u16 *, s32 *);
void collisionBstLookupOrAssert(CollisionBstNode *arg0, u32 arg1, s32 *arg2, s32 *arg3) {
    u8 sp2F;
    u16 sp2C;
    s32 sp28;

    if (arg0 == NULL) {
        sp2F = 0;
        sp2C = 0;
        sp28 = 0;
        collisionQueueSearch(arg1, &sp2F, &sp2C, &sp28);
        faultSetMessage(7, sp2F, sp2C, D_8076A064 - sp28);
    }
    if (arg1 == arg0->unk0) {
        *arg2 = arg0->unk4;
        *arg3 = arg0->unk8;
    } else if (arg0->unk0 < arg1) {
        collisionBstLookupOrAssert(arg0->right, arg1, arg2, arg3);
    } else {
        collisionBstLookupOrAssert(arg0->left, arg1, arg2, arg3);
    }
}

CollisionBstNode *collisionBstInsert();

void collisionBstInsertByHash(s32 arg0, s32 arg1, s32 arg2) {
    u32 index = collisionGetBucketIndex(arg0);

    D_807F9628[index] = collisionBstInsert(D_807F9628[index], arg0, arg1, arg2);
}

CollisionBstNode *collisionBstInsert(CollisionBstNode *node, u32 arg1, s32 arg2, s32 arg3) {
    if (node == NULL) {
        node = (CollisionBstNode *)func_80610FE8(sizeof(CollisionBstNode));
        node->unkC = 1;
        node->unk0 = arg1;
        node->unk4 = arg2;
        node->unk8 = arg3;
        node->unk10 = D_807F967C;
        node->right = NULL;
        node->left = NULL;
    } else if (arg1 == node->unk0) {
        node->unkC++;
        if (D_807F967C) {
            node->unk10 = 1;
        }
    } else if (node->unk0 < arg1) {
        node->right = collisionBstInsert(node->right, arg1, arg2, arg3);
    } else {
        node->left = collisionBstInsert(node->left, arg1, arg2, arg3);
    }
    return node;
}

s32 collisionBstLookupAndDecrement();

s32 collisionBstLookupAndDecrementByHash(s32 arg0) {
    return collisionBstLookupAndDecrement(D_807F9628[collisionGetBucketIndex(arg0)], arg0);
}

typedef struct CollisionQueueEntry {
    s32 unk0;
    s32 unk4;
    u16 unk8;
    u8 unkA;
} CollisionQueueEntry;

extern CollisionQueueEntry D_807FB228[];

void collisionQueueSearch(s32 arg0, u8 *arg1, u16 *arg2, s32 *arg3) {
    s32 i;

    if ((i = D_807FB221 - 1) < 0) {
        i = 0x3F;
    }
    while (i != D_807FB220) {
        if (arg0 == D_807FB228[i].unk4) {
            *arg1 = D_807FB228[i].unkA;
            *arg2 = D_807FB228[i].unk8;
            *arg3 = D_807FB228[i].unk0;
            break;
        }
        if (--i < 0) {
            i = 0x3F;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066BAB8.s")

void func_8066BAB8();

s32 collisionBstLookupAndDecrement(CollisionBstNodeBase *node, u32 arg1) {
    u8 sp2F;
    u16 sp2C;
    s32 sp28;

    if (node == NULL) {
        sp2F = 0;
        sp2C = 0;
        sp28 = 0;
        collisionQueueSearch(arg1, &sp2F, &sp2C, &sp28);
        return 0;
    }
    if (arg1 == node->unk0) {
        if (node->unk10 == 0) {
            node->unkC--;
        }
        func_8066BAB8(arg1, node->unk7, node->unkA);
        return node->unkC;
    }
    if (node->unk0 < arg1) {
        return collisionBstLookupAndDecrement(node->right, arg1);
    }
    return collisionBstLookupAndDecrement(node->left, arg1);
}

CollisionBstNode *collisionBstDelete();

void collisionBstDeleteByHash(s32 arg0, s32 arg1, s32 arg2) {
    u32 index = collisionGetBucketIndex(arg0);

    D_807F9628[index] = collisionBstDelete(D_807F9628[index], arg0, arg1, arg2);
}

CollisionBstNode *collisionBstExtractMin();

CollisionBstNode *collisionBstDelete(CollisionBstNode *node, u32 key, s32 *out_val1, s32 *out_val2) {
    CollisionBstNode *old;

    if (node != NULL) {
        if (key == node->unk0) {
            *out_val1 = node->unk4;
            *out_val2 = node->unk8;
            if (node->left == NULL && node->right == NULL) {
                heapFree(node);
                node = NULL;
            } else if (node->left == NULL) {
                old = node;
                node = node->right;
                heapFree(old);
            } else if (node->right == NULL) {
                old = node;
                node = node->left;
                heapFree(old);
            } else {
                node->right = collisionBstExtractMin(node->right, &node->unk0, &node->unk4, &node->unk8, &node->unkC, &node->unk10);
            }
        } else if (node->unk0 < key) {
            node->right = collisionBstDelete(node->right, key, out_val1, out_val2);
        } else {
            node->left = collisionBstDelete(node->left, key, out_val1, out_val2);
        }
    }
    return node;
}

CollisionBstNode *collisionBstExtractMin(CollisionBstNode *node, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, u8 *arg5) {
    void *pad;
    CollisionBstNode *left = node->left;

    if (left == NULL) {
        CollisionBstNode *old;

        *arg1 = node->unk0;
        *arg2 = node->unk4;
        *arg3 = node->unk8;
        *arg4 = node->unkC;
        *arg5 = node->unk10;
        old = node;
        node = node->right;
        heapFree(old);
    } else {
        node->left = collisionBstExtractMin(left, arg1, arg2, arg3, arg4, arg5);
    }
    return node;
}

void collisionBstRebalanceBucket(s32);

void collisionBstRebalanceAll(void) {
    s32 i;

    for (i = 0; i < 20; i++) {
        collisionBstRebalanceBucket(i);
    }
}

typedef struct CollisionBstFlatItem {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
} CollisionBstFlatItem;

void func_8066BFF0(CollisionBstNodeBase *, CollisionBstFlatItem *, s32 *);
void func_8066C0DC(void *, s32, s32);
CollisionBstNodeBase *collisionBstBuildBalanced(CollisionBstFlatItem *, s32, s32);
void collisionBstFreeTree(CollisionBstNodeBase *);

void collisionBstRebalanceBucket(s32 arg0) {
    s32 count;
    void *buffer;
    CollisionBstNodeBase *new_root;
    s32 index;

    index = 0;
    count = collisionBstCountNodes(D_807F9628[arg0]);
    if (count != 0) {
        buffer = func_80610FE8(count * 20);
        func_8066BFF0(D_807F9628[arg0], buffer, &index);
        func_8066C0DC(buffer, 0, count - 1);
        new_root = collisionBstBuildBalanced(buffer, 0, count - 1);
        collisionBstFreeTree(D_807F9628[arg0]);
        D_807F9628[arg0] = new_root;
        heapFree(buffer);
    }
}


void collisionBstFreeTree(CollisionBstNodeBase *node) {
    if (node != NULL) {
        collisionBstFreeTree(node->left);
        collisionBstFreeTree(node->right);
        heapFree(node);
    }
}

CollisionBstNodeBase *collisionBstBuildBalanced(CollisionBstFlatItem *buffer, s32 start, s32 end) {
    CollisionBstNode *node;
    s32 mid;

    node = (CollisionBstNode *)func_80610FE8(sizeof(CollisionBstNode));
    mid = (start + end) / 2;

    node->unk0 = buffer[mid].unk0;
    node->unk4 = buffer[mid].unk4;
    node->unk8 = buffer[mid].unk8;
    node->unkC = buffer[mid].unkC;
    node->unk10 = buffer[mid].unk10;

    if (start != mid) {
        node->left = (CollisionBstNode *)collisionBstBuildBalanced(buffer, start, mid - 1);
    } else {
        node->left = NULL;
    }

    if (end != mid) {
        node->right = (CollisionBstNode *)collisionBstBuildBalanced(buffer, mid + 1, end);
    } else {
        node->right = NULL;
    }

    return (CollisionBstNodeBase *)node;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066BFF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/6AD90/func_8066C0DC.s")

u32 collisionGetBucketIndex(u32 arg0) {
    return (arg0 >> 12) % 20;
}
