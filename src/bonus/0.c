#include "common.h"
#include "actor.h"
#include "proto/bonus/0.h"
#include "proto/bonus/12A0.h"
#include "proto/boot/3630.h"
#include "proto/boot/3D20.h"
#include "proto/global/1025E0.h"
#include "proto/global/103AB0.h"
#include "proto/global/112080.h"
#include "proto/global/126260.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/13A7A0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/450.h"
#include "proto/global/7130.h"
#include "proto/global/90D80.h"
#include "proto/global/9DD70.h"
#include "proto/global/A7710.h"
#include "proto/global/AA960.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/FCCD0.h"

extern Gfx D_1000118;
extern Gfx D_2000180;

typedef struct LB3bState {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[2];
    u8 unk8;
    u8 unk9;
} LB3bState;

Gfx *bonusRenderCounterHud(Gfx *gdl, Actor *actor) {
    LB3bState *s = *(LB3bState **)((u8 *)actor + 0x178);

    if (hudCanRender()) {
        gSPDisplayList(gdl++, &D_1000118);
        gdl = func_8070068C(gdl);
        gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
        gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gdl = hudDrawRollingCounter(
            textDrawAnimated(gdl, s->unk9, 8, 30.0f, 36.0f, 0.0f, 1.5f),
            0x26, 0x32, &s->unk2, s->unk4, &s->unk8);
    }
    return gdl;
}

void bonusInitSounds(void) {
    spawnNodeActivateAndSetState(1, 0x40, 0);
    spawnNodeActivateAndSetState(2, 0x40, 0);
    spawnNodeActivateAndSetState(3, 0x40, 0);
    spawnNodeActivateAndSetState(4, 0x40, 0);
    spawnNodeActivateAndSetState(5, 0x40, 0);
}

typedef struct LB3bSnd {
    u16 unk0;
    u8 pad2[2];
    struct GfSndState *unk4;
    s16 unk8;
    s16 unkA;
    u8 padC[0xC];
    u16 unk18;
} LB3bSnd;

extern Actor *gCurrentActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern s32 gCurrentMap;
extern s16 D_8076AEF2;
extern u16 D_80744508;
extern s16 D_80750AC4;
extern u8 D_807FBDC4;
extern u8 D_8002D863[];


void bonusControllerUpdate(void) {
    s16 i;
    LB3bState *s;
    u8 challengeType;
    u8 targetCount;
    u8 *messageText;
    u8 hasMessage;
    u8 triggerKind;
    u8 endOnTrigger;
    u8 *msgBuf;
    s32 pad5C;
    s32 pad58;
    u8 *msgBufCount;
    s32 pad50;
    s32 pad4C;
    s32 sfxId;
    u8 *pv;

    s = *(LB3bState **)((u8 *)gCurrentActor + 0x178);
    behaviourFrameBegin();
    challengeType = gBehaviourExtraState->respawnDelay;
    targetCount = gBehaviourExtraState->unkA;
    commandQueuePush(gPrimaryPlayerActor, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y + 30.0f, gPrimaryPlayerActor->z, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    if (!(gCurrentActor->flags & 0x10)) {
        hasMessage = 0;
        currentActorClearFlag();
        gBehaviourAnimState->flags |= 0x80;
        slotQueueSetDisplayMode(2, 0, 1);
        slotQueueSetDisplayMode(5, 0, 1);
        slotQueueSetDisplayMode(4, 0, 2);
        gCurrentActor->state = 0;
        hudSpawnCountdownTimer(0xDC, 0x2A, gBehaviourExtraState->unkB);
        switch (challengeType) {
        case 14:
            csModelStateSetByte((randomNonNegative() >> 15) % 32767 % 4, 1, 1);
        case 0:
        case 4:
        case 13:
tail:
            messageText = textTableGetString(0x1A, 2, 1);
            hasMessage = 1;
            break;
        case 15:
            playerSetKongByActorType(8);
            gActivePlayerActor->state = 0xC;
            gActivePlayerActor->unk155 = 0;
            actorScriptStartByIndex(gActivePlayerActor, 9);
            gActivePlayerActor->speedXZ = 0.0f;
            playerInitMoveParams();
            goto tail;
        case 1:
        case 10:
        case 12:
        case 16:
            s->unk2 = 0;
            break;
        case 3:
            bonusInitSounds();
            break;
        case 5:
            bonusInitSounds();
        case 2:
        case 6:
        case 7:
        case 8:
        case 11:
            D_80750AC4 = 0;
            messageText = textTableGetString(0x1A, 3, 1);
            hasMessage = 1;
            break;
        case 9:
            spawnNodeActivate((randomNonNegative() >> 15) % 32767 % 8 + 0x11, 0)->unk15F = 1;
            break;
        }
        if (hasMessage != 0) {
            s->unk9 = gfxResourceCreate(1, messageText, 8, 0.0f, 0.0f, 0.0f);
            func_806FDAB8(s->unk9, 0.0f);
            s->unk4 = targetCount;
            s->unk2 = targetCount;
        }
    }
    if (gCurrentActor->state == 0) {
        i = 0;
        if (D_807FBDC4 > 0) {
            do {
                if (gActorGlobalState.volumeTriggerQueueOp[i] == 3) {
                    endOnTrigger = 1;
                    triggerKind = ((u8 *)gActorGlobalState.volumeTriggerQueueId[i])[3]; // unk278[] points at script data read as s16 (1295B0, 80150) and as bytes here
                    switch (challengeType) {
                    case 0:
                        if (s->unk4 != 0) {
                            if (s->unk4 >= 2) {
                                messageText = textTableGetString(0x1A, 0xF, 1);
                                msgBuf = heapAlloc(strlen(messageText) + 5);
                                heapFreeDeferred(msgBuf);
                                _sprintf(msgBuf, "%d %s", s->unk4, messageText);
                            } else {
                                msgBuf = textTableGetString(0x1A, 0x10, 1);
                            }
                            textSpawnMarkerChecked(0, 0, 0x8C, msgBuf, 0, 0x28, 8, 8);
                            endOnTrigger = 0;
                        }
                        break;
                    case 16:
                        if (s->unk2 == 0 && triggerKind != 0x28) {
                            textSpawnMarkerChecked(0, 0, 0x8C, textTableGetString(0x1A, 0x17, 1), 0, 0x28, 8, 8);
                            endOnTrigger = 0;
                        }
                        if (triggerKind == 0x28) {
                            endOnTrigger = 0;
                        }
                        break;
                    case 2:
                        endOnTrigger = 1;
                        if (slotQueueGetValue(0xB, 0) < targetCount) {
                            if (s->unk4 >= 2) {
                                messageText = textTableGetString(0x1A, 0x11, 1);
                                msgBufCount = heapAlloc(strlen(messageText) + 5);
                                _sprintf(msgBufCount, "%d %s", targetCount - slotQueueGetValue(0xB, 0), messageText);
                            } else {
                                msgBufCount = textTableGetString(0x1A, 0x12, 1);
                            }
                            textSpawnMarkerChecked(0, 0, 0x8C, msgBufCount, 0, 0x28, 8, 8);
                            endOnTrigger = 0;
                        }
                        break;
                    case 7:
                    case 8:
                    case 9:
                    case 11:
                    case 15:
                        endOnTrigger = 0;
                        break;
                    case 12:
                    case 13:
                        endOnTrigger = 0;
                        if (triggerKind != 0x12) {
                            if (triggerKind == 0x27) {
                                gCurrentActor->unk15F += 1;
                                if (gCurrentActor->unk15F >= 3) {
                                    csModelStateSetFirstByte(2, 0xA);
                                }
                            } else {
                                bonusEndLose(1, 1);
                            }
                        }
                        break;
                    }
                    if (endOnTrigger != 0) {
                        bonusEndWin(1, 0xE);
                        func_80726EE0(0);
                    }
                }
            } while (++i < D_807FBDC4);
        }
    }
    if (gCurrentActor->state == 0) {
        switch (challengeType) {
        case 15:
            func_80724A20();
        case 4:
        case 11:
        case 13:
        case 14:
            if (s->unk4 == 0) {
                bonusEndWin(1, 0xE);
            }
        case 0:
            if ((((targetCount - D_80744508) < 0) ? 0 : (targetCount - D_80744508)) != s->unk4) {
                func_806FDAB8(s->unk9, 3.1415927f);
                s->unk4 = ((targetCount - D_80744508) < 0) ? 0 : (targetCount - D_80744508);
            }
            goto render;
        case 7:
        case 8:
            func_80724A20();
            goto render;
        case 5:
            if (gCurrentMap == 0x85 && s->unk4 == 1) {
                if (gCurrentActor->unk155 == 0) {
                    gCurrentActor->unk155 += 1;
                    csSendActorMessagePayload(0, 0);
                    csSendActorMessagePayload(1, 0);
                    csSendActorMessagePayload(2, 0);
                }
            }
        case 6:
            if (s->unk4 == 0) {
                bonusEndWin(1, 0xE);
            }
        case 2:
            if ((((targetCount - slotQueueGetValue(0xB, 0)) < 0) ? 0 : (targetCount - slotQueueGetValue(0xB, 0))) != s->unk4) {
                func_806FDAB8(s->unk9, 3.1415927f);
                s->unk4 = ((targetCount - slotQueueGetValue(0xB, 0)) < 0) ? 0 : (targetCount - slotQueueGetValue(0xB, 0));
            }
render:
            if (s->unk0 >= 2) {
                renderCallbacksRegister(bonusRenderCounterHud, gCurrentActor, 3);
            }
            break;
        case 9:
        case 10:
        case 12:
        case 16:
            func_80724A20();
            break;
        }
    }
    switch (s->unk0) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            if (D_8076AEF2 == 0x11) {
                resQueueSetValue(2);
            }
            resQueueAttachActor(gCurrentActor, 0, D_8002D863[challengeType << 2]);
            s->unk0 += 1;
        }
        break;
    case 1:
        if (!(gCurrentActor->flags & 0x02000000)) {
            camResumePath();
            hudCountdownTimerStart(gCurrentActor->parentActor);
            switch (gCurrentMap) {
            case 3:
            case 0x23:
            case 0x32:
            case 0xA5:
            case 0xC9:
            case 0xCA:
            case 0xD1:
            case 0xD2:
            case 0xD3:
            case 0xD4:
                sfxId = 0x75;
                break;
            default:
                switch (challengeType) {
                case 1:
                    sfxId = 0x59;
                    break;
                case 0:
                    sfxId = 0x52;
                    break;
                default:
                    sfxId = 8;
                    break;
                }
                break;
            }
            sfxAllocateChannel(sfxId, 1.0f);
            s->unk0 += 1;
        }
        break;
    }
    switch (gCurrentActor->state) {
    case 0:
        if ((challengeType == 1 || challengeType == 0 || challengeType == 2 || challengeType == 0x10) && gPrimaryPlayerActor->y < 0.0f) {
            bonusEndLose(1, 1);
            return;
        }
        if (challengeType == 4 && gPrimaryPlayerActor->y < -20.0f) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x362, 0xFF, 0x7F, 0);
            bonusEndLose(0, 1);
            camStartPath(gCurrentActor, 1, 1);
            return;
        }
        if (gPrimaryPlayerActor->state == 0x73) {
            if (challengeType == 1) {
                bonusEndLose(1, 0x13);
                return;
            }
            bonusEndLose(1, 1);
            return;
        }
        if (challengeType == 3 && gPrimaryPlayerActor->state == 0x31) {
            bonusEndLose(1, 0x14);
            return;
        }
        pv = &challengeType; // FAKE: address-taken challengeType keeps the 0x78 frame with challengeType at sp+0x6F (without it: 0x80, sp+0x77)
        if (gCurrentActor->parentActor->state == 5) {
            if (*pv == 3) {
                bonusEndWin(1, 0x15);
                return;
            }
            bonusEndLose(1, 0x16);
            return;
        }
        break;
    case 1:
        gCurrentActor->parentActor->state = 0;
        gCurrentActor->state += 1;
        break;
    case 0x27:
        func_806FDAB8(s->unk9, 3.1415927f);
        s->unk4 -= 1;
        if (s->unk4 == 0) {
            bonusEndWin(1, 0xE);
            return;
        }
        gCurrentActor->state = 0;
        break;
    case 0x28:
        s->unk2 = 1;
        gCurrentActor->state = 0;
        break;
    case 0x37:
        bonusEndLose(1, 1);
        return;
    case 0x12:
        bonusEndWin(1, 0xE);
        break;
    }
}

Gfx *bonusSetupHudGdl(Gfx *gdl, u8 unused) {
    gSPDisplayList(gdl++, &D_1000118);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
    return gdl;
}


s32 bonusGetSoundForMap(void) {
    switch (gCurrentMap) {
    case 0x35:
        return 0x261;
    case 0x49:
        return 0x262;
    case 0x9B:
        return 0x263;
    case 0x9C:
        return 0x264;
    case 0x9F:
        return 0x265;
    case 0x9D:
        return 0x266;
    case 0x9E:
        return 0x267;
    case 0xA0:
        return 0x268;
    case 0xA1:
        return 0x269;
    case 0xA2:
        return 0x26A;
    default:
        return -1;
    }
}

extern ALBank *D_8076D1F8;
extern PlayerState *gActivePlayerState;

void bonusMazeChallengeUpdate(void) {
    LB3bSnd *snd;

    snd = *(LB3bSnd **)((u8 *)gCurrentActor + 0x178);
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        snd->unk0 = 0x12C;
        snd->unkA = 0;
        snd->unk8 = 0;
        n_alSndpPlay(D_8076D1F8, 0x1E6, 0, 0x40, 1.0f, 0x80, &snd->unk4);
        hudSpawnCountdownTimer(0xDC, 0x2A, gBehaviourExtraState->unkB);
        spawnNodeActivateAndSetState(1, 0x40, 0x10);
        spawnNodeActivateAndSetState(2, 0x40, 0x10);
        spawnNodeActivateAndSetState(3, 0x40, 0x10);
        spawnNodeActivateAndSetState(4, 0x40, 0x10);
        gCurrentActor->state = 0;
        gCurrentActor->unk155 = 0;
        camRequestPathLength();
        snd->unk18 = camStartPath(0, 0, 1);
    }
    switch (gCurrentActor->state) {
    case 0:
        if (snd->unk18 != 0) {
            snd->unk18--;
        } else {
            hudCountdownTimerStart(gCurrentActor->parentActor);
            gCurrentActor->state = 1;
        }
        break;
    case 1:
        if (gCurrentActor->parentActor->state == 5) {
            textSpawnMarkerChecked(0x81, 0, 0x78, textTableGetString(0x1A, 0x15, 1), 0, 0x28, 8, 8);
            func_80726EE0(0);
            sfxAllocateChannel(0x28, 1.0f);
            actorSpawnNodeEntryScaled(0x56, 588.0f, 240.0f, 582.0f, 0, 0, bonusGetSoundForMap(), 0);
            gCurrentActor->state = 2;
        }
        if (gPrimaryPlayerActor->state == 0x39) {
            mapTransitionToPreviousOrExit();
            func_806C9974(0, 0x40);
            gCurrentActor->state = 2;
        }
        break;
    }
    {
        s32 decayedPitch = snd->unk8 - 0x96;
        snd->unk0--;
        if (decayedPitch < 0x1F40) {
            snd->unk8 = 0x1F40;
        } else {
            snd->unk8 = decayedPitch;
        }
    }
    {
        s32 steppedPitch = snd->unkA + 0x3E8;
        if (snd->unk8 < steppedPitch) {
            snd->unkA = snd->unk8;
        } else {
            snd->unkA = steppedPitch;
        }
    }
    n_alSndpPostEvent(snd->unk4, 8, snd->unkA);
    if (gActivePlayerState->stateFlags & 0xC0000) {
        if (snd->unk0 < 0x129) {
            snd->unk0 = 0x12C;
            if (gActivePlayerState->stateFlags & 0x40000) {
                if (((randomNonNegative() >> 15) % 1000) & 1) {
                    sfxPlayOnFreeSlot(0x1E7, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
                } else {
                    sfxPlayOnFreeSlot(0x1EA, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
                }
            } else {
                sfxPlayOnFreeSlot(0x1E8, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
            }
        }
        {
            s32 boostedPitch = snd->unk8 + 0x4650;
            if (boostedPitch >= 0x8000) {
                snd->unk8 = 0x7FFF;
            } else {
                snd->unk8 = boostedPitch;
            }
        }
        gActivePlayerState->stateFlags &= ~0xC0000;
    }
    switch (snd->unk0) {
    case 0x0:
    case 0x14:
    case 0x28:
    case 0x3C:
    case 0x50:
        sfxPlayOnFreeSlot(0x1E9, 0x7FFF - snd->unk0 * 0x96, 64.0f, 1.0f, 0xA, 0x80);
        if (snd->unk0 == 0) {
            snd->unk0 = 0xC8;
        }
        break;
    }
}
