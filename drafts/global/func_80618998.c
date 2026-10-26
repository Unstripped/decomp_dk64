// func_80618998 (src/global/19A00.c): stage 4: typed C reaches the target frame and reproduces conversion/call sequence. Remaining codegen is branch-likely/temporary-register scheduling in the eligibility and clamp condition; own double reloc is also local rodata.
typedef struct P19c3State { u8 pad0[0x38]; f32 unk38; } P19c3State;
typedef struct P19c3Actor { u8 pad0[4]; P19c3State *unk4; u8 pad8[0x50]; s32 unk58; u8 pad5C[4]; s32 unk60; u8 pad64[6]; u16 unk6A; } P19c3Actor;
typedef struct P19c3GameState { u8 pad0[0x104]; s32 unk104; } P19c3GameState;
void actorGetNodePosOrPosition(Actor *, s32 *, f32 *, f32 *);
void func_8061EF4C(s32, u8, s32, s32, f32, f32, f32, f32);
void func_80618998(Actor *arg0) {
    s32 sp4C; f32 sp48; f32 sp44; s16 sp42; s16 sp40; u8 sp3F; u8 sp3E; s32 temp_v0; u8 var_v1;
    actorGetNodePosOrPosition(arg0, &sp4C, &sp48, &sp44);
    func_80614F28(&sp3E); func_80614F28(&sp3F); func_80614F4C((u8 *)&sp42); func_80614F4C((u8 *)&sp40);
    sp3F = (u8)(u32)((f64)sp3F * ((f64)((P19c3Actor *)arg0)->unk4->unk38 / 0.15));
    temp_v0 = ((P19c3Actor *)arg0)->unk58;
    if ((temp_v0 == 0xCC) || ((((P19c3Actor *)arg0)->unk6A & 1) && ((((P19c3Actor *)arg0)->unk60 & 4) || (temp_v0 == 0xE4)) && (D_807444EC != 1))) {
        var_v1 = sp3F;
        if ((s32)sp3F >= 0x15) var_v1 = 0x14;
        func_8061EF4C(((P19c3GameState *)D_807FD580)->unk104, sp3E, var_v1 & 0xFFFF, sp4C, sp48, sp44, (f32)sp42, (f32)sp40);
    }
}
