#include "common.h"
#include "proto/critter/5110_battle_arena.h"
#include "proto/global/1025E0_gfx_resource.h"
#include "proto/global/112080_resource_parse.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/90D80_render_callbacks.h"
#include "proto/global/A7710_countdown_timer.h"
#include "proto/global/FCCD0_slot_queue.h"

typedef struct CritterBattleArenaState {
    s16 timer;
    u8 textGfxHandle;
    u8 pad3;
    s16 timeLimit;
} CritterBattleArenaState;

// This TU's .data (0x80029FA0-0x80029FB0). Global code (80150, 936B0, F9450) also decrements critterArenaTargetsLeft.
s8 critterArenaTargetsLeft = 0;
u16 critterArenaSavedAmmo = 0;
s8 critterArenaWon = 0;

s32 critterBitwiseNot(s32 val) {
    return ~val;
}

extern u8 gGameMode;
extern OSMesgQueue gPiDmaMesgQueue;
extern s32 gCurrentMap;
extern OSIoMesg gPiDmaIoMesg;
extern Actor *gCurrentActor;

void critterBattleArenaUpdate(void) {
    u16 *throwAmmo = &gPlayerInventoryTable[0].throwAmmo;
    u16 ammo;
    CritterBattleArenaState *challengeState;
    s32 *alignedBuf;
    void (*dcacheFunc)(void *, s32);
    s32 pad2;
    s32 mapChallengeIdx;
    s32 rewardFlag;
    s32 dmaBuffer[6];
    s32 pad3;
    s32 dmaRomOffset;
    s32 pad4[4];
    s32 returnMap;
    s32 returnExit;

    challengeState = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        critterArenaWon = 0;
        camStartPath(0, 0, 1);
        ammo = *throwAmmo;
        critterArenaSavedAmmo = ammo;
        *throwAmmo = 0;
        slotQueueSetShownValue(4, 0, 0);
        switch (gCurrentMap) {
        case 0xB1:
            challengeState->timeLimit = 0x3C;
            critterArenaTargetsLeft = 1;
            break;
        case 0xB6:
            challengeState->timeLimit = 0x3C;
            critterArenaTargetsLeft = 1;
            break;
        case 0xB4:
            challengeState->timeLimit = 0x3C;
            critterArenaTargetsLeft = 5;
            break;
        case 0xB5:
            challengeState->timeLimit = 0x3C;
            critterArenaTargetsLeft = 5;
            break;
        }
        gCurrentActor->state = 0;
    }

    switch (gCurrentActor->state) {
    case 0x0:
        if ((gGameMode == 1) && (camIsPathPaused() != 0)) {
            switch (gCurrentMap) {
            case 0xB1:
                mapChallengeIdx = 0;
                break;
            case 0xB6:
                mapChallengeIdx = 1;
                break;
            case 0xB4:
                mapChallengeIdx = 2;
                break;
            case 0xB5:
                mapChallengeIdx = 3;
                break;
            }
            resQueueAttachActor(gCurrentActor, 0x19, mapChallengeIdx);
            gCurrentActor->state = 1;
            hudSpawnCountdownTimer(0xDC, 0x2A, challengeState->timeLimit);
        }
        break;
    case 0x1:
        if (!(gCurrentActor->flags & 0x02000000)) {
            camResumePath();
            gCurrentActor->state = 2;
            hudCountdownTimerStart(gCurrentActor->parentActor);
            sfxAllocateChannel(8, 1.0f);
        }
        break;
    case 0x2:
        alignedBuf = dmaBuffer;
        while ((s32)alignedBuf & 7) {
            alignedBuf++;
        }
        dcacheFunc = (void (*)(void *, s32))critterBitwiseNot(~(s32)osWritebackDCache);
        if (critterArenaTargetsLeft <= 0) {
            gCurrentActor->state = 3;
        }
        dcacheFunc(alignedBuf, 0x10);
        dmaRomOffset = critterBitwiseNot(-0xDC1);
        ((void (*)(void *, s32, s32, s32, void *, s32, void *))critterBitwiseNot(~(s32)osPiStartDma))(&gPiDmaIoMesg, 0, 0, dmaRomOffset, alignedBuf, 0x10, &gPiDmaMesgQueue);
        if (gCurrentActor->parentActor->state == 5) {
            gCurrentActor->state = 0xFF;
        }
        ((void (*)(void *, s32, s32))critterBitwiseNot(~(s32)osRecvMesg))(&gPiDmaMesgQueue, 0, 1);
        ((void (*)(void *, s32))critterBitwiseNot(~(s32)osInvalDCache))(alignedBuf, 0x10);
        alignedBuf[0] += alignedBuf[1];
        if (alignedBuf[0] != 0x0A78F00E) {
            rewardFlag = (gCurrentMap == 0xB6) ? 0x184 : 0x183;
            flagSet(rewardFlag, 0, 0);
        }
        break;
    case 0x3:
        gCurrentActor->parentActor->state = 1;
        challengeState->textGfxHandle = gfxResourceCreate(1, "WELL DONE!", 2, 160.0f, 100.0f, 0.0f);
        sfxPlayOnFreeSlot(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
        challengeState->timer = 0x78;
        gCurrentActor->state = 0xFE;
        critterArenaWon = 1;
        break;
    case 0xFE:
        if (challengeState->timer > 0) {
            challengeState->timer--;
            if (challengeState->timer == 0) {
                if (critterArenaWon != 0) {
                    if (gCurrentMap == 0xB4) {
                        critterArenaSavedAmmo = 0x14;
                    }
                    switch (gCurrentMap) {
                    case 0xB1:
                        rewardFlag = 0x182;
                        break;
                    case 0xB6:
                        rewardFlag = 0x183;
                        break;
                    case 0xB4:
                        rewardFlag = 0x184;
                        break;
                    case 0xB5:
                        rewardFlag = 0x185;
                        break;
                    }
                    flagSet(rewardFlag, 1, 0);
                }
                ammo = critterArenaSavedAmmo;
                *throwAmmo = ammo;
                slotQueueSetShownValue(4, 0, ammo);
                mapFindPreviousSavedMap(&returnMap, &returnExit);
                mapTransitionExitCurrent(returnMap, 0);
            }
        }
        break;
    case 0xFF:
        critterArenaWon = 0;
        challengeState->textGfxHandle = gfxResourceCreate(1, "TIME OUT!", 2, 160.0f, 100.0f, 0.0f);
        challengeState->timer = 0x78;
        gCurrentActor->state = 0xFE;
        break;
    }
    renderCallbacksRegister(&critterRenderCenterImage, gCurrentActor, 3);
}

extern Gfx D_1000118;
extern Mtx D_2000180;

Gfx *critterRenderCenterImage(Gfx *glistp, Actor *actor) {
    CritterBattleArenaState *challengeState = actor->customState;

    gSPDisplayList(glistp++, &D_1000118);
    gDPPipeSync(glistp++);
    gDPSetPrimColor(glistp++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_TEX_EDGE2);
    gSPMatrix(glistp++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (actor->state == 0xFE) {
        glistp = textDrawAnimated(glistp, challengeState->textGfxHandle, 2, 160.0f, 100.0f, 0.0f, 1.5f);
    }
    return glistp;
}

