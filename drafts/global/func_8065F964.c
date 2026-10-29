// func_8065F964 (src/global/63EC0.c): stage 3: right shape (104 insns), frame 0xd0 vs 0xc8; ~28 diff lines: s6/s8 const swap (0x1c8 vs 1), lw/mflo t7/t8, idx kept named (v1) fixes lbu a1/lh v1. ugen reserves 8 more bytes iff entry ptr D_807F6C18[idx] is CSE'd across the if (cond using same expr + args); cond not using it => frame 0xc8
void mapRectIntersect(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);
void func_806545D4(s32, s32, s32, s32, f32, f32, f32, u8, void *, void *, void *);

void func_8065F964(EffectNode *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, void *arg5, void *arg6) {
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
    func_806545D4(s2, s3, s4, s5, arg1, arg2, arg3, arg4, arg5, arg6, sp70);
    arg0->unk40 = s2;
    arg0->unk42 = s3;
    arg0->unk44 = s4;
    arg0->unk46 = s5;
}
