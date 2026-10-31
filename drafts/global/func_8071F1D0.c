// func_8071F1D0 (src/global/11BC10.c): stage 6: 74 insns, frame 0x28; 6-line regalloc diff: first lui in v1 (lb a0,X(v1)) vs a0, negu after lb scheduled before swc1 f6, lw v1,900 after sb; uses -(dir & 0xFFu) + two dead D_8075567C reads (FAKE) to get dir into a0
extern s8 D_8075567C;

void func_8071F1D0(TimedEffectActorView *arg0, s8 *arg1) {
    TimedMotionState *var_v1;
    TimedMotionState *temp;
    s32 dir;

    if (arg0->unk384 == NULL) {
        temp = heapAlloc(0xC);
        dir = D_8075567C;
        if (D_8075567C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        arg0->unk384 = temp;
        temp->unk0 = arg0->unk340;
        temp->unk4 = arg0->unk348;
        temp->unk8 = (f32)dir;
        D_8075567C = -(dir & 0xFFu);
    }
    var_v1 = (TimedMotionState *)arg0->unk384;
    arg0->unk340 = (func_80612794(*(s16 *)((u8 *)arg0 + 0x35E)) * 14.0f) + var_v1->unk0;
    arg0->unk348 = (func_80612790(*(s16 *)((u8 *)arg0 + 0x35E)) * 14.0f) + var_v1->unk4;
    if (D_8075567C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    arg0->unk344 = arg0->unk344 + 0.5f;
    if (arg0->unk36D >= 5) {
        arg0->unk36D = arg0->unk36D - 4;
    } else {
        *arg1 = 1;
    }
    arg0->unk35C = arg0->unk35C + (s32)((f64)var_v1->unk8 * 200.0);
}
