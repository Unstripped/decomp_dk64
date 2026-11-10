#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/boot/3D20.h"
#include "proto/boss/3840.h"
#include "proto/global/100180.h"
#include "proto/global/10D2D0.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/135D30.h"
#include "proto/global/13A7A0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/3C10.h"
#include "proto/global/450.h"
#include "proto/global/FCCD0.h"
#include "proto/global/7130.h"

void bossInitScriptData(u8 *data) {
    s16 i;
    u8 *dst;

    if (gBehaviourAnimState->path != NULL) {
        heapFree(gBehaviourAnimState->path);
    }
    gBehaviourExtraState->pathCount = *data;
    gBehaviourAnimState->path = heapAlloc(*data * 2);
    dst = gBehaviourAnimState->path;
    for (i = 0; i < *data; i++) {
        dst[0] = data[i + 1];
        dst[1] = 0;
        dst += 2;
    }
}

typedef struct BossB_Struct_800278F4 {
    char pad0[8];
    f32 x;
    f32 y;
} BossB_Struct_800278F4;

void bossLerpCoords(BossB_Struct_800278F4 *coords, f32 factor, s16 targetY, s16 targetX) {
    coords->y += ((f32)targetY - coords->y) * factor;
    coords->x += ((f32)targetX - coords->x) * factor;
}

typedef struct BossB_Struct_80027950 {
    char pad0[0x15];
    u8 scriptPos;
} BossB_Struct_80027950;


void bossPickRandomWaypoint(BossB_Struct_80027950 *state, u8 *waypointRanges) {
    u8 prev = gBehaviourWorkState->unk25;
    do {
        s32 rand = randomNonNegative() >> 15;
        u8 offset = state->scriptPos;
        gBehaviourWorkState->unk25 = waypointRanges[offset] + ((rand % 65536) % (waypointRanges[offset + 1] - waypointRanges[offset] + 1));
    } while (gBehaviourWorkState->unk25 == prev);
    state->scriptPos += 2;
}

extern Actor *gCurrentActor;

void bossPickFarthestWaypoint(void *state, u8 *waypointRanges) {
    s16 i;
    s32 max_dist = 0;

    for (i = waypointRanges[((BossB_Struct_80027950 *)state)->scriptPos]; i <= waypointRanges[((BossB_Struct_80027950 *)state)->scriptPos + 1]; i++) {
        u8 idx = gBehaviourAnimState->path[i][0];
        Actor *actor = gCurrentActor;
        ZoneEntry *pt = &D_807FDCA0->entries[idx];
        f32 dz = actor->z - (f32)pt->z;
        f32 dx = actor->x - (f32)pt->x;
        f32 dy = actor->y - (f32)pt->y;
        s32 dist = (s32)sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));

        if (dist > max_dist) {
            max_dist = dist;
            gBehaviourWorkState->unk25 = i;
        }
    }
    ((BossB_Struct_80027950 *)state)->scriptPos += 2;
}


typedef struct BossScriptState {
    char pad0[4];
    s16 unk4;
    char pad6[2];
    s16 unk8[5];
    u16 unk12;
    u8 unk14;
    u8 scriptPos;
    u8 loopPos;
    u8 pad17;
    u8 unk18[8];
} BossScriptState;

typedef struct BossActor {
    Actor base;
    BossScriptState *scriptState;
    u8 *script;
} BossActor;

extern Actor *gPrimaryPlayerActor;
extern u8 gGameMode;
extern u8 gScreenRenderFlags;
extern s8 sHudDisabled;

void camEndPath(s32);
void currentActorClearFlag();
s32 currentActorTestClearFlag(void);
void actorSetTargetSpeed(void *, s32);
void resQueueAttachActor(void *, s32, s32);
u8 patrolPathStep(u8, u8);
u32 actorMoveWithinZone(u8, f32, f32, u16, f32);
void actorScriptStart(void *, s32);

#define BA40 ((BossActor *)gCurrentActor)

u8 bossScriptStep(u8 *script, u16 turnSpeed, f32 fwdSpeed) {
    PlayerState *playerData;
    BossScriptState *s0;
    u8 advanceScript;
    u8 didLoop;
    u8 tmp;

    playerData = gPrimaryPlayerActor->customState;
    s0 = BA40->scriptState;
    didLoop = 0;
    advanceScript = 1;
    switch (BA40->base.state) {
    case 0x54:
        advanceScript = 0;
        if (BA40->base.unk155 != 0) {
            if (currentActorTestClearFlag() != 0) {
                advanceScript = 1;
            }
        } else {
            currentActorClearFlag();
            BA40->base.unk155 = 1;
        }
        break;
    case 0x5F:
        camStartPath(gCurrentActor, script[s0->scriptPos++], 1);
        break;
    case 0x5E:
        if (gGameMode == 1) {
            camEndPath(playerData->camActor);
        }
        sHudDisabled = 0;
        BA40->base.flags &= ~4;
        gScreenRenderFlags |= 0x10;
        s0->unk4 = script[s0->scriptPos++] * 30;
        break;
    case 0x5D:
        actorSetTargetSpeed(gCurrentActor, script[s0->scriptPos++]);
        break;
    case 0x5C:
        {
            u8 *p = BA40->script;
            *p = script[s0->scriptPos];
            s0->scriptPos++;
        }
        break;
    case 0x5A:
        resQueueAttachActor(gCurrentActor, script[s0->scriptPos], script[s0->scriptPos + 1]);
        s0->scriptPos += 2;
        break;
    case 0x42:
block_16:
        actorMoveWithinZone(0x42, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, turnSpeed, fwdSpeed);
        if (patrolPathStep(BA40->base.state, 0) == 0) {
            advanceScript = 0;
        }
        break;
    case 0x69:
        gBehaviourWorkState->flags |= 0x20;
        break;
    case 0x58:
        BA40->base.flags |= 4;
        break;
    case 0x59:
        BA40->base.flags &= ~4;
        break;
    case 0x51:
        actorScriptStart(gCurrentActor, (script[s0->scriptPos] << 8) + script[s0->scriptPos + 1]);
        s0->scriptPos += 2;
        break;
    case 0x55:
        advanceScript = 0;
        if (BA40->base.unk155 == 0) {
            tmp = s0->scriptPos;
            s0->unk8[0] = (script[tmp] << 8) + script[tmp + 1];
            s0->scriptPos = tmp + 2;
            BA40->base.unk155 = 1;
        } else {
            s0->unk8[0] -= 1;
            if (s0->unk8[0] == 0) {
                advanceScript = 1;
            }
        }
        break;
    case 0x23:
        advanceScript = 0;
        if (BA40->base.unk155 == 0) {
            tmp = s0->scriptPos;
            s0->unk8[0] = script[tmp];
            s0->scriptPos = tmp + 1;
            BA40->base.unk155 = 1;
            actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkD);
        } else {
            actorMoveWithinZone(0x23, gBehaviourWorkState->unk4->x, gBehaviourWorkState->unk4->z, turnSpeed, fwdSpeed);
            s0->unk8[0] -= 1;
            if ((s0->unk8[0] == 0) || (playerData->stateFlags & 0x80000)) {
                playerData->stateFlags &= ~0x80000;
                advanceScript = 1;
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
            }
        }
        break;
    case 0x52:
        if (!(BA40->base.contactFlags & 1)) {
            advanceScript = 0;
        }
        break;
    case 0x53:
        if (BA40->base.unk155 == 0) {
            advanceScript = 0;
        }
        break;
    case 0x4F:
        s0->loopPos = s0->scriptPos;
        break;
    case 0x50:
        s0->scriptPos = s0->loopPos;
        break;
    case 0x66:
        if (gBehaviourWorkState->flags & 8) {
            s0->scriptPos = s0->loopPos;
        }
        break;
    case 0x63:
        tmp = s0->scriptPos;
        if (s0->unk8[script[tmp]] != 0) {
            s0->unk8[script[tmp]] -= 1;
            advanceScript = 0;
        } else {
            s0->scriptPos = tmp + 1;
        }
        break;
    case 0x62:
        s0->unk8[script[s0->scriptPos]] = script[s0->scriptPos + 1];
        s0->scriptPos += 2;
        didLoop = 1;
        break;
    case 0x64:
        s0->unk18[script[s0->scriptPos]] = script[s0->scriptPos + 1];
        s0->scriptPos += 2;
        didLoop = 1;
        break;
    case 0x68:
        gBehaviourWorkState->flags &= 0xFFEF;
        didLoop = 1;
        break;
    case 0x65:
        gBehaviourWorkState->timer = script[s0->scriptPos];
        s0->scriptPos++;
        didLoop = 1;
        break;
    case 0x67:
        bossPickRandomWaypoint((BossB_Struct_80027950 *)s0, script);
        advanceScript = 0;
        BA40->base.state = 0x42;
        BA40->base.unk155 = 0;
        goto block_16;
    case 0x4C:
        bossPickFarthestWaypoint(s0, script);
        advanceScript = 0;
        BA40->base.state = 0x42;
        BA40->base.unk155 = 0;
        goto block_16;
    case 0x4B:
        gBehaviourWorkState->unk25++;
        if (script[s0->scriptPos + 1] < gBehaviourWorkState->unk25) {
            gBehaviourWorkState->unk25 = script[s0->scriptPos];
        }
        s0->scriptPos += 2;
        advanceScript = 0;
        BA40->base.state = 0x42;
        BA40->base.unk155 = 0;
        goto block_16;
    case 0x41:
        gBehaviourWorkState->unk25 = script[s0->scriptPos];
        s0->scriptPos++;
        advanceScript = 0;
        BA40->base.state = 0x42;
        BA40->base.unk155 = 0;
        goto block_16;
    case 0x49:
    case 0x4A:
        advanceScript = 0;
        switch (BA40->base.unk155) {
        case 0:
            BA40->base.alpha -= 0xA;
            if (BA40->base.alpha < 0) {
                BA40->base.alpha = 0;
                BA40->base.unk155++;
            }
            break;
        case 1:
            if (BA40->base.state == 0x49) {
                gBehaviourWorkState->unk25 = script[s0->scriptPos];
                s0->scriptPos++;
            } else {
                bossPickRandomWaypoint((BossB_Struct_80027950 *)s0, script);
            }
            patrolPathStep(0x49, 0);
            BA40->base.x = gBehaviourWorkState->targetX;
            BA40->base.z = gBehaviourWorkState->targetZ;
            BA40->base.unk155++;
            break;
        case 2:
            BA40->base.alpha += 0xA;
            if (BA40->base.alpha >= 0x100) {
                BA40->base.alpha = 0xFF;
                advanceScript = 1;
            }
            break;
        }
        break;
    case 0x6D:
        break;
    default:
        advanceScript = 0;
        break;
    }
    if (advanceScript != 0) {
        BA40->base.state = script[s0->scriptPos];
        s0->scriptPos++;
        BA40->base.unk155 = 0;
    }
    return didLoop;
}



void bossClearMinigame(void) {
    mapTransitionToMenuOrPrevious();
}

void sfxAllocateChannel(s32, f32);
void actorSpawnNodeEntryScaled(s16, f32, f32, f32, s32, s32, s32, s32);

extern s32 D_8074E880[];

void bossSpawnParticleRing(flag, x, y, z, unkRot, unkScale)
u16 flag;
s16 x;
s16 y;
s16 z;
s16 unkRot;
u8 unkScale;
{
    s16 s0;

    sfxAllocateChannel(0x36, 1.0f);
    if (flagGet((s16)flag, 0) != 0) {
        bossClearMinigame();
        return;
    }
    for (s0 = 0; s0 < 6; s0++) {
        effectSetCallback(effectWispHomeUpdate);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetSpeed(gBehaviourTargetActor);
        effectCreateAtPosition(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3], 1.8f, gBehaviourTargetActor->x, gBehaviourTargetActor->y + (f32)gBehaviourTargetActor->eyeHeight, gBehaviourTargetActor->z);
    }
    actorSpawnNodeEntryScaled(0x48, (f32)x, (f32)y, (f32)z, (s32)unkRot, (s32)unkScale, (s16)flag, 0);
}

void hudSpawnCountdownTimer(s16, s16, u8);
void actorSetStateTwo(s32);

void bossStartCountdownTimer(void) {
    hudSpawnCountdownTimer(-0x7F83, 0xD2, 0xB4);
    actorSetStateTwo(gCurrentActor->parentActor);
}

#define Boss2C_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

typedef float Boss2C_MtxF[4][4];

extern PlayerStruct *gPlayerSlots;
extern u8 D_80750AD4;
extern Gfx D_1000118;

void *func_8070068C(Gfx *);

void bossDrawRoundText(Gfx *glist, s32 unused) {
    Boss2C_MtxF scaleMtx;
    Boss2C_MtxF transMtx;
    Mtx *mtx;
    char textBuf[16];

    mtx = heapAlloc(sizeof(Mtx));
    heapFreeDeferred(mtx);
    guScaleF(scaleMtx, 0.6f, 0.6f, 1.0f);
    guTranslateF(transMtx, 100.0f, (f32)(gPlayerSlots->rect[3] * 4 - 0x3C), 0.0f);
    guMtxCatF(scaleMtx, transMtx, scaleMtx);
    guMtxF2L(scaleMtx, mtx);
    Boss2C_WRITE_GFX(glist++, 0xDA380003, (u32)mtx);
    _sprintf(textBuf, "ROUND %d", D_80750AD4);
    Boss2C_WRITE_GFX(glist++, 0xDE000000, (u32)&D_1000118);
    Boss2C_WRITE_GFX(glist++, 0xE7000000, 0);
    Boss2C_WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);
    Boss2C_WRITE_GFX(glist++, 0xFA000000, 0xFFFFFFFF);
    glist = func_8070068C(glist);
    textDrawStringVtx(glist, 1, 0, 0, textBuf, 0);
}

static void bossRoundDummy(void) {}


void bossResetAudioChannels(void) {
    flagSet(0x51, 0, 2);
    flagSet(0x52, 0, 2);
    flagSet(0x53, 0, 2);
    flagSet(0x54, 0, 2);
}

typedef struct BossSoundState {
    s32 lastTick;
    s32 sndHandleA;
    s32 sndHandleB;
    u8 stepCount;
    u8 flags;
    s16 curVolume;
    s16 targetVolume;
} BossSoundState;

extern Actor *gActivePlayerActor;
extern s16 D_800359A0[];
extern s16 D_800359AC[];
extern s16 D_800359B8[];
extern s16 D_800359C4[];
extern u8 D_8071FE08[];
extern s32 D_8076D1F8;
extern u32 D_80767CC0;
extern s32 gCurrentMap;

void sfxStopChannel(s32, s32);
void func_80724A20(void);  // FAKE: callee prototype steer
void actorSetStateOne(void *);
void actorSetStateThree(void *);
f32 sfxGetChannelVolume(s32);
void renderCallbacksRegister(void *, void *, u8);


void bossRoundFrame(u8 *script) {
    BossScriptState *scriptState;
    u8 mapOffset;
    s16 mapFlag;
    BossSoundState *s0;

    scriptState = BA40->scriptState;
    mapOffset = gCurrentMap - 0xCB;
    s0 = (BossSoundState *)BA40->script;
    if (gPrimaryPlayerActor->y < 30.0f) {
        gPrimaryPlayerActor->x = 780.0f;
        gPrimaryPlayerActor->y = 50.0f;
        gPrimaryPlayerActor->z = 750.0f;
        effectCreateAtPosition(D_8071FE08, 1.0f, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y, gPrimaryPlayerActor->z);
    }
    if (!(BA40->base.flags & 0x10)) {
        slotQueueSetDisplayMode(5, 0, 1);
        slotQueueSetDisplayMode(2, 0, 1);
        BA40->base.flags &= 0xFFFDFFFF;
        if ((scriptState->unk14 == 0) || (BA40->base.actorType != 0x126)) {
            if (flagGet(0x5A, 2) == 0) {
                healthRefill(0);
            }
            D_80750AD4++;
            if (D_80750AD4 >= 0xD) {
                sfxStopChannel(0x2B, 0);
                healthRefill(0);
                flagSet(0x55, 0, 2);
                menuTransitionToMap(0xD7, 0);
                D_80750AD4 = 0;
                BA40->base.state = 0x6A;
                BA40->base.unk155 = 0;
            }
        }
        n_alSndpPlay(D_8076D1F8, 0x1E6, 0, 0x40, 1.0f, 0x80, &s0->sndHandleA);
        n_alSndpPlay(D_8076D1F8, 0x119, 0, 0x40, 1.0f, 0x80, &s0->sndHandleB);
    }
    func_80724A20();
    switch (BA40->base.state) {
    case 0x37:
        if (BA40->base.unk155 == 0) {
            actorSetStateOne(BA40->base.parentActor);
        }
        break;
    case 0x6A:
        if (BA40->base.unk155 == 0) {
            actorScriptStart(gCurrentActor, 0);
            BA40->base.unk155++;
        }
        break;
    case 0x6C:
        scriptState->unk12 |= 1;
        bossStartCountdownTimer();
        if ((scriptState->unk14 != 0) && (BA40->base.actorType == 0x126)) {
            actorSetStateThree(BA40->base.parentActor);
        }
        BA40->base.state = script[scriptState->scriptPos];
        scriptState->scriptPos++;
        BA40->base.unk155 = 0;
        break;
    default:
        if ((BA40->base.parentActor != NULL) && (BA40->base.parentActor->state == 5)) {
            bossResetAudioChannels();
            BA40->base.state = 0x6A;
            BA40->base.unk155 = 0;
            camStartPath(gCurrentActor, D_800359C4[mapOffset], 1);
            flagSet(0x5A, 1, 2);
        }
        break;
    }
    if (!(BA40->base.flags & 0x10)) {
        if (menuIsTransitionTypeC() != 0) {
            flagSet(0x55, 0, 2);
        }
        if ((flagGet(0x5D, 2) == 0) || (flagGet(0x5C, 2) != 0)) {
            bossResetAudioChannels();
            D_80750AD4 = 1;
            if (flagGet(0x5D, 2) == 0) {
                camStartPath(gCurrentActor, 0x19, 1);
                flagSet(0x5D, 1, 2);
            } else {
                camStartPath(gCurrentActor, D_800359A0[0], 1);
            }
            flagSet(0x5C, 0, 2);
            flagSet(0x55, 1, 2);
        } else {
            mapFlag = mapOffset + 0x55;
            if (flagGet(mapFlag, 2) == 0) {
                camStartPath(gCurrentActor, D_800359A0[mapOffset], 1);
                flagSet(mapFlag, 1, 2);
            } else if (flagGet(0x5A, 2) != 0) {
                if (flagGet(0x5B, 2) != 0) {
                    camStartPath(gCurrentActor, D_800359AC[mapOffset], 1);
                    flagSet(0x5A, 0, 2);
                } else {
                    sfxStopChannel(0x2B, 0);
                    BA40->base.state = 0x6A;
                    BA40->base.unk155 = 0;
                    flagSet(0x5B, 1, 2);
                    menuTransitionToMap(0xD7, 1);
                    D_80750AD4 -= 1;
                }
            } else {
                camStartPath(gCurrentActor, D_800359B8[mapOffset], 1);
            }
        }
    }
    if ((gActivePlayerActor->state == 0x67) || (sfxGetChannelVolume(0xF) > 0.1)) {
        s0->curVolume = 0x1D4C;
        if (s0->targetVolume - 0x3E8 < 0x1D4C) {
            s0->targetVolume = 0x1D4C;
        } else {
            s0->targetVolume = s0->targetVolume - 0x3E8;
        }
    } else {
        if (s0->curVolume - 0x64 < 0x1F40) {
            s0->curVolume = 0x1F40;
        } else {
            s0->curVolume = s0->curVolume - 0x64;
        }
        if (s0->curVolume < s0->targetVolume + 0x3E8) {
            s0->targetVolume = s0->curVolume;
        } else {
            s0->targetVolume = s0->targetVolume + 0x3E8;
        }
    }
    n_alSndpPostEvent(s0->sndHandleA, 8, s0->targetVolume);
    n_alSndpPostEvent(s0->sndHandleB, 8, s0->targetVolume);
    if (s0->flags & 0x17) {
        s16 snd = 0x1E8;
        if ((D_80767CC0 - s0->lastTick) >= 6U) {
            s0->lastTick = D_80767CC0;
            s0->stepCount = 0;
            if (s0->flags & 0x10) {
                snd = 0x42B;
            } else if (s0->flags & 4) {
                snd = 0x1EA;
            } else if (s0->flags & 2) {
                snd = 0x1E7;
            }
            sfxPlayOnFreeSlot(snd, 0x58EF, 64.0f, 1.0f, 0x14, 0x80);
        }
        if (s0->curVolume + 0x4650 >= 0x8000) {
            s0->curVolume = 0x7FFF;
        } else {
            s0->curVolume = s0->curVolume + 0x4650;
        }
        s0->flags &= 0xFFE0;
    }
    if (s0->flags & 8) {
        if ((D_80767CC0 - s0->lastTick) >= 6U) {
            if (s0->stepCount == 0) {
                s0->lastTick = D_80767CC0;
            }
            s0->stepCount++;
            switch (s0->stepCount) {
            case 0x3E:
                s0->stepCount = 0;
                s0->flags &= 0xFFF7;
            case 1:
            case 0x10:
            case 0x1D:
            case 0x29:
            case 0x34:
                sfxPlayOnFreeSlot(0x1E9, 0x58EF, 64.0f, 1.0f, 0, 0x80);
                break;
            }
        }
        if (s0->curVolume + 0x4650 >= 0x8000) {
            s0->curVolume = 0x7FFF;
        } else {
            s0->curVolume = s0->curVolume + 0x4650;
        }
    }
    if ((scriptState->unk12 & 1) && (hudCanRender() != 0)) {
        renderCallbacksRegister(bossDrawRoundText, gCurrentActor, 3);
    }
}


void actorSetNodeFlag(void *, s32);
void actorClearNodeFlag(void *, s32);

void bossSetCannonsVisible(enable)
u8 enable;
{
    if (enable) {
        actorSetNodeFlag(gCurrentActor, 2);
        actorSetNodeFlag(gCurrentActor, 3);
    } else {
        actorClearNodeFlag(gCurrentActor, 2);
        actorClearNodeFlag(gCurrentActor, 3);
    }
}

typedef struct {
    u8 map;
    u8 unk1;
    s16 flag;
    u8 stage;
    u8 unk5;
} BossB_Struct_800359D0;

extern BossB_Struct_800359D0 D_800359D0[];


void bossUpdateStageState(s16 *outStage) {
    s16 i = 0;
    while (D_800359D0[i].map != 0 && gCurrentMap != D_800359D0[i].map) {
        i++;
    }
    if (D_800359D0[i].map != 0 && D_800359D0[i].stage == *outStage) {
        if (flagGet(D_800359D0[i].flag, 2) != 0) {
            *outStage = D_800359D0[i].unk5;
        }
    }
}

void bossPlayStageMusic(void) {
    s16 i = 0;
    while (D_800359D0[i].map != 0 && gCurrentMap != D_800359D0[i].map) {
        i++;
    }
    if (D_800359D0[i].map != 0) {
        flagSet(D_800359D0[i].flag, 1, 2);
    }
}
