// func_806C9F74 (src/global/CEAE0.c): G02 stage 6: C is equivalent; diff = second call (func_806E9964) recomputes xori/sltu a1 (+8 bytes) instead of reusing the a1 hoisted above the 0x200 test; tried local temp/u8 local/spare K&R a1/& 0xFF/cast/ternary/!(==)/s16 local, return after first call, K&R func_806E9964; permuter 150s no clean result
extern s16 D_80750B54[][4];
void func_806EAB44(Actor *, u8);
void func_806E9964(Struct807FD580 *, s32);

void func_806C9F74(Actor *arg0) {
    u8 temp_v0 = arg0->unk154;
    s16 flags = D_80750B54[temp_v0][0];

    if (flags & 0x200) {
        func_806EAB44(arg0, temp_v0 != 2);
    } else if (flags & 0x100) {
        func_806E9964(D_807FD580, temp_v0 != 2);
    }
}
