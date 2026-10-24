// func_8069E660 (src/global/A2F10.c): stage 6: 1 insn long (0xc8 vs 0xc4): arg2 spilled (sw a2,8(sp)+reload) instead of hoisted mtc1 a2,f14; operand order arg2-first tried
extern Actor *D_807FBB40;

s32 func_8069E660(Actor *arg0, f32 arg1, f32 arg2) {
    f32 dx;
    f32 dz;

    dx = arg0->unk80 - 8.0f;
    return dx <= D_807FBB40->unk80 &&
           D_807FBB40->unk80 < arg0->unk80 + arg1 &&
           arg2 > (arg0->unk7C - D_807FBB40->unk7C) *
                      (arg0->unk7C - D_807FBB40->unk7C) +
                  (arg0->unk84 - D_807FBB40->unk84) *
                      (arg0->unk84 - D_807FBB40->unk84) &&
           arg0->unk144 != 1;
}
#else
