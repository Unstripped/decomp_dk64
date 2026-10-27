#include "common.h"

typedef struct {
    f32 pad0;
    f32 unk4;
} Struct_4_Unk0;

typedef struct {
    Struct_4_Unk0 *unk0;
    char pad4[0x30];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    char pad40[0x64 - 0x40];
    u16 unk64;
    char pad66[2];
    s32 unk68;
} Struct_4;

typedef struct {
    char pad[4];
    Struct_4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5E];
    s16 unkE6;
    s16 unkE8;
    char padEA[0x3E];
    s16 unk128;
    char pad12A[0x1A];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    struct Struct_7548 *unk174;
} Actor_74A0;

typedef struct Struct_7548 {
    void *unk0;
    s32 unk4[5];
    u8 unk18[5];
    char pad1D;
    s16 unk1E;
    s16 unk20;
    u8 unk22;
    u8 unk23;
    char pad24[2];
    u8 unk26;
} Struct_7548;
extern Actor_74A0 *D_807FBB40;

void actorDespawn(void *);
void func_80609140(s32, s32, f32, f32, s32, s32);
void projectileSetTargetCoords(f32, f32, f32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);

void func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
s16 func_806CC190(s16, s16, s32);
f32 func_80611BB4(f32, f32);
void func_8060E7EC(s32, s32, s32);
void func_8002733C(void *);
extern u16 D_807FD63C;
typedef struct {
    void *unk0;
    char pad4[4];
    u8 unk8;
    u8 unk9;
    char padA[7];
    u8 unk11;
} Struct_174;


typedef struct {
    char pad[4];
    Struct_4 *unk4;
    char pad8[0x50];
    s32 unk58;
    char pad5C[4];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5E];
    s16 unkE6;
    char padE8[0x6C];
    u8 unk154;
    char pad155[0x1F];
    Struct_174 *unk174;
    void *unk178;
    s16 *unk17C;
} Actor_BB44;

typedef struct {
    Actor_BB44 *unk0[6];
    char pad18[3];
    u8 unk1B;
    u8 unk1C;
    char pad1D[5];
    s16 unk22;
    char pad24;
    u8 unk25;
    char pad26[2];
    u8 unk28;
    char pad29[3];
    f32 unk2C;
} Struct_71B4;
typedef struct {
    s16 unk0;
    char pad2[6];
    s8 unk8[6];
    char padE[8];
    s16 unk16;
} Struct_T0;

typedef struct {
    Actor_BB44 *unk0;
    u8 unk4;
} Struct_Sp50;
typedef struct {
    char pad[0x23];
    u8 unk23;
    u8 unk24[2];
    u8 unk26[2];
    s16 unk28;
} Struct_CC08_174;
typedef struct {
    char pad[6];
    s16 unk6;
} Struct_AAA4_174;

typedef struct Actor_AAA4_Target {
    char pad[0x4];
    void *unk4;
    char pad8[0x50];
    s32 unk58;
    char pad5C[0x7C - 0x5C];
    f32 unk7C;
    f32 unk80;
    char pad84[0x174 - 0x84];
    struct {
        char pad[4];
        u8 unk4;
    } *unk174;
} Actor_AAA4_Target;

typedef struct {
    Actor_AAA4_Target *actor;
    s32 pad;
} ActorEntry_B930;

extern ActorEntry_B930 gActiveActors[];
extern u16 gActiveActorCount;
extern s16 D_8002D900;
typedef struct {
    char pad[0x24];
    u8 unk24;
    u8 unk25;
    u8 unk26;
} Struct_6940_174;
typedef struct {
    f32 unk0;
    f32 unk4;
    char pad8[0x10];
    s16 unk18;
    char pad1A[0x10];
    s16 unk2A;
    s8 unk2C;
    u8 unk2D;
} Struct_B920_S2;

typedef struct Actor_B920 Actor_B920;

typedef struct {
    Actor_B920 *unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
} Struct_B920_S1;

struct Actor_B920 {
    char pad[4];
    Struct_4 *unk4;
    char pad8[0x74];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5E];
    s16 unkE6;
    char padE8[0x40];
    s16 unk128;
    char pad12A[0x2A];
    u8 unk154;
    char pad155[0x1F];
    Struct_B920_S2 *unk174;
};

typedef struct {
    f32 x, y, z;
} Point3f;
extern Point3f **D_807F5FD4;

extern u8 D_807FBB85;
void func_8072881C(s32, void *, void *, void *);
void func_806FDAB8(u8, s32, void *, void *);
void actorUpdateModelMatrix(void *, s32);

extern u8 D_1000118[];
extern u8 D_2000180[];
Gfx *func_80026690();
Gfx *func_806FE078(Gfx *, u8, s32, f32, f32, f32, f32);
Gfx *func_8068DC54(Gfx *, s32, s32, void *, s32, void *);
extern u8 D_20000C0[];
extern u32 D_8076A064;
extern u8 D_807FC929;
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
extern s16 D_8002D8CA;
extern s16 D_8002D8D4[];
extern s16 D_8002D8E0[];
void actorClearAllNodeFlags(void *);
void actorAppendModelNode(void *, s32, f32, s32, f32, s32);
void lightGetColor(f32 *, f32 *, f32 *, s32);
void func_806BF920(void);
extern s16 D_80744490;
extern s16 D_80744494;
s32 func_8070E750(s32, s32, s32);
s32 func_806FBD5C(s32, s32);
s32 func_806FD894(s32);
Gfx *func_806FC530(Gfx *, s32, s16, s16, s32, s32);
void func_806F0C18(void *, s16 *);
void func_80613C48(void *, s16, f32, f32);
void func_80614644(void *, void *, s32);
extern f32 D_8002D90C;
f32 func_80612790(s16);
f32 func_80612794(s16);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxPlayFromActorDirect(void *, s32, s32, s32, s32, s32);
void sfxStopSlotSound(f32, s32, void *, s32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 func_806CC10C(s16, s16);
s32 func_806119A0(void);
f32 func_806119FC(void);
extern u8 D_8071A038[];
extern u8 D_8071FFD4[];
void func_80714944(s32);
void func_80714950(void *);
void func_8071495C(void);
void func_8071498C(void *);
void func_80714998(s32);
void func_807149FC(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
void effectFreeAndUnlink(s32);

extern Actor_BB44 *D_807FBB44;
s32 randomNonNegative(void);
s32 actorSpawn(s32, s32);
void actorScriptStart();
void func_80614D00(void *, f32, f32);

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80026690.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80026940.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80026CF0.s")

void func_800271B4(s16 arg0, s16 arg1, s16 arg2, u8 arg3, Struct_71B4 *arg4) {
    u8 var_a3;
    Struct_174 *temp_v1;

    if (arg4->unk28 < ((randomNonNegative() >> 0xF) % 100)) {
        var_a3 = 1;
    } else {
        var_a3 = 0;
    }
    if (actorSpawn(0xBA, var_a3 ? 0x32 : 0x33) != 0) {
        temp_v1 = D_807FBB44->unk174;
        actorScriptStart(D_807FBB44, var_a3 ? 0x211 : 0x20F);
        func_80614D00(D_807FBB44, arg4->unk2C, 0.0f);
        D_807FBB44->unk7C = (f32) arg0;
        D_807FBB44->unk80 = (f32) (arg1 - 0x19);
        D_807FBB44->unk84 = (f32) arg2;
        D_807FBB44->unkE6 = 0xC00;
        temp_v1->unk9 = arg3;
        temp_v1->unk8 = var_a3;
        temp_v1->unk0 = arg4;
        ((void **)arg4)[arg3] = D_807FBB44;
    }
}

void func_80027308(u8 *arg0, s32 *arg1) {
    arg1[arg0[9]] = 0;
    actorDespawn(D_807FBB40);
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002733C.s")

void func_800274A0(f32 arg0, f32 arg1, f32 arg2) {
    func_80609140(0x59, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
    projectileSetTargetCoords(D_807FBB40->unk7C, D_807FBB40->unk80 - 10.0f, D_807FBB40->unk84);
    projectileAimAndSpawn(0x23, 1, 0.6f, arg0, arg1, arg2, 385.0f, D_807FBB40);
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80027548.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_800277F8.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80027F14.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_800284C0.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80028648.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002881C.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80028E3C.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80029364.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80029B9C.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80029E54.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002A010.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002A398.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002AAA4.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002AD10.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002AED8.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002B920.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002BE44.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002BF98.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002C8EC.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002CC08.s")
