// func_806FD8E0 (src/global/1025E0.c): Behavioral C reaches the exact target except the two adjacent a2/a3 sign-extension instructions are scheduled in reverse; stage 5.
extern s16 D_80744490;
extern s32 func_806FBD5C(s16, s32);
s32 func_806FC530();

void func_806FD8E0(s32 arg0, s16 arg1, s32 arg2, s16 arg3, u8 arg4) {
    func_806FC530(arg0, arg1, (s16)((D_80744490 - func_806FBD5C(arg1, arg2)) * 2), (s16)(arg3 * 4), arg2, arg4);
}
