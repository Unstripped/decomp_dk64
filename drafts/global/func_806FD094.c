// func_806FD094 (src/global/100180.c): func_806FD094 (src/global/100180.c): Stage 5 (parked NON_MATCHING): frame 0xC8 (needs 2 extra f32 locals fa/fb, unknown real ones), regs/stack match; diff is regalloc only: post-call chr is v1 here vs t3 in target (chr range must interfere with vertex temps), tail ring shifted; deadsweep with 'if (chr && chr) {}' after gSP1Quadrangle and after line++ gets 57 lines (82 baseline)
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

extern u8 D_2000180[];

Gfx *func_806FD094(Gfx *dl, HbTextObj *arg1) {
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
    f32 fa;
    f32 fb;

    idx = 0;
    vp = (Vtx *)func_80610FE8(arg1->unkD << 6);
    heapFreeDeferred(vp);
    mp = (Mtx *)func_80610FE8(arg1->unkD << 6);
    heapFreeDeferred(mp);
    spB4 = vp;
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    gSPMatrix(dl++, D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(dl++, D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(dl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
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
                            guPosition(mp + idx, arg1->unk8[idx].unk18 * 57.295776f,
                                       arg1->unk8[idx].unk1C * 57.295776f, arg1->unk8[idx].unk20 * 57.295776f,
                                       arg1->unk8[idx].unk30, arg1->unk8[idx].unk0, arg1->unk8[idx].unk4,
                                       arg1->unk8[idx].unk8);
                            gSPMatrix(dl++, mp + idx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                            gDPPipeSync(dl++);
                            ((s16 *)vp)[0] = -(gw * 2);
                            ((s16 *)vp)[1] = gh * 2 - 1;
                            ((s16 *)vp)[2] = 0;
                            ((s16 *)vp)[4] = gx << 6;
                            ((s16 *)vp)[5] = gh << 6;
                            ((s16 *)vp)[8] = gw * 2 - 1;
                            ((s16 *)vp)[9] = gh * 2 - 1;
                            ((s16 *)vp)[10] = 0;
                            ((s16 *)vp)[12] = (gx + gw) << 6;
                            ((s16 *)vp)[13] = gh << 6;
                            ((s16 *)vp)[17] = -(gh * 2);
                            ((s16 *)vp)[16] = gw * 2 - 1;
                            ((s16 *)vp)[18] = 0;
                            ((s16 *)vp)[20] = (gx + gw) << 6;
                            ((s16 *)vp)[21] = 0;
                            ((s16 *)vp)[25] = -(gh * 2);
                            ((s16 *)vp)[24] = -(gw * 2);
                            ((s16 *)vp)[26] = 0;
                            ((s16 *)vp)[28] = gx << 6;
                            ((s16 *)vp)[29] = 0;
                            vp += 4;
                            gSPVertex(dl++, osVirtualToPhysical(spB4), 4, 0);
                            gSP1Quadrangle(dl++, 0, 1, 2, 3, 0);
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
    gDPPipeSync(dl++);
    return dl;
}
