#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

extern void *D_80754280;

s32 slotQueueGetAddress(arg0)
u8 arg0;
{
    return (arg0 * 0x2D0) + (s32)D_80754280;
}

typedef struct FcAPlayer {
    u8 pad0[0x284];
    f32 unk284;
    u8 pad288[0x68];
} FcAPlayer;

void func_806F8004(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    f32 sp88[4][4];
    f32 sp48[4][4];
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    sp34 = ((FcAPlayer *)D_807FC924)[D_807FC929].unk284;
    guRotateF(sp88, arg0, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp88, 0.0f, 0.0f, -sp34, &sp3C, &sp40, &sp44);
    guRotateF(sp48, arg1, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp48, sp3C, sp40, sp44, arg2, arg3, arg4);
    sp38 = -sp34 / *arg4;
    *arg2 *= sp38;
    *arg3 *= sp38;
    *arg4 = -sp34;
    *arg2 = (f32)((f64)*arg2 * 10.5);
    *arg3 = (f32)((f64)*arg3 * 10.5);
    *arg4 = (f32)((f64)*arg4 * 10.5);
}

void func_806F8004(f32, f32, f32 *, f32 *, f32 *);

typedef struct R2FCCD0eTransformSlot {
    void *unk0;
    u16 unk4;
    u8 pad6[0xA];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 pad1C[0x14];
} R2FCCD0eTransformSlot;

void slotQueueGetPosition(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if (arg0 < 0) {
        func_806F8004(16.5f, 0.0f, arg1, arg2, arg3);
    } else if (arg0 == 8) {
        func_806F8004((f32)(1.5 - (f64)(((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk4 * 7)), 26.0f, arg1, arg2, arg3);
    } else {
        *arg1 = ((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk10;
        *arg2 = ((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk14;
        *arg3 = ((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk18;
    }
}

typedef struct R2FCCD0cSlot {
    void *unk0;
    u8 pad4[0x1C];
    s32 unk20;
    s32 unk24;
    void *unk28;
    u8 unk2C;
    u8 pad2D[3];
} R2FCCD0cSlot;




typedef struct FcASlot30 {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[0x2A];
} FcASlot30;

void func_806F8278(u8 arg0) {
    s32 sum;
    u16 (*p)[0x2F];
    s32 i;
    s32 j;
    s8 n;
    sum = 0;
    p = (u16 (*)[0x2F])((u8 *)D_807FC950 + (u32)arg0 * 0x306);
    n = 14;
    for (i = 0; i < n; i++) {
        for (j = 0; j < 5; j++) {
            sum += p[j][i + 0x21];
        }
    }
    ((FcASlot30 *)D_80754280)[arg0 * 15 + 9].unk4 = sum;
}

typedef struct L2bSlot {
    u16 *unk0;
    u16 unk4;
    u8 unk6;
    u8 unk7;
    s32 unk8;
    s32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 pad1C[4];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 unk2C;
    u8 unk2D;
    u8 pad2E[2];
} L2bSlot;

extern s16 D_80744544;
extern u16 D_80750AC4;
extern u16 D_80750AC8;
extern void *D_80754284;
void *func_80610FE8(s32);
void heapClearBlock(void *);
s32 func_806C8DE0(s32);
s32 func_806F8EDC();
void func_806FB370(u8, u8, u8);
s32 func_807142D8();
#ifndef NON_MATCHING
void func_806F8278(u8);
#endif
extern s32 func_805FF030();

/* Initialises the per-player slot queue (15 slots of 0x30 bytes per player): sets each slot's text pointer, size and
 * screen position (func_806F8004). Formatting is load-bearing: the unk8/unkC stores share one line and the dead
 * `if (player && player)` fixes the register choice for the u8 argument. */
void func_806F833C(s32 arg0) {
    u32 j;
    s32 i;
    s16 sp96;
    u8 *fp;
    u8 sp8F;
    L2bSlot *base;
    u8 *sp84;
    s32 off;
    s8 flag;
    u8 player;

    sp96 = D_80744544;
    sp8F = func_805FF030(D_8076A0AB, 1);
    if (D_807FC928 >= 2) {
        sp96 = 0;
    }
    if (arg0 != 0) {
        D_80754280 = func_80610FE8(D_807FC928 * 0x2D0);
        heapClearBlock(D_80754280);
        D_80754284 = 0;
    }
    if (D_807FC928 > 0) {
        fp = (u8 *)D_807FC950;
        i = 0;
        do {
            sp84 = (u8 *)(func_806C8DE0(i) * 0x5E);
            sp84 = (u8 *)((s32)fp + (s32)sp84);
            player = i;
            if (player && player) {
            }
            base = (L2bSlot *)slotQueueGetAddress(player);
            j = 0;
            off = 0;
            do {
                flag = 0;
                if (arg0 != 0) {
                    (base + j)->unk20 = 0;
                    (base + j)->unk7 = 0;
                    (base + j)->unk24 = 0;
                    (base + j)->unk6 = 0;
                    (base + j)->unk28 = 0;
                    (base + j)->unk2C = 0;
                }
                if (func_807142D8() != 0) {
                    (base + j)->unk2C = 1;
                }
                switch (j) {
                case 0:
                    (base + j)->unk0 = &((u16 *)(sp84 + 0xA))[sp8F];
                    (base + j)->unk8 = 0x1E; (base + j)->unkC = 0x26;
                    func_806F8004(15.5f, 26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 13:
                    (base + j)->unk0 = NULL;
                    (base + j)->unk8 = 0x122; (base + j)->unkC = 0x26;
                    func_806F8004(-5.5f, -26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 8:
                    (base + j)->unk0 = &((u16 *)(sp84 + 0x42))[sp8F];
                    (base + j)->unk8 = 0x1E; (base + j)->unkC = 0x48;
                    func_806F8004(1.5f, 26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 12:
                    (base + j)->unk0 = NULL;
                    (base + j)->unk8 = 0xC2; (base + j)->unkC = 0xD0;
                    func_806F8004(-26.5f, 26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 10:
                    (base + j)->unk0 = NULL;
                    (base + j)->unk8 = 0x52; (base + j)->unkC = 0xD0;
                    func_806F8004(-26.5f, 26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 9:
                    (base + j)->unk0 = NULL;
                    (base + j)->unk8 = 0x7A; (base + j)->unkC = 0xD0;
                    break;
                case 5:
                    if (sp96 & 0x20) {
                        *(s16 *)(fp+0x2F6) = func_806F8EDC(5, i);
                        flag = 1;
                    }
                    (base + j)->unk0 = (u16 *)(fp + 0x2F6);
                    (base + j)->unk8 = 0x122; (base + j)->unkC = 0x8C;
                    func_806F8004(-5.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 2:
                    (base + j)->unk0 = (u16 *)(fp + 0x2F0);
                    (base + j)->unk8 = 0x122; (base + j)->unkC = 0x48;
                    func_806F8004(8.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 3:
                    if (sp96 & 0x4) {
                        *(s16 *)(fp+0x2F2) = func_806F8EDC(3, i);
                        flag = 1;
                    }
                    (base + j)->unk0 = (u16 *)(fp + 0x2F2);
                    (base + j)->unk8 = 0x122; (base + j)->unkC = 0x48;
                    func_806F8004(8.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 4:
                    if (sp96 & 0x8) {
                        *(s16 *)(fp+0x2F4) = func_806F8EDC(4, i);
                        flag = 1;
                    }
                    (base + j)->unk0 = (u16 *)(fp + 0x2F4);
                    (base + j)->unk8 = 0x122; (base + j)->unkC = 0x6A;
                    func_806F8004(1.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 6:
                    if (sp96 & 0x10) {
                        *(s16 *)(fp+0x2F8) = func_806F8EDC(6, i);
                        flag = 1;
                    }
                    (base + j)->unk0 = (u16 *)(fp + 0x2F8);
                    (base + j)->unk8 = 0x122; (base + j)->unkC = 0xD0;
                    func_806F8004(-19.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 11:
                    (base + j)->unk0 = &D_80750AC4;
                    (base + j)->unk8 = 0x122; (base + j)->unkC = 0x26;
                    func_806F8004(16.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 1:
                    if (sp96 & 0x2) {
                        *(s16 *)(sp84+6) = func_806F8EDC(1, i);
                        flag = 1;
                    }
                    (base + j)->unk0 = (u16 *)(sp84 + 6);
                    (base + j)->unk8 = 0x122; (base + j)->unkC = 0x26;
                    func_806F8004(16.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 7:
                    if (sp96 & 0x40) {
                        *(s16 *)(sp84+8) = func_806F8EDC(7, i);
                        flag = 1;
                    }
                    (base + j)->unk0 = (u16 *)(sp84 + 8);
                    (base + j)->unk8 = 0x122; (base + j)->unkC = 0xAE;
                    func_806F8004(-12.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 14:
                    (base + j)->unk0 = &D_80750AC8;
                    (base + j)->unk8 = 0x1E; (base + j)->unkC = 0x26;
                    func_806F8004(15.5f, 26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                }
                (base + j)->unk2D = flag;
                if (flag & 0xFF) {
                    (base + j)->unk2C = 1;
                }
                off += 0x30;
                if ((base + j)->unk0 != NULL) {
                    (base + j)->unk4 = *(base + j)->unk0;
                }
                j++;
            } while (j != 0xF);
            func_806F8278(player);
            i++;
            fp += 0x306;
        } while (i < D_807FC928);
    }
    if (D_8076A0A8 == 0x11 || D_8076A0A8 == 0x52) {
        func_806FB370(5, 0, 1);
    }
}


void func_806F8A8C(u8 arg0, u8 arg1, s32 arg2) {
    *(s16 *)((u8 *)slotQueueGetAddress(arg1 & 0xFF) + (arg0 * 0x30) + 4) = arg2;
}

s32 flagGridSumRows(s32, s32, s32, s32);

extern s32 func_805FF030();
u16 func_806F8AD4(u8 arg0, u8 arg1) {
    u16 var_a2;
    u16 sp26;
    s32 temp_v0;
    s32 sp1C;
    u8 *pa;
    R2FCCD0cSlot *slot;

    pa = &arg1;
    sp26 = 0;
    var_a2 = sp26;
    slot = (R2FCCD0cSlot *)slotQueueGetAddress(arg1) + arg0;
    switch (slot->unk2C) {
    case 2:
        break;
    case 0:
        if ((u16 *)slot->unk0 != NULL) {
            if (D_8076A0AB && D_8076A0AB) {}
            var_a2 = *(u16 *)slot->unk0;
        } else {
            sp1C = func_806C8DE0(arg1);
            temp_v0 = func_805FF030(D_8076A0AB, 1);
            if (arg0 != 0xA) {
                if (arg0 == 0xC) {
                    var_a2 = flagGridSumRows(0x1D5, temp_v0, temp_v0, sp1C);
                }
            } else {
                var_a2 = flagGridSumRows(0x225, temp_v0, temp_v0, sp1C);
            }
        }
        break;
    case 1:
        var_a2 = 0x14;
        break;
    }
    return var_a2;
}

void slotQueueUpdate(s32 arg0, u8 arg1, s32 arg2) {
    R2FCCD0cSlot *temp_v0;

    if ((D_807FC928 < 2) && (func_807142D8() == 0)) {
        if (arg0 == 8) {
            slotQueueUpdate(9, arg1, arg2 + 0xA);
            if (D_8076A0A8 == 0xF) {
                return;
            }
        }
        ((R2FCCD0cSlot *)D_80754280)[arg0].unk24 = arg1;
        temp_v0 = &((R2FCCD0cSlot *)D_80754280)[arg0];
        if (temp_v0->unk20 == 0) {
            temp_v0->pad4[3] = arg2;
        } else {
            temp_v0->pad4[3] = 0;
        }
        ((R2FCCD0cSlot *)D_80754280)[arg0].unk20 = 1;
        temp_v0 = &((R2FCCD0cSlot *)D_80754280)[arg0];
        if (temp_v0->pad4[2] == 0) {
            temp_v0->pad4[2] = arg1 != 0;
        }
    }
}


void func_806F8CB0(s32 arg0) {
    s32 var_v1;
    void *var_v0;

    if (arg0 == 8) {
        var_v0 = *(void **)((u8 *)D_80754280 + (arg0 * 0x30) + 0x28);
        var_v1 = 0;
        if (var_v0 != NULL) {
            do {
                *(s32 *)((u8 *)var_v0 + 0xC) = var_v1;
                var_v0 = *(void **)((u8 *)var_v0 + 0x18);
                var_v1 += 2;
            } while (var_v0 != NULL);
        }
    }
}


void slotQueueClearFlags(arg0, arg1)
s32 arg0;
u8 arg1;
{
    s32 temp_v0;

    temp_v0 = arg0 * 0x30;
    *((u8 *)D_80754280 + temp_v0 + 7) = 0;
    *((u8 *)D_80754280 + temp_v0 + 6) = 0;
    if (arg0 == 8) {
        slotQueueCancel(9, 0);
    }
}


int slotQueueCancel(arg0)
s32 arg0;
{
    s32 mask;
    void *var_v0 = D_80754284;

    *((u8 *)D_80754280 + (arg0 * 0x30) + 0x1C) = 0;
    if (var_v0 != NULL) {
        mask = ~(1 << arg0);
        do {
            *(s32 *)var_v0 &= mask;
            var_v0 = *(void **)((u8 *)var_v0 + 4);
        } while (var_v0 != NULL);
    }
    slotQueueClearFlags();
}

extern s32 func_805FF030();

void func_806F8DC4(s8 *arg0, s32 arg1, s32 arg2) {
    s32 sp1C;
    s32 temp_a3;
    s32 temp_v0;

    sp1C = func_805FF030(D_8076A0AB, 1);
    temp_v0 = func_806C8DE0(0);
    temp_a3 = temp_v0;
    *arg0 = 0x7F;
    if (arg2 != 8) {
        if (arg2 != 0xA) {
            if ((arg2 == 0xC) && (flagGridSumRows(0x1D5, sp1C, sp1C, temp_a3) != 0)) {
                *(u8 *)arg0 = 0xFF;
            }
        } else if (flagGridSumRows(0x225, sp1C, sp1C, temp_a3) != 0) {
            *(u8 *)arg0 = 0xFF;
        }
    } else if (arg1 < ((u16 *)&D_807FC950[temp_v0][0x42])[sp1C]) {
        *(u8 *)arg0 = 0xFF;
    }
}

extern s32 flagCountRange(s32, s32, s32);

s32 func_806F8EB4(void) {
    return flagCountRange(0x24D, 0x14, 0);
}

extern s32 func_806F6EDC();
extern s32 flagGet(s32, s32);
extern u8 D_807FC953[];
extern u8 D_807FC954[];

s32 func_806F8EDC(s32 arg0, s32 arg1) {
    s32 temp_t5;
    s32 temp_v0;
    s32 var_a0;
    s32 var_v1;
    u8 temp_a0;
    s32 var_v0;

    temp_v0 = func_806C8DE0(arg1);
    var_a0 = 0x64;
    switch (arg0) {
    case 1:
        if (arg1 == 0) {}
        var_a0 = 0x3E7;
        break;
    case 2:
        var_a0 = ((1 << D_807FC953[(arg1 * 0x306) + (temp_v0 * 0x5E)]) * 0x32) & 0xFFFF;
        break;
    case 3:
        if (D_807FC928 >= 2) {
            var_a0 = 0xA;
        } else {
            var_a0 = ((1 << D_807FC953[(arg1 * 0x306) + (temp_v0 * 0x5E)]) * 0x32) & 0xFFFF;
        }
        break;
    case 4:
        var_a0 = ((D_807FC953[(arg1 * 0x306) + (temp_v0 * 0x5E)] * 5) + 0x14) & 0xFFFF;
        break;
    case 5:
        if (D_807FC928 >= 2) {
            var_a0 = 0xBB8;
        } else if (func_806F6EDC() != 0) {
            var_a0 = ((func_806F8EB4() * 0x96) + 0xBB8) & 0xFFFF;
        } else {
            var_a0 = 0;
        }
        break;
    case 7:
        if (D_807FC928 >= 2) {
            var_a0 = 0x14;
        } else {
            temp_a0 = D_807FC954[(arg1 * 0x306) + (temp_v0 * 0x5E)];
            var_v1 = 1;
            if (temp_a0 & 1) {
                var_v0 = temp_a0;
                if (temp_a0 != 0) {
                    do {
                        var_v1 += 1;
                        var_v0 >>= 1;
                    } while (var_v0 != 0);
                }
                var_a0 = (var_v1 * 5) & 0xFFFF;
            } else {
                var_a0 = 0;
            }
        }
        break;
    case 6:
        if (flagGet(0x179, 0) != 0) {
            var_a0 = (func_806F8EB4() + 0xA) & 0xFFFF;
        } else {
            var_a0 = 0;
        }
        break;
    case 9:
        var_a0 = 0xC8;
        break;
    }
    return var_a0;
}

#ifdef NON_MATCHING
typedef struct NM2StatSlot {
    u16 *unk0;
    u8 pad4[0x28];
    u8 unk2C;
    u8 unk2D;
    u8 pad2E[2];
} NM2StatSlot;

extern u8 D_8074E77C;
extern s32 func_805FEF10(s16 *);
extern void func_80687C48(void);
extern void flagSet(s16, s32, s32);
extern s16 flagGridIndex(s32, s32, u8, s32);
extern void sfxAllocateChannel(s32, f32);

void func_806F91B4(arg0, arg1, arg2)
s32 arg0;
u8 arg1;
s16 arg2;
{
    u8 *pa;
    u8 *sp48;
    s16 *pb;
    s32 temp_v0;
    s32 sp3C;
    s32 temp_a3;
    s32 temp_v0_2;
    u16 *temp_v1;
    NM2StatSlot *temp_a0;
    s32 sp28;

    pa = &arg1;
    pb = &arg2;
    sp28 = arg1;
    temp_v0_2 = func_806C8DE0(arg1);
    sp48 = (u8 *)D_807FC950 + (arg1 * 0x306 + temp_v0_2 * 0x5E);
    temp_v0 = slotQueueGetAddress(arg1);
    temp_a0 = (NM2StatSlot *)(temp_v0 + (arg0 * 0x30));
    if (((temp_a0->unk2D == 0) || (arg2 >= 0)) && (temp_a0->unk2C == 0)) {
        if ((arg0 != 0xA) && (arg0 != 0xC)) {
            temp_v1 = temp_a0->unk0;
            if ((*temp_v1 + arg2) < 0) {
                *temp_v1 = 0;
            } else {
                temp_v1 = *((u16 **)(temp_v0 + (arg0 * 0x30)));
                *temp_v1 += arg2;
                temp_v0_2 = func_806F8EDC(arg0, sp28);
                temp_v1 = *((u16 **)(temp_v0 + (arg0 * 0x30)));
                if (temp_v0_2 < *temp_v1) {
                    *temp_v1 = temp_v0_2;
                }
                if (((arg0 * 0x30) == 0x180) && (func_805FEF10(&sp3C) != 0)) {
                    flagSet(sp3C, 1, 0);
                }
                if ((arg2 > 0) && ((arg0 * 0x30) == 0)) {
                    temp_v0_2 = func_805FF030(D_8076A0AB, 1);
                    temp_a3 = *(u16 *)(sp48 + (temp_v0_2 * 2) + 0x26) + *(u16 *)(sp48 + (temp_v0_2 * 2) + 0xA);
                    if ((temp_a3 >= 0x4B) && ((temp_a3 - arg2) < 0x4B)) {
                        flagSet(flagGridIndex(0x225, temp_v0_2, (&D_8074E77C)[arg1], temp_a3), 1, 0);
                        func_80687C48();
                    }
                    if ((temp_a3 == 0x64) && ((temp_a3 - arg2) < 0x64)) {
                        sfxAllocateChannel(0xAC, 1.0f);
                    }
                }
            }
        }
        if ((arg0 * 0x30) == 0x180) {
            func_806F8278(arg1);
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806F91B4.s")
#endif



void bitfieldSetMappedFlag(u16 *arg0, s32 arg1) {
    *arg0 |= 1 << func_805FF030(arg1 & 0xFF, 1);
}

void bitfieldClearMappedFlag(u16 *arg0, s32 arg1) {
    *arg0 &= ~(1 << func_805FF030(arg1 & 0xFF, 1));
}


s32 bitfieldHasMappedFlag(u16 arg0, s32 arg1) {
    return (1 << func_805FF030(arg1 & 0xFF, 1)) & arg0 & 0xFF;
}

typedef struct FcAScaleInfo {
    u8 pad0[9];
    u8 unk9;
    u8 padA[4];
    s16 unkE;
} FcAScaleInfo;

typedef struct FcAScaleActor {
    u8 pad0[0x330];
    FcAScaleInfo *unk330;
    u8 pad334[0x2C];
    f32 unk360;
    f32 unk364;
} FcAScaleActor;

void func_806F94AC(void *arg0_, s32 arg1) {
    FcAScaleActor *arg0 = arg0_;
    f32 temp_fv0;
    f32 temp_fa0;
    f32 var_fv1;

    temp_fv0 = arg0->unk330->unk9 * arg0->unk330->unkE;
    var_fv1 = 32.0f / temp_fv0;
    temp_fa0 = var_fv1;
    if (arg1 == 9) {
        var_fv1 = (f64)temp_fa0 * 1.2;
    }
    arg0->unk360 = arg0->unk360 * var_fv1;
    arg0->unk364 = arg0->unk364 * var_fv1;
}

typedef struct FcAAllocNode {
    s32 type;
    u8 pad4[0x10];
    void *unk14;
    struct FcAAllocNode *next;
} FcAAllocNode;

void effectFreeAndUnlink(s32);
void heapFree(void *);

void func_806F9518(s32 arg0) {
    FcAAllocNode **var_s1;
    FcAAllocNode *temp_s0;
    FcAAllocNode **temp_s2;
    s32 idx;
    s32 *rec;
    void *base;
    idx = arg0 * 0x30;
    base = D_80754280;
    var_s1 = (FcAAllocNode **)&((R2FCCD0cSlot *)(arg0 * 0x30 + (s32)D_80754280))->unk28;
    ((R2FCCD0cSlot *)base)[arg0].unk20 = 0;
    if (*var_s1 != NULL) {
        do {
            temp_s0 = *var_s1;
            temp_s2 = &temp_s0->next;
            if (temp_s0->type == 1) {
                rec = temp_s0->unk14;
                effectFreeAndUnlink(rec[2]);
                temp_s0 = *var_s1;
            }
            heapFree(temp_s0->unk14);
            heapFree(*var_s1);
            *var_s1 = NULL;
            var_s1 = temp_s2;
        } while (*temp_s2 != NULL);
    }
}

void func_806F9518(s32);

void slotQueueReleaseAll(void) {
    s32 i;

    i = 0;
    do {
        func_806F9518(i);
        i++;
    } while (i != 0xF);
}

typedef struct R1FCCD0bAllocRecord {
    s32 unk0;
    u8 pad4[0x10];
    void *unk14;
} R1FCCD0bAllocRecord;


void func_806F9608(R1FCCD0bAllocRecord **arg0) {
    R1FCCD0bAllocRecord *temp;

    temp = func_80610FE8(0x1C);
    *arg0 = temp;
    heapClearBlock(temp);
    (*arg0)->unk0 = 1;
    (*arg0)->unk14 = func_80610FE8(0xC);
    heapClearBlock((*arg0)->unk14);
}

void func_806F966C(R1FCCD0bAllocRecord **arg0) {
    R1FCCD0bAllocRecord *temp;

    temp = func_80610FE8(0x1C);
    *arg0 = temp;
    heapClearBlock(temp);
    (*arg0)->unk0 = 0;
    (*arg0)->unk14 = func_80610FE8(0x88);
    heapClearBlock((*arg0)->unk14);
}

typedef struct R1FCCD0bEffect {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    s32 unkC;
} R1FCCD0bEffect;

void effectSetDirection(R1FCCD0bEffect *arg0, u32 arg1) {
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    var_v1 = 0;
    arg0->unkC = 0;
    switch (arg1) {
    case 0:
    case 13:
    case 14:
        var_v0 = -1;
        break;
    case 9:
    case 10:
    case 12:
        var_v1 = 1;
        break;
    default:
        var_v0 = 1;
        break;
    }
    arg0->unk4 = (f32)(var_v0 * 0x30);
    arg0->unk8 = (f32)(var_v1 * 0x30);
}

typedef struct R1FCCD0bEffectNode {
    u8 pad0[2];
    s16 unk2;
    u8 unk4;
    u8 pad5[3];
    void *unk8;
} R1FCCD0bEffectNode;

void func_806F94AC(void *, s32);
s32 func_806FACE8(s32);
void func_80714944(s32);
void func_80714950(void *);
void func_8071495C(void);
void func_8071498C(void (*)(void));
void func_80714998(u8);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714A28(s32);
void *func_80714CC0(s32, f32, f32, f32, f32);
void func_8071BE04(void);

void effectSpawnSprite(void *arg0, s32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    u8 unused_byte;
    s32 unused_word;
    s32 sp2C;
    R1FCCD0bEffectNode *temp_s0;

    temp_s0 = *(R1FCCD0bEffectNode **)((u8 *)arg0 + 0x14);
    sp2C = 2;
    func_8071495C();
    func_807149FC(-1);
    if (arg1 == 0xE) {
        sp2C = 1;
    }
    func_80714998(((u8 *)&sp2C)[3]);
    func_80714944(arg4);
    func_80714950(arg0);
    func_8071498C(func_8071BE04);
    func_80714A28(0x21);
    if (arg1 == 3) {
        func_807149C8(0xFF, 0, 0, 0xFF);
    }
    temp_s0->unk8 = func_80714CC0(func_806FACE8(arg1), 1.0f, arg2, arg3, -10.0f);
    temp_s0->unk2 = 0;
    if (arg1 == 7) {
        temp_s0->unk4 = 1;
    } else {
        temp_s0->unk4 = 0;
    }
    func_806F94AC(temp_s0->unk8, arg1);
}

extern u8 D_8074E77C;

typedef struct FcBSlot9848 {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
} FcBSlot9848;

void func_806F9848(s32 arg0) {
    s32 sp3C;
    s32 sp30;
    u8 *sp44;
    s32 var_s1;
    s32 var_a1;
    u8 *var_s0;

    var_a1 = 1;
    var_s1 = -1;
    sp30 = arg0 * 0x30;
    var_s0 = (u8 *)((s32)D_80754280 + (0, sp30)) + 0x28;
    if (((f64)D_80744490 * 0.5) < (f64)((FcBSlot9848 *)((u8 *)D_80754280 + sp30))->unk8) {
        var_a1 = -1;
    }
    sp3C = var_a1;
    func_806F9608((R1FCCD0bAllocRecord **)var_s0);
    sp44 = *(u8 **)(*(u8 **)var_s0 + 0x14);
    effectSetDirection(*(R1FCCD0bEffect **)var_s0, arg0);
    effectSpawnSprite(*(void **)var_s0, arg0, (f32)((FcBSlot9848 *)((u8 *)D_80754280 + sp30))->unk8, (f32)((FcBSlot9848 *)((u8 *)D_80754280 + sp30))->unkC, 0);
    *sp44 = 0xFF;
    *(s16 *)(*(u8 **)var_s0 + 0x10) = 0;
    switch (D_8076A0A8) {
    case 0x2A:
        if (arg0 == 0xD) {
            var_s1 = 0x10;
        }
        break;
    case 1:
        if (arg0 == 0xE) {
            var_s1 = 0x11;
        }
    case 5:
        if ((var_s1 == -1) && (arg0 == 0xE)) {
            var_s1 = 0x13;
        }
    case 0x19:
        if ((var_s1 == -1) && (arg0 == 0xE)) {
            var_s1 = 0x12;
        } else if (arg0 == 1) {
            var_s1 = D_8074E77C + 0x14;
        }
        break;
    }
    if (var_s1 >= 0) {
        var_s0 = *(u8 **)var_s0 + 0x18;
        func_806F9608((R1FCCD0bAllocRecord **)var_s0);
        sp44 = *(u8 **)(*(u8 **)var_s0 + 0x14);
        effectSetDirection(*(R1FCCD0bEffect **)var_s0, arg0);
        effectSpawnSprite(*(void **)var_s0, var_s1, (f32)((FcBSlot9848 *)((u8 *)D_80754280 + sp30))->unk8, (f32)(((FcBSlot9848 *)((u8 *)D_80754280 + sp30))->unkC + 0x20), 0);
        *sp44 = 0xFF;
        *(s16 *)(*(u8 **)var_s0 + 0x10) = 0;
    }
    var_s0 = *(u8 **)var_s0 + 0x18;
    func_806F966C((R1FCCD0bAllocRecord **)var_s0);
    effectSetDirection(*(R1FCCD0bEffect **)var_s0, arg0);
    *(s16 *)(*(u8 **)var_s0 + 0x10) = 0;
    sp44 = *(u8 **)(*(u8 **)var_s0 + 0x14);
    *(s32 *)(*(u8 **)(*(u8 **)var_s0 + 0x14)) = ((FcBSlot9848 *)((u8 *)D_80754280 + sp30))->unk8 + sp3C * 0x14;
    *(s32 *)(sp44 + 4) = ((FcBSlot9848 *)((u8 *)D_80754280 + sp30))->unkC - 0xA;
}

typedef struct NmFCCD0ActorView {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    u8 pad348[0x16];
    s16 unk35E;
    f32 unk360;
    f32 unk364;
} NmFCCD0ActorView;

extern u8 D_807FD7A0;
extern u8 D_807FD7B8;
extern u8 D_807FD7D0;

void effectSpriteUpdatePosition(NmFCCD0ActorView *arg0, s8 *arg1) {
    f32 *temp_a2;
    f32 *temp_v0;
    int new_var;
    f32 temp_fv0;
    s32 temp_v1;

    new_var = arg0->unk35E;
    temp_v1 = 4 * new_var;
    temp_a2 = (f32 *)(temp_v1 + &D_807FD7A0);
    temp_fv0 = *temp_a2;
    if (*temp_a2 == -200.0f) {
        *arg1 = 1;
        return;
    }
    arg0->unk340 = *temp_a2;
    temp_v0 = (f32 *)(temp_v1 + &D_807FD7D0);
    arg0->unk344 = *(f32 *)(temp_v1 + &D_807FD7B8);
    arg0->unk360 = *temp_v0;
    arg0->unk364 = *temp_v0;
    *temp_a2 = -200.0f;
}

typedef struct FcBPayload9B64 {
    s32 unk0;
    s32 unk4;
} FcBPayload9B64;

extern void *D_80750518[];

void func_806F9B64(s32 arg0) {
    s32 unused;
    R1FCCD0bAllocRecord **temp_s4;
    FcBPayload9B64 *temp_v0;
    s32 i;

    temp_s4 = (R1FCCD0bAllocRecord **)((u8 *)D_80754280 + (0, arg0 * 0x30) + 0x28);
    func_806F966C(temp_s4);
    effectSetDirection((R1FCCD0bEffect *)*temp_s4, 0);
    *(s16 *)((u8 *)*temp_s4 + 0x10) = 0;
    temp_v0 = (FcBPayload9B64 *)(*temp_s4)->unk14;
    temp_v0->unk0 = *(s32 *)((u8 *)D_80754280 + arg0 * 0x30 + 8) + 0x14;
    temp_v0->unk4 = *(s32 *)((u8 *)D_80754280 + arg0 * 0x30 + 0xC) - 0x14;
    for (i = 0; i < 5; i++) {
        func_8071495C();
        func_807149FC(-1);
        func_8071498C((void (*)(void))effectSpriteUpdatePosition);
        func_80714950((void *)i);
        ((f32 *)&D_807FD7A0)[i] = -100.0f;
        func_80714CC0((s32)D_80750518[i], 1.0f, -200.0f, 0.0f, -10.0f);
    }
}

void func_806F9CD0(s32 arg0) {
    R1FCCD0bAllocRecord **temp_s0;
    void *sp30;

    temp_s0 = (R1FCCD0bAllocRecord **)((u8 *)D_80754280 + (0, arg0 * 0x30) + 0x28);
    func_806F9608(temp_s0);
    sp30 = *(void **)((u8 *)*temp_s0 + 0x14);
    effectSetDirection((R1FCCD0bEffect *)*temp_s0, arg0);
    effectSpawnSprite(*temp_s0, arg0, (f32)*(s32 *)((u8 *)D_80754280 + arg0 * 0x30 + 8), (f32)*(s32 *)((u8 *)D_80754280 + arg0 * 0x30 + 0xC), 0);
    func_806F8DC4(sp30, 0, arg0);
    *(s16 *)((u8 *)*temp_s0 + 0x10) = 0;
}

typedef struct FcBDraw9D8C {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    u8 padC[4];
    s16 unk10;
    u8 pad12[2];
    s32 *unk14;
} FcBDraw9D8C;

typedef struct FcBSlot9D8C {
    u8 pad0[4];
    u16 unk4;
    u8 pad6[2];
    s32 unk8;
    u8 padC[0x20];
    u8 unk2C;
} FcBSlot9D8C;

typedef struct FcBView9D8C {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} FcBView9D8C;

extern Gfx D_1000118;
extern Mtx D_2000080;
extern u8 D_807FD7E4;
extern f32 func_80612794(s16);
extern f32 floatCeil(f32);
extern s32 _sprintf(char *, const char *, ...);
extern s32 func_806FBD5C(s16, char *);
extern Gfx *func_806FC530(Gfx *, s16, s16, s16, char *, u8);
extern FcBView9D8C *cameraFindViewportEntry(s32);

#define FCB_SLOT9D8C ((FcBSlot9D8C *)((u8 *)D_80754280 + arg0 * 0x30))
Gfx *func_806F9D8C(s32 arg0, FcBDraw9D8C *arg1, Gfx *arg2) {
    s32 *matrix;
    char text[8];
    u8 alpha;
    FcBView9D8C *viewport;
    f32 scale;
    s32 width;

    matrix = arg1->unk14;
    scale = func_80612794(arg1->unk10);
    alpha = (u8)(u32)((f64)scale * 255.0);
    width = 0;
    gSPMatrix(arg2++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    guTranslate((Mtx *)((u8 *)matrix + (D_807444FC << 6) + 8), arg1->unk4 * (1.0f - scale), arg1->unk8 * (1.0f - scale), 0.0f);
    switch (FCB_SLOT9D8C->unk2C) {
    case 1:
        _sprintf(text, "o");
        break;
    case 2:
        if (FCB_SLOT9D8C->unk2C == 0) {
        }
        _sprintf(text, "NA");
        break;
    default:
        _sprintf(text, "%d", (arg0 * 0x30 == 0xF0) ? (s32)floatCeil((f32)(u32)FCB_SLOT9D8C->unk4 * 0.006666667f) : FCB_SLOT9D8C->unk4);
        break;
    }
    gSPMatrix(arg2++, (u8 *)matrix + (D_807444FC << 6) + 8, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gDPPipeSync(arg2++);
    gDPSetPrimColor(arg2++, 0, 0, 0, 0, 0, alpha);
    D_807FD7E4 = alpha;
    gSPDisplayList(arg2++, &D_1000118);
    gDPSetCombineLERP(arg2++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    viewport = cameraFindViewportEntry(0);
    gDPSetScissor(arg2++, G_SC_NON_INTERLACE, viewport->unk4, viewport->unk6, viewport->unk8, viewport->unkA);
    if ((f64)D_80744490 * 0.5 < (f64)FCB_SLOT9D8C->unk8) {
        width = func_806FBD5C(0x81, text);
    }
    arg2 = func_806FC530(arg2, 0x81, (s16)((matrix[0] - width) * 4), (s16)(matrix[1] * 4), text, 0);
    gSPPopMatrix(arg2++, G_MTX_MODELVIEW);
    gDPPipeSync(arg2++);
    return arg2;
}

extern s16 D_807505AE[];
extern u8 D_807FC992[];
extern Gfx D_2000180;
extern s32 flagGet(s32, s32);

Gfx *func_806FA1A4(s32 arg0, FcBDraw9D8C *arg1, Gfx *arg2) {
    s32 active;
    s32 savedU16;
    s32 savedY;
    f32 x;
    f32 y;
    f32 scale;
    s8 valid;
    s32 player;
    s32 i;
    s32 *cursor;
    s32 off;
    f64 u;

    cursor = arg1->unk14;
    player = func_805FF030(D_8076A0AB, 1);
    active = func_806C8DE0(0);
    off = arg0 * 0x30;
    savedU16 = *(u16 *)((u8 *)D_80754280 + off + 4);
    savedY = cursor[1];
    x = (f32)((f64)cursor[0] * 4.0);
    y = (f32)((f64)cursor[1] * 4.0);
    u = 1.0 - (f64)func_80612794(arg1->unk10);
    x = (f32)((f64)x - (4.0 * (6.0 - (u * (f64)arg1->unk4))));
    y = (f32)((f64)y + 92.0);
    for (i = 0; i != 5; i++) {
        valid = 1;
        if (i > 0) {
            valid = flagGet(D_807505AE[i], 0);
        }
        if (valid != 0) {
            if (i == active) {
                *(u16 *)((u8 *)D_80754280 + off + 4) = savedU16;
                scale = 2.0f;
            } else {
                *(u16 *)((u8 *)D_80754280 + off + 4) = ((u16 *)&D_807FC992[i * 0x5E])[player];
                scale = 1.5f;
            }
            arg2 = func_806F9D8C(arg0, arg1, arg2);
            if (i != active) {
                gDPSetPrimColor(arg2++, 0, 0, 0, 0, 0, D_807FD7E4 >> 1);
            }
            ((f32 *)&D_807FD7A0)[i] = (f32)((f64)x - (10.0 * (f64)scale));
            ((f32 *)&D_807FD7B8)[i] = (f32)((f64)y - (30.0 * (f64)scale));
            ((f32 *)&D_807FD7D0)[i] = (f32)((f64)scale * 1.15);
            y = (f32)((f64)y + 136.0);
            cursor[1] += 0x22;
        }
    }
    *(u16 *)((u8 *)D_80754280 + off + 4) = savedU16;
    cursor[1] = savedY;
    gSPMatrix(arg2++, &D_2000180, G_MTX_MODELVIEW | G_MTX_NOPUSH | G_MTX_LOAD);
    return arg2;
}


s32 func_806FA504(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    if (*(s32 *)arg1 == 0) {
        if (arg0 != 8) {
            arg3 = (s32)func_806F9D8C(arg0, arg1, (Gfx *)arg3);
        } else {
            arg3 = (s32)func_806FA1A4(arg0, arg1, (Gfx *)arg3);
        }
    } else if ((arg0 == 8) || (arg0 == 0xA) || (arg0 == 0xC)) {
        func_806F8DC4(*(s8 **)((u8 *)arg1 + 0x14), arg2, arg0);
    }
    return arg3;
}

typedef struct FcCNode {
    s32 unk0;
    u8 pad4[8];
    s32 unkC;
    s16 unk10;
    u8 pad12[6];
    struct FcCNode *unk18;
} FcCNode;

typedef struct FcCSlot {
    u16 *unk0;
    u16 unk4;
    u8 unk6;
    u8 unk7;
    u8 pad8[0x18];
    s32 unk20;
    u8 pad24[4];
    FcCNode *unk28;
} FcCSlot;


s32 func_806FA5A4(s32 arg0, s32 arg1) {
    s32 s1;
    s32 s2;
    s32 s3;
    FcCNode *node;

    node = ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk28;
    s2 = 0;
    s3 = 0;
    s1 = 0;
    if (((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 != 0) {
        ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 = ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 - 1;
        return arg1;
    }
    if (node == NULL) {
        switch (arg0) {
        case 8:
            func_806F9B64(arg0);
            return arg1;
        case 10:
        case 12:
            func_806F9CD0(arg0);
            return arg1;
        default:
            func_806F9848(arg0);
            return arg1;
        }
    } else {
        if (node != NULL) {
            do {
                s3 += 1;
                if (node->unkC != 0) {
                    node->unkC = node->unkC - 1;
                } else {
                    if (node->unk10 < 0x400) {
                        node->unk10 = (s32)((f32)node->unk10 + 102.4f);
                    } else {
                        s2 += 1;
                    }
                    if (node->unk10 >= 0x401) {
                        node->unk10 = 0x400;
                    }
                    arg1 = func_806FA504(arg0, node, s1, arg1);
                }
                if (node->unk0 == 1) {
                    s1 += 1;
                }
                node = node->unk18;
            } while (node != NULL);
        }
        if (s2 == s3) {
            if (((arg0 * 0x30) == 0x180) || ((arg0 * 0x30) == 0x1B0)) {
                ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 = 0x5A;
            } else {
                ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 = 0x1E;
            }
            ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk20 = 2;
            if (D_80754280 == 0) {}
        }
        return arg1;
    }
}

s32 func_806FA7A4(s32 arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (arg0 == 5) {
        var_v1 = 0x96;
    }
    return var_v1;
}

#ifdef NON_MATCHING
#define FCC_SLOT ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))

s32 func_806FA7BC(s32 arg0, s32 arg1) {
    extern s32 func_806FA7A4();
    s32 s1;
    FcCNode *node;
    u8 flag;
    u16 *p;
    s32 x;
    s32 step;
    s32 absd;
    s32 sign;
    s32 tmp;
    if (step == 0) {}

    node = FCC_SLOT->unk28;
    s1 = 0;
    p = FCC_SLOT->unk0;
    if (p != NULL) {
        flag = *p == ((u16 *)FCC_SLOT)[2];
    } else {
        flag = 1;
    }
    if (node != NULL) {
        do {
            arg1 = func_806FA504(arg0, node, s1, arg1);
            if (node->unk0 == 1) {
                s1 += 1;
            }
            node = node->unk18;
        } while (node != NULL);
    }
    if (flag == 0) {
        sign = *FCC_SLOT->unk0;
        if (FCC_SLOT->unk0 != NULL) {
            x = sign;
            s1 = FCC_SLOT->unk4;
            step = func_806FA7A4(arg0, *FCC_SLOT->unk0, FCC_SLOT->unk4);
            if ((x - s1) > 0) {
                absd = (x - s1);
            } else {
                absd = -(x - s1);
            }
            if (absd < step) {
                if ((x - s1) > 0) {
                    tmp = (x - s1);
                } else {
                    tmp = -(x - s1);
                }
                step = tmp;
            }
            if ((x - s1) >= 0) {
                sign = 1;
            } else {
                sign = -1;
            }
            FCC_SLOT->unk4 += sign * step;
        }
        flag = *FCC_SLOT->unk0 == ((u16 *)FCC_SLOT)[2];
    }
    if ((FCC_SLOT->unk7 == 0) && (flag != 0)) {
        FCC_SLOT->unk20 = 3;
        func_806F8CB0(arg0);
        if ((arg0 * 0x30) == 0x180) {
            slotQueueCancel(9, 5);
        }
        return arg1;
    } else if ((FCC_SLOT->unk7 != 0) && (FCC_SLOT->unk6 == 0)) {
        FCC_SLOT->unk7 = FCC_SLOT->unk7 - 1;
    }
    return arg1;
}

#undef FCC_SLOT
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/FCCD0/func_806FA7BC.s")
#endif

s32 func_806FA9C0(s32 arg0, s32 arg1) {
    s32 s1;
    FcCNode *node;
    s32 cnt;
    s32 done;

    node = ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk28;
    s1 = 0;
    if (node != NULL) {
        do {
            arg1 = func_806FA504(arg0, node, s1, arg1);
            if (node->unk0 == 1) {
                s1 += 1;
            }
            node = node->unk18;
        } while (node != NULL);
    }
    if (((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 != 0) {
        ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 = ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk7 - 1;
    } else {
        node = ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk28;
        done = 0;
        cnt = 0;
        if (node != NULL) {
            do {
                cnt += 1;
                if (node->unkC != 0) {
                    node->unkC = node->unkC - 1;
                } else {
                    if (node->unk10 > 0) {
                        node->unk10 = (s32)((f32)node->unk10 - 102.4f);
                    }
                    if (node->unk10 < 0) {
                        node->unk10 = 0;
                        done += 1;
                    }
                }
                node = node->unk18;
            } while (node != NULL);
        }
        if (cnt == done) {
            ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))->unk20 = 0;
        }
    }
    return arg1;
}

s32 func_806FA7BC(s32, s32);

Gfx *func_806FAB20(Gfx *arg0) {
    s32 i;

    if (D_807FC928 >= 2) {
        return arg0;
    }
    gDPPipeSync(arg0++);
    gSPMatrix(arg0++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    for (i = 0; i != 0xF; i++) {
        switch (*(s32 *)((u8 *)D_80754280 + i * 0x30 + 0x20)) {
        case 0:
            func_806F9518(i);
            break;
        case 1:
            arg0 = (Gfx *)func_806FA5A4(i, (s32)arg0);
            break;
        case 2:
            arg0 = (Gfx *)func_806FA7BC(i, (s32)arg0);
            break;
        case 3:
            arg0 = (Gfx *)func_806FA9C0(i, (s32)arg0);
            break;
        }
    }
    return arg0;
}

extern s32 D_80754288;

void func_806FAC64(u8 arg0) {
    s32 resource;

    resource = func_805FF030(D_8076A0AB, 0);
    *(u8 **)((u8 *)D_80754280 + 0x270) = &D_807FC950[arg0][resource * 2 + 0x26];
    *(u16 *)((u8 *)D_80754280 + 0x274) = **(u16 **)((u8 *)D_80754280 + 0x270);
    D_80754288 = arg0;
}

extern s32 D_807200A0, D_807201A0, D_80720268, D_8072029C, D_807203B0, D_807203D4, D_807203F8, D_8072041C, D_80720440, D_80720488, D_807204BC, D_80720508, D_8072052C, D_80720558, D_8072057C, D_807205A0, D_807205C4, D_807205E8, D_8072060C, D_807206A8, D_807207BC, D_807207E0, D_80720854, D_80720878, D_80720890, D_807208A8, D_807208C0, D_807208D8, D_807209EC, D_80720A10, D_80720A34, D_80720A58, D_80721200, D_8072121C, D_80721250, D_8072145C, D_807214A0, D_807214B8, D_807214D0, D_807214E8, D_80721500;

s32 func_806FACE8(s32 arg0) {
    s32 result;
    u32 player;

    result = 0;
    player = func_806C8DE0(0);
    if (arg0 == 13) {
        player = D_80754288;
    }
    switch (arg0) {
    case 0:
    case 13:
        switch (player) {
        case 1:
            result = (s32)&D_8072057C;
            break;
        case 0:
            result = (s32)&D_807205E8;
            break;
        case 3:
            result = (s32)&D_8072060C;
            break;
        case 2:
            result = (s32)&D_807205C4;
            break;
        case 4:
        case 5:
            result = (s32)&D_807205A0;
            break;
        }
        break;
    case 6:
        result = (s32)&D_80720488;
        break;
    case 4:
        result = (s32)&D_807204BC;
        break;
    case 2:
    case 3:
        switch (player) {
        case 1:
            result = (s32)&D_807200A0;
            break;
        case 0:
            result = (s32)&D_807206A8;
            break;
        case 3:
            result = (s32)&D_80720854;
            break;
        case 2:
            result = (s32)&D_8072029C;
            break;
        case 4:
            result = (s32)&D_807201A0;
            break;
        case 5:
            result = (s32)&D_80720268;
            break;
        }
        break;
    case 1:
    case 14:
        switch (player) {
        case 1:
            result = (s32)&D_807203B0;
            break;
        case 0:
            result = (s32)&D_8072041C;
            break;
        case 3:
            result = (s32)&D_80720440;
            break;
        case 2:
            result = (s32)&D_807203F8;
            break;
        case 4:
        case 5:
            result = (s32)&D_807203D4;
            break;
        }
        break;
    case 11:
        result = (s32)&D_807207BC;
        break;
    case 7:
        switch (player) {
        case 1:
            result = (s32)&D_80720878;
            break;
        case 0:
            result = (s32)&D_80720890;
            break;
        case 3:
            result = (s32)&D_807208A8;
            break;
        case 2:
            result = (s32)&D_807208D8;
            break;
        case 4:
        case 5:
            result = (s32)&D_807208C0;
            break;
        }
        break;
    case 5:
        result = (s32)&D_80720508;
        break;
    case 8:
        result = (s32)&D_8072052C;
        break;
    case 9:
        result = (s32)&D_8072052C;
        break;
    case 10:
        result = (s32)&D_80720558;
        break;
    case 12:
        switch (player) {
        case 1:
            result = (s32)&D_807209EC;
            break;
        case 0:
            result = (s32)&D_80720A34;
            break;
        case 3:
            result = (s32)&D_80720A58;
            break;
        case 2:
            result = (s32)&D_807207E0;
            break;
        case 4:
        case 5:
            result = (s32)&D_80720A10;
            break;
        }
        break;
    case 16:
        result = (s32)&D_8072145C;
        break;
    case 17:
        result = (s32)&D_80721250;
        break;
    case 18:
        result = (s32)&D_80721200;
        break;
    case 19:
        result = (s32)&D_8072121C;
        break;
    case 20:
        result = (s32)&D_807214A0;
        break;
    case 21:
        result = (s32)&D_807214B8;
        break;
    case 22:
        result = (s32)&D_807214D0;
        break;
    case 23:
        result = (s32)&D_807214E8;
        break;
    case 24:
        result = (s32)&D_80721500;
        break;
    }
    return result;
}

typedef struct FcDNode {
    s32 flags;
    struct FcDNode *next;
} FcDNode;

typedef struct FcDSlot {
    u8 pad0[6];
    u8 unk6;
    u8 pad7[0x19];
    s32 unk20;
    u8 pad24[8];
    u8 unk2C;
    u8 unk2D;
    u8 pad2E[2];
} FcDSlot;

void func_806FAFE4(void) {
    s32 i;
    FcDNode **link;
    FcDNode *alloc;

    link = (FcDNode **)&D_80754284;
    while (*link != NULL) {
        link = &(*link)->next;
    }
    alloc = func_80610FE8(8);
    *link = alloc;
    heapClearBlock(alloc);
    for (i = 0; i < 15; i++) {
        if ((((FcDSlot *)D_80754280)[i].unk20 == 1 || ((FcDSlot *)D_80754280)[i].unk20 == 2) && ((FcDSlot *)D_80754280)[i].unk6 != 0) {
            (*link)->flags |= 1 << i;
        }
    }
}


void slotQueueClearAllFlags(void)
{
  s32 i;
  s32 offset;
  func_806FAFE4();
 i = 0; offset = 0; do {
    if ((*((((u8 *) D_80754280) + offset) + 6)) != 0)
    {
      slotQueueClearFlags(i, 0);
    }
    i++;
    offset += 0x30;
  }
  while (i != 0xF);
}

void slotQueueReset(void) {
    func_806FAFE4();
    slotQueueReleaseAll();
}

void func_806FB2B8(void) {
    FcDNode **link;
    s32 i;

    link = (FcDNode **)&D_80754284;
    if (*link != NULL) {
        while ((*link)->next != NULL) {
            link = &(*link)->next;
        }
        for (i = 0; i != 15; i++) {
            if ((*link)->flags & (1 << i)) {
                slotQueueUpdate(i, 1, 0);
            }
        }
        heapFree(*link);
        *link = NULL;
    }
}

void func_806FB370(u8 arg0, u8 arg1, u8 arg2) {
    if (((FcDSlot *)D_80754280)[arg1 * 15 + arg0].unk2D == 0) {
        ((FcDSlot *)D_80754280)[arg1 * 15 + arg0].unk2C = arg2;
    }
}

u8 func_806FB3D0(u8 arg0, u8 arg1) {
    return ((FcDSlot *)D_80754280)[arg1 * 15 + arg0].unk2C;
}

s32 func_806FB418(void) {
    s32 sum;
    s32 i;
    s32 j;

    sum = 0;
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 8; i++) {
            sum += ((u16 *)D_807FC950[j])[0x21 + i];
        }
    }
    return sum;
}

