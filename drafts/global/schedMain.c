// schedMain (src/global/131B0.c): stage 6: structure matches (shape diff = hw-reg consts as lui 0xa410 + jtbl/.rodata relocs); remaining = temp-register numbering shifted by one in first loop block (v0/t9 vs t8/t0), tried deadsweep+permuter; dead stmts tagged FAKE; needs bss D_807F04C8/0500/0510 u64, OSTimer D_807F0540 (retyped in copy)
extern u8 D_807563B4;
extern s8 D_80746830;
extern s16 D_8074682C;
extern s8 D_80746844;
extern s8 D_80746848;
extern u32 D_8076154C;
extern u32 D_80744470[];
extern void faultFontInit(s32, s32, s32);
extern void faultPrintf(const char *, ...);

void schedMain(void *arg0) {
    u32 msg;
    s32 i;
    s32 flag;
    s32 pad1;
    int new_var;
    s32 pad2;
    s32 pad3;
    s32 pad4;

    for (;;) {
        osRecvMesg(arg0, (OSMesg *)&msg, OS_MESG_BLOCK);
        if (D_807F0560 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (D_807563B4 != 0) {
            if (D_80746830 == 0) {
                if (D_8074682C == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                D_8074682C--;
            }
            if (D_8074682C <= 0) {
                D_807F0518[0]++;
                new_var = D_807F0518[0];
                osViSwapBuffer((void *)D_80744470[(new_var >> 5) & 1]);
                if (D_80746848 && D_80746848) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                osViBlack(0);
                D_807F0518[0]++;
                if (D_8074682C < -0x9F && D_8074682C >= -0x100) {
                    for (i = 0; i < 2; i++) {
                        faultFontInit(D_80744470[i & 1], 2, 2);
                        faultPrintf("CURRENT=%x\n", IO_READ(DPC_CURRENT_REG));
                        faultPrintf("START=%x\n", IO_READ(DPC_START_REG));
                        faultPrintf("END=%x\n", IO_READ(DPC_END_REG));
                        faultPrintf("DPSTAT=%x\n", IO_READ(DPC_STATUS_REG));
                        faultPrintf("SPSTAT=%x\n", IO_READ(SP_STATUS_REG));
                        faultPrintf("MAIN-PC=%x\n", D_8076154C);
                    }
                }
                if (D_8074682C < -0x12B) {
                    flag = 0;
                    if ((D_807F0518[0] & 0x1F) == 0) {
                        flag = 1;
                    }
                    if (flag) {
                        if (D_80746848 && D_80746848) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        if (D_80746848 == 0) {
                            flag = 0;
                            D_80746848 = 1;
                        }
                    }
                    func_8060FAE4(D_80746844, flag);
                    D_80746844 = 0;
                    D_8074682C = -0x12C;
                }
                osWritebackDCacheAll();
            }
        }
        switch (msg) {
        case 0x29A:
            D_807F0560++;
            if (D_807F0560 % 0x1E0 == 0) {
                D_807F04C8 = D_807F04D0;
                D_807F04D8 = D_807F04DC;
            }
            schedHandleRetrace(arg0);
            break;
        case 0x29E:
            func_8060F208(arg0);
            break;
        case 0x29B:
            schedHandleRSP(arg0);
            break;
        case 0x29C:
            schedHandleRDP(arg0);
            break;
        case 0x29F:
            if (osSendMesg(D_807F0540.mq, D_807F0540.msg, OS_MESG_BLOCK) == -1) {
            }
            break;
        case 0x2A0:
        case 0x3F2:
            break;
        default:
            func_8060F1D0(arg0, (TaskNode *)msg);
            break;
        }
    }
}
