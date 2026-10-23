// func_806970CC (src/global/936B0.c): 3 insns: regalloc on unkEE+0x800 (t1, t2 vs v1); v1 matched with v1 = unkEE + 0x800; andi/subu/addu need t3/t6/t7
#define M93I_ACTOR70 ((M93I_Actor70 *)D_807FBB40)

void func_80696A6C(void);
s32 func_806725A0();
s16 func_80672A70(s16, s16);

void func_806970CC(void) {
    s16 temp_v0;

    if (!(M93I_ACTOR70->unk60 & 0x10)) {
        M93I_ACTOR70->unkFA = 0x2328;
    }
    func_80696A6C();
    if (!M93I_ACTOR70->unkFC) {
        return;
    }
    if (func_806725A0(D_807FBB40, M93I_ACTOR70->unkEE)) {
        return;
    }
    func_80608528(D_807FBB40, 0xF5, 0xFF, 0x7F, 0x1E);
    temp_v0 = func_80672A70(M93I_ACTOR70->unkF4, M93I_ACTOR70->unkF6);
    M93I_ACTOR70->unkEE = temp_v0 + (s16)(temp_v0 - ((M93I_ACTOR70->unkEE + 0x800) & 0xFFF));
}
