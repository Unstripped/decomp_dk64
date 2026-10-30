// func_8071F1D0 (src/global/11BC10.c): stage 5 (parked NON_MATCHING in 11BC10.c): 74 insns exact length match, frame 0x28. Alloc block scheduling 100% matches target; remaining diff only regalloc: dir in v1 vs a0 with extra move a0,v1 before mtc1
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
        D_8075567C = -dir;
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
