// func_8066CEE4 (src/global/70FD0.c): Unmatched: starter m2c draft (vertex transform, degenerate check via func_8066D250)
s32 func_8066D250(s16 *);                           /* extern */
s8 func_8066D2F4(s16 *);                            /* extern */
s16 func_8066D4DC(s16 *, u8 *);                     /* extern */
s32 func_8066DD34(void *);                          /* extern */

s32 func_8066CEE4(void *arg0, void *arg1, f32 (*arg2)[4]) {
    u8 sp6C;
    s16 sp6A;
    s16 sp68;
    s16 sp66;
    s16 sp64;
    s16 sp62;
    s16 sp60;
    s16 sp5E;
    s16 sp5C;
    s16 sp5A;
    s16 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    guMtxXFMF(arg2, (f32) arg0->unk0, (f32) arg0->unk2, (f32) arg0->unk4, &sp54, &sp50, &sp4C);
    sp58 = (s16) (s32) sp54;
    sp5A = (s16) (s32) sp50;
    sp5C = (s16) (s32) sp4C;
    guMtxXFMF(arg2, (f32) arg0->unk6, (f32) arg0->unk8, (f32) arg0->unkA, &sp48, &sp44, &sp40);
    sp5E = (s16) (s32) sp48;
    sp60 = (s16) (s32) sp44;
    sp62 = (s16) (s32) sp40;
    guMtxXFMF(arg2, (f32) arg0->unkC, (f32) arg0->unkE, (f32) arg0->unk10, &sp3C, &sp38, &sp34);
    sp64 = (s16) (s32) sp3C;
    sp66 = (s16) (s32) sp38;
    sp68 = (s16) (s32) sp34;
    if (func_8066D250(&sp58) != 0) {
        return 0;
    }
    if (arg0->unk12 & 1) {
        arg1->unk4D = 1;
    } else {
        arg1->unk4D = 0;
    }
    if (arg0->unk12 & 2) {
        arg1->unk4F = (u8) arg0->unk13;
    } else {
        arg1->unk4F = 0U;
    }
    if (arg0->unk12 & 4) {
        arg1->unk51 = 1;
    } else {
        arg1->unk51 = 0;
    }
    if (arg0->unk12 & 8) {
        arg1->unk50 = 5;
    } else {
        arg1->unk50 = 0xFF;
    }
    arg1->unk4E = (s8) arg0->unk14;
    arg1->unk24 = (s32) (sp54 * 8.0f);
    arg1->unk28 = (s32) (sp50 * 8.0f);
    arg1->unk2C = (s32) (sp4C * 8.0f);
    arg1->unk30 = (s32) (sp48 * 8.0f);
    arg1->unk34 = (s32) (sp44 * 8.0f);
    arg1->unk38 = (s32) (sp40 * 8.0f);
    arg1->unk3C = (s32) (sp3C * 8.0f);
    arg1->unk40 = (s32) (sp38 * 8.0f);
    arg1->unk44 = (s32) (sp34 * 8.0f);
    sp6A = func_8066D4DC(&sp58, &sp6C);
    arg1->unk4B = func_8066D2F4(&sp58);
    arg1->unk48 = sp6A;
    arg1->unk4C = sp6C;
    return func_8066DD34(arg1);
}
