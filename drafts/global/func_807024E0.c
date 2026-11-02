// func_807024E0 (src/global/103AB0.c): L103 (leftovers5): stage 5, 128 full/107 masked lines (was 138 with ILLEGAL unassigned reads), all FAKEs now legal (y = arg1 + u = 0 pre-loop defs). Frame 0x1d8 ok. Remaining: temp slot area sits 16 bytes low vs target (arg13 home 0xcc vs 0xdc; target has 5 unreferenced slot words at 0x94-0xa4), so ~60 lines are offset-only; lbu s7(arg15) not hoisted to y-loop preheader; u0/guard-delay sw 456 placement; (f32)tw f24 cvt order in y-body entry. Tried: hill-climb legal dead tests (~200k compiles), u reset at y-loop end instead of top (natural, 160), inlining ylo/yhi/siz/xmax/ymax (identical code), pad counts (slot area invariant), y=ys early (fixes move v0,s1 only). Prototype at 103AB0.c:877 must become (Gfx **, s32, s32, u32, s32, u32, u32, f32 x6, u8, u8, u8, void (*)()) and the later duplicate VtxColorView typedef must go.
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
void func_807024E0(Gfx **arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4, u32 arg5, u32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, u8 arg13, u8 arg14, u8 arg15, void (*arg16)()) {
    Gfx *dl;
    s32 y;
    VtxColorView *vtx;
    s32 u;
    s32 v;
    s16 xa;
    f32 xf;
    s32 lrs;
    s32 vc;
    s32 x;
    u32 xs;
    s32 ult;
    u32 ustep;
    s32 ua;
    s32 uls;
    u32 ys;
    s32 lrt;
    s32 vb;
    u32 xe;
    s32 pad1;
    u32 ye;
    u8 flag;
    u32 yhi;
    u32 xmax;
    f32 fsc;
    s32 u0;
    u32 vstep;
    u32 th;
    u32 ymax;
    s32 siz;
    s32 ylo;
    u32 tw;

    vstep = arg13 * arg6;
    fsc = arg13;
    dl = *arg0;
    xs = (u32)(arg7 * 32.0f);
    ys = (u32)(arg8 * 32.0f);
    flag = 1;
    xe = (u32)(arg9 * 32.0f);
    th = arg6 << 5;
    ye = (u32)(arg10 * 32.0f);
    tw = arg5 << 5;
    y = arg1;  // FAKE: defines y so the early dead read below is legal
    u0 = (s32)(fsc * arg11);
    ustep = arg13 * arg5;
    if (y) {}  // FAKE: y live range from entry
    if (arg3 > 0x200) {
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        flag = 0;
    } else {
        gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    vtx = (VtxColorView *)heapAlloc(((((xe - xs) / tw) + 1) * (((ye - ys) / th) + 1)) << 6);
    heapFreeDeferred(vtx);
    gDPPipeSync(dl++);
    v = (s32)(fsc * arg12);
    u = 0;  // FAKE: defines u before the loop
    for (y = ys; y < ye; y += th, v += vstep) {
        if (arg1 && u) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        u = u0;
        ylo = (y >> 5) - 1;
        yhi = (y >> 5) + arg6;
        siz = arg14;
        xmax = (xe >> 5) - 1;
        ymax = (ye >> 5) - 1;
        for (x = xs; x < xe; x += tw) {
            uls = (x >> 5) - 1 > 0 ? (x >> 5) - 1 : 0;
            lrs = (x >> 5) + arg5 < xmax ? (x >> 5) + arg5 : xmax;
            ult = ylo > 0 ? ylo : 0;
            lrt = yhi < ymax ? yhi : ymax;
            if (siz == 8) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_8b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (siz == 0x10) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_16b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (siz == 0x20) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_32b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (siz == 4) {
                gDPLoadTextureTile_4b(dl++, arg1, arg2, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            }
            if (arg15 != 0) {
                if (x == xs && arg15 == 1) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    if (x == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
                if (arg15 && xs) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            if (xe == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (arg16 != NULL) {
                arg11 = arg11;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (ye == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                arg16(u, v, vtx);
            }
            xf = (f32)x - 16.0;
            xe = xe;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (tw == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            vtxSetPosTex((s16 *)vtx++, u, v, xf, (s16)(f32)((f32)y - 16.0), flag);
            if (arg15 != 0) {
                if (ymax && th) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (x + tw >= xe && arg15 == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            vb = (s16)(v + vstep);
            vc = vb;
            vtx = vtx;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (arg16 != NULL) {
                arg16((s16)(u + ustep), v, vtx);
            }
            ua = (s16)(u + ustep);
            if (arg14 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            xa = xf + (f32)tw;
            vtxSetPosTex((s16 *)vtx++, ua, v, xa, (s16)(f32)((f32)y - 16.0), flag);
            if (arg15 != 0) {
                if (x + tw >= xe && arg15 == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                    if (!flag) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
            }
            if (v != vstep) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (arg16 != NULL) {
                arg16(ua, vb, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, ua, vc, xa, (s16)((f32)(f32)((f32)y - 16.0) + (f32)th), flag);
            if (ylo != u) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
            gSPVertex(dl++, osVirtualToPhysical(vtx - 4), 4, 0);
            gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(dl++);
            u += ustep;
            if (vtx && vtx) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
    }
    arg12 = arg12;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    *arg0 = dl;
    if (xs != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
}
