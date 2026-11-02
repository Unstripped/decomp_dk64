// cameraStepAspectScale (src/global/2F550.c): W2SchedB: TEXT-IDENTICAL (text=0), reloc only: function-local 'static f32 sc = 1.0f' for D_80747CD0 (sole user) makes uopt promote it, store after retv; needs .data carve of D_80747CD0 by orchestrator (R_MIPS HI/LO16 .data vs D_80747CD0)
extern u8 D_807444F0;
extern u8 D_807444EC;
extern s8 D_807444C0;
extern s32 gCurrentMap;

f32 cameraStepAspectScale(void) {
    static f32 sc = 1.0f; // D_80747CD0 (only user: this function; needs a .data carve)
    f32 target;
    f32 step;
    s32 flag;

    target = 1.0f;
    if (D_807444F0 != 1 && D_807444EC == 1) {
        step = 999.0f;
    } else {
        step = 0.02f;
    }
    flag = D_807444EC == 1;
    if (flag) {
        flag = gCurrentMap != 0x50;
    }
    if (D_807444C0 != 0 && !flag) {
        target = target * 1.2;
    }
    if (sc < target) {
        sc += step;
        if (target < sc) {
            sc = target;
        }
    } else {
        sc -= step;
        if (sc < target) {
            sc = target;
        }
    }
    return sc;
}
