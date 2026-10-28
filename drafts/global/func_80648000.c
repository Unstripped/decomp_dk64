// func_80648000 (src/global/478F0.c): stage 5: text size+frame+slots match (needs void *dm=&cs; to force cs in home slot; pad[20]); remaining diff: FP const webs after 2nd randomNonNegative (100.0 const shared between div and mul in mine, rematerialized in target) + f-reg numbering
typedef struct CsB6State80648000 {
    /* 0x00 */ f32 (*unk0)[4];
    /* 0x04 */ u8 pad4[0x96];
    /* 0x9A */ u8 unk9A;
} CsB6State80648000;

void func_80648000(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 pad[20];
    void *dm = &cs;
    f32 rx;
    f32 rz;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 t;
    f32 (*m)[4];
#define S ((CsB6State80648000 *)cs)

    if (S->unk0 == NULL && (S->unk9A & 1)) {
        m = func_80610FE8(0x44);
        S->unk0 = m;
        modelSlotGetNodePos(csId, 1, 1, &sp40, &m[4][0], &sp38);
        m[4][0] -= 10.0;
        guRotateF(m, D_807F622C, 0.0f, 1.0f, 0.0f);
    }
    if ((S->unk9A & 1) && (func_806119A0() / 10000U) % 20U == 0) {
        m = S->unk0;
        t = (randomNonNegative() >> 15) % 100;
        rx = t / 100.0;
        t = (randomNonNegative() >> 15) % 100;
        rz = t / 100.0;
        guMtxXFMF(m, rx * 100.0 + -50.0, 0.0f, rz * 150.0 + -75.0, &sp40, &sp3C, &sp38);
        sp40 = sp40 * D_807F6234 + D_807F621C;
        sp38 = sp38 * D_807F6234 + D_807F6224;
        func_807149B8(1);
        func_80714950(2);
        func_807149FC(-1);
        func_8071498C(func_80718BF4);
        func_80714CC0(D_8071FC40, 0.0f, sp40, m[4][0], sp38);
    }
#undef S
}
