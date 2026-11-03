// gfxDrawTexturedTileGrid (src/global/103AB0.c): L933 (leftovers7): stage 5, COUNT EXACT (948 lines = target; frame 0x1d8, same s-reg set), 90 full / 83 shape (was 98/90). Re-derived: ours matches the target's top 8 spill slots, remaining diff = (1) candidate/slot ORDER of 6 expressions: target ascending slot order is u0 < x+tw < ylo < yhi < siz < xe-1 < ye-1 < (s16)u < vb < ypos1 < (s16)v < ypos0 (ours: siz,(s16)u first, x+tw after yhi, (s16)v/ypos0 before xe-1, u0 last); (2) y-body entry order: target converts (f32)tw (f24) before xe-1/ye-1/vb and (f32)th later; lbu s7 (arg15) in the y-preheader (ours: x-preheader); (3) target has a ye temp spill (sw s3,0xC8) where ours needs the FAKE if((ye>>5)) {} (srl s7 early); (4) u store in beqz delay slot. NEW this unit: anneal over statement order+dead tests PLUS toggles (named local vs inline: siz, ylo, vb, ua, xf, vc; xn=x+tw local; y2/v2 body copies; declaration order) found: ylo inlined as (y>>5)-1 in ult, xf and ua computed at the top of the x body, vb right after the siz chain, 6 FAKEs left. Tried without gain: switch(siz) (190 shape), y as while, local types s32/u32/s16/u16/u8 for every local (single flips), u0 as named var (const-propagated away: identical), y2/v2 copies, no-FAKE base (best 166 after 3x900 s SA).
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6[2];
    s16 unk8;
    s16 unkA;
    s8 unkC;
    s8 unkD;
    s8 unkE;
    u8 unkF;
} VtxColorView;


void vtxSetColor(VtxColorView *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5);
void vtxSetPosTex(s16 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, u8 arg5);
void gfxDrawTexturedTileGrid(Gfx **arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4, u32 arg5, u32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, u8 arg13, u8 arg14, u8 arg15, void (*arg16)()) {
    Gfx *dl;
    s32 y;
    VtxColorView *vtx;
    s32 u;
    s32 v;
    u32 ustep;
    s16 xa;
    s32 uls;
    s32 vb;
    s32 vc;
    s32 x;
    s32 lrs;
    f32 xf;
    u32 xs;
    s32 ua;
    u32 ys;
    s32 pad1;
    s32 lrt;
    u32 xe;
    s32 ult;
    u32 ye;
    u8 flag;
    s32 ylo;
    f32 fsc;
    u32 tw;
    s32 siz;
    u32 th;
    u32 vstep;

    ustep = arg13 * arg5;
    dl = *arg0;
    flag = 1;
    vstep = arg13 * arg6;
    y = arg1;  // FAKE: defines y so the early dead read below is legal
    xs = (u32)(arg7 * 32.0f);
    fsc = arg13;
    xe = (u32)(arg9 * 32.0f);
    ye = (u32)(arg10 * 32.0f);
    if ((ye >> 5)) {}  // FAKE: dead test, steers spill-slot order / holes
    th = arg6 << 5;
    tw = arg5 << 5;
    if (arg3 > 0x200) {
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        flag = 0;
    } else {
        gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    ys = (u32)(arg8 * 32.0f);
    vtx = (VtxColorView *)heapAlloc(((((xe - xs) / tw) + 1) * (((ye - ys) / th) + 1)) << 6);
    heapFreeDeferred(vtx);
    gDPPipeSync(dl++);
    v = (s32)(fsc * arg12);
    u = 0;  // FAKE: defines u before the loop
    for (y = ys; y < ye; y += th, v += vstep) {
        siz = arg14;
        if (arg1 && u) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        u = ((s32)(fsc * arg11));
        for (x = xs; x < xe; x += tw) {
            uls = (x >> 5) - 1 > 0 ? (x >> 5) - 1 : 0;
            xf = (f32)x - 16.0;
            ua = (s16)(u + ustep);
            lrs = (x >> 5) + arg5 < ((xe >> 5) - 1) ? (x >> 5) + arg5 : ((xe >> 5) - 1);
            ult = ((y >> 5) - 1) > 0 ? ((y >> 5) - 1) : 0;
            lrt = ((y >> 5) + arg6) < ((ye >> 5) - 1) ? ((y >> 5) + arg6) : ((ye >> 5) - 1);
            if (siz == 8) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_8b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (siz == 0x10) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_16b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (siz == 0x20) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_32b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (siz == 4) {
                gDPLoadTextureTile_4b(dl++, arg1, arg2, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            }
            vb = (s16)(v + vstep);
            if (arg15 != 0) {
                if (x == xs && arg15 == 1) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            vc = vb;
            if (arg16 != NULL) {
                arg16(u, v, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, u, v, xf, (s16)(f32)((f32)y - 16.0), flag);
            if (arg15 != 0) {
                if (x + tw >= xe && arg15 == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                if (x) {}  // FAKE: dead test, steers spill-slot order / holes
                arg16((s16)(u + ustep), v, vtx);
            }
            xa = xf + (f32)tw;
            vtxSetPosTex((s16 *)vtx++, ua, v, xa, (s16)(f32)((f32)y - 16.0), flag);
            if (arg15 != 0) {
                if (x + tw >= xe && arg15 == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16(ua, vb, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, ua, vc, xa, (s16)((f32)(f32)((f32)y - 16.0) + (f32)th), flag);
            if (arg15 != 0) {
                if (x == xs && arg15 == 1) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16(u, vb, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, u, vc, xf, (s16)((f32)(f32)((f32)y - 16.0) + (f32)th), flag);
            u += ustep;
            gSPVertex(dl++, osVirtualToPhysical(vtx - 4), 4, 0);
            gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(dl++);
        }
    }
    if ((x >> 5) - 1) {}  // FAKE: dead test, steers spill-slot order / holes
    *arg0 = dl;
}
