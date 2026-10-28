#include "common.h"

typedef struct MinecartModelData {
    u8 pad0[0x34];
    f32 unk34;
    f32 unk38;
} MinecartModelData;

typedef struct MinecartFollowerActor {
    u8 pad0[4];
    MinecartModelData *unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
    s16 unkE8;
    u8 padEA[0x128 - 0xEA];
    s16 unk128;
    u8 pad12A[0x154 - 0x12A];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x15F - 0x156];
    u8 unk15F;
} MinecartFollowerActor;

typedef struct MinecartChildActor {
    u8 pad0[4];
    MinecartModelData *unk4;
    u8 pad8[0xEC - 8];
    s16 unkEC;
    u8 padEE[0x11C - 0xEE];
    void *unk11C;
    u8 pad120[0x168 - 0x120];
    s16 unk168;
} MinecartChildActor;

typedef struct MinecartRiddenCartFollower {
    u8 pad0[0xA4];
    f32 unkA4;
    u8 padA8[0x154 - 0xA8];
    u8 unk154;
} MinecartRiddenCartFollower;

typedef struct MinecartPlayerStateFollower {
    u8 pad0[0x88];
    MinecartRiddenCartFollower *unk88;
    u8 pad8C[0x104 - 0x8C];
    void *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} MinecartPlayerStateFollower;

typedef struct MinecartParamsFollower {
    u8 pad0[0xA];
    u8 unkA;
} MinecartParamsFollower;

typedef struct MinecartPlayerActorFollower {
    u8 pad0[0x7C];
    f32 unk7C;
    u8 pad80[0x84 - 0x80];
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
} MinecartPlayerActorFollower;

struct Struct_BB40;
struct StructBB4C;
struct ActorD580;
struct Struct_DC9C;

extern struct Struct_BB40 *D_807FBB40;
extern MinecartChildActor *D_807FBB44;
extern struct StructBB4C *D_807FBB4C;
extern struct ActorD580 *D_807FD580;
extern struct Struct_DC9C *D_807FDC9C;
extern u32 D_8076A064;

void behaviourFrameBegin(void);
void actorScriptStart(struct Struct_BB40 *, s32);
void actorSpawn(s32, s32);
void func_8067B238(void *, void *, f32);
s16 func_80613448(void *);
void func_806131D4(void *, s16);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s32 func_80724A20(void);
s16 func_806CC190(s16, s16, s32);
f32 func_80612794(s16);
f32 func_80612790(s16);
void actorUpdateModelMatrix(struct Struct_BB40 *, s32);

void minecartFollowerBehaviour(void) {
    u8 sp47;

    sp47 = 0x96;
    behaviourFrameBegin();
    if (!(((MinecartFollowerActor *)D_807FBB40)->unk60 & 0x10)) {
        actorScriptStart((struct Struct_BB40 *)D_807FBB40, 0x310);
        actorSpawn(0x11C, 0x4C);
        func_8067B238(D_807FBB44, D_807FBB40, (f32)(1.5 * (f64)((MinecartFollowerActor *)D_807FBB40)->unk4->unk38));
        D_807FBB44->unk11C = D_807FBB40;
        D_807FBB44->unk168 = -1;
        D_807FBB44->unk4->unk34 *= -1.0f;
        D_807FBB44->unkEC = 0x2BC;
        func_806131D4(D_807FBB44, func_80613448(D_807FBB44));
        actorSpawn(0x11C, 0x4C);
        func_8067B238(D_807FBB44, D_807FBB40, (f32)(1.5 * (f64)((MinecartFollowerActor *)D_807FBB40)->unk4->unk38));
        D_807FBB44->unk11C = D_807FBB40;
        D_807FBB44->unk168 = 1;
        D_807FBB44->unkEC = 0x2BC;
        func_806086CC(((MinecartFollowerActor *)D_807FBB40)->unk7C, ((MinecartFollowerActor *)D_807FBB40)->unk80, ((MinecartFollowerActor *)D_807FBB40)->unk84, 0x301, 0xFF, 0x7F, 0, 0, 0.0f, 0);
        ((MinecartFollowerActor *)D_807FBB40)->unk154 = 1;
        ((MinecartFollowerActor *)D_807FBB40)->unkE8 = 0x12C;
        ((MinecartFollowerActor *)D_807FBB40)->unk60 &= ~0x8000;
        ((MinecartFollowerActor *)D_807FBB40)->unk128 = 0x96;
    }
    if (func_80724A20()) {
        if (((MinecartPlayerStateFollower *)D_807FD580)->unk88->unk154 == 5) {
            if (((MinecartFollowerActor *)D_807FBB40)->unk154 == 6) {
                ((MinecartFollowerActor *)D_807FBB40)->unk154 = 5;
            } else if (((MinecartFollowerActor *)D_807FBB40)->unk154 == 5) {
                ((MinecartFollowerActor *)D_807FBB40)->unk154 = 6;
            }
        }
    }
    switch (((MinecartFollowerActor *)D_807FBB40)->unk154) {
    case 0:
        ((MinecartFollowerActor *)D_807FBB40)->unk80 += 5.0f;
        if (((MinecartFollowerActor *)D_807FBB40)->unk155++ >= 0x10) {
            ((MinecartFollowerActor *)D_807FBB40)->unk154 = 0x3B;
        }
        break;
    case 6:
        sp47 = 0xFA;
        if ((D_8076A064 % ((MinecartParamsFollower *)D_807FDC9C)->unkA) == 0) {
            func_806086CC(((MinecartFollowerActor *)D_807FBB40)->unk7C, ((MinecartFollowerActor *)D_807FBB40)->unk80, ((MinecartFollowerActor *)D_807FBB40)->unk84, 0x182, 0xFF, 0x7F, 0, 0, 0.3f, 0);
            actorSpawn(0x11F, 0x50);
            D_807FBB44->unk11C = D_807FBB40;
            func_8067B238(D_807FBB44, D_807FBB40, 0.06f);
            ((MinecartFollowerActor *)D_807FBB40)->unk15F++;
        }
        /* fallthrough */
    case 2:
    case 3:
    case 4:
    case 5:
        if (((MinecartFollowerActor *)D_807FBB40)->unk155 == 0xFF) {
            actorScriptStart((struct Struct_BB40 *)D_807FBB40, 0x311);
            ((MinecartFollowerActor *)D_807FBB40)->unk154 = 1;
        }
        /* fallthrough */
    case 1:
        ((MinecartFollowerActor *)D_807FBB40)->unkE6 = func_806CC190(((MinecartFollowerActor *)D_807FBB40)->unkE6, (((MinecartPlayerActorFollower *)D_807FBB4C)->unkE6 + 0x800) & 0xFFF, 0x41000000);
        ((MinecartFollowerActor *)D_807FBB40)->unk7C = (f32)(((f64)((func_80612794(((MinecartPlayerActorFollower *)D_807FBB4C)->unkE6) * (f32)sp47 + ((MinecartPlayerActorFollower *)D_807FBB4C)->unk7C) - ((MinecartFollowerActor *)D_807FBB40)->unk7C) * 0.3) + ((MinecartFollowerActor *)D_807FBB40)->unk7C);
        ((MinecartFollowerActor *)D_807FBB40)->unk84 = (f32)(((f64)((func_80612790(((MinecartPlayerActorFollower *)D_807FBB4C)->unkE6) * (f32)sp47 + ((MinecartPlayerActorFollower *)D_807FBB4C)->unk84) - ((MinecartFollowerActor *)D_807FBB40)->unk84) * 0.3) + ((MinecartFollowerActor *)D_807FBB40)->unk84);
        ((MinecartFollowerActor *)D_807FBB40)->unk7C += 4.0f * func_80612794(D_8076A064 * 0x35);
        ((MinecartFollowerActor *)D_807FBB40)->unk84 += 4.0f * func_80612790(D_8076A064 * 0x3E);
        ((MinecartFollowerActor *)D_807FBB40)->unk80 = (func_80612794(D_8076A064 * 0x32) * 10.0f) + (((MinecartPlayerStateFollower *)D_807FD580)->unk88->unkA4 + 30.0f);
        break;
    }
    actorUpdateModelMatrix((struct Struct_BB40 *)D_807FBB40, 0);
}

typedef struct TargetStruct {
    u8 pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
} TargetStruct;

typedef struct ActorSub {
    u8 pad0[0xA4];
    f32 unkA4;
    u8 padA8[0xB8 - 0xA8];
    f32 unkB8;
} ActorSub;

typedef struct ActorD580 {
    u8 pad0[0x88];
    ActorSub *unk88;
} ActorD580;

typedef struct StructBB4C {
    u8 pad0[0x7C];
    f32 unk7C;
    u8 pad80[0x84 - 0x80];
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
} StructBB4C;

struct Actor;

typedef struct Component {
    u8 pad0[0x34];
    u8 *unk34;
    u8 pad38[0x42 - 0x38];
    u8 unk42;
    u8 pad43[0x88 - 0x43];
    struct Actor *unk88;
} Component;

typedef struct Actor {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0x174 - 0xBC];
    Component *unk174;
} Actor;

typedef struct Struct_BB40_Sub2 {
    u8 pad0[4];
    u16 unk4;
} Struct_BB40_Sub2;

typedef struct Struct_BB40_Sub1 {
    u8 pad0[0x1C];
    Struct_BB40_Sub2 *unk1C;
} Struct_BB40_Sub1;

typedef struct AllocSub {
    s8 unk0;
    u8 unk1;
} AllocSub;

typedef struct CartSub {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0x30 - 0x12];
    AllocSub *unk30;
    AllocSub *unk34;
    u8 pad38[0x3A - 0x38];
    u8 unk3A;
    u8 pad3B;
    s16 unk3C;
} CartSub;

typedef struct Struct_BB40 {
    u8 pad0[4];
    Struct_BB40_Sub1 *unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0x154 - 0xBC];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x178 - 0x156];
    CartSub *unk178;
} Struct_BB40;

typedef struct Struct_DC90 {
    u8 pad0[0x26];
    s16 unk26;
    u8 pad28[0x35 - 0x28];
    u8 unk35;
} Struct_DC90;

typedef struct StructBB70_Sub {
    u8 pad0[2];
    s16 unk2;
    s16 unk4;
} StructBB70_Sub;

typedef struct StructBB70 {
    u8 pad0[0x15];
    u8 unk15;
    u8 pad16[0x200 - 0x16];
    u8 unk200;
    u8 pad201[0x254 - 0x201];
    u8 unk254;
    u8 pad255[0x278 - 0x255];
    StructBB70_Sub *unk278;
} StructBB70;

typedef struct Struct_DC9C {
    u8 pad0[0xD];
    u8 unkD;
} Struct_DC9C;

extern StructBB4C *D_807FBB4C;
extern ActorD580 *D_807FD580;
extern Struct_BB40 *D_807FBB40;
extern Struct_DC90 *D_807FDC90;
extern Actor *D_807FDC94;
extern Struct_DC9C *D_807FDC9C;
extern s32 D_80717D4C;
extern s32 D_8074E880[];
extern StructBB70 D_807FBB70;
extern s32 gCamActor;
extern s32 D_8076A0A8;
extern s32 D_8072030C;
extern s32 D_80028BD0;
void actorGetOrSetNodeScale(Struct_BB40 *, s32, f32);
void func_807149FC(s32);
void func_80714C08(void *, s32, Struct_BB40 *, s32, s32);
void minecartChooseBranchSide(CartSub *);
void minecartApplyJunction(CartSub *, void *, s32, s32);

f32 func_80612794(s16);
f32 func_80612790(s16);
s32 randomNonNegative(void);
void func_80714950(s32);
void func_8071498C(s32 *);
void func_807149B8(s32);
void func_80714A28(s32);
void func_80714CC0(s32, f32, f32, f32, f32);
void behaviourFrameBegin(void);
void func_80724CA4(s32, s32);
void sfxPlayFromActorWithAltitudeCheck(Struct_BB40 *, s32, s32, s32, s32);
void camStartShake(s32, s32, s32);
void func_8067E278(s32, s32);
void func_80724E48(s32);
s32 func_8072DE10(s32);
void actorScriptStart(Struct_BB40 *, s32);
void minecartStartScriptNearPlayer(void);
void func_8068ECF4(s32, s32);
void actorApproachTargetSpeed(s32);
void minecartFollowTrack(CartSub *, s32, s32);
void actorGetNodePos(Struct_BB40 *, s32, f32 *, f32 *, f32 *);
void func_8072177C(Struct_BB40 *, s16, s16, s16, s32, s32, s32, s32, s32);
void minecartPlayPassBySfx(CartSub *);
void actorUpdateModelMatrix(Struct_BB40 *, s32);
AllocSub *func_80610FE8(s32);
f32 sqrtf(f32);
u32 func_806119A0(void);
s32 minecartSetTargetAheadOfPlayer(TargetStruct *arg0, f32 arg1) {
    arg0->unkA = (s16) (s32) ((func_80612794(D_807FBB4C->unkE6) * (D_807FD580->unk88->unkB8 * arg1)) + D_807FBB4C->unk7C);
    arg0->unkC = (s16) (s32) D_807FD580->unk88->unkA4;
    arg0->unkE = (s16) (s32) ((func_80612790(D_807FBB4C->unkE6) * (D_807FD580->unk88->unkB8 * arg1)) + D_807FBB4C->unk84);
}

void minecartSpawnRandomParticle(void) {
    s32 unused;
    s32 sp28;
    s32 sp24;
    f32 f10;

    func_80714950(((randomNonNegative() >> 15) % 100) + 300);
    func_8071498C(&D_80717D4C);
    func_807149B8(1);
    func_80714A28(4);
    sp24 = randomNonNegative();
    sp28 = randomNonNegative();
    f10 = 10.0f;
    func_80714CC0(
        D_8074E880[((sp24 >> 15) % 1000) % 3],
        0.5f,
        (f32)((sp28 >> 15) % 20) + (D_807FBB40->unk7C - f10),
        D_807FBB40->unk80,
        (f32)((randomNonNegative() >> 15) % 20) + (D_807FBB40->unk84 - f10)
    );
}

typedef struct MinecartTargetStateChild {
    u8 pad0[0xA];
    s16 unkA;
    u8 padC[0xE - 0xC];
    s16 unkE;
    u8 pad10[0x2C - 0x10];
    s16 unk2C;
} MinecartTargetStateChild;

typedef struct MinecartFollowerChild {
    u8 pad0[4];
    f32 **unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE4 - 0x88];
    s16 unkE4;
    s16 unkE6;
    u8 padE8[0xEC - 0xE8];
    s16 unkEC;
    u8 padEE[0x11C - 0xEE];
    struct MinecartFollowerChild *unk11C;
    u8 pad120[0x128 - 0x120];
    s16 unk128;
    u8 pad12A[0x132 - 0x12A];
    s16 unk132;
    u8 pad134[0x154 - 0x134];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x15F - 0x156];
    u8 unk15F;
    u8 pad160[0x168 - 0x160];
    s16 unk168;
    u8 pad16A[1];
    u8 pad16B;
    u8 unk16C;
    u8 pad16D[7];
    MinecartTargetStateChild *unk174;
} MinecartFollowerChild;

typedef struct MinecartPlayerActorChild {
    u8 pad0[4];
    struct { u8 pad0[0x64]; u16 unk64; } *unk4;
    u8 pad8[0xE6 - 8];
    s16 unkE6;
} MinecartPlayerActorChild;

typedef struct MinecartPlayerStateChild {
    u8 pad0[0x88];
    struct { u8 pad0[0xA4]; f32 unkA4; u8 padA8[0x174 - 0xA8]; s16 *unk174; } *unk88;
    u8 pad8C[0x104 - 0x8C];
    void *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} MinecartPlayerStateChild;

typedef struct MinecartParamsChild {
    u8 pad0[0xB];
    u8 unkB;
} MinecartParamsChild;

void camSetTarget(void *, void *, s32, s16, s32, s32, s32, s32, s32, s32, f32);
void actorDespawn(void *);
void func_80613C48(void *, s32, f32, f32);

#define CB ((MinecartFollowerChild *)D_807FBB40)
#define CD ((MinecartPlayerStateChild *)D_807FD580)
#define C4C ((MinecartPlayerActorChild *)D_807FBB4C)

void minecartFollowerChildBehaviour(void) {
    s32 padA;
    MinecartTargetStateChild *sp68;
    s16 sp66;
    s32 padB;
    s32 padC;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    MinecartFollowerChild *s2;
    s16 *p;
    f64 d;
    f32 var;
    f32 x;
    s16 v;

    s2 = CB->unk11C;
    sp68 = s2->unk174;
    sp66 = CB->unk168 * CB->unkEC;
    if (!(CB->unk60 & 0x10)) {
        func_80613C48(D_807FBB40, 0x59C, 0.0f, 0.0f);
        CB->unk60 |= 0x800000;
        ((u8 *)CB)[0x16A] = 0xFF;
        ((u8 *)CB)[0x16B] = 0xFF;
        CB->unk16C = 0xFF;
        CB->unk60 &= ~0x8000;
        CB->unk128 = 0x96;
    }
    CB->unkE6 = s2->unkE6;
    CB->unk7C = (f32)(((f64)(((func_80612794((s16)(s2->unkE6 + sp66)) * 47.0f) + s2->unk7C) - CB->unk7C) * 0.3) + (f64)CB->unk7C);
    CB->unk84 = (f32)(((f64)(((func_80612790((s16)(s2->unkE6 + sp66)) * 47.0f) + s2->unk84) - CB->unk84) * 0.3) + (f64)CB->unk84);
    CB->unk80 = (f32)((f64)CB->unk80 + ((f64)((s2->unk80 - 10.0f) - CB->unk80) * 0.3));
    switch (s2->unk154) {
    case 2:
    case 3:
        if ((CB->unk168 == 1 && s2->unk154 == 2) || (CB->unk168 == -1 && s2->unk154 == 3)) {
            p = CD->unk88->unk174;
            minecartSpawnRandomParticle();
            switch (s2->unk155) {
            case 0:
                if (*p == 0) {
                    CB->unk155 = 0;
                    actorScriptStart(D_807FBB40, 0x312);
                    s2->unk155 = 1;
                    minecartSetTargetAheadOfPlayer((TargetStruct *)sp68, 2.2f);
                }
                break;
            case 1:
                d = (f64)CB->unk4[0][1] / 17.0;
                var = (d > 1.0) ? 1.0 : d;
                x = (f32)(((f64)func_80612790((s16)(s32)(var * 2048.0f + 2048.0f)) * 0.5) + 0.5);
                CB->unk7C = ((f32)sp68->unkA - CB->unk7C) * x + CB->unk7C;
                CB->unk80 = (CB->unk80 + 10.0f) + ((CD->unk88->unkA4 - (CB->unk80 + 10.0f)) * x);
                CB->unk84 = ((f32)sp68->unkE - CB->unk84) * x + CB->unk84;
                if (C4C->unk4->unk64 == 0x294 || (CB->unk4[0][1] > 16.0f && CB->unk4[0][1] < 18.0f)) {
                    CB->unk132 = 1;
                } else {
                    CB->unk132 = 0;
                }
                if (CB->unk155 != 0) {
                    s2->unk155 = 0xFF;
                }
                break;
            }
        }
        break;
    case 4:
    case 5:
        if ((CB->unk168 == 1 && s2->unk154 == 4) || (CB->unk168 == -1 && s2->unk154 == 5)) {
            minecartSpawnRandomParticle();
            switch (s2->unk155) {
            case 0:
                sp68->unk2C = 0x46;
                s2->unk155 = 1;
                CB->unk132 = 1;
                func_806086CC(CB->unk7C, CB->unk80, CB->unk84, 0x301, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            case 1:
                minecartSetTargetAheadOfPlayer((TargetStruct *)sp68, 0.3f);
                v = sp68->unk2C;
                sp68->unk2C = v - 1;
                if (v != 0) {
                    sp58 = (f32)(((f64)func_80612790((s16)(s32)(((f64)sp68->unk2C / 70.0) * 2048.0 + 2048.0)) * 0.5) + 0.5);
                    sp54 = func_80612794((s16)(s32)(2048.0f * sp58));
                    sp50 = func_80612794((s16)(s32)(sp58 * 1536.0f + 1024.0f)) * (f32)(CB->unk168 * -110);
                    sp4C = (f32)(((f64)func_80612790((s16)(s32)(sp58 * 4096.0f)) * 0.5 + 0.5) * 50.0 + -30.0);
                    CB->unk7C = ((func_80612794((s16)(C4C->unkE6 - 0x400)) * sp50 + (f32)sp68->unkA) - CB->unk7C) * sp54 + CB->unk7C;
                    CB->unk80 = CB->unk80 + (((CD->unk88->unkA4 + sp4C) - CB->unk80) * sp54);
                    CB->unk84 = ((func_80612790((s16)(C4C->unkE6 - 0x400)) * sp50 + (f32)sp68->unkE) - CB->unk84) * sp54 + CB->unk84;
                    if (sp68->unk2C < 0x10) {
                        CB->unk132 = 0;
                    }
                } else {
                    s2->unk155 = 0xFF;
                }
                break;
            }
            if (CB->unk168 == 1) {
                CB->unkE4 = func_806CC190(CB->unkE4, 0xC00, 0x40E00000);
            } else {
                CB->unkE4 = func_806CC190(CB->unkE4, 0x400, 0x40E00000);
            }
        }
        break;
    case 6:
        if (s2->unk155 == 0) {
            sp68->unk2C = ((MinecartParamsChild *)D_807FDC9C)->unkB;
            s2->unk155 = 1;
        }
        if (CB->unk168 == 1) {
            CB->unkE4 = func_806CC190(CB->unkE4, 0xC00, 0x41800000);
        } else {
            CB->unkE4 = func_806CC190(CB->unkE4, 0x400, 0x41800000);
        }
        v = sp68->unk2C;
        if (v != 0) {
            sp68->unk2C = v - 1;
        } else {
            s2->unk155 = 0xFF;
        }
        if (CB->unk155 == 0 && s2->unk15F == 4) {
            CD->unk1F0 |= 0x10000000;
            CB->unk15F = 0xB4;
            CB->unk155++;
        }
        CB->unkEC = func_806CC190(CB->unkEC, 0x64, 0x41200000);
        break;
    case 0x3B:
        actorDespawn(D_807FBB40);
        break;
    case 1:
        break;
    }
    if (s2->unk154 == 6) {
        if (CB->unk15F != 0) {
            CB->unk15F -= 0xC;
            camSetTarget(CD->unk104, CD->unk88, 4, (CB->unk15F << 12) / 360, 0x64, 0, 5, 0x23, 0x14, 0, 0.2f);
        }
    }
    if (s2->unk154 != 6) {
        if (CB->unkE4 != 0) {
            CB->unkE4 = func_806CC190(CB->unkE4, 0, 0x41000000);
            CB->unkEC = func_806CC190(CB->unkEC, 0x2BC, 0x41200000);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct MinecartTrackPoint {
    f32 x;
    f32 y;
    f32 z;
} MinecartTrackPoint;

typedef struct MinecartTrackCursor {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0x34 - 0x12];
    u8 *unk34;
} MinecartTrackCursor;

typedef struct MinecartRiddenCartTracker {
    u8 pad0[0x174];
    MinecartTrackCursor *unk174;
} MinecartRiddenCartTracker;

typedef struct MinecartPlayerStateTracker {
    u8 pad0[0x88];
    MinecartRiddenCartTracker *unk88;
    u8 pad8C[0x104 - 0x8C];
    void *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} MinecartPlayerStateTracker;

typedef struct MinecartPlayerPosition {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} MinecartPlayerPosition;

typedef struct MinecartTrackerActor {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xC0 - 0xBC];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0xE6 - 0xCC];
    s16 unkE6;
    u8 padE8[0xEC - 0xE8];
    s16 unkEC;
    s16 unkEE;
    s16 unkF0;
    u8 padF2[0x11C - 0xF2];
    struct MinecartTrackerActor *unk11C;
    u8 pad120[0x144 - 0x120];
    u8 unk144;
    u8 pad145[0x15F - 0x145];
    u8 unk15F;
    u8 pad160[0x168 - 0x160];
    s16 unk168;
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
} MinecartTrackerActor;

extern MinecartTrackPoint **D_807F5FD4;
extern u8 D_807FBB85;
extern MinecartPlayerPosition *D_807FC924;
extern s32 D_80720120;
void func_80613C48(void *, s32, f32, f32);
void animSetSpeed(void *, s32, f32);
void animSetLoopMode(void *, s32, s32);
void animSetLoopLimit(void *, s32, s32);
void actorApplyGravity(void);
void actorApplyVelocity(void *);
void func_80665564(void *, f32);
void actorDespawn(void *);
void camSetTargetScaled(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

#define MC ((MinecartTrackerActor *)D_807FBB40)
#define MD580 ((MinecartPlayerStateTracker *)D_807FD580)

void func_80027778(void) {
    f32 d;
    f32 dist;
    MinecartTrackCursor *sp64;
    s32 a;
    s16 sp5E;
    s16 sp5C;

    sp64 = MD580->unk88->unk174;
    sp5E = (s16)(s32)D_807F5FD4[MC->unk15F][MC->unk168].x;
    sp5C = (s16)(s32)D_807F5FD4[MC->unk15F][MC->unk168].z;
    if (!(MC->unk60 & 0x10)) {
        func_80613C48(MC, 0x5FF, 0.0f, 0.0f);
        animSetSpeed(MC, 0, 1.0f);
        animSetLoopMode(MC, 0, 0);
        animSetLoopLimit(MC, 0, -1);
        MC->unk144 = 0x24;
        if (MC->unk11C->unk15F == 1) {
            MC->unk15F = *sp64->unk34 & ~0xC0;
        } else {
            switch (*sp64->unk34 & ~0xC0) {
            case 1:
            case 2:
                MC->unk15F = (MC->unk11C->unk15F ^ 1) + 1;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                MC->unk15F = (MC->unk11C->unk15F % 4) + 3;
                break;
            case 7:
            case 8:
                MC->unk15F = (MC->unk11C->unk15F ^ 1) + 7;
                break;
            }
        }
        a = sp64->unk10 - 2;
        if (a < 0) {
            MC->unk168 = 0;
        } else {
            MC->unk168 = a;
        }
        MC->unkB8 = 1100.0f;
        MC->unkC0 = 400.0f;
        MC->unk60 |= 0x800000;
        MC->unk16A = 0xFF;
        MC->unk16B = 0xFF;
        MC->unk16C = 0xFF;
        MC->unkC4 = -10.0f;
        MC->unkC8 = -200.0f;
        MC->unkF0 = 0xB4;
        MC->unkEC = 0;
    }
    if (D_8076A064 % 3 == 0) {
        func_807149B8(1);
        func_80714CC0((s32)&D_80720120, 1.0f, MC->unk7C, MC->unk80 + 10.0f, MC->unk84);
    }
    MC->unkE6 = func_806CC190(MC->unkE6, mathAngleBetweenPoints2D((f32)sp5E, (f32)sp5C, MC->unk7C, MC->unk84), 0x40C00000);
    MC->unkEE = MC->unkE6;
    actorApplyGravity();
    actorApplyVelocity(MC);
    func_80665564(MC, 2.0 * func_80612794(D_8076A064 * 0x64) + 10.0);
    if (((f32)sp5E - MC->unk7C) * ((f32)sp5E - MC->unk7C) + ((f32)sp5C - MC->unk84) * ((f32)sp5C - MC->unk84) < 1600.0f) {
        MC->unk168++;
    }
    if (D_807FBB85 != 0 || (MC->unkF0--, MC->unkF0 == 0)) {
        if (MC->unk11C != NULL) {
            MC->unk11C->unk15F--;
        }
        if (MC->unk11C == NULL || MC->unk11C->unk15F == 0) {
            if (MD580->unk1F0 & 0x10000000) {
                MD580->unk1F0 &= ~0x10000000;
                camSetTargetScaled(MD580->unk104, MD580->unk88, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
            }
        }
        func_8067E278(0, 1);
        actorDespawn(MC);
    }
    dist = MC->unk7C - D_807FC924->unk210;
    dist = dist * dist;
    d = MC->unk80 - D_807FC924->unk214;
    dist = d * d + dist;
    d = MC->unk84 - D_807FC924->unk218;
    dist = d * d + dist;
    switch (MC->unkEC) {
    case 0:
    case 2:
        if (dist < 6400.0f) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x128, 0xFF, 0x7F, 0);
            MC->unkEC++;
        }
        break;
    case 1:
        if (dist > 10000.0f) {
            MC->unkEC++;
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

#undef MC
#undef MD580

void minecartStartScriptNearPlayer(void) {
    f32 dx, dy, dz;

    if (D_807FBB40->unk155 != 0) {
        return;
    }
    if (func_8072DE10(10000) != 0 ||
        (dx = D_807FDC94->unk7C - D_807FBB40->unk7C,
         dy = D_807FDC94->unk80 - D_807FBB40->unk80,
         dz = D_807FDC94->unk84 - D_807FBB40->unk84,
         dx * dx + dy * dy + dz * dz < 2500.0f)) {
        actorScriptStart(D_807FBB40, 0x280);
    }
}

void minecartChooseBranchSide(CartSub *arg0) {
    Component *c = D_807FDC94->unk174;
    Component *d = c->unk88->unk174;
    u8 b;
    b = *d->unk34 - 0x10;
    if (b < *((Component *)arg0)->unk34) { ((Component *)arg0)->unk42 = 1; return; }
    if (*((Component *)arg0)->unk34 < b) { ((Component *)arg0)->unk42 = 2; return; }
    ((Component *)arg0)->unk42 = 0;
}

void minecartAdjustTargetSpeed(void) {
    s32 temp_a0;
    s32 temp_v1_2;
    u16 temp_v1;
    u8 temp_v1_3;
    Component *comp = D_807FDC94->unk174;

    temp_v1 = D_807FBB40->unk4->unk1C->unk4;
    if (((s32) temp_v1 >= 0x47D1) && ((s32) temp_v1 < 0xB830)) {
        Struct_DC90 *dc90 = D_807FDC90;
        temp_v1_2 = dc90->unk26 - 5;
        if (temp_v1_2 < 9) {
            dc90->unk26 = 9;
            return;
        }
        dc90->unk26 = temp_v1_2;
        return;
    }
    if (((s32) temp_v1 < 0x3830) || ((s32) temp_v1 >= 0xC7D1)) {
        Struct_DC90 *dc90 = D_807FDC90;
        temp_v1_3 = D_807FDC9C->unkD;
        temp_a0 = dc90->unk26 + 5;
        if ((s32) temp_v1_3 < temp_a0) {
            dc90->unk26 = (s16) temp_v1_3;
            return;
        }
        dc90->unk26 = temp_a0;
        return;
    }
    D_807FDC90->unk26 = (s16) (s32) comp->unk88->unkB8;
}

void minecartPlayPassBySfx(CartSub *arg0) {
    f32 d;
    f32 dist = D_807FBB40->unk7C - D_807FDC94->unk7C;
    dist = dist * dist;
    d = D_807FBB40->unk80 - D_807FDC94->unk80;
    dist = d * d + dist;
    d = D_807FBB40->unk84 - D_807FDC94->unk84;
    dist = sqrtf(dist + d * d);
    if (dist < 200.0f) {
        if (++arg0->unk3A >= 9) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1F, 0xFF, (s16) (s32) (127.0f - (dist - (f32) arg0->unk3C)), 0);
            arg0->unk3A = (u8) (u32) (((f64) func_806119A0() / 4294967295.0) * 3.0);
        }
    }
    arg0->unk3C = (s16) (s32) dist;
}

void func_800280BC(void) {
    CartSub *cart;
    StructBB70_Sub *sub;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    AllocSub *alloc;
    cart = D_807FBB40->unk178;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(2, 1);
        D_807FDC90->unk35 = 6;
    }
    if (D_807FBB70.unk15 != 0) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF6, 0xFF, 0x7F, 0x1E);
        camStartShake(gCamActor, 0xA, 0x14);
        D_807FBB40->unk154 = 0x40;
        func_8067E278(0, 1);
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB70.unk254 != 0) {
            sub = D_807FBB70.unk278;
            alloc = func_80610FE8(2);
            alloc->unk0 = (s8) sub->unk2;
            alloc->unk1 = 0xFF;
            cart->unk34 = alloc;
            cart->unk10 = sub->unk4;
            D_807FDC90->unk26 = 0x46;
            D_807FBB40->unkB8 = 0.0f;
            D_807FBB40->unk154++;
            goto case_1;
        } else {
            func_80724E48(1);
            minecartStartScriptNearPlayer();
            actorUpdateModelMatrix(D_807FBB40, 0);
            return;
        }
    case 1:
case_1:
        func_80724E48(1);
        minecartStartScriptNearPlayer();
        minecartAdjustTargetSpeed();
        func_8068ECF4(6, 0xFF);
        actorApproachTargetSpeed(0x200);
        minecartFollowTrack(cart, 0x7FFF, 0x23);
        actorGetNodePos(D_807FBB40, 5, &sp44, &sp48, &sp4C);
        func_8072177C(D_807FBB40, (s16) (s32) sp44, (s16) (s32) sp48, (s16) (s32) sp4C, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        minecartPlayPassBySfx(cart);
        return;
    case 2:
        D_807FBB40->unk154 = 0x40;
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    default:
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    }
}

void func_8002835C(void) {
    CartSub *sp74;
    StructBB70_Sub *sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    AllocSub *temp_v0_2;
    s32 pad0, pad1, pad2;

    sp74 = (CartSub *) D_807FBB40->unk178;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        if ((D_8076A0A8 == 0x4D) || (D_8076A0A8 == 0x81) || (D_8076A0A8 == 0x82)) {
            actorGetOrSetNodeScale(D_807FBB40, 1, 50.0f);
        }
        func_807149B8(1);
        func_807149FC(-1);
        func_80714C08(&D_8072030C, 0x3E0F5C29, D_807FBB40, 0xB, 2);
        D_807FBB40->unk154 = 0;
    }
    if ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) {
        func_8067E278(0, 1);
        D_807FBB40->unk154 = 0x40;
        camStartShake(gCamActor, 0xA, 0x14);
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB70.unk254 != 0) {
            sp70 = D_807FBB70.unk278;
            temp_v0_2 = func_80610FE8(4);
            temp_v0_2->unk0 = (s8) sp70->unk2;
            temp_v0_2->unk1 = 0xFF;
            sp74->unk30 = temp_v0_2;
            sp74->unk34 = temp_v0_2;
            sp74->unk10 = 1;
            D_807FDC90->unk26 = sp70->unk4;
            D_807FBB40->unkB8 = 0.0f;
            D_807FBB40->unk154++;
            goto case_1;
        } else {
            actorUpdateModelMatrix(D_807FBB40, 0);
            return;
        }
    case 1:
case_1:
        if ((D_8076A0A8 == 0x4D) || (D_8076A0A8 == 0x81) || (D_8076A0A8 == 0x82)) {
            minecartChooseBranchSide(sp74);
            minecartApplyJunction(sp74, &D_80028BD0, 0, 3);
            actorGetNodePos(D_807FBB40, 1, &sp58, &sp5C, &sp60);
            actorGetNodePos(D_807FBB40, 2, &sp64, &sp68, &sp6C);
        }
        actorApproachTargetSpeed(0x200);
        minecartFollowTrack(sp74, 0x7FFF, 0x23);
        if ((D_807FBB40->unk154 == 2) && ((D_8076A0A8 == 0x4D) || (D_8076A0A8 == 0x81) || (D_8076A0A8 == 0x82))) {
            D_807FBB40->unk154 = 1;
            sp74->unk34 = (AllocSub *) ((u8 *) sp74->unk34 - 1);
        }
        actorGetNodePos(D_807FBB40, 5, &sp58, &sp5C, &sp60);
        func_8072177C(D_807FBB40, (s16) (s32) sp58, (s16) (s32) sp5C, (s16) (s32) sp60, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        minecartPlayPassBySfx(sp74);
        return;
    case 2:
        D_807FBB40->unk154 = 0x40;
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    default:
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    }
}

typedef struct MinecartTrackCartActor {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xE6 - 0xBC];
    s16 unkE6;
    u8 padE8[0x144 - 0xE8];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 pad155[0x178 - 0x155];
    CartSub *unk178;
} MinecartTrackCartActor;

extern s32 D_80028C34;
extern s32 D_80028C40;
extern s32 D_80028C48;
s32 mathAngleDistance(s16, s16);
s32 playerStateQueueCallback(s32, void *, s32);

void func_800286EC(void) {
    CartSub *sp84;
    s32 pad;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    Component *sp70;
    f64 t1;
    f64 t2;
    f64 t4;
    f64 t5;
    f32 dx;
    f32 dz;

    sp84 = ((MinecartTrackCartActor *)D_807FBB40)->unk178;
    behaviourFrameBegin();
    sp70 = D_807FDC94->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((MinecartTrackCartActor *)D_807FBB40)->unk144 = 0x3C;
        D_807FDC90->unk35 = 2;
        func_807149B8(1);
        func_807149FC(-1);
        func_80714C08(&D_8072030C, 0x3E0F5C29, D_807FBB40, 0xB, 2);
    }
    if (D_807FBB70.unk200 == 4) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF6, 0xFF, 0x7F, 0x1E);
        camStartShake(gCamActor, 0xA, 0x14);
        t1 = (f64)D_807FBB40->unkB8 * 1.2;
        if (t1 > 0.0) {
            t4 = t1;
        } else {
            t4 = -t1;
        }
        D_807FBB40->unkB8 = -t4;
        playerStateQueueCallback(0x34, D_807FBB40, 0);
    }
    func_80724A20();
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB70.unk254 != 0) {
            switch (D_8076A0A8) {
            case 0x37:
                sp84->unk34 = (AllocSub *)&D_80028C40;
                break;
            case 0x6A:
                sp84->unk34 = (AllocSub *)&D_80028C48;
                break;
            default:
                sp84->unk34 = (AllocSub *)&D_80028C34;
            }
            sp84->unk10 = 1;
            D_807FBB40->unkB8 = 0.0f;
            D_807FBB40->unk154++;
            goto case_1;
        } else {
            actorUpdateModelMatrix(D_807FBB40, 0);
            return;
        }
case_1:
    case 1:
        if (mathAngleDistance(mathAngleBetweenPoints2D(D_807FBB4C->unk7C, D_807FBB4C->unk84, D_807FBB40->unk7C, D_807FBB40->unk84), ((MinecartTrackCartActor *)D_807FBB40)->unkE6) >= 0x201 &&
            (dx = D_807FBB40->unk7C - D_807FBB4C->unk7C, dz = D_807FBB40->unk84 - D_807FBB4C->unk84, dx * dx + dz * dz < 22500.0f)) {
            D_807FDC90->unk26 = 0;
        } else {
            t2 = (f64)sp70->unk88->unkB8 * 1.4;
            if (t2 > 45.0) {
                t4 = t2;
            } else {
                t4 = 45.0;
            }
            if (t4 < 90.0) {
                if (t2 > 45.0) {
                    t5 = t2;
                } else {
                    t5 = 45.0;
                }
                D_807FDC90->unk26 = (s16)(s32)t5;
            } else {
                t5 = 90.0;
                D_807FDC90->unk26 = (s16)(s32)t5;
            }
        }
        actorApproachTargetSpeed(0x200);
        func_8068ECF4(6, 0xFF);
        minecartFollowTrack(sp84, 0x7FFF, 0x23);
        actorGetNodePos(D_807FBB40, 5, &sp74, &sp78, &sp7C);
        func_8072177C(D_807FBB40, (s16)(s32)sp74, (s16)(s32)sp78, (s16)(s32)sp7C, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        if (((MinecartTrackCartActor *)D_807FBB4C)->unk154 == 0x70 || sp84->unk10 == 0x90) {
            D_807FBB40->unk154++;
        }
        return;
    case 2:
        func_8067E278(0, 1);
        D_807FBB40->unk154 = 0x40;
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    default:
        actorUpdateModelMatrix(D_807FBB40, 0);
        return;
    }
}
