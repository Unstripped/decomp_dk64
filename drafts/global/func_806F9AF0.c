// func_806F9AF0 (src/global/FCCD0.c): Exact: permuter found the reloaded table value plus split index declaration.
typedef struct NmFCCD0ActorView {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    u8 pad348[0x16];
    s16 unk35E;
    f32 unk360;
    f32 unk364;
} NmFCCD0ActorView;

extern u8 D_807FD7A0;
extern u8 D_807FD7B8;
extern u8 D_807FD7D0;

void func_806F9AF0(NmFCCD0ActorView *arg0, s8 *arg1) {
    f32 *temp_a2;
    f32 *temp_v0;
    int new_var;
    f32 temp_fv0;
    s32 temp_v1;

    new_var = arg0->unk35E;
    temp_v1 = 4 * new_var;
    temp_a2 = (f32 *)(temp_v1 + &D_807FD7A0);
    temp_fv0 = *temp_a2;
    if (*temp_a2 == -200.0f) {
        *arg1 = 1;
        return;
    }
    arg0->unk340 = *temp_a2;
    temp_v0 = (f32 *)(temp_v1 + &D_807FD7D0);
    arg0->unk344 = *(f32 *)(temp_v1 + &D_807FD7B8);
    arg0->unk360 = *temp_v0;
    arg0->unk364 = *temp_v0;
    *temp_a2 = -200.0f;
}
