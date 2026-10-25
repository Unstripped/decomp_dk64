// func_8071B758 (src/global/11BC10.c): Stage 6: typed lightAdd and f32 fourth argument yield instruction-identical function body; whole-file offset remains shifted by the two unresolved preceding 0x9C motion helpers.
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

typedef struct {
    u8 pad0[0x330];
    void *unk330;
    u8 pad334[4];
    void *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    s16 unk34C;
    u8 pad34E[2];
} Ub4ActorView;

void func_8071B758(Ub4ActorView *arg0, s8 *arg1) {
    f32 ratio;
    s32 intensity;

    ratio = (f32)(*((s16 *)((u8 *)arg0->unk330 + 0x16)) - *((s16 *)((u8 *)arg0 + 0x34E))) / (f32)*((s16 *)((u8 *)arg0->unk330 + 0x16));
    if ((f64)ratio > 0.7) {
        ratio = 1.0f;
    }
    intensity = (u32)((-155.0f * ratio) + 255.0f) & 0xFF;
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 50.0f, 0, intensity, intensity, intensity);
}
