// func_806F2FC0 (src/global/F56F0.c): Stage 2 behavioral draft; target has 0x28 frame/no saved a0, while typed view draft saves a0 and differs in switch structure and call scheduling.
typedef struct F5CEffectActor {
    u8 pad0[0x8E];
    u8 unk8E;
    u8 unk8F;
    u8 unk90;
    u8 unk91;
} F5CEffectActor;

extern void effectSpawnBoneWhite(Actor *, s16, f32, f32, f32, s32, s32);

void func_806F2FC0(Actor *arg0, F5CEffectActor *arg1, s16 arg2) {
    s32 shouldSpawn;
    u8 state;

    switch (arg2) {
        case 0:
            state = arg1->unk8E;
            if (state != 0) {
                if ((state == 0x10) && (arg1->unk8F < 4)) {
                    arg1->unk8F = 0;
                }
                return;
            }
            if (arg1->unk8F < 4) {
                effectSpawnBoneWhite(arg0, 0xA, 0.3f, 0.0f, 0.0f, 0, -0xA);
            }
            break;
        case 1:
            shouldSpawn = 0;
            state = arg1->unk8E;
            if ((state == 0) || (state == 3)) {
                shouldSpawn = 1;
            } else if ((state == 0x10) && (arg1->unk8F < 6)) {
                arg1->unk8F = 0;
            }
            if (shouldSpawn != 0) {
                if (arg1->unk8E == 0) {
                    state = arg1->unk91 + 9;
                } else {
                    state = arg1->unk90 + 9;
                }
                effectSpawnBoneWhite(arg0, state, 0.2f, 0.0f, 0.0f, 0, -0xA);
            }
            break;
        case 4:
        case 5:
            state = arg1->unk8E;
            if (state != 0) {
                if ((state == 0x10) && (arg1->unk8F < 3)) {
                    arg1->unk8F = 0;
                }
                return;
            }
            if (arg1->unk8F < 3) {
                effectSpawnBoneWhite(arg0, 0xA, 0.6f, 0.0f, 0.0f, 0, -0xA);
            }
            break;
    }
}
