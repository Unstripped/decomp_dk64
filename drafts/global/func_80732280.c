// func_80732280 (src/global/136820.c): stage 6: instruction stream identical except IDO pads 2 nop words before the unreachable epilogue after while(1)/for(;;) (expected has none, so original loop shape differs); dummy s32 x local needed for frame 0x40; i<2 loop on D_80744470[i] gives the non-hoisted pointer form
extern OSMesgQueue D_807FEF58;
extern s32 D_807FEF80;
extern u8 D_807563B4;
extern s32 D_80744470[];

void func_80732280(void *arg) {
    OSMesg msg;
    OSThread *thread;
    s32 i;
    s32 x;

    osSetEventMesg(12, &D_807FEF58, (OSMesg)0x10);
    do {
        do {
            osRecvMesg(&D_807FEF58, &msg, 1);
        } while (D_807563B4 == 0);
        thread = (OSThread *)__osGetCurrFaultedThread();
    } while (thread == 0);
    while (1) {
        for (i = 0; i < 2; i++) {
            osViBlack(0);
            D_807FEF80 = D_80744470[i];
            func_80731E68(thread);
            func_80731E68(thread);
        }
    }
}
