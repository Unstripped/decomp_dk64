// func_8071A1E4 (src/global/11BC10.c): stage 6: frame 0xD8, all stack offsets and the instruction sequence match (s8 stores land in the malloc delay slot); remaining diff is t-register allocation only (unk35C CSE temp v0 vs t5 and cascading renames); parked under NON_MATCHING, callee-saved set s0 and frame match
#ifdef NON_MATCHING
void func_8071A1E4(TimedEffectActorView *arg0, s8 *arg1) {
    s32 Fx11BDt5;
    s32 Fx11BDa;
    s32 Fx11BDb;
    f32 sp8C[4][4];
    f32 sp4C[4][4];
    s8 sp4B;
    s8 sp4A;
    s8 sp49;
    s8 sp48;
    s16 sp46;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    if (arg0->unk384 == NULL) {
        sp48 = (u32)-(s32)(func_806119A0() / 10000U) % 30U;
        sp46 = (u32)(func_806119A0() / 10000U) % 180U;
        guRotateF(sp8C, (f32)sp48, 0.0f, 1.0f, 0.0f);
        sp4B = arg0->unk35C >> 0x10;
        Fx11BDt5 = arg0->unk35C;
        sp4A = Fx11BDt5 >> 8;
        sp49 = Fx11BDt5;
        arg0->unk384 = func_80610FE8(0xC);
        guAlignF(sp4C, (f32)sp46, (f32)sp4B, (f32)sp4A, (f32)sp49);
        guMtxCatF(sp8C, sp4C, sp8C);
        guMtxXFMF(sp8C, 0.0f, 0.0f, -2.0f, &sp40, &sp3C, &sp38);
        ((Fx11BDMotion3 *)arg0->unk384)->unk0 = (f32)((f64)sp40 * 0.5);
        if (sp3C < 0.0f) {
            ((Fx11BDMotion3 *)arg0->unk384)->unk4 = (f32)((f64)-sp3C * 0.5);
        } else {
            ((Fx11BDMotion3 *)arg0->unk384)->unk4 = (f32)((f64)sp3C * 0.5);
        }
        ((Fx11BDMotion3 *)arg0->unk384)->unk8 = (f32)((f64)sp38 * 0.5);
    }
    arg0->unk340 += ((Fx11BDMotion3 *)arg0->unk384)->unk0;
    arg0->unk344 += ((Fx11BDMotion3 *)arg0->unk384)->unk4;
    arg0->unk348 += ((Fx11BDMotion3 *)arg0->unk384)->unk8;
    Fx11BDa = *((s32 *)((u8 *)arg0 + 0x354));
    Fx11BDb = *((s32 *)((u8 *)arg0 + 0x358));
    if ((Fx11BDa - Fx11BDb) < 0xA) {
        ((Fx11BDMotion3 *)arg0->unk384)->unk4 = (f32)((f64)((Fx11BDMotion3 *)arg0->unk384)->unk4 - 0.1);
        if ((s32)arg0->unk36D >= 0x16) {
            arg0->unk36D = arg0->unk36D - 0x14;
            return;
        }
        arg0->unk36D = 0;
    }
}
