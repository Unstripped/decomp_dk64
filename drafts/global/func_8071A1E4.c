// func_8071A1E4 (src/global/11BC10.c): stage 6: 150/152 insns match (2-line diff only: sra t4, t5, 0x8 vs sra t3; sb t4 vs sb t3); direct unk354-unk358 subtraction and void* ptr aligned all registers and stack homes
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Fx11BDMotion3;

void func_8071A1E4(TimedEffectActorView *arg0, s8 *arg1) {
    void *ptr;
    s32 pad0;
    s32 pad1;
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
        sp4A = arg0->unk35C >> 8;
        sp49 = (short)arg0->unk35C;
        ptr = func_80610FE8(0xC);
        arg0->unk384 = ptr;
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
    if ((*(s32 *)((u8 *)arg0 + 0x354) - *(s32 *)((u8 *)arg0 + 0x358)) < 0xA) {
        ((Fx11BDMotion3 *)arg0->unk384)->unk4 = (f32)((f64)((Fx11BDMotion3 *)arg0->unk384)->unk4 - 0.1);
        if ((s32)arg0->unk36D >= 0x16) {
            arg0->unk36D = arg0->unk36D - 0x14;
            return;
        }
        arg0->unk36D = 0;
    }
}
