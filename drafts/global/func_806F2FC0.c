// func_806F2FC0 (src/global/F56F0.c): Stage 3: corrected dispatch input to s32 masking and recovered complete effect call ABI (four f32 arguments plus signed effect parameter); case-state control flow remains frame/register tuning work.
typedef struct F5CEffectActor {
    u8 pad0[0x8E];
    u8 unk8E;
    u8 unk8F;
    u8 unk90;
    u8 unk91;
} F5CEffectActor;
extern void effectSpawnBoneWhite(Actor *, s16, f32, f32, f32, f32, s32);
void func_806F2FC0(Actor *arg0, F5CEffectActor *arg1, s32 arg2) {
    u8 state;
    s32 should_spawn;
    switch (arg2 & 0xFFFF) {
    case 1:
        should_spawn = 0;
        state = arg1->unk8E;
        if (state == 0) {
            should_spawn = 1;
        } else if (state == 3) {
            should_spawn = 1;
        } else if ((state == 0x10) && (arg1->unk8F < 6)) {
            arg1->unk8F = 0;
        }
        if (should_spawn != 0) {
            effectSpawnBoneWhite(arg0, 0xA, 0.3f, 0.0f, 0.0f, 0.0f, -0xA);
        }
        break;
    case 2:
        state = arg1->unk8E;
        if ((state == 0) || (state == 3)) {
            effectSpawnBoneWhite(arg0, 0xA, 0.3f, 0.0f, 0.0f, 0.0f, -0xA);
        }
        break;
    }
}
