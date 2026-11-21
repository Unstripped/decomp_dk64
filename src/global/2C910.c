#include "common.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_csModelStateSetFirstByte // ORIG: hides the shared (s16, s16) prototype; the target passes the s32 b unconverted (lw a0,68(sp) at 0x1374), see the declaration below
#define PROTO_SKIP_textSpawnMarkerChecked // ORIG: hides the shared (u8, s16, s16, u8 *, u16, u16, u8, u8) prototype; the target promotes the u16 holdTime argument once (lhu t2,222(sp) at 0x118, sw t2,56(sp) at 0x128), see the declaration below
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

u16 gScriptAnimScriptIds[210] = {
    0x027B, 0x027C, 0x027D, 0x027E, 0x02D3, 0x02D4, 0x02D5, 0x0273,
    0x0272, 0x0271, 0x0270, 0x02B0, 0x0240, 0x0241, 0x0242, 0x0243,
    0x032A, 0x0274, 0x0275, 0x027F, 0x035C, 0x01A1, 0x01A2, 0x022B,
    0x0368, 0x01EC, 0x01ED, 0x032B, 0x032C, 0x036F, 0x0370, 0x0371,
    0x0372, 0x0383, 0x0384, 0x0385, 0x0386, 0x0387, 0x0388, 0x0389,
    0x038A, 0x0391, 0x0382, 0x038F, 0x0390, 0x0392, 0x0393, 0x0394,
    0x0381, 0x01EF, 0x01F0, 0x0396, 0x0397, 0x0399, 0x039A, 0x039B,
    0x039D, 0x039C, 0x0398, 0x022A, 0x037E, 0x01F2, 0x01F3, 0x01F4,
    0x01F1, 0x01EE, 0x029E, 0x03AC, 0x03AD, 0x03AE, 0x0014, 0x03A3,
    0x03A4, 0x03A5, 0x03A6, 0x03BF, 0x03C0, 0x038B, 0x038D, 0x0058,
    0x0059, 0x005A, 0x011D, 0x011F, 0x038E, 0x03C3, 0x0369, 0x03C4,
    0x03C5, 0x03C7, 0x03C8, 0x03C9, 0x03CB, 0x03CC, 0x0153, 0x0154,
    0x0155, 0x011E, 0x03CD, 0x03CE, 0x03CF, 0x03D2, 0x03D3, 0x038C,
    0x03D1, 0x03D0, 0x036A, 0x036C, 0x03CA, 0x03C6, 0x036D, 0x037F,
    0x0380, 0x03ED, 0x03D5, 0x03D4, 0x03D6, 0x0373, 0x0374, 0x0416,
    0x0417, 0x03D7, 0x0418, 0x0419, 0x041A, 0x041B, 0x041E, 0x041F,
    0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x040C, 0x040D,
    0x041D, 0x041C, 0x0427, 0x0428, 0x0429, 0x042D, 0x0426, 0x040A,
    0x037D, 0x0405, 0x011C, 0x0147, 0x01D1, 0x0176, 0x0057, 0x040B,
    0x03FC, 0x0375, 0x0376, 0x03F2, 0x006F, 0x033D, 0x042B, 0x042C,
    0x0216, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x021A, 0x026D, 0x03E2, 0x03F3, 0x03FA, 0x0000, 0x03F9,
    0x03E4, 0x03E6, 0x042E, 0x0395, 0x043D, 0x043E, 0x01E1, 0x043F,
    0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447,
    0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x0275, 0x044D, 0x044E,
    0x02FE, 0x02FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000,
};
Rgb8 sScriptTintColors[5] = { { 0xFF, 0xFF, 0xFF }, { 0xFF, 0x00, 0x00 }, { 0x00, 0xFF, 0x00 }, { 0x00, 0x00, 0xFF }, { 0xFF, 0xFF, 0x00 } };
u16 sScriptAnimBase[254] = {
    0x0000, 0x0010, 0x0012, 0x0017, 0x0021, 0x0022, 0x0028, 0x002C,
    0x0030, 0x0035, 0x003E, 0x0046, 0x0050, 0x0053, 0x0056, 0x006B,
    0x006E, 0x0071, 0x0072, 0x0079, 0x0087, 0x0089, 0x00A2, 0x00A2,
    0x00B0, 0x00B2, 0x00B8, 0x00C6, 0x00C7, 0x00C7, 0x00CC, 0x00D0,
    0x00D0, 0x00D4, 0x00D9, 0x00E4, 0x00E5, 0x00EC, 0x00EF, 0x00F8,
    0x00FA, 0x0103, 0x0116, 0x011A, 0x011E, 0x0121, 0x0126, 0x0128,
    0x013C, 0x013C, 0x013C, 0x014A, 0x0150, 0x0159, 0x015E, 0x0167,
    0x016C, 0x0170, 0x017A, 0x0181, 0x018B, 0x018E, 0x0193, 0x01A6,
    0x01AA, 0x01AE, 0x01B0, 0x01B3, 0x01BC, 0x01C5, 0x01CD, 0x01CD,
    0x01DA, 0x01E1, 0x01ED, 0x01F2, 0x01FE, 0x0202, 0x0207, 0x020C,
    0x0216, 0x021F, 0x0228, 0x022A, 0x022B, 0x0243, 0x0247, 0x024B,
    0x024D, 0x0250, 0x025E, 0x025E, 0x025E, 0x025E, 0x026C, 0x0274,
    0x027E, 0x0283, 0x0287, 0x0291, 0x0296, 0x029D, 0x02A3, 0x02AB,
    0x02AD, 0x02B6, 0x02B8, 0x02C0, 0x02D8, 0x02E3, 0x02E7, 0x02EA,
    0x02ED, 0x02EF, 0x02F1, 0x02F1, 0x02F1, 0x02F6, 0x02FB, 0x0307,
    0x030A, 0x0317, 0x0344, 0x0346, 0x0347, 0x0372, 0x0378, 0x0391,
    0x0394, 0x039A, 0x03B7, 0x03DA, 0x03EB, 0x03FF, 0x0402, 0x0403,
    0x0404, 0x0407, 0x0409, 0x040B, 0x040C, 0x0424, 0x0434, 0x0441,
    0x0443, 0x0443, 0x0443, 0x0444, 0x0448, 0x044D, 0x0451, 0x045B,
    0x045D, 0x045D, 0x0462, 0x0463, 0x0469, 0x0475, 0x047D, 0x0482,
    0x0485, 0x048D, 0x048E, 0x0493, 0x0496, 0x04A9, 0x04AA, 0x04AB,
    0x04B4, 0x04C0, 0x04D3, 0x04D6, 0x04E5, 0x04F1, 0x04F9, 0x04FA,
    0x04FF, 0x0511, 0x0517, 0x051B, 0x051C, 0x0520, 0x0526, 0x0527,
    0x0533, 0x0538, 0x054E, 0x0556, 0x0557, 0x0558, 0x055F, 0x0565,
    0x0579, 0x058B, 0x0597, 0x0599, 0x059A, 0x059C, 0x059F, 0x05AD,
    0x05B2, 0x05BE, 0x05C4, 0x05C7, 0x05ED, 0x05F0, 0x05FB, 0x05FF,
    0x0600, 0x0602, 0x0603, 0x0607, 0x0608, 0x0609, 0x060D, 0x0615,
    0x0616, 0x061A, 0x061F, 0x062A, 0x063F, 0x0641, 0x0649, 0x0651,
    0x0652, 0x0656, 0x0658, 0x0660, 0x0661, 0x0662, 0x0668, 0x066C,
    0x066F, 0x0673, 0x067F, 0x0687, 0x0688, 0x0689, 0x068D, 0x0694,
    0x0699, 0x069C, 0x069C, 0x06A5, 0x06AC, 0x06AD, 0x06B4, 0x06B9,
    0x06BD, 0x06BE, 0x06BF, 0x06C2, 0x06C3, 0x06C4,
};
Rgb8 sScriptParticleColors[8] = {
    { 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0xFF },
    { 0xFF, 0x00, 0x00 },
    { 0xFF, 0x00, 0xFF },
    { 0x00, 0xFF, 0x00 },
    { 0x00, 0xFF, 0xFF },
    { 0xFF, 0xE6, 0x00 },
    { 0xFF, 0xFF, 0xFF },
};

void actorSetTintFromPalette(u8 paletteIdx) {
    gSpawnedActor->tintR = D_80757F70[paletteIdx].r;
    gSpawnedActor->tintG = D_80757F70[paletteIdx].g;
    gSpawnedActor->tintB = D_80757F70[paletteIdx].b;
}

void textSpawnMarkerChecked(); // ORIG: target passes holdTime as a default-promoted int: duration loaded once (lhu t2,222(sp) at 0x118), spilled to 56(sp) and reloaded with lw at 0x1d8/0x210/0x250 for the three calls; under the owner's u16 prototype each call reloads lhu 222(sp) instead and the frame shrinks 0xd8 -> 0xd0: the original TU had no prototype for textSpawnMarkerChecked in scope

void textSpawnSubtitle(textId, duration, paletteIdx) // ORIG: old-style definition: the call at 0x3e8 passes (s16) duration unconverted (sll a1,v0,0x10 / sra at 0x3e0) into this u16 parameter, so no prototype is in scope there although this definition precedes it; a (u8, u16, u8) definition adds andi a1,v0,0xffff, a (u8, s16, u8) one loses the u16 spill at 0x118
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
    if (_strchr(s, ':') != NULL) {
        _strncpy(speaker, s, idx = _strcspn(s, ":") + 1);
        speaker[idx] = 0;
        textSpawnMarkerChecked(0xA, 0x14, 0x18, speaker, 0, (s16)duration, 0x32, 0x32);
        actorSetTintFromPalette(paletteIdx);
        s += strlen(speaker);
    }
    if ((s16)textGetStringWidth(6, s) >= 0x12D) {
        idx = (s32)strlen(s) / 2;
        while (s[idx] != ' ') {
            idx--;
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
    if (nodeId == 0 || v == NULL) {
        v = gPrimaryPlayerActor;
    }
    return v;
}


extern struct GfSndState *gSfxFreeSlotHandles[];
extern s8 gMenuNextExit;
extern u8 gTransitionFadeType;
extern s16 gPreviousMap;
extern ALBank *gSfxBank;
extern ALBank *gSfxBankHigh;

extern struct GfSndState *D_807F5D70[];
extern s16 D_807F5D7C;
extern Actor *gActivePlayerActor;
extern s32 gGlobalCutsceneFlags;
extern PlayerStruct *gPlayerSlots;
extern f32 gScreenFadeRate;

void func_80028EE8(s32, s32, s32, s32, s32, s32, s32, s32);
void csModelStateSetFirstByte(s32, s16); // ORIG: the original TU declared an int-width first and an s16 second parameter: call 2 passes the s32 b unconverted (lw a0,68(sp) at 0x1374, jal at 0x1380; the shared (s16, s16) prototype adds sll a0,v0,0x10 / sra t2,a0,0x10), while each call narrows its second argument on its own (lh a1,58(sp) at 0x1370/0x1384/0x139c, lh a1,70(sp) at 0x13b8); explicit (s16) casts under an unprototyped declaration share one narrowing spilled to 0x48

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
    s16 chunk;
    s16 slot;
    s16 firstByte;
    u32 hi;
    ScriptedActorState *comp;

    playerState = gPrimaryPlayerActor->customState;
    actorFindActiveByType(0xC, &camTarget);
    hi = (u32)params01 >> 16;
    b = (s16)(params01 & 0xFFFF);
    a = (s16)hi;
    params[0] = a;
    params[1] = b;
    c = (s16)((u32)params23 >> 16);
    params[2] = c;
    d = (s16)(params23 & 0xFFFF);
    params[3] = d;
    firstByte = d;
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
            mapRequestTransition(gPreviousMap, 0);
            return;
        case 0x3E:
            mapRequestTransition(0x22, 0xC);
            return;
        case 0x40:
            menuTransitionToCreditsOrMap28(0);
            return;
        case 0x36:
            playerSetKongByActorType(a + 2);
            playerKongHolsterGun(gPrimaryPlayerActor);
            return;
        case 0x33:
            comp = ((ScriptedActor *)actorFromSpawnNodeOrDefault(a))->scriptState;
            comp->particlePath = 0xFE;
            comp->particleSprite = b;
            comp->particleScalePct = c;
            comp->particleColor = d;
            comp->particleCount = 1;
            return;
        case 0x34:
            comp = ((ScriptedActor *)actorFromSpawnNodeOrDefault(a))->scriptState;
            comp->particlePath = 0xFF;
            return;
        case 0x0:
            playerState->launchYaw = gPrimaryPlayerActor->yaw;
            playerState->launchSpeedY = b;
            playerState->launchSpeedXZ = a;
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
            spawnNodesSendVolumeTrigger(1, a, b, c, d);
            return;
        case 0x5:
            spawnNodeSpawnById(a, 0, 0, 0, 0, 0, 0);
            return;
        case 0x4:
            if (a != 0) {
                spawnNodesSendVolumeTrigger(3, a, b, c, d);
            } else if (b == 2) {
                gActivePlayerActor->sub4->model->animId = -1;
                actorScriptStart(gActivePlayerActor, gScriptAnimScriptIds[c]);
                if (d != 0) {
                    scriptSetActorRampTarget(gActivePlayerActor, d / 100.0, 0);
                }
            }
            return;
        default:
            return;
        case 0x6:
            camSetPathLookActor(spawnNodeActivate(a, 0), b);
            return;
        case 0x7:
            camLoopPathStep(a, b);
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
            chunk = a;
            idx = b;
            mapChunkEffectSetFlag(chunk, idx, 0, c);
            mapChunkEffectSetFlag(chunk, idx, 1, c);
            mapChunkEffectSetFlag(chunk, idx, 2, c);
            mapChunkEffectSetFlag(chunk, idx, 3, c);
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
                actor = spawnNodeActivate(a, 0);
                if (b != 0) {
                    actor->flags |= 4;
                } else {
                    actor->flags &= ~4;
                }
                return;
            }
            idx = 1;
            while ((actor = spawnNodeActivate(idx++, 0)) != NULL) {
                if (b != 0) {
                    actor->flags |= 4;
                } else {
                    actor->flags &= ~4;
                }
            }
            return;
        case 0xB:
            zoneEntrySpawnEffect(a, b, c, d);
            return;
        case 0x11:
            screenWipeStart(hi & 0xFF);
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
            } else {
                commandSetParameters(0x320, 0x82, 0, a, b, c);
                commandSetFlags(1, 0);
            }
            return;
        case 0x32:
            effectNodeSetTargetPosition(a, b, c, d * 0.01);
            return;
        case 0xE:
            spawnNodeSignalActor(a);
            return;
        case 0x16:
            actor = spawnNodeActivate(a, 0);
            if (actor != NULL) {
                if (gGlobalCutsceneFlags & 2) {
                    actorCopyPoseAndScale(gPrimaryPlayerActor, actor, actor->sub4->scaleY);
                } else {
                    actorCopyPoseAndScale(gPrimaryPlayerActor, actor, 0.15f);
                    gPlayerSlots->sizeMode = 1;
                }
                playerResumeLocomotion(gPrimaryPlayerActor);
                gPrimaryPlayerActor->flags |= 4;
                actor->state = 0x40;
            }
            break;
        case 0x20:
            actor = spawnNodeActivate(a, 0);
            if (actor != NULL) {
                actorCopyPoseAndScale(actor, gPrimaryPlayerActor, gPrimaryPlayerActor->sub4->scaleY);
                gPrimaryPlayerActor->state = 0x77;
                gPrimaryPlayerActor->subState = 0;
            }
            break;
        case 0x29:
            if (camCueTimerIsRunning() == 0) {
                menuTransitionToMap(a, b);
            }
            break;
        case 0x43:
            if (camCueTimerIsRunning() == 0) {
                gMenuNextExit = c;
                menuTransitionToMap(a, b);
            }
            break;
        case 0x3F:
            menuTransitionToMapIfUnlocked(a, b, c);
            return;
        case 0x2A:
            actor = spawnNodeActivate(a, 0);
            if (actor != NULL) {
                actor->state = 0x3C;
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
                }
            }
            break;
        case 0x13:
            if (a != 0) {
                actor = spawnNodeActivate(a, 0);
            } else {
                actor = gPrimaryPlayerActor;
                actorClearMovementFlags(actor);
            }
            zoneEntryGetPosition(b, c, &actor->x, &actor->y, &actor->z);
            actorAppendMoveTarget2D(0, actor, actor->x, actor->z, 2, 1);
            actor->moveYaw = (d << 12) / 360;
            actor->yaw = (d << 12) / 360;
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
                D_807F5D7C = sfxPlayAtPositionPooled(actor->x, actor->y, actor->z, b, c != 0 ? c : 127.5, d != 0 ? d : 0x7F, 0, 0, 0.0f, 0);
            } else if (b < 0x800) {
                n_alSndpPlay(gSfxBank, b, c != 0 ? c / 255.0 * 32767.0 : 16383.5, 0x3F, d != 0 ? d / 127.0 : 1.0, 0, &D_807F5D70[-1 - a]);
            } else {
                n_alSndpPlay(gSfxBankHigh, b - 0x7FF, c != 0 ? c / 255.0 * 32767.0 : 16383.5, 0x3F, d != 0 ? d / 127.0 : 1.0, 0, &D_807F5D70[-1 - a]);
            }
            return;
        case 0x19:
            slot = (a > 0 ? a : -a) <= 0 ? 0 : (a > 0 ? a : -a) - 1;
            n_alSndpStop(D_807F5D70[slot]);
            return;
        case 0x1A:
            n_alSndpStop(gSfxFreeSlotHandles[D_807F5D7C]);
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
            comp = ((ScriptedActor *)spawnNodeActivate(1, 0))->scriptState;
            comp->rollToLo |= a;
            return;
        case 0x3B:
            actorFromSpawnNodeOrDefault(a)->segmentFlags = b;
            return;
        case 0x1C:
            actorFromSpawnNodeOrDefault(a)->yaw = gPlayerSlots->camYawInt & 0xFFF;
            return;
        case 0x30:
            actor = actorFromSpawnNodeOrDefault(a);
            if (b >= 0) {
                actor->tintR = b;
                actor->flags |= 0x800000;
                actor->tintG = c;
                actor->tintB = d;
            } else {
                actor->flags &= ~0x800000;
            }
            return;
        case 0x2C:
            actor = actorFromSpawnNodeOrDefault(a);
            zoneEntryGetPosition(b, c, &posX, &posY, &posZ);
            actor->yaw = mathAngleBetweenPoints2D(posX, posZ, actor->x, actor->z);
            return;
        case 0x2F:
            csModelStateSetFirstByte((s16)a, firstByte);
            if (b != 0) {
                csModelStateSetFirstByte(b, firstByte);
            }
            if (c != 0) {
                csModelStateSetFirstByte((s16)c, firstByte);
            }
            break;
        case 0x15:
            csModelStateSetFirstByte((s16)a, b);
            return;
        case 0x17:
            sfxAllocateChannel(a, b != 0 ? b / 255.0 : 1.0);
            return;
        case 0x18:
            resQueueSetValue(1);
            /* fallthrough */
        case 0x39:
            resQueueAttachActor(actorFromSpawnNodeOrDefault(a), b, c);
            return;
        case 0x1E:
            actorSpawn(0x108, 0x1D);
            gSpawnedActor->movePitch = c;
            resQueueAttachActor(gSpawnedActor, a, b);
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
            } else {
                playerRefillHealth(gPrimaryPlayerActor, 0);
            }
            return;
        case 0x23:
            gTransitionFadeType = a;
            gScreenFadeRate = b / 100.0;
            return;
        case 0x3A:
            menuSetTransitionTypeBFlag();
            return;
        case 0x35:
            if (a == 0) {
                effectShowBananaMedalIcon();
            }
            break;
    }
}


extern Actor *gCurrentActor;

s32 currentActorTestClearFlag(void) {
    s32 r = 0;

    if (gCurrentActor->contactFlags & 0x100) {
        gCurrentActor->contactFlags &= ~0x100;
        r = 1;
    }
    return r;
}

void currentActorClearFlag(void) {
    gCurrentActor->contactFlags &= ~0x100;
}
