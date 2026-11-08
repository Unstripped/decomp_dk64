#include "common.h"
#include "actor.h"

extern Gfx D_1000118;
extern Mtx D_2000080;
extern Mtx D_2000180;
Gfx *textDrawAnimated(Gfx *, u8, s32, f32, f32, f32, f32);
Gfx *hudDrawRollingCounter(Gfx *, s32, s32, void *, s16, void *);

typedef struct LB3Obj {
    Actor *act[4];
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

typedef struct LB3Player {
    u8 pad0[0x104];
    void *unk104;
} LB3Player;

typedef struct BonusEObj {
    Actor *unk0;
    s16 unk4;
} BonusEObj;

s32 actorSpawn(s32, s32);
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *D_807FBB4C;

Gfx *bonusRenderReelHud(Gfx *gdl, Actor *actor) {
    LB3Obj *reelObj = actor->unk174;

    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(gdl++, &D_1000118);
    gSPMatrix(gdl++, &D_2000080, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return hudDrawRollingCounter(
        textDrawAnimated(gdl, reelObj->unk19, 8, 30.0f, 36.0f, 0.0f, 1.5f),
        0x26, 0x32, &reelObj->unk14, reelObj->unk16, &reelObj->unk18);
}

void *bonusSpawnReel(s32 type, s16 x, s16 y, s16 z) {
    if (actorSpawn(0xDB, type) != 0) {
        BonusEObj *obj = gSpawnedActor->unk174;
        gSpawnedActor->x = (f32)x;
        gSpawnedActor->y = (f32)y;
        gSpawnedActor->z = (f32)z;
        obj->unk0 = gCurrentActor;
    }
    return gSpawnedActor;
}

extern u8 *D_8002D8B0[];

u8 bonusGetReelSymbol(LB3Obj *obj, u8 reelIndex) {
    s32 idx = reelIndex;
    return D_8002D8B0[idx][obj->act[idx]->unk15F];
}

void func_807149B8(s32);
s32 func_8071498C(void (*)(void));
void func_80714950(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
s32 randomNonNegative();
extern void *D_8074E880[];
void effectConfettiPhysicsUpdate(void);

void bonusSpawnEffectBurst(s16 x, s16 y, s16 z, s16 count) {
    s16 i;

    for (i = 0; i < count; i++) {
        func_807149B8(1);
        func_8071498C(effectConfettiPhysicsUpdate);
        func_80714950(1);
        func_80714CC0(D_8074E880[(randomNonNegative() >> 15) % 1000 % 3], 0.3f, (f32)x, (f32)y, (f32)z);
    }
}

void camSetTarget(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);

void bonusReelNextRound(LB3Obj *obj) {
    LB3Player *player = D_807FBB4C->unk174;
    camSetTarget(player->unk104, D_807FBB4C, 4, 0, 0xAA, 0, 0, 0, 0, 0, 0.09f);
    gCurrentActor->state = 3;
    gCurrentActor->unk155[0] = 1;
    gCurrentActor->yawSpeed = 0;
}

void bonusInitActors(LB3Obj *obj, u8 timerVal) {
    u8 i = 0;
    do {
        obj->act[i]->state++;
        obj->act[i]->movePitch = timerVal;
    } while (++i < 4);
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DC90.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DC98.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DCA0.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DCA8.s")

extern s32 gCurrentMap;
extern Actor *D_807FBB48;
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
void hudSpawnCountdownTimer(s32, s32, s32);
void actorSetStateTwo(void *);
void n_alSndpStop(s32);
void effectFreeAndUnlink(s32);
void renderCallbacksRegister(void *, void *, s32);
f32 mathSinF(s16);
s16 sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void bonusEndWin(u8, u8);
void bonusEndLose(u8, u8);
void textSpawnMarkerChecked(s32, s32, s32, s32, s32, s32, s32, s32);
void sfxAllocateChannel(s32, f32);
s32 textTableGetString(s32, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void actorUpdateModelMatrix(void *, s32);

void bonusReelGameUpdate(void) {
    LB3Player *player;
    LB3Obj *obj;
    u8 i;
    s32 two;

    two = 2;
    player = D_807FBB4C->unk174;
    obj = gCurrentActor->unk174;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->x = 52.0f;
        gCurrentActor->z = 18.0f;
        obj->unk19 = gfxResourceCreate(1, "HIT", 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(obj->unk19, 0.0f);
        obj->unk16 = 3;
        obj->unk14 = 3;
        obj->act[0] = bonusSpawnReel(0x90, -0x15, 1, 0x12);
        obj->act[1] = bonusSpawnReel(0x91, -7, 1, 0x12);
        obj->act[2] = bonusSpawnReel(0x92, 7, 1, 0x12);
        obj->act[3] = bonusSpawnReel(0x93, 0x15, 1, 0x12);
        playerStateQueueCallback(0x49, 0, 0);
        camSetTargetScaled(player->unk104, D_807FBB4C, 6, 0, 0xAA, 0, 0, 0, 0, 0, 1.0f);
        camStartPath(0, 1, 1);
        switch (gCurrentMap) {
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
    if (obj->unk1A != 0 && ((Actor *)gCurrentActor->unk11C)->state == 5) {
        gCurrentActor->state = 1;
        gCurrentActor->unk155[0] = 0;
    }
    switch (gCurrentActor->state) {
    case 0:
        switch (gCurrentActor->unk155[0]) {
        case 0:
            if (D_807444EC != 1) {
                func_8070D8C0(gCurrentActor, 0, 3);
                gCurrentActor->unk155[0] += 1;
            }
            break;
        case 1:
            if (!(gCurrentActor->flags & 0x02000000)) {
                gCurrentActor->state = 3;
                gCurrentActor->unk155[0] = 0;
                func_8071495C();
                func_80714998(2);
                func_807149FC(-1);
                obj->unk20 = func_80714CC0(&D_80720CF0, 1.0f, 40.0f, 200.0f, 5.0f);
            }
            break;
        }
        break;
    case 3:
        switch (gCurrentActor->unk155[0]) {
        case 0:
            hudSpawnCountdownTimer(0xDC, 0x2A, obj->unk1C);
            gCurrentActor->unk155[0] = 1;
        case 1:
            if (obj->act[3]->state == 0) {
                gCurrentActor->state = 2;
            }
            break;
        }
        break;
    case 4:
        switch (gCurrentActor->unk155[0]) {
        case 0:
            obj->unk10 = 0x400;
            obj->unk12 = 0x40;
            gCurrentActor->unk155[0] += 1;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x179, 0xFF, 0x7F, 1);
            if (obj->unk1A == 0) {
                obj->unk1A = 1;
                actorSetStateTwo((void *)gCurrentActor->unk11C);
                sfxAllocateChannel(8, 1.0f);
            }
            break;
        case 1:
            gCurrentActor->roll = mathSinF(obj->unk10) * -1024.0f + 1024.0f;
            obj->unk10 += obj->unk12;
            if (obj->unk10 >= 0x800) {
                obj->unk12 = -0x40;
                bonusInitActors(obj, (u32)((f32)obj->unk1E + (f32)(obj->unk1D - obj->unk1E) * ((f32)(obj->unk16 - 1) / (f32)two)));
                gCurrentActor->soundSlot = sfxPlayOnFreeSlot(0x24D, 0x7FFF, 64.0f, 1.0f, 0, 0);
                camSetTarget(player->unk104, D_807FBB48, 4, 0, 0x78, 0, 0, 0, 0, 0, 0.09f);
            } else if (obj->unk10 < 0x400) {
                gCurrentActor->state = 5;
                gCurrentActor->unk155[0] = 0;
            }
            break;
        }
        break;
    case 5:
        if (gCurrentActor->yawSpeed == 4) {
            gCurrentActor->state = 7;
            gCurrentActor->unk155[0] = 0;
            break;
        }
        if (gCurrentActor->unk155[0] != 0) {
            bonusSpawnEffectBurst(obj->act[gCurrentActor->yawSpeed]->x, obj->act[gCurrentActor->yawSpeed]->y, obj->act[gCurrentActor->yawSpeed]->z + 20.0f, 0xF);
            obj->act[gCurrentActor->yawSpeed]->state += 1;
            gCurrentActor->yawSpeed += 1;
            gCurrentActor->state = 6;
            gCurrentActor->unk155[0] = 0;
        }
        break;
    case 7:
        if (D_807457E4[gCurrentActor->soundSlot] != 0) {
            n_alSndpStop(D_807457E4[gCurrentActor->soundSlot]);
        }
    case 1:
        if (((Actor *)gCurrentActor->unk11C)->state != 5) {
            if (bonusGetReelSymbol(obj, 0) == 0 && bonusGetReelSymbol(obj, 0) == bonusGetReelSymbol(obj, 1) && bonusGetReelSymbol(obj, 1) == bonusGetReelSymbol(obj, 2) && bonusGetReelSymbol(obj, 2) == bonusGetReelSymbol(obj, 3)) {
                func_806FDAB8(obj->unk19, 3.1415927f);
                obj->unk16 -= 1;
                if (obj->unk16 == 0) {
                    D_807FBB4C->unk155[0] = 1;
                    bonusEndWin(0, 0);
                    gCurrentActor->state = 8;
                    obj->unk10 = 0;
                    obj->unk1A = 0;
                    camStartPath(0, 0, 0x11);
                } else {
                    textSpawnMarkerChecked(0, 0, 0xB4, textTableGetString(0x1A, 0xB, 1), 0, 0x28, 8, 8);
                    bonusReelNextRound(obj);
                }
            } else {
                textSpawnMarkerChecked(0, 0, 0xB4, textTableGetString(0x1A, 0xC, 1), 0, 0x28, 8, 8);
                bonusReelNextRound(obj);
            }
        } else {
            D_807FBB4C->unk155[0] = 2;
            bonusEndLose(0, 1);
            gCurrentActor->state = 9;
            obj->unk10 = 0;
            obj->unk1A = 0;
            camStartPath(0, 0, 0x11);
        }
        break;
    case 8:
        i = 0;
        do {
            if (!((obj->unk10 - i * 8 + 0x18) % 32)) {
                bonusSpawnEffectBurst(obj->act[i]->x, obj->act[i]->y, obj->act[i]->z + 20.0f, 0xF);
            }
        } while (++i < 4);
    case 9:
        obj->unk10 += 1;
        break;
    }
    if (gCurrentActor->state > 0 && gCurrentActor->state < 8) {
        renderCallbacksRegister(bonusRenderReelHud, gCurrentActor, 3);
    }
    if (gCurrentActor->state >= 8) {
        if (obj->unk20 != 0) {
            effectFreeAndUnlink(obj->unk20);
            obj->unk20 = 0;
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

f32 asinApprox(f32);
f32 sinApprox(f32);

void bonusReelUpdate(void) {
    BonusEObj *obj;
    s16 t;

    obj = gCurrentActor->unk174;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->roll = ((randomNonNegative() >> 15) % 6 * 0x3C000) / 360;
    }
    switch (gCurrentActor->state) {
    case 1:
        obj->unk4 = -0x18;
        gCurrentActor->state += 1;
        break;
    case 2:
        if (obj->unk4 < 0) {
            gCurrentActor->roll += obj->unk4;
            obj->unk4 += 2;
        } else {
            gCurrentActor->state += 1;
            obj->unk4 = gCurrentActor->movePitch;
        }
        break;
    case 4:
        t = 0x2AB - (gCurrentActor->roll % 0x2AB);
        if (t < obj->unk4) {
            gCurrentActor->state += 1;
            if (obj->unk0->state < 8) {
                obj->unk0->state = 5;
                obj->unk0->unk155[0] = 0;
            }
            gCurrentActor->splineT = asinApprox((obj->unk4 - t) * 0.015625);
            gCurrentActor->yawSpeed = (gCurrentActor->roll + t) & 0xFFF;
            gCurrentActor->unk15F = gCurrentActor->yawSpeed / 0x2AB;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17A, 0xFF, 0x7F, 1);
        }
    case 3:
        gCurrentActor->roll += obj->unk4;
        gCurrentActor->roll &= 0xFFF;
        break;
    case 5:
        if (gCurrentActor->splineT < 6.2831854820251465) {
            gCurrentActor->roll = sinApprox(gCurrentActor->splineT) * 90.0 + gCurrentActor->yawSpeed;
            gCurrentActor->splineT = gCurrentActor->splineT + 0.3;
        } else {
            gCurrentActor->roll = gCurrentActor->yawSpeed;
            gCurrentActor->state = 0;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
void camStartPathNearWall(void *, s32, s32, s32);

void bonusEndWin(u8 useCutsceneCam, u8 textIndex) {
    sfxPlayOnFreeSlot(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
    textSpawnMarkerChecked(0x81, 0, 0x78, textTableGetString(0x1A, textIndex, 1), 0, 0x28, 8, 8);
    ((Actor *)gCurrentActor->unk11C)->state = 0;
    sfxAllocateChannel(0x28, 1.0f);
    playerStateQueueCallback(0x44, 0, 0);
    gCurrentActor->state += 1;
    if (useCutsceneCam != 0) {
        camStartPathNearWall(D_807FBB4C, 5, 0x21, 5);
    }
}

void bonusEndLose(u8 useCutsceneCam, u8 textIndex) {
    ((Actor *)gCurrentActor->unk11C)->state = 0;
    textSpawnMarkerChecked(0x81, 0, 0x78, textTableGetString(0x1A, textIndex, 1), 0, 0x28, 8, 8);
    sfxAllocateChannel(0x57, 1.0f);
    playerStateQueueCallback(0x43, 0, 0);
    gCurrentActor->state += 1;
    if (useCutsceneCam != 0) {
        camStartPathNearWall(D_807FBB4C, 5, 0x21, 5);
    }
}
