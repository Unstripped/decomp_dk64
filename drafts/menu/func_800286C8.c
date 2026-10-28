// func_800286C8 (src/menu/3E10.c): stage 5 (frame+all insns match, parked-quality): only diff is a missing 'move v0,s0' before the gSPMatrix stores (target copies s0 to v0, sw 0(v0)/4(v0), a0=s0+8); tried g=arg1++/g=arg1/arr[0]/u32* forms, gSPMatrix(arg1++), named temp_s0 forms, permuter 120s: no change; pads padD4/CC/C8/BC reproduce the frame/layout
extern s32 D_807FBB60;
extern s32 *D_80033F28;
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);
void *func_80610FE8(s32);
void heapFreeDeferred(void *);
s32 func_806FC530(s32, s16, s16, s16, void *, s32);

s32 func_800286C8(void *arg0, Gfx *arg1) {
    s32 padD4;
    s32 spD0;
    s32 padCC;
    s32 padC8;
    f32 spC4;
    f32 spC0;
    s32 padBC;
    f32 sp7C[4][4];
    f32 sp3C[4][4];
    Mtx *sp38;
    void *temp_a0 = *(void **)((u8 *)arg0 + 0x174);

    D_807FBB60 |= 0x10;
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    spD0 = func_800317E8(temp_a0, 160.0f, 20.0f, &spC4, &spC0, 5, 1, 0.3f);
    sp38 = func_80610FE8(0x40);
    heapFreeDeferred(sp38);
    guScaleF(sp7C, 0.7f, 0.7f, 1.0f);
    guTranslateF(sp3C, spC4 * 4.0, spC0 * 4.0, 0.0f);
    guMtxCatF(sp7C, sp3C, sp7C);
    guMtxF2L(sp7C, sp38);
    arg1->words.w0 = 0xDA380003;
    arg1->words.w1 = (u32)sp38;
    return func_806FC530((s32)(arg1 + 1), 1, 0, 0, (void *)D_80033F28[spD0], 0x80);
}
