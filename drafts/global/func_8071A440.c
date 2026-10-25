// func_8071A440 (src/global/11BC10.c): stage 6: text-identical instruction stream with corrected lightAdd call and lightSetFlags extra argument; fdiff remains relocation-only (D_8075E8F8 versus local .rodata), so GLOBAL_ASM retained.
typedef struct {
    u8 pad0[0x88];
    s32 unk88;
} NM2LightOwner;

extern NM2LightOwner *D_807FD580;
extern void *D_80028C30;

void func_8071A440(Ub5Actor *arg0, s8 *arg1) {
    f32 var_fv0;

    var_fv0 = (f32)(arg0->unk330->unk16 - arg0->unk34E) / (f32)arg0->unk330->unk16;
    if ((f64)var_fv0 > 0.7) {
        var_fv0 = 1.0f;
    }
    if ((D_807FD580->unk88 == arg0->unk35C) && ((void *)arg0 == D_80028C30)) {
        lightSetFlags(1, arg0);
        lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f,
                 (f32)((f64)var_fv0 * 50.0), 0, 0xFF,
                 (u32)((-80.0f * var_fv0) + 255.0f),
                 (u32)((-205.0f * var_fv0) + 255.0f));
    }
}
