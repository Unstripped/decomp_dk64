// func_806A2328 (src/global/A6280.c): stage 1 (never attempted in C): m2c starter saved; not compiled/verified. Needs f64/sqrtf/16-bit angle code: unk160 double, unkE6/unkEC/unkF0/unkFA/unk168 s16
? actorDespawn(void *);                             /* extern */
? billboardSetFlags(?);                             /* extern */
? func_806086CC(f32, f32, f32, ?, s32, s32, s32, s32, f32, s32); /* extern */
f32 func_80612790(s16);                             /* extern */
f32 func_80612794(s16);                             /* extern */
? actorUpdateModelMatrix(void *, ?);                         /* extern */
? func_8065D254(void *, ?, ?, ?, s32, s32, s32, s32, s32, s32, f32); /* extern */
? actorUpdateFloorContactAndTilt(void *, ?);                         /* extern */
? func_8067ACB4(f64, f32, void *);                  /* extern */
? actorSetUniformScale(void *, s32);                       /* extern */
s16 mathAngleBetweenPoints2D(f32, f32, void **, f32, f32); /* extern */
extern void *D_807FBB40;
extern void *D_807FBB4C;

void func_806A2328(f64 arg0, f32 arg1) {
    f32 sp48;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fa1;
    f64 var_fa0;
    f64 var_fv0;
    f64 var_fv0_2;
    s16 temp_v0_2;
    s32 temp_v0;
    void *temp_s0;
    void *temp_s2;
    void *temp_v0_3;

    var_fa0 = arg0;
    var_fa1 = arg1;
    temp_s0 = D_807FBB40;
    temp_v0 = temp_s0->unk60;
    temp_s2 = temp_s0->unk174;
    if (!(temp_v0 & 0x10)) {
        temp_s0->unk60 = (s32) (temp_v0 | 0x1000);
        actorSetUniformScale(D_807FBB40, D_807FBB40->unk124->unkC);
        D_807FBB40->unk168 = mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, &D_807FBB4C, D_807FBB4C->unk7C, D_807FBB4C->unk84);
        D_807FBB40->unkF0 = (s16) (s32) ((f64) ((D_807FBB4C->unk80 + (f32) D_807FBB4C->unk15E) - D_807FBB40->unk80) * 0.5);
        temp_fv0 = D_807FBB40->unk7C - D_807FBB4C->unk7C;
        temp_fa1 = D_807FBB40->unk84 - D_807FBB4C->unk84;
        D_807FBB40->unkEC = (s16) (s32) ((f64) sqrtf((temp_fv0 * temp_fv0) + (temp_fa1 * temp_fa1)) * 0.5);
        var_fa1 = D_807FBB40->unk7C;
        temp_s2->unk0 = (s16) (s32) ((f64) var_fa1 + ((f64) (D_807FBB4C->unk7C - var_fa1) * 0.5));
        temp_ft5 = D_807FBB40->unk80;
        temp_s2->unk2 = (s16) (s32) ((f64) temp_ft5 + ((f64) (D_807FBB4C->unk80 - temp_ft5) * 0.5));
        temp_ft4 = D_807FBB40->unk84;
        temp_s2->unk4 = (s16) (s32) ((f64) temp_ft4 + ((f64) (D_807FBB4C->unk84 - temp_ft4) * 0.5));
        D_807FBB40->unk144 = 0x24;
        D_807FBB40->unkFA = 0x2328;
        D_807FBB40->unk160 = (f64) D_807FBB40->unk124->unk4;
        var_fa0 = D_807FBB40->unk160 * ((f64) D_807FBB40->unkEC * 0.01);
        if (var_fa0 > 15.0) {
            var_fv0 = var_fa0;
        } else {
            var_fv0 = 0.0;
        }
        if (var_fv0 < 150.0) {
            if (var_fa0 > 15.0) {
                var_fv0_2 = var_fa0;
            } else {
                var_fv0_2 = 0.0;
            }
            D_807FBB40->unk160 = var_fv0_2;
        } else {
            D_807FBB40->unk160 = 150.0;
        }
        temp_s2->unk8 = (s16) (s32) D_807FBB40->unk160;
    }
    func_8067ACB4(var_fa0, var_fa1, temp_s0);
    temp_fv0_2 = (f32) ((((f64) temp_s2->unk8 / D_807FBB40->unk160) * -4096.0) + 4096.0);
    temp_s2->unk6 = (s16) (s32) ((f32) D_807FBB40->unk168 + temp_fv0_2);
    sp48 = temp_fv0_2;
    D_807FBB40->unk7C = (f32) ((func_80612794(temp_s2->unk6) * (f32) D_807FBB40->unkEC) + (f32) temp_s2->unk0);
    D_807FBB40->unk84 = (f32) ((func_80612790(temp_s2->unk6) * (f32) D_807FBB40->unkEC) + (f32) temp_s2->unk4);
    D_807FBB40->unk80 = (f32) ((func_80612790((s16) (s32) (2048.0f + sp48)) * (f32) D_807FBB40->unkF0) + (f32) temp_s2->unk2);
    actorUpdateFloorContactAndTilt(D_807FBB40, 0);
    D_807FBB40->unkE6 = (s16) (D_807FBB40->unkE6 + 0x12C);
    if ((D_807FBB40->unkE6 & 0x7FF) < 0x12C) {
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x1DF, 0xFF, 0x7F, 0x14, 0x3C, 0.7f, 0);
    }
    temp_v0_2 = temp_s2->unk8;
    if (temp_v0_2 != 0) {
        temp_s2->unk8 = (s16) (temp_v0_2 - 1);
        if (temp_s2->unk8 == 0xB) {
            temp_v0_3 = D_807FBB40->unk11C;
            if (temp_v0_3 != NULL) {
                temp_v0_3->unk155 = (u8) (temp_v0_3->unk155 + 1);
            }
        }
    } else {
        actorDespawn(D_807FBB40);
    }
    billboardSetFlags(1);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x12C, 0xB4, 0, 1.0f);
    actorUpdateModelMatrix(D_807FBB40, 0);
}
