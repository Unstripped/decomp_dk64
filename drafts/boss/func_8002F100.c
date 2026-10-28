// func_8002F100 (src/boss/B100.c): stage 6 (unchanged, 4 exact diff lines: slti v0 first vs slti at after addiu). Pass 4 sweep (~150 variants): if (TIMER_STATE->unk2C-- < 4) reproduces the exact slti v0/addiu/beqz/sh order (cmp becomes a real candidate) but shifts coloring: switch temp cand 43 v0->v1, t (cand121) a0->v0, ptr v1->a0, load a0->a1 (116 diff lines). Compensation tried without effect: local decl permutations (24), case1/case4 forms (fld/dec/--), t as s32/u16, extra t2 local replacing pad, nov forms for case3 head/else-if, (t=unk2C--)<4 (cmp after store -> slti at), c=t<4 locals (folds to at), comma/|/+ compare forms, inverted if arms.
typedef struct BossPhaseState {
    u8 pad0[0x14];
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 pad17[1];
    u8 unk18;
} BossPhaseState;

typedef struct BossMainActor {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xCC - 0xBC];
    u8 unkCC;
    u8 padCD[0xE6 - 0xCD];
    s16 unkE6;
    u8 padE8[0x11C - 0xE8];
    void *unk11C;
    u8 pad120[0x132 - 0x120];
    s16 unk132;
    u8 pad134[0x144 - 0x134];
    u8 unk144;
    u8 pad145[1];
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x168 - 0x156];
    s16 unk168;
    u8 pad16A[0x178 - 0x16A];
    BossPhaseState *unk178;
} BossMainActor;

typedef struct BossTimerState {
    u8 pad0[0x2C];
    s16 unk2C;
} BossTimerState;

typedef struct BossGlobalC924 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} BossGlobalC924;

typedef struct BossWaypoint {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[4];
} BossWaypoint;

typedef struct BossWaypointList {
    u8 pad0[0x14];
    BossWaypoint *unk14;
} BossWaypointList;

typedef struct BossConfig {
    u8 pad0[0xC];
    u8 unkC;
} BossConfig;

extern u8 *D_80035A90[];
extern void *D_807FBB4C;
extern BossGlobalC924 *D_807FC924;
extern void *D_807FDC90;
extern BossConfig *D_807FDC9C;
extern BossWaypointList *D_807FDCA0;
extern void *gCamActor;

void behaviourFrameBegin(void);
void func_8070B308(s32);
void camSetSecondTarget(void *, s32, s32);
void func_80724CA4(s32, s32);
s32 flagGet(s32, s32);
void zoneEntryGetPosition(s32, s32, void *, void *, void *);
void bossRoundFrame(u8 *);
void camStartPath(void *, s32, u8);
void func_806A2B38(void *);
void func_805FF158(s32);
void func_805FF378(s32, s32);
f32 func_80612790(s16);
void func_806F3BEC(void *, s16, s16, s32);
void func_80641874(s32, s32);
void func_806D0468(void *, s32);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void actorSetTargetSpeed(void *, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s16 func_806CC190(s16, s16, f32);
s32 projectileSpawnWithShockwave(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_80613C48(void *, s32, f32, f32);
void func_80614D00(void *, f32, f32);
s32 currentActorTestClearFlag(void);
s32 bossScriptStep(u8 *, s32, f32);
void func_8072A450(void);
s32 func_8072881C(s32, void *);

#define MAIN_ACTOR ((BossMainActor *)D_807FBB40)
#define PLAYER_ACTOR ((BossMainActor *)D_807FBB4C)
#define SECOND_ACTOR ((BossMainActor *)D_807FBB44)
#define TIMER_STATE ((BossTimerState *)D_807FDC90)

void func_8002F100(void) {
    BossPhaseState *sp4C;
    u8 *sp48;
    s16 t;
    s32 pad[1];
    f32 sp3C;

    sp4C = MAIN_ACTOR->unk178;
    behaviourFrameBegin();
    if (!(MAIN_ACTOR->unk60 & 0x10)) {
        MAIN_ACTOR->unk132 = 8;
        func_8070B308(0);
        camSetSecondTarget(gCamActor, 0, 0);
        MAIN_ACTOR->unk146 = 5;
        MAIN_ACTOR->unkCC = 1;
        func_80724CA4(2, 1);
        MAIN_ACTOR->unk154 = 0x1E;
        MAIN_ACTOR->unk155 = 0;
        if (flagGet(0x54, 2) != 0) {
            sp4C->unk14 = 4;
            MAIN_ACTOR->unk154 = 0x37;
            MAIN_ACTOR->unk155 = 0;
        } else if (flagGet(0x53, 2) != 0) {
            sp4C->unk14 = 3;
        } else if (flagGet(0x52, 2) != 0) {
            sp4C->unk14 = 2;
        } else if (flagGet(0x51, 2) != 0) {
            sp4C->unk14 = 1;
        }
        if (sp4C->unk14 != 0 && MAIN_ACTOR->unk154 != 0x37) {
            MAIN_ACTOR->unk154 = 0x31;
            MAIN_ACTOR->unk155 = 0;
            zoneEntryGetPosition(1, 0, &MAIN_ACTOR->unk7C, &MAIN_ACTOR->unk80, &MAIN_ACTOR->unk84);
        }
    }
    sp48 = D_80035A90[sp4C->unk14];
    bossRoundFrame(sp48);
    switch (MAIN_ACTOR->unk154) {
    case 0x28:
        if (D_807FBD70 == 5 && D_807FC924->unk2C0 != 1) {
            MAIN_ACTOR->unk144 = 1;
            PLAYER_ACTOR->unk144 = 1;
            camStartPath(0, 2, 1);
            MAIN_ACTOR->unk154 = 0x29;
            func_806A2B38(MAIN_ACTOR->unk11C);
            func_805FF158(1);
            func_8070B308(1);
            func_805FF378(0xD6, 0);
            PLAYER_ACTOR->unk7C = func_80612794(MAIN_ACTOR->unkE6 + 0x320) * 30.0 + MAIN_ACTOR->unk7C;
            PLAYER_ACTOR->unk84 = func_80612790(MAIN_ACTOR->unkE6 + 0x320) * 30.0 + MAIN_ACTOR->unk84;
            sp3C = func_80612794(MAIN_ACTOR->unkE6 + 0x384);
            func_806F3BEC(PLAYER_ACTOR, (s32)(sp3C * 15.0f + MAIN_ACTOR->unk7C), (s32)(func_80612790(MAIN_ACTOR->unkE6 + 0x384) * 15.0f + MAIN_ACTOR->unk84), 0x50);
        } else {
            switch (MAIN_ACTOR->unk155) {
            case 0:
                if (sp4C->unk16 != 0) {
                    func_80641874(0, 0);
                }
                actorScriptStart(MAIN_ACTOR, 0x3FF);
                TIMER_STATE->unk2C = sp48[sp4C->unk15] * 0x1E;
                sp4C->unk15++;
                MAIN_ACTOR->unk155++;
                break;
            case 1:
                t = TIMER_STATE->unk2C;
                if (t != 0) {
                    TIMER_STATE->unk2C = t - 1;
                } else {
                    actorScriptStart(MAIN_ACTOR, 0x400);
                    MAIN_ACTOR->unk155++;
                }
                break;
            case 3:
                if (D_807FC924->unk2C0 != 1) {
                    func_806D0468(PLAYER_ACTOR, 1);
                }
                func_80641874(0, 0xFF);
                actorScriptStart(MAIN_ACTOR, 0x3E4);
                MAIN_ACTOR->unk154 = sp48[sp4C->unk15];
                sp4C->unk15++;
                MAIN_ACTOR->unk155 = 0;
                break;
            }
        }
        break;
    case 0x27:
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4310, 0.0f);
        switch (MAIN_ACTOR->unk155) {
        case 0:
            actorSetTargetSpeed(MAIN_ACTOR, 0);
            sp4C->unk18 = sp48[sp4C->unk15];
            sp4C->unk15++;
            MAIN_ACTOR->unk155++;
            /* fallthrough */
        case 1:
            TIMER_STATE->unk2C = 4;
            actorScriptStart(MAIN_ACTOR, 0x3E7);
            MAIN_ACTOR->unk155++;
            break;
        case 2:
            MAIN_ACTOR->unkE6 = func_806CC190(MAIN_ACTOR->unkE6, mathAngleBetweenPoints2D((f32)D_807FDCA0->unk14->unk0, (f32)D_807FDCA0->unk14->unk4, MAIN_ACTOR->unk7C, MAIN_ACTOR->unk84), 10.0f);
            break;
        case 3:
            t = TIMER_STATE->unk2C;
            if (t != 0 && (u32)D_8076A064 % 5 == 0) {
                projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 150, 3, (f32)((f64)(u32)sp4C->unk14 * 0.01 + 1.04), 0.0f, 0.0f, 0.0f);
                t = TIMER_STATE->unk2C;
                TIMER_STATE->unk2C = t - 1;
                if (t < 4) {
                    SECOND_ACTOR->unk168 = 0;
                } else {
                    func_806086CC(MAIN_ACTOR->unk7C, MAIN_ACTOR->unk80, MAIN_ACTOR->unk84, 0x25A, 0xFF, 0x7F, 1, 0, 0.3f, 0);
                }
                func_80613C48(SECOND_ACTOR, 0x4F9, 0.0f, 0.0f);
                func_80614D00(SECOND_ACTOR, 0.5f, 0.0f);
            } else if (t == 0) {
                TIMER_STATE->unk2C = sp4C->unk18;
                MAIN_ACTOR->unk155++;
            }
            break;
        case 4:
            t = TIMER_STATE->unk2C;
            if (t != 0) {
                TIMER_STATE->unk2C = t - 1;
            } else {
                actorSetTargetSpeed(MAIN_ACTOR, D_807FDC9C->unkC);
                actorScriptStart(MAIN_ACTOR, 0x3E4);
                MAIN_ACTOR->unk154 = sp48[sp4C->unk15];
                sp4C->unk15++;
                MAIN_ACTOR->unk155 = 0;
            }
            break;
        }
        break;
    case 0x1E:
        sp4C->unk14 = 0;
        sp4C->unk15 = 0;
        MAIN_ACTOR->unk154 = sp48[sp4C->unk15];
        sp4C->unk15++;
        MAIN_ACTOR->unk155 = 0;
        MAIN_ACTOR->unkB8 = (f32)(u32)D_807FDC9C->unkC;
        break;
    case 0:
        switch (MAIN_ACTOR->unk155) {
        case 0:
            actorScriptStart(MAIN_ACTOR, 0x3EA);
            MAIN_ACTOR->unk155++;
            break;
        case 2:
            MAIN_ACTOR->unk154 = sp48[sp4C->unk15];
            sp4C->unk15++;
            MAIN_ACTOR->unk155 = 0;
            break;
        }
        break;
    case 0x31:
        switch (MAIN_ACTOR->unk155) {
        case 0:
            func_806D0468(PLAYER_ACTOR, 0);
            func_806D0468(PLAYER_ACTOR, 1);
            camStartPath(MAIN_ACTOR, 1, 1);
            actorScriptStart(MAIN_ACTOR, 0x3FB);
            MAIN_ACTOR->unk155++;
            break;
        case 2:
            actorScriptStart(MAIN_ACTOR, 0x3E4);
            MAIN_ACTOR->unk154 = sp48[sp4C->unk15];
            sp4C->unk15++;
            MAIN_ACTOR->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (MAIN_ACTOR->unk155) {
        case 0:
            actorScriptStart(MAIN_ACTOR, 0);
            camStartPath(MAIN_ACTOR, 0x15, 1);
            MAIN_ACTOR->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                func_805FF158(0);
                func_805FF378(0xCF, 0);
                MAIN_ACTOR->unk155++;
            }
            break;
        }
        break;
    default:
        bossScriptStep(sp48, 0x10, 0.0f);
        break;
    }
    func_8072A450();
    if (func_8072881C(0, (u8 *)D_807FDC90 + 0x28) != 0) {
        func_8072881C(0x81, (u8 *)D_807FDC90 + 0x28);
    }
    actorUpdateModelMatrix(MAIN_ACTOR, 0);
}
