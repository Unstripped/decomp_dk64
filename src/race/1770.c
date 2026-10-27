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
extern s32 *D_807F5FD4;
extern void *D_807FBB40;
f32 func_80612794(s16);
void mathPickCloserTargetPoint3D(f32, f32, f32, RaceAPoint3f *, RaceAPoint3f *, RaceAPoint3f *, RaceAPoint3f *, f32 *, f32 *, f32 *);

void func_800257A4(u8 *arg0, f32 *arg1, f32 *arg2, s32 arg3, s32 arg4) {
    s32 padA;
    s32 padB;
    RaceAPoint3f *points;
    s32 i;
    f32 sp4C[3];
    s32 padM;
    s8 sp47;
    RaceAPoint3f *curPoint;

    points = (RaceAPoint3f *)D_807F5FD4[arg0[1]];
    curPoint = &points[*(u16 *)(arg0 + 2)];
    sp47 = arg0[0] - arg0[1];
    mathPickCloserTargetPoint3D(arg2[0], arg2[1], arg2[2], curPoint, &points[arg3], &points[arg3], &points[arg4], &sp4C[0], &sp4C[1], &sp4C[2]);
    *(f32 *)(arg0 + 8) = 0.01 * *(f32 *)((u8 *)D_807FBB40 + 0xB8) + *(f32 *)(arg0 + 8);
    if (*(f32 *)(arg0 + 8) >= 1.0f) {
        *(f32 *)(arg0 + 8) = 1.0f;
        arg0[0] = arg0[1];
    }
    *(f32 *)(arg0 + 0xC) = func_80612794((s16)(s32)(*(f32 *)(arg0 + 8) * 2048.0f)) * (f32)(sp47 * 300);
    for (i = 0; i < 3; i++) {
        arg1[i] = arg1[i] + *(f32 *)(arg0 + 8) * (sp4C[i] - arg1[i]);
    }
}

#ifdef NON_MATCHING
extern s32 D_807F5FD0;
void *memcpy(void *, const void *, unsigned int);
void *func_80610FE8(s32);

void func_8002597C(void) {
    RaceAPoint3f *buf, *src, *lo;
    s32 i;
    RaceAPoint3f **tbl;
    s32 count;
    u32 sz;

    count = (D_807F5FD4[1] - D_807F5FD4[0]) / 12 / 2;
    buf = func_80610FE8(count * 0x24);
    tbl = func_80610FE8(0x10);
    for (i = 0; i < 4; i++) {
        tbl[i] = (RaceAPoint3f *)((u8 *)buf + i * count * 12);
    }
    src = (RaceAPoint3f *)D_807F5FD4[0];
    sz = count * 12;
    buf = tbl[0];
    memcpy(buf, src, sz);
    buf = tbl[2];
    memcpy(buf, (u8 *)src + sz, sz);
    buf = tbl[1];
    lo = tbl[0];
    src = tbl[2];
    for (i = 0; i < count; i++) {
        buf[i].x = (lo[i].x + src[i].x) * 0.5;
        buf[i].y = (lo[i].y + src[i].y) * 0.5;
        buf[i].z = (lo[i].z + src[i].z) * 0.5;
    }
    D_807F5FD0 = 3;
    D_807F5FD4 = (s32 *)tbl;
}
#else

#pragma GLOBAL_ASM("asm/race/nonmatchings/1770/func_8002597C.s")
#endif

extern s16 D_80750AC4;
extern void *D_807FBB44;
void func_8002BBD0(void *, s32);
void func_8002BC2C(void *, s32, void *, void *);
void *spawnNodeSpawnById(s32, s32, s32, s32, s32, s32, s32);

void func_80025E9C(u8 *arg0) {
    u8 *sp54;
    u8 *s2;
    u8 *s1;
    u8 *s0;
    u8 *temp;
    u8 *sp40;
    u8 *sp3C;
    u8 *pad;

    sp54 = *(u8 **)(arg0 + 0x174);
    func_8002BBD0(arg0, 2);
    actorSpawn(0x12E, 0x95);
    s2 = (u8 *)D_807FBB44;
    s0 = *(u8 **)(s2 + 0x174);
    func_8002BC2C(arg0, 1, s2, s0);
    s0[0x37] = 0;
    s0[0x27] = 0;
    *(u8 **)(s0 + 0x30) = arg0;
    s0[0x36] = 1;
    s0[0x28] = 0;
    s1 = *(u8 **)(s2 + 0x178);
    sp40 = (u8 *)spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
    *(u8 **)(s1 + 0x30) = sp40;
    temp = *(u8 **)(sp40 + 0x184);
    *(u8 **)(temp + 4) = s0;
    *(u8 **)(temp + 0) = s2;
    actorSpawn(0x130, 0);
    sp3C = (u8 *)D_807FBB44;
    *(u8 **)(s1 + 0x34) = sp3C;
    s0 = *(u8 **)(sp40 + 0x178);
    func_8002BC2C(arg0, 0, sp40, s0);
    s0[0x37] = 0;
    s0[0x27] = 1;
    *(u8 **)(s0 + 0x30) = arg0;
    s0[0x36] = 0;
    s1 = *(u8 **)(sp40 + 0x17C);
    *(u8 **)(s1 + 0x30) = s2;
    *(u8 **)(s1 + 0x34) = sp3C;
    s0 = *(u8 **)(sp3C + 0x174);
    *(u8 **)(s0 + 0x30) = arg0;
    s1 = *(u8 **)(sp3C + 0x178);
    *(u8 **)(s1 + 0x30) = s2;
    D_80750AC4 = 0;
    sp54[0x25] = 1;
}

void func_8002597C(void);
void func_8002CFF0(void);

void func_80025FDC(void) {
    func_8002597C();
    func_8002CFF0();
}

void func_80609140(s32, s32, f32, f32, s32, s32);

void racePlayCheckpointSfx(u8 *arg0, u8 arg1, f32 arg2) {
    arg0[0x10] = arg1;
    *(f32 *)(arg0 + 0x14) = arg2;
    func_80609140(0x1EB, 0x7FFF, 64.0f, 1.0f, 0, 0);
}

void raceAdvanceCheckpoint(u16 *arg0, s8 *arg1, s32 arg2) {
    if (arg0[1] + 1 != arg2) {
        arg0[1]++;
    } else {
        arg0[1] = 0;
        if (arg1 != NULL) {
            arg1[0x37]++;
        }
    }
    if (arg1 != NULL) {
        *(u16 *)(arg1 + 0x3A) = arg0[1] + 1;
    }
}

extern void *D_807FBB40;
f32 func_80612790(s16);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
void func_80026098(f32 *arg0, f32 *arg1) {
    s16 sp2E;
    s32 pad;
    f32 sp24;
    f32 temp_fv1;
    f32 temp_fa1;

    sp2E = (s16) (s32) (((f64) mathAngleBetweenPointsRad(arg0[0], arg0[2], arg1[0], arg1[2]) * 2048.0) / 3.1415927410125732);
    temp_fv1 = arg1[2] - arg0[2];
    temp_fa1 = arg1[0] - arg0[0];
    sp24 = (f32) ((f64) sqrtf((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1)) * ((f64) *(f32 *)((u8 *)D_807FBB40 + 0xB8) * 0.03));
    *(f32 *)((u8 *)D_807FBB40 + 0x7C) = arg1[0] + (func_80612794(sp2E) * sp24);
    *(f32 *)((u8 *)D_807FBB40 + 0x84) = arg1[2] + (func_80612790(sp2E) * sp24);
    *(f32 *)((u8 *)D_807FBB40 + 0x80) = (f32) ((f64) *(f32 *)((u8 *)D_807FBB40 + 0x80) + ((f64) (arg0[1] - *(f32 *)((u8 *)D_807FBB40 + 0x80)) * 0.8));
}

s16 func_806CC10C(s16, s16, void *);

void func_800261E0(u8 *arg0) {
    s16 pad;
    s16 sp24;
    f32 sp20;
    s16 temp_s0;
    f32 temp_fv1;
    f32 temp_fv0;

    temp_s0 = (s32)(*(f32 *)(arg0 + 0xC) + *(f32 *)(arg0 + 0x18));
    sp24 = func_806CC10C(0, (s32)*(f32 *)(arg0 + 0x1C), arg0);
    temp_s0 &= 0xFFF;
    sp20 = func_80612790(temp_s0);
    temp_fv0 = func_80612794(temp_s0);
    *(s16 *)((u8 *)D_807FBB40 + 0xE6) = *(s16 *)((u8 *)D_807FBB40 + 0xEE) + temp_s0;
    *(s16 *)((u8 *)D_807FBB40 + 0xE6) &= 0xFFF;
    temp_fv1 = (f32) sp24;
    *(s16 *)((u8 *)D_807FBB40 + 0xE8) = (s32)(temp_fv1 * sp20);
    *(s16 *)((u8 *)D_807FBB40 + 0xE8) = *(f32 *)(arg0 + 0x20) + (f32)*(s16 *)((u8 *)D_807FBB40 + 0xE8);
    *(s16 *)((u8 *)D_807FBB40 + 0xE8) &= 0xFFF;
    *(s16 *)((u8 *)D_807FBB40 + 0xE4) = (s32)(temp_fv1 * temp_fv0);
    *(s16 *)((u8 *)D_807FBB40 + 0xE4) = *(f32 *)(arg0 + 0x24) + (f32)*(s16 *)((u8 *)D_807FBB40 + 0xE4);
    *(s16 *)((u8 *)D_807FBB40 + 0xE4) &= 0xFFF;
}

#pragma GLOBAL_ASM("asm/race/nonmatchings/1770/func_80026354.s")

typedef struct {
    s32 pad[15];
} Struct3C;
s32 func_8002D360(void *);

void func_80026B20(u8 *arg0) {
    void *sp34;
    void *sp30;
    u8 *sp2C;

    if (*(void **)(arg0 + 0x2C) == NULL && arg0[0x2A] != 0) {
        sp30 = *(void **)((u8 *)D_807FBB40 + 0x178);
        arg0[0x2A]--;
        actorSpawn(0x131, 0x96);
        sp34 = *(void **)((u8 *)D_807FBB44 + 0x178);
        sp2C = *(u8 **)((u8 *)D_807FBB44 + 0x17C);
        *(void **)(sp2C + 0xC) = D_807FBB40;
        *(s32 *)(sp2C + 8) = func_8002D360(D_807FBB40);
        *(void **)(arg0 + 0x2C) = D_807FBB44;
        *(f32 *)((u8 *)D_807FBB44 + 0x7C) = *(f32 *)((u8 *)D_807FBB40 + 0x7C);
        *(f32 *)((u8 *)D_807FBB44 + 0x80) = *(f32 *)((u8 *)D_807FBB40 + 0x80);
        *(f32 *)((u8 *)D_807FBB44 + 0x84) = *(f32 *)((u8 *)D_807FBB40 + 0x84);
        *(s16 *)((u8 *)D_807FBB44 + 0xEE) = *(s16 *)((u8 *)D_807FBB40 + 0xEE);
        *(s16 *)((u8 *)D_807FBB44 + 0xE6) = *(s16 *)((u8 *)D_807FBB40 + 0xE6);
        *(f32 *)((u8 *)D_807FBB44 + 0xB8) = *(f32 *)((u8 *)D_807FBB40 + 0xB8);
        *(Struct3C *)sp34 = *(Struct3C *)sp30;
        func_80609140(0x18B, 0x7FFF, 64.0f, 1.0f, 0, 0);
    } else {
        func_80609140(0xE2, 0x7FFF, 64.0f, 1.0f, 0, 0);
    }
    arg0[0x29] = 0;
}

void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);

void func_80026CA8(void) {
    sfxPlayActorSound(D_807FBB40, 0x12D, 0, 1, 0, 0xFF, 1.0f, 0);
    sfxPlayActorSound(D_807FBB40, 0x12E, 0, 1, 1, 0xFF, 1.0f, 0);
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];
s32 func_806119A0(void);

void func_80026D2C(f32 arg0) {
    s32 pad;
    s16 idx;

    idx = D_80770628[*(s16 *)((u8 *)D_807FBB40 + 0x6E)];
    D_80770B68[idx] = arg0 / 20.0 + 1.0;
    D_80770BC0[idx] = 1.0f;
    idx = D_80770628[*(s16 *)((u8 *)D_807FBB40 + 0x70)];
    *(f32 *)((u8 *)D_807FBB40 + 0x74) = arg0 / 20.0;
    if (*(f32 *)((u8 *)D_807FBB40 + 0x74) > 1.0) {
        *(f32 *)((u8 *)D_807FBB40 + 0x74) = 1.0f;
    }
    if (*(f32 *)((u8 *)D_807FBB40 + 0x74) < 0.0) {
        *(f32 *)((u8 *)D_807FBB40 + 0x74) = 0.0f;
    }
    if (D_80770BC0[idx] == 0.0f) {
        D_80770B68[idx] = ((u32)func_806119A0() / 4294967295.0 * 0.05 + 0.975) * (0.2 + arg0 / 15.0);
        D_80770BC0[idx] = 3.0f;
    }
}

void func_8002CAC8(void *, void *, void *);

void func_80026EE4(void *arg0, u8 *arg1) {
    func_8002CAC8(arg0, arg1, *(void **)(arg1 + 0x174));
}

extern u8 D_807FBD70;
extern void *D_807FBB4C;
s32 raceGetPrevWaypointIndex(s32, s32);
void func_80026354(void *, void *, s32);
void actorUpdateModelMatrix(void *, s32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
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
void func_8068ECF4(s32, s32);
void sfxStopSlotSound(void *, s32);
void renderCallbacksRegister(void *, void *, s32);

#ifdef NON_MATCHING
void func_80026F04(void) {
    s32 len;
    u8 *sp78;
    u8 *s1;
    s16 sv;
    f32 off;
    f32 f;
    u8 *o;
    u8 *o2;
    s32 i;
    f32 sp58;
    f32 sp54;
    f32 sp50;

    s1 = *(u8 **)((u8 *)D_807FBB40 + 0x174);
    sp78 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    if (!(*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x10)) {
        len = (D_807F5FD4[sp78[0] + 1] - D_807F5FD4[sp78[0]]) / 12;
        s1[0x2A] = 3;
        *(u8 *)((u8 *)D_807FBB40 + 0x144) = 0x3C;
        *(u16 *)(sp78 + 2) = raceGetPrevWaypointIndex(len, 0);
        func_80026354(sp78, s1, 1);
        if (func_807142D8() != 0 || flagGet(0x12, 2) != 0) {
            playerStateQueueCallback(0x4B, D_807FBB40, s1[0x28]);
        } else {
            func_806F397C(D_807FBB4C, D_807FBB40, 0, 0x4B);
        }
        actorClearNodeFlag(D_807FBB40, 2);
        func_80026CA8();
    }
    if (D_807FBD70 == 5 && sp78[0x39] == 0) {
        if (s1[0x34] == 2) {
            func_8072DB68(3);
        }
        sp78[0x39] = 0x1E;
    }
    if (s1[0x35] == 0) {
        if (s1[0x34] == 1) {
            slotQueueUpdate(0xB, 1, 0);
            s1[0x35]++;
        } else if (s1[0x34] == 5) {
            slotQueueCancel(0xB, 0);
            s1[0x35]++;
        }
    }
    if (s1[0x34] == 1) {
        o = *(u8 **)(s1 + 0x30);
        o2 = *(u8 **)(o + 0x174);
        if (*(u16 *)(o2 + 0x1C) == 8 || *(u16 *)(o2 + 0x1C) == 0x13) {
            func_806086CC(*(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x80), *(f32 *)((u8 *)D_807FBB40 + 0x84), 0x187, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        func_80026D2C(s1[0x26] * 1.5);
    } else if (s1[0x34] < 5) {
        sv = 0;
        if (s1[0x26] != 0) {
            f = func_8002D2C0(s1);
            if (f != 0) {
                f = 1.5f * f + 1.5f;
                racePlayCheckpointSfx(sp78, 0x1E, f);
            }
            s1[0x26] = 0;
        }
        if (sp78[0x39] != 0) {
            f32 t = sp78[0x39];
            if (t > 10.0f) {
                sv = (s32)((t - 10.0f) * 204.8f);
                t = 300.0f;
                *(f32 *)(sp78 + 0x20) = func_80612794(sv) * t;
                *(f32 *)(sp78 + 0x24) = func_80612794(sv * 2) * t;
            } else {
                *(f32 *)(sp78 + 0x20) = 0.0f;
                *(f32 *)(sp78 + 0x24) = 0.0f;
            }
        }
        func_80026354(sp78, s1, 1);
        *(f32 *)((u8 *)D_807FBB40 + 0x80) += 20.0f * func_80612794((s32)(sv * 0.5f));
        func_80026D2C(*(f32 *)((u8 *)D_807FBB40 + 0xB8));
    } else if (s1[0x34] == 5) {
        *(s32 *)((u8 *)D_807FBB40 + 0x60) &= ~4;
        *(f32 *)((u8 *)D_807FBB40 + 0xB8) = 0.0f;
        for (i = 0; i != 2; i++) {
            if (*(s16 *)((u8 *)D_807FBB40 + i * 2 + 0x6E) != -1) {
                sfxStopSlotSound(D_807FBB40, i & 0xFF);
            }
        }
    }
    if (s1[0x29] != 0) {
        func_80026B20(s1);
    }
    if (s1[0x34] < 5) {
        if (s1[0x34] == 2) {
            off = 10.0;
        } else {
            off = -200.0f;
        }
        sp58 = *(f32 *)((u8 *)D_807FBB40 + 0x7C);
        sp50 = *(f32 *)((u8 *)D_807FBB40 + 0x84);
        sp54 = *(f32 *)((u8 *)D_807FBB40 + 0x80) + off;
        func_806F4D70(s1[0x28], sp58, sp54, sp50, 12.0f);
        func_806F4DC0(s1[0x28], (sp58 + *(f32 *)((u8 *)D_807FBB40 + 0x88)) * 0.5, sp54, (sp50 + *(f32 *)((u8 *)D_807FBB40 + 0x90)) * 0.5, 12.0f);
    }
    if (*(s32 *)((u8 *)D_807FBB40 + 0x60) & 4) {
        func_8068ECF4(1, 0xC8);
        func_8068ECF4(2, 0xC8);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    if (s1[0x34] > 0 && s1[0x34] < 5) {
        renderCallbacksRegister(func_80026EE4, D_807FBB40, 3);
    }
}
#else

#pragma GLOBAL_ASM("asm/race/nonmatchings/1770/func_80026F04.s")
#endif

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
void func_80714CC0(void *, f32, f32, f32, f32);
void func_8002D338(void *, void *);

void func_800274C0(void) {
    u8 *sp4C;
    void *sp48;
    s32 pad[3];
    u8 var_v1;
    u16 *s1;
    u16 t3;

    var_v1 = 0;
    sp4C = *(u8 **)((u8 *)D_807FBB40 + 0x174);
    sp48 = *(void **)((u8 *)D_807FBB40 + 0x178);
    s1 = *(u16 **)((u8 *)D_807FBB40 + 0x17C);
    if (!(*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x10)) {
        *s1 = 0x78;
        *(s32 *)((u8 *)D_807FBB40 + 0x60) |= 0x10;
        *(u8 *)((u8 *)D_807FBB40 + 0x144) = 0x3C;
        *(f32 *)(sp4C + 4) = 5.0f;
    }
    if ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0) || (D_807FBB70.unk200 == 5)) {
        func_807149B8(1);
        func_80714CC0(D_80720340, 3.0f, *(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x80), *(f32 *)((u8 *)D_807FBB40 + 0x84));
        func_806086CC(*(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x80), *(f32 *)((u8 *)D_807FBB40 + 0x84), 0xF6, 0xFF, 0x7F, 0x14, 0x32, 0.3f, 0);
        var_v1 = 1;
    }
    func_80026354(sp48, sp4C, 0);
    *(f32 *)((u8 *)D_807FBB40 + 0x80) += 5.0f;
    if (*s1 != 0) {
        func_807149B8(1);
        func_80714CC0(D_8071FFA0, 1.0f, *(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x80) + 10.0f, *(f32 *)((u8 *)D_807FBB40 + 0x84));
        if (--*s1 == 0) {
            var_v1 = 1;
        }
    }
    if (var_v1 != 0) {
        func_8002D338(D_807FBB40, s1);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
