// func_80028440 (src/race/36B0.c): stage 5, parked NON_MATCHING in LargeR1 copy: all regs/frame/size identical; only diff = 3-insn order at state-0 dispatch (expected 'move a0,v1; beqz v1; move v0,v1 [delay]', mine 'move v0,v1; beqz v1; move a0,v1 [delay]'; pre-as1 order from uopt LR split is [sw copy, var_a0 copy]). Needed: s32 temp_v1_2/var_a0/temp_v1_3 locals, a[0]=a[1]=2 chain, s32 playerStateQueueCallback, case +1 as s1[0x35]+1. Reloc-only diffs: .rodata vs D_8002FF88/jtbl_8002FF8C
extern u8 D_807FBD70;
extern s16 D_80750AC8;
extern s32 D_8002FC0C[];
s32 raceGetPrevWaypointIndex(s32, s32);
void behaviourFrameBegin(void);
void actorClearNodeFlag(void *, s32);
void actorUpdateModelMatrix(void *, s32);
void func_80026354(void *, void *, s32);
void func_800282D8(void);
void func_8002D72C(void *);
void func_8002D754(void *);
s32 func_8002E8EC(void *, void *, s32);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
void camStartPath(void *, s16, s32);
void camResumePath(void);
void func_805FF544(void);
void func_8063DA40(s32, s32);
s32 func_806F8AD4(s32, s32);
void hudSpawnTextScreen(s32);
s32 playerStateQueueCallback(s32, s32, s32);
void spawnNodeSpawnById(s16, s32, s32, s32, s32, s32, s32);
f32 func_80612794(s16);
s32 func_807142D8(void);

void func_80028440(void) {
    s32 pad70[2];
    u8 *sp6C;
    u8 *sp68;
    s32 count;
    u8 *sp60;
    u8 *temp_s1;
    u8 *temp_s0;
    u32 temp_v0_2;
    f32 temp_fv0;
    s32 var_a0;
    s32 var_s0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 pad38[1];
    s32 cam;
    s32 var_v1;
    s32 pad30;

    temp_s1 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    temp_s0 = *(u8 **)((u8 *)D_807FBB40 + 0x17C);
    sp6C = *(u8 **)((u8 *)D_807FBB40 + 0x180);
    sp68 = *(u8 **)((u8 *)D_807FBB40 + 0x184);
    sp60 = *(u8 **)(temp_s1 + 0x30);
    behaviourFrameBegin();
    if (!(*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x10)) {
        count = (D_807F5FD4[temp_s0[0] + 1] - D_807F5FD4[temp_s0[0]]) / 12;
        *(u8 *)((u8 *)D_807FBB40 + 0x144) = 0x3C;
        *(s32 *)((u8 *)D_807FBB40 + 0x60) &= ~1;
        temp_s0[0] = temp_s0[1] = 2;
        *(f32 *)(sp68 + 0x14) = 0.0f;
        *(u16 *)(temp_s0 + 2) = raceGetPrevWaypointIndex(count, 0);
        sp68[0x10] = 1;
        func_8002DE78(sp68, 5, D_8002FBD0, D_8002FC00);
        temp_s1[0x34] = 0;
        if ((flagGet(0x12, 2) == 0) && (flagGet(0x8B, 0) == 0) && (func_807142D8() == 0)) {
            camStartPath(D_807FBB40, 0, 1);
            flagSet(0x12, 1, 2);
        } else {
            temp_s1[0x35] = 3;
        }
        currentActorClearFlag();
        D_80750AC8 = 0xA;
        actorClearNodeFlag(D_807FBB40, 4);
    }
    if (D_807FBD70 == 4) {
        func_800280E8(temp_s0);
    } else if (D_807FBD70 == 5) {
        temp_s0[0x39] = 0x1E;
        *(f32 *)(temp_s0 + 0x20) = 0.0f;
    }
    if (*sp6C != 0) {
        *sp6C = *sp6C - 1;
    }
    temp_v0_2 = temp_s0[0x39];
    if (temp_v0_2 != 0) {
        temp_fv0 = (f32)temp_v0_2;
        if (temp_fv0 > 10.0f) {
            *(f32 *)(temp_s0 + 0x20) = (temp_fv0 - 10.0f) * 204.8f;
        } else {
            *(f32 *)(temp_s0 + 0x20) = 0.0f;
        }
    } else {
        if ((temp_s1[0x34] >= 2) && (temp_s1[0x34] < 4)) {
            func_80027CE8();
        }
    }
    if (temp_s1[0x34] == 1) {
        func_800282D8();
    }
    if (temp_s1[0x34] < 5) {
        func_80026354(temp_s0, temp_s1, 1);
        *(f32 *)((u8 *)D_807FBB40 + 0x80) += 50.0f * func_80612794((s16)(s32)(*(f32 *)(temp_s0 + 0x20) * 0.5f));
    } else {
        *(f32 *)((u8 *)D_807FBB40 + 0xB8) = 0.0f;
    }
    func_800283D4(*(f32 *)((u8 *)D_807FBB40 + 0xB8));
    if (temp_s1[0x34] == 0) {
        temp_v1_2 = temp_s1[0x35];
        var_a0 = temp_v1_2;
        switch (temp_v1_2) {
        case 0:
            if (*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x02000000) {
                temp_s1[0x35] = temp_s1[0x35] + 1;
                var_a0 = temp_s1[0x35];
            }
            break;
        case 1:
            if (!(*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x02000000)) {
                camResumePath();
                temp_s1[0x35] = temp_s1[0x35] + 1;
                var_a0 = temp_s1[0x35];
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                temp_s1[0x35] = temp_s1[0x35] + 1;
            }
            var_a0 = temp_s1[0x35];
            break;
        }
        if (var_a0 < 3) {
            func_8002D72C(sp60);
        } else {
            func_8002D754(sp60);
            var_s0 = 2;
            do {
                spawnNodeSpawnById(var_s0, 0, 0, 0, 0, 0, 0);
                var_s0 += 1;
            } while (var_s0 != 7);
        }
    } else if (temp_s1[0x34] == 4) {
        if (temp_s1[0x35] == 0) {
            if (flagGet(0x8B, 0) == 0) {
                cam = D_8002FC0C[func_8002E8EC(temp_s1, *(void **)(sp68 + 4), 0xA)];
                camStartPath(D_807FBB40, cam, 1);
                currentActorClearFlag();
            } else {
                func_805FF544();
            }
            temp_s1[0x35] = temp_s1[0x35] + 1;
        }
    } else if (temp_s1[0x34] == 5) {
        temp_v1_3 = temp_s1[0x35];
        switch (temp_v1_3) {
        case 0:
            if (flagGet(0x8B, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                var_s0 = 0;
                *(s16 *)((u8 *)D_807FBB40 + 0xE4) = 0;
                var_v1 = 0;
                *(s16 *)((u8 *)D_807FBB40 + 0xE8) = 0;
                do {
                    if (*(s16 *)((u8 *)D_807FBB40 + var_v1 + 0x6E) != -1) {
                        sfxStopSlotSound(D_807FBB40, var_s0 & 0xFF);
                    }
                    var_s0 += 1;
                    var_v1 += 2;
                } while (var_s0 != 2);
            }
            temp_s1[0x35] = temp_s1[0x35] + 1;
            break;
        case 1:
            if (*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x02000000) {
                temp_s1[0x35] = temp_s1[0x35] + 1;
            }
            break;
        case 2:
            if (!(*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x02000000)) {
                camResumePath();
                if ((temp_s1[0x36] == 0) || (func_806F8AD4(0xB, 0) < 0xA)) {
                    temp_s1[0x35] = 3;
                }
                temp_s1[0x35] = temp_s1[0x35] + 1;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                func_8063DA40(0x62, 0xA);
                temp_s1[0x35] = temp_s1[0x35] + 1;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (flagGet(0x8B, 0) != 0) {
                    func_805FF544();
                } else {
                    hudSpawnTextScreen(1);
                }
                temp_s1[0x35] = temp_s1[0x35] + 1;
            }
            break;
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
