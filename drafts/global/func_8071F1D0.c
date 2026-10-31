// func_8071F1D0 (src/global/11BC10.c): R2Aud1 stage 6: 74 insns frame/regs/lui a0 all match; 4-line schedule diff only: negu before swc1 f6,4(v0) vs after, and 'lw v1,900(s0)' after sb vs before. Uses FAKE dead if(arg0->unk384 x3) before the neg store + dead if(D_8075567C) in else (block-split FAKEs split as1 scheduling; without them lui lands v1). Tried: 400+ type/neg/dead-if position grids, hc 20k variants, named-vs-expr arg0->unk384 forms.
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
