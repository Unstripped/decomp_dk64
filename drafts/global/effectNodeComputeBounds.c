// effectNodeComputeBounds (src/global/63EC0.c): stage 3 (EffC2): 104 insns, 28 text lines, only frame 0xd0 vs 0xc8 + const regs s7/s8 + t7/t8 order differ. Frame reserve is NOT the declared-local count (i/idx/target all inline or named still 0xd0; replacing counter i with address-taken spA8 gives 0xc8, so the strength-reduced loop counter/IV costs 8). Narrow s16 i+idx gives 0xc8 but kills the IV (sll/sra, no pointer s0). Struct/u8-cast/M/P field forms, register kw, scopes, decl-order brute force (720), permuter 8min: no change.
void mapRectIntersect(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);
void mapScreenRectBuildFrustum(s32, s32, s32, s32, f32, f32, f32, u8, void *, void *, void *);

void effectNodeComputeBounds(EffectNode *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, void *arg5, void *arg6) {
    s32 s2 = 0;
    s32 s3 = 0;
    s32 s4 = 0;
    s32 s5 = 0;
    s32 spB4;
    s32 spB0;
    s32 spAC;
    s32 spA8;
    u8 sp70[0x38];
    s32 i;
    s32 idx;
    EffectSubNode *target = arg0->target;

    for (i = 0; i < target->unk67; i++) {
        idx = target->unk50[i];
        if (((u8 *)&D_807F6C18[idx])[0] == 1) {
            mapRectIntersect(s2, s3, s4, s5, *(s32 *)(((u8 *)&D_807F6C18[idx]) + 0x68), *(s32 *)(((u8 *)&D_807F6C18[idx]) + 0x6C), *(s32 *)(((u8 *)&D_807F6C18[idx]) + 0x70), *(s32 *)(((u8 *)&D_807F6C18[idx]) + 0x74), &spB4, &spB0, &spAC, &spA8);
            s2 = spB4;
            s3 = spB0;
            s4 = spAC;
            s5 = spA8;
        }
    }
    mapScreenRectBuildFrustum(s2, s3, s4, s5, arg1, arg2, arg3, arg4, arg5, arg6, sp70);
    arg0->unk40 = s2;
    arg0->unk42 = s3;
    arg0->unk44 = s4;
    arg0->unk46 = s5;
}
