// func_806FCC88 (src/global/100180.c): func_806FCC88 (src/global/100180.c): Stage 5 (parked NON_MATCHING): frame 0xC8, s0-s7/fp/fs0-fs1 and stack layout (line C4, chr/started C3/C2, idx BC, vp B8, spB4 B4, mp B0) match; diff is regalloc only: post-call chr is uopt v1 here vs ugen t6 in target (ring shifts t4/t5 after); deadsweep (chr/idx/started extras) got 65 text lines, permuter -j2 900s no gain
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0xC];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    u8 pad24[0xC];
    f32 unk30;
    u8 pad34[4];
} HbTextElem;

typedef struct {
    u8 pad0[4];
    u8 *unk4;
    HbTextElem *unk8;
    u8 unkC;
    u8 unkD;
} HbTextObj;

extern u8 *D_807549FC[];
extern u8 D_80754A35[];
extern u8 D_80754A36[];
extern u8 D_2000000[];
extern u8 D_2000200[];
s32 func_806FB914(s16, u8 *);
void heapFreeDeferred(void *);
Gfx *func_8070068C(Gfx *);
Gfx *func_806FBEF0(Gfx *, u8, s16);
s32 func_806FB914(s16, u8 *);

Gfx *func_806FCC88(Gfx *dl, HbTextObj *arg1) {
    s32 line;
    u8 chr;
    u8 started;
    s32 idx;
    Vtx *vp;
    Vtx *spB4;
    Mtx *mp;
    s32 i;
    s32 gw;
    s32 gx;
    s32 gh;

    idx = 0;
    vp = (Vtx *)func_80610FE8(arg1->unkD << 6);
    heapFreeDeferred(vp);
    mp = (Mtx *)func_80610FE8(arg1->unkD << 6);
    heapFreeDeferred(mp);
    spB4 = vp;
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    dl = func_8070068C(dl);
    line = 1;
    if (D_80754A35[arg1->unkC * 6] + 1 >= 2) {
        do {
            started = 0;
            i = 1;
            chr = arg1->unk4[0];
            if (chr) {
                do {
                    if (chr != 0x20) {
                        func_806FB914(arg1->unkC, &chr);
                        if (chr >= (D_807549FC[arg1->unkC] + line)[-1] && chr < (D_807549FC[arg1->unkC] + line)[0]) {
                            gw = ((u8 *)((u8 **)D_80754A18)[arg1->unkC])[chr * 4 + 2];
                            gx = *(s16 *)((u8 *)((u8 **)D_80754A18)[arg1->unkC] + chr * 4);
                            gh = D_80754A36[arg1->unkC * 6];
                            if (started == 0) {
                                started = 1;
                                dl = func_806FBEF0(dl, arg1->unkC, line);
                            }
                            guPosition(mp + idx, 0.0f, 0.0f, arg1->unk8[idx].unk20 * 57.295776f, arg1->unk8[idx].unk30,
                                       arg1->unk8[idx].unk0, arg1->unk8[idx].unk4, 0.0f);
                            gSPMatrix(dl++, mp + idx, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                            gDPPipeSync(dl++);
                            ((s16 *)vp)[0] = -(gw * 2);
                            ((s16 *)vp)[1] = gh * 2 - 1;
                            ((s16 *)vp)[2] = -5;
                            ((s16 *)vp)[4] = gx << 6;
                            ((s16 *)vp)[5] = gh << 6;
                            ((s16 *)vp)[8] = gw * 2 - 1;
                            ((s16 *)vp)[9] = gh * 2 - 1;
                            ((s16 *)vp)[10] = -5;
                            ((s16 *)vp)[12] = (gx + gw) << 6;
                            ((s16 *)vp)[13] = gh << 6;
                            ((s16 *)vp)[17] = -(gh * 2);
                            ((s16 *)vp)[16] = gw * 2 - 1;
                            ((s16 *)vp)[18] = -5;
                            ((s16 *)vp)[20] = (gx + gw) << 6;
                            ((s16 *)vp)[21] = 0;
                            ((s16 *)vp)[25] = -(gh * 2);
                            ((s16 *)vp)[24] = -(gw * 2);
                            ((s16 *)vp)[26] = -5;
                            ((s16 *)vp)[28] = gx << 6;
                            ((s16 *)vp)[29] = 0;
                            vp += 4;
                            gSPVertex(dl++, osVirtualToPhysical(spB4), 4, 0);
                            gSP1Quadrangle(dl++, 0, 1, 2, 3, 0);
                            gSPPopMatrix(dl++, G_MTX_MODELVIEW);
                            spB4 = vp;
                        }
                        idx++;
                    }
                    chr = arg1->unk4[i];
                    i++;
                } while (chr);
                idx = 0;
            }
            line++;
        } while (line < D_80754A35[arg1->unkC * 6] + 1);
    }
    gSPMatrix(dl++, D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(dl++, D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gDPPipeSync(dl++);
    return dl;
}
