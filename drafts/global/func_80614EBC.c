// func_80614EBC (src/global/19A00.c): stage 4; closest diff 20 (permuter): base-table register allocation remains. Attempts: m2c starter; typed state fields; pointer-table cast forms; local script temporary; 600-second permuter search.
typedef int s32;
typedef unsigned char u8;
typedef short s16;
typedef float f32;
typedef struct Actor { void *unk4; } Actor;
typedef struct Perm2EBCState { u8 pad0[0x64]; s16 unk64; u8 pad66[2]; u8 *unk68; u8 *unk6C; s32 unk70; u8 pad74[4]; s32 unk78; s32 unk7C; f32 unk80; u8 pad84[4]; s32 unk88; } Perm2EBCState;
extern u8 *D_807F5AF0;
extern u8 *D_807FBB50;
extern s32 D_807F5AF4;
void func_80614EBC(Actor *arg0, s32 arg1) {
    Perm2EBCState *state;
    u8 *script;
    state = (Perm2EBCState *)arg0->unk4;
    state->unk70 = 0; state->unk78 = 0; state->unk7C = 0; state->unk88 = 0; state->unk80 = 0.0f;
    if (arg1 == 0) { state->unk68 = NULL; D_807F5AF0 = NULL; D_807F5AF4 = 0; return; }
    state->unk64 = arg1;
    script = (u8 *)(*(s32 *)(D_807FBB50 + (arg1 * 4)) + (s32)D_807FBB50);
    state->unk68 = script; state->unk6C = script; D_807F5AF0 = script;
}
