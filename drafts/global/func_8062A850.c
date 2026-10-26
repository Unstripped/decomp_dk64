// func_8062A850 (src/global/2F550.c): stage 5: same size/frame as target; only diff is D_80747CD0 addressing (target: lui at before the load and a second lui at before the store in jr delay slot; ours CSEs the address into v0/addiu and sinks stores into bc1fl delay slots). 42 diff lines; 2-iteration permuter run (best score 805 of 1401 start) gave nothing readable.
extern u8 D_807444F0;
extern u8 D_807444EC;
extern s8 D_807444C0;
extern s32 D_8076A0A8;
extern f32 D_80747CD0;

f32 func_8062A850(void) {
    f32 target;
    f32 step;
    f32 cur;
    s32 flag;

    target = 1.0f;
    if (D_807444F0 != 1 && D_807444EC == 1) {
        step = 999.0f;
    } else {
        step = 0.02f;
    }
    flag = D_807444EC == 1;
    if (flag) {
        flag = D_8076A0A8 != 0x50;
    }
    if (D_807444C0 != 0 && !flag) {
        target = target * 1.2;
    }
    cur = D_80747CD0;
    if (cur < target) {
        cur += step;
        if (target < cur) {
            cur = target;
        }
    } else {
        cur -= step;
        if (cur < target) {
            cur = target;
        }
    }
    D_80747CD0 = cur;
    return cur;
}
