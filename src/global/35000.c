#include "common.h"

typedef struct RenderEntry RenderEntry;
struct RenderEntry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ RenderEntry *unk14;
    /* 0x18 */ RenderEntry *unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[3];
};

extern RenderEntry *D_807F5FF0;
extern RenderEntry *D_807F5FF4;
extern RenderEntry *D_807F5FF8;
extern RenderEntry *D_807F5FFC;

void renderEntryListsReset(void) {
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

void renderEntryListFree(RenderEntry *);

void func_8063039C(void) {
    renderEntryListFree(D_807F5FF4);
    D_807F5FF4 = 0;
}

void *heapAlloc(s32);

RenderEntry *renderEntryAddOrUpdate(RenderEntry *arg0, u8 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, s16 arg7, u8 arg8, s16 arg9, u8 arg10) {
    s32 found;
    RenderEntry *prev;
    RenderEntry *node;
    RenderEntry *head;

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
        node = heapAlloc(0x28);
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

RenderEntry *renderEntryRemove(RenderEntry *arg0, s32 arg1, u8 arg2, u8 *arg3) {
    u8 found;
    RenderEntry *prev;
    RenderEntry *head;

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

void renderEntryListFree(RenderEntry *arg0) {
    RenderEntry *cur;

    if (arg0 != NULL) {
        do {
            cur = arg0;
            arg0 = arg0->unk14;
            heapFree(cur);
        } while (arg0 != NULL);
    }
}

RenderEntry *renderEntryListPurgeUntouched(RenderEntry *arg0) {
    RenderEntry *head;

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

void renderEntryListClearTouched(RenderEntry *arg0) {
    if (arg0 != NULL) {
        do {
            arg0->unk23 = 0;
            arg0 = arg0->unk14;
        } while (arg0 != NULL);
    }
}

void func_806307CC(RenderEntry *arg0, s32 arg1, u8 arg2, u8 arg3, s8 *arg4) {
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
RenderEntry *func_80630890(RenderEntry *arg0, f32 arg1, f32 arg2, f32 arg3, RenderEntry **arg4) {
    RenderEntry *node;
    f32 dx;
    f32 dy;
    f32 dz;
    RenderEntry *head;
    RenderEntry *cur;
    RenderEntry *ins;
    RenderEntry *base;
    s32 inserted;
    f32 dist;
    f32 cmpB;

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
                dz = (f32)((cur->unk1C < cur->unk10) ? 9999.0 : cur->unk10);
                ins = cur->unk18;
                if (ins != NULL) {
                    do {
                        cmpB = (f32)((ins->unk1C < ins->unk10) ? 9999.0 : ins->unk10);
                        if (dz <= cmpB || cur->unk1C == -2) {
                            inserted = 1;
                            if (ins != cur->unk18) {
                                cur->unk18->unk14 = cur->unk14;
                                node = cur->unk14;
                                if (node != NULL) {
                                    node->unk18 = cur->unk18;
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

typedef struct GfxWords {
    u32 w0;
    u32 w1;
} GfxWords;

typedef struct EntryModel {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u32 unk60;
} EntryModel;

extern s32 D_8076A048;
extern u8 D_807F6009;
extern s32 D_807FBB60;
extern u8 D_2000180[];

void *func_80630DCC(s32, void *, GfxWords *, u8);
void *func_80636FFC(void *, void *, f32, f32, f32, s32, s32, s32);
void *renderModelQuadGfx(void *, void *, f32, f32, f32, s32, s32, s32);
void *func_80715E94(void *, void *, s16);

#define WRITE_GFX_WORDS(pkt, _w0, _w1) { GfxWords *_g = (GfxWords *)(pkt); _g->w0 = (_w0); _g->w1 = (u32)(_w1); }

GfxWords *renderEntryListBuildDisplayList(GfxWords *arg0, RenderEntry *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s16 arg6, u8 arg7) {
    s32 ok;
    u8 type;
    EntryModel *model;
    GfxWords *tmp;

    ok = 1;
    arg0->w0 = 0xE7000000;
    arg0->w1 = 0;
    arg0++;
    if (arg1 != NULL) {
        do {
            type = arg1->unk24;
            model = (EntryModel *)arg1->unk0;
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
                    arg0 = renderModelQuadGfx(model, arg0, arg2, arg3, arg4, 1, arg6, arg7);
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
    WRITE_GFX_WORDS(arg0++, 0xE7000000, 0);
    return arg0;
}

#ifdef NON_MATCHING
typedef struct ModelInfo {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
} ModelInfo;

typedef struct ActorCtl {
    /* 0x000 */ u8 pad0[0x1A4];
    /* 0x1A4 */ u8 unk1A4;
} ActorCtl;

typedef struct RenderActor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ModelInfo *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 pad5E[2];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x45];
    /* 0x0CD */ u8 unkCD;
    /* 0x0CE */ s16 unkCE;
    /* 0x0D0 */ u8 padD0[0x58];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[2];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[0x16];
    /* 0x148 */ void *unk148[2];
    /* 0x150 */ u8 pad150[0xE];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[0xB];
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 unk16D;
    /* 0x16E */ u8 pad16E[6];
    /* 0x174 */ ActorCtl *unk174;
} RenderActor;

typedef struct PlayerView {
    /* 0x000 */ u8 pad0[0x21C];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ u8 pad228[0x2F0 - 0x228];
} PlayerView;

extern u8 D_807444FC;
extern PlayerView *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;

void func_80614A64(void *);
void *renderActorDisplayList(void *, void *);
s32 mapPointOutsideClipBounds(f32, f32, f32, u8, s32);
void lightSampleColorAtPosition(f32, f32, f32, s16, u8 *, u8 *, u8 *, s16);
void *func_80722294(void *, void *, u8);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void renderCalcPlayerDistanceAlpha(f32, f32, f32, f32, s16, s16 *);
f32 renderScaleDistanceByFov(f32);
void *renderSetSegment6AndFog(void *, s16, u8);

#define RENDER_ACT ((RenderActor *)arg1)
#define CUR_PLAYER_VIEW ((PlayerView *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0))

void *func_80630DCC(s32 arg0, void *arg1, GfxWords *arg2, u8 arg3) {
    ActorCtl *ctl;
    s32 flag;
    f32 dx;
    f32 dy;
    f32 dz;
    u8 spCB;
    u8 spCA;
    u8 spC9;
    f64 x;
    f32 size;
    f32 spB8;
    f64 d;

    spB8 = 1.0f;
    if (!(RENDER_ACT->unk60 & 4)) {
        flag = 0;
        if (D_807FC928 >= 2 && (RENDER_ACT->unk5C & 1) && (ctl = RENDER_ACT->unk174, D_807FC929 != ctl->unk1A4)) {
            flag = 1;
        }
        if (flag == 0) {
            return arg2;
        }
    }
    if (RENDER_ACT->unk58 != 0x1F && RENDER_ACT->unk58 != 0x27 && RENDER_ACT->unk58 != 0xAE && !(RENDER_ACT->unk60 & 0x400)) {
        dx = CUR_PLAYER_VIEW->unk21C - RENDER_ACT->unk7C;
        dy = CUR_PLAYER_VIEW->unk220 - RENDER_ACT->unk80;
        dz = CUR_PLAYER_VIEW->unk224 - RENDER_ACT->unk84;
        dx = dx * dx;
        dy = dy * dy;
        dz = dz * dz;
        if (sqrtf(dx + dy + dz) > renderScaleDistanceByFov(RENDER_ACT->unk12A)) {
            return arg2;
        }
        if (mapPointOutsideClipBounds(RENDER_ACT->unk7C, RENDER_ACT->unk80, RENDER_ACT->unk84, RENDER_ACT->unk130, RENDER_ACT->unk131)) {
            return arg2;
        }
    }
    RENDER_ACT->unk60 |= 0x100;
    if (!(RENDER_ACT->unk60 & 0x200)) {
        func_80614A64(arg1);
    }
    WRITE_GFX_WORDS(arg2++, 0xE7000000, 0);
    WRITE_GFX_WORDS(arg2++, 0xD9FFFFFF, 0x200001);
    WRITE_GFX_WORDS(arg2++, 0xD9FEF9FF, 0);
    if (RENDER_ACT->unk58 == 0x135) {
        WRITE_GFX_WORDS(arg2++, 0xD9FFFFFE, 0);
    }
    WRITE_GFX_WORDS(arg2++, 0xDB06003C, osVirtualToPhysical(RENDER_ACT->unk148[D_807444FC]));
    if (RENDER_ACT->unk60 & 0x1000) {
        arg2 = func_80722294(arg2, arg1, D_807FC929);
        WRITE_GFX_WORDS(arg2++, 0xD9FFFFFF, 0x20000);
        WRITE_GFX_WORDS(arg2++, 0xFA0000FF, 0xFFFFFFFF);
    } else {
        u8 node;
        s32 padE[1];
        f32 sp88;
        f32 sp84;
        f32 sp80;
        s32 padF[1];
        WRITE_GFX_WORDS(arg2++, 0xD9FDFFFF, 0);
        if (RENDER_ACT->unk60 & 0x800000) {
            spCB = RENDER_ACT->unk16A;
            spCA = RENDER_ACT->unk16B;
            spC9 = RENDER_ACT->unk16C;
        } else {
            node = RENDER_ACT->unkCD;
            if (node) {
                actorGetNodePos(arg1, node, &sp88, &sp84, &sp80);
            } else {
                sp88 = RENDER_ACT->unk7C;
                sp84 = RENDER_ACT->unk80;
                sp80 = RENDER_ACT->unk84;
            }
            lightSampleColorAtPosition(sp88, sp84, sp80, RENDER_ACT->unkCE, &spCB, &spCA, &spC9, RENDER_ACT->unk12C);
            if (!(RENDER_ACT->unk64 & 1)) {
                dx = RENDER_ACT->unk16D / 15.0f;
                spCB = spCB * dx;
                spCA = spCA * dx;
                spC9 = spC9 * dx;
            }
        }
        WRITE_GFX_WORDS(arg2++, 0xFA0000FF, (spCB << 24) | (spCA << 16) | (spC9 << 8) | 0xFF);
    }
    if (RENDER_ACT->unk60 & 0x8000) {
        renderCalcPlayerDistanceAlpha(RENDER_ACT->unk7C, RENDER_ACT->unk80, RENDER_ACT->unk84, RENDER_ACT->unk12A, -1, &RENDER_ACT->unk128);
    }
    if (RENDER_ACT->unk5C != 0x80 && RENDER_ACT->unk5C != 0x40 && RENDER_ACT->unk5C != 8) {
        if ((RENDER_ACT->unk80 - 5.0f < CUR_PLAYER_VIEW->unk220 && CUR_PLAYER_VIEW->unk220 < RENDER_ACT->unk80 + 2.0 * RENDER_ACT->unk15E) || (RENDER_ACT->unk6A & 0x2000)) {
            size = RENDER_ACT->unk84 - CUR_PLAYER_VIEW->unk224;
            dz = RENDER_ACT->unk7C - CUR_PLAYER_VIEW->unk21C;
            dy = RENDER_ACT->unk4->unk38;
            if (dy < 0.01) {
                dy = 0.01f;
            }
            spB8 = ((((f64)(s32)(size * size + dz * dz) / (dy / 0.15) / 400.0) > 0.3 ? ((f64)(s32)(size * size + dz * dz) / (dy / 0.15) / 400.0) - 0.3 : 0.0) < 1.0) ? (((f64)(s32)(size * size + dz * dz) / (dy / 0.15) / 400.0) > 0.3 ? ((f64)(s32)(size * size + dz * dz) / (dy / 0.15) / 400.0) - 0.3 : 0.0) : 1.0;
        }
    }
    dx = RENDER_ACT->unk128 * spB8;
    if (dx != 0.0f) {
        arg2 = renderActorDisplayList(renderSetSegment6AndFog(arg2, dx, 1), arg1);
    }
    WRITE_GFX_WORDS(arg2++, 0xE7000000, 0);
    WRITE_GFX_WORDS(arg2++, 0xE3001001, 0);
    WRITE_GFX_WORDS(arg2++, 0xE7000000, 0);
    return arg2;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/35000/func_80630DCC.s")
#endif

typedef struct ModelScale {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
} ModelScale;

typedef struct MatrixActor {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ ModelScale *unk4;
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
} MatrixActor;

f32 func_80612790(s16);
f32 func_80612794(s16);

void actorBuildModelMatrix(MatrixActor *arg0, f32 *arg1) {
    f32 sinA;
    f32 cosA;
    f32 sinB;
    f32 cosB;
    f32 sinC;
    f32 cosC;
    f32 u;
    f32 us;
    f32 pad0;
    f32 t20;

    sinA = func_80612790(arg0->unkE4);
    cosA = func_80612794(arg0->unkE4);
    sinB = func_80612790(arg0->unkE8);
    cosB = func_80612794(arg0->unkE8);
    sinC = func_80612790(arg0->unkE6);
    cosC = func_80612794(arg0->unkE6);
    u = arg0->unk4->unk34;
    us = u * sinA;
    u = u * cosA;
    *arg1++ = us * sinC + u * (cosB * cosC);
    *arg1++ = u * sinB;
    *arg1++ = (f32)u * (cosB * sinC) - us * cosC;
    *arg1++ = 0.0f;
    u = arg0->unk4->unk38;
    us = u * sinA;
    u = u * cosA;
    *arg1++ = (f32)us * (cosB * cosC) - u * sinC;
    *arg1++ = us * sinB;
    *arg1++ = u * cosC + us * (cosB * sinC);
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













void actorBuildModelMatrixFromAngles(MatrixActor *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sinA;
    f32 cosA;
    f32 sinB;
    f32 cosB;
    f32 sinC;
    f32 cosC;
    f32 u;
    f32 us;
    f32 pad0;
    f32 t20;

    sinA = func_80612790((s16)(s32)arg2);
    cosA = func_80612794((s16)(s32)arg2);
    sinB = func_80612790((s16)(s32)arg3);
    cosB = func_80612794((s16)(s32)arg3);
    sinC = func_80612790((s16)(s32)arg4);
    cosC = func_80612794((s16)(s32)arg4);
    u = arg0->unk4->unk34;
    us = u * sinA;
    u = u * cosA;
    *arg1++ = us * sinC + u * (cosB * cosC);
    *arg1++ = u * sinB;
    *arg1++ = (f32)u * (cosB * sinC) - us * cosC;
    *arg1++ = 0.0f;
    u = arg0->unk4->unk38;
    us = u * sinA;
    u = u * cosA;
    *arg1++ = (f32)us * (cosB * cosC) - u * sinC;
    *arg1++ = us * sinB;
    *arg1++ = u * cosC + us * (cosB * sinC);
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

void actorBuildModelMatrix(MatrixActor *, f32 *);
void actorBuildModelMatrixFromAngles(MatrixActor *, f32 *, f32, f32, f32);

void actorUpdateModelMatrix(MatrixActor *arg0, u8 arg1) {
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
            actorBuildModelMatrixFromAngles(arg0, (f32 *)sp78, x, sp32, sp30);
            guMtxCatF(arg0->unkC, sp78, arg0->unkC);
            return;
        }
        actorBuildModelMatrixFromAngles(arg0, (f32 *)arg0->unkC, x, sp32, sp30);
        return;
    }
    if (arg1 != 0) {
        actorBuildModelMatrix(arg0, (f32 *)sp78);
        guMtxCatF(arg0->unkC, sp78, arg0->unkC);
        return;
    }
    actorBuildModelMatrix(arg0, (f32 *)arg0->unkC);
}
