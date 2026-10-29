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

s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
s16 func_806CC190(s16, s16, f32);
f32 func_80611BB4(f32, f32);
void func_8060E7EC(s32, s32, s32);
void bonusResetAmmo(void *);
extern u16 D_807FD63C;
struct Struct_71B4;
typedef struct {
    struct Struct_71B4 *unk0;
    u8 unk4[4];
    u8 unk8;
    u8 unk9;
    char padA[7];
    u8 unk11;
    char pad12[0xA];
    u8 unk1C;
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

typedef struct Struct_71B4 {
    Actor_BB44 *unk0[6];
    char pad18[3];
    u8 unk1B;
    u8 unk1C;
    char pad1D[3];
    s16 unk20;
    s16 unk22;
    char pad24;
    u8 unk25;
    char pad26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    char pad2A[2];
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
void func_806FDAB8(u8, f32);
void actorUpdateModelMatrix(void *, s32);

extern u8 D_1000118[];
extern u8 D_2000180[];
Gfx *bonusRenderCrosshair();
Gfx *textDrawAnimated(Gfx *, s32, s32, f32, f32, f32, f32);
Gfx *func_8068DC54(Gfx *, s32, s32, void *, s32, void *);
extern u8 D_20000C0[];
extern u32 D_8076A064;
extern u8 D_807FC929;
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
extern s16 D_8002D8CA;
extern s16 D_8002D8D4[];
extern s16 D_8002D8E0[];
void actorClearAllNodeFlags(void *);
void actorAppendModelNode(void *, f32, f32, f32, f32, s32);
void lightGetColor(f32 *, f32 *, f32 *, s32);
void func_806BF920(void);
extern s16 D_80744490;
extern s16 D_80744494;
s32 func_8070E750(s32, s32, s32);
s32 textGetStringWidth(s32, s32);
s32 textGetFontHeight(s32);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, s32, s32);
void func_806F0C18(void *, s16 *);
void func_80613C48(void *, s16, f32, f32);
void func_80614644(void *, void *, s32);
extern f32 D_8002D90C;
f32 func_80612790(s16);
f32 func_80612794(s16);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxPlayFromActorDirect(void *, s32, s32, f32, s32, s32);
void sfxStopSlotSound();
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

Gfx *bonusRenderCrosshair(Gfx *gdl, Actor_74A0 *arg1) {
    Struct_7548 *temp_v0 = arg1->unk174;
    s16 sp6A = temp_v0->unk1E;
    s16 sp68 = temp_v0->unk20;
    s32 pad;

    gDPPipeSync(gdl++);
    gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(gdl++, D_1000118);
    gSPMatrix(gdl++, D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gdl = func_8068C5A8(gdl, (u16)((D_8076A064 >> 1) % 12 + 0x83), 0, 2, 0x20, 0x10, (s16)(sp6A - 0x34), (s16)(sp68 - 0x34), 3.2f, 3.2f, 0xE1, 0.0f);
    gdl = func_8068C5A8(gdl, (u16)((D_8076A064 >> 1) % 12 + 0x83), 0, 2, 0x20, 0x10, (s16)(sp6A + 0x34), (s16)(sp68 - 0x34), 3.2f, 3.2f, 0x13B, 0.0f);
    gdl = func_8068C5A8(gdl, (u16)((D_8076A064 >> 1) % 12 + 0x83), 0, 2, 0x20, 0x10, (s16)(sp6A + 0x34), (s16)(sp68 + 0x34), 3.2f, 3.2f, 0x2D, 0.0f);
    gdl = func_8068C5A8(gdl, (u16)((D_8076A064 >> 1) % 12 + 0x83), 0, 2, 0x20, 0x10, (s16)(sp6A - 0x34), (s16)(sp68 + 0x34), 3.2f, 3.2f, 0x87, 0.0f);
    return gdl;
}

typedef struct {
    char pad0[0x20];
    u8 unk20;
    char pad21;
    s16 unk22;
    u8 unk24;
    u8 unk25;
} BonusA_6940_178;
typedef struct {
    char pad[0x154];
    u8 unk154;
    char pad155[0x1F];
    Struct_6940_174 *unk174;
    BonusA_6940_178 *unk178;
} BonusA_Actor6940;

Gfx *bonusRenderTargetGameHud(Gfx *gdl, BonusA_Actor6940 *arg1) {
    Struct_6940_174 *temp_s1 = arg1->unk174;
    BonusA_6940_178 *temp_t0 = arg1->unk178;
    s32 pad1[4];
    s32 sp64;
    s32 pad2[6];
    s32 sp48;
    s32 pad3[4];
    s32 sp34;

    if (arg1->unk154 == 0) {
        if (temp_s1->unk26 != 0) {
            gdl = bonusRenderCrosshair(gdl, (Actor_74A0 *)arg1);
        }
    }
    gSPDisplayList(gdl++, D_1000118);
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gSPMatrix(gdl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (arg1->unk154 != 1) {
        gdl = func_8068DC54(textDrawAnimated(gdl, temp_t0->unk25, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &temp_t0->unk20, temp_t0->unk22, &temp_t0->unk24);
    }
    if (temp_s1->unk25 != 0) {
        sp48 = D_80744490 >> 1;
        sp64 = func_8070E750(0x1A, 6, 1);
        gDPPipeSync(gdl++);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, temp_s1->unk25);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        sp48 -= textGetStringWidth(1, sp64) >> 1;
        gdl = textDrawStringVtx(gdl, 1, sp48 << 2, (D_80744494 - textGetFontHeight(1)) * 2, sp64, 1);
        temp_s1->unk25 -= (temp_s1->unk25 < 8) ? temp_s1->unk25 : 8;
    }
    if (temp_s1->unk24 != 0) {
        sp34 = D_80744490 >> 1;
        sp64 = func_8070E750(0x1A, 8, 1);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, temp_s1->unk24);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        sp34 -= textGetStringWidth(1, sp64) >> 1;
        gdl = textDrawStringVtx(gdl, 1, sp34 << 2, (textGetFontHeight(1) + D_80744494) * 2, sp64, 1);
        temp_s1->unk24 -= (temp_s1->unk24 < 8) ? temp_s1->unk24 : 8;
    }
    return gdl;
}

typedef struct {
    char pad0[5];
    u8 unk5;
    char pad6[2];
    s16 unk8;
} BonusA_CF0_Inner;
typedef struct {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x174 - 0x88];
    BonusA_CF0_Inner *unk174;
} BonusA_CF0_S1;
typedef struct {
    char pad0[4];
    BonusA_CF0_S1 *unk4;
} BonusA_CF0_Link;
typedef struct {
    char pad0[0x174];
    BonusA_CF0_Link *unk174;
} BonusA_CF0_Actor;
typedef struct {
    BonusA_CF0_Actor *unk0[6];
} BonusA_CF0_List;
typedef struct {
    char pad0[0x154];
    u8 unk154;
    char pad155[0x1F];
    Struct_6940_174 *unk174;
    BonusA_CF0_List *unk178;
} BonusA_ActorCF0;
s32 gfxResourceCreate(s32, s32, s32, f32, f32, f32);
void gfxResourceFree(s16);

Gfx *bonusRenderPopupGameHud(Gfx *gdl, BonusA_ActorCF0 *arg1) {
    Struct_6940_174 *temp_s2 = arg1->unk174;
    BonusA_CF0_List *temp_list = arg1->unk178;
    s32 var_s5 = 0;
    s32 var_s1;
    s32 var_s3;
    s32 i;
    BonusA_CF0_S1 *temp_s1;
    BonusA_CF0_Inner *temp_inner;
    BonusA_CF0_Actor *temp_v0;
    BonusA_CF0_Link *temp_v1;

    if (arg1->unk154 == 0) {
        if (temp_s2->unk26 != 0) {
            gdl = bonusRenderCrosshair(gdl, (Actor_74A0 *)arg1);
        }
    }
    if (temp_s2->unk25 != 0) {
        var_s1 = D_80744490 >> 1;
        var_s3 = func_8070E750(0x1A, 6, 1);
        gDPPipeSync(gdl++);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, temp_s2->unk25);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        var_s1 -= textGetStringWidth(1, var_s3) >> 1;
        gdl = textDrawStringVtx(gdl, 1, var_s1 << 2, (D_80744494 - textGetFontHeight(1)) * 2, var_s3, 1);
        temp_s2->unk25 -= (temp_s2->unk25 < 8) ? temp_s2->unk25 : 8;
    }
    if (temp_s2->unk24 != 0) {
        var_s1 = D_80744490 >> 1;
        var_s3 = func_8070E750(0x1A, 7, 1);
        gDPPipeSync(gdl++);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, temp_s2->unk24);
        gDPSetCombineLERP(gdl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        var_s1 -= textGetStringWidth(1, var_s3) >> 1;
        gdl = textDrawStringVtx(gdl, 1, var_s1 << 2, (textGetFontHeight(1) + D_80744494) * 2, var_s3, 1);
        temp_s2->unk24 -= (temp_s2->unk24 < 8) ? temp_s2->unk24 : 8;
    }
    for (i = 0; i < 6; i++) {
        temp_v0 = temp_list->unk0[i];
        temp_v1 = temp_v0->unk174;
        temp_s1 = temp_v1->unk4;
        temp_inner = temp_s1->unk174;
        if (temp_inner->unk5 != 0 && arg1->unk154 == 0) {
            if (temp_inner->unk8 < 0) {
                temp_inner->unk8 = gfxResourceCreate(1, func_8070E750(0x1A, 9, 1), 9, temp_s1->unk7C * 0.25, temp_s1->unk80 * 0.25, temp_s1->unk84 * 0.25);
            }
            if (var_s5 == 0) {
                gSPDisplayList(gdl++, D_1000118);
                gDPPipeSync(gdl++);
                gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
                gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
                gSPSetGeometryMode(gdl++, G_SHADE | G_SHADING_SMOOTH);
                gDPSetCycleType(gdl++, G_CYC_1CYCLE);
                gSPMatrix(gdl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                var_s5 = 1;
            }
            gdl = textDrawAnimated(gdl, temp_inner->unk8, 9, temp_s1->unk7C, temp_s1->unk80 + 20.0f, temp_s1->unk84, 0.1f);
        } else if (temp_inner->unk8 >= 0) {
            gfxResourceFree(temp_inner->unk8);
            temp_inner->unk8 = -1;
        }
    }
    return gdl;
}

void bonusSpawnTarget(s16 arg0, s16 arg1, s16 arg2, u8 arg3, Struct_71B4 *arg4) {
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

void bonusDespawnTarget(Struct_174 *arg0, Struct_71B4 *arg1) {
    arg1->unk0[arg0->unk9] = 0;
    actorDespawn(D_807FBB40);
}

void bonusResetAmmo(void *arg0) {
    s16 i;
    s16 y;
    u8 *temp_s1;
    s32 *temp_s3;
    s32 p;
    y = 0x118;
    for (i = 0; i < 5; i++) {
        p = (s32)D_8071A038;
        temp_s3 = (s32 *)arg0 + i;
        if (temp_s3[1] != 0) {
            effectFreeAndUnlink(temp_s3[1]);
        }
        temp_s1 = (u8 *)arg0 + i;
        temp_s1[0x18] = 0;
        func_8071495C();
        func_807149FC(-1);
        func_80714998(2);
        func_80714944(i * 3);
        func_8071498C((void *)p);
        func_80714950(temp_s1 + 0x18);
        temp_s3[1] = func_80714CC0(D_8071FFD4, 1.0f, (f32) y, 210.0f, -10.0f);
        y -= 0x1E;
    }
    func_80609140(0x3E4, 0x7FFF, 63.0f, 1.0f, 5, 0);
}

void bonusFireProjectile(f32 arg0, f32 arg1, f32 arg2) {
    func_80609140(0x59, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
    projectileSetTargetCoords(D_807FBB40->unk7C, D_807FBB40->unk80 - 10.0f, D_807FBB40->unk84);
    projectileAimAndSpawn(0x23, 1, 0.6f, arg0, arg1, arg2, 385.0f, D_807FBB40);
}

u8 bonusAimAndFire(f32 arg0, f32 arg1, f32 arg2) {
    Struct_7548 *temp_s0 = D_807FBB40->unk174;
    f32 sp50;
    f32 sp4C;
    s16 var_v0;
    f32 temp_fv0;
    u8 sp40[1];

    sp40[0] = 0;
    temp_s0->unk26 = 1;
    camProjectToScreen(arg0, arg1, arg2, &sp50, &sp4C, 0, 4.0f, 0);
    temp_s0->unk1E = sp50;
    temp_s0->unk20 = sp4C;
    D_807FBB40->unkE6 = func_806CC190(D_807FBB40->unkE6, mathAngleBetweenPoints2D(arg0, arg2, D_807FBB40->unk7C, D_807FBB40->unk84), 10.0f);
    temp_fv0 = sqrtf((D_807FBB40->unk7C - arg0) * (D_807FBB40->unk7C - arg0) + (D_807FBB40->unk84 - arg2) * (D_807FBB40->unk84 - arg2));
    D_807FBB40->unkE8 = func_806CC190(D_807FBB40->unkE8, (s32)(func_80611BB4(D_807FBB40->unk80 - arg1, temp_fv0) * 2048.0 / 3.1415927f + 150.0), 5.0f);
    if ((D_807FD63C & 0xE000) != 0) {
        if (D_807FBB40->unk154 == 0) {
            sp40[0] = 1;
            if (temp_s0->unk22 != 0) {
                if (temp_s0->unk23 != 0 && temp_s0->unk18[0] == 0) {
                    bonusFireProjectile(arg0, arg1, arg2);
                    temp_s0->unk23--;
                    effectFreeAndUnlink(temp_s0->unk4[temp_s0->unk23]);
                    func_8060E7EC(0, 0xFF, 3);
                    temp_s0->unk4[temp_s0->unk23] = 0;
                    for (var_v0 = 0; var_v0 < temp_s0->unk23; var_v0++) {
                        temp_s0->unk18[var_v0] = 10;
                    }
                } else if (temp_s0->unk23 == 0) {
                    if (D_807FBB40->unk155 == 0) {
                        sp40[0] = 2;
                        D_807FBB40->unk155 = 1;
                    }
                }
            } else if (temp_s0->unk23 < 5) {
                temp_s0->unk23 = 5;
                bonusResetAmmo(temp_s0);
                D_807FBB40->unk155 = 0;
            }
        }
    }
    return sp40[0];
}

typedef struct {
    s16 unk0;
    char pad2[0x20];
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
} BonusB2_Sub174;

typedef struct BonusB2_Actor {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x84];
    s16 unkE8;
    char padEA[0x11C - 0xEA];
    struct BonusB2_Actor *unk11C;
    char pad120[0x154 - 0x120];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    BonusB2_Sub174 *unk174;
    Struct_71B4 *unk178;
} BonusB2_Actor;

typedef struct {
    char pad0[0x2E];
    s8 unk2E;
    s8 unk2F;
    u8 unk30;
    u8 unk31;
} BonusB_Ctrl;

#define BB2 ((BonusB2_Actor *)D_807FBB40)

extern s32 D_8076A0A8;
extern void *D_807FD580;

typedef struct {
    char pad0[0x104];
    void *unk104;
} BonusB_Cam;

#define BCAM ((BonusB_Cam *)D_807FD580)

extern BonusB_Ctrl D_807FD610;
extern u8 D_807444EC;
s32 playerStateQueueCallback(s32, s32, s32);
void camSetTarget(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
u16 camStartPath(s32, s32, s32);
void bonusEndLose(u8, u8);
void bonusEndWin(u8, u8);
void actorSetStateTwo(void *);
void sfxAllocateChannel(s32, f32);
void func_806A2A10(s32, s32, u8);
void func_8070D8C0(void *, s32, s32);

void renderCallbacksRegister(void *, void *, s32);

void bonusTargetGameUpdate(void) {
    BonusB2_Sub174 *t3c = BB2->unk174;
    Struct_71B4 *t0 = BB2->unk178;
    Point3f *p;
    f32 ang;
    f32 ang2;
    u8 c;
    s32 r;
    u8 idx;

    if (!(BB2->unk60 & 0x10)) {
        c = gfxResourceCreate(1, func_8070E750(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        t0->unk25 = c;
        func_806FDAB8(c, 0.0f);
        t3c->unk23 = 5;
        t3c->unk0 = -2;
        t3c->unk22 = 0;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(BCAM->unk104, D_807FBB40, 4, 0x800, -7, 0, 0x16, 0x2C, 4, 0, 0.05f);
        camStartPath(0, 0, 1);
        BB2->unkE8 = 0x310;
        switch (D_8076A0A8) {
        case 0xA:
            t0->unk27 = 0x55;
            t0->unk28 = 0x46;
            t0->unk2C = 0.85f;
            t0->unk20 = 0x12;
            t0->unk22 = t0->unk20;
            t0->unk29 = 0x3C;
            break;
        case 0x73:
            t0->unk27 = 0x5A;
            t0->unk28 = 0x46;
            t0->unk2C = 1.0f;
            t0->unk20 = 0x16;
            t0->unk22 = t0->unk20;
            t0->unk29 = 0x3C;
            break;
        case 0x74:
            t0->unk27 = 0x57;
            t0->unk28 = 0x50;
            t0->unk2C = 1.2f;
            t0->unk20 = 0x19;
            t0->unk22 = t0->unk20;
            t0->unk29 = 0x3C;
            break;
        case 0x75:
            t0->unk27 = 0x5C;
            t0->unk28 = 0x50;
            t0->unk2C = 1.3f;
            t0->unk20 = 0x1C;
            t0->unk22 = t0->unk20;
            t0->unk29 = 0x3C;
            break;
        }
    }
    if (t3c->unk0 > 0) {
        t3c->unk22 = 0;
        if (BB2->unk154 == 0 && (D_807FD610.unk30 >= 0x1F || D_807FD610.unk31 >= 0x1F)) {
            ang = func_80611BB4((f32)D_807FD610.unk2F, (f32)D_807FD610.unk2E) / 6.2831855f * 8.0 + 5.5;
            ang2 = ang;
            if (9.0f < ang) {
                ang2 = ang - 8.0f;
            }
            t3c->unk22 = (u32)ang2;
        }
        p = *D_807F5FD4 + t3c->unk22;
        if (bonusAimAndFire(p->x, p->y, p->z) == 2) {
            t3c->unk25 = 0xFF;
            func_80609140(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        switch (BB2->unk154) {
        case 0:
            if (BB2->unk11C->unk154 == 5) {
                BB2->unk154 = 0xFF;
            }
            if (t0->unk22 == 0) {
                bonusEndWin(0, 0);
                camStartPath(0, 1, 0x11);
                BB2->unk154 = 1;
            } else if (t0->unk27 < (randomNonNegative() >> 0xF) % 100) {
                r = (randomNonNegative() >> 0xF) % 0xFF;
                idx = r % 8;
                if (t0->unk0[idx] == 0) {
                    p = *D_807F5FD4 + idx + 1;
                    bonusSpawnTarget(p->x, p->y, p->z, idx, t0);
                }
            }
            if (BB2->unk11C->unk154 == 4 && BB2->unk11C->unk155 != 0xFF) {
                BB2->unk154 = 0xFE;
            }
            break;
        case 0xFE:
            t3c->unk24 = 0xFF;
            func_80609140(0x142, 0x7FFF, 63.0f, 1.0f, 0, 0);
            BB2->unk154 = 0;
            break;
        case 0xFF:
            bonusEndLose(0, 5);
            camStartPath(0, 1, 0x11);
            BB2->unk154 = 1;
            break;
        }
    } else {
        switch (t3c->unk0) {
        case -2:
            if (D_807444EC != 1) {
                t3c->unk0++;
                func_806A2A10(0xDC, 0x2A, t0->unk29);
                func_8070D8C0(D_807FBB40, 0, 1);
            }
            break;
        case -1:
            if (!(BB2->unk60 & 0x2000000)) {
                t3c->unk0 = 1;
                actorSetStateTwo(BB2->unk11C);
                bonusResetAmmo(t3c);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    if (t3c->unk0 >= -1) {
        renderCallbacksRegister(bonusRenderTargetGameHud, D_807FBB40, 3);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct {
    s16 unk0;
    char pad2[0x20];
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
} BonusB_Sub7F14;

typedef struct {
    Actor_BB44 *unk0[6];
    char pad18[2];
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    char pad1D[3];
    f32 unk20;
} BonusB_Sub178;

typedef struct BonusB_Actor7F14 {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x84];
    s16 unkE8;
    char padEA[0x11C - 0xEA];
    struct BonusB_Actor7F14 *unk11C;
    char pad120[0x154 - 0x120];
    u8 unk154;
    u8 unk155;
    char pad156[9];
    u8 unk15F;
    char pad160[0x14];
    BonusB_Sub7F14 *unk174;
    BonusB_Sub178 *unk178;
} BonusB_Actor7F14;

#define BB_B ((BonusB_Actor7F14 *)D_807FBB40)

void bonusPopupSpawnActors(BonusB_Sub178 *);

void bonusPopupGameUpdate(void) {
    BonusB_Sub7F14 *t0 = BB_B->unk174;
    BonusB_Sub178 *s38 = BB_B->unk178;
    Point3f *p;
    f32 y;
    f32 z;

    if (!(BB_B->unk60 & 0x10)) {
        t0->unk23 = 5;
        t0->unk0 = -2;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(BCAM->unk104, D_807FBB40, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        BB_B->unkE8 = 0x9A;
        switch (D_8076A0A8) {
        case 0x12:
            s38->unk20 = 0.5f;
            s38->unk1A = 0x2D;
            s38->unk1B = 0x1E;
            s38->unk1C = 0x46;
            break;
        case 0x76:
            s38->unk20 = 0.8f;
            s38->unk1A = 0x2D;
            s38->unk1B = 0x14;
            s38->unk1C = 0x46;
            break;
        case 0x77:
            s38->unk20 = 1.0f;
            s38->unk1A = 0x3C;
            s38->unk1B = 0x14;
            s38->unk1C = 0x46;
            break;
        case 0x78:
            s38->unk20 = 1.5f;
            s38->unk1A = 0x3C;
            s38->unk1B = 0x14;
            s38->unk1C = 0x46;
            break;
        }
        bonusPopupSpawnActors(s38);
    }
    if (BB_B->unk154 == 0) {
        BB_B->unk15F = 1;
    } else {
        BB_B->unk15F = 0;
    }
    if (t0->unk0 > 0) {
        t0->unk22 = 0;
        if (BB_B->unk154 == 0 && (D_807FD610.unk30 >= 0x1F || D_807FD610.unk31 >= 0x1F)) {
            if (D_807FD610.unk2F > 0) {
                if (D_807FD610.unk2E < -0x28) {
                    t0->unk22 = 1;
                } else if (D_807FD610.unk2E >= 0x29) {
                    t0->unk22 = 3;
                } else {
                    t0->unk22 = 2;
                }
            } else if (D_807FD610.unk2E < -0x28) {
                t0->unk22 = 4;
            } else if (D_807FD610.unk2E >= 0x29) {
                t0->unk22 = 5;
            } else {
                t0->unk22 = 6;
            }
        }
        p = *D_807F5FD4 + t0->unk22;
        y = p->y;
        z = p->z;
        if (t0->unk22 != 0) {
            y += 27.0f;
            z -= 8.0f;
        }
        switch (bonusAimAndFire(p->x, y, z)) {
        case 1:
            if (t0->unk22) {
                Actor_BB44 *e = s38->unk0[t0->unk22 - 1];
                if (e->unk174->unk1C == 0) {
                    e->unk174->unk1C = 6;
                }
            }
            break;
        case 2:
            t0->unk25 = 0xFF;
            func_80609140(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (BB_B->unk154) {
        case 0:
            if (BB_B->unk11C->unk154 == 5) {
                BB_B->unk154 = 0xFF;
            }
            if (BB_B->unk11C->unk154 == 4 && BB_B->unk11C->unk155 != 0xFF) {
                BB_B->unk154 = 0xFE;
            }
            break;
        case 2:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            BB_B->unk154 = 1;
            BB_B->unk155 = 0;
            break;
        case 0xFE:
            t0->unk24 = 0xFF;
            BB_B->unk154 = 0;
            break;
        case 0xFF:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            BB_B->unk154 = 1;
            BB_B->unk155 = 1;
            break;
        }
    } else {
        switch (t0->unk0) {
        case -2:
            if (D_807444EC != 1) {
                t0->unk0++;
                func_806A2A10(0xDC, 0x2A, s38->unk1A);
                func_8070D8C0(D_807FBB40, 0, 2);
            }
            break;
        case -1:
            if (!(BB_B->unk60 & 0x2000000)) {
                t0->unk0 = 1;
                actorSetStateTwo(BB_B->unk11C);
                bonusResetAmmo(t0);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    if (t0->unk0 >= -1) {
        renderCallbacksRegister(bonusRenderPopupGameHud, D_807FBB40, 3);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct {
    char pad0[0x60];
    s32 unk60;
    char pad64[0xE0];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    Struct_174 *unk174;
} BonusB_Actor84C0;

#define BB_A ((BonusB_Actor84C0 *)D_807FBB40)

void bonusTargetUpdate(void) {
    Struct_174 *sub = BB_A->unk174;
    Struct_71B4 *p = sub->unk0;
    s32 step;

    if (!(BB_A->unk60 & 0x10)) {
        BB_A->unk144 = 0x24;
    }
    func_8072881C(0, sub->unk4, sub, p);
    switch (BB_A->unk154) {
    case 0:
        if (D_807FBB85 != 0) {
            if (p->unk22 - ((sub->unk8 != 0) ? 2 : 1) < 0) {
                p->unk22 = 0;
            } else {
                if (sub->unk8 != 0) {
                    step = 2;
                } else {
                    step = 1;
                }
                p->unk22 -= step;
            }
            func_806FDAB8(p->unk25, 3.1415927f);
            actorScriptStart(D_807FBB40, (sub->unk8 != 0) ? 0x212 : 0x210);
            BB_A->unk154 = 1;
            BB_A->unk155 = 0;
        } else if (BB_A->unk155 != 0) {
            bonusDespawnTarget(sub, p);
        }
        break;
    case 1:
        if (BB_A->unk155 != 0) {
            bonusDespawnTarget(sub, p);
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct {
    void *unk0;
    void *unk4;
    char pad8[9];
    u8 unk11;
} BonusB_Sub8648;

typedef struct {
    void *unk0;
    char pad4[2];
    u8 unk6;
    char pad7;
    s16 unk8;
} BonusB_Sub8648b;

void bonusPopupSpawnActors(BonusB_Sub178 *arg0) {
    s32 i;
    BonusB_Sub8648 *s2;
    BonusB_Actor84C0 *s5;
    Point3f *s3;

    for (i = 1; i != 7; i++) {
        if (actorSpawn(0x12C, 0x15) != 0) {
            s2 = (BonusB_Sub8648 *)D_807FBB44->unk174;
            s2->unk0 = D_807FBB40;
            s2->unk11 = (((randomNonNegative() >> 0xF) % 0x7FFF) % (arg0->unk1C - arg0->unk1B + 1)) + arg0->unk1B;
            s3 = *D_807F5FD4 + i;
            actorScriptStart(D_807FBB44, 0x1F5);
            D_807FBB44->unk7C = s3->x;
            D_807FBB44->unk80 = s3->y;
            D_807FBB44->unk84 = s3->z;
            D_807FBB44->unk60 |= 0x1000;
            D_807FBB44->unkE6 = 0x800;
            arg0->unk0[i - 1] = D_807FBB44;
            s5 = (BonusB_Actor84C0 *)D_807FBB44;
            if (actorSpawn(0x12D, 0x16) != 0) {
                BonusB_Sub8648b *v0 = (BonusB_Sub8648b *)D_807FBB44->unk174;
                v0->unk0 = s5;
                v0->unk6 = i - 1;
                s2->unk4 = D_807FBB44;
                v0->unk8 = -1;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002881C.s")

typedef struct {
    char pad0[0xC];
    f32 unkC;
    s8 unk10;
} BonusB_Par8E3C;

typedef struct {
    char pad0[0x174];
    BonusB_Par8E3C *unk174;
} BonusB_Parent8E3C;

typedef struct {
    BonusB_Parent8E3C *unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    char pad7[5];
    f32 unkC;
} BonusB_Sub8E3C;

typedef struct {
    char pad0[0x60];
    s32 unk60;
    char pad64[6];
    u16 unk6A;
    u16 unk6C;
    char pad6E[0xE];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x30];
    f32 unkB8;
    char padBC[4];
    f32 unkC0;
    f32 unkC4;
    char padC8[0x1C];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    char padEA[4];
    s16 unkEE;
    char padF0[0x84];
    BonusB_Sub8E3C *unk174;
} BonusB_Actor8E3C;

#define BB_C ((BonusB_Actor8E3C *)D_807FBB40)

extern s16 D_8002D8C0[];
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_8067ACB4(void *);
void actorApplyVelocity(void *);
void func_80665564(void *, f32);

void func_80028E3C(void) {
    BonusB_Sub8E3C *t0 = BB_C->unk174;
    BonusB_Par8E3C *p40 = t0->unk0->unk174;
    f32 temp;
    f32 c;
    f64 v;
    s16 idx;
    s32 a0;

    if (!(BB_C->unk60 & 0x10)) {
        BB_C->unkE6 = (randomNonNegative() >> 0xF) % 4096;
        BB_C->unkC4 = -10.0f;
        BB_C->unk6A &= 0xFFFE;
        func_80613C48(D_807FBB40, 0x688, 0.0f, 0.0f);
        func_80614D00(D_807FBB40, 1.0, 0.0f);
    }
    if (p40->unk10 == -1 && t0->unk4 == 0) {
        if (p40->unkC < 220.0f) {
            if (t0->unk5 == 0) {
                a0 = 0x7F;
                t0->unk5 = 1;
                idx = t0->unk6 % 3;
                if (t0->unk6 / 3 != 0) {
                    idx = 2 - idx;
                    a0 = 0x64;
                }
                idx = D_8002D8C0[idx];
                func_806086CC(BB_C->unk7C, BB_C->unk80, BB_C->unk84, idx, 0xFF, a0, 0, 0, 0.0f, 0);
            }
            if (p40->unkC < 40.0f) {
                t0->unk4 = 1;
                func_806086CC(BB_C->unk7C, BB_C->unk80, BB_C->unk84, 0x1ED, 0xFF, 0x7F, 0, 0, 0.0f, 0);
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x76, 0xFF, 0x7F, 0x1E);
                BB_C->unkEE = BB_C->unkE6;
                BB_C->unkB8 = 10.0f;
                actorScriptStart(t0->unk0, 0x1F7);
            }
        }
    }
    if (t0->unk4 == 0) {
        actorGetNodePos(t0->unk0, 1, &BB_C->unk7C, &BB_C->unk80, &BB_C->unk84);
    } else {
        if ((BB_C->unk6A & 1) && !(BB_C->unk6C & 1)) {
            BB_C->unkC0 = t0->unkC * -0.8f;
            v = -t0->unkC * 1.5;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xFF, (u8)((255.0 < v) ? 255.0 : v), 0x7F, 0xA);
        }
        BB_C->unkC0 = BB_C->unkC0 + BB_C->unkC4;
        t0->unkC = BB_C->unkC0;
        func_8067ACB4(D_807FBB40);
        actorApplyVelocity(D_807FBB40);
        func_80665564(D_807FBB40, 0);
    }
    BB_C->unkE6 = (f32)BB_C->unkE6 + p40->unkC;
    if (BB_C->unkE6 >= 0x1000) {
        BB_C->unkE6 -= 0x1000;
    }
    temp = 30000.0f / p40->unkC;
    BB_C->unkE4 = func_80612794(BB_C->unkE6) * -temp;
    BB_C->unkE8 = func_80612790(BB_C->unkE6) * temp;
    temp = temp * 0.006666667f;
    if (temp < 1.0f) {
        temp = 1.0f;
    } else {
        c = (temp > 2.5f) ? 2.5f : temp;
        temp = c;
    }
    func_80614D00(D_807FBB40, temp, 0.0f);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_80029364.s")

typedef struct {
    char pad0[3];
    u8 unk3;
    char pad4[2];
    char unk6[2];
    char unk8[2];
    s16 unkA;
} BonusC_9B9C_A;

typedef struct {
    char pad0[0x11];
    u8 unk11;
    char unk12[2];
    char unk14[2];
    s16 unk16;
} BonusC_9B9C_B;

typedef struct {
    char pad0[0x25];
    u8 unk25;
    char unk26[2];
    char unk28[2];
    s16 unk2A;
} BonusC_9B9C_C;

Gfx *func_80029B9C(Gfx *gdl, Actor_BB44 *arg1) {
    Actor_BB44 *actor;
    BonusC_9B9C_B *p0;
    BonusC_9B9C_A *p1;
    BonusC_9B9C_C *p2;

    p2 = (void *)arg1->unk174;
    p0 = arg1->unk178;
    if (p2) {
    }
    p1 = arg1->unk178;
    actor = arg1;

    if (actor->unk58 != 0x7E && actor->unk154 == 0 && ((u8 *)actor->unk174)[0x26] != 0) {
        gdl = bonusRenderCrosshair(gdl, (void *)arg1);
    }
    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (actor->unk58) {
    case 0x7D:
        if (actor->unk154 != 3) {
            gdl = func_8068DC54(textDrawAnimated(gdl, p0->unk11, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p0->unk14, p0->unk16, p0->unk12);
        }
        break;
    case 0x7C:
        if (actor->unk154 != 3) {
            gdl = func_8068DC54(textDrawAnimated(gdl, p1->unk3, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p1->unk8, p1->unkA, p1->unk6);
        }
        break;
    case 0x7E:
        switch (actor->unk154) {
        case 7:
            break;
        case 0:
        case 1:
        case 2:
            gdl = func_8068DC54(textDrawAnimated(gdl, p2->unk25, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p2->unk28, p2->unk2A, p2->unk26);
            break;
        }
        break;
    }
    return gdl;
}

typedef struct {
    void *unk0;
    u8 unk4;
} BonusC_9E54_S;

void func_80029E54(void *arg0) {
    void *a = arg0;
    s32 i;
    s16 *X = &D_8002D8CA - 1;
    s8 *base = ((Actor_BB44 *)a)->unk178;

    for (i = 1; i != 7; i++) {
        if (actorSpawn(0x147, X[i - 1]) != 0) {
            BonusC_9E54_S *temp_v1 = (BonusC_9E54_S *)D_807FBB44->unk174;
            s16 *temp_a1 = D_807FBB44->unk17C;
            f32 *pt;
            f32 scale;

            *temp_a1 = X[i - 1];
            temp_v1->unk0 = a;
            temp_v1->unk4 = i - 1;
            pt = (f32 *)((u8 *)*D_807F5FD4 + ((base + 8)[temp_v1->unk4] & 0x7F) * 12) + 3;
            D_807FBB44->unk7C = pt[0];
            D_807FBB44->unk80 = pt[1];
            D_807FBB44->unk84 = pt[2];
            D_807FBB44->unk154 = 0;
            D_807FBB44->unk60 |= 0x1000;
            D_807FBB44->unkE6 = 0x800;
            if (i != 6) {
                func_806F0C18(D_807FBB44, temp_a1);
                actorScriptStart(D_807FBB44, D_8002D8D4[i - 1]);
            }
            if (i != 6) {
                scale = 0.25f;
            } else {
                scale = 0.04f;
            }
            D_807FBB44->unk4->unk34 = scale;
            D_807FBB44->unk4->unk38 = scale;
            D_807FBB44->unk4->unk3C = scale;
        }
    }
}

void func_8002A010(void) {
    f32 scale;
    Struct_Sp50 *sp50;
    Actor_BB44 *v;
    Struct_T0 *sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 *p;
    s8 var_a3;
    s8 flags;
    Struct_4 *u4;

    sp50 = (Struct_Sp50 *)D_807FBB40->unk174;
    v = sp50->unk0;
    sp48 = (Struct_T0 *)v->unk178;
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (sp50->unk4 != 5) {
            actorClearAllNodeFlags(D_807FBB40);
            actorAppendModelNode(D_807FBB40, 0.0f, 50.0f, 0.0f, 80.0f, -1);
        }
        D_807FBB40->unk144 = 0x24;
    }
    p = (f32 *)((u8 *)*D_807F5FD4 + (sp48->unk8[sp50->unk4] & 0x7F) * 12) + 3;
    D_807FBB40->unk7C = p[0];
    D_807FBB40->unk80 = p[1];
    D_807FBB40->unk84 = p[2];
    lightGetColor(&sp44, &sp40, &sp3C, 0);
    if (sp44 < 0.1f) {
        D_807FBB40->unk144 = 0;
    } else {
        D_807FBB40->unk144 = 0x24;
    }
    var_a3 = 0;
    if (D_807FBB85 == 1 && sp48->unk0 >= -9) {
        var_a3 = 1;
    }
    if (sp50->unk4 != 5) {
        flags = sp48->unk8[sp50->unk4];
        if (flags & 0x80) {
            sp48->unk8[sp50->unk4] = flags & 0x7F;
            actorScriptStart(D_807FBB40, D_8002D8D4[sp50->unk4]);
        } else if (sp44 < 0.05f && D_807FBB40->unk4->unk68 != 0) {
            actorScriptStart(D_807FBB40, 0);
        }
        if (var_a3 != 0) {
            actorScriptStart(D_807FBB40, D_8002D8E0[sp50->unk4]);
            func_80609140(0x2A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
            if (sp48->unk16 != 0) {
                sp48->unk16 += 1;
            }
        }
        func_806BF920();
    } else {
        D_807FBB40->unk60 |= 0x1000;
        D_807FBB40->unkE6 += 0x12C;
        if (sp48->unk0 < -0x1C) {
            D_807FBB40->unk154 = 0;
        }
        u4 = D_807FBB40->unk4;
        scale = u4->unk34;
        if (D_807FBB40->unk154 == 1) {
            scale = scale - 0.005;
            if (scale < 0.0) {
                scale = 0.0f;
            }
        } else {
            scale = 0.04f;
        }
        u4->unk34 = scale;
        D_807FBB40->unk4->unk38 = scale;
        D_807FBB40->unk4->unk3C = scale;
        if (var_a3 != 0) {
            func_80609140(0x2A1, 0x7FFF, 63.0f, 1.0f, 0, 0);
            sp48->unk0 = 0;
            sp48->unk16 -= 1;
            D_807FBB40->unk154 = 1;
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct {
    s16 unk0;
    char pad2;
    u8 unk3;
    s16 unk4;
    u8 unk6;
    char pad7;
    s16 unk8;
    s16 unkA;
} LargeB1_Sub178;

extern s8 D_8002D904;
Gfx *func_80029B9C(Gfx *, Actor_BB44 *);

void func_8002A398(void) {
    BonusB2_Sub174 *t3c = BB2->unk174;
    LargeB1_Sub178 *t0 = (LargeB1_Sub178 *)BB2->unk178;
    Point3f *p;
    f32 y;
    f32 z;
    s32 n;
    s32 i;

    if (!(BB2->unk60 & 0x10)) {
        t3c->unk23 = 5;
        t3c->unk0 = -2;
        D_8002D904 = 0;
        switch (D_8076A0A8) {
        case 0x90:
            t0->unkA = 6;
            D_8002D900 = 0x15;
            break;
        case 0x91:
            t0->unkA = 8;
            D_8002D900 = 0x12;
            break;
        case 0x92:
            t0->unkA = 0xA;
            D_8002D900 = 0xF;
            break;
        case 0x93:
            t0->unkA = 0xC;
            D_8002D900 = 0xC;
            break;
        }
        t0->unk4 = 0x3C;
        t0->unk6 = 0;
        t0->unk8 = t0->unkA;
        t0->unk3 = gfxResourceCreate(1, func_8070E750(0x1A, 4, 1), 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(t0->unk3, 0.0f);
        t0->unk0 = 0x1E;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(*(void **)((u8 *)D_807FD580 + 0x104), D_807FBB40, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        BB2->unkE8 = 0x9A;
        for (i = 1; i != 7; i++) {
            if (actorSpawn(0x148, 0x21) != 0) {
                BonusC_9E54_S *u = (BonusC_9E54_S *)D_807FBB44->unk174;

                u->unk0 = D_807FBB40;
                u->unk4 = i;
                p = *D_807F5FD4 + i;
                D_807FBB44->unk7C = p->x;
                D_807FBB44->unk80 = p->y;
                D_807FBB44->unk84 = p->z + 45.0;
                D_807FBB44->unk154 = 0;
                D_807FBB44->unkE6 = 0x800;
                D_807FBB44->unk4->unk34 = 0.45f;
                D_807FBB44->unk4->unk38 = 0.45f;
                D_807FBB44->unk4->unk3C = 0.45f;
            }
        }
    }
    if (t3c->unk0 > 0) {
        if (t0->unk0 > 0) {
            t0->unk0--;
        } else {
            if (actorSpawn(0x149, 0x3D) != 0) {
                BonusC_9E54_S *u = (BonusC_9E54_S *)D_807FBB44->unk174;

                n = D_8002D904;
                u->unk0 = D_807FBB40;
                p = (Point3f *)((u8 *)*D_807F5FD4 + (n + n + n) * 12) + 1;
                D_807FBB44->unk7C = p->x + 50.0;
                D_807FBB44->unk80 = p->y + 12.0;
                D_807FBB44->unk84 = p->z - 5.0;
                D_807FBB44->unkE6 = -0x400;
                D_807FBB44->unk4->unk34 = 0.08f;
                if (u) {}
                D_807FBB44->unk4->unk38 = 0.08f;
                D_807FBB44->unk4->unk3C = 0.08f;
            }
            n = D_8002D904;
            t0->unk0 = 0x5A;
            ((s8 *)&D_8002D900)[4] = (1 - n) & 0xFFFF;
        }
        t3c->unk22 = 0;
        if (BB2->unk154 == 0 && (D_807FD610.unk30 >= 0x1F || D_807FD610.unk31 >= 0x1F)) {
            if (D_807FD610.unk2F > 0) {
                if (D_807FD610.unk2E < -0x28) {
                    t3c->unk22 = 1;
                } else if (D_807FD610.unk2E >= 0x29) {
                    t3c->unk22 = 3;
                } else {
                    t3c->unk22 = 2;
                }
            } else if (D_807FD610.unk2E < -0x28) {
                t3c->unk22 = 4;
            } else if (D_807FD610.unk2E >= 0x29) {
                t3c->unk22 = 5;
            } else {
                t3c->unk22 = 6;
            }
        }
        p = *D_807F5FD4 + t3c->unk22;
        y = p->y;
        z = p->z;
        if (t3c->unk22 != 0) {
            y += 27.0f;
            z -= 8.0f;
        }
        switch (bonusAimAndFire(p->x, y, z)) {
        case 1:
            break;
        case 2:
            t3c->unk25 = 0xFF;
            func_80609140(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (BB2->unk154) {
        case 0:
            if (t0->unk8 == 0) {
                BB2->unk154 = 2;
            }
            if (BB2->unk11C->unk154 == 5) {
                BB2->unk154 = 1;
            }
            break;
        case 1:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            BB2->unk154 = 3;
            break;
        case 2:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            BB2->unk154 = 3;
            break;
        }
    } else {
        switch (t3c->unk0) {
        case -2:
            if (D_807444EC != 1) {
                t3c->unk0++;
                func_806A2A10(0xDC, 0x2A, *((u8 *)t0 + 5));
                func_8070D8C0(D_807FBB40, 0, 0xB);
            }
            break;
        case -1:
            if (!(BB2->unk60 & 0x2000000)) {
                t3c->unk0 = 1;
                actorSetStateTwo(BB2->unk11C);
                bonusResetAmmo(t3c);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        }
    }
    renderCallbacksRegister(func_80029B9C, D_807FBB40, 3);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct {
    char pad[4];
    u8 unk4;
} BonusC_AAA4_T;

void func_8002AAA4(void) {
    Struct_AAA4_174 *sp64;
    Actor_AAA4_Target *temp_v1;
    f32 dx;
    f32 dz;
    s32 sp54;
    Struct_4_Unk0 *sp50;
    Struct_4 *temp_v0;
    BonusC_AAA4_T *new_var;
    s32 i;

    sp64 = (Struct_AAA4_174 *)D_807FBB40->unk174;
    temp_v0 = D_807FBB40->unk4;
    sp50 = temp_v0->unk0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x239);
        D_807FBB40->unk144 = 0x24;
        temp_v0 = D_807FBB40->unk4;
    }
    sp54 = temp_v0->unk64;
    if (sp54 == 0x239) {
        for (i = 0; i < gActiveActorCount; i++) {
            temp_v1 = gActiveActors[i].actor;
            if (temp_v1->unk58 == 0x149) {
                dx = temp_v1->unk7C - D_807FBB40->unk7C;
                dz = temp_v1->unk80 - D_807FBB40->unk80;
                if (dx < 5.0 && dx > -5.0 && dz < 20.0f && dz > -20.0) {
                    new_var = (BonusC_AAA4_T *)temp_v1->unk174;
                    new_var->unk4 = 8;
                    actorScriptStart(D_807FBB40, 0x23B);
                }
            }
        }
    }
    if ((sp54 == 0x239 || sp54 == 0x23B || (sp54 == 0x238 && sp50 != NULL && sp50->unk4 > 48.0f)) && D_807FBB85 == 1) {
        actorScriptStart(D_807FBB40, 0x23C);
        sp64->unk6 = ((func_806119A0() & 7) + 6) * D_8002D900;
    }
    if (sp54 == 0x23A) {
        sp64->unk6 -= 1;
        if (sp64->unk6 == 0) {
            actorScriptStart(D_807FBB40, 0x238);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct {
    char pad0[0xA];
    s16 unkA;
} BonusC_AD10_B;

typedef struct {
    BonusC_AD10_B *unk0;
    s8 unk4;
} BonusC_AD10_S;

void func_8002AD10(void) {
    Actor_74A0 *a;
    BonusC_AD10_S *sp28;
    Actor_BB44 *v;
    BonusC_AD10_B *sp20;
    f32 *p;

    sp28 = (BonusC_AD10_S *)D_807FBB40->unk174;
    v = (Actor_BB44 *)sp28->unk0;
    sp20 = (BonusC_AD10_B *)v->unk178;
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x2B5, sp20);
    }
    if (sp28->unk4 == 0 || sp28->unk4 >= 5) {
        D_807FBB40->unk7C = D_807FBB40->unk7C - 1.5;
    }
    p = (f32 *)*D_807F5FD4 + 9;
    if (D_807FBB40->unk7C < *p - 50.0) {
        if (sp20->unkA > 0) {
            sp20->unkA -= 1;
        }
        actorDespawn(D_807FBB40);
    }
    if (sp28->unk4 != 0) {
        sp28->unk4 -= 1;
        if (sp28->unk4 < 4) {
            if (sp28->unk4 == 3) {
                func_80609140(0x2D2, 0x7FFF, 63.0f, 7.12f, 0, 1);
            }
            D_807FBB40->unk4->unk34 *= 0.8f;
            D_807FBB40->unk4->unk38 *= 0.8f;
            D_807FBB40->unk4->unk3C *= 0.8f;
        }
        if (sp28->unk4 == 0) {
            actorDespawn(D_807FBB40);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002AED8.s")

typedef struct {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} BonusDModel;

typedef struct {
    char pad0[4];
    BonusDModel *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5E];
    s16 unkE6;
    char padE8[0x40];
    s16 unk128;
    char pad12A[0x1A];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    char pad155[0x1F];
    void *unk174;
} BonusDActor;
#define BDX ((BonusDActor *)D_807FBB40)

typedef struct {
    BonusDActor *unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
} BonusDB920Link;

typedef struct {
    f32 unk0;
    f32 unk4;
    char pad8[0x10];
    s16 unk18;
    char pad1A[0x10];
    s16 unk2A;
    s8 unk2C;
    s8 unk2D[2];
} BonusDB920Tgt;

void func_8002B920(void) {
    BonusDB920Link *temp_s1 = BDX->unk174;
    BonusDActor *sp48 = temp_s1->unk0;
    BonusDB920Tgt *temp_s2 = sp48->unk174;
    f32 sp40;
    f32 sp3C;
    f32 dx;

    if (!(BDX->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x32F);
        BDX->unk4->unk34 = 0.06f;
        BDX->unk4->unk38 = 0.06f;
        BDX->unk4->unk3C = 0.06f;
        sfxPlayActorSound(D_807FBB40, 0x10E, 0x3C, 1, 0, 0xFF, 1.0f, 0);
    }
    if (BDX->unk154 == 0) {
        if (temp_s2->unk2C == 0) {
            if (temp_s1->unkC > 0) {
                if (temp_s1->unkC == 0x28) {
                    sfxPlayFromActorDirect(D_807FBB40, 0x801, 0xFF, 3.0f, 2, 0);
                }
                temp_s1->unkC--;
                sp40 = 5.0f;
            } else {
                sp40 = 3.0f;
            }
            BDX->unkE6 -= func_806CC10C((s16)(mathAngleBetweenPoints2D(BDX->unk7C, BDX->unk84, temp_s1->unk4, temp_s1->unk8) + 0x800), BDX->unkE6) >> 3;
            BDX->unk7C += func_80612794(BDX->unkE6) * sp40;
            BDX->unk84 += func_80612790(BDX->unkE6) * sp40;
            temp_s1->unkE--;
            if (temp_s1->unkE <= 0) {
                s16 angle;

                if (temp_s1->unkC > 0) {
                    temp_s1->unkE = (func_806119A0() & 7) + 0xA;
                } else {
                    temp_s1->unkE = (func_806119A0() & 0x3F) + 0xF;
                }
                angle = (s16)mathAngleBetweenPoints2D(temp_s2->unk0, temp_s2->unk4, temp_s1->unk4, temp_s1->unk8);
                angle += ((func_806119A0() & 7) << 8) + 0x400;
                sp3C = func_806119FC() * 70.0;
                temp_s1->unk4 = func_80612794(angle) * sp3C + temp_s2->unk0;
                temp_s1->unk8 = func_80612790(angle) * sp3C + temp_s2->unk4;
            }
        } else {
            if (temp_s2->unk2C == 0x28) {
                sfxPlayFromActorDirect(D_807FBB40, 0x801, 0xFF, 3.0f, 2, 0);
            }
            BDX->unk80 = func_80612794(temp_s2->unk18) * 5.0 + (sp48->unk80 - 30.0);
        }
    } else {
        BDX->unk128 -= 4;
        if (BDX->unk128 < 5) {
            BDX->unk128 = 0;
            actorDespawn(D_807FBB40);
        }
    }
    if (sp48->unk154 == 2) {
        f32 dz;
        dx = func_80612794(sp48->unkE6) * 65.0f + sp48->unk7C;
        dz = func_80612790(sp48->unkE6) * 65.0f + sp48->unk84;
        dx -= BDX->unk7C;
        dz -= BDX->unk84;
        if (BDX->unk154 == 0) {
            if (dx < 12.0 && dx > -12.0 && dz < 12.0 && dz > -12.0) {
                s32 var_v0;

                sfxStopSlotSound(D_807FBB40, 0);
                actorScriptStart(D_807FBB40, 0x331);
                if (temp_s2->unk2A != 0) {
                    temp_s2->unk2A--;
                }
                var_v0 = 0;
                for (; var_v0 < 1; var_v0++) {
                    if (temp_s2->unk2D[var_v0] == 0) {
                        temp_s2->unk2D[var_v0] = 0x1E;
                        var_v0 = 1;
                    }
                }
                BDX->unk154 = 1;
                sfxPlayFromActorDirect(D_807FBB40, 0x16, 0xFF, 1.0f, 0x14, 0);
                BDX->unk128 = 0xFF;
                BDX->unk60 &= 0xFFFF7FFF;
            } else if (dx * dx + dz * dz < 900.0f) {
                temp_s1->unkC = 0x3C;
                temp_s1->unkE = 1;
            }
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct {
    char pad0[4];
    s32 unk4;
    char pad8[8];
    s16 unk10;
} BonusDBE44Anim;

typedef struct {
    BonusDBE44Anim *unk0;
    char pad4[0x30];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} BonusDBE44Model;

typedef struct BonusDBE44Actor BonusDBE44Actor;
typedef struct {
    BonusDBE44Actor *unk0;
} BonusDBE44Link;

struct BonusDBE44Actor {
    char pad0[4];
    BonusDBE44Model *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5E];
    s16 unkE6;
    s16 unkE8;
    char padEA[0x8A];
    BonusDBE44Link *unk174;
};

#define BDA ((BonusDBE44Actor *)D_807FBB40)
void func_8002BE44(void) {
    BonusDBE44Link *link = BDA->unk174;
    BonusDBE44Actor *temp_v1 = link->unk0;
    BonusDBE44Anim *sp24 = BDA->unk4->unk0;
    BonusDBE44Anim *var_t0 = temp_v1->unk4->unk0;
    s16 var_a1;

    if (!(BDA->unk60 & 0x10)) {
        BDA->unkE8 = 0;
        BDA->unkE6 = 0x800;
        func_80613C48(D_807FBB40, 0x5FB, 0, 0);
        BDA->unk4->unk34 = 0.2f;
        BDA->unk4->unk38 = 0.2f;
        BDA->unk4->unk3C = 0.2f;
    }
    BDA->unk7C = temp_v1->unk7C;
    BDA->unk80 = temp_v1->unk80 - 35.0;
    BDA->unk84 = temp_v1->unk84;
    if (sp24 != NULL) {
        if (var_t0 != NULL) {
            var_a1 = var_t0->unk10;
            if (var_a1 == 0x5FD) {
                var_a1 = 0x5FE;
            }
            if (var_a1 != sp24->unk10) {
                func_80613C48(D_807FBB40, var_a1, 0, 0);
            }
            func_80614644(D_807FBB40, sp24, var_t0->unk4);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct LargeB4Actor LargeB4Actor;
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 pad25;
    s16 unk26;
    s16 unk28;
    s8 unk2A[1];
} LargeB4Sub;

struct LargeB4Actor {
    char pad0[4];
    Struct_4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x94];
    LargeB4Actor *unk11C;
    char pad120[0x24];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    LargeB4Sub *unk174;
};

typedef struct {
    char pad0[4];
    s16 unk4;
    char pad6[2];
    f32 unk8;
    s16 unkC;
} LargeB4Spawn;

typedef struct {
    char pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0x7C];
    u16 *unk298;
    char pad29C[0x2C];
    s16 unk2C8;
    char pad2CA[0x26];
} LargeB4Player;

typedef struct {
    char pad0[2];
    s8 unk2;
    s8 unk3;
} LargeB4Ctrl;

extern void *D_807FBB4C;
extern LargeB4Player *D_807FC924;
extern LargeB4Ctrl *D_807ECDEC;
void lightSetColor(f32, f32, f32, s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
Gfx *func_8002CC08(Gfx *, Actor_BB44 *);

#define LB4A ((LargeB4Actor *)D_807FBB40)
#define LB4C ((LargeB4Actor *)D_807FBB4C)
void func_8002BF98(void) {
    f32 sp84;
    f32 fv0;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 fv1;
    f32 ft5;
    LargeB4Sub *temp_s5 = LB4A->unk174;
    LargeB4Spawn *temp_s0;
    s32 i;
    s8 *p;
    s16 sp5A;

    if (!(LB4A->unk60 & 0x10)) {
        LB4C->unk154 = 0x77;
        LB4C->unk155 = 0;
        LB4C->unk144 = 1;
        temp_s5->unk0 = 1.0f;
        temp_s5->unk4 = LB4A->unk7C;
        temp_s5->unk8 = LB4A->unk84;
        switch (D_8076A0A8) {
            case 0x67:
                temp_s5->unk28 = 4;
                D_8002D90C = 1.0f;
                break;
            case 0x8A:
                temp_s5->unk28 = 6;
                D_8002D90C = 1.3f;
                break;
            case 0x8B:
                temp_s5->unk28 = 8;
                D_8002D90C = 1.6f;
                break;
            case 0x8C:
                temp_s5->unk28 = 0xA;
                D_8002D90C = 1.9f;
                break;
        }
        temp_s5->unk24 = 0;
        temp_s5->unk26 = temp_s5->unk28;
        temp_s5->unk20 = 0x3C;
        temp_s5->unk23 = gfxResourceCreate(1, func_8070E750(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(temp_s5->unk23, 0.0f);
        LB4A->unk4->unk34 = 0.33f;
        LB4A->unk4->unk38 = 0.33f;
        LB4A->unk4->unk3C = 0.33f;
        camSetTarget(*(void **)((u8 *)D_807FD580 + 0x104), D_807FBB40, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        LB4A->unk154 = 3;
        temp_s5->unk14 = 0.0;
        temp_s5->unk18 = 0.0;
        temp_s5->unkC = 0.0;
        temp_s5->unk10 = 0.0;
        temp_s5->unk0 = 1.0;
        i = 0;
        p = (s8 *)temp_s5;
        do {
            i++;
            p[0x2A] = 1;
            p++;
        } while (i != 1);
    }
    for (i = 0, p = (s8 *)temp_s5; i < 1; i++, p++) {
        if (p[0x2A] > 0) {
            p[0x2A] = p[0x2A] - 1;
            if (p[0x2A] == 0 && actorSpawn(0x14B, 0x21) != 0) {
                temp_s0 = (LargeB4Spawn *)D_807FBB44->unk174;
                *(void **)temp_s0 = D_807FBB40;
                temp_s0->unkC = 2;
                temp_s0->unkC = (func_806119A0() & 0x3F) + 0xF;
                temp_s0->unk4 = func_806119A0() & 0xF;
                temp_s0->unk8 = func_806119FC() * 40.0 + 15.0;
                sp5A = temp_s0->unk4 * 0xC8 - 0x578;
                D_807FBB44->unk7C = func_80612794(sp5A) * temp_s0->unk8 + temp_s5->unk4;
                D_807FBB44->unk80 = D_807FBB40->unk80;
                D_807FBB44->unk84 = func_80612790(sp5A) * temp_s0->unk8 + temp_s5->unk8;
            }
        }
    }
    temp_s5->unk1C += 0x19;
    if (LB4A->unk154 == 0 || LB4A->unk154 == 1) {
        temp_s5->unk0 = temp_s5->unk0 - 0.03333333333333333;
        if (temp_s5->unk0 < 0.0) {
            temp_s5->unk0 = 0.0;
        }
    } else {
        temp_s5->unk0 = temp_s5->unk0 + 0.03333333333333333;
        if (temp_s5->unk0 > 1.0) {
            temp_s5->unk0 = 1.0;
        }
    }
    lightSetColor(temp_s5->unk0, temp_s5->unk0, temp_s5->unk0, -1);
    switch (LB4A->unk154) {
        case 0: {
            sp84 = func_80612794((&D_807FC924[D_807FC929])->unk2C8);
            fv0 = func_80612790((&D_807FC924[D_807FC929])->unk2C8);
            fv1 = temp_s5->unk14;
            sp7C = temp_s5->unk18;
            sp74 = D_807ECDEC->unk2 * 0.06f;
            ft5 = D_807ECDEC->unk3 * 0.06f;
            fv1 = ((sp74 * fv0) - (ft5 * sp84)) - fv1;
            temp_s5->unk14 = temp_s5->unk14 + fv1 * 0.155f;
            temp_s5->unk18 = temp_s5->unk18 + ((sp74 * sp84 + ft5 * fv0) - sp7C) * 0.25f;
            temp_s5->unkC = temp_s5->unkC + temp_s5->unk14;
            temp_s5->unk10 = temp_s5->unk10 - temp_s5->unk18;
            if (temp_s5->unk26 == 0) {
                LB4A->unk154 = 5;
            }
            if (LB4A->unk11C->unk154 == 5) {
                LB4A->unk154 = 6;
            }
            if (temp_s5->unk1E > 0) {
                temp_s5->unk1E = temp_s5->unk1E - 1;
            }
            if (temp_s5->unk1E <= 0 && (*(&D_807FC924[D_807FC929])->unk298 & 0xE000)) {
                func_80609140(0x59, 0x7FFF, 63.0f, 1.0, 0x1E, 0);
                sp7C = func_80612794(D_807FC924->unk2C8) * 30.0f + D_807FC924->unk210;
                sp78 = D_807FC924->unk214 - 25.0f;
                sp74 = func_80612790(D_807FC924->unk2C8) * 30.0f + D_807FC924->unk218;
                projectileSetTargetCoords(sp7C, sp78, sp74);
                projectileAimAndSpawn(0x23, 1, 0.8f, LB4A->unk7C, LB4A->unk80, LB4A->unk84, 625.0f, D_807FBB40);
                temp_s5->unk1E = 0x1E;
            }
            break;
        }
        case 3:
            if (D_807444EC != 1) {
                LB4A->unk154 = 4;
                func_806A2A10(0xDC, 0x2A, *((u8 *)temp_s5 + 0x21));
                func_8070D8C0(D_807FBB40, 0, 0xC);
            }
            break;
        case 4:
            if (!(LB4A->unk60 & 0x02000000)) {
                LB4A->unk154 = 0;
                actorSetStateTwo(LB4A->unk11C);
                sfxAllocateChannel(8, 1.0);
            }
            break;
        case 5:
        case 6:
            if (LB4A->unk154 == 6) {
                bonusEndLose(0, 1);
            } else {
                bonusEndWin(0, 0);
            }
            camStartPath(0, 1, 0x11);
            LB4A->unk154 = 7;
            break;
    }
    sp7C = temp_s5->unkC;
    sp74 = temp_s5->unk10;
    fv0 = sqrtf(sp7C * sp7C + sp74 * sp74);
    if (fv0 > 110.0f) {
        sp78 = 110.0f / fv0;
        temp_s5->unkC = sp7C * sp78;
        temp_s5->unk10 = sp74 * sp78;
    }
    LB4A->unk7C = func_80612794(temp_s5->unk1C) * 5.0 + (temp_s5->unk4 + temp_s5->unkC);
    LB4A->unk84 = func_80612790((s16)(temp_s5->unk1C * 2)) * 2.0 + (temp_s5->unk8 + temp_s5->unk10);
    LB4C->unk7C = temp_s5->unk4 + temp_s5->unkC * 0.5f;
    LB4C->unk80 = LB4A->unk80;
    LB4C->unk84 = temp_s5->unk8 + temp_s5->unk10 * 0.5f;
    renderCallbacksRegister(func_8002CC08, D_807FBB40, 3);
    lightAdd(LB4A->unk7C, LB4A->unk80 + 25.0, LB4A->unk84, LB4A->unk7C, LB4A->unk80, LB4A->unk84, 25.0f, 1, 0xFF, 0xFF, 0xFF);
}


typedef struct {
    char pad0[4];
    f32 unk4;
    f32 unk8;
    char padC[0x1C];
    s16 unk28;
    s8 unk2A[2];
} BonusDC8ECTgt;

typedef struct {
    BonusDActor *unk0;
    s16 unk4;
    char pad6[2];
    f32 unk8;
    s16 unkC;
} BonusDC8ECLink;

void func_8002C8EC(void) {
    s32 e1, e2, e3;
    f32 sp40;
    s32 d1, d2, d3;
    f32 sp30, sp34;
    s16 temp_s0_2;
    s32 var_v0;
    BonusDActor *temp_v0;
    BonusDC8ECLink *temp_s2 = BDX->unk174;
    BonusDC8ECTgt *temp_s3;

    temp_v0 = temp_s2->unk0;
    temp_s3 = temp_v0->unk174;

    if (!(BDX->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x232);
        BDX->unk144 = 0x24;
        BDX->unk4->unk34 = 0.25f;
        BDX->unk4->unk38 = 0.25f;
        BDX->unk4->unk3C = 0.25f;
    }
    if (BDX->unk154 == 0) {
        sp40 = D_8002D90C;
        temp_s0_2 = temp_s2->unk4 * 0xC8 - 0x578;
        sp30 = func_80612794(temp_s0_2) * temp_s2->unk8 + temp_s3->unk4;
        sp34 = func_80612790(temp_s0_2) * temp_s2->unk8 + temp_s3->unk8;
        BDX->unkE6 -= func_806CC10C(mathAngleBetweenPoints2D(BDX->unk7C, BDX->unk84, sp30, sp34) + 0x800, BDX->unkE6) >> 5;
        BDX->unk7C += func_80612794(BDX->unkE6) * sp40;
        BDX->unk84 += func_80612790(BDX->unkE6) * sp40;
        temp_s2->unkC--;
        if (temp_s2->unkC <= 0) {
            temp_s2->unkC = (func_806119A0() & 0x3F) + 0xF;
            temp_s2->unk4 += (func_806119A0() & 0xF) + 3;
            temp_s2->unk8 = 40.0 * func_806119FC() + 10.0;
        }
        if (D_807FBB85 == 1) {
            BDX->unk128 = 0xFF;
            BDX->unk60 &= 0xFFFF7FFF;
            actorScriptStart(D_807FBB40, 0x332);
            BDX->unk154 = 1;
            func_80609140(0x16, 0x7FFF, 63.0f, 1.0f, 0, 0);
            var_v0 = 0;
            if (temp_s3->unk28 != 0) {
                temp_s3->unk28--;
            }
            for (; var_v0 < 1; var_v0++) {
                if (temp_s3->unk2A[var_v0] == 0) {
                    temp_s3->unk2A[var_v0] = 0x1E;
                    var_v0 = 1;
                }
            }
        }
    } else {
        BDX->unk128 -= 4;
        if (BDX->unk128 < 5) {
            BDX->unk128 = 0;
            actorDespawn(D_807FBB40);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

Gfx *func_8002CC08(Gfx *arg0, Actor_BB44 *arg1) {
    Struct_CC08_174 *sp84;
    f32 sp80;
    f32 sp7C;
    s32 temp_v0;
    s16 sp76;
    s16 sp74;

    sp84 = (Struct_CC08_174 *)arg1->unk174;
    camProjectToScreen(arg1->unk7C, arg1->unk80, arg1->unk84, &sp80, &sp7C, 0, 1.0f, D_807FC929);
    sp76 = (f32)(sp80 * 4.0);
    sp74 = (f32)(sp7C * 4.0);
    gDPPipeSync(arg0++);
    gDPSetCombineMode(arg0++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(arg0++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(arg0++, D_1000118);
    gSPMatrix(arg0++, D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    temp_v0 = arg1->unk154;
    if (temp_v0 == 0 || temp_v0 == 1) {
        arg0 = func_8068C5A8(arg0, (u16)((D_8076A064 >> 1) % 12 + 0x83), 0, 2, 0x20, 0x10, (s16)(sp76 - 0x34), (s16)(sp74 - 0x34), 3.2f, 3.2f, 0xE1, 0.0f);
        arg0 = func_8068C5A8(arg0, (u16)((D_8076A064 >> 1) % 12 + 0x83), 0, 2, 0x20, 0x10, (s16)(sp76 + 0x34), (s16)(sp74 - 0x34), 3.2f, 3.2f, 0x13B, 0.0f);
        arg0 = func_8068C5A8(arg0, (u16)((D_8076A064 >> 1) % 12 + 0x83), 0, 2, 0x20, 0x10, (s16)(sp76 + 0x34), (s16)(sp74 + 0x34), 3.2f, 3.2f, 0x2D, 0.0f);
        arg0 = func_8068C5A8(arg0, (u16)((D_8076A064 >> 1) % 12 + 0x83), 0, 2, 0x20, 0x10, (s16)(sp76 - 0x34), (s16)(sp74 + 0x34), 3.2f, 3.2f, 0x87, 0.0f);
    }
    gSPMatrix(arg0++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (arg1->unk154) {
    case 7:
        do {
        } while (0);
        break;
    case 0:
    case 1:
        arg0 = func_8068DC54(textDrawAnimated(arg0, sp84->unk23, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &sp84->unk26, sp84->unk28, &sp84->unk24);
        break;
    }
    return arg0;
}
