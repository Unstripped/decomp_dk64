// func_807024E0 (src/global/103AB0.c): QL1 stage 5 (frame 0x1d8 ok, 934 vs 933 insns). 3 deadsweep FAKEs (if (y) {} after u0, if (u && u) {} at y-loop top, if (u) {} after x loop) fix the registers: with sp offsets masked only ~115 diff lines remain (854 before), incl. y/v copies a1/a0 now like target. Remaining blocker = uopt temp-slot bit order (offsets): target slots high->low: a13c ustep vstep xs xe ye th tw u0 | hole184 | ushr(y,5)+x+tw 180 | ylo yhi siz | 5 holes (FP chain f32 y/cvt.d/sub.d/f32 tw) | xmax ymax | u16 vb vc16 xf16 yC | 3 holes | v16 yA, i.e. late (copy-prop) nodes follow call args bottom-up (call4 u16,vb,vc16,xf16,yC then call2 v16,yA) and xmax/ymax are EARLY bits (target's xmax is not a copy-prop'd xe use; here xe>>5 is replaced by xe's def expr => late bit). Ours: u16 xf16 early, v16/yA mid, xmax ymax x+tw vb vc16 yC late. Tried (no effect or worse): inline ylo/yhi/siz/xmax/ymax + f32 yd at y top (frame 472, slot score 76->56, regs break), xmax from literal (u32)(arg9*32.0f), named yd f64/f32 after siz, per-row vr copy (v lands in s8, 935 insns), s16/s32/inline toggles of ua/vb/vc/xa/xf (no code change), (f32)tw+xf operand flip (no effect), random/GA over inline/type/decl-swap/y-top order/fake toggles (floor ~139 unmasked). add.s f16,f20,f24 operand order (xa) and one extra lw v1 at the u store still differ. Prototype at 103AB0.c:877 must change and the later duplicate VtxColorView typedef must go (function sits above it).
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
    s32 x;
    u32 xs;
    u32 ys;
    s32 uls;
    s32 ult;
    s32 lrs;
    s32 lrt;
    f32 xf;
    s32 ua;
    s32 vb;
    s32 vc;
    s16 xa;
    u32 ustep;
    u32 xe;
    s32 pad1;
    u32 ye;
    u8 flag;
    s32 ylo;
    u32 yhi;
    s32 siz;
    u32 xmax;
    f32 fsc;
    u32 vstep;
    u32 ymax;
    s32 u0;
    u32 th;
    u32 tw;

    ustep = arg13 * arg5;
    vstep = arg13 * arg6;
    fsc = arg13;
    dl = *arg0;
    xs = (u32)(arg7 * 32.0f);
    ys = (u32)(arg8 * 32.0f);
    flag = 1;
    xe = (u32)(arg9 * 32.0f);
    ye = (u32)(arg10 * 32.0f);
    th = arg6 << 5;
    tw = arg5 << 5;
    u0 = (s32)(fsc * arg11);
    if (y) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
    for (y = ys; y < ye; y += th, v += vstep) {
        if (u && u) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16(u, v, vtx);
            }
            xf = (f32)x - 16.0;
            vtxSetPosTex((s16 *)vtx++, u, v, xf, (s16)(f32)((f32)y - 16.0), flag);
            if (arg15 != 0) {
                if (x + tw >= xe && arg15 == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            vb = (s16)(v + vstep);
            vc = vb;
            if (arg16 != NULL) {
                arg16((s16)(u + ustep), v, vtx);
            }
            ua = (s16)(u + ustep);
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
            gSPVertex(dl++, osVirtualToPhysical(vtx - 4), 4, 0);
            gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(dl++);
            u += ustep;
        }
    }
    if (u) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    *arg0 = dl;
}
