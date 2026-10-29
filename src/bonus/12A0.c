#include "common.h"

extern Gfx D_1000118;
extern Mtx D_2000080;
extern Mtx D_2000180;
Gfx *textDrawAnimated(Gfx *, u8, s32, f32, f32, f32, f32);
Gfx *func_8068DC54(Gfx *, s32, s32, void *, s16, void *);

struct LB3Actor;
typedef struct LB3Obj {
    struct LB3Actor *act[4];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 pad1B;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 pad1F;
    s32 unk20;
} LB3Obj;

typedef struct LB3Actor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x6E - 0x64];
    s16 unk6E;
    u8 pad70[0x7C - 0x70];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE8 - 0x88];
    s16 unkE8;
    u8 padEA[0xF0 - 0xEA];
    s16 unkF0;
    u8 padF2[0x11C - 0xF2];
    struct LB3Actor *unk11C;
    u8 pad120[0x154 - 0x120];
    u8 unk154;
    u8 unk155;
    u8 pad156[9];
    u8 unk15F;
    u8 pad160[0x168 - 0x160];
    s16 unk168;
    u8 pad16A[0x174 - 0x16A];
    LB3Obj *unk174;
} LB3Actor;

typedef struct LB3Player {
    u8 pad0[0x104];
    void *unk104;
} LB3Player;

typedef struct LB3PlayerActor {
    u8 pad0[0x155];
    u8 unk155;
    u8 pad156[0x174 - 0x156];
    LB3Player *unk174;
} LB3PlayerActor;

struct BonusEActor;
typedef struct BonusEObj {
    struct LB3Actor *unk0;
    s16 unk4;
} BonusEObj;

typedef struct BonusEActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE8 - 0x88];
    s16 unkE8;
    u8 padEA[6];
    s16 unkF0;
    u8 padF2[0x154 - 0xF2];
    u8 unk154;
    u8 unk155;
    u8 pad156[9];
    s8 unk15F;
    f64 unk160;
    s16 unk168;
    u8 pad16A[0xA];
    BonusEObj *unk174;
} BonusEActor;

s32 actorSpawn(s32, s32);
extern void *D_807FBB40;
extern void *D_807FBB44;
extern void *D_807FBB4C;

#define LA ((LB3Actor *)D_807FBB40)
#define BA ((BonusEActor *)D_807FBB40)
#define RA ((BonusEActor *)D_807FBB44)
#define LPA ((LB3PlayerActor *)D_807FBB4C)

Gfx *bonusRenderReelHud(Gfx *gdl, void *arg1) {
    LB3Obj *temp_t0 = ((LB3Actor *)arg1)->unk174;

    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(gdl++, &D_1000118);
    gSPMatrix(gdl++, &D_2000080, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return func_8068DC54(
        textDrawAnimated(gdl, temp_t0->unk19, 8, 30.0f, 36.0f, 0.0f, 1.5f),
        0x26, 0x32, &temp_t0->unk14, temp_t0->unk16, &temp_t0->unk18);
}

void *bonusSpawnReel(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    if (actorSpawn(0xDB, arg0) != 0) {
        BonusEObj *obj = RA->unk174;
        RA->unk7C = (f32)arg1;
        RA->unk80 = (f32)arg2;
        RA->unk84 = (f32)arg3;
        obj->unk0 = D_807FBB40;
    }
    return D_807FBB44;
}

extern u8 *D_8002D8B0[];

u8 bonusGetReelSymbol(LB3Obj *obj, u8 arg1) {
    s32 idx = arg1;
    return D_8002D8B0[idx][obj->act[idx]->unk15F];
}

void func_807149B8(s32);
s32 func_8071498C(void (*)(void));
void func_80714950(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
s32 randomNonNegative();
extern void *D_8074E880[];
void D_80717404(void);

void bonusSpawnEffectBurst(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 i;

    for (i = 0; i < arg3; i++) {
        func_807149B8(1);
        func_8071498C(D_80717404);
        func_80714950(1);
        func_80714CC0(D_8074E880[(randomNonNegative() >> 15) % 1000 % 3], 0.3f, (f32)arg0, (f32)arg1, (f32)arg2);
    }
}

void camSetTarget(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);

void bonusReelNextRound(LB3Obj *arg0) {
    LB3Player *temp_v0 = LPA->unk174;
    camSetTarget(temp_v0->unk104, D_807FBB4C, 4, 0, 0xAA, 0, 0, 0, 0, 0, 0.09f);
    LA->unk154 = 3;
    LA->unk155 = 1;
    LA->unk168 = 0;
}

void bonusInitActors(LB3Obj *obj, u8 arg1) {
    u8 i = 0;
    do {
        obj->act[i]->unk154++;
        obj->act[i]->unkF0 = arg1;
    } while (++i < 4);
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DC90.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DC98.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DCA0.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DCA8.s")

extern s32 D_8076A0A8;
extern void *D_807FBB48;
extern u8 D_807444EC;
extern s32 D_807457E4[];
extern u8 D_80720CF0;
s32 gfxResourceCreate(s32, char *, s32, f32, f32, f32);
void func_806FDAB8(u8, f32);
s32 playerStateQueueCallback(s32, s32, s32);
void camSetTargetScaled(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
unsigned int camStartPath(s32, s32, s32);
void func_8070D8C0(void *, s32, u8);
void func_8071495C(void);
void func_80714998(s32);
void func_807149FC(s32);
void func_806A2A10(s32, s32, s32);
void actorSetStateTwo(void *);
void n_alSndpStop(s32);
void effectFreeAndUnlink(s32);
void renderCallbacksRegister(void *, void *, s32);
f32 func_80612794(s16);
s16 func_80609140(s32, s32, f32, f32, s32, s32);
void bonusEndWin(u8, u8);
void bonusEndLose(u8, u8);
void textSpawnMarkerChecked(s32, s32, s32, s32, s32, s32, s32, s32);
void sfxAllocateChannel(s32, f32);
s32 func_8070E750(s32, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void actorUpdateModelMatrix(void *, s32);

void bonusReelGameUpdate(void) {
    LB3Player *sp4C;
    LB3Obj *obj;
    u8 i;
    s32 two;

    two = 2;
    sp4C = LPA->unk174;
    obj = LA->unk174;
    if (!(LA->unk60 & 0x10)) {
        LA->unk7C = 52.0f;
        LA->unk84 = 18.0f;
        obj->unk19 = gfxResourceCreate(1, "HIT", 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(obj->unk19, 0.0f);
        obj->unk16 = 3;
        obj->unk14 = 3;
        obj->act[0] = bonusSpawnReel(0x90, -0x15, 1, 0x12);
        obj->act[1] = bonusSpawnReel(0x91, -7, 1, 0x12);
        obj->act[2] = bonusSpawnReel(0x92, 7, 1, 0x12);
        obj->act[3] = bonusSpawnReel(0x93, 0x15, 1, 0x12);
        playerStateQueueCallback(0x49, 0, 0);
        camSetTargetScaled(sp4C->unk104, D_807FBB4C, 6, 0, 0xAA, 0, 0, 0, 0, 0, 1.0f);
        camStartPath(0, 1, 1);
        switch (D_8076A0A8) {
        case 0x20:
            obj->unk1C = 0x2D;
            obj->unk1E = 0x20;
            obj->unk1D = 0x20;
            break;
        case 0x79:
            obj->unk1C = 0x2D;
            obj->unk1E = 0x34;
            obj->unk1D = 0x20;
            break;
        case 0x7A:
            obj->unk1C = 0x28;
            obj->unk1E = 0x34;
            obj->unk1D = 0x2A;
            break;
        case 0x7B:
            obj->unk1C = 0x23;
            obj->unk1E = 0x40;
            obj->unk1D = 0x37;
            break;
        }
    }
    if (obj->unk1A != 0 && LA->unk11C->unk154 == 5) {
        LA->unk154 = 1;
        LA->unk155 = 0;
    }
    switch (LA->unk154) {
    case 0:
        switch (LA->unk155) {
        case 0:
            if (D_807444EC != 1) {
                func_8070D8C0(D_807FBB40, 0, 3);
                LA->unk155 += 1;
            }
            break;
        case 1:
            if (!(LA->unk60 & 0x02000000)) {
                LA->unk154 = 3;
                LA->unk155 = 0;
                func_8071495C();
                func_80714998(2);
                func_807149FC(-1);
                obj->unk20 = func_80714CC0(&D_80720CF0, 1.0f, 40.0f, 200.0f, 5.0f);
            }
            break;
        }
        break;
    case 3:
        switch (LA->unk155) {
        case 0:
            func_806A2A10(0xDC, 0x2A, obj->unk1C);
            LA->unk155 = 1;
        case 1:
            if (obj->act[3]->unk154 == 0) {
                LA->unk154 = 2;
            }
            break;
        }
        break;
    case 4:
        switch (LA->unk155) {
        case 0:
            obj->unk10 = 0x400;
            obj->unk12 = 0x40;
            LA->unk155 += 1;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x179, 0xFF, 0x7F, 1);
            if (obj->unk1A == 0) {
                obj->unk1A = 1;
                actorSetStateTwo(LA->unk11C);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        case 1:
            LA->unkE8 = func_80612794(obj->unk10) * -1024.0f + 1024.0f;
            obj->unk10 += obj->unk12;
            if (obj->unk10 >= 0x800) {
                obj->unk12 = -0x40;
                bonusInitActors(obj, (u32)((f32)obj->unk1E + (f32)(obj->unk1D - obj->unk1E) * ((f32)(obj->unk16 - 1) / (f32)two)));
                LA->unk6E = func_80609140(0x24D, 0x7FFF, 64.0f, 1.0f, 0, 0);
                camSetTarget(sp4C->unk104, D_807FBB48, 4, 0, 0x78, 0, 0, 0, 0, 0, 0.09f);
            } else if (obj->unk10 < 0x400) {
                LA->unk154 = 5;
                LA->unk155 = 0;
            }
            break;
        }
        break;
    case 5:
        if (LA->unk168 == 4) {
            LA->unk154 = 7;
            LA->unk155 = 0;
            break;
        }
        if (LA->unk155 != 0) {
            bonusSpawnEffectBurst(obj->act[LA->unk168]->unk7C, obj->act[LA->unk168]->unk80, obj->act[LA->unk168]->unk84 + 20.0f, 0xF);
            obj->act[LA->unk168]->unk154 += 1;
            LA->unk168 += 1;
            LA->unk154 = 6;
            LA->unk155 = 0;
        }
        break;
    case 7:
        if (D_807457E4[LA->unk6E] != 0) {
            n_alSndpStop(D_807457E4[LA->unk6E]);
        }
    case 1:
        if (LA->unk11C->unk154 != 5) {
            if (bonusGetReelSymbol(obj, 0) == 0 && bonusGetReelSymbol(obj, 0) == bonusGetReelSymbol(obj, 1) && bonusGetReelSymbol(obj, 1) == bonusGetReelSymbol(obj, 2) && bonusGetReelSymbol(obj, 2) == bonusGetReelSymbol(obj, 3)) {
                func_806FDAB8(obj->unk19, 3.1415927f);
                obj->unk16 -= 1;
                if (obj->unk16 == 0) {
                    LPA->unk155 = 1;
                    bonusEndWin(0, 0);
                    LA->unk154 = 8;
                    obj->unk10 = 0;
                    obj->unk1A = 0;
                    camStartPath(0, 0, 0x11);
                } else {
                    textSpawnMarkerChecked(0, 0, 0xB4, func_8070E750(0x1A, 0xB, 1), 0, 0x28, 8, 8);
                    bonusReelNextRound(obj);
                }
            } else {
                textSpawnMarkerChecked(0, 0, 0xB4, func_8070E750(0x1A, 0xC, 1), 0, 0x28, 8, 8);
                bonusReelNextRound(obj);
            }
        } else {
            LPA->unk155 = 2;
            bonusEndLose(0, 1);
            LA->unk154 = 9;
            obj->unk10 = 0;
            obj->unk1A = 0;
            camStartPath(0, 0, 0x11);
        }
        break;
    case 8:
        i = 0;
        do {
            if (!((obj->unk10 - i * 8 + 0x18) % 32)) {
                bonusSpawnEffectBurst(obj->act[i]->unk7C, obj->act[i]->unk80, obj->act[i]->unk84 + 20.0f, 0xF);
            }
        } while (++i < 4);
    case 9:
        obj->unk10 += 1;
        break;
    }
    if (LA->unk154 > 0 && LA->unk154 < 8) {
        renderCallbacksRegister(bonusRenderReelHud, D_807FBB40, 3);
    }
    if (LA->unk154 >= 8) {
        if (obj->unk20 != 0) {
            effectFreeAndUnlink(obj->unk20);
            obj->unk20 = 0;
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

f32 asinApprox(f32);
f32 sinApprox(f32);

void bonusReelUpdate(void) {
    BonusEObj *obj;
    s16 t;

    obj = BA->unk174;
    if (!(BA->unk60 & 0x10)) {
        BA->unkE8 = ((randomNonNegative() >> 15) % 6 * 0x3C000) / 360;
    }
    switch (BA->unk154) {
    case 1:
        obj->unk4 = -0x18;
        BA->unk154 += 1;
        break;
    case 2:
        if (obj->unk4 < 0) {
            BA->unkE8 += obj->unk4;
            obj->unk4 += 2;
        } else {
            BA->unk154 += 1;
            obj->unk4 = BA->unkF0;
        }
        break;
    case 4:
        t = 0x2AB - (BA->unkE8 % 0x2AB);
        if (t < obj->unk4) {
            BA->unk154 += 1;
            if (obj->unk0->unk154 < 8) {
                obj->unk0->unk154 = 5;
                obj->unk0->unk155 = 0;
            }
            BA->unk160 = asinApprox((obj->unk4 - t) * 0.015625);
            BA->unk168 = (BA->unkE8 + t) & 0xFFF;
            BA->unk15F = BA->unk168 / 0x2AB;
            sfxPlayFromActorWithAltitudeCheck(BA, 0x17A, 0xFF, 0x7F, 1);
        }
    case 3:
        BA->unkE8 += obj->unk4;
        BA->unkE8 &= 0xFFF;
        break;
    case 5:
        if (BA->unk160 < 6.2831854820251465) {
            BA->unkE8 = sinApprox(BA->unk160) * 90.0 + BA->unk168;
            BA->unk160 = BA->unk160 + 0.3;
        } else {
            BA->unkE8 = BA->unk168;
            BA->unk154 = 0;
        }
        break;
    }
    actorUpdateModelMatrix(BA, 0);
}
void camStartPathNearWall(void *, s32, s32, s32);

void bonusEndWin(u8 arg0, u8 arg1) {
    func_80609140(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
    textSpawnMarkerChecked(0x81, 0, 0x78, func_8070E750(0x1A, arg1, 1), 0, 0x28, 8, 8);
    LA->unk11C->unk154 = 0;
    sfxAllocateChannel(0x28, 1.0f);
    playerStateQueueCallback(0x44, 0, 0);
    LA->unk154 += 1;
    if (arg0 != 0) {
        camStartPathNearWall(D_807FBB4C, 5, 0x21, 5);
    }
}

void bonusEndLose(u8 arg0, u8 arg1) {
    LA->unk11C->unk154 = 0;
    textSpawnMarkerChecked(0x81, 0, 0x78, func_8070E750(0x1A, arg1, 1), 0, 0x28, 8, 8);
    sfxAllocateChannel(0x57, 1.0f);
    playerStateQueueCallback(0x43, 0, 0);
    LA->unk154 += 1;
    if (arg0 != 0) {
        camStartPathNearWall(D_807FBB4C, 5, 0x21, 5);
    }
}
