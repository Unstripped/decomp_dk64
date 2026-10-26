// func_806317D4 (src/global/35000.c): stage 5, parked NON_MATCHING: frame 0x50 OK, ang spill 0x24/sp20 0x20 OK, *arg1++ gives addiu s0,s0,60; remaining: same FP alloc as func_8063162C (cosB*cosC spilled in mine; expected f14=sinC f16=cosB f18=cosB*cosC), 1 insn longer
typedef struct R35000aVec {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
} R35000aVec;

typedef struct R35000aActor {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ R35000aVec *unk4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ f32 unkC[4][4];
    /* 0x4C */ u8 pad4C[0x14];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 pad64[0x18];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x54];
    /* 0xDC */ s16 unkDC;
    /* 0xDE */ s16 unkDE;
    /* 0xE0 */ u8 padE0[4];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ s16 unkE8;
} R35000aActor;

f32 func_80612790(s16);
f32 func_80612794(s16);

void func_806317D4(R35000aActor *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sinA;
    f32 cosA;
    f32 sinB;
    f32 cosB;
    f32 sinC;
    f32 cosC;
    f32 u;
    f32 pad0;
    f32 pad1;
    f32 pad2;

    sinA = func_80612790((s16)(s32)arg2);
    cosA = func_80612794((s16)(s32)arg2);
    sinB = func_80612790((s16)(s32)arg3);
    cosB = func_80612794((s16)(s32)arg3);
    sinC = func_80612790((s16)(s32)arg4);
    cosC = func_80612794((s16)(s32)arg4);
    u = arg0->unk4->unk34;
    *arg1++ = u * sinA * sinC + u * cosA * (cosB * cosC);
    *arg1++ = u * cosA * sinB;
    *arg1++ = u * cosA * (cosB * sinC) - u * sinA * cosC;
    *arg1++ = 0.0f;
    u = arg0->unk4->unk38;
    *arg1++ = u * sinA * (cosB * cosC) - u * cosA * sinC;
    *arg1++ = u * sinA * sinB;
    *arg1++ = u * cosA * cosC + u * sinA * (cosB * sinC);
    *arg1++ = 0.0f;
    u = arg0->unk4->unk3C;
    *arg1++ = u * sinB * cosC;
    *arg1++ = -u * cosB;
    *arg1++ = u * sinB * sinC;
    *arg1++ = 0.0f;
    *arg1++ = arg0->unk7C;
    *arg1++ = arg0->unk80;
    *arg1++ = arg0->unk84;
    *arg1 = 1.0f;
}
