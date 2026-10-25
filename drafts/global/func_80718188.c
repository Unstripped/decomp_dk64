// func_80718188 (src/global/11BC10.c): Recovered logic; function call ABI and pointer register allocation differ from target.
extern s16 D_807502D0;

typedef struct {
    u8 pad0[0x330];
    void *unk330;
    u8 pad334[4];
    void *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
    f32 unk360;
    u8 pad364[0x20];
    void *unk384;
} Ub2ActorView;

void func_80718188(arg0, arg1)
Ub2ActorView *arg0;
s8 *arg1;
{
    s16 *temp_v0;
    s16 *temp_v1;
    s16 *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(2);
        arg0->unk384 = temp_v0;
        *temp_v0 = 0;
        var_v1 = arg0->unk384;
    }
    arg0->unk344 = arg0->unk344 + (f32) *var_v1;
    *var_v1 -= 1;
    temp_v1 = arg0->unk384;
    if (*temp_v1 < D_807502D0) {
        *temp_v1 = D_807502D0;
    }
    if (arg0->unk344 < (f32) arg0->unk35C) {
        *arg1 = 1;
        func_80718124((f32) ((f64) arg0->unk360 * 1.5), arg0->unk340, (f32) arg0->unk35C, arg0->unk348);
    }
}
