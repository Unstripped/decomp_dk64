// func_8071F1D0 (src/global/11BC10.c): W2SchedA: TEXT-IDENTICAL (fdiff TEXT OK; deadsweep full=4 is only the 4 reloc lines .data vs @8075567C). KEY: function-local 'static s8 sd = 1;' replaces extern D_8075567C (only user of that .data byte): a non-aliased static's store does not kill the ilod arg0->unk384 so the PRE reload lands before the sb, no dir local, ZERO FAKEs. File-scope static / extern / u8 / s16 types do NOT work. Needs a data carve of D_8075567C (1 byte =0x01, 14C450.data) into this TU's .data (built .data 16 bytes vs 0).
void func_8071F1D0(TimedEffectActorView *arg0, s8 *arg1) {
    static s8 sd = 1;
    TimedMotionState *var_v1;
    TimedMotionState *temp;

    if (arg0->unk384 == NULL) {
        temp = heapAlloc(0xC);
        arg0->unk384 = temp;
        temp->unk0 = arg0->unk340;
        temp->unk4 = arg0->unk348;
        temp->unk8 = (f32)sd;
        sd = -sd;
    }
    var_v1 = (TimedMotionState *)arg0->unk384;
    arg0->unk340 = (func_80612794(*(s16 *)((u8 *)arg0 + 0x35E)) * 14.0f) + var_v1->unk0;
    arg0->unk348 = (func_80612790(*(s16 *)((u8 *)arg0 + 0x35E)) * 14.0f) + var_v1->unk4;
    arg0->unk344 = arg0->unk344 + 0.5f;
    if (arg0->unk36D >= 5) {
        arg0->unk36D = arg0->unk36D - 4;
    } else {
        *arg1 = 1;
    }
    arg0->unk35C = arg0->unk35C + (s32)((f64)var_v1->unk8 * 200.0);
}
