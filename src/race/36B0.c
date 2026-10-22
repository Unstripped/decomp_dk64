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

void func_8068EB3C(f32, f32, f32, Point3f *, Point3f *, Point3f *, Point3f *, f32 *, f32 *, f32 *);
f32 func_80027710(s32, s32, void *);

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_80027710.s")

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

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_80027920.s")

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

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_80027BD0.s")

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

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_80027CE8.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_800280E8.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_800282D8.s")

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

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_80028440.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_80028AD0.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/36B0/func_80028E20.s")

typedef struct {
    u8 pad0[0x15];
    u8 unk15;
    u8 pad16[0x200 - 0x16];
    u8 unk200;
} StructBB70_Race;
extern StructBB70_Race D_807FBB70;
extern u8 *D_807FDC9C;
void func_80729B00(void);
void func_80028E20(void *);
void func_8066EA90(void *, s32);
void *func_807270C0(s32, s32);
void func_8067E278(s32, s32);
void func_80671C0C(void *, s32, f32 *, f32 *, f32 *);
void func_8072177C(void *, s16, s16, s16, s32, s32, s32, s32, s32);
void func_80026354(void *, void *, s32);
void func_806319C4(void *, s32);

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
    func_80729B00();
    if (!(*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x10)) {
        func_80028E20(sp50);
        *(u8 *)((u8 *)D_807FBB40 + 0x144) = 0x3C;
        *(f32 *)(temp_s1 + 4) = 0.5f;
        func_8066EA90(D_807FBB40, 1);
        *(void **)(sp50 + 0x30) = func_807270C0(1, 0);
        *(s32 *)((u8 *)D_807FBB40 + 0x60) &= ~1;
    }
    temp_v0 = *(u8 **)(sp50 + 0x30);
    sp48 = *(u8 **)(temp_v0 + 0x178);
    if ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) {
        func_8067E278(0, 1);
        *(u8 *)((u8 *)D_807FBB40 + 0x154) = 0x40;
    }
    func_80671C0C(D_807FBB40, 6, &sp3C, &sp40, &sp44);
    func_8072177C(D_807FBB40, (s16)(s32)sp3C, (s16)(s32)sp40, (s16)(s32)sp44, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    func_80671C0C(D_807FBB40, 0xB, &sp3C, &sp40, &sp44);
    func_8072177C(D_807FBB40, (s16)(s32)sp3C, (s16)(s32)sp40, (s16)(s32)sp44, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    func_80026354(sp50, temp_s1, 1);
    if ((temp_s1[0x34] == 0) && (sp48[0x34] == 5)) {
        *(u8 *)(D_807FDC9C + 0x14) = 0;
        *(u8 *)((u8 *)D_807FBB40 + 0x154) = 0x40;
        temp_s1[0x34]++;
    }
    func_806319C4(D_807FBB40, 0);
}
