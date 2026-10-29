#include "common.h"

typedef struct {
    f32 x, y, z;
} Point3f;

typedef struct RaceActor RaceActor;

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[8];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0xC];
    /* 0x30 */ RaceActor *unk30;
    /* 0x34 */ u8 pad34[5];
    /* 0x39 */ u8 unk39;
} RaceCursor;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0x14];
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u8 pad1E[6];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[3];
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 pad29[7];
    /* 0x30 */ RaceActor *unk30;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ s8 unk37;
    /* 0x38 */ u8 pad38[2];
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ u8 pad3C[9];
    /* 0x45 */ u8 unk45;
    /* 0x46 */ u8 pad46[0xBE];
    /* 0x104 */ void *unk104;
} RaceState;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[7];
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 unk14;
} RaceAux;

typedef struct {
    /* 0x174 */ void *unk174;
    /* 0x178 */ RaceState *unk178;
    /* 0x17C */ RaceCursor *unk17C;
    /* 0x180 */ u8 *unk180;
    /* 0x184 */ RaceAux *unk184;
} RaceViewA;

typedef struct {
    /* 0x174 */ RaceState *unk174;
    /* 0x178 */ RaceCursor *unk178;
} RaceViewB;

struct RaceActor {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 pad64[0xA];
    /* 0x6E */ s16 unk6E[2];
    /* 0x72 */ s16 unk72;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x30];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x28];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ u8 padE6[2];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[0x5A];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ union {
        RaceViewA a;
        RaceViewB b;
    } view;
};

extern Point3f **D_807F5FD4;
extern RaceActor *D_807FBB40;

s32 raceGetNextWaypointIndex(s32, s32);

s32 func_800276B0(s32 arg0, RaceCursor *arg1, RaceCursor *arg2) {
    s32 diff;
    s32 abs_diff;
    s32 sign;

    diff = arg2->unk2 - arg1->unk2;
    abs_diff = (diff > 0) ? diff : -diff;
    if ((arg0 / 2) < abs_diff) {
        sign = (diff >= 0) ? 1 : -1;
        diff -= sign * arg0;
    }
    return diff;
}

void mathPickCloserTargetPoint3D(f32, f32, f32, Point3f *, Point3f *, Point3f *, Point3f *, f32 *, f32 *, f32 *);

#define RB_SQ(v) ((v) * (v))
f32 func_80027710(s32 arg0, RaceActor *arg1, RaceCursor *arg2) {
    s32 idx1;
    s32 idx2;
    Point3f *base;
    Point3f *cur;
    Point3f *p1;
    Point3f *p2;
    Point3f out;
    f32 d2;
    f32 e2;

    idx1 = raceGetNextWaypointIndex(arg0, arg2->unk2);
    idx2 = raceGetNextWaypointIndex(arg0, idx1);
    base = D_807F5FD4[arg2->unk0];
    p1 = &base[idx1];
    p2 = &base[idx2];
    cur = &base[arg2->unk2];
    mathPickCloserTargetPoint3D(arg1->unk7C, arg1->unk80, arg1->unk84, cur, p1, p1, p2, &out.x, &out.y, &out.z);
    d2 = RB_SQ(cur->x - p1->x) + RB_SQ(cur->y - p1->y) + RB_SQ(cur->z - p1->z);
    return sqrtf((e2 = RB_SQ(cur->z - out.z) + (RB_SQ(cur->x - out.x) + RB_SQ(cur->y - out.y))) / d2);
}

f32 raceGetPathDistance(s32 arg0, u16 arg1, u16 arg2) {
    s32 index;
    Point3f *points;
    Point3f *p1;
    Point3f *p2;
    f32 dx;
    f32 dy;
    f32 dz;

    index = raceGetNextWaypointIndex(arg0, arg2);
    points = D_807F5FD4[arg1];
    p1 = &points[arg2];
    p2 = &points[index];
    dx = p1->x - p2->x;
    dy = p1->y - p2->y;
    dz = p1->z - p2->z;
    return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

f32 func_80027920(RaceActor *arg0, RaceCursor *arg1, RaceActor *arg2, RaceCursor *arg3) {
    s32 count;
    s32 dir;
    f32 fracA;
    f32 fracB;
    f32 distA;
    f32 distB;
    f32 total;
    s32 cur;
    s32 sign;
    s32 end;

    count = D_807F5FD4[arg3->unk0 + 1] - D_807F5FD4[arg3->unk0];
    dir = func_800276B0(count, arg1, arg3);
    fracA = func_80027710(count, arg0, arg1);
    fracB = func_80027710(count, arg2, arg3);
    distA = raceGetPathDistance(count, arg3->unk0, arg1->unk2);
    distB = raceGetPathDistance(count, arg3->unk0, arg3->unk2);
    if (dir == 0) {
        total = fracB * distB - fracA * distA;
    } else {
        if (dir > 0) {
            total = fracB * distB + (1.0f - fracA) * distA;
            cur = raceGetNextWaypointIndex(count, arg1->unk2);
            end = arg3->unk2;
        } else {
            total = fracA * distA + (1.0f - fracB) * distB;
            cur = raceGetNextWaypointIndex(count, arg3->unk2);
            end = arg1->unk2;
        }
        while (cur != end) {
            total += raceGetPathDistance(count, arg3->unk0, cur);
            cur = raceGetNextWaypointIndex(count, cur);
        }
        sign = (dir >= 0) ? 1 : -1;
        total = sign * total;
    }
    return total;
}

u32 func_806119A0(void);

void func_80027AF8(RaceCursor *arg0, s8 arg1) {
    if (arg1 > 0) {
        arg0->unk1++;
    } else {
        arg0->unk1--;
    }
    arg0->unk8 = 0.0f;
}

void func_80027B30(RaceCursor *arg0) {
    switch (arg0->unk0) {
    case 0:
        arg0->unk1++;
        break;
    case 1:
        if ((func_806119A0() & 0xFF) >= 0x80) {
            arg0->unk1++;
        } else {
            arg0->unk1--;
        }
        break;
    case 2:
        arg0->unk1--;
        break;
    }
    arg0->unk8 = 0.0f;
}

f32 raceGetCompletionFraction(RaceCursor *arg0, RaceState *arg1, RaceState *arg2) {
    f32 result;
    s8 temp_v0;
    s32 count;
    f32 num;
    f32 den;

    temp_v0 = arg1->unk37;
    result = 0.0f;
    if (temp_v0 > 0) {
        count = D_807F5FD4[arg0->unk0 + 1] - D_807F5FD4[arg0->unk0];
        num = (temp_v0 - 1) * count + arg1->unk3A;
        den = arg2->unk24 * count;
        result = num / den;
    }
    return result;
}

extern void *D_80720120;
void func_807149B8(s32);
void func_80714C08(void *, f32, void *, s32, s32);

void func_80027C60(void) {
    s32 var_s0;

    for (var_s0 = 1; var_s0 < 3; var_s0++) {
        func_807149B8(1);
        func_80714C08(&D_80720120, 1.0f, D_807FBB40, var_s0, 0);
    }
}

extern f32 D_8002FBD0[];
extern u8 D_8002FC00[];
f32 func_8002E1C8(RaceAux *, f32, f32 *, u8 *);
void func_8002DE78(RaceAux *, s32, f32 *, u8 *);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(void *, u8);
s32 spawnNodeHasActor(u8);
void *spawnNodeActivate(s16, s32);

void func_80027CE8(void) {
    RaceState *sp54;
    RaceCursor *temp_s2;
    RaceActor *sp4C;
    RaceCursor *sp48;
    s32 pad44;
    RaceAux *sp40;
    f32 sp3C;
    f32 sp38;
    u8 flag;
    u32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    RaceActor *temp_v0_3;
    RaceActor *temp_v0_2;
    RaceState *temp_v0_4;
    RaceCursor *temp_a3_2;
    f32 temp_fv0_2;

    sp54 = D_807FBB40->view.a.unk178;
    temp_s2 = D_807FBB40->view.a.unk17C;
    sp4C = temp_s2->unk30;
    sp48 = sp4C->view.b.unk178;
    sp40 = D_807FBB40->view.a.unk184;
    sp3C = func_80027920(D_807FBB40, temp_s2, sp4C, sp48);
    sp38 = func_8002E1C8(sp40, sp3C, D_8002FBD0, D_8002FC00);
    flag = (temp_s2->unk0 == temp_s2->unk1) && (temp_s2->unk4 == 0);
    if (sp40->unkF != 0) {
        temp_v0_2 = sp54->unk30;
        if (raceGetCompletionFraction(temp_s2, sp54, temp_v0_2->view.b.unk174) > 0.8) {
            func_8002DE78(sp40, 0, D_8002FBD0, D_8002FC00);
        }
    }
    switch (sp40->unkF) {
    case 5:
        func_80027C60();
    case 0:
    case 1:
        if (flag) {
            temp_v0 = func_806119A0();
            if ((D_8002FBD0[2] < sp3C) && (sp3C < D_8002FBD0[4]) && (temp_s2->unk0 != sp48->unk0) && ((u8)((temp_v0 & 0xFF) < 0x14))) {
                func_80027AF8(temp_s2, sp48->unk0 - temp_s2->unk0);
            } else if ((D_8002FBD0[6] < sp3C) && (sp3C < D_8002FBD0[8]) && (temp_s2->unk0 == sp48->unk0) && ((u8)((temp_v0 & 0xFF) < 0x14))) {
                func_80027B30(temp_s2);
            }
            flag = (temp_s2->unk0 == temp_s2->unk1) && (temp_s2->unk4 == 0);
            if (flag) {
                var_s0 = 2;
                if ((sp3C < D_8002FBD0[2]) || (D_8002FBD0[4] < sp3C)) {
                    var_s1 = 0;
                    do {
                        if (spawnNodeHasActor(var_s0) != 0) {
                            temp_v0_3 = spawnNodeActivate(var_s0, 0);
                            temp_a3_2 = temp_v0_3->view.b.unk178;
                            if (temp_a3_2->unk0 == temp_s2->unk0) {
                                temp_fv0_2 = func_80027920(D_807FBB40, temp_s2, temp_v0_3, temp_a3_2);
                                if ((temp_fv0_2 > 20.0f) && (temp_fv0_2 < 300.0f)) {
                                    var_s1 = 1;
                                    func_80027B30(temp_s2);
                                }
                            }
                        }
                        var_s0++;
                    } while ((var_s0 < 7) && (var_s1 == 0));
                }
            }
        }
        break;
    }
    sp54->unk4 = sp38;
    if ((sp3C < 0.0f) && (sp40->unk14 > 0.0f)) {
        if (D_807FBB40->unk6E[1] == -1) {
            sfxPlayActorSound(D_807FBB40, 0x130, 0, 1, 1, 0xFF, 1.0f, 0);
        }
        D_807FBB40->unk72 = 0x14;
    }
    if (D_807FBB40->unk72 > 0) {
        D_807FBB40->unk72--;
    } else if (D_807FBB40->unk6E[1] != -1) {
        sfxStopSlotSound(D_807FBB40, 1);
    }
    if (sp3C < -7000.0f) {
        temp_v0_4 = sp4C->view.b.unk174;
        temp_v0_4->unk45 = 1;
    }
    sp40->unk14 = sp3C;
}

void func_8060E7EC(s32, u8, s32, u8 *);
void func_80609140(s32, s32, f32, f32, s32, s32);

void func_800280E8(RaceCursor *arg0) {
    RaceActor *v1;
    s32 pad[2];
    RaceAux *sp28;
    f32 y;
    u8 *flag;

    v1 = arg0->unk30;
    flag = D_807FBB40->view.a.unk180;
    sp28 = D_807FBB40->view.a.unk184;
    if (D_807FBB40->unkB8 > v1->unkB8) {
        y = D_807FBB40->unkB8 - v1->unkB8;
    } else {
        y = -(D_807FBB40->unkB8 - v1->unkB8);
    }
    if (*flag == 0) {
        y *= 1.5;
        y = (y > 10.0) ? 10.0 : y;
        *flag = 3;
        func_8060E7EC(0, 255.0f * y * 0.1f, *flag, flag);
        func_80609140(0x18A, 0x7FFF, 64.0f, 1.0f, 0xA, 0);
        if (sp28->unk14 < 0.0f) {
            v1->unkB8 -= y;
            D_807FBB40->unkB8 += y;
        } else {
            v1->unkB8 += y;
            D_807FBB40->unkB8 -= y;
        }
    }
}

void func_806086CC(f32, f32, f32, s32, s32, u8, s32, s32, f32, s32);

void func_800282D8(void) {
    RaceState *temp_v0;
    RaceActor *temp_v1;
    RaceState *temp_t0;

    temp_v0 = D_807FBB40->view.a.unk178;
    temp_v1 = temp_v0->unk30;
    temp_t0 = temp_v1->view.b.unk174;
    switch (temp_t0->unk1C) {
    case 0x5A:
        sfxPlayActorSound(D_807FBB40, 0x107, 0, 1, 0, 0xFF, 1.0f, 0);
    case 0x1D:
    case 0x25:
    case 0x2C:
    case 0x30:
    case 0x38:
    case 0x3F:
    case 0x43:
    case 0x47:
    case 0x4E:
    case 0x54:
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x187, 0xFF, (s32)(((f64)(temp_t0->unk1C - 0x1D) * 0.5) + 157.0), 0, 0, 0.3f, 0);
        break;
    }
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void func_800283D4(f32 arg0) {
    s16 temp_v0;

    temp_v0 = D_80770628[D_807FBB40->unk6E[0]];
    D_807FBB40->unk74 = 1.0f;
    D_80770B68[temp_v0] = (f64)(arg0 * 0.05f) + 1.0;
    D_80770BC0[temp_v0] = 1.0f;
}

extern u8 D_807FBD70;
extern s16 D_80750AC8;
extern s32 D_8002FC0C[];
s32 raceGetPrevWaypointIndex(s32, s32);
void behaviourFrameBegin(void);
void actorClearNodeFlag(void *, s32);
void actorUpdateModelMatrix(void *, s32);
void racePathFollowStep(RaceCursor *, RaceState *, s32);
void func_8002D72C(void *);
void func_8002D754(void *);
s32 func_8002E8EC(RaceState *, void *, s32);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
void camStartPath(void *, s16, s32);
void camResumePath(void);
void func_805FF544(void);
void csModelStateSetFirstByte(s32, s32);
s32 slotQueueGetValue(s32, s32);
void hudSpawnTextScreen(s32);
s32 playerStateQueueCallback(s32, s32, s32);
void spawnNodeSpawnById(s16, s32, s32, s32, s32, s32, s32);
f32 func_80612794(s16);
s32 func_807142D8(void);

void func_80028440(void) {
    s32 pad70[2];
    u8 *sp6C;
    RaceAux *sp68;
    s32 count;
    RaceActor *sp60;
    RaceState *temp_s1;
    RaceCursor *temp_s0;
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

    temp_s1 = D_807FBB40->view.a.unk178;
    temp_s0 = D_807FBB40->view.a.unk17C;
    sp6C = D_807FBB40->view.a.unk180;
    sp68 = D_807FBB40->view.a.unk184;
    sp60 = temp_s1->unk30;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        count = D_807F5FD4[temp_s0->unk0 + 1] - D_807F5FD4[temp_s0->unk0];
        D_807FBB40->unk144 = 0x3C;
        D_807FBB40->unk60 &= ~1;
        temp_s0->unk0 = temp_s0->unk1 = 2;
        sp68->unk14 = 0.0f;
        temp_s0->unk2 = raceGetPrevWaypointIndex(count, 0);
        sp68->unk10 = 1;
        func_8002DE78(sp68, 5, D_8002FBD0, D_8002FC00);
        temp_s1->unk34 = 0;
        if ((flagGet(0x12, 2) == 0) && (flagGet(0x8B, 0) == 0) && (func_807142D8() == 0)) {
            camStartPath(D_807FBB40, 0, 1);
            flagSet(0x12, 1, 2);
        } else {
            temp_s1->unk35 = 3;
        }
        currentActorClearFlag();
        D_80750AC8 = 0xA;
        actorClearNodeFlag(D_807FBB40, 4);
    }
    if (D_807FBD70 == 4) {
        func_800280E8(temp_s0);
    } else if (D_807FBD70 == 5) {
        temp_s0->unk39 = 0x1E;
        temp_s0->unk20 = 0.0f;
    }
    if (*sp6C != 0) {
        (*sp6C)--;
    }
    temp_v0_2 = temp_s0->unk39;
    if (temp_v0_2 != 0) {
        temp_fv0 = (f32)temp_v0_2;
        if (temp_fv0 > 10.0f) {
            temp_s0->unk20 = (temp_fv0 - 10.0f) * 204.8f;
        } else {
            temp_s0->unk20 = 0.0f;
        }
    } else if ((temp_s1->unk34 >= 2) && (temp_s1->unk34 < 4)) {
        func_80027CE8();
    }
    if (temp_s1->unk34 == 1) {
        func_800282D8();
    }
    if (temp_s1->unk34 < 5) {
        racePathFollowStep(temp_s0, temp_s1, 1);
        D_807FBB40->unk80 += 50.0f * func_80612794((s16)(temp_s0->unk20 * 0.5f));
    } else {
        D_807FBB40->unkB8 = 0.0f;
    }
    func_800283D4(D_807FBB40->unkB8);
    if (temp_s1->unk34 == 0) {
        var_a0 = temp_s1->unk35;
        temp_v1_2 = temp_s1->unk35;
        temp_v0_2 = temp_v1_2;
        switch (temp_v0_2) {
        case 0:
            if (D_807FBB40->unk60 & 0x02000000) {
                temp_s1->unk35 = temp_s1->unk35 + 1;
                var_a0 = temp_s1->unk35;
            }
            break;
        case 1:
            if (!(D_807FBB40->unk60 & 0x02000000)) {
                camResumePath();
                temp_s1->unk35++;
                var_a0 = temp_s1->unk35;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                temp_s1->unk35++;
            }
            var_a0 = temp_s1->unk35;
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
            } while (var_s0 < 7);
        }
    } else if (temp_s1->unk34 == 4) {
        if (temp_s1->unk35 == 0) {
            if (flagGet(0x8B, 0) == 0) {
                cam = D_8002FC0C[func_8002E8EC(temp_s1, sp68->unk4, 0xA)];
                camStartPath(D_807FBB40, cam, 1);
                currentActorClearFlag();
            } else {
                func_805FF544();
            }
            temp_s1->unk35++;
        }
    } else if (temp_s1->unk34 == 5) {
        temp_v1_3 = temp_s1->unk35;
        switch (temp_v1_3) {
        case 0:
            if (flagGet(0x8B, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                var_s0 = 0;
                D_807FBB40->unkE4 = 0;
                var_v1 = 0;
                D_807FBB40->unkE8 = 0;
                do {
                    if (*(s16 *)((u8 *)D_807FBB40 + var_v1 + 0x6E) != -1) {
                        sfxStopSlotSound(D_807FBB40, var_s0);
                    }
                    var_s0 += 1;
                    var_v1 += 2;
                } while (var_s0 != 2);
            }
            temp_s1->unk35++;
            break;
        case 1:
            if (D_807FBB40->unk60 & 0x02000000) {
                temp_s1->unk35++;
            }
            break;
        case 2:
            if (!(D_807FBB40->unk60 & 0x02000000)) {
                camResumePath();
                if ((temp_s1->unk36 == 0) || (slotQueueGetValue(0xB, 0) < 0xA)) {
                    temp_s1->unk35 = 3;
                }
                temp_s1->unk35++;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                csModelStateSetFirstByte(0x62, 0xA);
                temp_s1->unk35++;
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
                temp_s1->unk35++;
            }
            break;
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

#ifdef NON_MATCHING
typedef struct {
    char pad0[4];
    RaceActor *unk4;
    char pad8[0x2F0 - 8];
} RaceBStructPlayer;
extern RaceBStructPlayer *D_807FC924;
void camSetFixedView(void *, f32, f32, f32, f32, f32, f32, s32);

void func_80028AD0(void) {
    s32 pad54[3];
    RaceActor *sp50;
    RaceState *sp4C;
    RaceCursor *sp48;
    s32 pad44;
    RaceState *sp40;
    s32 pad3C;
    int sp38;
    f32 sp34;
    f32 sp30;
    f32 temp_fv0;
    f32 var_fv0;
    f32 temp_fv0_3;
    int temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    RaceCursor *temp_s0;
    RaceState *temp_s1;
    RaceActor *temp_a1;

    temp_s0 = D_807FBB40->view.b.unk178;
    temp_s1 = D_807FBB40->view.b.unk174;
    sp50 = temp_s0->unk30;
    sp4C = sp50->view.b.unk174;
    sp48 = sp50->view.b.unk178;
    temp_a1 = D_807FC924[sp4C->unk28].unk4;
    sp40 = temp_a1->view.b.unk174;
    sp38 = D_807F5FD4[temp_s0->unk0 + 1] - D_807F5FD4[temp_s0->unk0];
    sp30 = 1.0f;
    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_v0 = raceGetPrevWaypointIndex(sp38, sp48->unk2);
        temp_s0->unk2 = temp_v0;
        temp_s0->unk2 = raceGetPrevWaypointIndex(sp38, (u16)temp_v0);
        temp_s0->unk0 = temp_s0->unk1 = 1;
        racePathFollowStep(temp_s0, temp_s1, 0);
    }
    temp_v0_2 = sp4C->unk34;
    if (temp_v0_2 != temp_s1->unk34) {
        temp_s1->unk34 = temp_v0_2;
        temp_s1->unk35 = 0;
    }
    temp_fv0 = func_80027920(D_807FBB40, temp_s0, sp50, sp48);
    sp34 = temp_fv0;
    temp_v0_3 = sp48->unk1;
    if (temp_v0_3 != temp_s0->unk1) {
        temp_s0->unk1 = temp_v0_3;
        temp_s0->unk8 = 0.0f;
    }
    if ((temp_s1->unk34 >= 2) && (temp_s1->unk34 < 4)) {
        if ((u32)sp48->unk10 > 24.0) {
            sp30 = -2.5f;
        } else if (sp48->unk14 > 0.5f) {
            sp30 = 2.5f;
        }
        temp_s0->unk39 = sp48->unk39;
        temp_s0->unk10 = sp48->unk10;
        temp_s1->unk4 = sp4C->unk4 + ((temp_fv0 - (90.0f * sp30)) * 0.006f);
        if (temp_fv0 < 30.0f) {
            if (sp50->unkB8 < D_807FBB40->unkB8) {
                D_807FBB40->unkB8 = sp50->unkB8;
            }
        }
        racePathFollowStep(temp_s0, temp_s1, 0);
    }
    if ((temp_s1->unk34 < 4) && (temp_s1->unk34 > 0)) {
        temp_fv0_3 = sp34 / 90.0f;
        if (temp_fv0_3 < 0.0f) {
            var_fv0 = 0.0f;
        } else {
            if (temp_fv0_3 > 1.0f) {
                temp_fv0 = 1.0f;
            } else {
                temp_fv0 = temp_fv0_3;
            }
            var_fv0 = temp_fv0;
        }
        camSetFixedView(sp40->unk104, D_807FBB40->unk7C, D_807FBB40->unk80 + ((20.0f * var_fv0) + 20.0f), D_807FBB40->unk84, sp50->unk7C, sp50->unk80 + 20.0f, sp50->unk84, 1);
    }
}
#else

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_80028AD0.s")
#endif


void raceFindNearestWaypoint(RaceCursor *arg0) {
    Point3f *p;
    s32 count;
    s32 i;
    s32 j;
    f32 best;
    f32 px;
    f32 py;
    f32 pz;
    f32 d;

    count = D_807F5FD4[1] - D_807F5FD4[0];
    p = D_807F5FD4[0];
    best = 10000000.0f;
    px = D_807FBB40->unk7C;
    py = D_807FBB40->unk80;
    pz = D_807FBB40->unk84;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < count; j++) {
            d = RB_SQ(px - p->x) + RB_SQ(py - p->y) + RB_SQ(pz - p->z);
            if (d < best) {
                arg0->unk2 = j;
                arg0->unk0 = i;
                arg0->unk1 = i;
                best = d;
            }
            p++;
        }
    }
}

typedef struct {
    u8 pad0[0x15];
    u8 unk15;
    u8 pad16[0x200 - 0x16];
    u8 unk200;
} StructBB70_Race;
typedef struct {
    u8 pad0[0x14];
    u8 unk14;
} RaceDC9C;
extern StructBB70_Race D_807FBB70;
extern RaceDC9C *D_807FDC9C;
void func_8067E278(s32, s32);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void commandQueuePush(void *, s16, s16, s16, s32, s32, s32, s32, s32);

void func_80029054(void) {
    RaceActor *temp_v0;
    RaceCursor *sp50;
    RaceState *temp_s1;
    RaceState *sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    temp_s1 = D_807FBB40->view.a.unk178;
    sp50 = D_807FBB40->view.a.unk17C;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        raceFindNearestWaypoint(sp50);
        D_807FBB40->unk144 = 0x3C;
        temp_s1->unk4 = 0.5f;
        actorClearNodeFlag(D_807FBB40, 1);
        sp50->unk30 = spawnNodeActivate(1, 0);
        D_807FBB40->unk60 &= ~1;
    }
    temp_v0 = sp50->unk30;
    sp48 = temp_v0->view.a.unk178;
    if ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) {
        func_8067E278(0, 1);
        D_807FBB40->unk154 = 0x40;
    }
    actorGetNodePos(D_807FBB40, 6, &sp3C, &sp40, &sp44);
    commandQueuePush(D_807FBB40, (s16)sp3C, (s16)sp40, (s16)sp44, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    actorGetNodePos(D_807FBB40, 0xB, &sp3C, &sp40, &sp44);
    commandQueuePush(D_807FBB40, (s16)sp3C, (s16)sp40, (s16)sp44, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    racePathFollowStep(sp50, temp_s1, 1);
    if ((temp_s1->unk34 == 0) && (sp48->unk34 == 5)) {
        D_807FDC9C->unk14 = 0;
        D_807FBB40->unk154 = 0x40;
        temp_s1->unk34++;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
