// _n_loadOutputBuffer (src/global/141EF0.c): stage 7: all 198 instructions and statement shapes match; GPR allocation diverges from pointer phase calculation through the then branch
Acmd *_n_loadOutputBuffer(void *arg0, void *arg1, s32 arg2, s32 arg3, Acmd *arg4) {
    Acmd *sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    u8 *sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s16 sp2A;

    sp54 = arg4;
    sp48 = 0x2E0;
    sp34 = 0;
    sp2C = 0xB8;
    if (*(void **)((u8 *)arg1 + 0x24) != NULL) {
        sp30 = *(s32 *)((u8 *)arg1 + 4) - *(s32 *)arg1;
        sp38 = _doModFunc(arg1, sp2C);
        sp38 = sp38 / sp30;
        sp38 = (f32)(s32)(sp38 * 32768.0f);
        sp38 = sp38 / 32768.0f;
        sp3C = 1.0f - sp38;
        sp40 = (*(f32 *)((u8 *)*(void **)((u8 *)arg1 + 0x24) + 0x24)) + (sp3C * (f32)sp2C);
        sp4C = (s32)sp40;
        *(f32 *)((u8 *)*(void **)((u8 *)arg1 + 0x24) + 0x24) = sp40 - sp4C;
        sp44 = *(u8 **)((u8 *)arg0 + (arg2 * 4) + 0x28) + ((-(*(s32 *)((u8 *)arg1 + 4) - *(s32 *)((u8 *)arg1 + 0x18))) * 2);
        sp34 = ((s32)sp44 & 7) >> 1;
        sp54 = _n_loadBuffer(arg0, arg2, sp44 - (sp34 * 2), sp48, sp4C + sp34, sp54);
        sp50 = (s32)(sp3C * 32768.0f);
        sp2A = (s16)(arg3 >> 8);
        {
            Acmd *sp24;
            sp24 = sp54++;
            sp24->words.w0 = (osVirtualToPhysical(*(void **)((u8 *)*(void **)((u8 *)arg1 + 0x24) + (arg2 * 4) + 0x14)) & 0xFFFFFF) | 0x05000000;
            sp24->words.w1 = ((sp50 & 0xFFFF) << 14) | ((*(u32 *)((u8 *)*(void **)((u8 *)arg1 + 0x24) + 0x28) & 3) << 30) | (((sp48 + (sp34 * 2)) & 0xFFF) << 2) | (sp2A & 3);
        }
        *(u32 *)((u8 *)*(void **)((u8 *)arg1 + 0x24) + 0x28) = 0;
        *(s32 *)((u8 *)arg1 + 0x18) += sp4C - sp2C;
    } else {
        sp44 = *(u8 **)((u8 *)arg0 + (arg2 * 4) + 0x28) + (-*(s32 *)((u8 *)arg1 + 4) * 2);
        sp54 = _n_loadBuffer(arg0, arg2, sp44, arg3, 0xB8, sp54);
    }
    return sp54;
}
