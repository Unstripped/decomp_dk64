// func_8066A64C (src/global/699B0.c): starter m2c draft (unattempted)
? func_8062FF10(f32 (*)[4], f32 *);                 /* extern */
? memcpy(f32 (*)[4], s32, ?, void *);               /* extern */
extern u8 D_807444FC;
extern s32 D_8076A064;
extern void *D_807F9470;
extern f32 D_807F9474;
extern f32 D_807F9478;
extern f32 D_807F947C;
extern u32 D_807F9480;
extern s8 D_807F94B2;

void func_8066A64C(s32 arg0, void *arg1, void *arg2, f32 arg3, f32 arg4, f32 arg5) {
    u32 temp_v0;
    u32 temp_v0_2;
    u8 var_v1;
    void *temp_a3;

    D_807F9470 = arg1;
    temp_a3 = arg1->unk140;
    if (D_8076A064 == temp_a3->unk88) {
        var_v1 = D_807444FC;
    } else {
        var_v1 = (D_807444FC ^ 1) & 0xFF;
    }
    temp_v0 = arg2->unk48;
    if ((temp_v0 != arg2->unk4C) || (temp_v0 != arg2->unk50)) {
        D_807F94B2 = 1;
    }
    D_807F9480 = arg2->unk48;
    temp_v0_2 = arg2->unk48;
    if (temp_v0_2 == -1U) {
        memcpy((f32 (*)[4]) &sp78[0], temp_a3->unk70, 0x40, temp_a3);
    } else {
        guMtxL2F((f32 (*)[4]) &sp78[0], ((temp_v0_2 >> 6) << 6) + (temp_a3 + (var_v1 * 4))->unk74);
    }
    func_8062FF10((f32 (*)[4]) &sp38[0], &sp78[0]);
    guMtxXFMF((f32 (*)[4]) &sp38[0], arg3, arg4, arg5, &D_807F9474, &D_807F9478, &D_807F947C);
}
