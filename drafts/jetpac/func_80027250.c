// func_80027250 (src/jetpac/3060.c): stage 5-6: frame 0x48 matches; target compiles 'A||B' as sltu t0,zero,v0; bnez t0; or v0,t0 / sltu t1; or v0,t1 with no extra stack, but an explicit '||' (or any s32 temp) adds an 8-byte slot (frame 0x50); this if(A) return 1; return B!=0 form gives beqz v0 + li v0,1 instead. Tried ||, != 0 forms, ternary, local r, permuter 150s.
u32 jetpacCheckAabbOverlap(f32, f32, f32, f32, f32, f32, f32, f32);
void func_80027108(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5);

s32 func_80027250(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp44, sp40, sp3C, sp38, sp34, sp30, sp2C, sp28;
    func_80027108(arg0, arg2, &sp44, &sp40, &sp3C, &sp38);
    func_80027108(arg4, arg6, &sp34, &sp30, &sp2C, &sp28);
    if (jetpacCheckAabbOverlap(sp44, arg1, sp40, arg3, sp34, arg5, sp30, arg7) != 0) {
        return 1;
    }
    return jetpacCheckAabbOverlap(sp3C, arg1, sp38, arg3, sp2C, arg5, sp28, arg7) != 0;
}
