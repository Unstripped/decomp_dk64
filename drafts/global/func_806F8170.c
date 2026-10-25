// func_806F8170 (src/global/FCCD0.c): Stage 6: matched; retained in the private FCCD0.c replacement with TEXT OK.
typedef struct R2FCCD0eTransformSlot {
    void *unk0;
    u16 unk4;
    u8 pad6[0xA];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 pad1C[0x14];
} R2FCCD0eTransformSlot;

void func_806F8170(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if (arg0 < 0) {
        func_806F8004(16.5f, 0.0f, arg1, arg2, arg3);
    } else if (arg0 == 8) {
        func_806F8004((f32)(1.5 - (f64)(((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk4 * 7)), 26.0f, arg1, arg2, arg3);
    } else {
        *arg1 = ((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk10;
        *arg2 = ((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk14;
        *arg3 = ((R2FCCD0eTransformSlot *)D_80754280)[arg0].unk18;
    }
}
