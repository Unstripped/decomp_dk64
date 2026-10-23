// func_8068C5A8 (src/global/90D80.c): 814 insns; epilogue load-delay scheduling solved via if/else return structure; prologue sw a1, 0x1AC(sp) matched with u16 arg1; frame 0x1B0 due to inner-block var_v0 (drops to 0x1A8 when inlined, but multiply schedule shifts)
typedef f32 Act90A_MtxF[4][4];
extern u16 D_807FC79E;
extern Mtx D_2000180;
extern Mtx D_2000080;
void *func_80610FE8(s32);
void heapFreeDeferred(void *);
void func_80612CA0(Act90A_MtxF, f32);
s32 func_8068C12C(u16);
void func_80702464(Gfx **, s32, s32, u8, u8, s32, s32, f32, f32, f32, f32, f32, f32, s32, s32);
void func_80704444(Vtx *, s16, s16, s16, s16, s32);

#define Act90A_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_8068C5A8(Gfx *glist, u16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9, s32 arg10, f32 arg11) {
    s32 tex;
    Vtx *var_s0;
    Act90A_MtxF sp14C;
    Act90A_MtxF sp10C;
    Mtx *mtx1;
    s16 half_w;
    s16 half_h;
    f32 scaled_w;
    f32 scaled_h;
    s16 s1;
    s16 t1;
    s16 s2;
    s16 t2;

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

    tex = func_8068C12C(arg1);

    if (((((s32)var_s0 * (u8)arg4 * (u8)arg5) >> 3)) > 0x1000) {
        s32 var_v0;
        Act90A_WRITE_GFX(glist++, 0xDA380003, (u32)&D_2000180);
        Act90A_WRITE_GFX(glist++, 0xDA380007, (u32)&D_2000080);
        gDPPipeSync(glist++);

        var_v0 = ((s32)var_s0 < 0x20) ? 0x20 : 0x1E;

        func_80702464(&glist, tex, arg2, (u8)arg4, (u8)arg5, var_v0, var_v0, 0.0f, 0.0f,
                      (f32)(u8)arg4, (f32)(u8)arg5,
                      (f32)((s16)arg6 - ((u8)arg4 >> 1)), (f32)((s16)arg7 - ((u8)arg5 >> 1)),
                      1, (s32)var_s0);
    } else {
        mtx1 = func_80610FE8(sizeof(Mtx));
    heapFreeDeferred(mtx1);
    var_s0 = func_80610FE8(sizeof(Mtx));
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
    func_80612CA0(sp10C, (f32)(s16)arg10);
    guMtxCatF(sp14C, sp10C, sp14C);
    guTranslateF(sp10C, (f32)(s16)arg6, (f32)(s16)arg7, 0.0f);
    guMtxCatF(sp14C, sp10C, sp14C);
    guMtxF2L(sp14C, mtx1);

    Act90A_WRITE_GFX(glist++, 0xDA380003, (u32)mtx1);

    if (arg9 > 0.0f) {
        half_w = (u8)arg4 >> 1;
        half_h = (u8)arg5 >> 1;
        scaled_w = (f32)(u8)arg4 * arg11;
        scaled_h = (f32)(u8)arg5 * arg11;
        s1 = 0.0f - scaled_w;
        t1 = (f32)((u8)arg5 - 1) + scaled_h;

        func_80704444(var_s0++, -half_w, half_h, s1, t1, 6);
        s2 = (f32)((u8)arg4 - 1) + scaled_w;
        func_80704444(var_s0++, half_w, half_h, s2, t1, 6);
        t2 = 0.0f - scaled_h;
        func_80704444(var_s0++, half_w, -half_h, s2, t2, 6);
        func_80704444(var_s0++, -half_w, -half_h, s1, t2, 6);
    } else {
        half_w = (u8)arg4 >> 1;
        scaled_w = (f32)(u8)arg4 * arg11;
        scaled_h = (f32)(u8)arg5 * arg11;
        s1 = 0.0f - scaled_w;
        t1 = (f32)((u8)arg5 - 1) + scaled_h;

        func_80704444(var_s0++, -half_w, 0, s1, t1, 6);
        s2 = (f32)((u8)arg4 - 1) + scaled_w;
        func_80704444(var_s0++, half_w, 0, s2, t1, 6);
        t2 = 0.0f - scaled_h;
        func_80704444(var_s0++, half_w, -(u8)arg5, s2, t2, 6);
        func_80704444(var_s0++, -half_w, -(u8)arg5, s1, t2, 6);
    }

    Act90A_WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(var_s0 - 4));
    Act90A_WRITE_GFX(glist++, 0x06000204, 0x00000406);
        Act90A_WRITE_GFX(glist++, 0xE7000000, 0);
    }

    return glist;
}
