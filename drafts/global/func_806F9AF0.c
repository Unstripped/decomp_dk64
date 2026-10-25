// func_806F9AF0 (src/global/FCCD0.c): Stage 4: behaviour confirmed; 4 extra instructions from offset arithmetic register allocation.
typedef struct R1FCCD0bActorView {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    u8 pad348[0x16];
    s16 unk35E;
    f32 unk360;
    f32 unk364;
} R1FCCD0bActorView;

extern u8 D_807FD7A0;
extern u8 D_807FD7B8;
extern u8 D_807FD7D0;

void func_806F9AF0(R1FCCD0bActorView *arg0, s8 *arg1) {
    f32 *temp_a2;
    f32 *temp_v0;
    f32 temp_fv0;
    s32 temp_v1;

    temp_v1 = arg0->unk35E * 4;
    temp_a2 = (f32 *)(temp_v1 + &D_807FD7A0);
    temp_fv0 = *temp_a2;
    if (temp_fv0 == -200.0f) {
        *arg1 = 1;
        return;
    }
    arg0->unk340 = temp_fv0;
    temp_v0 = (f32 *)(temp_v1 + &D_807FD7D0);
    arg0->unk344 = *(f32 *)(temp_v1 + &D_807FD7B8);
    arg0->unk360 = *temp_v0;
    arg0->unk364 = *temp_v0;
    *temp_a2 = -200.0f;
}
