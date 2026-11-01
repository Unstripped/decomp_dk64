// func_8068F72C (src/global/936B0.c): func_8068F72C (src/global/936B0.c): stage 5 parked NON_MATCHING (R3c): score 177->159 by naming the first unkB8 reload in the fv0 chain with the dead local sp40 (FP webs now match: sp50 f12, 0.0 const f14, first web f2, second f0). Left: t-ring phase from the arg3 block (target fl loads t2,t3 vs mine t0,t1), sp48 narrowing chain (target mfc1 t9/andi t8/sll t0/sra v0 pure ring temps; mine mfc1 v0 because uopt splits sp48 (cand 17) into v0 pieces for each chain node), and sp58==2 -> sp48 -0x1E/-0x28 wants if/else shape (bne;li -40;b;li -30) but if/else/ternary/other-local variants all score worse (+3 insns). Tried: callee return widths (s16/s32 for mathAngleSignedDistance/190: same), later sp48 var swapped to sp34/temp_v0/sp4A, mask/cast injection sweep on every assignment, dead-use sweeps (sp48/sp4A/sp58/args).
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
        if (sp48) {} // FAKE: extra ref lets uopt colour sp48 (v0) across the arg3 block
        sp48 = (s32)((f32)sp48 + sp50 * 200.0f) & 0xFFF;
        if (fl[3] != 0 || fl[2] != 0) {
            if (ACTOR_MOVE_VIEW->unkE8) {} // FAKE: hoists the unkE8 load to the arm start
            sp4A = (s32)((f64)sp4A + ((f64)(S->unk4 * -50.0f) + (f64)ACTOR_MOVE_VIEW->unkB8 * -0.5)) & 0xFFF;
        } else {
            if (ACTOR_MOVE_VIEW->unkE8) {} // FAKE: hoists the unkE8 load to the arm start
            sp4A = ACTOR_MOVE_VIEW->unkE8;
        }
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
    sp48 = -0x28;
    if (sp58 == 2) {
        sp48 = -0x1E;
    }
    S->unk0 = (s32)((f64)S->unk0 + (f64)(sp50 * (f32)sp48) * (1.0 + (f64)fv0 * 0.05));
    S->unk0 = S->unk0 & 0xFFF;
    if (arg2) {
        fa0 = ACTOR_MOVE_VIEW->unk80;
        if (sp48) {} // FAKE: extra ref reshapes the FP/ang candidates in the arg2 block
        fv0 = ACTOR_MOVE_VIEW->unkAC;
        if (fa0 < fv0) {
            ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC0 + ((fv0 - fa0) * 3.0f + 15.0f);
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
                if (sp58) {} // FAKE: extra ref keeps sp58 in a0 (not reloaded)
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
    if (fl[2] != 0 && !(ACTOR_MOVE_VIEW->unk6C & 1)) {
        ACTOR_MOVE_VIEW->unkC0 = -10.0f;
    }
    ACTOR_MOVE_VIEW->unkE6 = (S->unk0 + S->unk2) & 0xFFF;
}
#undef S
