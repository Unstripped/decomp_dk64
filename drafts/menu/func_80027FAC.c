// func_80027FAC (src/menu/3E10.c): func_80027FAC (src/menu/3E10.c): stage 5 (QMenu round 2, parked NON_MATCHING): frame 0x60, no callee-saved, masked-register diff ~32 lines of 455 (was ~74). KEY FIX: the 4/5-way id test is a SWITCH (case -2,-3,-4,-5 written in descending order so bodies lay out -2,-3,-4,-5 with the beq chain -5..-2 and separate 'b' tails per arm); default holds the '< -5' / '>= 0' / random arms. Value local must be 'int cur = *var_a0' (s16 cur -> spilled sh/lh 54(sp); camStartPath(0, cur, 1) as the call arg keeps cur out of a1: use cur for switch + '<-5' + '>=0' tests but '*var_a0' for 'var_a1 = -6 - *var_a0' hoist and the camStartPath arg). Decl order var_a1,var_v0,temp_t2,var_a0_2 puts var_a0_2 home at 60(sp). Remaining: (1) 'move a2,a1' selector copy after the first beq (target has the switch value and compare value in ONE a1 web), (2) var_a1 home 70(sp) vs 64, (3) start-of-function t5/t6 ring shift (struct copy w1 temp t5 vs t6; decrement t6 vs t5) so ~190 text lines differ in register names only, (4) lh 2(a0) arm loads scheduled one slot late. deadsweep (locals via --forms): 'if (var_a1 && var_a1) {}' after the 2nd 'do {' (201->153), 'if (var_a1 == 0) {}' after 'if (var_a0_2 == temp_t2) {' (->126), 'if (sp4F == 0) {}' after 'D_80033F56 = 1;' (->101) cut text diff but are fakes; not applied. Arrays as deadsweep targets (if (D_800336A4) {}) emit code: rejected.
typedef struct {
    s32 unk0;
    s32 unk4;
} MenuL1b_Pair;

typedef struct {
    f32 unk0;
    f32 unk4;
    char pad8[0xB];
    s8 unk13;
    char pad14[2];
    s8 unk16;
    s8 unk17;
} MenuL1b_S174;

extern s16 D_800336A0;
extern s16 D_800336A4[];
extern s16 D_80033724[];
extern s8 D_800337F0;
extern s8 D_800337F4;
extern MenuL1b_Pair D_800337FC;
extern f32 D_80033F3C;
extern f32 D_80033F40;
extern s16 D_80033F52;
extern s8 D_80033F54;
extern s8 D_80033F55;
extern s8 D_80033F56;
extern f32 D_80033F58;
extern f32 D_80033F5C;
extern s8 D_8076A0D2;

void actorFindActiveByType(s32, s32 *);
void actorScriptStart(void *, s32);
s32 camIsCutsceneActive();
void camStartPath(void *, s32, s32);
s32 flagGet(s16, u8);
s32 randomLcgNext();
f32 randomFloat();
void func_8067AB20(s32, s32, s32, s32, void *, s32);
void gfxSetBackgroundBlend(f32);
void lightSetColor(f32, f32, f32, s32);
void menuHandleScrollInput();
void menuUpdateItemTransition(void *, MenuScreenState *, s32);
void menuUpdateScrollAnimation();
void spawnNodesSetActorStateByFlag(s32, s32);

void func_80027FAC(void *arg0, s32 arg1) {
    MenuL1b_S174 *var_a3;
    MenuL1b_Pair sp54;
    s32 sp50;
    s8 sp4F;
    s16 *var_a0;
    s16 var_a1;
    s32 var_v0;
    s16 temp_t2;
    s16 var_a0_2;
    int cur;
    f32 var_ft4;

    var_a3 = *(MenuL1b_S174 **)((u8 *)arg0 + 0x174);
    sp54 = D_800337FC;
    sp4F = 0;
    if (D_800337F4 > 0) {
        D_800337F4 -= 1;
    } else {
        D_800337F4 = 0;
    }
    D_800337F0 = 0;
    if (var_a3->unk0 == 0.0f && D_80033F3C == 0.0f && D_800337F4 == 0) {
        if (var_a3->unk4 == 0.0f) {
            D_800337F0 = 1;
            switch (var_a3->unk17) {
            case 2:
                if (flagGet(0x1C, 1) == 0) {
                    D_800337F0 = -1;
                }
                break;
            case 3:
                if (flagGet(0, 1) == 0) {
                    D_800337F0 = -1;
                }
                break;
            }
            menuHandleScrollInput(var_a3, 5, arg1);
        }
        menuUpdateScrollAnimation(var_a3, 5);
    }
    D_8076A0D2 = 0;
    if (D_80033F40 != 0.0f) {
        D_80033F3C += D_80033F40;
        if (D_80033F3C > 1.0f) {
            D_80033F3C = 1.0f;
            var_a3->unk16 = 0;
            switch (var_a3->unk17) {
            default:
                var_a3->unk13 = 2;
                break;
            case 1:
                var_a3->unk13 = 8;
                break;
            case 2:
                var_a3->unk13 = 6;
                break;
            case 3:
                var_a3->unk13 = 0xA;
                break;
            case 4:
                var_a3->unk13 = 9;
                break;
            }
            if (camIsCutsceneActive() != 0) {
                camEndPath(gCamActor);
            }
            spawnNodesSetActorStateByFlag(0x40, 0x3C);
            if (D_80033F55 != 0) {
                sp4F = -1;
            }
            D_80033F56 = 0;
        }
    }
    menuUpdateItemTransition(arg0, var_a3, 0);
    D_80033F52 -= 1;
    if (D_80033F52 <= 0) {
        var_a0 = &D_800336A4[D_80033F54];
        cur = *var_a0;
        switch (cur) {
        case -2:
            D_80033F54 += 2;
            sp4F = 1;
            D_80033F52 = var_a0[1];
            break;
        case -3:
            D_80033F54 += 2;
            sp4F = -1;
            D_80033F52 = var_a0[1];
            break;
        case -4:
            D_80033F54 += 2;
            D_80033F52 = var_a0[1];
            D_80033F56 = 1;
            break;
        case -5:
            D_80033F54 += 2;
            D_80033F52 = var_a0[1];
            D_80033F56 = 0;
            break;
        default:
        if (cur < -5) {
            var_a1 = -6 - *var_a0;
            if (D_800337F4 == 0) {
                actorScriptStart(D_807FBB4C, D_80033724[(s16)var_a1]);
                var_a0 = &D_800336A4[D_80033F54];
            }
            D_80033F54 += 2;
            D_80033F52 = var_a0[1];
        } else if (cur >= 0) {
            camStartPath(0, cur, 1);
            D_80033F52 = D_800336A4[D_80033F54 + 1];
            D_80033F54 += 2;
        } else {
            var_a1 = 0;
            var_a0_2 = (s32)(randomFloat(0) * 10.0f);
            D_80033F52 = (randomLcgNext() & 0x7F) + 0x12C;
            D_80033F54 = 0;
            if (var_a0_2 >= 0xB) {
                var_a0_2 = 0;
            }
            var_v0 = 1 << var_a0_2;
            temp_t2 = var_a0_2;
            if (D_800336A0 & var_v0) {
                do {
                    var_a0_2 += 1;
                    if (var_a0_2 == 0xB) {
                        var_a0_2 = 0;
                    }
                    var_v0 = 1 << var_a0_2;
                    if (var_a0_2 == temp_t2) {
                        D_800336A0 = 0;
                    }
                } while (D_800336A0 & var_v0);
            }
            D_800336A0 |= var_v0;
            if (var_a0_2 != 0) {
                do {
                    if (D_800336A4[D_80033F54] != -1) {
                        do {
                            D_80033F54 += 1;
                        } while (D_800336A4[D_80033F54] != -1);
                    }
                    var_a1 += 1;
                    D_80033F54 += 1;
                } while (var_a1 != var_a0_2);
            }
        }
        }
    }
    if (sp4F != 0) {
        actorFindActiveByType(0xC, &sp50);
        if (sp4F < 0) {
            D_80033F55 = 0;
            var_v0 = 2;
        } else {
            D_80033F55 = 1;
            var_v0 = 1;
        }
        func_8067AB20(gCamActor, sp50, 0x01000000, var_v0 & 0xFF, &sp54, 0);
    }
    if (D_80033F56 != 0) {
        var_ft4 = 0.0f;
        D_80033F5C += 0.005;
        if (D_80033F5C > 1.0) {
            D_80033F5C = 1;
        }
    } else {
        var_ft4 = 1;
        if (D_80033F5C > 0.0) {
            D_80033F5C -= 0.005;
        } else if (D_80033F55 != 0) {
            var_ft4 = 0.45f;
        }
    }
    D_80033F58 += (var_ft4 - D_80033F58) * 0.01;
    lightSetColor(D_80033F58 * 0.83 + 0.17, D_80033F58 * 0.8 + 0.2, D_80033F58 * 0.6 + 0.4, -1);
    gfxSetBackgroundBlend(D_80033F5C);
}
