#include "common.h"

s32 raceGetNextWaypointIndex(s32 arg0, s32 arg1) {
    s32 next = arg1 + 1;
    if (arg0 != next) {
        return arg1 + 1;
    }
    return 0;
}

s32 raceGetPrevWaypointIndex(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        return arg0 - 1;
    }
    return arg1 - 1;
}

typedef struct {
    f32 x, y, z;
} RaceAPoint3f;

struct RaceActor;

/* Per-participant checkpoint path state (RaceActor.unk178). */
typedef struct {
    u8 unk0;
    u8 unk1;
    u16 unk2;
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 pad11[3];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 pad2C[4];
    void *unk30;
    void *unk34;
    u8 pad38;
    u8 unk39;
    u8 pad3A[2];
} RacePathState;

/* Participant state (RaceActor.unk174). */
typedef struct {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x14];
    u16 unk1C;
    u8 pad1E[7];
    u8 unk25;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 pad2B;
    struct RaceActor *unk2C;
    struct RaceActor *unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    s8 unk37;
    u8 pad38[2];
    u16 unk3A;
    u8 pad3C[4];
    f32 unk40;
} RaceParticipant;

/* Auxiliary state (RaceActor.unk17C). */
typedef struct {
    u16 unk0;
    u8 pad2[6];
    s32 unk8;
    struct RaceActor *unkC;
} RaceAuxState;

typedef struct RaceActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0xA];
    s16 unk6E[2];
    u8 pad72[2];
    f32 unk74;
    u8 pad78[4];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    f32 unk88;
    u8 pad8C[4];
    f32 unk90;
    u8 pad94[0x24];
    f32 unkB8;
    u8 padBC[0x28];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[4];
    s16 unkEE;
    u8 padF0[0x54];
    u8 unk144;
    u8 pad145[0x2F];
    RaceParticipant *unk174;
    RacePathState *unk178;
    RaceAuxState *unk17C;
    u8 pad180[4];
    void *unk184;
} RaceActor;

typedef struct {
    RaceActor *actor;
    RaceParticipant *participant;
} RaceNodeLinks;

/* Effect node actor spawned by spawnNodeSpawnById. */
typedef struct {
    u8 pad0[0x178];
    RaceParticipant *unk178;
    RacePathState *unk17C;
    u8 pad180[4];
    RaceNodeLinks *unk184;
} RaceNodeActor;

extern RaceAPoint3f **D_807F5FD4;
extern RaceActor *D_807FBB40;
f32 func_80612794(s16);
s32 mathPickCloserTargetPoint3D(f32, f32, f32, RaceAPoint3f *, RaceAPoint3f *, RaceAPoint3f *, RaceAPoint3f *, f32 *, f32 *, f32 *);

void func_800257A4(RacePathState *arg0, f32 *arg1, f32 *arg2, s32 arg3, s32 arg4) {
    s32 padA;
    s32 padB;
    RaceAPoint3f *points;
    s32 i;
    f32 sp4C[3];
    s32 padM;
    s8 sp47;
    RaceAPoint3f *curPoint;

    points = D_807F5FD4[arg0->unk1];
    curPoint = &points[arg0->unk2];
    sp47 = arg0->unk0 - arg0->unk1;
    mathPickCloserTargetPoint3D(arg2[0], arg2[1], arg2[2], curPoint, &points[arg3], &points[arg3], &points[arg4], &sp4C[0], &sp4C[1], &sp4C[2]);
    arg0->unk8 += 0.01 * D_807FBB40->unkB8;
    if (arg0->unk8 >= 1.0f) {
        arg0->unk8 = 1.0f;
        arg0->unk0 = arg0->unk1;
    }
    arg0->unkC = func_80612794(arg0->unk8 * 2048.0f) * (sp47 * 300);
    for (i = 0; i < 3; i++) {
        arg1[i] = arg1[i] + arg0->unk8 * (sp4C[i] - arg1[i]);
    }
}

extern s32 D_807F5FD0;
void *memcpy(void *, const void *, unsigned int);
void *func_80610FE8(s32);

void func_8002597C(void) {
    RaceAPoint3f *buf;
    u8 *src;
    RaceAPoint3f **tbl;
    u32 lo; /* byte length first, then the upper table pointer (one slot reused) */
    s32 i;
    s32 count;

    count = (D_807F5FD4[1] - D_807F5FD4[0]) / 2;
    buf = func_80610FE8(count * 0x24);
    tbl = func_80610FE8(0x10);
    for (i = 0; i < 4; i++) {
        tbl[i] = buf + i * count;
    }
    src = (u8 *)D_807F5FD4[0];
    lo = count * 12;
    buf = tbl[0];
    memcpy(buf, src, lo);
    buf = tbl[2];
    memcpy(buf, lo + src, lo);
    buf = tbl[1];
    src = (u8 *)tbl[0];
    lo = (u32)tbl[2];
    for (i = 0; i < count; i++) {
        buf[i].x = (((RaceAPoint3f *)lo)[i].x + ((RaceAPoint3f *)src)[i].x) * 0.5;
        buf[i].y = (((RaceAPoint3f *)lo)[i].y + ((RaceAPoint3f *)src)[i].y) * 0.5;
        buf[i].z = (((RaceAPoint3f *)lo)[i].z + ((RaceAPoint3f *)src)[i].z) * 0.5;
    }
    D_807F5FD0 = 3;
    D_807F5FD4 = tbl;
}

extern s16 D_80750AC4;
extern RaceActor *D_807FBB44;
void func_8002BBD0(void *, s32);
void func_8002BC2C(void *, s32, void *, void *);
RaceNodeActor *spawnNodeSpawnById(s32, s32, s32, s32, s32, s32, s32);

void func_80025E9C(RaceActor *arg0) {
    RaceParticipant *sp54;
    RaceActor *s2;
    RacePathState *s1;
    RaceParticipant *s0;
    RaceNodeLinks *temp;
    RaceNodeActor *sp40;
    RaceActor *sp3C;
    u8 *pad;

    sp54 = arg0->unk174;
    func_8002BBD0(arg0, 2);
    actorSpawn(0x12E, 0x95);
    s2 = D_807FBB44;
    s0 = s2->unk174;
    func_8002BC2C(arg0, 1, s2, s0);
    s0->unk37 = 0;
    s0->unk27 = 0;
    s0->unk30 = arg0;
    s0->unk36 = 1;
    s0->unk28 = 0;
    s1 = s2->unk178;
    sp40 = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
    s1->unk30 = sp40;
    temp = sp40->unk184;
    temp->participant = s0;
    temp->actor = s2;
    actorSpawn(0x130, 0);
    sp3C = D_807FBB44;
    s1->unk34 = sp3C;
    s0 = sp40->unk178;
    func_8002BC2C(arg0, 0, sp40, s0);
    s0->unk37 = 0;
    s0->unk27 = 1;
    s0->unk30 = arg0;
    s0->unk36 = 0;
    s1 = sp40->unk17C;
    s1->unk30 = s2;
    s1->unk34 = sp3C;
    s0 = sp3C->unk174;
    s0->unk30 = arg0;
    s1 = sp3C->unk178;
    s1->unk30 = s2;
    D_80750AC4 = 0;
    sp54->unk25 = 1;
}

void func_8002597C(void);
void func_8002CFF0(void);

void func_80025FDC(void) {
    func_8002597C();
    func_8002CFF0();
}

void func_80609140(s32, s32, f32, f32, s32, s32);

void racePlayCheckpointSfx(RacePathState *arg0, u8 arg1, f32 arg2) {
    arg0->unk10 = arg1;
    arg0->unk14 = arg2;
    func_80609140(0x1EB, 0x7FFF, 64.0f, 1.0f, 0, 0);
}

void raceAdvanceCheckpoint(RacePathState *arg0, RaceParticipant *arg1, s32 arg2) {
    if (arg0->unk2 + 1 != arg2) {
        arg0->unk2++;
    } else {
        arg0->unk2 = 0;
        if (arg1 != NULL) {
            arg1->unk37++;
        }
    }
    if (arg1 != NULL) {
        arg1->unk3A = arg0->unk2 + 1;
    }
}

f32 func_80612790(s16);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
f32 func_80611BB4(f32, f32);
s16 func_806CC190(s16, s16, f32);
void func_80714950(void *);
void func_8071498C(void *);
void timedLightOrbitUpdate();
extern u8 D_8072006C;
extern s32 D_8002FBB0[4];
extern u8 D_8002FBC0;
void func_80026098(f32 *arg0, f32 *arg1) {
    s16 sp2E;
    s32 pad;
    f32 sp24;
    f32 temp_fv1;
    f32 temp_fa1;

    sp2E = mathAngleBetweenPointsRad(arg0[0], arg0[2], arg1[0], arg1[2]) * 2048.0 / 3.1415927f;
    temp_fv1 = arg1[2] - arg0[2];
    temp_fa1 = arg1[0] - arg0[0];
    sp24 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1)) * (*(f32 *)&D_807FBB40->unkB8 * 0.03);
    D_807FBB40->unk7C = arg1[0] + (func_80612794(sp2E) * sp24);
    D_807FBB40->unk84 = arg1[2] + (func_80612790(sp2E) * sp24);
    D_807FBB40->unk80 = D_807FBB40->unk80 + (arg0[1] - D_807FBB40->unk80) * 0.8;
}

s16 func_806CC10C();

void func_800261E0(RacePathState *arg0) {
    s16 pad;
    s16 sp24;
    f32 sp20;
    s16 temp_s0;
    f32 temp_fv1;
    f32 temp_fv0;

    temp_s0 = arg0->unk18 + arg0->unkC;
    sp24 = func_806CC10C(0, (s16)arg0->unk1C, arg0);
    temp_s0 &= 0xFFF;
    sp20 = func_80612790(temp_s0);
    temp_fv0 = func_80612794(temp_s0);
    D_807FBB40->unkE6 = D_807FBB40->unkEE + temp_s0;
    D_807FBB40->unkE6 &= 0xFFF;
    temp_fv1 = sp24;
    D_807FBB40->unkE8 = temp_fv1 * sp20;
    D_807FBB40->unkE8 = D_807FBB40->unkE8 + arg0->unk20;
    D_807FBB40->unkE8 &= 0xFFF;
    D_807FBB40->unkE4 = temp_fv1 * temp_fv0;
    D_807FBB40->unkE4 = D_807FBB40->unkE4 + arg0->unk24;
    D_807FBB40->unkE4 &= 0xFFF;
}

void func_800257A4(RacePathState *, f32 *, f32 *, s32, s32);
void func_80026098(f32 *, f32 *);
void func_800261E0(RacePathState *);
s32 raceGetNextWaypointIndex(s32, s32);
void raceAdvanceCheckpoint(RacePathState *, RaceParticipant *, s32);
s32 func_806119A0(void);
s32 func_80714CC0(void *, f32, f32, f32, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);

void racePathFollowStep(RacePathState *arg0, RaceParticipant *arg1, u8 arg2) {
    s32 count;
    s32 next;
    s32 next2;
    RaceAPoint3f *points;
    RaceAPoint3f *cur;
    RaceAPoint3f *nxt;
    RaceAPoint3f *nxt2;
    f32 pos[3];
    f32 tgt[3];
    f32 ang;
    f32 thrust;
    f32 oldAng;
    f32 spd;
    f32 dist;
    u8 flag;
    s16 sp54;
    f32 hx;
    f32 hy;
    f32 hz;

    count = D_807F5FD4[arg0->unk0 + 1] - D_807F5FD4[arg0->unk0];
    next = raceGetNextWaypointIndex(count, arg0->unk2);
    next2 = raceGetNextWaypointIndex(count, next);
    points = D_807F5FD4[arg0->unk0];
    cur = &points[arg0->unk2];
    nxt2 = &points[next2];
    nxt = &points[next];
    oldAng = D_807FBB40->unkEE;
    flag = arg0->unk39;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk7C = cur->x;
        D_807FBB40->unk80 = cur->y;
        D_807FBB40->unk84 = cur->z;
        D_807FBB40->unkB8 = 0.0f;
        D_807FBB40->unkE6 = mathAngleBetweenPointsRad(nxt->x, nxt->z, D_807FBB40->unk7C, D_807FBB40->unk84) * 2048.0 / 3.1415927f;
        D_807FBB40->unkEE = D_807FBB40->unkE6;
        arg0->unk18 = 0.0f;
    }
    if (flag != 0) {
        thrust = 0.0f;
        arg0->unk39--;
        D_807FBB40->unkB8 = 0.0f;
        arg0->unk14 = 0.0f;
        arg0->unk10 = 0;
    } else {
        thrust = arg1->unk4;
    }
    if (arg0->unk10 != 0) {
        arg0->unk10--;
    } else {
        arg0->unk14 = arg0->unk14 * 0.7;
    }
    spd = D_807FBB40->unkB8 * D_807FBB40->unkB8 * 0.0033333334f + 0.2;
    D_807FBB40->unkB8 = D_807FBB40->unkB8 + (thrust - spd);
    if (D_807FBB40->unkB8 < 0.0f) {
        D_807FBB40->unkB8 = 0.0f;
    }
    ang = mathAngleBetweenPointsRad(nxt->x, nxt->z, cur->x, cur->z) * 2048.0 / 3.1415927f;
    pos[0] = func_80612794(D_807FBB40->unkEE) * D_807FBB40->unkB8 + D_807FBB40->unk7C;
    pos[2] = func_80612790(D_807FBB40->unkEE) * D_807FBB40->unkB8 + D_807FBB40->unk84;
    pos[1] = D_807FBB40->unk80;
    dist = sqrtf((cur->x - nxt->x) * (cur->x - nxt->x) + (cur->z - nxt->z) * (cur->z - nxt->z));
    arg0->unk1C = func_806CC190(arg0->unk1C, func_80611BB4(cur->y - nxt->y, dist) * 2048.0 / 3.1415927f, 3.0f);
    if (D_807FBB40->unkB8 > 0.001) {
        D_807FBB40->unkEE = func_806CC190(D_807FBB40->unkEE, ang, 50.0f / D_807FBB40->unkB8);
    }
    if (mathPickCloserTargetPoint3D(pos[0], pos[1], pos[2], cur, nxt, nxt, nxt2, &tgt[0], &tgt[1], &tgt[2]) != 0) {
        raceAdvanceCheckpoint(arg0, arg1, count);
        next = raceGetNextWaypointIndex(count, arg0->unk2);
        next2 = raceGetNextWaypointIndex(count, next);
        cur = &points[arg0->unk2];
        nxt2 = &points[next2];
    }
    if (arg0->unk0 != arg0->unk1) {
        func_800257A4(arg0, tgt, pos, next, next2);
    } else if (arg0->unk4 != 0) {
        arg0->unk4--;
    }
    func_80026098(tgt, pos);
    sp54 = func_806CC10C(D_807FBB40->unkEE, (s16)oldAng);
    arg0->unk28 += -0.04f * D_807FBB40->unkB8 * sp54 * func_80612790(arg0->unk18);
    arg0->unk28 -= 10.0f * D_807FBB40->unkB8 * func_80612794(arg0->unk18);
    arg0->unk28 = arg0->unk28 * 0.7f;
    arg0->unk18 = arg0->unk18 + arg0->unk28;
    func_800261E0(arg0);
    if (arg2 != 0) {
        if ((u32)(func_806119A0() & 0xFF) < D_807FBB40->unkB8 * 0.3 && arg0->unk0 == arg0->unk1) {
            mathPickCloserTargetPoint3D(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, cur, &points[next], &points[next], nxt2, &hx, &hy, &hz);
            func_80714950(D_807FBB40);
            func_8071498C(timedLightOrbitUpdate);
            D_8002FBB0[D_8002FBC0] = func_80714CC0(&D_8072006C, 0.4f, hx, hy, hz);
            D_8002FBC0++;
            D_8002FBC0 = D_8002FBC0 % 4;
            func_806086CC(hx, hy, hz, 0x8A, 0x96, 0x7F, 0x14, 0x50, 0.3f, 0);
        }
    }
    if (arg1 != NULL) {
        nxt = &points[next];
        arg1->unk40 = (D_807FBB40->unk7C - nxt->x) * (D_807FBB40->unk7C - nxt->x) + (D_807FBB40->unk80 - nxt->y) * (D_807FBB40->unk80 - nxt->y) + (D_807FBB40->unk84 - nxt->z) * (D_807FBB40->unk84 - nxt->z);
    }
}

s32 raceFindNearestParticipant(void *);

void func_80026B20(RaceParticipant *arg0) {
    RacePathState *sp34;
    RacePathState *sp30;
    RaceAuxState *sp2C;

    if (arg0->unk2C == NULL && arg0->unk2A != 0) {
        sp30 = D_807FBB40->unk178;
        arg0->unk2A--;
        actorSpawn(0x131, 0x96);
        sp34 = D_807FBB44->unk178;
        sp2C = D_807FBB44->unk17C;
        sp2C->unkC = D_807FBB40;
        sp2C->unk8 = raceFindNearestParticipant(D_807FBB40);
        arg0->unk2C = D_807FBB44;
        D_807FBB44->unk7C = D_807FBB40->unk7C;
        D_807FBB44->unk80 = D_807FBB40->unk80;
        D_807FBB44->unk84 = D_807FBB40->unk84;
        D_807FBB44->unkEE = D_807FBB40->unkEE;
        D_807FBB44->unkE6 = D_807FBB40->unkE6;
        D_807FBB44->unkB8 = D_807FBB40->unkB8;
        *sp34 = *sp30;
        func_80609140(0x18B, 0x7FFF, 64.0f, 1.0f, 0, 0);
    } else {
        func_80609140(0xE2, 0x7FFF, 64.0f, 1.0f, 0, 0);
    }
    arg0->unk29 = 0;
}

void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);

void func_80026CA8(void) {
    sfxPlayActorSound(D_807FBB40, 0x12D, 0, 1, 0, 0xFF, 1.0f, 0);
    sfxPlayActorSound(D_807FBB40, 0x12E, 0, 1, 1, 0xFF, 1.0f, 0);
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void func_80026D2C(f32 arg0) {
    s32 pad;
    s16 idx;

    idx = D_80770628[D_807FBB40->unk6E[0]];
    D_80770B68[idx] = arg0 / 20.0 + 1.0;
    D_80770BC0[idx] = 1.0f;
    idx = D_80770628[D_807FBB40->unk6E[1]];
    D_807FBB40->unk74 = arg0 / 20.0;
    if (D_807FBB40->unk74 > 1.0) {
        D_807FBB40->unk74 = 1.0f;
    }
    if (D_807FBB40->unk74 < 0.0) {
        D_807FBB40->unk74 = 0.0f;
    }
    if (D_80770BC0[idx] == 0.0f) {
        D_80770B68[idx] = ((u32)func_806119A0() / 4294967295.0 * 0.05 + 0.975) * (0.2 + arg0 / 15.0);
        D_80770BC0[idx] = 3.0f;
    }
}

void func_8002CAC8(void *, void *, void *);

void func_80026EE4(void *arg0, RaceActor *arg1) {
    func_8002CAC8(arg0, arg1, arg1->unk174);
}

extern u8 D_807FBD70;
extern void *D_807FBB4C;
s32 raceGetPrevWaypointIndex(s32, s32);
void racePathFollowStep(RacePathState *, RaceParticipant *, u8);
void actorUpdateModelMatrix(void *, s32);
s32 func_807142D8(void);
s32 flagGet(s32, s32);
void playerStateQueueCallback(s32, void *, u8);
void func_806F397C(void *, void *, s32, s32);
void actorClearNodeFlag(void *, s32);
void func_8072DB68(s32);
void slotQueueUpdate(s32, s32, s32);
void slotQueueCancel(s32, s32);
f32 func_8002D2C0(void *);
void func_806F4D70(u8, f32, f32, f32, f32);
void func_806F4DC0(u8, f32, f32, f32, f32);
void actorSpawnNodeEffectFacingCamera(s32, s32);
void sfxStopSlotSound(void *, s32);
void renderCallbacksRegister(void *, void *, s32);

void func_80026F04(void) {
    s32 len;
    RacePathState *sp78;
    RaceParticipant *s1;
    s16 sv;
    f32 off;
    f32 pad; /* unused: its stack home is needed for the frame layout */
    RaceActor *o;
    RaceParticipant *o2;
    s32 i;
    f32 sp58;
    f32 sp54;
    f32 sp50;

    s1 = D_807FBB40->unk174;
    sp78 = D_807FBB40->unk178;
    if (!(D_807FBB40->unk60 & 0x10)) {
        len = D_807F5FD4[sp78->unk0 + 1] - D_807F5FD4[sp78->unk0];
        s1->unk2A = 3;
        D_807FBB40->unk144 = 0x3C;
        sp78->unk2 = raceGetPrevWaypointIndex(len, 0);
        racePathFollowStep(sp78, s1, 1);
        if (func_807142D8() != 0 || flagGet(0x12, 2) != 0) {
            playerStateQueueCallback(0x4B, D_807FBB40, s1->unk28);
        } else {
            func_806F397C(D_807FBB4C, D_807FBB40, 0, 0x4B);
        }
        actorClearNodeFlag(D_807FBB40, 2);
        func_80026CA8();
    }
    if (D_807FBD70 == 5 && sp78->unk39 == 0) {
        if (s1->unk34 == 2) {
            func_8072DB68(3);
        }
        sp78->unk39 = 0x1E;
    }
    if (s1->unk35 == 0) {
        if (s1->unk34 == 1) {
            slotQueueUpdate(0xB, 1, 0);
            s1->unk35++;
        } else if (s1->unk34 == 5) {
            slotQueueCancel(0xB, 0);
            s1->unk35++;
        }
    }
    if (s1->unk34 == 1) {
        o = s1->unk30;
        o2 = o->unk174;
        if (o2->unk1C == 8 || o2->unk1C == 0x13) {
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x187, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        func_80026D2C(s1->unk26 * 1.5);
    } else if (s1->unk34 < 5) {
        sv = 0;
        if (s1->unk26 != 0) {
            sp50 = func_8002D2C0(s1);
            if (sp50 != 0) {
                sp50 = 1.5f * sp50 + 1.5f;
                racePlayCheckpointSfx(sp78, 0x1E, sp50);
            }
            s1->unk26 = 0;
        }
        if (sp78->unk39 != 0) {
            sp58 = sp78->unk39;
            if (sp58 > 10.0f) {
                sv = (sp58 - 10.0f) * 204.8f;
                sp58 = 300.0f;
                sp78->unk20 = func_80612794(sv) * sp58;
                sp78->unk24 = func_80612794(sv * 2) * sp58;
            } else {
                sp78->unk20 = 0.0f;
                sp78->unk24 = 0.0f;
            }
        }
        racePathFollowStep(sp78, s1, 1);
        D_807FBB40->unk80 += 20.0f * func_80612794(sv * 0.5f);
        func_80026D2C(D_807FBB40->unkB8);
    } else if (s1->unk34 == 5) {
        D_807FBB40->unk60 &= ~4;
        D_807FBB40->unkB8 = 0.0f;
        for (i = 0; i != 2; i++) {
            if (D_807FBB40->unk6E[i] != -1) {
                sfxStopSlotSound(D_807FBB40, i & 0xFF);
            }
        }
    }
    if (s1->unk29 != 0) {
        func_80026B20(s1);
    }
    if (s1->unk34 < 5) {
        if (s1->unk34 == 2) {
            off = 10.0;
        } else {
            off = -200.0f;
        }
        sp58 = D_807FBB40->unk7C;
        sp50 = D_807FBB40->unk84;
        sp54 = D_807FBB40->unk80 + off;
        func_806F4D70(s1->unk28, sp58, sp54, sp50, 12.0f);
        sp58 += D_807FBB40->unk88;
        sp58 *= 0.5;
        sp50 += D_807FBB40->unk90;
        sp50 *= 0.5;
        func_806F4DC0(s1->unk28, sp58, sp54, sp50, 12.0f);
    }
    if (D_807FBB40->unk60 & 4) {
        actorSpawnNodeEffectFacingCamera(1, 0xC8);
        actorSpawnNodeEffectFacingCamera(2, 0xC8);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    if (s1->unk34 > 0 && s1->unk34 < 5) {
        renderCallbacksRegister(func_80026EE4, D_807FBB40, 3);
    }
}

typedef struct {
    u8 pad0[0x15];
    u8 unk15;
    u8 pad16[0x200 - 0x16];
    u8 unk200;
} StructBB70_Race;
extern StructBB70_Race D_807FBB70;

extern u8 D_80720340[];
extern u8 D_8071FFA0[];

void func_807149B8(s32);
void func_8002D338(void *, void *);

void func_800274C0(void) {
    RaceParticipant *sp4C;
    RacePathState *sp48;
    s32 pad[3];
    u8 var_v1;
    RaceAuxState *s1;
    u16 t3;

    var_v1 = 0;
    sp4C = D_807FBB40->unk174;
    sp48 = D_807FBB40->unk178;
    s1 = D_807FBB40->unk17C;
    if (!(D_807FBB40->unk60 & 0x10)) {
        s1->unk0 = 0x78;
        D_807FBB40->unk60 |= 0x10;
        D_807FBB40->unk144 = 0x3C;
        sp4C->unk4 = 5.0f;
    }
    if ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0) || (D_807FBB70.unk200 == 5)) {
        func_807149B8(1);
        func_80714CC0(D_80720340, 3.0f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0xF6, 0xFF, 0x7F, 0x14, 0x32, 0.3f, 0);
        var_v1 = 1;
    }
    racePathFollowStep(sp48, sp4C, 0);
    D_807FBB40->unk80 += 5.0f;
    if (s1->unk0 != 0) {
        func_807149B8(1);
        func_80714CC0(D_8071FFA0, 1.0f, D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f, D_807FBB40->unk84);
        if (--s1->unk0 == 0) {
            var_v1 = 1;
        }
    }
    if (var_v1 != 0) {
        func_8002D338(D_807FBB40, s1);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
