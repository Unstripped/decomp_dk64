#include "common.h"
#include "actor.h"

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

typedef struct Struct_7548 {
    s16 unk0;
    char pad2[2];
    s32 unk4[5];
    u8 unk18[5];
    char pad1D;
    s16 unk1E;
    s16 unk20;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    u8 unk26;
} Struct_7548;
// Actor storage beyond the 0x178-byte Actor view (bonus actors keep a second payload pointer here).
typedef struct BonusActorExt {
    Actor actor;
    void *unk178;
    s16 *unk17C;
} BonusActorExt;

extern Actor *D_807FBB40;

void actorDespawn(void *);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void projectileSetTargetCoords(f32, f32, f32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);

s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
s16 mathAngleEaseToward(s16, s16, f32);
f32 func_80611BB4(f32, f32);
void rumbleRequest(s32, s32, s32);
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


typedef struct Struct_71B4 {
    Actor *unk0[6];
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
    Actor *unk0;
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
Gfx *textDrawAnimated(Gfx *, s32, s32, f32, f32, f32, f32);
Gfx *hudDrawRollingCounter(Gfx *, s32, s32, void *, s32, void *);
extern u8 D_20000C0[];
extern u32 gFrameCounter;
extern u8 gCurrentPlayerIndex;
Gfx *renderRotatedSprite(Gfx *, u16, s32, s32, s32, s32, s16, s16, f32, f32, s32, f32);
extern s16 D_8002D8CA;
extern s16 D_8002D8D4[];
extern s16 D_8002D8E0[];
void actorClearAllNodeFlags(void *);
void actorAppendModelNode(void *, f32, f32, f32, f32, s32);
void lightGetColor(f32 *, f32 *, f32 *, s32);
void func_806BF920(void);
extern s16 D_80744490;
extern s16 D_80744494;
s32 textTableGetString(s32, s32, s32);
s32 textGetStringWidth(s32, s32);
s32 textGetFontHeight(s32);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, s32, s32);
void func_806F0C18(void *, s16 *);
void func_80613C48(void *, s16, f32, f32);
void controllerApplyMotionWindow(void *, void *, f32);
extern f32 D_8002D90C;
f32 func_80612790(s16);
f32 func_80612794(s16);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxPlayFromActorDirect(void *, s32, s32, f32, s32, s32);
void sfxStopSlotSound();
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathAngleSignedDistance(s16, s16);
s32 randomLcgNext(void);
f32 randomFloat(void);
void effectSpriteMatrixUpdate();
extern u8 D_8071FFD4[];
void func_80714944(s32);
void func_80714950(void *);
void func_8071495C(void);
void func_8071498C(void *);
void func_80714998(s32);
void func_807149FC(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
void effectFreeAndUnlink(s32);

extern Actor *D_807FBB44;
s32 randomNonNegative(void);
s32 actorSpawn(s32, s32);
void actorScriptStart();
void scriptSetActorRampTarget(void *, f32, f32);

Gfx *bonusRenderCrosshair(Gfx *gdl, Actor *arg1) {
    Struct_7548 *temp_v0 = arg1->unk174;
    s16 sp6A = temp_v0->unk1E;
    s16 sp68 = temp_v0->unk20;
    s32 pad;

    gDPPipeSync(gdl++);
    gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(gdl++, D_1000118);
    gSPMatrix(gdl++, D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, sp6A - 0x34, sp68 - 0x34, 3.2f, 3.2f, 0xE1, 0.0f);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, sp6A + 0x34, sp68 - 0x34, 3.2f, 3.2f, 0x13B, 0.0f);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, sp6A + 0x34, sp68 + 0x34, 3.2f, 3.2f, 0x2D, 0.0f);
    gdl = renderRotatedSprite(gdl, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, sp6A - 0x34, sp68 + 0x34, 3.2f, 3.2f, 0x87, 0.0f);
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
Gfx *bonusRenderTargetGameHud(Gfx *gdl, Actor *arg1) {
    Struct_7548 *temp_s1 = arg1->unk174;
    BonusA_6940_178 *temp_t0 = ((BonusActorExt *)arg1)->unk178;
    s32 pad1[4];
    s32 sp64;
    s32 pad2[6];
    s32 sp48;
    s32 pad3[4];
    s32 sp34;

    if (arg1->unk154 == 0) {
        if (temp_s1->unk26 != 0) {
            gdl = bonusRenderCrosshair(gdl, arg1);
        }
    }
    gSPDisplayList(gdl++, D_1000118);
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gSPMatrix(gdl++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (arg1->unk154 != 1) {
        gdl = hudDrawRollingCounter(textDrawAnimated(gdl, temp_t0->unk25, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &temp_t0->unk20, temp_t0->unk22, &temp_t0->unk24);
    }
    if (temp_s1->unk25 != 0) {
        sp48 = D_80744490 >> 1;
        sp64 = textTableGetString(0x1A, 6, 1);
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
        sp64 = textTableGetString(0x1A, 8, 1);
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
s32 gfxResourceCreate(s32, s32, s32, f32, f32, f32);
void gfxResourceFree(s16);

Gfx *bonusRenderPopupGameHud(Gfx *gdl, Actor *arg1) {
    Struct_7548 *temp_s2 = arg1->unk174;
    BonusA_CF0_List *temp_list = ((BonusActorExt *)arg1)->unk178;
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
            gdl = bonusRenderCrosshair(gdl, arg1);
        }
    }
    if (temp_s2->unk25 != 0) {
        var_s1 = D_80744490 >> 1;
        var_s3 = textTableGetString(0x1A, 6, 1);
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
        var_s3 = textTableGetString(0x1A, 7, 1);
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
                temp_inner->unk8 = gfxResourceCreate(1, textTableGetString(0x1A, 9, 1), 9, temp_s1->unk7C * 0.25, temp_s1->unk80 * 0.25, temp_s1->unk84 * 0.25);
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
        scriptSetActorRampTarget(D_807FBB44, arg4->unk2C, 0.0f);
        D_807FBB44->unk7C = arg0;
        D_807FBB44->unk80 = arg1 - 0x19;
        D_807FBB44->unk84 = arg2;
        D_807FBB44->unkE6 = 0xC00;
        temp_v1->unk9 = arg3;
        temp_v1->unk8 = var_a3;
        temp_v1->unk0 = arg4;
        arg4->unk0[arg3] = D_807FBB44;
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
        p = (s32)effectSpriteMatrixUpdate;
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
    sfxPlayOnFreeSlot(0x3E4, 0x7FFF, 63.0f, 1.0f, 5, 0);
}

void bonusFireProjectile(f32 arg0, f32 arg1, f32 arg2) {
    sfxPlayOnFreeSlot(0x59, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
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
    D_807FBB40->unkE6 = mathAngleEaseToward(D_807FBB40->unkE6, mathAngleBetweenPoints2D(arg0, arg2, D_807FBB40->unk7C, D_807FBB40->unk84), 10.0f);
    temp_fv0 = sqrtf((D_807FBB40->unk7C - arg0) * (D_807FBB40->unk7C - arg0) + (D_807FBB40->unk84 - arg2) * (D_807FBB40->unk84 - arg2));
    D_807FBB40->unkE8 = mathAngleEaseToward(D_807FBB40->unkE8, (s32)(func_80611BB4(D_807FBB40->unk80 - arg1, temp_fv0) * 2048.0 / 3.1415927f + 150.0), 5.0f);
    if ((D_807FD63C & 0xE000) != 0) {
        if (D_807FBB40->unk154 == 0) {
            sp40[0] = 1;
            if (temp_s0->unk22 != 0) {
                if (temp_s0->unk23 != 0 && temp_s0->unk18[0] == 0) {
                    bonusFireProjectile(arg0, arg1, arg2);
                    temp_s0->unk23--;
                    effectFreeAndUnlink(temp_s0->unk4[temp_s0->unk23]);
                    rumbleRequest(0, 0xFF, 3);
                    temp_s0->unk4[temp_s0->unk23] = 0;
                    for (var_v0 = 0; var_v0 < temp_s0->unk23; var_v0++) {
                        temp_s0->unk18[var_v0] = 10;
                    }
                } else if (temp_s0->unk23 == 0) {
                    if (D_807FBB40->unk155[0] == 0) {
                        sp40[0] = 2;
                        D_807FBB40->unk155[0] = 1;
                    }
                }
            } else if (temp_s0->unk23 < 5) {
                temp_s0->unk23 = 5;
                bonusResetAmmo(temp_s0);
                D_807FBB40->unk155[0] = 0;
            }
        }
    }
    return sp40[0];
}

typedef struct {
    char pad0[0x2E];
    s8 unk2E;
    s8 unk2F;
    u8 unk30;
    u8 unk31;
} BonusB_Ctrl;

extern s32 gCurrentMap;
extern void *gActivePlayerState;
typedef struct {
    char pad0[0x104];
    void *unk104;
} BonusB_Cam104;
#define BB_CAMCTX ((BonusB_Cam104 *)gActivePlayerState)

typedef struct {
    char pad0[0x104];
    void *unk104;
} BonusB_Cam;

#define BCAM ((BonusB_Cam *)gActivePlayerState)

extern BonusB_Ctrl gPlayerPadState;
extern u8 D_807444EC;
s32 playerStateQueueCallback(s32, s32, s32);
void camSetTarget(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
u16 camStartPath(s32, s32, s32);
void bonusEndLose(u8, u8);
void bonusEndWin(u8, u8);
void actorSetStateTwo(void *);
void sfxAllocateChannel(s32, f32);
void hudSpawnCountdownTimer(s32, s32, u8);
void func_8070D8C0(void *, s32, s32);

void renderCallbacksRegister(void *, void *, s32);

void bonusTargetGameUpdate(void) {
    Struct_7548 *t3c = D_807FBB40->unk174;
    Struct_71B4 *t0 = ((BonusActorExt *)D_807FBB40)->unk178;
    Point3f *p;
    f32 ang;
    u8 c;
    s32 r;
    u8 idx;

    if (!(D_807FBB40->unk60 & 0x10)) {
        c = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        t0->unk25 = c;
        func_806FDAB8(c, 0.0f);
        t3c->unk23 = 5;
        t3c->unk0 = -2;
        t3c->unk22 = 0;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(BCAM->unk104, D_807FBB40, 4, 0x800, -7, 0, 0x16, 0x2C, 4, 0, 0.05f);
        camStartPath(0, 0, 1);
        D_807FBB40->unkE8 = 0x310;
        switch (gCurrentMap) {
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
        if (D_807FBB40->unk154 == 0 && (gPlayerPadState.unk30 >= 0x1F || gPlayerPadState.unk31 >= 0x1F)) {
            ang = func_80611BB4(gPlayerPadState.unk2F, gPlayerPadState.unk2E) / 6.2831855f * 8.0 + 5.5;
            if (9.0f < ang) {
                ang -= 8.0f;
            }
            t3c->unk22 = ang;
        }
        p = *D_807F5FD4 + t3c->unk22;
        if (bonusAimAndFire(p->x, p->y, p->z) == 2) {
            t3c->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        switch (D_807FBB40->unk154) {
        case 0:
            if (((Actor *)D_807FBB40->unk11C)->unk154 == 5) {
                D_807FBB40->unk154 = 0xFF;
            }
            if (t0->unk22 == 0) {
                bonusEndWin(0, 0);
                camStartPath(0, 1, 0x11);
                D_807FBB40->unk154 = 1;
            } else if (t0->unk27 < (randomNonNegative() >> 0xF) % 100) {
                r = (randomNonNegative() >> 0xF) % 0xFF;
                idx = r % 8;
                if (t0->unk0[idx] == 0) {
                    p = *D_807F5FD4 + idx + 1;
                    bonusSpawnTarget(p->x, p->y, p->z, idx, t0);
                }
            }
            if (((Actor *)D_807FBB40->unk11C)->unk154 == 4 && ((Actor *)D_807FBB40->unk11C)->unk155[0] != 0xFF) {
                D_807FBB40->unk154 = 0xFE;
            }
            break;
        case 0xFE:
            t3c->unk24 = 0xFF;
            sfxPlayOnFreeSlot(0x142, 0x7FFF, 63.0f, 1.0f, 0, 0);
            D_807FBB40->unk154 = 0;
            break;
        case 0xFF:
            bonusEndLose(0, 5);
            camStartPath(0, 1, 0x11);
            D_807FBB40->unk154 = 1;
            break;
        }
    } else {
        switch (t3c->unk0) {
        case -2:
            if (D_807444EC != 1) {
                t3c->unk0++;
                hudSpawnCountdownTimer(0xDC, 0x2A, t0->unk29);
                func_8070D8C0(D_807FBB40, 0, 1);
            }
            break;
        case -1:
            if (!(D_807FBB40->unk60 & 0x2000000)) {
                t3c->unk0 = 1;
                actorSetStateTwo((void *)D_807FBB40->unk11C);
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
    Actor *unk0[6];
    char pad18[2];
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    char pad1D[3];
    f32 unk20;
} BonusB_Sub178;

void bonusPopupSpawnActors(BonusB_Sub178 *);

void bonusPopupGameUpdate(void) {
    Struct_7548 *t0 = D_807FBB40->unk174;
    BonusB_Sub178 *s38 = ((BonusActorExt *)D_807FBB40)->unk178;
    Point3f *p;
    f32 y;
    f32 z;

    if (!(D_807FBB40->unk60 & 0x10)) {
        t0->unk23 = 5;
        t0->unk0 = -2;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(BCAM->unk104, D_807FBB40, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        D_807FBB40->unkE8 = 0x9A;
        switch (gCurrentMap) {
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
    if (D_807FBB40->unk154 == 0) {
        D_807FBB40->unk15F = 1;
    } else {
        D_807FBB40->unk15F = 0;
    }
    if (t0->unk0 > 0) {
        t0->unk22 = 0;
        if (D_807FBB40->unk154 == 0 && (gPlayerPadState.unk30 >= 0x1F || gPlayerPadState.unk31 >= 0x1F)) {
            if (gPlayerPadState.unk2F > 0) {
                if (gPlayerPadState.unk2E < -0x28) {
                    t0->unk22 = 1;
                } else if (gPlayerPadState.unk2E >= 0x29) {
                    t0->unk22 = 3;
                } else {
                    t0->unk22 = 2;
                }
            } else if (gPlayerPadState.unk2E < -0x28) {
                t0->unk22 = 4;
            } else if (gPlayerPadState.unk2E >= 0x29) {
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
                Actor *e = s38->unk0[t0->unk22 - 1];
                if (((Struct_174 *)e->unk174)->unk1C == 0) {
                    ((Struct_174 *)e->unk174)->unk1C = 6;
                }
            }
            break;
        case 2:
            t0->unk25 = 0xFF;
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (D_807FBB40->unk154) {
        case 0:
            if (((Actor *)D_807FBB40->unk11C)->unk154 == 5) {
                D_807FBB40->unk154 = 0xFF;
            }
            if (((Actor *)D_807FBB40->unk11C)->unk154 == 4 && ((Actor *)D_807FBB40->unk11C)->unk155[0] != 0xFF) {
                D_807FBB40->unk154 = 0xFE;
            }
            break;
        case 2:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk155[0] = 0;
            break;
        case 0xFE:
            t0->unk24 = 0xFF;
            D_807FBB40->unk154 = 0;
            break;
        case 0xFF:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk155[0] = 1;
            break;
        }
    } else {
        switch (t0->unk0) {
        case -2:
            if (D_807444EC != 1) {
                t0->unk0++;
                hudSpawnCountdownTimer(0xDC, 0x2A, s38->unk1A);
                func_8070D8C0(D_807FBB40, 0, 2);
            }
            break;
        case -1:
            if (!(D_807FBB40->unk60 & 0x2000000)) {
                t0->unk0 = 1;
                actorSetStateTwo((void *)D_807FBB40->unk11C);
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

void bonusTargetUpdate(void) {
    Struct_174 *sub = D_807FBB40->unk174;
    Struct_71B4 *p = sub->unk0;
    s32 step;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk144 = 0x24;
    }
    func_8072881C(0, sub->unk4, sub, p);
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB85 != 0) {
            if (p->unk22 - ((sub->unk8 != 0) ? 2 : 1) < 0) {
                p->unk22 = 0;
            } else {
                step = (sub->unk8 != 0) ? 2 : 1;
                p->unk22 -= step;
            }
            func_806FDAB8(p->unk25, 3.1415927f);
            actorScriptStart(D_807FBB40, (sub->unk8 != 0) ? 0x212 : 0x210);
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk155[0] = 0;
        } else if (D_807FBB40->unk155[0] != 0) {
            bonusDespawnTarget(sub, p);
        }
        break;
    case 1:
        if (D_807FBB40->unk155[0] != 0) {
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
    Actor *s5;
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
            s5 = D_807FBB44;
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

#ifdef NON_MATCHING
typedef struct {
    s8 unk0;
    u8 unk1;
    u16 unk2;
    s16 unk4;
    s16 unk6;
} BonusVtxEntry;

typedef struct {
    char pad0[0x1C];
    BonusVtxEntry *unk1C;
} BonusVtxModel;

typedef struct {
    char pad0[0x20];
    f32 unk20;
} BonusVtxInfo;

typedef struct {
    char pad0[4];
    u8 unk4;
    u8 unk5;
} BonusVtxSub;

typedef struct BonusVtxActor BonusVtxActor;
struct BonusVtxActor {
    char pad0[4];
    BonusVtxModel *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x82];
    s16 unkE6;
    char padE8[0x5C];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    void *unk174;
    BonusVtxInfo *unk178;
};

typedef struct {
    BonusVtxActor *unk0;
    BonusVtxActor *unk4;
    f32 unk8;
    f32 unkC;
    s8 unk10;
    u8 unk11;
    char pad12[2];
    f32 unk14;
    f32 unk18;
    u8 unk1C;
} BonusVtxLink;
#define BONUS_VTX_ACTOR ((BonusVtxActor *)D_807FBB40)

extern u8 D_807FBD70;
void *heapAlloc(s32);
void heapClearBlock(void *);

void bonusActorUpdateVertexPositions(void) {
    BonusVtxLink *link = BONUS_VTX_ACTOR->unk174;
    s16 *sp50 = link->unk0->unk174;
    BonusVtxInfo *sp4C = link->unk0->unk178;
    BonusVtxSub *sub;
    BonusVtxEntry *chk;
    s32 vb[2];
    f32 sp38;
    BonusVtxEntry *p;
    f32 fx;
    f32 fy;
    f32 sp28;
    s32 i;

    if (!(BONUS_VTX_ACTOR->unk60 & 0x10)) {
        BONUS_VTX_ACTOR->unk144 = 0x24;
        link->unkC = 275.0f;
        link->unk8 = 275.0f;
        link->unk10 = link->unk11;
        BONUS_VTX_ACTOR->unk4->unk1C = heapAlloc(0x38);
        heapClearBlock(BONUS_VTX_ACTOR->unk4->unk1C);
    }
    sub = link->unk4->unk174;
    if (D_807FBD70 == 4 && sub->unk4 == 0 && link->unk10 == -1) {
        link->unk8 = 275.0f;
        link->unk10 = link->unk11;
        sub->unk5 = 0;
    }
    if (*sp50 > 0 && link->unk0->unk154 == 0) {
        if (sub->unk4 == 0) {
            if (link->unk10 >= 0) {
                link->unk10--;
            }
            if (link->unk10 < 0) {
                link->unk8 -= sp4C->unk20;
            }
        } else {
            link->unk8 += 40.0f;
            link->unk0->unk154 = 2;
        }
    }
    link->unkC = link->unkC + (link->unk8 - link->unkC) * 0.3;
    if (sub->unk4 != 0) {
        if (link->unk14 < 1.0f) {
            link->unk14 += 0.1f;
        } else if (link->unk14 > 1.0f) {
            link->unk14 = 1.0f;
        }
    } else if (link->unk1C != 0) {
        link->unk1C--;
        if (link->unk1C == 0) {
            actorScriptStart(D_807FBB40, 0x1F6);
        }
    }
    chk = BONUS_VTX_ACTOR->unk4->unk1C;
    if (chk != 0) {
        vb[1] = 0;
        vb[0] = (s32)chk;
        sp38 = 1.0f - ((link->unkC - 40.0f) / 235.0f);
        fx = func_80612794(link->unk4->unkE6) * (5000.0f * sp38 + 150.0f);
        fy = func_80612790(link->unk4->unkE6) * (5000.0f * sp38 + 150.0f);
        sp28 = link->unk14 * 128.0f + -128.0f;
        i = 4;
        if (fx < 0.0f) {
            fx = 65535.0f + fx;
        }
        if (fy < 0.0f) {
            fy = 65535.0f + fy;
        }
        p = (BonusVtxEntry *)(vb[1] * 8 + vb[0]);
        do {
            p->unk1 = i;
            i++;
            p->unk0 = (s32)sp28;
            p->unk2 = (u32)fx;
            p->unk4 = 0;
            p->unk6 = (u32)fy;
            if (fx > 32767.0f) {
                fx = fx + (65535.0f - fx) * 0.5;
            } else {
                fx = fx * 0.5;
            }
            if (fy > 32767.0f) {
                fy = fy + (65535.0f - fy) * 0.5;
            } else {
                fy = fy * 0.5;
            }
            p++;
        } while (i < 7);
        switch (BONUS_VTX_ACTOR->unk155) {
        case 0:
            link->unk18 = link->unk18 + (sp38 - link->unk18) * 0.1;
            break;
        case 1:
        case 2:
            link->unk18 = link->unk18 + (0.0 - link->unk18) * 0.1;
            break;
        }
        p->unk0 = (s32)(link->unk18 * -128.0f);
        p->unk1 = 0xE;
        p->unk2 = 0x61A8;
        p->unk4 = 0;
        p->unk6 = 0;
        p++;
        i = 0xC;
        do {
            p->unk0 = (s32)(link->unk18 * -128.0f);
            p->unk1 = i;
            i++;
            p += 2;
            p[-2].unk2 = 0xD8F0;
            p[-2].unk4 = 0;
            p[-2].unk6 = 0;
        } while (i < 0xD);
        p->unk0 = 0;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/bonusActorUpdateVertexPositions.s")
#endif

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

extern s16 D_8002D8C0[];
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_8067ACB4(void *);
void actorApplyVelocity(void *);
void actorUpdateFloorContactAndTilt(void *, f32);

void func_80028E3C(void) {
    BonusB_Sub8E3C *t0 = D_807FBB40->unk174;
    BonusB_Par8E3C *p40 = t0->unk0->unk174;
    f32 temp;
    f64 v;
    s16 idx;
    s32 a0;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unkE6 = (randomNonNegative() >> 0xF) % 4096;
        D_807FBB40->unkC4 = -10.0f;
        D_807FBB40->unk6A &= 0xFFFE;
        func_80613C48(D_807FBB40, 0x688, 0.0f, 0.0f);
        scriptSetActorRampTarget(D_807FBB40, 1.0, 0.0f);
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
                sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, idx, 0xFF, a0, 0, 0, 0.0f, 0);
            }
            if (p40->unkC < 40.0f) {
                t0->unk4 = 1;
                sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x1ED, 0xFF, 0x7F, 0, 0, 0.0f, 0);
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x76, 0xFF, 0x7F, 0x1E);
                D_807FBB40->unkEE = D_807FBB40->unkE6;
                D_807FBB40->unkB8 = 10.0f;
                actorScriptStart(t0->unk0, 0x1F7);
            }
        }
    }
    if (t0->unk4 == 0) {
        actorGetNodePos(t0->unk0, 1, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
    } else {
        if ((D_807FBB40->unk6A & 1) && !(D_807FBB40->unk6C & 1)) {
            D_807FBB40->unkC0 = t0->unkC * -0.8f;
            v = -t0->unkC * 1.5;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xFF, (u8)((255.0 < v) ? 255.0 : v), 0x7F, 0xA);
        }
        D_807FBB40->unkC0 = D_807FBB40->unkC0 + D_807FBB40->unkC4;
        t0->unkC = D_807FBB40->unkC0;
        func_8067ACB4(D_807FBB40);
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0);
    }
    D_807FBB40->unkE6 += p40->unkC;
    if (D_807FBB40->unkE6 >= 0x1000) {
        D_807FBB40->unkE6 -= 0x1000;
    }
    temp = 30000.0f / p40->unkC;
    D_807FBB40->unkE4 = func_80612794(D_807FBB40->unkE6) * -temp;
    D_807FBB40->unkE8 = func_80612790(D_807FBB40->unkE6) * temp;
    temp = temp * 0.006666667f;
    temp = (temp < 1.0f) ? 1.0f : ((temp > 2.5f) ? 2.5f : temp);
    scriptSetActorRampTarget(D_807FBB40, temp, 0.0f);
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

Gfx *func_80029B9C(Gfx *gdl, Actor *arg1) {
    Actor *actor;
    BonusC_9B9C_B *p0;
    BonusC_9B9C_A *p1;
    BonusC_9B9C_C *p2;

    p2 = (void *)arg1->unk174;
    p0 = ((BonusActorExt *)arg1)->unk178;
    if (p2) { // FAKE: empty guard steers regalloc
    }
    p1 = ((BonusActorExt *)arg1)->unk178;
    actor = arg1;

    if (actor->unk58 != 0x7E && actor->unk154 == 0 && ((Struct_7548 *)actor->unk174)->unk26 != 0) {
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
            gdl = hudDrawRollingCounter(textDrawAnimated(gdl, p0->unk11, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p0->unk14, p0->unk16, p0->unk12);
        }
        break;
    case 0x7C:
        if (actor->unk154 != 3) {
            gdl = hudDrawRollingCounter(textDrawAnimated(gdl, p1->unk3, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p1->unk8, p1->unkA, p1->unk6);
        }
        break;
    case 0x7E:
        switch (actor->unk154) {
        case 7:
            break;
        case 0:
        case 1:
        case 2:
            gdl = hudDrawRollingCounter(textDrawAnimated(gdl, p2->unk25, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p2->unk28, p2->unk2A, p2->unk26);
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
    Actor *a = arg0;
    s32 i;
    s16 *X = &D_8002D8CA - 1;
    Struct_T0 *base = ((BonusActorExt *)a)->unk178;

    for (i = 1; i != 7; i++) {
        if (actorSpawn(0x147, X[i - 1]) != 0) {
            BonusC_9E54_S *temp_v1 = (BonusC_9E54_S *)D_807FBB44->unk174;
            s16 *temp_a1 = ((BonusActorExt *)D_807FBB44)->unk17C;
            Point3f *pt;
            f32 scale;

            *temp_a1 = X[i - 1];
            temp_v1->unk0 = a;
            temp_v1->unk4 = i - 1;
            pt = *D_807F5FD4 + (base->unk8[temp_v1->unk4] & 0x7F) + 1;
            D_807FBB44->unk7C = pt->x;
            D_807FBB44->unk80 = pt->y;
            D_807FBB44->unk84 = pt->z;
            D_807FBB44->unk154 = 0;
            D_807FBB44->unk60 |= 0x1000;
            D_807FBB44->unkE6 = 0x800;
            if (i != 6) {
                func_806F0C18(D_807FBB44, temp_a1);
                actorScriptStart(D_807FBB44, D_8002D8D4[i - 1]);
            }
            scale = (i != 6) ? 0.25f : 0.04f;
            D_807FBB44->unk4->unk34 = scale;
            D_807FBB44->unk4->unk38 = scale;
            D_807FBB44->unk4->unk3C = scale;
        }
    }
}

void func_8002A010(void) {
    f32 scale;
    Struct_Sp50 *sp50;
    Actor *v;
    Struct_T0 *sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Point3f *p;
    s8 var_a3;
    s8 flags;

    sp50 = (Struct_Sp50 *)D_807FBB40->unk174;
    v = sp50->unk0;
    sp48 = (Struct_T0 *)((BonusActorExt *)v)->unk178;
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (sp50->unk4 != 5) {
            actorClearAllNodeFlags(D_807FBB40);
            actorAppendModelNode(D_807FBB40, 0.0f, 50.0f, 0.0f, 80.0f, -1);
        }
        D_807FBB40->unk144 = 0x24;
    }
    p = *D_807F5FD4 + (sp48->unk8[sp50->unk4] & 0x7F) + 1;
    D_807FBB40->unk7C = p->x;
    D_807FBB40->unk80 = p->y;
    D_807FBB40->unk84 = p->z;
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
        } else if (sp44 < 0.05f && ((Struct_4 *)D_807FBB40->unk4)->unk68 != 0) {
            actorScriptStart(D_807FBB40, 0);
        }
        if (var_a3 != 0) {
            actorScriptStart(D_807FBB40, D_8002D8E0[sp50->unk4]);
            sfxPlayOnFreeSlot(0x2A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
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
        scale = D_807FBB40->unk4->unk34;
        if (D_807FBB40->unk154 == 1) {
            scale = scale - 0.005;
            if (scale < 0.0) {
                scale = 0.0f;
            }
        } else {
            scale = 0.04f;
        }
        D_807FBB40->unk4->unk34 = scale;
        D_807FBB40->unk4->unk38 = scale;
        D_807FBB40->unk4->unk3C = scale;
        if (var_a3 != 0) {
            sfxPlayOnFreeSlot(0x2A1, 0x7FFF, 63.0f, 1.0f, 0, 0);
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

void func_8002A398(void) {
    Struct_7548 *t3c = D_807FBB40->unk174;
    LargeB1_Sub178 *t0 = ((BonusActorExt *)D_807FBB40)->unk178;
    Point3f *p;
    f32 y;
    f32 z;
    s32 n;
    s32 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        t3c->unk23 = 5;
        t3c->unk0 = -2;
        D_8002D904 = 0;
        switch (gCurrentMap) {
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
        t0->unk3 = gfxResourceCreate(1, textTableGetString(0x1A, 4, 1), 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(t0->unk3, 0.0f);
        t0->unk0 = 0x1E;
        playerStateQueueCallback(0x48, 0, 0);
        camSetTarget(BB_CAMCTX->unk104, D_807FBB40, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        D_807FBB40->unkE8 = 0x9A;
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
                p = *D_807F5FD4 + (n + n + n) + 1;
                D_807FBB44->unk7C = p->x + 50.0;
                D_807FBB44->unk80 = p->y + 12.0;
                D_807FBB44->unk84 = p->z - 5.0;
                D_807FBB44->unkE6 = -0x400;
                D_807FBB44->unk4->unk34 = 0.08f;
                if (u) {} // FAKE: empty guard steers regalloc
                D_807FBB44->unk4->unk38 = 0.08f;
                D_807FBB44->unk4->unk3C = 0.08f;
            }
            n = D_8002D904;
            t0->unk0 = 0x5A;
            ((s8 *)&D_8002D900)[4] = (u16)(1 - n);
        }
        t3c->unk22 = 0;
        if (D_807FBB40->unk154 == 0 && (gPlayerPadState.unk30 >= 0x1F || gPlayerPadState.unk31 >= 0x1F)) {
            if (gPlayerPadState.unk2F > 0) {
                if (gPlayerPadState.unk2E < -0x28) {
                    t3c->unk22 = 1;
                } else if (gPlayerPadState.unk2E >= 0x29) {
                    t3c->unk22 = 3;
                } else {
                    t3c->unk22 = 2;
                }
            } else if (gPlayerPadState.unk2E < -0x28) {
                t3c->unk22 = 4;
            } else if (gPlayerPadState.unk2E >= 0x29) {
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
            sfxPlayOnFreeSlot(0x3BC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        }
        switch (D_807FBB40->unk154) {
        case 0:
            if (t0->unk8 == 0) {
                D_807FBB40->unk154 = 2;
            }
            if (((Actor *)D_807FBB40->unk11C)->unk154 == 5) {
                D_807FBB40->unk154 = 1;
            }
            break;
        case 1:
            bonusEndLose(0, 1);
            camStartPath(0, 1, 0x11);
            D_807FBB40->unk154 = 3;
            break;
        case 2:
            bonusEndWin(0, 0);
            camStartPath(0, 1, 0x11);
            D_807FBB40->unk154 = 3;
            break;
        }
    } else {
        switch (t3c->unk0) {
        case -2:
            if (D_807444EC != 1) {
                t3c->unk0++;
                hudSpawnCountdownTimer(0xDC, 0x2A, (u8)t0->unk4);
                func_8070D8C0(D_807FBB40, 0, 0xB);
            }
            break;
        case -1:
            if (!(D_807FBB40->unk60 & 0x2000000)) {
                t3c->unk0 = 1;
                actorSetStateTwo((void *)D_807FBB40->unk11C);
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
    temp_v0 = (Struct_4 *)D_807FBB40->unk4;
    sp50 = temp_v0->unk0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x239);
        D_807FBB40->unk144 = 0x24;
        temp_v0 = (Struct_4 *)D_807FBB40->unk4;
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
        sp64->unk6 = ((randomLcgNext() & 7) + 6) * D_8002D900;
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
    Actor *unk0;
    s8 unk4;
} BonusC_AD10_S;

void func_8002AD10(void) {
    s32 pad;
    BonusC_AD10_S *sp28;
    Actor *v;
    BonusC_AD10_B *sp20;
    Point3f *p;

    sp28 = (BonusC_AD10_S *)D_807FBB40->unk174;
    v = sp28->unk0;
    sp20 = ((BonusActorExt *)v)->unk178;
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x2B5, sp20);
    }
    if (sp28->unk4 == 0 || sp28->unk4 >= 5) {
        D_807FBB40->unk7C = D_807FBB40->unk7C - 1.5;
    }
    p = *D_807F5FD4 + 3;
    if (D_807FBB40->unk7C < p->x - 50.0) {
        if (sp20->unkA > 0) {
            sp20->unkA -= 1;
        }
        actorDespawn(D_807FBB40);
    }
    if (sp28->unk4 != 0) {
        sp28->unk4 -= 1;
        if (sp28->unk4 < 4) {
            if (sp28->unk4 == 3) {
                sfxPlayOnFreeSlot(0x2D2, 0x7FFF, 63.0f, 7.12f, 0, 1);
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

extern Actor *D_807FBB4C;
extern LargeB4Player *gPlayerSlots;
extern LargeB4Ctrl *D_807ECDEC;
void lightSetColor(f32, f32, f32, s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
#ifdef NON_MATCHING
typedef struct {
    char pad0[4];
    f32 unk4;
    char pad8[0x1C];
    f32 unk24;
} LargeB5Anim;

typedef struct {
    LargeB5Anim *unk0;
    char pad4[0x30];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} LargeB5Model;

typedef struct LargeB5Actor {
    char pad0[4];
    LargeB5Model *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5E];
    s16 unkE6;
    s16 unkE8;
    char padEA[0x32];
    struct LargeB5Actor *unk11C;
    char pad120[0x34];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    struct LargeB5State *unk174;
} LargeB5Actor;

typedef struct LargeB5State {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    char pad1A[2];
    f32 unk1C;
    char pad20[2];
    s16 unk22;
    char pad24;
    u8 unk25;
    u8 unk26;
    char pad27;
    s16 unk28;
    s16 unk2A;
    s8 unk2C;
    s8 unk2D[1];
} LargeB5State;

typedef struct {
    void *unk0;
    f32 unk4;
    f32 unk8;
    char padC[2];
    s16 unkE;
} LargeB5Proj;

#define LB5 ((LargeB5Actor *)D_807FBB40)

void func_8002AED8(void) {
    s32 pad0[4];
    f32 fs0;
    f32 fs1;
    f32 sp6C;
    LargeB5Anim *sp68 = LB5->unk4->unk0;
    LargeB5State *t = LB5->unk174;
    s32 i;
    u8 c;
    s32 padz;
    LargeB5Proj *p0;
    s16 sp52;

    if (!(LB5->unk60 & 0x10)) {
        D_807FBB4C->unk154 = 0x77;
        D_807FBB4C->unk155[0] = 0;
        t->unk0 = LB5->unk7C + 10.0;
        t->unk4 = LB5->unk84 + 8.0;
        LB5->unk80 = LB5->unk80 + 50.0;
        switch (gCurrentMap) {
        case 0x66:
            t->unk2A = 4;
            break;
        case 0x94:
            t->unk2A = 6;
            break;
        case 0x95:
            t->unk2A = 8;
            break;
        case 0x96:
            t->unk2A = 0xA;
            break;
        }
        t->unk26 = 0;
        t->unk22 = 0x3C;
        t->unk28 = t->unk2A;
        fs0 = 1 * 0.0f;
        c = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, fs0, fs0, fs0);
        t->unk25 = c;
        func_806FDAB8(c, fs0);
        lightSetColor(1.0f, 1.0f, 1.0f, -1);
        LB5->unkE8 = 0;
        LB5->unkE6 = 0x800;
        func_80613C48(D_807FBB40, 0x5FB, 0.0f, 0.0f);
        LB5->unk4->unk34 = 0.2f;
        LB5->unk4->unk38 = 0.2f;
        LB5->unk4->unk3C = 0.2f;
        camStartPath(0, 0, 1);
        LB5->unk154 = 3;
        t->unk1C = 0.0f;
        t->unk10 = 0.0f;
        t->unk14 = 0.0f;
        t->unk8 = 0.0f;
        t->unkC = 0.0f;
        actorSpawn(0x14C, 0x55);
        p0 = (LargeB5Proj *)D_807FBB44->unk174;
        p0->unk0 = D_807FBB40;
        t->unk2C = 0x3C;
        i = 0;
        do {
            t->unk2D[i] = 1;
            i++;
        } while (i != 1);
    }
    for (i = 0; i < 1; i++) {
        if (t->unk2D[i] > 0) {
            t->unk2D[i] -= 1;
            if (t->unk2D[i] == 0 && actorSpawn(0x14A, 0x53) != 0) {
                LargeB5Proj *s0 = (LargeB5Proj *)D_807FBB44->unk174;

                s0->unk0 = D_807FBB40;
                s0->unk4 = D_807FBB44->unk7C;
                s0->unk8 = D_807FBB44->unk84;
                s0->unkE = 2;
                sp52 = mathAngleBetweenPoints2D(t->unk0, t->unk4, LB5->unk7C, LB5->unk84) + 0x800;
                s0->unk4 = func_80612794(sp52) * 70.0 + t->unk0;
                s0->unk8 = func_80612790(sp52) * 70.0 + t->unk4;
                if (t->unk2C == 0) {
                    D_807FBB44->unk7C = s0->unk4;
                    D_807FBB44->unk80 = LB5->unk80 - 30.0;
                    D_807FBB44->unk84 = s0->unk8;
                } else {
                    D_807FBB44->unk7C = t->unk0 - 30.0;
                    D_807FBB44->unk84 = t->unk0;
                    D_807FBB44->unk80 = LB5->unk80 - 30.0;
                }
            }
        }
    }
    if (t->unk2C != 0) {
        t->unk2C -= 1;
    }
    t->unk18 += 0x19;
    if (LB5->unk154 < 2) {
        f32 fv0;
        f32 fv1;

        fs1 = func_80612794(gPlayerSlots[gCurrentPlayerIndex].unk2C8);
        fv0 = func_80612790(gPlayerSlots[gCurrentPlayerIndex].unk2C8);
        fs0 = D_807ECDEC->unk2 * 0.04f;
        fv1 = D_807ECDEC->unk3 * 0.04f;

        sp6C = t->unk10;
        sp6C = (fs0 * fv0 - fv1 * fs1) - sp6C;
        t->unk10 += sp6C * 0.125f;
        t->unk14 += ((fs0 * fs1 + fv1 * fv0) - t->unk14) * 0.25f;
        t->unk8 += t->unk10;
        t->unkC -= t->unk14;
    }
    switch (LB5->unk154) {
    case 0: {
        f32 prev = t->unk1C;

        t->unk1C += (-sp6C * 4.0f - t->unk1C) * 0.125f;
        if (t->unk1C < 0.0f) {
            if (t->unk1C < -8.0f) {
                t->unk1C = -8.0f;
            }
            if (prev >= 0.0f) {
                func_80613C48(D_807FBB40, 0x5FC, 0.0f, 0.0f);
            }
            if (sp68 != NULL) {
                controllerApplyMotionWindow(D_807FBB40, sp68, -t->unk1C);
            }
        } else {
            if (t->unk1C > 8.0f) {
                t->unk1C = 8.0f;
            }
            if (prev < 0.0f) {
                func_80613C48(D_807FBB40, 0x5FB, 0.0f, 0.0f);
            }
            if (sp68 != NULL) {
                controllerApplyMotionWindow(D_807FBB40, sp68, t->unk1C);
            }
        }
        if (t->unk28 == 0) {
            LB5->unk154 = 5;
        }
        if (LB5->unk11C->unk154 == 5) {
            LB5->unk154 = 6;
        }
        if (LB5->unk154 == 0 && (*gPlayerSlots[gCurrentPlayerIndex].unk298 & 0xE000)) {
            sfxPlayOnFreeSlot(0x25, 0x7FFF, 63.0f, 0.51f, 0, 0);
            func_80613C48(D_807FBB40, 0x5FD, 0.0f, 1.0f);
            LB5->unk154 = 1;
        }
        break;
    }
    case 1:
    case 2:
        if (sp68->unk4 > 10.0f && sp68->unk4 < 14.0f) {
            LB5->unk154 = 2;
        } else {
            LB5->unk154 = 1;
        }
        if (sp68->unk24 == 0.0f) {
            func_80613C48(D_807FBB40, 0x5FC, 0.0f, 1.0f);
            LB5->unk154 = 0;
            t->unk1C = 0.0f;
        }
        break;
    case 3:
        if (D_807444EC != 1) {
            LB5->unk154 = 4;
            hudSpawnCountdownTimer(0xDC, 0x2A, ((u8 *)&t->unk22)[1]);
            func_8070D8C0(D_807FBB40, 0, 0xA);
        }
        break;
    case 4:
        if (!(LB5->unk60 & 0x2000000)) {
            LB5->unk154 = 0;
            actorSetStateTwo(LB5->unk11C);
            sfxAllocateChannel(8, 1.0f);
        }
        break;
    case 5:
    case 6:
        if (LB5->unk154 == 6) {
            bonusEndLose(0, 1);
        } else {
            bonusEndWin(0, 0);
        }
        camStartPath(0, 1, 0x11);
        LB5->unk154 = 7;
        break;
    }
    {
        f32 d;

        fs0 = t->unk8 * 0.85;
        fs1 = t->unkC - 40.0;
        d = sqrtf(fs0 * fs0 + fs1 * fs1);

        if (d > 80.0f) {
            f32 k = 80.0f / d;

            t->unk8 = (fs0 * k) / 0.85;
            t->unkC = (fs1 * k) + 40.0;
        }
    }
    LB5->unk7C = func_80612794(t->unk18) * 5.0 + (t->unk0 + t->unk8 * 0.8);
    LB5->unk84 = 2.0 * func_80612790((s16)(t->unk18 * 2)) + (t->unk4 + t->unkC * 0.9);
    D_807FBB4C->unk7C = t->unk0 + t->unk8 * 0.5f;
    D_807FBB4C->unk80 = LB5->unk80;
    D_807FBB4C->unk84 = t->unk4 + t->unkC * 0.5f;
    renderCallbacksRegister(func_80029B9C, D_807FBB40, 3);
    actorUpdateModelMatrix(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/2690/func_8002AED8.s")
#endif

typedef struct {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} BonusDModel;

typedef struct {
    Actor *unk0;
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
    BonusDB920Link *temp_s1 = D_807FBB40->unk174;
    Actor *sp48 = temp_s1->unk0;
    BonusDB920Tgt *temp_s2 = sp48->unk174;
    f32 sp40;
    f32 sp3C;
    f32 dx;

    if (!(D_807FBB40->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x32F);
        D_807FBB40->unk4->unk34 = 0.06f;
        D_807FBB40->unk4->unk38 = 0.06f;
        D_807FBB40->unk4->unk3C = 0.06f;
        sfxPlayActorSound(D_807FBB40, 0x10E, 0x3C, 1, 0, 0xFF, 1.0f, 0);
    }
    if (D_807FBB40->unk154 == 0) {
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
            D_807FBB40->unkE6 -= mathAngleSignedDistance(mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, temp_s1->unk4, temp_s1->unk8) + 0x800, D_807FBB40->unkE6) >> 3;
            D_807FBB40->unk7C += func_80612794(D_807FBB40->unkE6) * sp40;
            D_807FBB40->unk84 += func_80612790(D_807FBB40->unkE6) * sp40;
            temp_s1->unkE--;
            if (temp_s1->unkE <= 0) {
                s16 angle;

                if (temp_s1->unkC > 0) {
                    temp_s1->unkE = (randomLcgNext() & 7) + 0xA;
                } else {
                    temp_s1->unkE = (randomLcgNext() & 0x3F) + 0xF;
                }
                angle = mathAngleBetweenPoints2D(temp_s2->unk0, temp_s2->unk4, temp_s1->unk4, temp_s1->unk8);
                angle += ((randomLcgNext() & 7) << 8) + 0x400;
                sp3C = randomFloat() * 70.0;
                temp_s1->unk4 = func_80612794(angle) * sp3C + temp_s2->unk0;
                temp_s1->unk8 = func_80612790(angle) * sp3C + temp_s2->unk4;
            }
        } else {
            if (temp_s2->unk2C == 0x28) {
                sfxPlayFromActorDirect(D_807FBB40, 0x801, 0xFF, 3.0f, 2, 0);
            }
            D_807FBB40->unk80 = func_80612794(temp_s2->unk18) * 5.0 + (sp48->unk80 - 30.0);
        }
    } else {
        D_807FBB40->unk128 -= 4;
        if (D_807FBB40->unk128 < 5) {
            D_807FBB40->unk128 = 0;
            actorDespawn(D_807FBB40);
        }
    }
    if (sp48->unk154 == 2) {
        f32 dz;
        dx = func_80612794(sp48->unkE6) * 65.0f + sp48->unk7C;
        dz = func_80612790(sp48->unkE6) * 65.0f + sp48->unk84;
        dx -= D_807FBB40->unk7C;
        dz -= D_807FBB40->unk84;
        if (D_807FBB40->unk154 == 0) {
            if (dx < 12.0 && dx > -12.0 && dz < 12.0 && dz > -12.0) {
                s32 var_v0;

                sfxStopSlotSound(D_807FBB40, 0);
                actorScriptStart(D_807FBB40, 0x331);
                if (temp_s2->unk2A != 0) {
                    temp_s2->unk2A--;
                }
                for (var_v0 = 0; var_v0 < 1; var_v0++) {
                    if (temp_s2->unk2D[var_v0] == 0) {
                        temp_s2->unk2D[var_v0] = 0x1E;
                        var_v0 = 1;
                    }
                }
                D_807FBB40->unk154 = 1;
                sfxPlayFromActorDirect(D_807FBB40, 0x16, 0xFF, 1.0f, 0x14, 0);
                D_807FBB40->unk128 = 0xFF;
                D_807FBB40->unk60 &= ~0x8000;
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
    f32 unk4;
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

typedef struct {
    Actor *unk0;
} BonusDBE44Link;

void func_8002BE44(void) {
    BonusDBE44Link *link = D_807FBB40->unk174;
    Actor *temp_v1 = link->unk0;
    BonusDBE44Anim *sp24 = ((BonusDBE44Model *)D_807FBB40->unk4)->unk0;
    BonusDBE44Anim *var_t0 = ((BonusDBE44Model *)temp_v1->unk4)->unk0;
    s16 var_a1;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unkE8 = 0;
        D_807FBB40->unkE6 = 0x800;
        func_80613C48(D_807FBB40, 0x5FB, 0, 0);
        D_807FBB40->unk4->unk34 = 0.2f;
        D_807FBB40->unk4->unk38 = 0.2f;
        D_807FBB40->unk4->unk3C = 0.2f;
    }
    D_807FBB40->unk7C = temp_v1->unk7C;
    D_807FBB40->unk80 = temp_v1->unk80 - 35.0;
    D_807FBB40->unk84 = temp_v1->unk84;
    if (sp24 != NULL) {
        if (var_t0 != NULL) {
            var_a1 = var_t0->unk10;
            if (var_a1 == 0x5FD) {
                var_a1 = 0x5FE;
            }
            if (var_a1 != sp24->unk10) {
                func_80613C48(D_807FBB40, var_a1, 0, 0);
            }
            controllerApplyMotionWindow(D_807FBB40, sp24, var_t0->unk4);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

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

typedef struct {
    Actor *unk0;
    s16 unk4;
    char pad6[2];
    f32 unk8;
    s16 unkC;
} LargeB4Spawn;

Gfx *func_8002CC08(Gfx *, Actor *);

void func_8002BF98(void) {
    f32 sp84;
    f32 fv0;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 fv1;
    f32 ft5;
    LargeB4Sub *temp_s5 = D_807FBB40->unk174;
    LargeB4Spawn *temp_s0;
    s32 i;
    s32 pad;
    s16 sp5A;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB4C->unk154 = 0x77;
        D_807FBB4C->unk155[0] = 0;
        D_807FBB4C->unk144 = 1;
        temp_s5->unk0 = 1.0f;
        temp_s5->unk4 = D_807FBB40->unk7C;
        temp_s5->unk8 = D_807FBB40->unk84;
        switch (gCurrentMap) {
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
        temp_s5->unk23 = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(temp_s5->unk23, 0.0f);
        D_807FBB40->unk4->unk34 = 0.33f;
        D_807FBB40->unk4->unk38 = 0.33f;
        D_807FBB40->unk4->unk3C = 0.33f;
        camSetTarget(BCAM->unk104, D_807FBB40, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        D_807FBB40->unk154 = 3;
        temp_s5->unk14 = 0.0;
        temp_s5->unk18 = 0.0;
        temp_s5->unkC = 0.0;
        temp_s5->unk10 = 0.0;
        temp_s5->unk0 = 1.0;
        i = 0;
        do {
            temp_s5->unk2A[i] = 1;
            i++;
        } while (i != 1);
    }
    for (i = 0; i < 1; i++) {
        if (temp_s5->unk2A[i] > 0) {
            temp_s5->unk2A[i] -= 1;
            if (temp_s5->unk2A[i] == 0 && actorSpawn(0x14B, 0x21) != 0) {
                temp_s0 = (LargeB4Spawn *)D_807FBB44->unk174;
                temp_s0->unk0 = D_807FBB40;
                temp_s0->unkC = 2;
                temp_s0->unkC = (randomLcgNext() & 0x3F) + 0xF;
                temp_s0->unk4 = randomLcgNext() & 0xF;
                temp_s0->unk8 = randomFloat() * 40.0 + 15.0;
                sp5A = temp_s0->unk4 * 0xC8 - 0x578;
                D_807FBB44->unk7C = func_80612794(sp5A) * temp_s0->unk8 + temp_s5->unk4;
                D_807FBB44->unk80 = D_807FBB40->unk80;
                D_807FBB44->unk84 = func_80612790(sp5A) * temp_s0->unk8 + temp_s5->unk8;
            }
        }
    }
    temp_s5->unk1C += 0x19;
    if (D_807FBB40->unk154 == 0 || D_807FBB40->unk154 == 1) {
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
    switch (D_807FBB40->unk154) {
        case 0: {
            sp84 = func_80612794(gPlayerSlots[gCurrentPlayerIndex].unk2C8);
            fv0 = func_80612790(gPlayerSlots[gCurrentPlayerIndex].unk2C8);
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
                D_807FBB40->unk154 = 5;
            }
            if (((Actor *)D_807FBB40->unk11C)->unk154 == 5) {
                D_807FBB40->unk154 = 6;
            }
            if (temp_s5->unk1E > 0) {
                temp_s5->unk1E = temp_s5->unk1E - 1;
            }
            if (temp_s5->unk1E <= 0 && (*gPlayerSlots[gCurrentPlayerIndex].unk298 & 0xE000)) {
                sfxPlayOnFreeSlot(0x59, 0x7FFF, 63.0f, 1.0, 0x1E, 0);
                sp7C = func_80612794(gPlayerSlots->unk2C8) * 30.0f + gPlayerSlots->unk210;
                sp78 = gPlayerSlots->unk214 - 25.0f;
                sp74 = func_80612790(gPlayerSlots->unk2C8) * 30.0f + gPlayerSlots->unk218;
                projectileSetTargetCoords(sp7C, sp78, sp74);
                projectileAimAndSpawn(0x23, 1, 0.8f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 625.0f, D_807FBB40);
                temp_s5->unk1E = 0x1E;
            }
            break;
        }
        case 3:
            if (D_807444EC != 1) {
                D_807FBB40->unk154 = 4;
                hudSpawnCountdownTimer(0xDC, 0x2A, (u8)temp_s5->unk20);
                func_8070D8C0(D_807FBB40, 0, 0xC);
            }
            break;
        case 4:
            if (!(D_807FBB40->unk60 & 0x02000000)) {
                D_807FBB40->unk154 = 0;
                actorSetStateTwo((void *)D_807FBB40->unk11C);
                sfxAllocateChannel(8, 1.0);
            }
            break;
        case 5:
        case 6:
            if (D_807FBB40->unk154 == 6) {
                bonusEndLose(0, 1);
            } else {
                bonusEndWin(0, 0);
            }
            camStartPath(0, 1, 0x11);
            D_807FBB40->unk154 = 7;
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
    D_807FBB40->unk7C = func_80612794(temp_s5->unk1C) * 5.0 + (temp_s5->unk4 + temp_s5->unkC);
    D_807FBB40->unk84 = func_80612790(temp_s5->unk1C * 2) * 2.0 + (temp_s5->unk8 + temp_s5->unk10);
    D_807FBB4C->unk7C = temp_s5->unk4 + temp_s5->unkC * 0.5f;
    D_807FBB4C->unk80 = D_807FBB40->unk80;
    D_807FBB4C->unk84 = temp_s5->unk8 + temp_s5->unk10 * 0.5f;
    renderCallbacksRegister(func_8002CC08, D_807FBB40, 3);
    lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80 + 25.0, D_807FBB40->unk84, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 25.0f, 1, 0xFF, 0xFF, 0xFF);
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
    Actor *unk0;
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
    Actor *temp_v0;
    BonusDC8ECLink *temp_s2 = D_807FBB40->unk174;
    BonusDC8ECTgt *temp_s3;

    temp_v0 = temp_s2->unk0;
    temp_s3 = temp_v0->unk174;

    if (!(D_807FBB40->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x232);
        D_807FBB40->unk144 = 0x24;
        D_807FBB40->unk4->unk34 = 0.25f;
        D_807FBB40->unk4->unk38 = 0.25f;
        D_807FBB40->unk4->unk3C = 0.25f;
    }
    if (D_807FBB40->unk154 == 0) {
        sp40 = D_8002D90C;
        temp_s0_2 = temp_s2->unk4 * 0xC8 - 0x578;
        sp30 = func_80612794(temp_s0_2) * temp_s2->unk8 + temp_s3->unk4;
        sp34 = func_80612790(temp_s0_2) * temp_s2->unk8 + temp_s3->unk8;
        D_807FBB40->unkE6 -= mathAngleSignedDistance(mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, sp30, sp34) + 0x800, D_807FBB40->unkE6) >> 5;
        D_807FBB40->unk7C += func_80612794(D_807FBB40->unkE6) * sp40;
        D_807FBB40->unk84 += func_80612790(D_807FBB40->unkE6) * sp40;
        temp_s2->unkC--;
        if (temp_s2->unkC <= 0) {
            temp_s2->unkC = (randomLcgNext() & 0x3F) + 0xF;
            temp_s2->unk4 += (randomLcgNext() & 0xF) + 3;
            temp_s2->unk8 = 40.0 * randomFloat() + 10.0;
        }
        if (D_807FBB85 == 1) {
            D_807FBB40->unk128 = 0xFF;
            D_807FBB40->unk60 &= ~0x8000;
            actorScriptStart(D_807FBB40, 0x332);
            D_807FBB40->unk154 = 1;
            sfxPlayOnFreeSlot(0x16, 0x7FFF, 63.0f, 1.0f, 0, 0);
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
        D_807FBB40->unk128 -= 4;
        if (D_807FBB40->unk128 < 5) {
            D_807FBB40->unk128 = 0;
            actorDespawn(D_807FBB40);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

Gfx *func_8002CC08(Gfx *arg0, Actor *arg1) {
    Struct_CC08_174 *sp84;
    f32 sp80;
    f32 sp7C;
    s32 temp_v0;
    s16 sp76;
    s16 sp74;

    sp84 = (Struct_CC08_174 *)arg1->unk174;
    camProjectToScreen(arg1->unk7C, arg1->unk80, arg1->unk84, &sp80, &sp7C, 0, 1.0f, gCurrentPlayerIndex);
    sp76 = (f32)(sp80 * 4.0);
    sp74 = (f32)(sp7C * 4.0);
    gDPPipeSync(arg0++);
    gDPSetCombineMode(arg0++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(arg0++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(arg0++, D_1000118);
    gSPMatrix(arg0++, D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    temp_v0 = arg1->unk154;
    if (temp_v0 == 0 || temp_v0 == 1) {
        arg0 = renderRotatedSprite(arg0, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, sp76 - 0x34, sp74 - 0x34, 3.2f, 3.2f, 0xE1, 0.0f);
        arg0 = renderRotatedSprite(arg0, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, sp76 + 0x34, sp74 - 0x34, 3.2f, 3.2f, 0x13B, 0.0f);
        arg0 = renderRotatedSprite(arg0, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, sp76 + 0x34, sp74 + 0x34, 3.2f, 3.2f, 0x2D, 0.0f);
        arg0 = renderRotatedSprite(arg0, (gFrameCounter >> 1) % 12 + 0x83, 0, 2, 0x20, 0x10, sp76 - 0x34, sp74 + 0x34, 3.2f, 3.2f, 0x87, 0.0f);
    }
    gSPMatrix(arg0++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (arg1->unk154) {
    case 7:
        do {
        } while (0); // FAKE: empty do/while(0) steers branch codegen
        break;
    case 0:
    case 1:
        arg0 = hudDrawRollingCounter(textDrawAnimated(arg0, sp84->unk23, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, &sp84->unk26, sp84->unk28, &sp84->unk24);
        break;
    }
    return arg0;
}
