// func_8071F758 (src/global/11BC10.c): stage 5: behavior and matrix sequence reached; target needs state in v1 then s0 and matrix bases sp+0x6C/sp+0x2C rather than current allocation.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} M2F758State;

typedef struct {
    u8 pad0[0x32C];
    u8 unk32C;
    u8 pad32D[0x33];
    f32 unk360;
    f32 unk364;
    u8 pad368[0x1C];
    M2F758State *unk384;
} M2F758ActorView;

void func_8071F758(M2F758ActorView *arg0, void *arg1) {
    f32 sp6C[4][4];
    f32 sp2C[4][4];
    f32 temp_fv0;
    M2F758State *temp_v0;
    M2F758State *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0.01f;
        temp_v0->unk8 = 0.0f;
        temp_v0->unk4 = arg0->unk360;
        var_v1 = arg0->unk384;
    }
    temp_fv0 = var_v1->unk0;
    var_v1->unk8 = var_v1->unk8 + 5.0f;
    var_v1->unk0 = (f32)(((f64)(var_v1->unk4 - temp_fv0) * 0.1) + (f64)temp_fv0);
    arg0->unk360 = (f32)(((f64)func_80612794((s16)(D_8076A064 * 0x32)) * 0.1) + (f64)var_v1->unk0);
    arg0->unk364 = (f32)(((f64)func_80612790((s16)(D_8076A064 * 0x19)) * 0.1) + (f64)var_v1->unk0);
    guScaleF(sp6C, arg0->unk360, arg0->unk364, 0.0f);
    func_80612CA0(sp2C, var_v1->unk8);
    guMtxCatF(sp6C, sp2C, sp6C);
    guMtxF2L(sp6C, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->unk32C = 2;
}
