// func_8066F84C (src/global/70FD0.c): collision plane response with guMtxXFMF 3-vertex loop, angle wrapping, and calls to func_8066FD6C and func_8066FC0C
void matrix4Invert(f32 [4][4], void *);
void func_8066C610(s16, s8, void *);
void func_8066FC0C(M70D_Actor *, void *, void *);
s32 func_8066FD6C(M70D_Actor *);
void func_8066FE08(s16);
s32 func_806744A8(void *, s32, s32, s32, s32);
extern s32 D_807F6000;
extern s32 D_807FB5C4;
extern s32 D_807FB5C8;
extern s32 D_807FB5CC;
extern s32 D_807FB5D0;
extern void *D_807FB5D8;

void func_8066F84C(s16 arg0, M70D_Actor *arg1, s32 arg2) {
    u8 sp138[0x40];
    f32 spB8[4][4];
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    s32 sp74;
    f32 *var_s0_2;
    f32 *var_s1;
    f32 *var_s2;
    f32 *var_s3;
    f32 *var_s4;
    f32 *var_s5;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv1;
    s16 temp_v0;
    s32 temp_s1;
    s32 temp_t6;
    s32 var_s0;
    void *temp_s7;
    void *temp_v1;

    temp_s7 = arg1->unk140;
    var_s0 = 0;
    temp_s1 = func_806744A8(D_807FB5D8, *(s32 *)temp_s7, *(s32 *)((u8 *)temp_s7 + 4), *(s32 *)((u8 *)temp_s7 + 8), *(s32 *)((u8 *)temp_s7 + 0xC)) & 0xFF;
    func_8066FE08(arg0);
    if (temp_s1 != 0) {
        *((s8 *)temp_s7 + 0x5A) = *((s8 *)D_807FB5D8 + 0x4E);
        *(s16 *)((u8 *)temp_s7 + 0x58) = (s16) ((s32) ((u8 *)D_807FB5D8 - (u8 *)arg2) / 88);
        func_8066C610(arg0, *((s8 *)D_807FB5D8 + 0x4E), sp138);
        matrix4Invert(spB8, sp138);
        temp_t6 = arg0 * 0x90;
        sp74 = temp_t6;
        temp_v1 = *(void **)((u8 *)D_807F6000 + temp_t6 + 0x7C);
        if ((temp_v1 != NULL) && (*((u8 *)temp_v1 + 0x9B) & 0x24)) {
            var_s0 = 1;
        }
        if (var_s0 != 0) {
            var_fv1 = *(f32 *)((u8 *)arg1 + 0x7C);
            var_fa0 = *(f32 *)((u8 *)arg1 + 0x80);
            var_fa1 = *(f32 *)((u8 *)arg1 + 0x84);
        } else {
            var_fv1 = (f32) D_807FB5C4 / 8.0f;
            var_fa0 = (f32) D_807FB5C8 / 8.0f;
            var_fa1 = (f32) D_807FB5CC / 8.0f;
        }
        if (!(arg1->unk60 & 0x800)) {
            guMtxXFMF(spB8, var_fv1, var_fa0, var_fa1, (f32 *)((u8 *)temp_s7 + 0x4C), (f32 *)((u8 *)temp_s7 + 0x50), (f32 *)((u8 *)temp_s7 + 0x54));
        }
        var_s1 = &spA0;
        var_s2 = &sp94;
        var_s0_2 = &sp88;
        var_s3 = (f32 *)((u8 *)temp_s7 + 0x28);
        var_s4 = (f32 *)((u8 *)temp_s7 + 0x34);
        var_s5 = (f32 *)((u8 *)temp_s7 + 0x40);
        spA0 = (f32) *(s32 *)((u8 *)D_807FB5D8 + 0x24) / 8.0f;
        sp94 = (f32) *(s32 *)((u8 *)D_807FB5D8 + 0x28) / 8.0f;
        sp88 = (f32) *(s32 *)((u8 *)D_807FB5D8 + 0x2C) / 8.0f;
        spA4 = (f32) *(s32 *)((u8 *)D_807FB5D8 + 0x30) / 8.0f;
        sp98 = (f32) *(s32 *)((u8 *)D_807FB5D8 + 0x34) / 8.0f;
        sp8C = (f32) *(s32 *)((u8 *)D_807FB5D8 + 0x38) / 8.0f;
        spA8 = (f32) *(s32 *)((u8 *)D_807FB5D8 + 0x3C) / 8.0f;
        sp9C = (f32) *(s32 *)((u8 *)D_807FB5D8 + 0x40) / 8.0f;
        sp90 = (f32) *(s32 *)((u8 *)D_807FB5D8 + 0x44) / 8.0f;
        do {
            guMtxXFMF(spB8, *var_s1, *var_s2, *var_s0_2, var_s3, var_s4, var_s5);
            var_s0_2 += 1;
            var_s1 += 1;
            var_s2 += 1;
            var_s3 += 1;
            var_s4 += 1;
            var_s5 += 1;
        } while (var_s0_2 != &sp94);
        *(s16 *)((u8 *)temp_s7 + 0x26) = *(s16 *)((u8 *)D_807F6000 + sp74 + 0x88);
        *(s32 *)((u8 *)temp_s7 + 0x5C) = D_807FB5D0;
        if (D_807FB5D0 < 0x14) {
            *(s32 *)((u8 *)temp_s7 + 0x5C) = 0x14;
        }
        *(s32 *)((u8 *)temp_s7 + 0x64) = func_8066FD6C(arg1);
        *(s16 *)((u8 *)temp_s7 + 0x66) = *(s16 *)((u8 *)D_807FB5D8 + 0x48);
        if (*((u8 *)D_807FB5D8 + 0x4C) != 0) {
            *(s16 *)((u8 *)temp_s7 + 0x66) -= 0x800;
        }
        temp_v0 = *(s16 *)((u8 *)temp_s7 + 0x66);
        if (temp_v0 < 0) {
            *(s16 *)((u8 *)temp_s7 + 0x66) = temp_v0 + 0x1000;
        }
        *((u8 *)temp_s7 + 0x6C) = 1;
        if (arg1->unk5C & 1) {
            func_8066FC0C(arg1, D_807FB5D8, temp_s7);
        }
    }
}
