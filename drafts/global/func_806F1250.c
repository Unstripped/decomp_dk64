// func_806F1250 (src/global/F56F0.c): Stage 3 behavioral draft recovered from m2c; variadic-looking parameter scheduling prevents a match.
typedef struct F5AActorExtra {
    u8 pad0[0x1F0];
    s32 flags;
} F5AActorExtra;

void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, s32, f32, s32);
void func_80613194(s32);
void sfxAllocateChannel(s32, f32);
extern s32 D_807FBB68;

void func_806F1250(Actor *arg0) {
    F5AActorExtra *extra = arg0->unk174;

    if (arg0->unk58 == 6) {
        func_80613194(0x10);
        func_806086CC(arg0->unk7C, arg0->unk80, arg0->unk84, 0x2E2, 0xFF, 0xA0, 0, 0x32, 0, 0.0f, 0);
        if (!(D_807FBB68 & 2)) {
            sfxAllocateChannel(0x6C, 1.0f);
        }
    }
    extra->flags |= 0x40;
}
