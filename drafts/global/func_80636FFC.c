// func_80636FFC (src/global/36880.c): stage 4 WIP: all instrs match except (1) frame/spill-slot layout (frame 0x138 ok, spill slots 0x70-0x7c etc fine but top-level locals pads guessed), (2) guRotateF arg setup: mine hoists addiu a0,&spB8 above c.eq.d (target keeps it after mfc1 a1), bc1tl vs bc1t on 3rd rotate, (3) flags local fl in v0 instead of a0 (target has extra move v0,a0). Needs s32 func_80636D38 prototype (changed from void).
typedef struct {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 pad61;
    /* 0x62 */ s16 unk62;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ u8 pad66[0x32];
    /* 0x98 */ s16 unk98;
} L80636FFCModel;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ struct L80636FFCCtl *unk4;
    /* 0x08 */ u8 pad8[0x214];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ u8 pad228[0xC8];
} L80636FFCPlayer; /* 0x2F0 */

typedef struct L80636FFCCtl {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
} L80636FFCCtl;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ Mtx unk20[2];
    /* 0xA0 */ u32 unkA0[2];
    /* 0xA8 */ u32 unkA8[2];
    /* 0xB0 */ u32 unkB0;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ void *unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 unkC2;
    /* 0xC3 */ u8 unkC3;
    /* 0xC4 */ u8 unkC4;
    /* 0xC5 */ u8 unkC5;
} L80636FFCObj;

void func_80639968(R36880eSeg *);
void func_8063E6B4(void *);
void func_8065C334(f32, f32, f32, s16, u8 *, u8 *, u8 *, s16);
void func_8065EB10(u8, s16, f32, f32, f32, s32, f32, s32);
s32 func_806D0964(s32, u8, s32);
void renderCalcPlayerDistanceAlpha(f32, f32, f32, f32, s16, s16 *);
f32 renderScaleDistanceByFov(f32);
Gfx *renderSetSegment6AndFog(Gfx *, s16, u8);
u32 osVirtualToPhysical(void *);

#define L80636FFC_PLAYER(i) (((L80636FFCPlayer *)D_807FC924)[i])

Gfx *func_80636FFC(L80636FFCObj *arg0, Gfx *arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, s16 arg6, s32 arg7) {
    f32 spF8[4][4];
    f32 spB8[4][4];
    f32 dx;
    f32 dy;
    f32 dz;
    u8 sel;
    u8 *sel78;
    f32 scale;
    L80636FFCModel *model;
    s32 pad;
    u8 sp97;
    u8 sp96;
    u8 sp95;
    s16 sp92;
    s16 sp90;
    s32 pad2;
    f32 sp88;
    f32 sp84;
    s32 fl;
    s32 pad3[3];

    if (0) {
        func_8063E6B4((void *)&arg5);
    }
    if (arg5 != 0) {
        dx = L80636FFC_PLAYER(D_807FC929).unk21C - arg0->unk0;
        dy = L80636FFC_PLAYER(D_807FC929).unk220 - arg0->unk4;
        dz = L80636FFC_PLAYER(D_807FC929).unk224 - arg0->unk8;
        dx *= dx;
        dy *= dy;
        dz *= dz;
        sp88 = sqrtf(dx + dy + dz);
        sp84 = renderScaleDistanceByFov(arg0->unkC0);
        if (arg0->unkC5 & 1) {
            sp84 = arg0->unkC0;
        }
        if (sp84 < sp88) {
            return arg1;
        }
    }
    if (arg0->unkC3 != 0) {
        func_8065EB10(arg0->unkC3, arg0->unkB6, arg0->unk0, arg0->unk4, arg0->unk8, arg0->unkC0, sp88 / sp84, arg6);
    }
    if (arg0->unkB4 == 0 || arg0->unkB4 == 0x241) {
        return arg1;
    }
    if (arg0->unkB4 == 0x74 || arg0->unkB4 == 0x288 || arg0->unkB4 == 0x290) {
        arg0->unk14 += 10.0;
    }
    guScaleF(spF8, arg0->unkC, arg0->unkC, arg0->unkC);
    if (arg0->unk10 != 0.0) {
        guRotateF(spB8, arg0->unk10, 1.0f, 0.0f, 0.0f);
        guMtxCatF(spF8, spB8, spF8);
    }
    if (arg0->unk14 != 0.0) {
        guRotateF(spB8, arg0->unk14, 0.0f, 1.0f, 0.0f);
        guMtxCatF(spF8, spB8, spF8);
    }
    if (arg0->unk18 != 0.0) {
        guRotateF(spB8, arg0->unk18, 0.0f, 0.0f, 1.0f);
        guMtxCatF(spF8, spB8, spF8);
    }
    guTranslateF(spB8, arg0->unk0, arg0->unk4, arg0->unk8);
    guMtxCatF(spF8, spB8, spF8);
    guMtxF2L(spF8, &arg0->unk20[D_807444FC]);
    gDPPipeSync(arg1++);
    gSPSegment(arg1++, 8, osVirtualToPhysical((void *)arg0->unkB0));
    sel78 = NULL;
    if (arg0->unkB6 != -1) {
        sp90 = hashTableLookup(arg0->unkB6);
        func_80636D38(&D_807F6000[sp90], 0, 1);
        sel78 = D_807F6000[sp90].unk78;
        if (func_806D0964(*(s32 *)D_807F6000[sp90].unk24, D_807FC929, (s32)sel78) != 0) {
            return arg1;
        }
    }
    if (sel78 != NULL) {
        gSPSegment(arg1++, 9, osVirtualToPhysical((void *)((u32 *)sel78)[D_807444FC]));
    }
    gSPMatrix(arg1++, osVirtualToPhysical(&arg0->unk20[D_807444FC]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    if (arg0->unkB8 != 0) {
        sel = D_807444FC;
        func_80639968((R36880eSeg *)arg0);
    } else {
        sel = 0;
    }
    gSPSegment(arg1++, 10, osVirtualToPhysical((void *)arg0->unkA0[sel]));
    gSPClearGeometryMode(arg1++, G_FOG | G_CULL_BOTH);
    if (arg5 != 0 && arg0->unkC2 == 0) {
        model = D_807F6000[sp90].unk7C;
        if (model != NULL) {
            scale = model->unk98;
        } else {
            scale = 0.0f;
        }
        func_8065C334(arg0->unk0, arg0->unk4 + scale, arg0->unk8, 0, &sp97, &sp96, &sp95, arg6);
        scale = arg0->unkC4 / 15.0f;
        sp97 = sp97 * scale;
        sp96 = sp96 * scale;
        sp95 = sp95 * scale;
    } else {
        sp95 = 0xFF;
        sp96 = 0xFF;
        sp97 = 0xFF;
    }
    gDPSetPrimColor(arg1++, 0, 0xFF, sp97, sp96, sp95, 0xFF);
    if (arg5 != 0) {
        if (arg0->unkB6 != -1 && (model = D_807F6000[sp90].unk7C) != NULL && model->unk60 == 1) {
            func_8063E6B4(model);
            sp92 = ((L80636FFCModel *)D_807F6000[sp90].unk7C)->unk64;
        } else {
            renderCalcPlayerDistanceAlpha(arg0->unk0, arg0->unk4, arg0->unk8, arg0->unkC0, arg0->unkB4, &sp92);
            if (arg0->unkB6 != -1) {
                model = D_807F6000[sp90].unk7C;
                if (model != NULL && D_80750AB4 == 1) {
                    model->unk62 = sp92;
                }
            }
            if (arg0->unkB6 != -1) {
                model = D_807F6000[sp90].unk7C;
                if (model != NULL) {
                    func_8063E6B4(model);
                }
            }
            if (arg0->unkB6 != -1) {
                model = D_807F6000[sp90].unk7C;
                if (model != NULL && D_80750AB4 == 1) {
                    sp92 = model->unk64;
                }
            }
        }
    } else {
        sp92 = 0xFF;
    }
    if (sp92 != 0) {
        if (arg0->unkB6 != -1) {
            fl = D_807F6000[sp90].unk8C;
            if (fl != 0) {
                if ((fl & 8) && L80636FFC_PLAYER(D_807FC929).unk4->unk58 != 2) {
                    sp92 = 0x64;
                }
                if ((D_807F6000[sp90].unk8C & 2) && L80636FFC_PLAYER(D_807FC929).unk4->unk58 != 3) {
                    sp92 = 0x64;
                }
                if ((D_807F6000[sp90].unk8C & 4) && L80636FFC_PLAYER(D_807FC929).unk4->unk58 != 5) {
                    sp92 = 0x64;
                }
                if ((D_807F6000[sp90].unk8C & 1) && L80636FFC_PLAYER(D_807FC929).unk4->unk58 != 6) {
                    sp92 = 0x64;
                }
                if ((D_807F6000[sp90].unk8C & 0x10) && L80636FFC_PLAYER(D_807FC929).unk4->unk58 != 4) {
                    sp92 = 0x64;
                }
            }
        }
        arg1 = renderSetSegment6AndFog(arg1, sp92, 0);
        gDPPipeSync(arg1++);
        gSPDisplayList(arg1++, osVirtualToPhysical((void *)arg0->unkA0[sel]));
        gDPPipeSync(arg1++);
        gSPDisplayList(arg1++, osVirtualToPhysical((void *)arg0->unkA8[sel]));
    }
    gDPPipeSync(arg1++);
    gSPPopMatrix(arg1++, G_MTX_MODELVIEW);
    return arg1;
}
