// func_806F2FC0 (src/global/F56F0.c): Stage 3 reconstructed all selector 0/1/4/5 paths; current closest has target control flow but needs ABI/register-frame tuning.
typedef struct F5N5EffectState {
    u8 pad0[0x8E];
    u8 unk8E;
    u8 unk8F;
    u8 unk90;
    u8 unk91;
} F5N5EffectState;

void effectSpawnBoneWhite(Actor *, s16, f32, f32, f32, f32, s32);

void func_806F2FC0(Actor *arg0, F5N5EffectState *arg1, s32 arg2) {
    s16 bone;
    s32 selector;
    s32 shouldSpawn;
    u8 state0;
    u8 state1;
    u8 state2;

    selector = arg2 & 0xFFFF;
    switch (selector) {
    case 0:
        state0 = arg1->unk8E;
        if (state0 != 0) {
            if ((state0 == 0x10) && ((s32)arg1->unk8F < 4)) {
                arg1->unk8F = 0;
                return;
            }
        } else {
            if ((s32)arg1->unk8F >= 4) {
                effectSpawnBoneWhite(arg0, 0xA, 0.3f, 0.0f, 0.0f, 0.0f, -10);
                return;
            }
            return;
        }
        break;
    case 1:
        state1 = arg1->unk8E;
        shouldSpawn = 0;
        if ((state1 != 0) && (state1 != 3)) {
            if ((state1 == 0x10) && ((s32)arg1->unk8F < 6)) {
                arg1->unk8F = 0;
            }
        } else if ((s32)arg1->unk8F >= 6) {
            shouldSpawn = 1;
        }
        if (shouldSpawn != 0) {
            if (arg1->unk8E != 0) {
                bone = arg1->unk90 + 9;
            } else {
                bone = arg1->unk91 + 9;
            }
            effectSpawnBoneWhite(arg0, bone, 0.2f, 0.0f, 0.0f, 0.0f, -10);
            return;
        }
        break;
    case 4:
    case 5:
        state2 = arg1->unk8E;
        if (state2 != 0) {
            if ((state2 == 0x10) && ((s32)arg1->unk8F < 3)) {
                arg1->unk8F = 0;
                return;
            }
        } else if ((s32)arg1->unk8F >= 3) {
            effectSpawnBoneWhite(arg0, 0xA, 0.6f, 0.0f, 0.0f, 0.0f, -10);
        }
        break;
    }
}
