// func_80678824 (src/global/7CA80.c): stage 4: 30 insns, frame 0x18, ra saved at 0x14; uopt hoists base of D_807FBFE0 into v0 (12 insns) vs target 12 insns direct off at via %hi/%lo of D_807FBFE4/8
void func_8067889C(s32);
void func_806790F4(s32);
void func_80678B04(void);
void func_80679334(void);

void func_80678824(void) {
    D_807FBE09 = 1;
    D_807FBF10 = 0;
    D_807FBFE0[1] = NULL;
    D_807FBFE0[0] = NULL;
    D_807FBFE0[2] = NULL;
    D_807FBFE0[3] = NULL;
    func_8067889C(1);
    func_8067889C(2);
    func_806790F4(1);
    func_80678B04();
    D_807FBE09 = 0;
    actorFlushDespawnQueue();
    func_80679334();
}
