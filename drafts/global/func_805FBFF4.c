// func_805FBFF4 (src/global/0.c): Stage 6, text-identical to expected (instr stream + relocs except D_80761680+4 vs D_80761684) when compiled with a TU boundary at seg11DmaRead (0x805FB750): the only diff in 0.c as one TU is the .align 5 before the epilogue after the infinite loop (2 nops vs 6; epilogue 32-aligned relative to TU start, original TU starts at global+0x450). Needs hidden TU split [0x450, c, ...] in dk64.global.us.yaml. Needs s8 D_80744460, u8 D_8076A0B2 definitions.
extern s16 D_8074682C;
extern u8 D_807F059C;

void func_805FBFF4(s32 arg0) {
    u8 first;
    s32 sp38;

    first = 1;
    if (osTvType == 0) {
        D_807444BC = 1.25f;
    }
    func_805FBC5C();
    osViSetSpecialFeatures(0x42);
    func_805FBE04();
    D_8076A070[0] = D_80767CC0 - 2;
    osRecvMesg(&D_8076A110, (OSMesg *)&sp38, 1);
    while (1) {
        D_8074682C = 0xC8;
        while (D_80744460 != 0) {
        }
        if ((D_8076A0B1 & 1) && D_8076A0B2 == 0) {
            func_805FE7FC();
            if (D_807444F8 == 2) {
                D_807FBB60 |= 0x200;
                D_80744504 = 8;
            }
        }
        switch (D_807444EC) {
            case 6:
                transitionRunFrame(D_807444E4, D_807444E8);
                break;
            case 3:
                func_80024000();
                break;
            case 4:
                func_80024000();
                break;
            case 5:
                break;
            default:
                func_805FC2B0();
                break;
        }
        timerQueueUpdate();
        dmaDrainQueueAndFreeBuffer();
        func_80610268(0x4D2);
        if (D_807F059C != 0) {
            func_80610268(0x929);
        }
        frameTimingUpdate();
        if (D_807444EC == 0 || D_807444EC == 1 || D_807444EC == 7) {
            func_80658CCC();
            func_80700BF4();
        }
        func_80611730();
        if (D_80761680 != 0x12345678) {
            faultSetMessage(2, 0, 0, 0);
        }
        if (first != 0) {
            osSendMesg(D_807655E0, (OSMesg)0x309, 1);
            first = 0;
        }
        if ((D_8076A0B1 & 1) && gScreenFadeProgress == 31.0f) {
            D_8076A0B2--;
        }
        D_807444F0 = D_807444EC;
    }
}
