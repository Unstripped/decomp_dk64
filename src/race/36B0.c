#include "common.h"

s32 func_800276B0(s32 arg0, u8 *arg1, u8 *arg2) {
    s32 diff;
    s32 abs_diff;
    s32 sign;

    diff = *(u16 *)(arg2 + 2) - *(u16 *)(arg1 + 2);
    abs_diff = (diff > 0) ? diff : -diff;
    if ((arg0 / 2) < abs_diff) {
        sign = (diff >= 0) ? 1 : -1;
        diff -= sign * arg0;
    }
    return diff;
}

extern s32 *D_807F5FD4;
s32 raceGetNextWaypointIndex(s32, s32);

typedef struct {
    f32 x, y, z;
} Point3f;

typedef struct {
    u8 unk0;
    u8 unk1;
    u16 unk2;
} Waypoint;

void mathPickCloserTargetPoint3D(f32, f32, f32, Point3f *, Point3f *, Point3f *, Point3f *, f32 *, f32 *, f32 *);
f32 func_80027710(s32, s32, void *);

#define RB_SQ(v) ((v) * (v))
f32 func_80027710(s32 arg0, s32 arg1, void *arg2) {
    s32 idx1;
    s32 idx2;
    Point3f *base;
    Point3f *cur;
    Point3f *p1;
    Point3f *p2;
    Point3f out;
    f32 d2;
    f32 e2;

    idx1 = raceGetNextWaypointIndex(arg0, ((Waypoint *)arg2)->unk2);
    idx2 = raceGetNextWaypointIndex(arg0, idx1);
    base = (Point3f *)D_807F5FD4[((Waypoint *)arg2)->unk0];
    p1 = &base[idx1];
    p2 = &base[idx2];
    cur = &base[((Waypoint *)arg2)->unk2];
    mathPickCloserTargetPoint3D(*(f32 *)(arg1 + 0x7C), *(f32 *)(arg1 + 0x80), *(f32 *)(arg1 + 0x84), cur, p1, p1, p2, &out.x, &out.y, &out.z);
    d2 = RB_SQ(cur->x - p1->x) + RB_SQ(cur->y - p1->y) + RB_SQ(cur->z - p1->z);
    return sqrtf((e2 = RB_SQ(cur->z - out.z) + (RB_SQ(cur->x - out.x) + RB_SQ(cur->y - out.y))) / d2);
}

f32 raceGetPathDistance(s32 arg0, u16 arg1, u16 arg2) {
    s32 index;
    Point3f *points;
    f32 *p1;
    f32 *p2;
    f32 dx;
    f32 dy;
    f32 dz;

    index = raceGetNextWaypointIndex(arg0, arg2);
    points = (Point3f *)D_807F5FD4[arg1];
    p1 = (f32 *)&points[arg2];
    p2 = (f32 *)&points[index];
    dx = p1[0] - p2[0];
    dy = p1[1] - p2[1];
    dz = p1[2] - p2[2];
    return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

f32 func_80027920(s32 arg0, s32 arg1, s32 arg2, Waypoint *arg3) {
    s32 count;
    s32 dir;
    f32 fracA;
    f32 fracB;
    f32 distA;
    f32 distB;
    f32 total;
    s32 cur;
    s32 sign;

    count = (D_807F5FD4[arg3->unk0 + 1] - D_807F5FD4[arg3->unk0]) / 12;
    dir = func_800276B0(count, (u8 *)arg1, (u8 *)arg3);
    fracA = func_80027710(count, arg0, (void *)arg1);
    fracB = func_80027710(count, arg2, arg3);
    distA = raceGetPathDistance(count, arg3->unk0, ((Waypoint *)arg1)->unk2);
    distB = raceGetPathDistance(count, arg3->unk0, arg3->unk2);
    if (dir == 0) {
        total = fracB * distB - fracA * distA;
    } else {
        if (dir > 0) {
            total = fracB * distB + (1.0f - fracA) * distA;
            cur = raceGetNextWaypointIndex(count, ((Waypoint *)arg1)->unk2);
            do {
            } while (0);
            arg2 = arg3->unk2;
        } else {
            total = fracA * distA + (1.0f - fracB) * distB;
            cur = raceGetNextWaypointIndex(count, arg3->unk2);
            arg2 = ((Waypoint *)arg1)->unk2;
        }
        if (cur != arg2) {
            do {
                total += raceGetPathDistance(count, arg3->unk0, cur);
                cur = raceGetNextWaypointIndex(count, cur);
            } while (cur != arg2);
        }
        if (dir >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }
        total = sign * total;
    }
    return total;
}

s32 func_806119A0(void);

void func_80027AF8(u8 *arg0, s8 arg1) {
    if (arg1 > 0) {
        arg0[1]++;
    } else {
        arg0[1]--;
    }
    *(f32 *)(arg0 + 8) = 0.0f;
}


void func_80027B30(u8 *arg0) {
    u8 temp_v0;

    temp_v0 = arg0[0];
    switch (temp_v0) {
    case 0:
        arg0[1] = arg0[1] + 1;
        break;
    case 1:
        if ((u32)(func_806119A0() & 0xFF) >= 0x80) {
            arg0[1] = arg0[1] + 1;
        } else {
            arg0[1] = arg0[1] - 1;
        }
        break;
    case 2:
        arg0[1] = arg0[1] - 1;
        break;
    }
    *(f32 *)(arg0 + 8) = 0.0f;
}

extern s32 *D_807F5FD4;

f32 raceGetCompletionFraction(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 result;
    s8 temp_v0;
    s8 new_var;
    s32 count;
    f32 num;
    f32 den;

    temp_v0 = arg1[0x37];
    result = 0.0f;
    if (temp_v0 > 0) {
        count = (D_807F5FD4[arg0[0] + 1] - D_807F5FD4[arg0[0]]) / 12;
        num = *(u16 *)(arg1 + 0x3A) + ((new_var = temp_v0) - 1) * count;
        den = arg2[0x24] * count;
        result = num / den;
    }
    return result;
}

extern void *D_80720120;
typedef struct {
    char pad[0x6E];
    s16 unk6E;
    char pad2[4];
    f32 unk74;
    f32 unk78;
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Struct_807FBB40_Race;
extern Struct_807FBB40_Race *D_807FBB40;
void func_807149B8(s32);
void func_80714C08(void *, f32, void *, s32, s32);

void func_80027C60(void) {
    s32 var_s0;

    for (var_s0 = 1; var_s0 != 3; var_s0++) {
        func_807149B8(1);
        func_80714C08(&D_80720120, 1.0f, D_807FBB40, var_s0, 0);
    }
}

extern f32 D_8002FBD0[];
extern u8 D_8002FC00[];
f32 func_8002E1C8(void *, f32, void *, void *);
void func_8002DE78(void *, s32, void *, void *);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(void *, s32);
s32 spawnNodeHasActor(s32);
void *spawnNodeActivate(s32, s32);

void func_80027CE8(void) {
    u8 *sp54;
    u8 *temp_s2;
    u8 *sp4C;
    u8 *sp48;
    s32 pad44;
    u8 *sp40;
    f32 sp3C;
    f32 sp38;
    u8 flag;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    u8 *temp_v0_3;
    u8 *temp_v0_2;
    u8 *temp_v0_4;
    u8 *temp_a3_2;
    f32 temp_fv0_2;

    sp54 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    temp_s2 = *(u8 **)((u8 *)D_807FBB40 + 0x17C);
    sp4C = *(u8 **)(temp_s2 + 0x30);
    sp48 = *(u8 **)(sp4C + 0x178);
    sp40 = *(u8 **)((u8 *)D_807FBB40 + 0x184);
    sp3C = func_80027920((s32)D_807FBB40, (s32)temp_s2, (s32)sp4C, (Waypoint *)sp48);
    sp38 = func_8002E1C8(sp40, sp3C, D_8002FBD0, D_8002FC00);
    flag = (temp_s2[1] == temp_s2[0]) && (temp_s2[4] == 0);
    if ((sp40[0xF] != 0) && (temp_v0_2 = *(u8 **)(sp54 + 0x30), (raceGetCompletionFraction(temp_s2, sp54, *(u8 **)(temp_v0_2 + 0x174)) > 0.8))) {
        func_8002DE78(sp40, 0, D_8002FBD0, D_8002FC00);
    }
    switch (sp40[0xF]) {
    case 5:
        func_80027C60();
    case 0:
    case 1:
        if (flag) {
            temp_v0 = func_806119A0();
            if ((D_8002FBD0[2] < sp3C) && (sp3C < D_8002FBD0[4]) && (sp48[0] != temp_s2[0]) && ((u8)((u32)(temp_v0 & 0xFF) < 0x14U))) {
                func_80027AF8(temp_s2, sp48[0] - temp_s2[0]);
            } else if ((D_8002FBD0[6] < sp3C) && (sp3C < D_8002FBD0[8]) && (sp48[0] == temp_s2[0]) && ((u8)((u32)(temp_v0 & 0xFF) < 0x14U))) {
                func_80027B30(temp_s2);
            }
            flag = (temp_s2[1] == temp_s2[0]) && (temp_s2[4] == 0);
            if (flag && ((var_s0 = 2, (sp3C < D_8002FBD0[2])) || (D_8002FBD0[4] < sp3C))) {
                var_s1 = 0;
                do {
                    if (spawnNodeHasActor(var_s0 & 0xFF) != 0) {
                        temp_v0_3 = spawnNodeActivate((s16)var_s0, 0);
                        temp_a3_2 = *(u8 **)(temp_v0_3 + 0x178);
                        if (temp_s2[0] == temp_a3_2[0]) {
                            temp_fv0_2 = func_80027920((s32)D_807FBB40, (s32)temp_s2, (s32)temp_v0_3, (Waypoint *)temp_a3_2);
                            if ((temp_fv0_2 > 20.0f) && (temp_fv0_2 < 300.0f)) {
                                var_s1 = 1;
                                func_80027B30(temp_s2);
                            }
                        }
                    }
                    var_s0 += 1;
                } while ((var_s0 < 7) && (var_s1 == 0));
            }
        }
        break;
    }
    *(f32 *)(sp54 + 4) = sp38;
    if ((sp3C < 0.0f) && (*(f32 *)(sp40 + 0x14) > 0.0f)) {
        if (*(s16 *)((u8 *)D_807FBB40 + 0x70) == -1) {
            sfxPlayActorSound(D_807FBB40, 0x130, 0, 1, 1, 0xFF, 1.0f, 0);
        }
        *(s16 *)((u8 *)D_807FBB40 + 0x72) = 0x14;
    }
    if (*(s16 *)((u8 *)D_807FBB40 + 0x72) > 0) {
        *(s16 *)((u8 *)D_807FBB40 + 0x72) = *(s16 *)((u8 *)D_807FBB40 + 0x72) - 1;
    } else if (*(s16 *)((u8 *)D_807FBB40 + 0x70) != -1) {
        sfxStopSlotSound(D_807FBB40, 1);
    }
    if (sp3C < -7000.0f) {
        temp_v0_4 = *(u8 **)(sp4C + 0x174);
        temp_v0_4[0x45] = 1;
    }
    *(f32 *)(sp40 + 0x14) = sp3C;
}

void func_8060E7EC(s32, s32, s32, u8 *);
void func_80609140(s32, s32, f32, f32, s32, s32);

void func_800280E8(void *arg0) {
    u8 *v1;
    s32 pad[2];
    u8 *sp28;
    f32 y;
    u8 *flag;

    v1 = *(u8 **)((u8 *)arg0 + 0x30);
    flag = *(u8 **)((u8 *)D_807FBB40 + 0x180);
    sp28 = *(u8 **)((u8 *)D_807FBB40 + 0x184);
    if (*(f32 *)((u8 *)D_807FBB40 + 0xB8) > *(f32 *)(v1 + 0xB8)) {
        y = *(f32 *)((u8 *)D_807FBB40 + 0xB8) - *(f32 *)(v1 + 0xB8);
    } else {
        y = -(*(f32 *)((u8 *)D_807FBB40 + 0xB8) - *(f32 *)(v1 + 0xB8));
    }
    if (*flag == 0) {
        y = y * 1.5;
        y = (y > 10.0) ? 10.0 : y;
        *flag = 3;
        func_8060E7EC(0, (u32)(255.0f * y * 0.1f) & 0xFF, *flag, flag);
        func_80609140(0x18A, 0x7FFF, 64.0f, 1.0f, 0xA, 0);
        if (*(f32 *)(sp28 + 0x14) < 0.0f) {
            *(f32 *)(v1 + 0xB8) = *(f32 *)(v1 + 0xB8) - y;
            *(f32 *)((u8 *)D_807FBB40 + 0xB8) = *(f32 *)((u8 *)D_807FBB40 + 0xB8) + y;
        } else {
            *(f32 *)(v1 + 0xB8) = *(f32 *)(v1 + 0xB8) + y;
            *(f32 *)((u8 *)D_807FBB40 + 0xB8) = *(f32 *)((u8 *)D_807FBB40 + 0xB8) - y;
        }
    }
}

void func_806086CC(f32, f32, s32, s32, s32, u8, s32, s32, f32, s32);

void func_800282D8(void) {
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_t0;

    temp_v0 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    temp_v1 = *(u8 **)(temp_v0 + 0x30);
    temp_t0 = *(u8 **)(temp_v1 + 0x174);
    switch (*(u16 *)(temp_t0 + 0x1C)) {
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
        func_806086CC(*(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x80), *(s32 *)((u8 *)D_807FBB40 + 0x84), 0x187, 0xFF, (s32)(((f64)(*(u16 *)(temp_t0 + 0x1C) - 0x1D) * 0.5) + 157.0), 0, 0, 0.3f, 0);
        break;
    }
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void func_800283D4(f32 arg0) {
    s16 temp_v0;

    temp_v0 = D_80770628[D_807FBB40->unk6E];
    D_807FBB40->unk74 = 1.0f;
    D_80770B68[temp_v0] = (f64) (arg0 * 0.05f) + 1.0;
    D_80770BC0[temp_v0] = 1.0f;
}

extern u8 D_807FBD70;
extern s16 D_80750AC8;
extern s32 D_8002FC0C[];
s32 raceGetPrevWaypointIndex(s32, s32);
void behaviourFrameBegin(void);
void actorClearNodeFlag(void *, s32);
void actorUpdateModelMatrix(void *, s32);
void racePathFollowStep(void *, void *, s32);
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
        racePathFollowStep(temp_s0, temp_s1, 1);
        *(f32 *)((u8 *)D_807FBB40 + 0x80) += 50.0f * func_80612794((s16)(s32)(*(f32 *)(temp_s0 + 0x20) * 0.5f));
    } else {
        *(f32 *)((u8 *)D_807FBB40 + 0xB8) = 0.0f;
    }
    func_800283D4(*(f32 *)((u8 *)D_807FBB40 + 0xB8));
    if (temp_s1[0x34] == 0) {
        var_a0 = temp_s1[0x35];
        temp_v1_2 = temp_s1[0x35];
        temp_v0_2 = temp_v1_2;
        switch (temp_v0_2) {
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

#ifdef NON_MATCHING
typedef struct {
    char pad0[4];
    void *unk4;
    char pad8[0x2F0 - 8];
} RaceBStructPlayer;
extern RaceBStructPlayer *D_807FC924;
void camSetFixedView(void *, f32, f32, f32, f32, f32, f32, s32);
void racePathFollowStep(void *, void *, s32);

void func_80028AD0(void) {
    s32 pad54[3];
    u8 *sp50;
    u8 *sp4C;
    u8 *sp48;
    s32 pad44;
    u8 *sp40;
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
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_a1;

    temp_s0 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    temp_s1 = *(u8 **)((u8 *)D_807FBB40 + 0x174);
    sp50 = *(u8 **)(temp_s0 + 0x30);
    sp4C = *(u8 **)(sp50 + 0x174);
    sp48 = *(u8 **)(sp50 + 0x178);
    temp_a1 = (u8 *)D_807FC924[sp4C[0x28]].unk4;
    sp40 = *(u8 **)(temp_a1 + 0x174);
    sp38 = (D_807F5FD4[temp_s0[0] + 1] - D_807F5FD4[temp_s0[0]]) / 12;
    sp30 = 1.0f;
    if (!(*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x10)) {
        temp_v0 = raceGetPrevWaypointIndex(sp38, *(u16 *)(sp48 + 2));
        *(u16 *)(temp_s0 + 2) = temp_v0;
        *(u16 *)(temp_s0 + 2) = raceGetPrevWaypointIndex(sp38, (u16)temp_v0);
        temp_s0[0] = temp_s0[1] = 1;
        racePathFollowStep(temp_s0, temp_s1, 0);
    }
    temp_v0_2 = sp4C[0x34];
    if (temp_v0_2 != temp_s1[0x34]) {
        temp_s1[0x34] = temp_v0_2;
        temp_s1[0x35] = 0;
    }
    temp_fv0 = func_80027920((s32)D_807FBB40, (s32)temp_s0, (s32)sp50, (Waypoint *)sp48);
    sp34 = temp_fv0;
    temp_v0_3 = sp48[1];
    if (temp_v0_3 != temp_s0[1]) {
        temp_s0[1] = temp_v0_3;
        *(f32 *)(temp_s0 + 8) = 0.0f;
    }
    if ((temp_s1[0x34] >= 2) && (temp_s1[0x34] < 4)) {
        if ((u32)sp48[0x10] > 24.0) {
            sp30 = -2.5f;
        } else if (*(f32 *)(sp48 + 0x14) > 0.5f) {
            sp30 = 2.5f;
        }
        temp_s0[0x39] = sp48[0x39];
        temp_s0[0x10] = sp48[0x10];
        *(f32 *)(temp_s1 + 4) = *(f32 *)(sp4C + 4) + ((temp_fv0 - (90.0f * sp30)) * 0.006f);
        if (temp_fv0 < 30.0f) {
            if (*(f32 *)(sp50 + 0xB8) < *(f32 *)((u8 *)D_807FBB40 + 0xB8)) {
                *(f32 *)((u8 *)D_807FBB40 + 0xB8) = *(f32 *)(sp50 + 0xB8);
            }
        }
        racePathFollowStep(temp_s0, temp_s1, 0);
    }
    if ((temp_s1[0x34] < 4) && (temp_s1[0x34] > 0)) {
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
        camSetFixedView(*(void **)(sp40 + 0x104), *(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x80) + ((20.0f * var_fv0) + 20.0f), *(f32 *)((u8 *)D_807FBB40 + 0x84), *(f32 *)(sp50 + 0x7C), *(f32 *)(sp50 + 0x80) + 20.0f, *(f32 *)(sp50 + 0x84), 1);
    }
}
#else

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_80028AD0.s")
#endif

void raceFindNearestWaypoint(void *arg0) {
    Point3f *p;
    s32 count;
    s32 i;
    s32 j;
    f32 best;
    f32 px;
    f32 py;
    f32 pz;
    f32 d;

    count = (D_807F5FD4[1] - D_807F5FD4[0]) / 12;
    p = (Point3f *)D_807F5FD4[0];
    best = 10000000.0f;
    px = *(f32 *)((u8 *)D_807FBB40 + 0x7C);
    py = *(f32 *)((u8 *)D_807FBB40 + 0x80);
    pz = *(f32 *)((u8 *)D_807FBB40 + 0x84);
    for (i = 0; i != 3; i++) {
        for (j = 0; j < count; j++) {
            d = RB_SQ(px - p->x) + RB_SQ(py - p->y) + RB_SQ(pz - p->z);
            if (d < best) {
                *(u16 *)((u8 *)arg0 + 2) = j;
                *(u8 *)arg0 = i;
                *((u8 *)arg0 + 1) = i;
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
extern StructBB70_Race D_807FBB70;
extern u8 *D_807FDC9C;
void raceFindNearestWaypoint(void *);
void func_8067E278(s32, s32);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void func_8072177C(void *, s16, s16, s16, s32, s32, s32, s32, s32);

void func_80029054(void) {
    u8 *temp_v0;
    u8 *sp50;
    u8 *temp_s1;
    u8 *sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    temp_s1 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    sp50 = *(u8 **)((u8 *)D_807FBB40 + 0x17C);
    behaviourFrameBegin();
    if (!(*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x10)) {
        raceFindNearestWaypoint(sp50);
        *(u8 *)((u8 *)D_807FBB40 + 0x144) = 0x3C;
        *(f32 *)(temp_s1 + 4) = 0.5f;
        actorClearNodeFlag(D_807FBB40, 1);
        *(void **)(sp50 + 0x30) = spawnNodeActivate(1, 0);
        *(s32 *)((u8 *)D_807FBB40 + 0x60) &= ~1;
    }
    temp_v0 = *(u8 **)(sp50 + 0x30);
    sp48 = *(u8 **)(temp_v0 + 0x178);
    if ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) {
        func_8067E278(0, 1);
        *(u8 *)((u8 *)D_807FBB40 + 0x154) = 0x40;
    }
    actorGetNodePos(D_807FBB40, 6, &sp3C, &sp40, &sp44);
    func_8072177C(D_807FBB40, (s16)(s32)sp3C, (s16)(s32)sp40, (s16)(s32)sp44, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    actorGetNodePos(D_807FBB40, 0xB, &sp3C, &sp40, &sp44);
    func_8072177C(D_807FBB40, (s16)(s32)sp3C, (s16)(s32)sp40, (s16)(s32)sp44, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    racePathFollowStep(sp50, temp_s1, 1);
    if ((temp_s1[0x34] == 0) && (sp48[0x34] == 5)) {
        *(u8 *)(D_807FDC9C + 0x14) = 0;
        *(u8 *)((u8 *)D_807FBB40 + 0x154) = 0x40;
        temp_s1[0x34]++;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
