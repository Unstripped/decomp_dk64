// func_807024E0 (src/global/103AB0.c): Stage 5 (L7): C compiles; frame 0x1D8 and all 4 tile-load cases + 4 corner blocks + loop shape match; remaining diff = row-prologue hoist order, stack-slot order of hoisted temps and a0/a1 + s4/s5 alloc. Needs: func_807024E0 proto (Gfx**,s32,s32,u32,s32,u32,u32,f32 x6,u8,u8,u8,void(*)()), struct R1F103AB0cTransformView tagged, func_80704444 declared/defined s32 (not void) for caller match; 14 dummy pad locals reproduce named-local frame
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
} L7Vtx;

struct R1F103AB0cTransformView;
void func_80704130(struct R1F103AB0cTransformView *, u8, u8, u8, u8, u8);
s32 func_80704444(s16 *, s16, s16, s16, s16, u8);

void func_807024E0(Gfx **arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4, u32 arg5, u32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, u8 arg13, u8 arg14, u8 arg15, void (*arg16)()) {
    Gfx *dl;
    s32 y;
    L7Vtx *vtx;
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
    s16 ub;
    s32 vb;
    s16 vc;
    s16 xa;
    u32 ustep;
    u32 xe;
    s32 pad1;
    u32 ye;
    u8 flag;
    f32 fsc;
    u32 vstep;
    s32 padE;
    s32 padF;
    s32 padG;
    s32 padH;
    s32 padI;

    ustep = arg13 * arg5;
    vstep = arg13 * arg6;
    fsc = arg13;
    dl = *arg0;
    xs = (u32)(arg7 * 32.0f);
    ys = (u32)(arg8 * 32.0f);
    flag = 1;
    xe = (u32)(arg9 * 32.0f);
    ye = (u32)(arg10 * 32.0f);
    if (arg3 > 0x200) {
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        flag = 0;
    } else {
        gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    vtx = (L7Vtx *)func_80610FE8(((((xe - xs) / (arg5 << 5)) + 1) * (((ye - ys) / (arg6 << 5)) + 1)) << 6);
    heapFreeDeferred(vtx);
    gDPPipeSync(dl++);
    v = (s32)(fsc * arg12);
    for (y = ys; y < ye; y += arg6 << 5, v += vstep) {
        u = (s32)(fsc * arg11);
        for (x = xs; x < xe; x += arg5 << 5) {
            uls = (x >> 5) - 1 > 0 ? (x >> 5) - 1 : 0;
            lrs = (x >> 5) + arg5 < (xe >> 5) - 1 ? (x >> 5) + arg5 : (xe >> 5) - 1;
            ult = (y >> 5) - 1 > 0 ? (y >> 5) - 1 : 0;
            lrt = (y >> 5) + arg6 < (ye >> 5) - 1 ? (y >> 5) + arg6 : (ye >> 5) - 1;
            if (arg14 == 8) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_8b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (arg14 == 0x10) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_16b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (arg14 == 0x20) {
                gDPLoadTextureTile(dl++, arg1, arg2, G_IM_SIZ_32b, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (arg14 == 4) {
                gDPLoadTextureTile_4b(dl++, arg1, arg2, arg3, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            }
            if (arg15 != 0) {
                if (x == xs && arg15 == 1) {
                    func_80704130((struct R1F103AB0cTransformView *)vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    func_80704130((struct R1F103AB0cTransformView *)vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16(u, v, vtx);
            }
            xf = (f32)x - 16.0;
            func_80704444((s16 *)vtx++, u, v, xf, (s16)(f32)((f32)y - 16.0), flag);
            if (arg15 != 0) {
                if (x + (arg5 << 5) >= xe && arg15 == 2) {
                    func_80704130((struct R1F103AB0cTransformView *)vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    func_80704130((struct R1F103AB0cTransformView *)vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            vb = (s16)(v + vstep);
            vc = vb;
            if (arg16 != NULL) {
                arg16((s16)(u + ustep), v, vtx);
            }
            ua = (s16)(u + ustep);
            xa = xf + (f32)(arg5 << 5);
            func_80704444((s16 *)vtx++, ua, v, xa, (s16)(f32)((f32)y - 16.0), flag);
            if (arg15 != 0) {
                if (x + (arg5 << 5) >= xe && arg15 == 2) {
                    func_80704130((struct R1F103AB0cTransformView *)vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    func_80704130((struct R1F103AB0cTransformView *)vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16(ua, vb, vtx);
            }
            func_80704444((s16 *)vtx++, ua, vc, xa, (s16)((f32)(f32)((f32)y - 16.0) + (f32)(arg6 << 5)), flag);
            if (arg15 != 0) {
                if (x == xs && arg15 == 1) {
                    func_80704130((struct R1F103AB0cTransformView *)vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    func_80704130((struct R1F103AB0cTransformView *)vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (arg16 != NULL) {
                arg16(u, vb, vtx);
            }
            func_80704444((s16 *)vtx++, u, vc, xf, (s16)((f32)(f32)((f32)y - 16.0) + (f32)(arg6 << 5)), flag);
            gSPVertex(dl++, osVirtualToPhysical(vtx - 4), 4, 0);
            gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(dl++);
            u += ustep;
        }
    }
    *arg0 = dl;
}
