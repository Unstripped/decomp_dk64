#include "common.h"
#include "actor.h"
#define PROTO_SKIP_csModelStateSetFirstByte // FAKE: callee prototype steer
#define PROTO_SKIP_textSpawnMarkerChecked // FAKE: callee prototype steer
#include "proto/boot/3630.h"
#include "proto/global/100180.h"
#include "proto/global/10E1D0.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/126260.h"
#include "proto/global/1295B0.h"
#include "proto/global/1332B0.h"
#include "proto/global/13A7A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/2DE90.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/55B20.h"
#include "proto/global/63EC0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/9DD70.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"

extern Actor *gSpawnedActor;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
} Rgb8;

const Rgb8 D_80757F70[8] = {
    { 0xFF, 0xFF, 0xFF },
    { 0xC8, 0x00, 0x32 },
    { 0xDC, 0xC8, 0x00 },
    { 0x32, 0xC8, 0x00 },
    { 0xCA, 0x5B, 0xFF },
    { 0x00, 0x96, 0xFF },
    { 0x32, 0x32, 0xFA },
    { 0x00, 0x00, 0x00 },
};

void actorSetTintFromPalette(u8 paletteIdx) {
    gSpawnedActor->tintR = D_80757F70[paletteIdx].r;
    gSpawnedActor->tintG = D_80757F70[paletteIdx].g;
    gSpawnedActor->tintB = D_80757F70[paletteIdx].b;
}

void textSpawnMarkerChecked(s32, s32, s32, u8 *, s32, s32, s32, s32); // FAKE: callee prototype steer

void textSpawnSubtitle(textId, duration, paletteIdx)
u8 textId;
u16 duration;
u8 paletteIdx;
{
    u8 *s;
    u8 line1[0x3C];
    u8 line2[0x40];
    u8 speaker[0x14];
    s16 idx;

    s = textTableGetString(1, textId, 1);
    if (_strchr(s, ':') != 0) {
        _strncpy(speaker, s, idx = _strcspn(s, ":") + 1);
        speaker[idx] = 0;
        textSpawnMarkerChecked(0xA, 0x14, 0x18, speaker, 0, (s16)duration, 0x32, 0x32);
        actorSetTintFromPalette(paletteIdx);
        s += strlen(speaker);
    }
    if ((s16)textGetStringWidth(6, s) >= 0x12D) {
        idx = (s32)strlen(s) / 2;
        if (s[idx] != ' ') {
            do {
                idx--;
            } while (s[idx] != ' ');
        }
        _strncpy(line1, s, idx);
        line1[idx] = 0;
        _strncpy(line2, s + idx + 1, 0xFF);
        textSpawnMarkerChecked(0, 0, 0xCD, line1, 0, duration, 0x32, 0x32);
        actorSetTintFromPalette(paletteIdx);
        textSpawnMarkerChecked(0, 0, 0xD7, line2, 0, duration, 0x32, 0x32);
        actorSetTintFromPalette(paletteIdx);
        return;
    }
    textSpawnMarkerChecked(0, 0, 0xCD, s, 0, duration, 0x32, 0x32);
    actorSetTintFromPalette(paletteIdx);
}

extern Actor *gPrimaryPlayerActor;

Actor *actorFromSpawnNodeOrDefault(s16 nodeId) {
    Actor *v;

    if (nodeId != 0) {
        v = spawnNodeActivate(nodeId, 0);
    }
    if ((nodeId == 0) || (v == 0)) {
        v = gPrimaryPlayerActor;
    }
    return v;
}


#define Matcher14_OFF(p, T, o) (*(T *)((u8 *)(p) + (o)))

extern struct GfSndState *D_807457E4[];
extern u16 D_80747750[];
extern s8 D_8075536C;
extern s8 D_8076AEE0;
extern s16 D_8076AEF2;
extern s32 D_8076D1F8;
extern s32 D_8076D1FC;
extern Actor *gCamActor;
extern u8 D_807F5D6C[];
extern struct GfSndState *D_807F5D70[];
extern s16 D_807F5D7C;
extern Actor *gActivePlayerActor;
extern s32 gGlobalCutsceneFlags;
extern void *gPlayerSlots;
extern f32 gScreenFadeRate;

void func_80028EE8(s32, s32, s32, s32, s32, s32, s32, s32);
void csModelStateSetFirstByte(); // FAKE: callee prototype steer

void camPathCommandDispatch(s32 cmd, s32 params01, s32 params23) {
    s16 params[4];
    PlayerState *playerState;
    Actor *actor;
    Actor *camTarget;
    Actor *q;
    s32 a;
    s32 b;
    f32 posX;
    f32 posY;
    f32 posZ;
    s32 c;
    s32 d;
    s16 idx;
    s16 node;
    Actor *p;

    playerState = gPrimaryPlayerActor->customState;
    actorFindActiveByType(0xC, &camTarget);
    p = (Actor *)((u32)params01 >> 16); // FAKE: dead store; makes the ushr item precede the (s16)arg1 item (spilltemps slot order)
    b = (s16)(params01 & 0xFFFF);
    a = (s16)((u32)params01 >> 16);
    params[0] = a;
    params[1] = b;
    c = (s16)((u32)params23 >> 16);
    params[2] = c;
    d = (s16)(params23 & 0xFFFF);
    params[3] = d;
    if ((u32)d < 0U) { // FAKE: unreachable call precolors d, keeping its item spilled
        sfxSetMode(d);
    }
    switch (cmd & 0xFF) {
        case 0x45:
            spawnNodesSetActorStateByFlag(2, 0x40);
            return;
        case 0x42:
            textSpawnSubtitle(a & 0xFF, (s16)(b != 0 ? b : 0x5A), (u8)c);
            return;
        case 0x41:
            mapTransitionToMenuOrPrevious();
            return;
        case 0x3D:
            mapRequestTransition(D_8076AEF2, 0);
            return;
        case 0x3E:
            mapRequestTransition(0x22, 0xC);
            return;
        case 0x40:
            menuTransitionToCreditsOrMap28(0);
            return;
        case 0x36:
            playerSetKongByActorType(a + 2);
            playerKongStopSoundByState(gPrimaryPlayerActor);
            return;
        case 0x33:
            q = Matcher14_OFF(actorFromSpawnNodeOrDefault(a), void *, 0x17C);
            Matcher14_OFF(q, u8, 0x30) = 0xFE;
            Matcher14_OFF(q, u8, 0x33) = b;
            Matcher14_OFF(q, u8, 0x22) = c;
            Matcher14_OFF(q, u8, 0x32) = d;
            Matcher14_OFF(q, u8, 0x31) = 1;
            return;
        case 0x34:
            q = Matcher14_OFF(actorFromSpawnNodeOrDefault(a), void *, 0x17C);
            Matcher14_OFF(q, u8, 0x30) = 0xFF;
            return;
        case 0x0:
            playerState->unk70 = gPrimaryPlayerActor->yaw;
            playerState->unk74 = b;
            playerState->unk6C = a;
            playerStateQueueCallback(0x17, 0, 0);
            return;
        case 0x1:
            func_80028EE8((c + 6) & 0xFF, 0, 0xC8, a & 0xFF, 0, b + 0x28, 0x64, 0xFF);
            return;
        case 0x2:
            playerState->stateFlags |= 8;
            return;
        case 0x3:
            playerState->stateFlags &= ~8;
            return;
        case 0x24:
            func_80724994(1, a, b, c, d);
            return;
        case 0x5:
            spawnNodeSpawnById(a, 0, 0, 0, 0, 0, 0);
            return;
        case 0x4:
            if (a != 0) {
                func_80724994(3, a, b, c, d);
                return;
            }
            if (b == 2) {
                gActivePlayerActor->sub4->model->animId = -1;
                actorScriptStart(gActivePlayerActor, D_80747750[c]);
                if (d != 0) {
                    scriptSetActorRampTarget(gActivePlayerActor, d / 100.0, 0);
                    return;
                }
            }
        default:
            return;
        case 0x6:
            camSetPathLookActor(spawnNodeActivate(a, 0), b);
            return;
        case 0x7:
            camLoopPathStep(a, (u8)b);
            return;
        case 0x2D:
            camSetPathLookAhead(a);
            return;
        case 0x2E:
            actorFromSpawnNodeOrDefault(a)->eyeHeight = b;
            return;
        case 0x25:
            playerWaypointPathStartPacked(gPrimaryPlayerActor, 0, a, 0);
            return;
        case 0x26:
            csSendActorMessagePayload(a, b);
            return;
        case 0x27:
            node = a;
            idx = b;
            mapChunkEffectSetFlag(node, idx, 0, (u8)c);
            mapChunkEffectSetFlag(node, idx, 1, (u8)c);
            mapChunkEffectSetFlag(node, idx, 2, (u8)c);
            mapChunkEffectSetFlag(node, idx, 3, (u8)c);
            return;
        case 0x8:
            camSetPath(a);
            return;
        case 0x2B:
            transitionSetState(a);
            return;
        case 0x9:
            camSetRollBlend(a, b, c);
            return;
        case 0x10:
            camStartShake(gCamActor, b, a);
            return;
        case 0xA:
            if (a != 0) {
                p = spawnNodeActivate(a, 0);
                if (b != 0) {
                    p->flags |= 4;
                    return;
                }
                p->flags &= ~4;
                return;
            }
            idx = 1;
            p = spawnNodeActivate(idx++, 0);
            if (p != NULL) {
                do {
                    if (b != 0) {
                        p->flags |= 4;
                    } else {
                        p->flags &= ~4;
                    }
                    p = spawnNodeActivate(idx++, 0);
                } while (p != NULL);
                return;
            }
            break;
        case 0xB:
            zoneEntrySpawnEffect(a, b, c, d);
            return;
        case 0x11:
            screenWipeStart(((u32)params01 >> 16) & 0xFF);
            return;
        case 0xC:
            actorAppendCallbackMemcpy8(gCamActor, camTarget, 0x01000000, 1, params, 0);
            return;
        case 0xD:
            actorAppendCallbackMemcpy8(gCamActor, camTarget, 0x01000000, 0x10, params, 0);
            params[3] = -1;
            actorAppendCallbackMemcpy8(gCamActor, camTarget, 0x01000000, 0xE, params, 0);
            return;
        case 0x12:
            actorAppendCallbackMemcpy8(gCamActor, camTarget, 0x01000000, 0x14, params, 0);
            return;
        case 0x31:
            if (d != 0) {
                commandSetParameters(0x320, 0x82, 0, 0x64, 0x64, 0x64);
                commandSetFlags(1, 1);
                return;
            }
            commandSetParameters(0x320, 0x82, 0, a, b, c);
            commandSetFlags(1, 0);
            return;
        case 0x32:
            effectNodeSetTargetPosition(a, b, c, d * 0.01);
            return;
        case 0xE:
            func_80729AA4(a);
            return;
        case 0x16:
            actor = spawnNodeActivate(a, 0);
            if (actor != NULL) {
                if (gGlobalCutsceneFlags & 2) {
                    actorCopyPoseAndScale(gPrimaryPlayerActor, actor, actor->sub4->scaleY);
                } else {
                    actorCopyPoseAndScale(gPrimaryPlayerActor, actor, 0.15f);
                    Matcher14_OFF(gPlayerSlots, u8, 0x2C0) = 1;
                }
                playerResumeLocomotion(gPrimaryPlayerActor);
                gPrimaryPlayerActor->flags |= 4;
                actor->state = 0x40;
                return;
            }
            break;
        case 0x20:
            p = spawnNodeActivate(a, 0);
            if (p != NULL) {
                actorCopyPoseAndScale(p, gPrimaryPlayerActor, gPrimaryPlayerActor->sub4->scaleY);
                gPrimaryPlayerActor->state = 0x77;
                gPrimaryPlayerActor->unk155 = 0;
                return;
            }
            break;
        case 0x29:
            if (camCueTimerIsRunning() == 0) {
                menuTransitionToMap(a, b);
                return;
            }
            break;
        case 0x43:
            if (camCueTimerIsRunning() == 0) {
                D_8075536C = c;
                menuTransitionToMap(a, b);
                return;
            }
            break;
        case 0x3F:
            func_80713EB0(a, b, c);
            return;
        case 0x2A:
            p = spawnNodeActivate(a, 0);
            if (p != NULL) {
                p->state = 0x3C;
                return;
            }
            break;
        case 0x28:
            actor = spawnNodeActivate(a, 0);
            if (actor != NULL) {
                q = spawnNodeActivate(b, 0);
                if (q != NULL) {
                                        actorCopyPoseAndScale(actor, q, q->sub4->scaleY);
                    controllerAnimSetState(actor, q->sub4->model->animId, q->sub4->model->frame, 0.0f);
                    controllerStepMotionWindows(actor);
                    actor->flags |= 4;
                    q->flags &= ~4;
                    return;
                }
            }
            break;
        case 0x13:
            if (a != 0) {
                actor = spawnNodeActivate(a, 0);
            } else {
                actorClearMovementFlags(actor = gPrimaryPlayerActor);
            }
            zoneEntryGetPosition(b, c, &actor->x, &actor->y, &actor->z);
            actorAppendMoveTarget2D(0, actor, actor->x, actor->z, 2, 1);
            {
                s32 t = (d << 12) / 360;
                actor->moveYaw = t;
                actor->yaw = t;
            }
            actor->peakY = actor->y;
            actorUpdateModelMatrix(actor, 0);
            actorCheckWorldBounds(actor);
            return;
        case 0x14:
            if (a >= 0) {
                if (a != 0) {
                    actor = spawnNodeActivate(a, 0);
                } else {
                    actor = gPrimaryPlayerActor;
                }
                D_807F5D7C = sfxPlayAtPositionPooled(actor->x, actor->y, actor->z, b, (u32)(c != 0 ? (f64)c : 127.5), d != 0 ? d : 0x7F, 0, 0, 0.0f, 0);
                return;
            }
            if (b < 0x800) {
                n_alSndpPlay((void *)D_8076D1F8, b, (u32)(c != 0 ? ((f64)c / 255.0) * 32767.0 : 16383.5), 0x3F, d != 0 ? (f64)d / 127.0 : 1.0, 0, (u8 *)D_807F5D6C + -(a * 4));
                return;
            }
            n_alSndpPlay((void *)D_8076D1FC, (s16)(b - 0x7FF), (u32)(c != 0 ? ((f64)c / 255.0) * 32767.0 : 16383.5), 0x3F, d != 0 ? (f64)d / 127.0 : 1.0, 0, (u8 *)D_807F5D6C + -(a * 4));
            return;
        case 0x19:
            node = (a > 0 ? a : -a) <= 0 ? 0 : (a > 0 ? a : -a) - 1;
            idx = node;
            n_alSndpStop(D_807F5D70[idx]);
            return;
        case 0x1A:
            n_alSndpStop(D_807457E4[D_807F5D7C]);
            return;
        case 0x38:
            if (a != 0) {
                actor = spawnNodeActivate(a, 0);
            } else {
                actor = gPrimaryPlayerActor;
            }
            sfxPlayActorSound(actor, b, 0, 1, 0, c != 0 ? c : 0xFF, 1.0f, d);
            return;
        case 0x37:
            if (a != 0) {
                actor = spawnNodeActivate(a, 0);
            } else {
                actor = gPrimaryPlayerActor;
            }
            sfxStopSlotSound(actor, 0);
            return;
        case 0x1B:
            sfxStopChannel(a, 0);
            return;
        case 0x44:
            sfxSetMode(a & 0xFF);
            return;
        case 0x3C:
            q = Matcher14_OFF(spawnNodeActivate(1, 0), void *, 0x17C);
            Matcher14_OFF(q, u8, 0xD) |= a;
            return;
        case 0x3B:
            actorFromSpawnNodeOrDefault(a)->unk146 = b;
            return;
        case 0x1C:
            actorFromSpawnNodeOrDefault(a)->yaw = Matcher14_OFF(gPlayerSlots, s16, 0x2C8) & 0xFFF;
            return;
        case 0x30:
            p = actorFromSpawnNodeOrDefault(a);
            if (b >= 0) {
                p->tintR = b;
                p->flags |= 0x800000;
                p->tintG = c;
                p->tintB = d;
                return;
            }
            p->flags &= 0xFF7FFFFF;
            return;
        case 0x2C:
            actor = actorFromSpawnNodeOrDefault(a);
            zoneEntryGetPosition(b, (u8)c, &posX, &posY, &posZ);
            actor->yaw = mathAngleBetweenPoints2D(posX, posZ, actor->x, actor->z);
            return;
        case 0x2F:
            csModelStateSetFirstByte((s16)a, (s16)(u16)d); // FAKE: prevents sharing this narrowing across calls
            if (b != 0) {
                csModelStateSetFirstByte(b, (s16)d);
            }
            if (c != 0) {
                csModelStateSetFirstByte((s16)c, (s16)d);
                return;
            }
            break;
        case 0x15:
            csModelStateSetFirstByte((s16)a, (s16)b);
            return;
        case 0x17:
            sfxAllocateChannel(a, b != 0 ? (f64)b / 255.0 : 1.0);
            return;
        case 0x18:
            resQueueSetValue(1);
            /* fallthrough */
        case 0x39:
            resQueueAttachActor(actorFromSpawnNodeOrDefault(a), (u16)b, (u8)c);
            return;
        case 0x1E:
            actorSpawn(0x108, 0x1D);
            gSpawnedActor->movePitch = c;
            resQueueAttachActor(gSpawnedActor, a & 0xFFFF, (u8)b);
            return;
        case 0x1D:
            camPausePath();
            return;
        case 0x21:
            camSetFlags(gCamActor, 0x8000);
            return;
        case 0x22:
            if (a != 0) {
                mapRequestTransition(a, b);
                return;
            }
            playerRefillHealth(gPrimaryPlayerActor, 0);
            return;
        case 0x23:
            D_8076AEE0 = a;
            gScreenFadeRate = b / 100.0;
            return;
        case 0x3A:
            menuSetTransitionTypeBFlag();
            return;
        case 0x35:
            if (a == 0) {
                func_80687C48();
            }
            break;
    }
}
#undef Matcher14_OFF


extern Actor *gCurrentActor;

s32 currentActorTestClearFlag(void) {
    s32 r = 0;

    if (gCurrentActor->contactFlags & 0x100) {
        gCurrentActor->contactFlags &= 0xFEFF;
        r = 1;
    }
    return r;
}

void currentActorClearFlag(void) {
    gCurrentActor->contactFlags &= 0xFEFF;
}
