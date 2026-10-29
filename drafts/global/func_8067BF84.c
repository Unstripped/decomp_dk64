// func_8067BF84 (src/global/80150.c): stage 5: frame size 0x48 matches, s0/s1/fs0 match, 4-insn diff in loop indexing
extern u8 D_807FC928;
extern struct PlayerData *D_807FC924;
void actorApplyVelocity(Actor *);
s32 actorHasActiveMovementFlags(Actor *);
void animSetSpeed(Actor *, s32, f32);
void animSetLoopMode(Actor *, s32, s32);
void animSetDirection(Actor *, s32, s32);
void animSetLoopLimit(Actor *, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void func_80689114(s16, f32, f32, f32, s16, f32, void *);
extern u8 D_807FBBA8;
extern s32 D_8071FE08;
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void actorUpdateModelMatrix(Actor *, s32);

s32 func_8067BF84(s32 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    volatile u8 sp47; // FAKE: force stack home
    s32 pad[2];
    u8 var_a0;
    f32 var_fs0;
    f32 temp_f0;
    f32 temp_f1;

    sp47 = 0;
    var_fs0 = 99999.0f;
    if (D_807FBB40->unk60 & 0x10) {
        animSetSpeed(D_807FBB40, 0, 0.5f);
        animSetLoopMode(D_807FBB40, 0, 0);
        animSetDirection(D_807FBB40, 0, 0);
        animSetLoopLimit(D_807FBB40, 0, -1);
        if (D_807FBBA8 != 0 || *arg1 != 0 || *arg3 != 0) {
            *arg3 = 0;
            sp47 = 1;
        }
        if (sp47 != 0) {
            var_a0 = 0;
            if ((s32)D_807FC928 > 0) {
                do {
                    u8 *entry = (u8 *)D_807FC924 + (s32)var_a0 * 0x2F0;
                    if (*entry != 0) {
                        Actor *player = *(Actor **)(entry + 4);
                        temp_f0 = player->unk84 - D_807FBB40->unk84;
                        temp_f1 = player->unk7C - D_807FBB40->unk7C;
                        temp_f0 = sqrtf((temp_f0 * temp_f0) + (temp_f1 * temp_f1));
                        if (temp_f0 < var_fs0) {
                            var_fs0 = temp_f0;
                        }
                    }
                    var_a0++;
                } while (var_a0 < D_807FC928);
            }
            if ((f64)var_fs0 > 12.0) {
                *arg1 = 0;
            } else {
                *arg1 = 1;
                sp47 = 0;
            }
        }
    } else {
        sp47 = 1;
        *arg1 = 0;
        D_807FBB40->unkC0 = -10.0f;
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        if (actorHasActiveMovementFlags(D_807FBB40) != 0) {
            *arg2 = 1;
        } else {
            *arg2 = 0;
        }
    }
    if (sp47 != 0) {
        func_80689114(arg0, D_807FBB40->unk7C, (f32)((f64)D_807FBB40->unk80 + 8.3), D_807FBB40->unk84, 0, 1.0f, D_807FBB40);
        if (D_807FBB40->unk60 & 0x10) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x31, 0xFF, 0x7F, 1);
            func_807149B8(0);
            func_807149FC(1);
            func_80714CC0(&D_8071FE08, 0.5f, D_807FBB40->unk7C, D_807FBB40->unk80 + 7.0f, D_807FBB40->unk84);
        }
    }
    if (*arg2 != 0) {
        D_807FBB40->unkC0 = -10.0f;
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    return sp47;
}
