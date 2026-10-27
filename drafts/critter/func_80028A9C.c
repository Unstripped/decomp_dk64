// func_80028A9C (src/critter/4840.c): C1 stage 4: text matches except frame 0xE0 vs 0xD8: idx (u8 arg3) is CSE'd+spilled (sw t2,0x40(sp)) where target reloads lbu 0xE7(sp) from param home each use (not promoted); sp50 f32 def kept early by (f32)(u32)arg1[arg3+0x810]/12.0f reload; ang is unnamed repeated (s16)(sp50*2048.0f); matrix ptr expr repeated. Tried: K&R, &arg3 (too many reloads), named ang/volatile.
f32 func_80612794(s16);
Gfx *func_806FC530(Gfx *, s32, s16, s16, s32, s32);
extern u8 D_807444FC;

Gfx *func_80028A9C(Gfx *glistp, u8 *arg1, char *arg2, u8 arg3) {
    f32 sp98[4][4];
    f32 sp58[4][4];
    u8 sp57;
    f32 sp50;
    s16 sp4E;

    sp57 = 100;
    guMtxIdentF(sp98);
    if (arg1[arg3 + 0x810] != 0) {
        sp50 = (f32)(u32)arg1[arg3 + 0x810] / 12.0f;
        arg1[arg3 + 0x810]--;
        sp4E = (*(s16 **)(arg1 + 8))[arg3] - (*(s16 **)(arg1 + 4))[arg3];
        guTranslateF(sp98, -sp4E, -26.0f, 0.0f);
        guScaleF(sp58, func_80612794((s16)(sp50 * 2048.0f)) * 0.5 + 1.0, func_80612794((s16)(sp50 * 2048.0f)) * 0.8 + 1.0, 1.0f);
        guMtxCatF(sp98, sp58, sp98);
        guTranslateF(sp58, sp4E, 26.0f, 0.0f);
        guMtxCatF(sp98, sp58, sp98);
        sp57 = (u32)(func_80612794((s16)(sp50 * 2048.0f)) * 127.0f + 128.0f);
    }
    guTranslateF(sp58, (*(s16 **)(arg1 + 4))[arg3], *(s16 *)arg1, 0.0f);
    guMtxCatF(sp98, sp58, sp98);
    guMtxF2L(sp98, (Mtx *)(arg1 + arg3 * 0x80 + D_807444FC * 0x40 + 0x90));
    gSPMatrix(glistp++, arg1 + arg3 * 0x80 + D_807444FC * 0x40 + 0x90, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, sp57);
    return func_806FC530(glistp, 6, 0, 0, (s32)arg2, 0);
}
