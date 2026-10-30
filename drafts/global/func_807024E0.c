// func_807024E0 (src/global/103AB0.c): Stage 5: code identical to target except y-row preheader order (45 opcode diffs, 931 vs 933 insns); frame 0x1D8 and homes y/u/v/xe/ye/flag (464/456/452/396/388/387) match. Blocker is uopt temp-slot layout: spilltemps (uoptreg2.c) gives PRE temps slots in candidate-bit order, reusing a slot when regions do not overlap (see ok-fine notes/ido-uopt-temp-slots). Target temps need: named locals 248 B (here 268), temps 128 B; call-arg values (u16,v16,xf16,yA,vb,vc,yC) created late by copy propagation (a per-row copy of v gives 18/22 target slots and the target's move a0,a1, but then v lands in s8); x+tw must reuse the ushr(y,5) slot. vc s32 (separate vb/vc temps) and siz s32 (siz temp after yhi) confirmed; statement order/decl order of loop-top vars has no effect. Draft carries the VtxColorView typedef and vtxSetColor/vtxSetPosTex prototypes (drop the duplicate typedef on integration). NOT paste-ready as-is: also replace the forward proto at 103AB0.c:877 with (Gfx **, s32, s32, u32, s32, u32, u32, f32 x6, u8, u8, u8, void (*)()), since drafts.py paste only replaces the pragma
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
    *arg0 = dl;
}
