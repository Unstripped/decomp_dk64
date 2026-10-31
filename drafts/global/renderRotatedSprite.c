// renderRotatedSprite (src/global/90D80.c): stage 5 (parked NON_MATCHING in 90D80.c): text identical to target incl. frame 0x1A8; only 2 spill-temp slots swapped (v0 CSE'd s16 v-coord expr 84 vs 88(sp), a3 u-coord expr 88 vs 84) in both vertex branches (16 diff lines). Levers found: u16/u8/u8/s16/s16 params + (u16) cast ANIM_TEX at callers; half_w/half_h s32 locals (frame word count); dead 'if (D_807FC79E && D_807FC79E) {}' at first-branch start (FAKE) fixes the 3 early slots (arg4/arg5/half_w) ordering. Tried: deadsweep (forms, ~10 syms, 2 rounds), 2 permuter runs (no gain), statement/decl order, casts, commutative swaps.
// prototype seen by callers must be: Gfx *renderRotatedSprite(Gfx *, u16, s32, s32, u8, u8, s16, s16, f32, f32, s32, f32); and ANIM_TEX in actorDrawAnimatedEffect = ((u16)(((D_8076A064 >> 1) % 12) + 0x83))
extern u16 D_807FC79E;
extern Mtx D_2000080;
extern Mtx D_2000180;
void func_80702464(Gfx **, s32, s32, u8, u8, s32, s32, f32, f32, f32, f32, f32, f32, s32, s32);
void vtxSetPosTex(Vtx *, s16, s16, s16, s16, s32);

Gfx *renderRotatedSprite(Gfx *glist, u16 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, s16 arg6, s16 arg7, f32 arg8, f32 arg9, s32 arg10, f32 arg11) {
    volatile s32 tex;
    s32 var_v0;
    Vtx *var_s0;
    s32 half_w;
    s32 half_h;
    f32 scaled_w;
    f32 scaled_h;
    RenderMtxF sp14C;
    RenderMtxF sp10C;
    Mtx *mtx1;

    arg3 &= ~0xC000;
    if (!(u16)arg1) {
        arg1 = D_807FC79E;
    }

    switch (arg3) {
    case 0:
        var_s0 = (Vtx *)4;
        break;
    case 1:
        var_s0 = (Vtx *)8;
        break;
    case 3:
        var_s0 = (Vtx *)32;
        break;
    default:
        var_s0 = (Vtx *)16;
        break;
    }

    tex = texCacheFindOrLoad(arg1);

    if (((((s32)var_s0 * (u8)arg4 * (u8)arg5) >> 3)) > 0x1000) {
        if (D_807FC79E && D_807FC79E) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        WRITE_GFX(glist++, 0xDA380003, (u32)&D_2000180);
        WRITE_GFX(glist++, 0xDA380007, (u32)&D_2000080);
        gDPPipeSync(glist++);
        var_v0 = ((s32)var_s0 < 0x20) ? 0x20 : 0x1E;
        func_80702464(&glist, tex, arg2, (u8)arg4, (u8)arg5, var_v0, var_v0, 0.0f, 0.0f,
                      (f32)(u32)(u8)arg4, (f32)(u32)(u8)arg5,
                      (f32)((s16)arg6 - ((u8)arg4 >> 1)), (f32)((s16)arg7 - ((u8)arg5 >> 1)),
                      1, (s32)var_s0);
    } else {
        mtx1 = heapAlloc(sizeof(Mtx));
        heapFreeDeferred(mtx1);
        var_s0 = heapAlloc(sizeof(Mtx));
        heapFreeDeferred(var_s0);

        switch (arg3) {
        case 0:
            gDPLoadTextureBlock_4b(glist++, (u8 *)(tex + 0x80000000), arg2, (u8)arg4, (u8)arg5, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            break;
        case 1:
            gDPLoadTextureBlock(glist++, (u8 *)(tex + 0x80000000), arg2, G_IM_SIZ_8b, (u8)arg4, (u8)arg5, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            break;
        case 2:
            gDPLoadTextureBlock(glist++, (u8 *)(tex + 0x80000000), arg2, G_IM_SIZ_16b, (u8)arg4, (u8)arg5, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            break;
        }

        guScaleF(sp14C, (arg8 > 0.0f) ? arg8 : -arg8, (arg9 > 0.0f) ? arg9 : -arg9, 0.0f);
        matrixMakeRotationZ(sp10C, (f32)(s16)arg10);
        guMtxCatF(sp14C, sp10C, sp14C);
        guTranslateF(sp10C, (f32)(s16)arg6, (f32)(s16)arg7, 0.0f);
        guMtxCatF(sp14C, sp10C, sp14C);
        guMtxF2L(sp14C, mtx1);

        WRITE_GFX(glist++, 0xDA380003, (u32)mtx1);

        if (arg9 > 0.0f) {
            half_w = (u8)arg4 >> 1;
            half_h = (u8)arg5 >> 1;
            scaled_w = (f32)(u32)(u8)arg4 * arg11;
            scaled_h = (f32)(u32)(u8)arg5 * arg11;

            vtxSetPosTex(var_s0++, -half_w, half_h, 0.0f - scaled_w, (f32)((u8)arg5 - 1) + scaled_h, 6);
            vtxSetPosTex(var_s0++, half_w, half_h, (f32)((u8)arg4 - 1) + scaled_w, (f32)((u8)arg5 - 1) + scaled_h, 6);
            vtxSetPosTex(var_s0++, half_w, -half_h, (f32)((u8)arg4 - 1) + scaled_w, 0.0f - scaled_h, 6);
            vtxSetPosTex(var_s0++, -half_w, -half_h, 0.0f - scaled_w, 0.0f - scaled_h, 6);
        } else {
            scaled_w = (f32)(u32)(u8)arg4 * arg11;
            scaled_h = (f32)(u32)(u8)arg5 * arg11;

            vtxSetPosTex(var_s0++, -((u8)arg4 >> 1), 0, 0.0f - scaled_w, (f32)((u8)arg5 - 1) + scaled_h, 6);
            vtxSetPosTex(var_s0++, (u8)arg4 >> 1, 0, (f32)((u8)arg4 - 1) + scaled_w, (f32)((u8)arg5 - 1) + scaled_h, 6);
            vtxSetPosTex(var_s0++, (u8)arg4 >> 1, -(u8)arg5, (f32)((u8)arg4 - 1) + scaled_w, 0.0f - scaled_h, 6);
            vtxSetPosTex(var_s0++, -((u8)arg4 >> 1), -(u8)arg5, 0.0f - scaled_w, 0.0f - scaled_h, 6);
        }

        WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(var_s0 - 4));
        WRITE_GFX(glist++, 0x06000204, 0x00000406);
        WRITE_GFX(glist++, 0xE7000000, 0);
    }

    return glist;
}
