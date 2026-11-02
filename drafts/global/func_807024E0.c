// func_807024E0 (src/global/103AB0.c): L933 (leftovers6): stage 5, COUNT EXACT (933 insns = target, frame 0x1d8, same s-reg set), 98 full / 90 shape (stored 128 was 932 insns). Parked NON_MATCHING in the L933 copy. Remaining: (1) y-body entry order: target emits (f32)tw f24 cvt (bgez block) BEFORE xmax/vb/ymax and (f32)th after; ours th first; ypos1 conv last in target; (2) lbu s7 (arg15) hoisted to y-preheader in target, in x-preheader in ours; (3) u store in the x-guard beqz delay slot vs move a0,a1; (4) ~45 lines are spill-slot order/holes (first 9 slots match; target middle holes 5 after siz). KEY: the original has 4 fewer vregs than a 1:1 draft (here u0/yhi/xmax/ymax inlined as expressions: top spill slot 0xdc then matches) plus codeless spill candidates (dead tests). Found by SA over commuting statement order + dead tests scored on full+shape+slot-sequence(with holes)+count (.scratch/L933/anneal.py). Tried: arg15 hoist via u=arg15*0 (count breaks), named f32/s16 coordinate locals (shape 73 but regs cascade), loop shapes, callee ret types for arg16, statement permutations of y-body header (exhaustive).
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
    f32 fsc;
    u32 vstep;
    u32 th;
    s32 siz;
    s32 ylo;
    u32 tw;

    ustep = arg13 * arg5;
    vstep = arg13 * arg6;
    dl = *arg0;
    flag = 1;
    xs = (u32)(arg7 * 32.0f);
    xe = (u32)(arg9 * 32.0f);
    y = arg1;  // FAKE: defines y so the early dead read below is legal
    ys = (u32)(arg8 * 32.0f);
    ye = (u32)(arg10 * 32.0f);
    if (arg15) {}  // FAKE: dead test, steers spill-slot order / holes
    fsc = arg13;
    if ((ye >> 5)) {}  // FAKE: dead test, steers spill-slot order / holes
    th = arg6 << 5;
    tw = arg5 << 5;
    if (arg3 > 0x200) {
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        flag = 0;
    } else {
        gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    vtx = (VtxColorView *)heapAlloc(((((xe - xs) / tw) + 1) * (((ye - ys) / th) + 1)) << 6);
    heapFreeDeferred(vtx);
    if (th) {}  // FAKE: dead test, steers spill-slot order / holes
    gDPPipeSync(dl++);
    v = (s32)(fsc * arg12);
    u = 0;  // FAKE: defines u before the loop
    for (y = ys; y < ye; y += th, v += vstep) {
        siz = arg14;
        if (arg1 && u) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        ylo = (y >> 5) - 1;
        u = ((s32)(fsc * arg11));
        for (x = xs; x < xe; x += tw) {
            uls = (x >> 5) - 1 > 0 ? (x >> 5) - 1 : 0;
            lrs = (x >> 5) + arg5 < ((xe >> 5) - 1) ? (x >> 5) + arg5 : ((xe >> 5) - 1);
            ult = ylo > 0 ? ylo : 0;
            lrt = ((y >> 5) + arg6) < ((ye >> 5) - 1) ? ((y >> 5) + arg6) : ((ye >> 5) - 1);
            xf = (f32)x - 16.0;
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
                    if (arg4 && arg4) {}  // FAKE: dead test, steers spill-slot order / holes
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16(u, v, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, u, v, xf, (s16)(f32)((f32)y - 16.0), flag);
            vb = (s16)(v + vstep);
            if (arg15 != 0) {
                if (x + tw >= xe && arg15 == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    if (vb != 0) {}  // FAKE: dead test, steers spill-slot order / holes
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
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
            if ((y >> 5)) {}  // FAKE: dead test, steers spill-slot order / holes
            if (arg16 != NULL) {
                arg16(ua, vb, vtx);
            }
            vc = vb;
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
    *arg0 = dl;
}
