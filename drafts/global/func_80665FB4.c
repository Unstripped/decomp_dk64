// func_80665FB4 (src/global/699B0.c): Code matches 100%, rodata differs by 8-byte padding after 0.15f
void func_806303C4(s32, s32, Actor *, f32, f32, f32, s32, s32, s32, s32, s32);
void actorSub140SetVectors(Actor *, f32, f32, f32, f32);
extern s32 D_8076A064;

void func_80665FB4(Actor *arg0) {
    f32 x;
    f32 y;
    f32 z;
    f32 scale;

    x = arg0->unk7C;
    y = arg0->unk80;
    z = arg0->unk84;
    if (arg0->unk4 != NULL) {
        func_806303C4(0, 0, arg0, x, y, z, arg0->unk12A, 0, 1, -1, 1);
    }
    if (arg0->unk140 != NULL) {
        if (arg0->unk4 != NULL) {
            scale = arg0->unk4->unk38;
        } else {
            scale = 0.15f;
        }
        actorSub140SetVectors(arg0, x, y, z, scale);
        arg0->unk140->unk80 = D_8076A064;
    }
}
