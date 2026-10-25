// func_806F2A40 (src/global/F56F0.c): Stage 3: all blocks and behavior recovered. Current draft misses target 8-byte frame/s0 output-pointer cache and reg allocation; target has shared 0.7 double load and differs in temp order.
typedef struct F5CPlayerState {
    u8 pad0[0x21E];
    u16 unk21E;
    u8 pad220[0x38];
    f32 unk258;
    f32 unk25C;
} F5CPlayerState;
typedef struct F5CPlayerActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x128 - 0x64];
    s16 unk128;
    u8 pad12A[0x154 - 0x12A];
    u8 unk154;
} F5CPlayerActor;
typedef struct F5COutput {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
} F5COutput;
#define F5C_PS ((F5CPlayerState *)D_807FD580)
void func_806F2A40(F5CPlayerActor *arg0, F5COutput *arg1, s32 *arg2) {
    F5CPlayerActor *actor;
    F5COutput *out;
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_fv1;
    u16 temp_v1;
    actor = arg0;
    out = arg1;
    temp_v1 = F5C_PS->unk21E;
    temp_fv0 = (f32)temp_v1 * 0.03333333507f;
    if ((f64)temp_fv0 < 1e-05) temp_fv0 = 0.000009999999747f;
    if ((actor->unk154 == 0x34) || (actor->unk154 == 0x84)) {
        if ((f64)F5C_PS->unk25C > 0.01) {
            F5C_PS->unk258 = (f32)((f64)F5C_PS->unk258 * 0.7);
            F5C_PS->unk25C = (f32)((f64)F5C_PS->unk25C * 0.7);
        } else {
            actor->unk60 &= ~0x8000;
            if (F5C_PS->unk21E != 0) F5C_PS->unk21E -= 1;
            actor->unk128 = (s16)(255.0f * temp_fv0);
        }
        var_fv1 = F5C_PS->unk258;
        var_fa0 = F5C_PS->unk25C;
    } else {
        var_fa0 = temp_fv0;
        var_fv1 = temp_fv0;
        if (temp_v1 < 0x1E) {
            actor->unk60 |= 0x8000;
            temp_v1 = 0x1E - temp_v1;
            if (temp_v1 >= 3) temp_v1 = 2;
            F5C_PS->unk21E += temp_v1;
            F5C_PS->unk258 = 1.0f;
            F5C_PS->unk25C = F5C_PS->unk258;
        }
    }
    out[*arg2].unk0 = 0;
    out[*arg2].unk1 = 0xFF;
    out[*arg2].unk4 = var_fv1;
    out[*arg2].unk8 = var_fa0;
    out[*arg2].unkC = var_fv1;
    *arg2 += 1;
}
