// func_8068F72C (src/global/936B0.c): MidB R5: stage 5 parked, deadsweep score 70->28 (558 insns = expected). Left: sp48 narrowing chain in arg3 block (target mfc1 t9/andi t8/sll t0/sra v0 ring temps, mine mfc1 v0 + t6/t9: uopt splits sp48 per chain node), t-ring phase t2,t3 vs t0,t1 (lbu 47/46 after it), f2 vs f0 for unkAC load in !arg2 block, lui+lw D_807FBB40 vs lw s0,0(s1) at the tail (dead D_807FBB40 test at end needed: without it +3 insns). sp58==2 now if/else with sp48 -0x28 in else (+dead sp48&&sp48). Tried: s32/u16/s16 extra locals for narrowing chain, 85 spellings of the chain (casts, | 0, ^0, temps, split stmts), sp48 temp swaps (temp_v0/sp34/sp4A), if/else/ternary shapes, local for unkAC in arg2/!arg2 blocks (sp38/sp40/sp54/fa0), self-assign grid, 3 hill-climbs (~80k compiles) with frame/size weighting. | R5 W4Mid (no gain, still 28): 3 x 800 s anneals (35k evals each; dead tests/self-assigns/|0 over sp48/sp4A/sp58/arg2/arg3/fl[]/pl/arg1, cost full+6|n|+0.3 fakes+0.5 shape) never beat start; remaining diff unchanged (sp48 chain mfc1/andi/sll/sra ring t9,t8,t0 vs v0,t6,t9; fl lbu t2,t3 vs t0,t1; sp4A else-arm sll/sra/move vs target plain 'sh a0,74(sp)' + 'lh a1,74(sp)' reload = sp4A memory-resident not a candidate; f2 vs f0; lui+lw D_807FBB40 vs lw s0,0(s1)).
typedef struct ActorMoveState {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0x27 - 0x14];
    u8 unk27;
    u8 unk28;
    u8 pad29[0x34 - 0x29];
    u8 unk34;
    u8 unk35;
} ActorMoveState;

typedef struct ActorMoveStepFlag {
    u8 pad0[4];
    u8 unk4;
} ActorMoveStepFlag;

typedef struct PlayerActorRef {
    u8 pad0[4];
    Actor *actor;
    u8 pad8[0x2F0 - 8];
} PlayerActorRef;

typedef struct ActorMoveView {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[4];
    u32 unk60;
    u8 pad64[6];
    u16 unk6A;
    u16 unk6C;
    u8 pad6E[0x80 - 0x6E];
    f32 unk80;
    u8 pad84[0xAC - 0x84];
    f32 unkAC;
    u8 padB0[0xB8 - 0xB0];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0xDC - 0xCC];
    s16 unkDC;
    s16 unkDE;
    u8 padE0[4];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[4];
    s16 unkEE;
    u8 padF0[8];
    s16 unkF8;
    u8 padFA[0x144 - 0xFA];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
} ActorMoveView;

#define ACTOR_MOVE_VIEW ((ActorMoveView *)D_807FBB40)

extern s16 D_8075033C;
extern u32 D_807FBB64;
extern struct PlayerTrackEntry *gPlayerSlots;
f32 func_80612790(s16);
f32 func_80612794(s16);
s32 mathAngleSignedDistance(s16, s16);
s16 mathAngleEaseToward(s16, s16, f32);
void actorStepPhysics(Actor *, s16, s16);
void actorApplyVelocity(Actor *);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void func_8002F490(void *);

#define S ((ActorMoveState *)arg0)

void func_8068F72C(arg0, arg1, arg2, arg3)
void *arg0;
s32 arg1;
u8 arg2;
u8 arg3;
{
    f32 fa0;
    s32 sp58;
    f32 sp54;
    f32 sp50;
    f32 fv0;
    s16 sp4A;
    s16 sp48;
    u8 fl[4];
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s16 temp_v0;
    s16 sp34;
    ActorMoveView *pl;

    pl = (ActorMoveView *)((PlayerActorRef *)gPlayerSlots)[S->unk28].actor;
    sp58 = pl->unk58;
    sp4A = 0;
    sp48 = 0;
    fl[3] = ACTOR_MOVE_VIEW->unk80 <= ACTOR_MOVE_VIEW->unkAC + 1.0f;
    fl[2] = ACTOR_MOVE_VIEW->unk6A & 1;
    if (!(ACTOR_MOVE_VIEW->unk60 & 0x10)) {
        ACTOR_MOVE_VIEW->unk60 |= 0x10400;
        ACTOR_MOVE_VIEW->unk154 = 0;
        ACTOR_MOVE_VIEW->unk155 = 0;
        ACTOR_MOVE_VIEW->unkB8 = 0.0f;
        S->unk34 = 0;
        S->unk35 = 0;
        if (S->unk27 == 0) {
            ACTOR_MOVE_VIEW->unk144 = 0x3C;
            ACTOR_MOVE_VIEW->unkC4 = -20.0f;
        } else {
            ACTOR_MOVE_VIEW->unk144 |= 0x18;
            ACTOR_MOVE_VIEW->unkC4 = -30.0f;
        }
        ACTOR_MOVE_VIEW->unkC8 = -900.0f;
        ACTOR_MOVE_VIEW->unkF8 = 0x12C;
    }
    sp40 = func_80612794(ACTOR_MOVE_VIEW->unkEE) * ACTOR_MOVE_VIEW->unkB8;
    sp3C = func_80612790(ACTOR_MOVE_VIEW->unkEE) * ACTOR_MOVE_VIEW->unkB8;
    if (fl[3] != 0) {
        sp38 = S->unk4 * 50.0f;
        if (sp58 == 2) {
            fa0 = 5000.0f;
        } else {
            fa0 = 10000.0f;
        }
        sp54 = 1.0f / fa0 * (ACTOR_MOVE_VIEW->unkB8 * ACTOR_MOVE_VIEW->unkB8) + S->unk8;
        if (S->unk4 != 0.0f) {
            sp54 = sp54 + 30.0f;
        } else {
            sp54 = sp54 + 3.0f;
        }
    } else {
        fv0 = 2.0f;
        if (fl[2] != 0) {
            sp38 = S->unk4 * 4.0f;
            sp54 = S->unk8 + ACTOR_MOVE_VIEW->unkB8 * ACTOR_MOVE_VIEW->unkB8 * 0.00002f + fv0;
        } else {
            sp38 = S->unk4 * fv0;
            sp54 = S->unk8 + ACTOR_MOVE_VIEW->unkB8 * ACTOR_MOVE_VIEW->unkB8 * 0.00002f + fv0;
        }
    }
    sp40 += func_80612794(S->unk0) * sp38;
    sp3C += func_80612790(S->unk0) * sp38;
    ACTOR_MOVE_VIEW->unkB8 = sqrtf(sp40 * sp40 + sp3C * sp3C);
    ACTOR_MOVE_VIEW->unkEE = (s16)(s32)(func_80611BB4(sp40, sp3C) * 4096.0 / 6.2831854820251465);
    if (fl[2] != 0) {
        sp34 = 0x400 - ACTOR_MOVE_VIEW->unkDE;
        temp_v0 = mathAngleSignedDistance(ACTOR_MOVE_VIEW->unkDC, S->unk0);
        fv0 = (f32)sp34;
        sp4A = (s16)(s32)(func_80612790(temp_v0) * fv0);
        sp48 = (s16)(s32)(func_80612794(temp_v0) * fv0);
    } else if (!arg3) {
        ACTOR_MOVE_VIEW->unkE8 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE8, 0, 4.0f);
        ACTOR_MOVE_VIEW->unkE4 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE4, 0, 5.0f);
    }
    sp50 = S->unk10 * S->unkC;
    if (arg3) {
        sp48 = (s32)((f32)sp48 + sp50 * 200.0f) & 0xFFF;
        if (fl[3] != 0 || fl[2] != 0) {
            if (ACTOR_MOVE_VIEW->unkE8) {} // FAKE: hoists the unkE8 load to the arm start
            sp4A = (s32)((f64)sp4A + ((f64)(S->unk4 * -50.0f) + (f64)ACTOR_MOVE_VIEW->unkB8 * -0.5)) & 0xFFF;
        } else {
            sp4A = ACTOR_MOVE_VIEW->unkE8;
        }
        if (!sp4A) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        ACTOR_MOVE_VIEW->unkE8 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE8, sp4A, 4.0f);
        ACTOR_MOVE_VIEW->unkE4 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE4, sp48, 5.0f);
    }
    ACTOR_MOVE_VIEW->unkB8 = ACTOR_MOVE_VIEW->unkB8 - sp54;
    sp40 = ACTOR_MOVE_VIEW->unkB8;
    if (sp40 < 0.0f) {
        ACTOR_MOVE_VIEW->unkB8 = 0.0f;
        sp40 = ACTOR_MOVE_VIEW->unkB8;
    }
    fv0 = sp40 - ACTOR_MOVE_VIEW->unkBC;
    if (fv0 < 0.0f) {
        fv0 = 0.0f;
    }
    if (sp58 == 2) {
        sp48 = -0x1E;
    } else {
        if (sp48 && sp48) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        sp48 = -0x28;
    }
    S->unk0 = (s32)((f64)S->unk0 + (f64)(sp50 * (f32)sp48) * (1.0 + (f64)fv0 * 0.05));
    S->unk0 = S->unk0 & 0xFFF;
    if (arg2) {
        fa0 = ACTOR_MOVE_VIEW->unk80;
        sp54 = ACTOR_MOVE_VIEW->unkAC;
        if (fa0 < sp54) {
            if (fl[3] != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC0 + ((sp54 - fa0) * 3.0f + 15.0f);
            fv0 = ACTOR_MOVE_VIEW->unkC0;
            if (fv0 > 0.0f) {
                fa0 = fv0;
            } else {
                fa0 = -fv0;
            }
            if (fa0 > 20.0f) {
                ACTOR_MOVE_VIEW->unkC0 = fv0 - fv0 / 12.0f;
            }
        }
    }
    ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC0 + ACTOR_MOVE_VIEW->unkC4;
    if (((ActorMoveStepFlag *)arg1)->unk4 != 0) {
        ((ActorMoveStepFlag *)arg1)->unk4 = 0;
        if (fl[3] != 0) {
            if (sp58 == 2) {
                ACTOR_MOVE_VIEW->unkC0 = 200.0f;
            } else {
                ACTOR_MOVE_VIEW->unkC0 = (f32)D_8075033C;
            }
        } else if (fl[2] != 0) {
            ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC0 + 200.0f;
        }
    }
    fv0 = ACTOR_MOVE_VIEW->unkC8;
    if (ACTOR_MOVE_VIEW->unkC0 < fv0) {
        ACTOR_MOVE_VIEW->unkC0 = fv0;
    }
    if (sp58 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    actorStepPhysics(D_807FBB40, ACTOR_MOVE_VIEW->unkE6, S->unk0);
    actorApplyVelocity(D_807FBB40);
    actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
    if (!arg2) {
        if (ACTOR_MOVE_VIEW->unk80 < ACTOR_MOVE_VIEW->unkAC) {
            ACTOR_MOVE_VIEW->unk80 = ACTOR_MOVE_VIEW->unkAC;
            ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC4;
        }
    }
    if (D_807FBB64 & 0x2000) {
        func_8002F490(arg0);
    }
    if (D_807FBB40 && D_807FBB40) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (fl[2] != 0 && !(ACTOR_MOVE_VIEW->unk6C & 1)) {
        ACTOR_MOVE_VIEW->unkC0 = -10.0f;
    }
    ACTOR_MOVE_VIEW->unkE6 = (S->unk0 + S->unk2) & 0xFFF;
}
#undef S
