// func_806EC4AC (src/global/EFDC0.c): Stage 3: bounded permutation improved score from 5815 to 4671; frame and floating-register allocation remain unmatched.
typedef struct EfN3PlayerState {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0xA];
    f32 unk1C;
    u8 pad20[0xC];
    f32 unk30;
    u8 pad34[0x14];
    s16 unk48;
} EfN3PlayerState;

typedef struct EfN3Actor {
    u8 pad0[0x80];
    f32 unk80;
    u8 pad84[0x1C];
    f32 unkA0;
    u8 padA4[8];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0x90];
    u8 unk154;
    u8 unk155;
} EfN3Actor;

#define EFN3_P ((EfN3PlayerState *)D_807FD580)
#define EFN3_A40 ((EfN3Actor *)D_807FBB40)
#define EFN3_A48 ((EfN3Actor *)D_807FBB48)

extern f32 D_80753250[];
extern s16 D_8075388C[];
extern s16 D_807538D8[];
extern s16 D_807538E8[];
extern s16 D_807538F8[];
extern f32 D_80753988[];
extern s16 D_807539FC[];
extern f32 D_80753A5C[];
void func_806CF398(Actor *);

void func_806EC4AC(void) {
    f32 temp_fa0;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 var_fa1;
    f32 var_fs0;
    f32 var_ft5;
    s16 temp_v0;
    s32 temp_v1;

    func_806CF398(D_807FBB48);
    temp_fv0 = D_80753A5C[D_807FD584];
    temp_v1 = D_807FD584 * 2;
    if (temp_fv0 > 0.0f) {
        var_fs0 = temp_fv0;
    } else {
        var_fs0 = -temp_fv0;
    }
    temp_ft4 = EFN3_A48->unkAC;
    temp_fv0_2 = D_807538D8[D_807FD584];
    var_ft5 = EFN3_A48->unkA0 - temp_ft4;
    if (temp_fv0_2 < var_ft5) {
        var_ft5 = temp_fv0_2;
    }
    temp_v0 = D_807538E8[D_807FD584];
    temp_fa0 = (((D_807538F8[D_807FD584] - temp_v0) * (var_ft5 / temp_fv0_2)) + temp_v0) - ((temp_ft4 - D_8075388C[D_807FD584]) - EFN3_A48->unk80);
    temp_fa0 *= 40.0f;
    if (temp_fa0 > 0.0f) {
        var_fa1 = (f32)((f64)EFN3_A48->unkC0 * (0.5 + (f64)((var_ft5 * 40.0f) / (2.0f * (temp_fv0_2 * 40.0f)))));
        if (((var_fa1 * var_fa1) / (2.0f * temp_fa0)) < var_fs0) {
            goto block_9;
        }
    } else {
        var_fa1 = 0.0f;
block_9:
        var_ft5 = var_fs0;
    }
    EFN3_A48->unkC0 = var_fa1;
    EFN3_P->unk1C = var_ft5;
    EFN3_P->unk10 = 0;
    EFN3_P->unk30 = D_80753250[D_807FD584];
    temp_fv1 = D_80753988[D_807FD584];
    temp_fv0_3 = EFN3_A40->unkB8;
    if (temp_fv0_3 < temp_fv1) {
        EFN3_A40->unkB8 = temp_fv0_3;
    } else {
        EFN3_A40->unkB8 = temp_fv1;
    }
    EFN3_A48->unk154 = 0x4E;
    EFN3_A48->unk155 = 0;
    func_80614E78(D_807FBB40, 0x35);
    EFN3_P->unk48 = D_807539FC[D_807FD584];
}
