#include "common.h"

typedef struct {
    char pad[0x25];
    u8 unk25;
    u8 unk26;
} Struct_sp5C;

typedef struct {
    char pad0[0x4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    char pad14[0x20 - 0x14];
    s32 unk20;
    char pad24[0x27 - 0x24];
    u8 unk27;
    u8 unk28;
    char pad29[0x30 - 0x29];
    void *unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    char pad37[0x44 - 0x37];
    u8 unk44;
} Struct_sp58;

typedef struct {
    char pad[0x174];
    Struct_sp58 *unk174;
    Struct_sp58 *unk178;
    void *unk17C;
} Struct_sp54;

typedef struct {
    char pad[0x174];
    Struct_sp5C *unk174;
} Struct_arg0;

extern u8 D_807FC928;
extern Struct_sp54 *D_807FBB44;
typedef struct {
    char pad[0x34];
    f32 unk34[3];
} Actor_BB40_Sub4;

typedef struct {
    void *pad0;
    void *unk4;
    char pad8[0x10 - 0x8];
    u8 unk10;
} Struct_sp20;

typedef struct {
    char pad[0x4];
    Actor_BB40_Sub4 *unk4;
    char pad8[0x60 - 0x8];
    u32 unk60;
    char pad64[0x6A - 0x64];
    u16 unk6A;
    char pad6C[0x6E - 0x6C];
    s16 unk6E[2];
    char pad72[0x7C - 0x72];
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    char pad88[0xB8 - 0x88];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    char padCC[0xDC - 0xCC];
    s16 unkDC;
    s16 unkDE;
    char padE0[0xE4 - 0xE0];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    char padEA[0xEE - 0xEA];
    s16 unkEE;
    char padF0[0xF8 - 0xF0];
    s16 unkF8;
    char padFA[0x144 - 0xFA];
    u8 unk144;
    char pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
    char pad156[0x174 - 0x156];
    Struct_sp58 *unk174;
    Struct_sp58 *unk178;
    Struct_sp20 *unk17C;
} Actor_BB40;
extern Actor_BB40 *D_807FBB40;

void behaviourFrameBegin(void);
void func_8002DE78(void *, s32, void *, void *);
void actorOrNodeFlags(void *, s32, s32);
void func_8002E644(void *);
typedef struct {
    char pad[0x4];
    void *unk4;
    char pad8[0xF - 0x8];
    u8 unkF;
} Struct_8002B180_Arg1;
void func_8002B180(Struct_sp58 *, Struct_8002B180_Arg1 *);
void func_8002A7F8(Struct_sp58 *);
void func_800283D4(f32);
void actorUpdateModelMatrix(void *, s32);
extern void *D_8002FC70;
extern void *D_8002FCA0;
extern s16 D_80750AC8;
extern Actor_BB40 *D_807FBB40;

void playerStateQueueCallback();
void sfxStopSlotSound(Actor_BB40 *, u8);
void func_8070D8C0(Actor_BB40 *, s32, s32);
void func_8063DA40(s32, s32);
void flagSet(s32, s32, s32);
void hudSpawnTextScreen(s32);
void func_80026CA8(void);
void func_80026D2C(f32);
void func_8068ECF4(s32, u8);
void slotQueueUpdate(s32, s32, s32);
void slotQueueCancel(s32, s32);
void func_806F4D70(u8, s32, s32, s32, f32);
void renderCallbacksRegister(void *, void *, s32);
typedef struct {
    char pad[0x25];
    u8 unk25;
} Struct_DC90;

typedef struct {
    char pad[0x20];
    u8 *unk20;
} Struct_DC98;

typedef struct {
    char pad[0x11];
    u8 unk11;
} Struct_DC9C;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6;
    u8 unk7;
    u8 pad8[2];
} Struct_FDCA0_Sub;

typedef struct {
    char pad[0x14];
    Struct_FDCA0_Sub *unk14;
} Struct_FDCA0;


extern Struct_DC90 *D_807FDC90;
extern Struct_DC98 *D_807FDC98;
extern Struct_DC9C *D_807FDC9C;
extern Struct_FDCA0 *D_807FDCA0;

s32 func_8002E960(u8);
f32 func_8002F784(s32, Struct_sp58 *, void *);
s32 mathAngleDiscrete(f32, f32, s32, s32, f32);
s32 func_806CC10C(s16, s16);
f32 raceGetProgressPercent(s32, Struct_sp58 *, Struct_sp5C *);
f32 func_8002E1C8(void *, f32, void *, void *);
extern s32 D_807FBB64;
f32 func_80612794(s16);
f32 func_80612790(s16);
f32 func_80611BB4(f32, f32);
s16 mathAngleFromVector2D(f32, f32);
s16 func_806CC190(s16, s16, f32, s16);
void actorStepPhysics(Actor_BB40 *, s16, s16);
void actorApplyVelocity(Actor_BB40 *);
void func_80665564(Actor_BB40 *, s32);
void func_8002F490(Struct_sp58 *);
typedef struct {
    char pad[0x104];
    void *unk104;
} Struct_174;

typedef struct {
    char pad[0x174];
    Struct_174 *unk174;
} Struct_PlayerActor;

typedef struct {
    char pad[0x4];
    Struct_PlayerActor *unk4;
    char pad8[0x2F0 - 0x8];
} Struct_Player;

extern Struct_Player *D_807FC924;

typedef struct {
    char pad[0x28];
    u8 unk28;
} Struct_8002B610_Sub;

typedef struct {
    void *unk0;
    Struct_8002B610_Sub *unk4;
} Struct_8002B610_Arg1;

void func_8061C6A8(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_800282D8(void);

void func_8002D72C(void *);
void func_8002D754(void *);
s32 currentActorTestClearFlag(void);
void currentActorClearFlag(void);
void func_8061CB08(void);

void func_8002BBD0(void *, s32);
void actorSpawn(s32, s32);
void func_8002BC2C(void *, s32, void *, void *);
void *spawnNodeSpawnById(s32, s32, s32, s32, s32, s32, s32);
void func_8002BCB0(void *, s32, void *, void *);
void actorInitFromSpawnPoint(void *, void *);

void raceInitParticipants(Struct_arg0 *arg0) {
    Struct_sp5C *sp5C;
    Struct_sp58 *sp58;
    Struct_sp54 *sp54;
    s32 var_s1;
    s32 var_s0;
    s32 var_s5;

    var_s5 = D_807FC928;
    var_s1 = 0;
    sp5C = arg0->unk174;
    if (var_s5 == 1) {
        var_s5++;
    }
    func_8002BBD0(arg0, var_s5);
    for (var_s0 = 0; var_s0 < D_807FC928; var_s0++) {
        actorSpawn(0x142, 0x95);
        sp54 = D_807FBB44;
        sp58 = sp54->unk174;
        sp58->unk27 = 0;
        func_8002BC2C(arg0, var_s1, sp54, sp58);
        var_s1++;
        sp58->unk28 = var_s0;
    }
    var_s0 = 0;
    if (D_807FC928 == 1) {
        sp54 = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        sp58 = sp54->unk178;
        sp58->unk27 = 1;
        func_8002BC2C(arg0, var_s1, sp54, sp58);
        func_8002BCB0(arg0, 0, sp54->unk17C, (u8 *)sp54->unk17C + 4);
        sp5C->unk25 = 1;
    } else {
        sp5C->unk25 = 0;
    }
    if (var_s5 > 0) {
        do {
            func_8002BCB0(arg0, var_s0, &sp54, &sp58);
            sp58->unk36 = var_s0;
            sp58->unk30 = arg0;
            actorInitFromSpawnPoint(sp54, sp58);
            var_s0++;
        } while (var_s0 != var_s5);
    }
    sp5C->unk26 = 0;
}

#pragma GLOBAL_ASM("asm/race/nonmatchings/6650/func_8002A7F8.s")

s32 func_8002CAC8(void *arg0, void *arg1, void *arg2);
void actorDrawAnimatedEffect(s32 arg0, void *arg1);

void func_8002AE6C(void *arg0, u8 *arg1) {
    actorDrawAnimatedEffect(func_8002CAC8(arg0, arg1, *(void **)(arg1 + 0x174)), arg1);
}

#pragma GLOBAL_ASM("asm/race/nonmatchings/6650/func_8002AE9C.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/6650/func_8002B180.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/6650/func_8002B518.s")
void func_8002B610(Struct_sp58 *arg0, Struct_8002B610_Arg1 *arg1) {
    if (arg0->unk35 == 0) {
        Struct_8002B610_Sub *sub = arg1->unk4;
        Struct_PlayerActor *actor = D_807FC924[sub->unk28].unk4;
        s32 a = 0xBE;
        s32 b = 0x4A;
        Struct_174 *unk174 = actor->unk174;
        s32 c = 0xAE;
        s32 d = 0x2D;
        func_8061C6A8(unk174->unk104, arg1->unk0, 4, 0x800, a, 0, b, c, d, 0, 0.2f);
        arg0->unk35++;
    }
    func_800282D8();
}

extern s32 D_8002FCAC[];
s32 func_8002E8EC(void *arg0, void *arg1, s32 arg2);

s32 func_8002B6C8(void *arg0, void *arg1) {
    return D_8002FCAC[func_8002E8EC(arg0, arg1, 10)];
}


s32 flagGet(s32, s32);
void func_8061CC40(void *, s32, s32);
void currentActorClearFlag(void);
void func_805FF544(void);

void func_8002B6F4(u8 *arg0, s32 arg1) {
    if (arg0[0x35] == 0) {
        if (flagGet(0x145, 0) == 0) {
            func_8061CC40(D_807FBB40, 1, 1);
            currentActorClearFlag();
        } else {
            func_805FF544();
        }
        arg0[0x35]++;
    }
}

#pragma GLOBAL_ASM("asm/race/nonmatchings/6650/func_8002B76C.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/6650/func_8002B964.s")
