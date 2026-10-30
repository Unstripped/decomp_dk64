// schedMain (src/global/131B0.c): stage 6: ONLY diff: cond2 of the range check emits 'bnez at; move s0,zero' (as1 pulls i=0 into the delay slot) vs expected 'bnezl at; slti at,v0,-299; move s0,zero'; cnt local (pad2 reused: cnt = D_807F0560 + 1; D_807F0560 = cnt) fixed the v0 candidate + temp numbering; 4 dead stmts left; as1 refuses the pull only if s0 live at target (real read of i after loop reproduces bnezl in a toy, but expected has none)
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
    u32 cnt;
    s32 pad3;
    s32 pad4;

    for (;;) {
        osRecvMesg(arg0, (OSMesg *)&msg, OS_MESG_BLOCK);
        if (D_807F0560 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (D_807563B4 != 0) {
            if (D_80746830 == 0) {
                D_8074682C--;
            }
            if (D_80744470 && D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (D_807F0518 && D_807F0518) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
                        if (D_80746848 == 0) {
                            flag = 0;
                            D_80746848 = 1;
                        }
                    }
                    schedDlDebugDump(D_80746844, flag);
                    D_80746844 = 0;
                    D_8074682C = -0x12C;
                }
                osWritebackDCacheAll();
            }
        }
        switch (msg) {
        case 0x29A:
            cnt = D_807F0560 + 1;
            D_807F0560 = cnt;
            if (cnt % 0x1E0 == 0) {
                D_807F04C8 = D_807F04D0;
                D_807F04D8 = D_807F04DC;
            }
            schedHandleRetrace(arg0);
            break;
        case 0x29E:
            schedStartAudioOrYield(arg0);
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
