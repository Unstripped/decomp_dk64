// func_806FCC88 (src/global/100180.c): func_806FCC88 (src/global/100180.c): stage 5 (parked NON_MATCHING), no dead stmts. Instruction multiset identical to target (only 5 lines of as1 scheduling off: addiu a3,a2,-1 after negu a1; sh zero,58(s0) hoisted to first vertex store; sh t2,34(s0) last). KEY: glyph via struct array ((NM3Glyph *)D_80754A18[font])[chr].unk2/.unk0 (not byte offsets) took diff 101->11; vertex stores written as vp[n].v.ob/tc in a permuted order (random walk on multiset diff, tools shuf2) fixed v0/t2 temp colouring; chr = arg1->unk4[i++] fixes addu operand order. Remaining: find store order/line barriers giving same colouring AND target store schedule (target order vp0 ob0,ob1,ob2,tc0,tc1, vp1..., vp2 ob1 before ob0, zero tc1 stores last).
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

extern u8 D_80754A36[];
extern u8 D_2000200[];
void heapFreeDeferred(void *);
Gfx *func_8070068C(Gfx *);

typedef struct { s16 unk0; u8 unk2; u8 unk3; } NM3Glyph;
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
                            gw = ((NM3Glyph *)D_80754A18[arg1->unkC])[chr].unk2;
                            gx = ((NM3Glyph *)D_80754A18[arg1->unkC])[chr].unk0;
                            gh = D_80754A36[arg1->unkC * 6];
                            if (started == 0) {
                                started = 1;
                                dl = func_806FBEF0(dl, arg1->unkC, (s16)line);
                            }
                            guPosition(mp + idx, 0.0f, 0.0f, arg1->unk8[idx].unk20 * 57.295776f, arg1->unk8[idx].unk30,
                                       arg1->unk8[idx].unk0, arg1->unk8[idx].unk4, 0.0f);
                            gSPMatrix(dl++, mp + idx, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                            gDPPipeSync(dl++);
                            vp[3].v.tc[1] = 0;
                            vp[0].v.ob[0] = -(gw * 2);
                            vp[0].v.ob[1] = gh * 2 - 1;
                            vp[0].v.ob[2] = -5;
                            vp[0].v.tc[0] = gx << 6;
                            vp[0].v.tc[1] = gh << 6;
                            vp[1].v.ob[0] = gw * 2 - 1;
                            vp[1].v.ob[1] = gh * 2 - 1;
                            vp[1].v.ob[2] = -5;
                            vp[1].v.tc[0] = (gx + gw) << 6;
                            vp[1].v.tc[1] = gh << 6;
                            vp[2].v.ob[0] = gw * 2 - 1;
                            vp[2].v.ob[2] = -5;
                            vp[2].v.tc[0] = (gx + gw) << 6;
                            vp[2].v.tc[1] = 0;
                            vp[3].v.ob[1] = -(gh * 2);
                            vp[3].v.ob[0] = -(gw * 2);
                            vp[3].v.ob[2] = -5;
                            vp[3].v.tc[0] = gx << 6;
                            vp[2].v.ob[1] = -(gh * 2);
                            vp += 4;
                            gSPVertex(dl++, osVirtualToPhysical(spB4), 4, 0);
                            gSP1Quadrangle(dl++, 0, 1, 2, 3, 0);
                            gSPPopMatrix(dl++, G_MTX_MODELVIEW);
                            spB4 = vp;
                        }
                        idx++;
                    }
                    chr = arg1->unk4[i++];
                } while (chr);
                idx = 0;
            }
            line++;
        } while (line < D_80754A35[arg1->unkC * 6] + 1);
    }
    gSPMatrix(dl++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(dl++, D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gDPPipeSync(dl++);
    return dl;
}
