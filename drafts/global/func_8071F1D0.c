// func_8071F1D0 (src/global/11BC10.c): R3a: stage 6, still 4 lines (negu before swc1 f6,4(v0) vs after; 'lw v1,900(s0)' lands after sb vs before). New: uopt ALWAYS sinks the post-if reload of arg0->unk384 to the END of the then block (after the global sb, which kills it), so as1 keeps sb<lw. Form that gets lw BEFORE sb with v1/a0/negu all right: 'var_v1 = arg0->unk384; if (var_v1 == NULL) {..temp->unk8 = (f32)dir; var_v1 = arg0->unk384; if (var_v1 && var_v1 && var_v1) {} /*FAKE*/ D_8075567C = -(dir&0xFF);}' + dead if(D_8075567C) in else + NO post-if assign (ucode: lw $3 before sb, no PRE reload) -- first 28 insns then match, but the join loses the spill-at-head (sw v1,36(sp) lands after jal, first reload is v1 not t8): 14 lines. Statement permutation grid (720) of A/U0/U4/U8/SB/FAKE and 3 pre/post/cond grids: none beat 4. Untried: a form that puts a spill store at the join head WITHOUT a post-if load (store of var_v1 into a non-promoted home?).
extern s8 D_8075567C;

void func_8071F1D0(TimedEffectActorView *arg0, s8 *arg1) {
    TimedMotionState *var_v1;
    TimedMotionState *temp;
    s32 dir;

    if (arg0->unk384 == NULL) {
        temp = heapAlloc(0xC);
        dir = D_8075567C;
        arg0->unk384 = temp;
        temp->unk0 = arg0->unk340;
        temp->unk4 = arg0->unk348;
        temp->unk8 = (f32)dir;
        if (arg0->unk384 && arg0->unk384 && arg0->unk384) {}  // FAKE: dead uses steer dir/var_v1 colouring
        D_8075567C = -(dir & 0xFF);
    }
    var_v1 = (TimedMotionState *)arg0->unk384;
    arg0->unk340 = (func_80612794(*(s16 *)((u8 *)arg0 + 0x35E)) * 14.0f) + var_v1->unk0;
    arg0->unk348 = (func_80612790(*(s16 *)((u8 *)arg0 + 0x35E)) * 14.0f) + var_v1->unk4;
    arg0->unk344 = arg0->unk344 + 0.5f;
    if (arg0->unk36D >= 5) {
        if (D_8075567C) {}  // FAKE: dead read steers dir into $a0
        arg0->unk36D = arg0->unk36D - 4;
    } else {
        *arg1 = 1;
    }
    arg0->unk35C = arg0->unk35C + (s32)((f64)var_v1->unk8 * 200.0);
}
