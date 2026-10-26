#include "common.h"

typedef struct R35000aNode R35000aNode;
struct R35000aNode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ R35000aNode *unk14;
    /* 0x18 */ R35000aNode *unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[3];
};

extern R35000aNode *D_807F5FF0;
extern R35000aNode *D_807F5FF4;
extern R35000aNode *D_807F5FF8;
extern R35000aNode *D_807F5FFC;

void func_80630300(void) {
    D_807F5FF0 = 0;
    D_807F5FF4 = 0;
    D_807F5FF8 = 0;
    D_807F5FFC = 0;
}

s32 func_80630324(u8 arg0, u8 *arg1) {
    if (arg0 == 2) {
        if (arg1[0x4E] & 2) {
            return 0;
        }
        if (arg1[0x4E] & 1) {
            return 1;
        }
        return 0;
    }
    switch (arg0) {
    case 0:
    case 1:
        return 0;
    case 5:
        return 1;
    default:
        return 0;
    }
}

void func_806306D0(R35000aNode *);

void func_8063039C(void) {
    func_806306D0(D_807F5FF4);
    D_807F5FF4 = 0;
}

void *func_80610FE8(s32);

R35000aNode *func_806303C4(R35000aNode *arg0, u8 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, s16 arg7, u8 arg8, s16 arg9, u8 arg10) {
    s32 found;
    R35000aNode *prev;
    R35000aNode *node;
    R35000aNode *head;

    found = 0;
    prev = NULL;
    if (arg10 == 1) {
        arg0 = D_807F5FF0;
    }
    if (arg10 == 2) {
        arg0 = D_807F5FF4;
    }
    if (arg10 == 3) {
        arg0 = D_807F5FF8;
    }
    if (arg10 == 4) {
        arg0 = D_807F5FFC;
    }
    head = arg0;
    if (arg0 != NULL) {
        do {
            if (arg2 == arg0->unk0) {
                found = 1;
            } else {
                prev = arg0;
                arg0 = arg0->unk14;
            }
        } while (arg0 != NULL && found == 0);
    }
    if (found != 0) {
        arg0->unk4 = arg3;
        arg0->unk8 = arg4;
        arg0->unkC = arg5;
        arg0->unk1C = arg6;
        if (arg9 != -1) {
            arg0->unk20 = arg9;
        }
        arg0->unk23 = 1;
    } else {
        node = func_80610FE8(0x28);
        node->unk24 = arg1;
        node->unk0 = arg2;
        node->unk4 = arg3;
        node->unk8 = arg4;
        node->unkC = arg5;
        node->unk1C = arg6;
        node->unk1E = arg7;
        node->unk22 = arg8;
        node->unk23 = 1;
        node->unk20 = 0;
        node->unk14 = NULL;
        node->unk10 = 0.0f;
        if (prev != NULL) {
            prev->unk14 = node;
            node->unk18 = prev;
        } else {
            head = node;
            node->unk18 = NULL;
        }
    }
    if (arg10 == 1) {
        D_807F5FF0 = head;
    }
    if (arg10 == 2) {
        D_807F5FF4 = head;
    }
    if (arg10 == 3) {
        D_807F5FF8 = head;
    }
    if (arg10 == 4) {
        D_807F5FFC = head;
    }
    return head;
}

void heapFree(void *);

R35000aNode *func_80630588(R35000aNode *arg0, s32 arg1, u8 arg2, u8 *arg3) {
    u8 found;
    R35000aNode *prev;
    R35000aNode *head;

    found = 0;
    prev = NULL;
    if (arg2 == 1) {
        arg0 = D_807F5FF0;
    }
    if (arg2 == 2) {
        arg0 = D_807F5FF4;
    }
    if (arg2 == 3) {
        arg0 = D_807F5FF8;
    }
    if (arg2 == 4) {
        arg0 = D_807F5FFC;
    }
    head = arg0;
    if (arg0 != NULL) {
        do {
            if (arg1 == arg0->unk0) {
                found = 1;
            } else {
                prev = arg0;
                arg0 = arg0->unk14;
            }
        } while (arg0 != NULL && found == 0);
    }
    if (found != 0) {
        if (prev != NULL) {
            prev->unk14 = arg0->unk14;
        } else {
            head = arg0->unk14;
        }
        if (arg0->unk14 != NULL) {
            arg0->unk14->unk18 = prev;
        }
        heapFree(arg0);
    }
    *arg3 = found;
    if (arg2 == 1) {
        D_807F5FF0 = head;
    }
    if (arg2 == 2) {
        D_807F5FF4 = head;
    }
    if (arg2 == 3) {
        D_807F5FF8 = head;
    }
    if (arg2 == 4) {
        D_807F5FFC = head;
    }
    return head;
}

void func_806306D0(R35000aNode *arg0) {
    R35000aNode *cur;

    if (arg0 != NULL) {
        do {
            cur = arg0;
            arg0 = arg0->unk14;
            heapFree(cur);
        } while (arg0 != NULL);
    }
}

R35000aNode *func_8063070C(R35000aNode *arg0) {
    R35000aNode *head;

    head = arg0;
    if (arg0 != NULL) {
        do {
            if (arg0->unk22 == 1 && arg0->unk23 == 0) {
                if (arg0->unk18 != NULL) {
                    arg0->unk18->unk14 = arg0->unk14;
                } else {
                    head = arg0->unk14;
                }
                if (arg0->unk14 != NULL) {
                    arg0->unk14->unk18 = arg0->unk18;
                }
                heapFree(arg0);
            }
            arg0 = arg0->unk14;
        } while (arg0 != NULL);
    }
    return head;
}

void func_806307AC(R35000aNode *arg0) {
    if (arg0 != NULL) {
        do {
            arg0->unk23 = 0;
            arg0 = arg0->unk14;
        } while (arg0 != NULL);
    }
}

void func_806307CC(R35000aNode *arg0, s32 arg1, u8 arg2, u8 arg3, s8 *arg4) {
    s8 found;

    found = 0;
    if (arg2 == 1) {
        arg0 = D_807F5FF0;
    }
    if (arg2 == 2) {
        arg0 = D_807F5FF4;
    }
    if (arg2 == 3) {
        arg0 = D_807F5FF8;
    }
    if (arg2 == 4) {
        arg0 = D_807F5FFC;
    }
    if (arg0 != NULL) {
        do {
            if (arg1 == arg0->unk0) {
                found = 1;
            } else {
                arg0 = arg0->unk14;
            }
        } while (arg0 != NULL && found == 0);
    }
    if (found != 0) {
        if (arg3) {
            arg0->unk10 = -1.0f;
        } else {
            arg0->unk1C = -2;
        }
    }
    *arg4 = found;
}

#ifdef NON_MATCHING
R35000aNode *func_80630890(R35000aNode *arg0, f32 arg1, f32 arg2, f32 arg3, R35000aNode **arg4) {
    R35000aNode *node;
    f32 dx;
    f32 dy;
    f32 dz;
    R35000aNode *head;
    R35000aNode *cur;
    R35000aNode *ins;
    R35000aNode *base;
    s32 inserted;
    f32 dist;

    dist = 0.0f;
    node = arg0;
    head = arg0;
    *arg4 = NULL;
    base = arg0;
    if (base != NULL) {
        do {
            dx = node->unk4 - arg1;
            dy = node->unk8 - arg2;
            dz = node->unkC - arg3;
            if (node->unk10 != -1.0) {
                node->unk10 = sqrtf(dx * dx + dy * dy + dz * dz);
            }
            node = node->unk14;
        } while (node != NULL);
    }
    if (base != NULL) {
        if (base->unk10 < base->unk1C || base->unk1C == -2) {
            *arg4 = base;
            if (base->unk1C == -2) {
                dist = 9999.0f;
            } else {
                dist = base->unk10;
            }
        }
        cur = base->unk14;
        if (cur != NULL) {
            do {
                inserted = 0;
                if ((dist < cur->unk10 && cur->unk10 < cur->unk1C) || cur->unk1C == -2) {
                    *arg4 = cur;
                    if (cur->unk1C == -2) {
                        dist = 9999.0f;
                    } else {
                        dist = cur->unk10;
                    }
                }
                ins = cur->unk18;
                dz = (f32)((cur->unk1C < cur->unk10) ? 9999.0 : cur->unk10);
                if (ins != NULL) {
                    do {
                        dx = (f32)((ins->unk1C < ins->unk10) ? 9999.0 : ins->unk10);
                        if (dz <= dx || cur->unk1C == -2) {
                            inserted = 1;
                            if (ins != cur->unk18) {
                                cur->unk18->unk14 = cur->unk14;
                                if (cur->unk14 != NULL) {
                                    cur->unk14->unk18 = cur->unk18;
                                }
                                node = ins->unk14;
                                ins->unk14 = cur;
                                cur->unk14 = node;
                                if (node != NULL) {
                                    node->unk18 = cur;
                                }
                                cur->unk18 = ins;
                            }
                        }
                        ins = ins->unk18;
                    } while (ins != NULL && inserted == 0);
                }
                if (inserted == 0) {
                    cur->unk18->unk14 = cur->unk14;
                    if (cur->unk14 != NULL) {
                        cur->unk14->unk18 = cur->unk18;
                    }
                    cur->unk18 = NULL;
                    cur->unk14 = head;
                    head->unk18 = cur;
                    head = cur;
                }
                cur = cur->unk14;
            } while (cur != NULL);
        }
    }
    return head;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/35000/func_80630890.s")
#endif

typedef struct R35000aGfx {
    u32 w0;
    u32 w1;
} R35000aGfx;

typedef struct R35000aModel {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u32 unk60;
} R35000aModel;

extern s32 D_8076A048;
extern u8 D_807F6009;
extern s32 D_807FBB60;
extern u8 D_2000180[];

void *func_80630DCC(s32, void *, void *, u8);
void *func_80636FFC(void *, void *, f32, f32, f32, s32, s32, s32);
void *func_80637B6C(void *, void *, f32, f32, f32, s32, s32, s32);
void *func_80715E94(void *, void *, s16);

#define R35000A_WRITE_GFX(pkt, _w0, _w1) { R35000aGfx *_g = (R35000aGfx *)(pkt); _g->w0 = (_w0); _g->w1 = (u32)(_w1); }

R35000aGfx *func_80630B70(R35000aGfx *arg0, R35000aNode *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s16 arg6, u8 arg7) {
    s32 ok;
    u8 type;
    R35000aModel *model;
    R35000aGfx *tmp;

    ok = 1;
    arg0->w0 = 0xE7000000;
    arg0->w1 = 0;
    arg0++;
    if (arg1 != NULL) {
        do {
            type = arg1->unk24;
            model = (R35000aModel *)arg1->unk0;
            if ((arg5 & 0x20) == 0 && type != 0 && type != 5) {
                ok = 0;
            }
            if ((arg5 & 0x20000) == 0 && type == 5) {
                ok = 0;
            }
            if ((arg5 & 0x10000) == 0 && type == 0 && (!(model->unk60 & 0x40000000) || (D_807FBB60 & 2))) {
                ok = 0;
            }
            if (ok != 0) {
                switch (type) {
                case 0:
                    tmp = func_80630DCC(D_8076A048, model, arg0, arg7);
                    tmp->w0 = 0xDA380003;
                    tmp->w1 = (u32)D_2000180;
                    arg0 = tmp + 1;
                    D_807F6009 = 0;
                    break;
                case 1:
                    arg0 = func_80636FFC(model, arg0, arg1->unk4, arg1->unk8, arg1->unkC, 1, arg6, arg7);
                    D_807F6009 = 1;
                    break;
                case 2:
                    arg0 = func_80637B6C(model, arg0, arg2, arg3, arg4, 1, arg6, arg7);
                    break;
                case 5:
                    arg0 = func_80715E94(model, arg0, arg6);
                    break;
                }
            } else {
                ok = 1;
            }
            arg1 = arg1->unk14;
        } while (arg1 != NULL);
    }
    R35000A_WRITE_GFX(arg0++, 0xE7000000, 0);
    return arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/35000/func_80630DCC.s")

typedef struct R35000aVec {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
} R35000aVec;

typedef struct R35000aActor {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ R35000aVec *unk4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ f32 unkC[4][4];
    /* 0x4C */ u8 pad4C[0x14];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 pad64[0x18];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x54];
    /* 0xDC */ s16 unkDC;
    /* 0xDE */ s16 unkDE;
    /* 0xE0 */ u8 padE0[4];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ s16 unkE8;
} R35000aActor;

f32 func_80612790(s16);
f32 func_80612794(s16);

#ifdef NON_MATCHING
void func_8063162C(R35000aActor *arg0, f32 *arg1) {
    f32 sinA;
    f32 cosA;
    f32 sinB;
    f32 cosB;
    f32 sinC;
    f32 cosC;
    f32 u;
    f32 pad0;
    f32 pad1;
    f32 pad2;
    f32 t20;

    sinA = func_80612790(arg0->unkE4);
    cosA = func_80612794(arg0->unkE4);
    sinB = func_80612790(arg0->unkE8);
    cosB = func_80612794(arg0->unkE8);
    sinC = func_80612790(arg0->unkE6);
    cosC = func_80612794(arg0->unkE6);
    u = arg0->unk4->unk34;
    t20 = cosB * sinC;
    *arg1++ = u * sinA * sinC + u * cosA * (cosB * cosC);
    *arg1++ = u * cosA * sinB;
    *arg1++ = u * cosA * t20 - u * sinA * cosC;
    *arg1++ = 0.0f;
    u = arg0->unk4->unk38;
    *arg1++ = u * sinA * (cosB * cosC) - u * cosA * sinC;
    *arg1++ = u * sinA * sinB;
    *arg1++ = u * cosA * cosC + u * sinA * t20;
    *arg1++ = 0.0f;
    u = arg0->unk4->unk3C;
    *arg1++ = u * sinB * cosC;
    *arg1++ = -u * cosB;
    *arg1++ = u * sinB * sinC;
    *arg1++ = 0.0f;
    *arg1++ = arg0->unk7C;
    *arg1++ = arg0->unk80;
    *arg1++ = arg0->unk84;
    *arg1 = 1.0f;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/35000/func_8063162C.s")
#endif













#ifdef NON_MATCHING
void func_806317D4(R35000aActor *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sinA;
    f32 cosA;
    f32 sinB;
    f32 cosB;
    f32 sinC;
    f32 cosC;
    f32 u;
    f32 pad0;
    f32 pad1;
    f32 pad2;

    sinA = func_80612790((s16)(s32)arg2);
    cosA = func_80612794((s16)(s32)arg2);
    sinB = func_80612790((s16)(s32)arg3);
    cosB = func_80612794((s16)(s32)arg3);
    sinC = func_80612790((s16)(s32)arg4);
    cosC = func_80612794((s16)(s32)arg4);
    u = arg0->unk4->unk34;
    *arg1++ = u * sinA * sinC + u * cosA * (cosB * cosC);
    *arg1++ = u * cosA * sinB;
    *arg1++ = u * cosA * (cosB * sinC) - u * sinA * cosC;
    *arg1++ = 0.0f;
    u = arg0->unk4->unk38;
    *arg1++ = u * sinA * (cosB * cosC) - u * cosA * sinC;
    *arg1++ = u * sinA * sinB;
    *arg1++ = u * cosA * cosC + u * sinA * (cosB * sinC);
    *arg1++ = 0.0f;
    u = arg0->unk4->unk3C;
    *arg1++ = u * sinB * cosC;
    *arg1++ = -u * cosB;
    *arg1++ = u * sinB * sinC;
    *arg1++ = 0.0f;
    *arg1++ = arg0->unk7C;
    *arg1++ = arg0->unk80;
    *arg1++ = arg0->unk84;
    *arg1 = 1.0f;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/35000/func_806317D4.s")
#endif

void func_8063162C(R35000aActor *, f32 *);
void func_806317D4(R35000aActor *, f32 *, f32, f32, f32);

void func_806319C4(R35000aActor *arg0, u8 arg1) {
    f32 sp78[4][4];
    f32 sp38[4][4];
    s16 angle;
    s16 sp34;
    s16 sp32;
    s16 sp30;
    s16 x;
    s16 y;

    if (arg0->unk60 & 1) {
        angle = (arg0->unkE6 - arg0->unkDC) & 0xFFF;
        if (angle >= 0x801) {
            angle -= 0x1000;
        }
        sp34 = (0x400 - arg0->unkDE) & 0xFFF;
        sp32 = (s32)(func_80612790(angle) * (f32)sp34);
        sp32 = (sp32 + arg0->unkE8) & 0xFFF;
        x = (s32)(func_80612794(angle) * (f32)sp34);
        x = (x + arg0->unkE4) & 0xFFF;
        sp30 = arg0->unkE6;
        if (arg1 != 0) {
            func_806317D4(arg0, (f32 *)sp78, x, sp32, sp30);
            guMtxCatF(arg0->unkC, sp78, arg0->unkC);
            return;
        }
        func_806317D4(arg0, (f32 *)arg0->unkC, x, sp32, sp30);
        return;
    }
    if (arg1 != 0) {
        func_8063162C(arg0, (f32 *)sp78);
        guMtxCatF(arg0->unkC, sp78, arg0->unkC);
        return;
    }
    func_8063162C(arg0, (f32 *)arg0->unkC);
}
