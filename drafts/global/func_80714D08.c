// func_80714D08 (src/global/119370.c): Stage 2: m2c semantic allocator/list linker. A full raw-field reconstruction compiles in Ua1c but needs block and ABI/register work; use m2c draft as starting map.
void *func_80610FE8(f32, f32, ?);                   /* extern */
? func_80714778(f32);                               /* extern */
? func_80714A9C(f32, f32, ?);                       /* extern */
? func_8071509C(void *);                            /* extern */
extern u8 D_80750AB4;
extern s32 D_807FBB64;
extern void *D_807FDB00;
extern void *D_807FDB04;
extern void *D_807FDB08;
extern u8 D_807FDB0C;
extern u8 D_807FDB0D;
extern u8 D_807FDB0E;
extern u8 D_807FDB0F;
extern s32 D_807FDB10;
extern s32 D_807FDB14;
extern u8 D_807FDB18;
extern s16 D_807FDB1A;
extern u8 D_807FDB1C;
extern u8 D_807FDB1D;
extern f32 D_807FDB20;
extern f32 D_807FDB24;
extern u8 D_807FDB28;
extern s32 D_807FDB2C;
extern s32 D_807FDB30;
extern u16 D_807FDB36;
extern s16 D_807FDB38;
extern s16 D_807FDB3A;
extern s16 D_807FDB3C;
extern s16 D_807FDB3E;
extern s16 D_807FDB40;
extern s16 D_807FDB42;

void *func_80714D08(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8) {
    void *sp2C;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv1;
    s32 var_s1;
    s32 var_v0;
    u8 temp_v1;
    void *temp_v0;
    void *var_s0;
    void *var_s0_2;

    func_80714778(arg1);
    var_s0 = D_807FDB00;
    var_v0 = 0;
    if (var_s0 != NULL) {
loop_1:
        if (arg0 == var_s0->unk0) {
            var_v0 = 1;
        } else {
            var_s0 = var_s0->unk24;
        }
        if ((var_v0 == 0) && (var_s0 != NULL)) {
            goto loop_1;
        }
    }
    if (var_v0 == 0) {
        func_80714A9C(arg1, arg3, 0x3A0);
        return NULL;
    }
    temp_v0 = func_80610FE8(arg1, arg3, 0x3A0);
    var_fv1 = arg2;
    var_fa0 = arg1;
    var_fa1 = arg3;
    if (D_807FDB04 != NULL) {
        D_807FDB08->unk39C = temp_v0;
        temp_v0->unk398 = (void *) D_807FDB08;
    } else {
        D_807FDB04 = temp_v0;
        temp_v0->unk398 = NULL;
    }
    D_807FDB08 = temp_v0;
    if (D_807FDB1D != 0) {
        var_fv1 *= 4.0f;
        var_fa1 *= 4.0f;
        var_fa0 *= 4.0f;
        arg4 *= 4.0f;
        D_807FDB20 *= 4.0f;
        D_807FDB24 *= 4.0f;
    }
    temp_v0->unk340 = var_fv1;
    temp_v0->unk344 = var_fa1;
    temp_v0->unk348 = arg4;
    if (D_807FDB28 != 0) {
        temp_v0->unk360 = (f32) D_807FDB20;
        temp_v0->unk364 = (f32) D_807FDB24;
    } else {
        temp_v0->unk360 = var_fa0;
        temp_v0->unk364 = var_fa0;
    }
    if (D_807FDB0F != 0) {
        temp_v0->unk36A = (u8) D_807FDB0C;
        temp_v0->unk36B = (u8) D_807FDB0D;
        temp_v0->unk36C = (u8) D_807FDB0E;
        temp_v0->unk36D = (u8) D_807FDB0F;
    } else {
        temp_v0->unk36A = (u8) var_s0->unk10;
        temp_v0->unk36B = (u8) var_s0->unk11;
        temp_v0->unk36C = (u8) var_s0->unk12;
        temp_v0->unk36D = (u8) var_s0->unk13;
    }
    temp_v0->unk36E = (u8) D_807FDB18;
    temp_v0->unk36F = (u8) D_807FDB1D;
    temp_v0->unk368 = (s16) D_807FDB1A;
    temp_v0->unk380 = (s32) (var_s0->unk8 * var_s0->unk9);
    temp_v0->unk334 = arg8;
    temp_v0->unk338 = arg5;
    temp_v0->unk33C = (s16) arg6;
    temp_v0->unk33E = (s8) arg7;
    temp_v0->unk34E = (s16) D_807FDB30;
    temp_v0->unk351 = 0;
    temp_v0->unk350 = (u8) D_807FDB1C;
    temp_v0->unk358 = 0;
    temp_v0->unk354 = (s32) D_807FDB10;
    temp_v0->unk35C = (s32) D_807FDB2C;
    if (D_807FBB64 & 0x100) {
        temp_v0->unk34C = 0x7D0;
    } else {
        temp_v0->unk34C = (s16) D_807FDB3A;
    }
    temp_v0->unk330 = var_s0;
    temp_v0->unk39C = 0;
    temp_v0->unk384 = 0;
    temp_v0->unk328 = (s32) D_807FDB14;
    temp_v0->unk38A = -1;
    temp_v0->unk388 = (s16) D_807FDB38;
    temp_v0->unk38C = (u16) D_807FDB36;
    temp_v0->unk38E = (s16) D_807FDB3C;
    temp_v0->unk390 = (s16) D_807FDB3E;
    var_s0_2 = temp_v0;
    var_s1 = 0;
    temp_v0->unk392 = (s16) D_807FDB40;
    temp_v0->unk394 = (s16) D_807FDB42;
    temp_v1 = D_80750AB4;
    sp2C = temp_v0;
    if ((s32) temp_v1 > 0) {
        sp2C = temp_v0;
        do {
            var_s0_2->unk0 = func_80610FE8(7.17e-43f);
            var_s0_2->unk4 = func_80610FE8(7.17e-43f);
            var_s1 += 1;
            var_s0_2 += 8;
        } while (var_s1 < (s32) D_80750AB4);
    }
    sp2C->unk20 = temp_v1;
    func_8071509C(sp2C);
    func_80714A9C();
    return sp2C;
}
