// func_8060A60C (src/global/7130.c): matches alone; reverted on merge: caller func_80602C6C needs unprototyped decl (K&R s32 arg1 passed in a1), callee needs (s32, f32) prototype; cfe rejects both in one TU
void func_8060A60C(s32 arg0, f32 arg1) {
    D_80770578[arg0] = arg1;
    D_80770598[arg0] = 1;
}
