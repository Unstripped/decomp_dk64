#include "common.h"
#include "actor.h"
#include "boss.h"
#include "sched.h"
#include "proto/boot/3D20.h"
#include "proto/boss/3840.h"
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/10D2D0.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/13A7A0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/3C10.h"
#include "proto/global/450.h"
#include "proto/global/90D80.h"
#include "proto/global/A7710.h"
#include "proto/global/FCCD0.h"
#include "proto/global/7130.h"


void bossInitScriptData(u8 *data) {
    s16 i;
    u8 (*dst)[2];

    if (gBehaviourAnimState->path != NULL) {
        heapFree(gBehaviourAnimState->path);
    }
    gBehaviourExtraState->pathCount = *data;
    gBehaviourAnimState->path = heapAlloc(*data * 2);
    dst = gBehaviourAnimState->path;
    for (i = 0; i < *data; i++) {
        (*dst)[0] = data[i + 1];
        (*dst)[1] = 0;
        dst++;
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

void bossPickRandomWaypoint(BossScriptState *state, u8 *waypointRanges) {
    u8 prev = gBehaviourWorkState->unk25;
    do {
        s32 rand = randomNonNegative() >> 15;
        u8 offset = state->scriptPos;
        gBehaviourWorkState->unk25 = waypointRanges[offset] + ((rand % 65536) % (waypointRanges[offset + 1] - waypointRanges[offset] + 1));
    } while (gBehaviourWorkState->unk25 == prev);
    state->scriptPos += 2;
}

extern Actor *gCurrentActor;

void bossPickFarthestWaypoint(BossScriptState *state, u8 *waypointRanges) {
    s16 i;
    s32 maxDist = 0;

    for (i = waypointRanges[state->scriptPos]; i <= waypointRanges[state->scriptPos + 1]; i++) {
        u8 idx = gBehaviourAnimState->path[i][0];
        Actor *actor = gCurrentActor;
        ZoneEntry *pt = &D_807FDCA0->entries[idx];
        f32 dz = actor->z - (f32)pt->z;
        f32 dx = actor->x - (f32)pt->x;
        f32 dy = actor->y - (f32)pt->y;
        s32 dist = (s32)sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));

        if (dist > maxDist) {
            maxDist = dist;
            gBehaviourWorkState->unk25 = i;
        }
    }
    state->scriptPos += 2;
}


// Boss actor: Actor plus its component pointers (0x178 script state, 0x17C per-boss state).
typedef struct BossActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
    /* 0x17C */ void *typeState;
} BossActor;

extern Actor *gPrimaryPlayerActor;
extern u8 gGameMode;
extern u8 gScreenRenderFlags;
extern s8 sHudDisabled;


#define BOSS_ACTOR ((BossActor *)gCurrentActor)

u8 bossScriptStep(u8 *script, u16 turnSpeed, f32 fwdSpeed) {
    PlayerState *playerData;
    BossScriptState *scriptState;
    u8 advanceScript;
    u8 didLoop;
    u8 pos;

    playerData = gPrimaryPlayerActor->customState;
    scriptState = BOSS_ACTOR->scriptState;
    didLoop = 0;
    advanceScript = 1;
    switch (BOSS_ACTOR->base.state) {
    case 0x54:
        advanceScript = 0;
        if (BOSS_ACTOR->base.unk155 != 0) {
            if (currentActorTestClearFlag() != 0) {
                advanceScript = 1;
            }
        } else {
            currentActorClearFlag();
            BOSS_ACTOR->base.unk155 = 1;
        }
        break;
    case 0x5F:
        camStartPath(gCurrentActor, script[scriptState->scriptPos++], 1);
        break;
    case 0x5E:
        if (gGameMode == 1) {
            camEndPath(playerData->camActor);
        }
        sHudDisabled = 0;
        BOSS_ACTOR->base.flags &= ~4;
        gScreenRenderFlags |= 0x10;
        scriptState->unk4 = script[scriptState->scriptPos++] * 30;
        break;
    case 0x5D:
        actorSetTargetSpeed(gCurrentActor, script[scriptState->scriptPos++]);
        break;
    case 0x5C:
        {
            u8 *p = BOSS_ACTOR->typeState;
            *p = script[scriptState->scriptPos];
            scriptState->scriptPos++;
        }
        break;
    case 0x5A:
        resQueueAttachActor(gCurrentActor, script[scriptState->scriptPos], script[scriptState->scriptPos + 1]);
        scriptState->scriptPos += 2;
        break;
    case 0x42:
patrol:
        actorMoveWithinZone(0x42, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, turnSpeed, fwdSpeed);
        if (patrolPathStep(BOSS_ACTOR->base.state, 0) == 0) {
            advanceScript = 0;
        }
        break;
    case 0x69:
        gBehaviourWorkState->flags |= 0x20;
        break;
    case 0x58:
        BOSS_ACTOR->base.flags |= 4;
        break;
    case 0x59:
        BOSS_ACTOR->base.flags &= ~4;
        break;
    case 0x51:
        actorScriptStart(gCurrentActor, (script[scriptState->scriptPos] << 8) + script[scriptState->scriptPos + 1]);
        scriptState->scriptPos += 2;
        break;
    case 0x55:
        advanceScript = 0;
        if (BOSS_ACTOR->base.unk155 == 0) {
            pos = scriptState->scriptPos;
            scriptState->unk8[0] = (script[pos] << 8) + script[pos + 1];
            scriptState->scriptPos = pos + 2;
            BOSS_ACTOR->base.unk155 = 1;
        } else {
            scriptState->unk8[0] -= 1;
            if (scriptState->unk8[0] == 0) {
                advanceScript = 1;
            }
        }
        break;
    case 0x23:
        advanceScript = 0;
        if (BOSS_ACTOR->base.unk155 == 0) {
            pos = scriptState->scriptPos;
            scriptState->unk8[0] = script[pos];
            scriptState->scriptPos = pos + 1;
            BOSS_ACTOR->base.unk155 = 1;
            actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkD);
        } else {
            actorMoveWithinZone(0x23, gBehaviourWorkState->unk4->x, gBehaviourWorkState->unk4->z, turnSpeed, fwdSpeed);
            scriptState->unk8[0] -= 1;
            if ((scriptState->unk8[0] == 0) || (playerData->stateFlags & 0x80000)) {
                playerData->stateFlags &= ~0x80000;
                advanceScript = 1;
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
            }
        }
        break;
    case 0x52:
        if (!(BOSS_ACTOR->base.contactFlags & 1)) {
            advanceScript = 0;
        }
        break;
    case 0x53:
        if (BOSS_ACTOR->base.unk155 == 0) {
            advanceScript = 0;
        }
        break;
    case 0x4F:
        scriptState->loopPos = scriptState->scriptPos;
        break;
    case 0x50:
        scriptState->scriptPos = scriptState->loopPos;
        break;
    case 0x66:
        if (gBehaviourWorkState->flags & 8) {
            scriptState->scriptPos = scriptState->loopPos;
        }
        break;
    case 0x63:
        pos = scriptState->scriptPos;
        if (scriptState->unk8[script[pos]] != 0) {
            scriptState->unk8[script[pos]] -= 1;
            advanceScript = 0;
        } else {
            scriptState->scriptPos = pos + 1;
        }
        break;
    case 0x62:
        scriptState->unk8[script[scriptState->scriptPos]] = script[scriptState->scriptPos + 1];
        scriptState->scriptPos += 2;
        didLoop = 1;
        break;
    case 0x64:
        scriptState->unk18[script[scriptState->scriptPos]] = script[scriptState->scriptPos + 1];
        scriptState->scriptPos += 2;
        didLoop = 1;
        break;
    case 0x68:
        gBehaviourWorkState->flags &= 0xFFEF;
        didLoop = 1;
        break;
    case 0x65:
        gBehaviourWorkState->timer = script[scriptState->scriptPos];
        scriptState->scriptPos++;
        didLoop = 1;
        break;
    case 0x67:
        bossPickRandomWaypoint(scriptState, script);
        advanceScript = 0;
        BOSS_ACTOR->base.state = 0x42;
        BOSS_ACTOR->base.unk155 = 0;
        goto patrol;
    case 0x4C:
        bossPickFarthestWaypoint(scriptState, script);
        advanceScript = 0;
        BOSS_ACTOR->base.state = 0x42;
        BOSS_ACTOR->base.unk155 = 0;
        goto patrol;
    case 0x4B:
        gBehaviourWorkState->unk25++;
        if (script[scriptState->scriptPos + 1] < gBehaviourWorkState->unk25) {
            gBehaviourWorkState->unk25 = script[scriptState->scriptPos];
        }
        scriptState->scriptPos += 2;
        advanceScript = 0;
        BOSS_ACTOR->base.state = 0x42;
        BOSS_ACTOR->base.unk155 = 0;
        goto patrol;
    case 0x41:
        gBehaviourWorkState->unk25 = script[scriptState->scriptPos];
        scriptState->scriptPos++;
        advanceScript = 0;
        BOSS_ACTOR->base.state = 0x42;
        BOSS_ACTOR->base.unk155 = 0;
        goto patrol;
    case 0x49:
    case 0x4A:
        advanceScript = 0;
        switch (BOSS_ACTOR->base.unk155) {
        case 0:
            BOSS_ACTOR->base.alpha -= 0xA;
            if (BOSS_ACTOR->base.alpha < 0) {
                BOSS_ACTOR->base.alpha = 0;
                BOSS_ACTOR->base.unk155++;
            }
            break;
        case 1:
            if (BOSS_ACTOR->base.state == 0x49) {
                gBehaviourWorkState->unk25 = script[scriptState->scriptPos];
                scriptState->scriptPos++;
            } else {
                bossPickRandomWaypoint(scriptState, script);
            }
            patrolPathStep(0x49, 0);
            BOSS_ACTOR->base.x = gBehaviourWorkState->targetX;
            BOSS_ACTOR->base.z = gBehaviourWorkState->targetZ;
            BOSS_ACTOR->base.unk155++;
            break;
        case 2:
            BOSS_ACTOR->base.alpha += 0xA;
            if (BOSS_ACTOR->base.alpha >= 0x100) {
                BOSS_ACTOR->base.alpha = 0xFF;
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
        BOSS_ACTOR->base.state = script[scriptState->scriptPos];
        scriptState->scriptPos++;
        BOSS_ACTOR->base.unk155 = 0;
    }
    return didLoop;
}



void bossClearMinigame(void) {
    mapTransitionToMenuOrPrevious();
}

void sfxAllocateChannel(s32, f32);
void actorSpawnNodeEntryScaled(s16, f32, f32, f32, s32, s32, s32, Actor *);

extern void *D_8074E880[];

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
        effectSetSpeed((s32)gBehaviourTargetActor);
        effectCreateAtPosition(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3], 1.8f, gBehaviourTargetActor->x, gBehaviourTargetActor->y + (f32)gBehaviourTargetActor->eyeHeight, gBehaviourTargetActor->z);
    }
    actorSpawnNodeEntryScaled(0x48, (f32)x, (f32)y, (f32)z, (s32)unkRot, (s32)unkScale, (s16)flag, 0);
}



void bossStartCountdownTimer(void) {
    hudSpawnCountdownTimer(-0x7F83, 0xD2, 0xB4);
    hudCountdownTimerStart(gCurrentActor->parentActor);
}

extern PlayerStruct *gPlayerSlots;
extern u8 D_80750AD4;
extern Gfx D_1000118;

Gfx *bossDrawRoundText(Gfx *glist, Actor *actor) {
    f32 scaleMtx[4][4];
    f32 transMtx[4][4];
    Mtx *mtx;
    u8 textBuf[16];

    mtx = heapAlloc(sizeof(Mtx));
    heapFreeDeferred(mtx);
    guScaleF(scaleMtx, 0.6f, 0.6f, 1.0f);
    guTranslateF(transMtx, 100.0f, (f32)(gPlayerSlots->rect[3] * 4 - 0x3C), 0.0f);
    guMtxCatF(scaleMtx, transMtx, scaleMtx);
    guMtxF2L(scaleMtx, mtx);
    gSPMatrix(glist++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    _sprintf(textBuf, "ROUND %d", D_80750AD4);
    gSPDisplayList(glist++, &D_1000118);
    gDPPipeSync(glist++);
    gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    glist = func_8070068C(glist);
    return textDrawStringVtx(glist, 1, 0, 0, textBuf, 0);
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
    struct GfSndState *sndHandleA;
    struct GfSndState *sndHandleB;
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
extern ALBank *D_8076D1F8;
extern SchedStruct gScheduler;
extern s32 gCurrentMap;

void func_80724A20(void);  // FAKE: callee prototype steer


void bossRoundFrame(u8 *script) {
    BossScriptState *scriptState;
    u8 mapOffset;
    s16 mapFlag;
    BossSoundState *sound;

    scriptState = BOSS_ACTOR->scriptState;
    mapOffset = gCurrentMap - 0xCB;
    sound = BOSS_ACTOR->typeState;
    if (gPrimaryPlayerActor->y < 30.0f) {
        gPrimaryPlayerActor->x = 780.0f;
        gPrimaryPlayerActor->y = 50.0f;
        gPrimaryPlayerActor->z = 750.0f;
        effectCreateAtPosition(D_8071FE08, 1.0f, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y, gPrimaryPlayerActor->z);
    }
    if (!(BOSS_ACTOR->base.flags & 0x10)) {
        slotQueueSetDisplayMode(5, 0, 1);
        slotQueueSetDisplayMode(2, 0, 1);
        BOSS_ACTOR->base.flags &= 0xFFFDFFFF;
        if ((scriptState->phase == 0) || (BOSS_ACTOR->base.actorType != 0x126)) {
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
                BOSS_ACTOR->base.state = 0x6A;
                BOSS_ACTOR->base.unk155 = 0;
            }
        }
        n_alSndpPlay(D_8076D1F8, 0x1E6, 0, 0x40, 1.0f, 0x80, &sound->sndHandleA);
        n_alSndpPlay(D_8076D1F8, 0x119, 0, 0x40, 1.0f, 0x80, &sound->sndHandleB);
    }
    func_80724A20();
    switch (BOSS_ACTOR->base.state) {
    case 0x37:
        if (BOSS_ACTOR->base.unk155 == 0) {
            hudCountdownTimerHold(BOSS_ACTOR->base.parentActor);
        }
        break;
    case 0x6A:
        if (BOSS_ACTOR->base.unk155 == 0) {
            actorScriptStart(gCurrentActor, 0);
            BOSS_ACTOR->base.unk155++;
        }
        break;
    case 0x6C:
        scriptState->unk12 |= 1;
        bossStartCountdownTimer();
        if ((scriptState->phase != 0) && (BOSS_ACTOR->base.actorType == 0x126)) {
            hudCountdownTimerResume(BOSS_ACTOR->base.parentActor);
        }
        BOSS_ACTOR->base.state = script[scriptState->scriptPos];
        scriptState->scriptPos++;
        BOSS_ACTOR->base.unk155 = 0;
        break;
    default:
        if ((BOSS_ACTOR->base.parentActor != NULL) && (BOSS_ACTOR->base.parentActor->state == 5)) {
            bossResetAudioChannels();
            BOSS_ACTOR->base.state = 0x6A;
            BOSS_ACTOR->base.unk155 = 0;
            camStartPath(gCurrentActor, D_800359C4[mapOffset], 1);
            flagSet(0x5A, 1, 2);
        }
        break;
    }
    if (!(BOSS_ACTOR->base.flags & 0x10)) {
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
                    BOSS_ACTOR->base.state = 0x6A;
                    BOSS_ACTOR->base.unk155 = 0;
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
        sound->curVolume = 0x1D4C;
        if (sound->targetVolume - 0x3E8 < 0x1D4C) {
            sound->targetVolume = 0x1D4C;
        } else {
            sound->targetVolume = sound->targetVolume - 0x3E8;
        }
    } else {
        if (sound->curVolume - 0x64 < 0x1F40) {
            sound->curVolume = 0x1F40;
        } else {
            sound->curVolume = sound->curVolume - 0x64;
        }
        if (sound->curVolume < sound->targetVolume + 0x3E8) {
            sound->targetVolume = sound->curVolume;
        } else {
            sound->targetVolume = sound->targetVolume + 0x3E8;
        }
    }
    n_alSndpPostEvent(sound->sndHandleA, 8, sound->targetVolume);
    n_alSndpPostEvent(sound->sndHandleB, 8, sound->targetVolume);
    if (sound->flags & 0x17) {
        s16 snd = 0x1E8;
        if ((gScheduler.unk280 - sound->lastTick) >= 6U) {
            sound->lastTick = gScheduler.unk280;
            sound->stepCount = 0;
            if (sound->flags & 0x10) {
                snd = 0x42B;
            } else if (sound->flags & 4) {
                snd = 0x1EA;
            } else if (sound->flags & 2) {
                snd = 0x1E7;
            }
            sfxPlayOnFreeSlot(snd, 0x58EF, 64.0f, 1.0f, 0x14, 0x80);
        }
        if (sound->curVolume + 0x4650 >= 0x8000) {
            sound->curVolume = 0x7FFF;
        } else {
            sound->curVolume = sound->curVolume + 0x4650;
        }
        sound->flags &= 0xFFE0;
    }
    if (sound->flags & 8) {
        if ((gScheduler.unk280 - sound->lastTick) >= 6U) {
            if (sound->stepCount == 0) {
                sound->lastTick = gScheduler.unk280;
            }
            sound->stepCount++;
            switch (sound->stepCount) {
            case 0x3E:
                sound->stepCount = 0;
                sound->flags &= 0xFFF7;
            case 1:
            case 0x10:
            case 0x1D:
            case 0x29:
            case 0x34:
                sfxPlayOnFreeSlot(0x1E9, 0x58EF, 64.0f, 1.0f, 0, 0x80);
                break;
            }
        }
        if (sound->curVolume + 0x4650 >= 0x8000) {
            sound->curVolume = 0x7FFF;
        } else {
            sound->curVolume = sound->curVolume + 0x4650;
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
