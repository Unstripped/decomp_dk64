// gfxDrawTexturedTileGrid (src/global/103AB0.c): stage 5: R12_fable_5 (base f826d6ee) as1-XBB survey: park full=90 text=90 reloc=0 shape=83; candidate-limit variants give L0..L5=98 (one target-matching hoist from a source ranked 6-10 is lost), L10=90, L20=99 (a source ranked 11-20 adds a hoist the target lacks, so the original also ran at limit 10): no as1-steerable hunk; the diff is uopt spilltemp slot offsets as noted. No C changed, park kept. | Prior: stage 5: verified stage-5 count-exact parked body: full=90 text=90 reloc=0 shape=83 n=933 (expected 948 lines), frame 0x1d8 (472 bytes), exact saved-register set. The 90-line diff is entirely internal spilltemp slot displacements (offsets 0x64 vs 0xBC, 0xA8 vs 0xB4, 0x100 vs 0x148, etc.) caused by uopt's spilltemps pass sorting by ascending candidate bit and non-overlapping PRE regions before globalcolor. Pre-establishing early candidate chains moves relative offsets (-372 -> -284) but shrinks frame 472 -> 456, regressing score to 166. Exact park/GLOBAL_ASM form retained in .scratch/R11_gfxDrawTexturedTileGrid/103AB0.c; whole-file fdiff OK. | Prior: stage 5: 90 full / 90 text / 0 reloc / 83 shape; 948 normalized lines = 933 instructions, COUNT EXACT, frame 0x1d8, same s-reg set. Matcher11: unchanged best after 99 named-vs-expression experiments: individual alias elimination with original home padding or dropped slots (fsc/tw/th/siz/ustep/vstep/vc/vb/ua/xf/xa), all fsc/tw/th/siz alias combinations, spare-local caches for u0/ylo/ypos/xe/ye/x+tw, narrow alias types, selective inlining per use, fsc-frame padding, reversed xa sum operands. No improvement. Keeping vc/vb/xa declarations as unused pads while inlining aliases is code-identical; direct arg13 cast only in u0 expression (not v0) shrinks frame 472->456 and moves u0 spill 100->168; padding 16/20 restores frame but scores 121/118, not a match. Revisit-9 trace remains: 75/83 differences in Y-preheader temploc order; desired u0<x+tw<ylo<yhi<siz<xe-1<ye-1<(s16)u<vb<ypos1<(s16)v<ypos0; homes y464,u456,v452,xe396,ye388,flag387. Existing NON_MATCHING park retained unchanged; no merge. Regalloc5, base fbd144c9379503913f2cd699388bab5cf9d1299e: unchanged stage-5 best. Source proves spilltemps assigns by ascending final chain bit, first same-size slot whose PRE regions do not overlap, BEFORE globalcolor; spilltemplodstr only emits that slot and raises highestmdef. An exact early u0 chain moves candidate584 ->119 and ucode offset -372 ->-284 (the desired relative offset), but frame shrinks472->456 and score worsens166. Ordered integer guards, dead-store seeds, XOR guards, real caches/cap inlining and delayed y-position chains did not improve90. Complete derivation and evidence: .scratch/RegallocGroup/gfxDrawTexturedTileGrid.md.
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
